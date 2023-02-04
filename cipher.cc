#include "cipher.h"

/* Cheshire smile implementation.
   It only contains the cipher alphabet
 */
struct Cipher::CipherCheshire
{
    string cipher_alpha;
    string plain_alpha;
};

/* This function checks the cipher alphabet
   to make sure it's valid
 */
bool is_valid_alpha(string alpha);

// -------------------------------------------------------
// Cipher implementation
/* Default constructor
   This will actually not encrypt the input text
   because it's using the unscrambled alphabet
 */
Cipher::Cipher()
{
    // TODO: Implement this default constructor
    smile = new CipherCheshire();
    smile->cipher_alpha = "abcdefghijklmnopqrstuvwxyz";
    smile->plain_alpha = "abcdefghijklmnopqrstuvwxyz";
}

/* This constructor initiates the object with a
   input cipher key
 */
Cipher::Cipher(string cipher_alpha)
{
    // TODO: Implement this constructor

    if (is_valid_alpha(cipher_alpha))
    {
        smile = new CipherCheshire();
        smile->cipher_alpha = cipher_alpha;
        smile->plain_alpha = "abcdefghijklmnopqrstuvwxyz";
    }
    else
    {
        cout << "Invalid cipher alphabet/key: " << cipher_alpha << endl;
        exit(EXIT_FAILURE);
    }
}

/* Destructor
 */
Cipher::~Cipher()
{
    // TODO: Implement this constructor
    delete (smile);
}

/* This member function encrypts the input text
   using the intialized cipher key
 */
string Cipher::encrypt(string raw)
{
    cout << "Encrypting...";
    string retStr;

    // TODO: Finish this function
    int inputLen = raw.length();
    char ch, temp;
    int pos;
    for (int i = 0; i < inputLen; ++i)
    {
        temp = ' ';
        ch = raw.at(i);
        if (ch != ' ')
        {
            pos = find_pos(smile->plain_alpha, ch);
            if (ch >= 65 && ch <= 90)
            {
                // If the letter is uppercase, then print its uppercase counterpart. Numbers are from ASCII table.
                temp = UPPER_CASE(smile->cipher_alpha[pos]);
            }
            else
            {
                // If the letter is lowercase, then print its uppercase counterpart.
                temp = LOWER_CASE(smile->cipher_alpha[pos]);
            }
        }
        retStr += temp;
    }

    cout << "Done" << endl;

    return retStr;
}

/* This member function decrypts the input text
   using the intialized cipher key
 */
string Cipher::decrypt(string enc)
{
    string retStr;
    cout << "Decrypting...";
    // TODO: Finish this function
    int inputLen = enc.length();
    char ch, temp;
    int pos;
    for (int i = 0; i < inputLen; ++i)
    {
        temp = ' ';
        ch = enc.at(i);
        if (ch != ' ')
        {
            pos = find_pos(smile->cipher_alpha, ch);
            if (ch >= 65 && ch <= 90)
            {
                // If the letter is uppercase, then print its uppercase counterpart. Numbers are from ASCII table.
                temp = UPPER_CASE(smile->plain_alpha[pos]);
            }
            else
            {
                // If the letter is lowercase, then print its uppercase counterpart.
                temp = LOWER_CASE(smile->plain_alpha[pos]);
            }
        }
        retStr += temp;
    }

    cout << "Done" << endl;

    return retStr;
}
// -------------------------------------------------------

//  Helper functions
/* Find the character c's position in the cipher alphabet/key
 */
unsigned int find_pos(string alpha, char c)
{
    unsigned int pos = 0;

    // TODO: You will likely need this function. Finish it.
    char ch = LOWER_CASE(c);

    for (unsigned int i = 0; i < alpha.length(); i++)
    {
        if (ch == alpha.at(i))
        {
            pos = i;
            break;
        }
    }

    return pos;
}

/* Make sure the cipher alphabet is valid -
   a) it must contain every letter in the alphabet
   b) it must contain only one of each letter
   c) it must be all lower case letters
   ALL of the above conditions must be met for the text to be a valid
   cipher alphabet.
 */
bool is_valid_alpha(string alpha)
{
    bool is_valid = true;
    if (alpha.size() != ALPHABET_SIZE)
    {
        is_valid = false;
    }
    else
    {
        unsigned int letter_exists[ALPHABET_SIZE];
        for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
        {
            letter_exists[i] = 0;
        }
        for (unsigned int i = 0; i < alpha.size(); i++)
        {
            char c = alpha[i];
            if (!((c >= 'a') && (c <= 'z')))
            {
                is_valid = false;
            }
            else
            {
                letter_exists[(c - 'a')]++;
            }
        }
        for (unsigned int i = 0; i < ALPHABET_SIZE; i++)
        {
            if (letter_exists[i] != 1)
            {
                is_valid = false;
            }
        }
    }

    return is_valid;
}
