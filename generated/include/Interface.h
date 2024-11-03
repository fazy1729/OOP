#ifndef INTERFACE_H
#define INTERFACE_H

#include "EVERYTHING.h"

using namespace std;

class Interface {
private:
    string name;
    ifstream inputFile;

public:
    Interface() = default;
    Interface(const Interface& other);

    explicit Interface(const string& fileName);
    friend ostream& operator<<(ostream& os, const Interface& obj);
    Interface &operator=(const Interface &other);
    string getPlayerName() const;

    ~Interface() = default;
};

#endif