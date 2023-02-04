#ifndef KCIPHER_H_
#define KCIPHER_H_
#include "cipher.h"
#include "ccipher.h"

using namespace std;

const unsigned int MAX_LENGTH = 100;

/* A class that implements a
   Running key cipher class. It
   inherts class Cipher */
// TODO: Implement this function
class KCipher : public Cipher
{
protected:
   struct CipherCheshire;
   CipherCheshire *smile;

public:
   KCipher();
   KCipher(string page);
   ~KCipher();
   virtual string encrypt(string raw);
   virtual string decrypt(string enc);
   virtual void add_key(string page);
   virtual void set_id(int id);
};
bool is_valid_page(string page);

#endif
