#include "EVERYTHING.h"
#include "Terminal.h"
using namespace std;

Terminal::Terminal() {
        fileSystem["/"] = {"home", "etc", "SECRET"};
        fileSystem["/home"] = {"user1", "user2"};
        fileSystem["/home/user1"] = {"caesar.txt", "file2.txt", "projects"};
        fileSystem["/etc"] = {"passwd", "hosts"};
        fileSystem["/SECRET"] =  {"CIA"};

        currentDirectory = "/";
    }

Terminal::Terminal(const Terminal &other) {
    this->fileSystem = other.fileSystem;
    this->currentDirectory = other.currentDirectory;
}

Terminal & Terminal::operator=(const Terminal &other) {
    if(this != &other) {
        fileSystem = other.fileSystem;
        currentDirectory = other.currentDirectory;
    }
    return *this;
}


string Terminal::getCurrentDirectory() {return currentDirectory;}

void Terminal::displayPlayerName(const string& playerName) {cout<<playerName<<"@"<<getCurrentDirectory() <<":$";}

void Terminal::list_commands_help() {
        cout<<"1. Linux commands - Commands to use in the terminal\n";
        cout<<"2. Hacker commands - Commands that can help you pass a level\n";
        cout<<"Enter a number: ";
        int number;cin>>number;
        if(number == 1) {
            cout<<"ls - Prints the contents in a directory: usage example: ls <directory>\n";
            cout<<"cd - Navigate to another directory: usage example: cd <directory>\n";
            cout<<"pwd - Prints the working directory: usage example: pwd\n";
            cout<<"--objective - See the objective for this level\n";
        }
        else if(number == 2) {
            cout<<"--sha256 - You can hash a message using the SHA256 alghoritm : usage example : --sha256 <file.txt>\n";
            cout<<"--caesar - You can decrypt an encrypted message that if shifted with 3 positions: usage example: --caesar <file.txt>\n";
        }
    }

void Terminal::ls() const {
    cout<<"Listing files in: "<<currentDirectory<<endl;
    auto it = fileSystem.find(currentDirectory);
    if (it != fileSystem.end()) {
        for(const string& fileName : it->second)
            cout<<fileName<<endl;
    } else {
        cout<<"Files not found";
    }
}


void Terminal::cd(const string &directory) {
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
void Terminal::pwd() const {
    cout<<"Current directory: " << currentDirectory << "\n";
}


void Terminal::cat(const string &key, const map<string, vector<string>> &catFile) const {
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

ostream& operator<<(ostream &os, const Terminal &terminal) {
    os<<"Current directory: "<<terminal.currentDirectory<<"\n";
    return os;
}