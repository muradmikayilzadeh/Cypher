#include <string>
#include <iostream>
#include "rcipher.h"

// -------------------------------------------------------
// ROT13 Cipher implementation
// -------------------------------------------------------

/* Cheshire smile implementation.
   It only contains the offset integer
 */
struct RCipher::CipherCheshire
{
    int offset_int;
};

// Defualt Constructor
RCipher::RCipher()
{
    // TODO: Implement this default constructor
    smile = new CipherCheshire();
    smile->offset_int = 13;
}

/* Destructor
 */
RCipher::~RCipher()
{
    delete (smile);
}

/* This member function encrypts the input text
   using the intialized offset integer
 */
string RCipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;
    // TODO: Finish this function
    int inputLen = raw.length();
    char ch, temp;

    for (int i = 0; i < inputLen; i++)
    {
        temp = ' ';
        ch = raw.at(i);
        if (ch != ' ')
        {
            if (ch >= 65 && ch <= 90)
            { // uppercase

                // ROT13 is the special case of Caeser with the shift amount of 13, which is exact half of the
                // number of letters in the english alphabet. By checking the ASCII table value of each letter,
                // we can determine in which half the letter is located.
                if (ch < 78)
                    temp = ch + 13;
                else
                    temp = ch - 13;
            }
            else
            { // lowercase
                if (ch < 110)
                    temp = ch + 13;
                else
                    temp = ch - 13;
            }
        }
        retStr += temp;
    }
    cout << "Done" << endl;
    return retStr;
}

/* This member function decrypts the input text
   using the intialized offset integer
 */
string RCipher::decrypt(string enc)
{
    cout << "Decrypting...";
    string retStr;

    // // TODO: Finish this function
    int inputLen = enc.length();
    char ch, temp;

    for (int i = 0; i < inputLen; i++)
    {
        temp = ' ';
        ch = enc.at(i);
        if (ch != ' ')
        {
            if (ch >= 65 && ch <= 90)
            { // uppercase
                if (ch < 78)
                    temp = ch + 13;
                else
                    temp = ch - 13;
            }
            else
            { // lowercase
                if (ch < 110)
                    temp = ch + 13;
                else
                    temp = ch - 13;
            }
        }
        retStr += temp;
    }

    cout << "Done" << endl;
    return retStr;
}