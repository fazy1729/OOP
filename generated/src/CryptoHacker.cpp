#include "CryptoHacker.h"
using namespace std;


void CryptoHacker::CaesarDecypher(string &text) {
    cout<<"Your message is: ";
    for(auto &s : text) {
        if(s >= 'a' && s <= 'z') {
            s = (s - 'a' - 3 + 26 ) % 26 + 'a';
        }
        else if (s >= 'A' && s <= 'Z') {
            s = (s - 'A' - 3 + 26 ) % 26 + 'A';
        }
        cout<<s;
    }
    cout<<"\n";
}

string CryptoHacker:: SHA256(const string &fileName, const map<string, vector<string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        cout << "File not found" << endl;
        return "";
    }

    string message;
    for (const auto &line : it->second) {
        message += line;
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength;

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) {
        cerr << "Error creating hash context" << endl;
        return "";
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1 ||
        EVP_DigestUpdate(context, message.c_str(), message.size()) != 1 ||
        EVP_DigestFinal_ex(context, hash, &hashLength) != 1) {

        cerr << "Error during hashing" << endl;
        EVP_MD_CTX_free(context);
     return "";
        }

    EVP_MD_CTX_free(context);

    stringstream hexa;
    for (unsigned int i = 0; i < hashLength; i++) {
        hexa << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
    }
    return hexa.str();
}





