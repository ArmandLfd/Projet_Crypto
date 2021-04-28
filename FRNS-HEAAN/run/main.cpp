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
	
	int maxCountry = 0;
	if(argc >= 2) maxCountry = atoi(argv[1]);
	else maxCountry = 187;
	
	double numberOfCountry = 1/maxCountry; // Bound = 1.0 
	double* listNumber = (double*) malloc(sizeof(double)*maxCountry);
	FILE *file = fopen("worldometer_data.csv","r");
	if (file == NULL){
		return -1;
	}
	double maxIntFile = 0;
	for (int i =0;i<187;i++){
		double tmp = 0;
		fscanf(file,"%lf", &tmp);
		if(tmp>maxIntFile) maxIntFile = tmp;
	}
	
	for (int i =0;i<maxCountry;i++){
		double readInt;
		fscanf(file,"%lf", &readInt);
		listNumber[i] = (double) readInt/maxIntFile;
		cout << listNumber[i] << endl;
	}
	fclose(file);
	//------------------- Crypto
	// Param
	long slots = maxCountry;
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
	srand(time(NULL));
	//-----------------------------------------
	Ciphertext cipher = scheme.encrypt(listNumber, slots, L);
	timeutils.start("Mean of COVID19 infected");
	Ciphertext sumCipher = algo.partialSlotsSum(cipher, slots);
	Ciphertext meanCipher = scheme.multByConst(sumCipher, numberOfCountry);
	scheme.reScaleByAndEqual(meanCipher, 1);
	timeutils.stop("Mean of COVID19 infected");

	complex<double>* dvec = scheme.decrypt(secretKey, meanCipher);

	double meanPlain;
	for (long i = 0; i < slots; ++i) {
		meanPlain += listNumber[i];
	}
	meanPlain /= maxCountry;

	cout << "Result of mean from plaintext: " << meanPlain << "\nResult of mean from ciphertext:" << dvec[0] << endl;
	//StringUtils::showcompare(meanPlain, dvec, slots, "Mean of COVID19 infected");
	
	free(listNumber);
	return 0;
}
