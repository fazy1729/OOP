#ifndef CRYPTOHACKER_H
#define CRYPTOHACKER_H

#include "EVERYTHING.h"
#include <Hacker.h>
using namespace std;

class CryptoHacker : public Hacker {
public:
    CryptoHacker(const string &skills) : Hacker("Cryptographer", skills) {}

    static void CaesarDecypher(string &text);
    static string SHA256(const string &fileName, const map<string, vector<string>> &catFiles);

    CryptoHacker(const CryptoHacker &other) = default;
    CryptoHacker& operator=(const CryptoHacker &other) = default;

};

#endif