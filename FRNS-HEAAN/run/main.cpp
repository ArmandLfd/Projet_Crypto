/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/

#include "../src/TestScheme.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <complex>
#include <cstdlib>
#include "../src/Numb.h"
#include "../src/Context.h"
#include "../src/SecretKey.h"
#include "../src/Scheme.h"
#include "../src/EvaluatorUtils.h"
#include "../src/StringUtils.h"
#include "../src/TimeUtils.h"
#include "../src/SchemeAlgo.h"
#include <cstring>
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc,char** argv) {	
	//void TestScheme::testBasic(long logN, long L, long logp, long logSlots) 
	// logp seems to be = to logq -> see Context.cpp line 44-66.
	//In Context.h we can see Q0_BIT_SIZE defined as 61, in the paper logq0 = 61. Line 55 and 60 we can see that we replace that macro by loqp.
	//Print logq at Context.cpp -> print 55
	//
	// Choose a power-of-two interger N/QL
	// logQL -> bit size of QL
	// logslots != logQL -> slots must be same on HEAAN and FRNS-HEAAN
	// logSlots -> slots = 1 << logSlots <-> slots = 2^logSlots mod 32(sizeofBits(long))
	//
	// QL -> Ql = q^l in theory for RNS -> approximate (for 0 <= i <= l) Ql *= qi => QL becomes (for 0 <= i <= L) QL *= qi -> logQL = log(mul qi)
	// In lines 270-292 in Context.cpp, they compute QModp -> array[L][K] -> (for 0 <= i <= l) el[l][j] = (mul qi)mod j
	// See code in comments at those lines
	// Very near of the value said in the pdf : 1) logQL = 323 2) logQL = 602 3) logQL = 857
	// That could explain why there is no way to vary this parameter.
	/*
	TestScheme::testBasic(15, 5, 55, 1);
	
	TestScheme::testBasic(15, 10, 55, 1);
	
	TestScheme::testBasic(16, 15, 55, 1);
	*/

	double maxCountry = 0.0;
	if(argc >= 2) maxCountry = (double) atoi(argv[1]);
	else maxCountry = 187.0;
	
	long slots = 1 << (int) (ceil(log((int)maxCountry)/log(2)));
	
	double numberOfCountry = (double) (1.0/maxCountry);
	complex<double>* listNumber = (complex<double>*) malloc(sizeof(complex<double>)*slots);
	FILE *file = fopen("country_wise_latest.csv","r");
	if (file == NULL){
		return -1;
	}
	long double maxIntFile = 0;
	for (int i =0;i<209;i++){
		long double tmp = 0;
		fscanf(file,"%Lf", &tmp);
		if(tmp>maxIntFile) maxIntFile = tmp;
	}
	fclose(file);
	file = fopen("country_wise_latest.csv","r");
	if (file == NULL){
		return -1;
	}
	for (int i =0;i<slots;i++){
		long double readInt;
		if (i < maxCountry){
			fscanf(file,"%Lf", &readInt);
			listNumber[i].real((double) (readInt/maxIntFile));
		}
		else listNumber[i].real(0.0);
		//cout << listNumber[i] << endl;
	}
	fclose(file);
	//------------------- Crypto
	// Param
	
	long L = 5;
	long K = L + 1;
	long logN = 14;
	long logp = 55;
	TimeUtils timeutils; 
	Context context(logN, logp, L, K);
	SecretKey secretKey(context);
	Scheme scheme(secretKey, context);
	SchemeAlgo algo(scheme);
	scheme.addLeftRotKeys(secretKey);
	//-----------------------------------------
	Ciphertext cipher = scheme.encrypt(listNumber, slots, L);
	timeutils.start("Mean of COVID19 infected");
	algo.partialSlotsSumAndEqual(cipher, slots);
	cout << "After partial sum:" << scheme.decrypt(secretKey, cipher)[0] << endl;
	Ciphertext meanCipher = scheme.multByConst(cipher, numberOfCountry);
	scheme.reScaleByAndEqual(meanCipher, 1);
	cout << "After multiplying by 1/country:" << scheme.decrypt(secretKey, meanCipher)[0] << endl;
	timeutils.stop("Mean of COVID19 infected");

	complex<double>* dvec = scheme.decrypt(secretKey, meanCipher);

	complex<double> meanPlain;
	for (long i = 0; i < maxCountry; ++i) {
		meanPlain += listNumber[i];
	}
	cout << "Sum of each infections:" << meanPlain << endl;
	meanPlain *= numberOfCountry;
	cout << "Multiply by 1/country:" << meanPlain << endl;
	meanPlain *= maxIntFile;
	
	for (int i =0;i<slots;i++) dvec[i] *= maxIntFile;
	
	cout << "Result of mean from plaintext: " << meanPlain << "\nResult of mean from ciphertext:" << dvec[0] << endl;
	//StringUtils::showcompare(meanPlain, dvec, slots, "Mean of COVID19 infected");
	
	free(listNumber);
	return 0;
}
