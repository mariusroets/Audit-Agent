
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include "encryptor.h"
#include "general.h"

#define BITS 256

Encryptor::Encryptor(const string& key) : mKey(key)
{
    srand(time(NULL));
}
string Encryptor::decrypt(const string& encrypted)
{

    unsigned int offset = 0;
    string ascii_encrypted = makeAsciiString(offset, encrypted);

    string decrypted = "";

    for (int i = 0; i < (int)ascii_encrypted.length(); ++i) {
        int key_index = i - ((i/mKey.length()) * mKey.length());
        unsigned int tmpCharValue = ascii_encrypted[i] ^ mKey[key_index];
        if (tmpCharValue <= offset) {
            tmpCharValue += (BITS - offset);
        } else {
            tmpCharValue -= offset;
        }
        offset = ascii_encrypted[i];
        offset &= BITS-1; // Filter out MSB
        decrypted += tmpCharValue;

    }

    return decrypted;

}
string Encryptor::encrypt(const string& plain_text)
{
    string encrypted = "";
    // Random number between 0 and BITS
    int base_offset, offset;
    base_offset = offset = rand()%BITS;
    for (int i = 0; i < (int)plain_text.size(); ++i) {
        int key_index = i - ((i/mKey.size()) * mKey.size());

        unsigned int asciiEncryptedValue = (plain_text[i] + offset) % BITS;
        asciiEncryptedValue ^= mKey[key_index];
        encrypted += asciiEncryptedValue;
        offset = asciiEncryptedValue;
    }

    return makeHexString(base_offset, encrypted);
}

string Encryptor::makeHexString(unsigned int offset, const string& str)
{
    stringstream strm;

    strm << hex << setw(2) << setfill('0') << offset;
    for (int i = 0; i < (int)str.size(); ++i) {
        int num = (unsigned)(str[i]);
        num &= BITS-1; // Filter out MSB
        strm << hex << setw(2) << setfill('0') << num;
    }
    // Transform to uppercase
    string s = strm.str();
    std::transform(s.begin(), s.end(),s.begin(), ::toupper);
    return s;
}

string Encryptor::makeAsciiString(unsigned int &offset, const string& str)
{
    offset = getOffset(str);

    string ascii_string = "";
    for (int i = 2; i < (int)str.length(); i+=2) {
        string s = str.substr(i,2);
        ascii_string += (char)General::from_string<int>(s, std::hex);
    }
    return ascii_string;
}
int Encryptor::getOffset(const string& str)
{
    return General::from_string<int>(str.substr(0,2), std::hex);
}
