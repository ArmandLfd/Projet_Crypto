/*
* Copyright (c) by CryptoLab inc.
* This program is licensed under a
* Creative Commons Attribution-NonCommercial 3.0 Unported License.
* You should have received a copy of the license along with this
* work.  If not, see <http://creativecommons.org/licenses/by-nc/3.0/>.
*/

#include "../src/HEAAN.h"
#include <string>
/**
  * This file is for test HEAAN library
  * You can find more in src/TestScheme.h
  * "./TestHEAAN Encrypt" will run Encrypt Test
  * There are Encrypt, EncryptSingle, Add, Mult, iMult, RotateFast, Conjugate Tests
  */
int main(int argc, char **argv) {

	//long logq = 55; ///< Ciphertext Modulus
	//long logp = 55; ///< Real message will be quantized by multiplying 2^40
	//long logn = 1; ///< log2(The number of slots)
	// !!! All others parameters are in param.h !!!
	// For L, the only thing that I found in the code is at lines 165-166 in scheme.cpp.
	// logl is given in parameters. And used in TestScheme.cpp and Ring.cpp as logSlots
	// logn =? logl ???
	// Moreover, in HEAAN page 13 at Table 1, they explain that encrypting a plaintext will output a <c,L,v,B_clean>
	// But we ask logn and not L ... => log2(5) = 2,32 log2(10)=3.32 log2(15) = 3.9
	if(argc != 4){
		cout << "Error : need logq,logp,logn" << endl;
		return -1;
	}
	long logq = stol(argv[1]);
	long logp = stol(argv[2]);
	long logn = stol(argv[3]);
	TestScheme::testBasic(logq, logp, logn);
	// Since we cannot have a portable version of param.h, do it one by one
	//TestScheme::testBasic(55, 55, 1);
	//TestScheme::testBasic(55, 55, 1);
	
	
//----------------------------------------------------------------------------------
//   STANDARD TESTS
//----------------------------------------------------------------------------------
/*
	if(string(argv[1]) == "Encrypt") TestScheme::testEncrypt(logq, logp, logn);
	if(string(argv[1]) == "EncryptBySk") TestScheme::testEncryptBySk(logq, logp, logn);
	if(string(argv[1]) == "DecryptForShare") TestScheme::testDecryptForShare(logq, logp, logn, stol(argv[2]));
	if(string(argv[1]) == "EncryptSingle") TestScheme::testEncryptSingle(logq, logp);
	if(string(argv[1]) == "Add") TestScheme::testAdd(logq, logp, logn);
	if(string(argv[1]) == "Mult") TestScheme::testMult(logq, logp, logn);
	if(string(argv[1]) == "iMult") TestScheme::testiMult(logq, logp, logn);

//----------------------------------------------------------------------------------
//   ROTATE & CONJUGATE
//----------------------------------------------------------------------------------

	long r = 1; ///< The amout of rotation
	if(string(argv[1]) == "RotateFast") TestScheme::testRotateFast(logq, logp, logn, r);
	if(string(argv[1]) == "Conjugate") TestScheme::testConjugate(logq, logp, logn);
    
//----------------------------------------------------------------------------------
//   BOOTSTRAPPING
//----------------------------------------------------------------------------------
    
    logq = logp + 10; //< suppose the input ciphertext of bootstrapping has logq = logp + 10
    logn = 3; //< larger logn will make bootstrapping tech much slower
    long logT = 4; //< this means that we use Taylor approximation in [-1/T,1/T] with double angle fomula
    if(string(argv[1]) == "Bootstrapping") TestScheme::testBootstrap(logq, logp, logn, logT);
*/
	return 0;
}
