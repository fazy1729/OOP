#include "Interface.h"

Interface::Interface(const string& fileName) {
    cout << "WELCOME TO INTRUSION\n";
    cout << "AT ANY TIME YOU CAN USE THE COMMAND --help TO LIST ANYTHING THAT YOU MIGHT NEED OR --exit TO LEAVE\n";
    cout << "Your objective will be to access the SECRET directory which will provide you with further information. To access this directory, you have to solve the puzzles and then use the PASSWORD to access the folder."
         << " You can always use the command OBJECTIVE to see what you have to do: usage example --objective\n\n\n";
    cout << "Please enter your name: \n\n\n";

    inputFile.open(fileName);
    getline(inputFile, name);
}

Interface::Interface(const Interface& other) : name(other.name) {}

ostream& operator<<(ostream& os, const Interface& obj) {
    os << "Your name is: " << obj.name;
    return os;
}

string Interface::getPlayerName() const {
    return name;
}
Interface& Interface::operator=(const Interface& other) {
    if(this != &other) {
        name = other.name;
        if (inputFile.is_open()) {
            inputFile.close();
        }

    }
    return *this;

}