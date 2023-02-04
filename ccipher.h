#ifndef CCIPHER_H_
#define CCIPHER_H_
#include "cipher.h"

using namespace std;

/* A class that implements a
   Caesar cipher class. It
   inherits the Cipher class */
// TODO: Implement this class
class CCipher : public Cipher
{
protected:
   struct CipherCheshire;
   CipherCheshire *smile;

public:
   CCipher();
   CCipher(int offset_int);
   ~CCipher();
   virtual string encrypt(string raw);
   virtual string decrypt(string enc);
};
/* Helper function headers
 */
void rotate_string(string &in_str, int rot);
bool is_valid_offset(int offset);
#endif
