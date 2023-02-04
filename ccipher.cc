#include <string>
#include <iostream>
#include <algorithm>
#include "ccipher.h"

/* Cheshire smile implementation. */
struct CCipher::CipherCheshire
{
    int offset_int;
    string plain_alpha;
    string rot_alpha;
};

// -------------------------------------------------------
// Caesar Cipher implementation

// Defualt Constructor
CCipher::CCipher()
{
    // TODO: Implement this default constructor
    smile = new CipherCheshire();
    smile->offset_int = 0;
    smile->plain_alpha = smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
}

/* This constructor initiates the object with a
   input cipher key
 */
CCipher::CCipher(int offset_int)
{
    // TODO: Implement this constructor
    if (is_valid_offset(offset_int))
    {
        smile = new CipherCheshire();
        smile->offset_int = offset_int;
        smile->plain_alpha = smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
    }
    else
    {
        cout << "Error: Caeser cipher is less than 0" << endl;
        exit(EXIT_FAILURE);
    }
}

/* Destructor
 */
CCipher::~CCipher()
{
    delete (smile);
}

/* This member function encrypts the input text
   using the intialized offset integer
 */
string CCipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;

    // TODO: Finish this function

    // Rotating alphabet by offset_int amount will give us new cipher alphabet
    // The rest is the same as substitution cipher
    rotate_string(smile->rot_alpha, smile->offset_int);
    int inputLen = raw.length();
    char ch, temp;
    int pos;
    for (int i = 0; i < inputLen; i++)
    {
        temp = ' ';
        ch = raw.at(i);
        if (ch != ' ')
        {
            pos = find_pos(smile->plain_alpha, ch);
            if (ch >= 65 && ch <= 90)
            {
                temp = UPPER_CASE(smile->rot_alpha[pos]);
            }

            else
            {
                temp = LOWER_CASE(smile->rot_alpha[pos]);
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
string CCipher::decrypt(string enc)
{
    cout << "Decrypting...";
    string retStr;

    // TODO: Finish this function
    int inputLen = enc.length();
    char ch, temp;
    int pos;
    for (int i = 0; i < inputLen; i++)
    {
        temp = ' ';
        ch = enc.at(i);
        if (ch != ' ')
        {
            pos = find_pos(smile->rot_alpha, ch);
            if (ch >= 65 && ch <= 90)
            {
                // uppercase
                temp = UPPER_CASE(smile->plain_alpha[pos]);
            }
            else
            {
                // lowercase
                temp = LOWER_CASE(smile->plain_alpha[pos]);
            }
        }
        retStr += temp;
    }

    cout << "Done" << endl;
    return retStr;
}

// -------------------------------------------------------
// Rotates the input string in_str by rot positions
void rotate_string(string &in_str, int rot)
{
    // TODO: You will likely need this function. Implement it.
    rot = rot % in_str.length();
    rotate(in_str.begin(), in_str.begin() + rot, in_str.end());
}

// Validating shift number
bool is_valid_offset(int offset)
{
    return (offset >= 0) ? true : false;
}
