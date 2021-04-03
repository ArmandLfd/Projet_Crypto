/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/

#include "../src/TestScheme.h"

int main() {	
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
	TestScheme::testBasic(15, 5, 55, 1);
	
	TestScheme::testBasic(15, 10, 55, 1);
	
	TestScheme::testBasic(16, 15, 55, 1);

	return 0;
}
