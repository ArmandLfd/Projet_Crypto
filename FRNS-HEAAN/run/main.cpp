/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/

#include "../src/TestScheme.h"

int main() {

//	TestScheme::testEncodeSingle(14, 1, 55);

//	TestScheme::testEncodeBatch(15, 6, 55, 3);

	
	
	//void TestScheme::testBasic(long logN, long L, long logp, long logSlots) 
	// logp seems to be = to logq -> see Context.cpp line 44-66.
	//In Context.h we can see Q0_BIT_SIZE defined as 61, in the paper logq0 = 61. Line 55 and 60 we can see that we replace that macro by loqp.
	//Print logq at Context.cpp -> print 55
	//
	// Choose a power-of-two interger N/QL -> nToChoose=x^2N or nToChoose=x^2QL
	// logQL = log(2^(logQL))
	// logQL -> bit size of QL
	// logslots != logQL -> slots must be same on HEAAN and FRNS-HEAAN -> Must be zero ???
	TestScheme::testBasic(15, 5, 55, 336);
	
	TestScheme::testBasic(15, 10, 55, 611);
	
	TestScheme::testBasic(16, 15, 55, 886);

//	TestScheme::testConjugateBatch(15, 6, 55, 1);

//	TestScheme::testRotateByPo2Batch(16, 26, 40, 1, 4, false);

//	TestScheme::testRotateBatch(15, 6, 55, 3, 4, true);

//	TestScheme::testimultBatch(16, 16, 55, 2);

//	TestScheme::testPowerOf2Batch(16, 15, 50, 2, 3);

//	TestScheme::testInverseBatch(14, 5, 55, 4, 3);

//	TestScheme::testExponentBatch(14, 5, 55, 7, 3);

//	TestScheme::testSigmoidBatch(16, 15, 55, 3, 3);

//	TestScheme::testSlotsSum(16, 15, 40, 3);

//	TestScheme::testMeanVariance(14, 3, 55, 13);

//	TestScheme::testHEML("data/uis.txt", 0, 5);

	return 0;
}
