#include <string>
#include <iostream>
#include <vector>
#include "kcipher.h"
#include "vcipher.h"
#include <algorithm>

// -------------------------------------------------------
// Running Key Cipher implementation
// -------------------------------------------------------
// -------------------------------------------------------
/* Cheshire smile implementation. */
struct VCipher::CipherCheshire
{
    string key;
    string plain_alpha;
    string rot_alpha;
};

VCipher::VCipher()
{
    // TODO: Implement this constructor
    smile = new CipherCheshire();
    smile->key = "";
}

VCipher::VCipher(string key)
{
    // TODO: Implement this constructor

    if (is_valid_key(key))
    {
        smile = new CipherCheshire();
        smile->key = key;
        smile->plain_alpha = smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
    }
    else
    {
        cout << "Error: not a valid Vigenere key word" << endl;
        exit(EXIT_FAILURE);
    }
}

/* Destructor
 */
VCipher::~VCipher()
{
    // TODO: Implement this constructor
    delete (smile);
}

/* This member function encrypts the input text
   using the intialized offset integer
 */
string VCipher::encrypt(string raw)
{
    cout << "Encrypting...";

    // TODO: Finish this function
    string retStr, key, plain_text;
    key = smile->key;

    // Same idea as the running key cipher, except the key which is one word, will be repeated untill the end of plain text
    // via repeat() helper function

    if (!key.empty())
    {
        plain_text = raw;
        plain_text.erase(remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end());

        int inputLen = raw.length();
        char ch, temp;
        int pos, key_pos;
        key = repeat(key, inputLen);

        int plain_iter = 0;
        int raw_iter = 0;
        while (raw_iter < inputLen)
        {
            ch = raw.at(raw_iter);
            temp = ' ';

            if (ch != ' ')
            {
                ch = plain_text.at(plain_iter);

                pos = find_pos(smile->plain_alpha, ch);
                key_pos = find_pos(smile->plain_alpha, key[plain_iter]);
                if (ch >= 65 && ch <= 90)
                {
                    // uppercase
                    rotate_string(smile->rot_alpha, pos);
                    temp = UPPER_CASE(smile->rot_alpha[key_pos]);
                    smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
                }
                else
                {
                    // lowercase
                    rotate_string(smile->rot_alpha, pos);
                    temp = LOWER_CASE(smile->rot_alpha[key_pos]);
                    smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
                }
                plain_iter++;
            }

            raw_iter++;
            retStr += temp;
        }
    }
    else
    {
        retStr = raw;
    }

    cout << "Done" << endl;
    return retStr;
}

/* This member function decrypts the input text
   using the intialized offset integer
 */
string VCipher::decrypt(string enc)
{
    cout << "Decrypting...";

    string retStr, key, plain_text;
    key = smile->key;

    // Same idea as the running key cipher, except the key which is one word, will be repeated untill the end of plain text
    // via repeat() helper function
    if (!key.empty())
    {
        plain_text = enc;
        key.erase(remove(key.begin(), key.end(), ' '), key.end()); // remove spaces from the key text
        plain_text.erase(remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end());

        int inputLen = enc.length();
        char ch, temp;
        int rot_amount;
        key = repeat(key, inputLen);

        int plain_iter = 0;
        int raw_iter = 0;
        while (raw_iter < inputLen)
        {
            ch = enc.at(raw_iter);
            temp = ' ';

            if (ch != ' ')
            {
                ch = plain_text.at(plain_iter);
                rot_amount = find_pos(smile->plain_alpha, plain_text[plain_iter]) - find_pos(smile->plain_alpha, key[plain_iter]) + 26;
                rotate_string(smile->rot_alpha, rot_amount);

                if (ch >= 65 && ch <= 90)
                {
                    // uppercase
                    temp = UPPER_CASE(smile->rot_alpha[0]);
                    smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
                }
                else
                {
                    // lowercase
                    temp = LOWER_CASE(smile->rot_alpha[0]);
                    smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
                }
                plain_iter++;
            }

            raw_iter++;
            retStr += temp;
        }
    }
    else
    {
        retStr = enc;
    }

    cout << "Done" << endl;
    return retStr;
}

// Helper functions

// Helper function that checks validity of the key
bool is_valid_key(string key)
{
    bool is_valid = true;

    for (unsigned int i = 0; i < key.length(); i++)
    {
        if (ispunct(key[i]) || isupper(key[i]) || isspace(key[i]))
        {
            is_valid = false;
            break;
        }
    }

    return is_valid;
}

// Helper function that repeats key for char_num characters
string repeat(string key, int char_num)
{
    string result;
    int key_len = key.length();
    int j = 0;
    for (int i = 0; i < char_num; i++)
    {
        result += key[j];
        if (j != key_len - 1)
        {
            j++;
        }
        else
        {
            j = 0;
        }
    }

    return result;
}
