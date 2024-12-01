#ifndef CRYPTOHACKER_H
#define CRYPTOHACKER_H
#include "EVERYTHING.h"
#include <Hacker.h>

// CryptoHacker class definition
// This class represents a hacker specializing in cryptography and provides methods for cryptographic tasks.

class CryptoHacker : public Hacker {
public:
    // Constructor that initializes CryptoHacker with specific cryptographic skills.
    // @param skills A string representing the skills of the CryptoHacker.
    CryptoHacker(const std::string &skills) : Hacker("Cryptographer", skills) {}

    // Default constructor for CryptoHacker
    CryptoHacker() = default;

    // Overrides the hack method to perform cryptographic analysis (e.g., cracking a Caesar cipher).
    // This is a demonstration of cryptographic hacking tasks.
    void hack() override {
        std::cout << "Performing cryptographic analysis..." << std::endl;
        std::cout << "Cracking Caesar cipher with a shift of 3..." << std::endl;
        std::cout << "Cipher cracked! Message decrypted." << std::endl;
    }

    // Clones the CryptoHacker object by creating a new instance.
    // @return A pointer to a new instance of CryptoHacker.
    Hacker* clone() const override {
        return new CryptoHacker(*this);  // Return a clone of the CryptoHacker object
    }

    // Displays the specialization of the CryptoHacker.
    void display() const override {
        std::cout << "CryptoHacker specializing in cryptography!" << std::endl;
    }

    // Static method that performs Caesar cipher decryption on the given text.
    // @param text The text to be decrypted.
    static void CaesarDecypher(std::string &text);

    // Static method that performs SHA256 hashing on a file's content.
    // @param fileName The name of the file to be hashed.
    // @param catFiles A map containing files and their associated content.
    // @return A string containing the SHA256 hash of the file's content.
    static std::string SHA256(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles);

    // Copy constructor for CryptoHacker
    CryptoHacker(const CryptoHacker &other) = default;

    // Assignment operator for CryptoHacker
    CryptoHacker& operator=(const CryptoHacker &other) = default;

    // Destructor for CryptoHacker
    ~CryptoHacker() = default;
};

#endif
