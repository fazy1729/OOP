#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <openssl/evp.h>
#include <sstream>
#include <string.h>
using namespace std;

class Interface {
private:
    string name;
    ifstream inputFile;

public:
    Interface() = default;
    explicit Interface(const string& fileName) {
        cout << "WELCOME TO INTRUSION\n";
        cout << "AT ANY TIME YOU CAN USE THE COMMAND --help TO LIST ANYTHING THAT YOU MIGHT NEED OR --exit TO LEAVE\n";
        cout<<"Your objective will be to access the SECRET directory which it will provide you with further information. To access this directory you have to solve the puzzles  and then use the PASSWORD to access the folder."
              "You can always use the command OBJECTIVE to see what you have to do:usage example --objective\n\n\n";
        cout << "Please enter your name: \n\n\n";

        inputFile = ifstream(fileName);
        getline(inputFile, name);
    }
    Interface(const Interface &other) {
        name = other.name;
    }
    friend ostream& operator<<(ostream &os, const Interface& obj) {
        os<<"Your name is:" << obj.name;
        return os;
    }

    string getPlayerName() const {return name;}
    ~Interface() = default;

};

class Terminal {
private:
    map<string, vector<string>> fileSystem;
    string currentDirectory;
public:
    Terminal() {
        fileSystem["/"] = {"home", "etc", "SECRET"};
        fileSystem["/home"] = {"user1", "user2"};
        fileSystem["/home/user1"] = {"caesar.txt", "file2.txt", "projects"};
        fileSystem["/etc"] = {"passwd", "hosts"};
        fileSystem["/SECRET"] =  {"CIA"};

        currentDirectory = "/";
    }

    string getCurrentDirectory() {return currentDirectory;}
    void displayPlayerName(const string& playerName) {cout<<playerName<<"@"<<getCurrentDirectory() <<":$";}
    static void list_commands_help() {
        cout<<"1. Linux commands - Commands to use in the terminal\n";
        cout<<"2. Hacker commands - Commands that can help you pass a level\n";
        cout<<"Enter a number: ";
        int number;cin>>number;
        if(number == 1) {
            cout<<"ls - Prints the contents in a directory: usage example: ls <directory>\n";
            cout<<"cd - Navigate to another directory: usage example: cd <directory>\n";
            cout<<"pwd - Prints the working directory: usage example: pwd\n";
        }
        else if(number == 2) {
            cout<<"--sha256 - You can hash a message using the SHA256 alghoritm : usage example : --sha256 <file.txt>\n";
            cout<<"--caesar - You can decrypt an encrypted message that if shifted with 3 positions: usage example: --caesar <file.txt>\n";
        }
    }

    void ls() const {
        cout<<"Listing files in: "<<currentDirectory<<endl;
        auto it = fileSystem.find(currentDirectory);
        if (it != fileSystem.end()) {
            for(const string& fileName : it->second)
                cout<<fileName<<endl;
        } else {
            cout<<"Files not found";
        }
    }


    void cd(const string &directory) {
            if(directory == "..") {
                if(currentDirectory != "/") {
                    size_t pos = currentDirectory.find_last_of('/');
                    currentDirectory = currentDirectory.substr(0, pos);
                    if(currentDirectory.empty() == true) currentDirectory = "/";
                }
            }
            else {
                string newPath;
                if(currentDirectory == "/")
                    newPath = "/" + directory;
                else
                    newPath = currentDirectory + "/" + directory;

                if(fileSystem.contains(newPath)) {
                    currentDirectory = newPath;
                    cout<<"Changed directory to: "<<currentDirectory<<"\n";
                }
                else
                    cout<<"Directory not found\n";
            }

    }
    void pwd() const {
        cout<<"Current directory: " << currentDirectory << "\n";
    }
    static void cat(const string &key, const map<string, vector<string>> &catFile) {
        size_t pos = key.find(' ');
        if(pos != string::npos) {
            if(key.size() >= 4 && key.substr(key.size() - 4) == ".txt") {
                auto ex = catFile.find(key);
                if(ex != catFile.end()) {
                    cout<<"Contents of the folder: ";
                    for(auto &text : ex->second)
                        cout<<text<<endl;
                }
            }
            else
                cout<<"The file maybe does not exist or is not a .txt file...\n";
        }
        else
            cout<<"The correct format is: cat <file.txt>\n";
    }

    ~Terminal() = default;
};


class Hacker {
private:
    string specialization;
    string skills;
    string commands_list[3][3];
    string hacker_personality[3];

public:
    Hacker() = default;
    Hacker(const string &specialization,
        const string &skills)
    {
        this->specialization = specialization;
        this->skills = skills;


        commands_list[0][0] = "Decryption Alghoritms";
        commands_list[0][1] = "Hash Functions";
        commands_list[0][2] = "Key Exchange Protocols";

        commands_list[1][0] = "Digital Evidence Recovery";
        commands_list[1][1] = "Malware Analysis";
        commands_list[1][2] = "Incident Response";

        commands_list[2][0] = "Network Penetration Testing";
        commands_list[2][1] = "Packet Analysis";
        commands_list[2][2] = "Firewall and Intrusion Detection Bypassing";

        hacker_personality[0] = "CryptoHacker";
        hacker_personality[1] = "ForensicsHacker";
        hacker_personality[2] = "NetworkingHacker";

    }
    Hacker(const Hacker &other) {
        specialization = other.specialization;
        skills = other.skills;

        for(int i = 0; i < 3; i++)
            for(int j=0; j < 3; j++)
                commands_list[i][j] = other.commands_list[i][j];
        for(int i = 0; i < 3; i++)
            hacker_personality[i] = other.hacker_personality[i];
    }
    Hacker& operator=(const Hacker &other) {
        if(this !=  &other) {
            specialization = other.specialization;
            skills = other.skills;

            for(int i = 0; i < 3; i++)
                for(int j=0; j < 3; j++)
                    commands_list[i][j] = other.commands_list[i][j];
            for(int i = 0; i < 3; i++)
                hacker_personality[i] = other.hacker_personality[i];
        }
        return *this;
    }
    void printHackerPersonality() const {
        for(int i = 0; i < 3; i++) {
            cout<<i+1<<". "<<hacker_personality[i]<<endl;
        }
    }
    bool checkPersonality(const string &personality) {
        for(const auto & i : hacker_personality)
            if(personality == i)
                return true;
        return false;
    }

    string getCommands(const int i, const int j) const {return commands_list[i][j];}

    bool checkCommandExist(const string &command) {
        for(auto & i : commands_list)
            for(const auto & j : i)
                if(command == j)
                    return true;
        return false;
    }
    void help_commands(const int number) const {
        if(number == 1)
            for(int i=0; i<3; i++)
                cout<<getCommands(0,i)<<endl;
        else if(number == 2)
            for(int i=0; i<3; i++)
                cout<<getCommands(1,i)<<endl;
        else
            for(int i=0; i<3; i++)
                cout<<getCommands(2,i)<<endl;
    }
    virtual ~Hacker() = default;
};

class CryptoHacker : public Hacker {
public:
    CryptoHacker(const string &skills,
                    int experience, int age) : Hacker("Cryptographer", skills) {}

    static void CaesarDecypher(string &text) {
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

    static string SHA256(const string &fileName, const map<string, vector<string>> &catFiles) {
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

};

class Level : public Terminal {
private:
    int currentlevel;

    string objective;
    string target;

    map<string, vector<string>> catFiles;

public:
    explicit Level(int currentLevel) {
        this->currentlevel = currentLevel;
        cout << "LEVEL " << currentLevel;

        if (currentLevel == 1) {
            objective = "Decrypt the MESSAGE, find the PASSWORD, to gain important knowledge about the MOSSAD agent\n";
            catFiles["caesar.txt"] = {"Kdvk wklv phvvdjh zlwk wkh WDUJHW dqg WLPH Dojkrulwp"};
            this->target = "SHAd aku";
            cout << ": TEL AVIV  32.0929 N 34.8072 E..." << "TARGET: " << target << "...TIME 14:56...\n";
        }
    }

    string getObjective() const {return objective;}
    map<string, vector<string>> getCatFiles() {return catFiles;}
    int getCurrentLevel() {return this->currentlevel;}

    void getPassword(int currLevel)  {
        if (currLevel == 1) {
            const string verif = "0ea1c6dd1697dc4e8035da6149a2d680e847a57ff69ee7e73662b507c1a58698";
            cout<<"Please enter the password: ";
            string pass;cin>>pass;
            if(pass == verif) {
                cout<<"You got it\n";
                currLevel+=1;
            }
            else
                cout<<"ACCESS DENIED\n";
        }
    }

    ~Level() = default;

};


class GameEngine {
private:
    Hacker root;
    CryptoHacker cryptohacker;
    Interface interface;
    Level level;
    Terminal terminal;

    ifstream inputFile;
    bool readingFromFile;
    bool run;
public:
    explicit GameEngine(const string& fileName) :
          root("CryptoHacker", "ROOT"),
          cryptohacker("HELP", 10, 20),
          interface(fileName),
          level(1),
          readingFromFile(true),
          run(true)
    {
        inputFile.open(fileName);
        if (!inputFile) {
            cerr << "Unable to open file " << fileName << endl;
            readingFromFile = false;
        }
    }
    void executeCdCommand() {
        string dir;
        getline(cin, dir);
        size_t poz = dir.find(' ');
        if(poz != string::npos) {
            dir = dir.substr(poz+1);
            if(dir != "SECRET")
                terminal.cd(dir);
            else
                level.getPassword(level.getCurrentLevel());
        }
        else
            cout<<"The correct format is: cd <directory>\n";

    }
    void executeCaesarCommand(ifstream &inputFile, bool readingFromFile) {
        string file;
        if (readingFromFile == false)
            getline(cin,file);
        else {
            cout<<"You entered: "<< file <<"\n";
            getline(inputFile,file);
        }
        size_t pos = file.find(' ');
        if(pos != string::npos) {
            file = file.substr(pos+1);
            map<string, vector<string> > catFiles = level.getCatFiles();
            auto it = catFiles.find(file);
            if(it != catFiles.end())
                for(auto &text : it->second)
                    cryptohacker.CaesarDecypher(text);
            else
                cout<<"File not found"<<endl;
        }
        else
            cout<<"The correct format is: --caesar <file.txt>\n";
    }
    void executeSHA256Command(ifstream &file, bool readingFromFile) {
        string fileName;
        if(readingFromFile == false)
            getline(cin, fileName);
        else
            getline(file,fileName);

        size_t pos = fileName.find(' ');
        if(pos != string::npos) {
            fileName = fileName.substr(pos+1);
            string hash = cryptohacker.SHA256(fileName, level.getCatFiles());
            cout << "SHA256 hash: " << hash << endl;
        }
        else
            cout<<"The correct format is: --sha256 <file.txt>\n";
    }
    void executeCATCommand() {
        string file;
        getline(cin,file);
        terminal.cat(file,level.getCatFiles());
    }
    void displayHelp(ifstream &fileName, const bool &fileRead) {
        cout<<"HOW MIGHT I HELP YOU TODAY?"<<endl;
        cout<<"1. List of personalities: "<<endl;
        cout<<"2. List of commands: "<<endl;
        cout<<"Enter a number:";

        int number;
        if(fileRead == false)
            cin>>number;
        else {
            fileName >> number;
            cout<<"You've entered number "<<number<<"\n";
        }
        if(number == 1) {
            cout<<"Enter your personality from the list: "<<endl;

            root.printHackerPersonality();
            int hackerPersonality;

            cout << "Enter a number from the list: ";
            if(fileRead == false)
                cin>>hackerPersonality;
            else {
                fileName >> hackerPersonality;
                cout<<"You've entered number "<<hackerPersonality<<"\n";
            }
            if( (hackerPersonality == 1 || hackerPersonality == 2) || hackerPersonality == 3)
                root.help_commands(hackerPersonality);
            else {
                cout<<"That was a nice try, writing a name that is not in a list... You lost...";
                run = false;
            }
        }
        else if(number == 2)
            terminal.list_commands_help();

        else {
            cout<<"You tried to trick me by inserting something else than a number... Dissapointing...";
            run = false;
        }
    }
    void exec_commands(const string &input) {
        if(input == "ls")
            terminal.ls();
        else if(input == "pwd")
            terminal.pwd();
        else if(input == "cd")
            executeCdCommand();
        else if(input == "--caesar")
            executeCaesarCommand(inputFile, readingFromFile);
        else if(input == "--sha256")
            executeSHA256Command(inputFile, readingFromFile);
        else if(input == "cat")
            executeCATCommand();
        else if(input == "--help")
            displayHelp(inputFile, readingFromFile);
        else if(input == "--objective")
            cout<<level.getObjective();
        else if(input =="--exit")
            run = false;
        else
            cout<<"Command not found... Type --help to see the list of commands..."<<endl;
    }

    void display_prompt() {
        string playerName = interface.getPlayerName();
        terminal.displayPlayerName(playerName);
    }

    void readingCommandsFromFile() {
        string commandLine;
        while (getline(inputFile, commandLine)) {
            display_prompt();
            cout << "Executing from file: " << commandLine << endl;
            while(getline(inputFile, commandLine)) {
                cout << "Executing from file: " << commandLine << endl;
                exec_commands(commandLine);
            }
        }
        readingFromFile = false;
        inputFile.close();
    }

    void start() {
        while(run) {
            display_prompt();
            if(readingFromFile)
                readingCommandsFromFile();
            else {
                string input;
                cin>>input;
                exec_commands(input);
            }
        }
    }
};
int main() {

    GameEngine game("tastatura.txt");
    game.start();

    return 0;
}