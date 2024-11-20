#include "GameEngine.h"
using namespace std;

GameEngine::GameEngine(const string& fileName) :
      root("CryptoHacker", "ROOT"),
      cryptohacker("HELP"),
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
void GameEngine::executeCdCommand() {
    ///FACEM CD DIN LINUX - EFECTIV NE PLIMBAM PRIN HASHMAP
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
void GameEngine::executeCaesarCommand(ifstream &inputFile, bool isReadingFromFile) {
    ///EXECUTAM ALGORITMUL CEZAR
    string file;
    if (isReadingFromFile == false)
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
void GameEngine::executeSHA256Command(ifstream &file, bool isReadingFromFile) {
    ///EXECUTAM ALGORITMUL DE HASHING
    string fileName;
    if(isReadingFromFile == false)
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
void GameEngine::executeCATCommand() {
    ///COMANDA CAT EFECTIV NE ARATA CE SE AFLA IN CHEIA MAPULUI
    string file;
    getline(cin,file);
    terminal.cat(file,level.getCatFiles());
}
void GameEngine::displayHelp(ifstream &fileName, const bool &isFileRead) {
    ///PREZENTARE DIVERSE FUNCTII CARE EXISTA PE BAZA CATEGORIEI DIN CARE FAC PARTE
    cout<<"HOW MIGHT I HELP YOU TODAY?"<<endl;
    cout<<"1. List of personalities: "<<endl;
    cout<<"2. List of commands: "<<endl;
    cout<<"Enter a number:";

    int number;
    if(isFileRead == false)
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
        if(isFileRead == false)
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
void GameEngine::exec_commands(const string &input) {
    ///IN FUNCTIE DE INPUT-UL UTILIZATORIULUI EXECUTAM COMANDA, DACA NU EXISTA ATUNCI NE VA AFISA UN MESAJ CORESPUNZATOR
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

void GameEngine::display_prompt() {
    ///NE ARATA PROMPTUL
    string playerName = interface.getPlayerName();
    terminal.displayPlayerName(playerName);
}

void GameEngine::readingCommandsFromFile() {
    ///CITIRE DIN FISIER PENTRU SIMULARE
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

    void GameEngine::start() {
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

GameEngine::GameEngine(const GameEngine &other)
    : root(other.root),
      cryptohacker(other.cryptohacker),
      interface(other.interface),
      level(other.level),
      readingFromFile(other.readingFromFile),
      run(other.run)
{
    if (readingFromFile && other.inputFile.is_open()) {
        inputFile.open("tastatura.txt");
        if (!inputFile) {
            cerr << "Unable to open file tastatura.txt" << endl;
            readingFromFile = false;
        }
    }
}

GameEngine& GameEngine::operator=(const GameEngine &other) {
    if (this != &other) {
        root = other.root;
        cryptohacker = other.cryptohacker;
        level = other.level;
        readingFromFile = other.readingFromFile;
        run = other.run;

        if (inputFile.is_open()) {
            inputFile.close();
        }
        if (readingFromFile && other.readingFromFile) {
            inputFile.open("tastatura.txt");
            if (!inputFile) {
                cerr << "Unable to open file tastatura.txt" << endl;
                readingFromFile = false;
            }
        }
    }
    return *this;
}
