#ifndef VCIPHER_H_
#define VCIPHER_H_
//#include "cipher.h"
#include "kcipher.h"

using namespace std;

/* A class that implements a
   Vigenere cipher class. It
   inherts KCipher */
// TODO: Implement this class
class VCipher : public KCipher
{
protected:
   struct CipherCheshire;
   CipherCheshire *smile;

public:
   VCipher();
   VCipher(string page);
   ~VCipher();
   string encrypt(string raw);
   string decrypt(string enc);
};

bool is_valid_key(string key);
string repeat(string key, int char_num);
#endif
