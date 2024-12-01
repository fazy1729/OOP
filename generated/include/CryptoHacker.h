#ifndef CRYPTOHACKER_H
#define CRYPTOHACKER_H

#include "EVERYTHING.h"
#include <Hacker.h>
using namespace std;

class CryptoHacker : public Hacker {
public:
    CryptoHacker(const string &skills) : Hacker("Cryptographer", skills) {}
    CryptoHacker() = default;

    void hack() override {
        cout << "Performing cryptographic analysis..." << endl;
        // Simulate some cryptographic hacking task (e.g., cracking a Caesar cipher)
        cout << "Cracking Caesar cipher with a shift of 3..." << endl;
        // (For simplicity, just print a message; you can replace it with actual code)
        cout << "Cipher cracked! Message decrypted." << endl;
    }

    Hacker* clone() const override {
        return new CryptoHacker(*this);  // Returnează o clonă a obiectului CryptoHacker
    }


    void display() const override {
        cout << "CryptoHacker specializing in cryptography!" << endl;
    }



    static void CaesarDecypher(string &text);
    static string SHA256(const string &fileName, const map<string, vector<string>> &catFiles);
    CryptoHacker(const CryptoHacker &other) = default;
    CryptoHacker& operator=(const CryptoHacker &other) = default;
    ~CryptoHacker() = default;

};

#endif