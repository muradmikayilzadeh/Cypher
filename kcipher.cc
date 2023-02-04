#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "kcipher.h"

/* Helper function definitions
 */
bool is_valid_page(string alpha);
// -------------------------------------------------------
// Running Key Cipher implementation

// -------------------------------------------------------
/* Cheshire smile implementation. */
struct KCipher::CipherCheshire
{
    int page;
    vector<string> book;
    string plain_alpha;
    string rot_alpha;
};

KCipher::KCipher()
{
    // TODO: Implement this constructor
    smile = new CipherCheshire();
    smile->book.push_back("");
    smile->page = 0;
}

KCipher::KCipher(string page)
{
    // TODO: Implement this constructor

    if (is_valid_page(page))
    {
        smile = new CipherCheshire();
        smile->book.push_back(page);
        smile->plain_alpha = smile->rot_alpha = "abcdefghijklmnopqrstuvwxyz";
    }
    else
    {
        cout << "Invalid Running key: " + page << endl;
        exit(EXIT_FAILURE);
    }
}

/* Destructor
 */
KCipher::~KCipher()
{
    // TODO: Implement this constructor
    delete (smile);
}

/* This member function encrypts the input text
   using the intialized offset integer
 */
string KCipher::encrypt(string raw)
{
    cout << "Encrypting...";

    // TODO: Finish this function
    string retStr, key, plain_text;
    key = smile->book[smile->page];

    if (!key.empty())
    {
        plain_text = raw;
        key.erase(remove(key.begin(), key.end(), ' '), key.end());                             // remove spaces from the key text
        plain_text.erase(remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end()); // remove spaces from the plain text

        int inputLen = raw.length();
        char ch, temp;
        int pos, key_pos;

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
string KCipher::decrypt(string enc)
{
    cout << "Decrypting...";

    string retStr, key, plain_text;
    key = smile->book[smile->page];

    if (!key.empty())
    {
        plain_text = enc;
        key.erase(remove(key.begin(), key.end(), ' '), key.end());                             // remove spaces from the key text
        plain_text.erase(remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end()); // remove spaces from the plain text

        int inputLen = enc.length();
        char ch, temp;
        int rot_amount;

        int plain_iter = 0;
        int raw_iter = 0;
        while (raw_iter < inputLen)
        {
            ch = enc.at(raw_iter);
            temp = ' ';

            // Crypted letter is n steps away from the real letter.
            // n is the position of the key's corresponding letter in the normal alphabet.
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

void KCipher::add_key(string page)
{
    if (is_valid_page(page))
    {
        smile->book.push_back(page);
    }
    else
    {
        cout << "Invalid Running key: " + page << endl;
        exit(EXIT_FAILURE);
    }
}

void KCipher::set_id(int id)
{
    if (id >= 0 && id < (int)smile->book.size() - 1)
    {
        smile->page = id;
    }
    else
    {
        cout << "Warning: invalid id: " << id << endl;
        exit(EXIT_FAILURE);
    }
}

// Helper functions

// Function to check the validity of the page.
bool is_valid_page(string page)
{
    bool is_valid = true;

    if (!page.empty())
    {
        for (unsigned int i = 0; i < page.length(); i++)
        {
            if (ispunct(page[i]) || isupper(page[i]))
            {
                is_valid = false;
                break;
            }
        }
    }
    else
    {
        is_valid = false;
    }

    return is_valid;
}