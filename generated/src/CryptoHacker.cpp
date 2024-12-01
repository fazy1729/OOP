#include "CryptoHacker.h"

/**
 * @brief Decrypts the given text using the Caesar cipher (classic).
 *
 * The method shifts each letter 3 positions backward in the alphabet.
 * If a letter is less than 'C', it wraps around to the end of the alphabet.
 *
 * @param text The text to be decrypted.
 */
void CryptoHacker::CaesarDecypher(std::string &text) {
    std::cout << "Your message is: ";
    for (auto &s : text) {
        if (s >= 'a' && s <= 'z') {
            s = (s - 'a' - 3 + 26) % 26 + 'a';
        }
        else if (s >= 'A' && s <= 'Z') {
            s = (s - 'A' - 3 + 26) % 26 + 'A';
        }
        std::cout << s;
    }
    std::cout << "\n";
}

/**
 * @brief Computes the SHA-256 hash of a file's contents.
 *
 * This function uses OpenSSL's EVP API to compute the SHA-256 hash of a file's contents.
 * It finds the file's content in the `catFiles` map, concatenates the lines,
 * and computes the hash.
 *
 * @param fileName The name of the file to be hashed.
 * @param catFiles The map of files and their contents.
 * @return A string representing the SHA-256 hash of the file.
 */
std::string CryptoHacker::SHA256(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        std::cout << "File not found" << std::endl;
        return "";
    }

    std::string message;
    for (const auto &line : it->second) {
        message += line;
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        std::cerr << "Error creating hash context" << std::endl;
        return "";
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(context, message.c_str(), message.size()) != 1 ||
        EVP_DigestFinal_ex(context, hash, &hashLength) != 1) {

        std::cerr << "Error during hashing" << std::endl;
        EVP_MD_CTX_free(context);
        return "";
    }

    EVP_MD_CTX_free(context);

    std::stringstream hexa;
    for (unsigned int i = 0; i < hashLength; i++) {
        hexa << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return hexa.str();
}
