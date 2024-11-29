#include "Hacker.h"

Hacker::Hacker(const string &specialization,const string &skills)
{
    this->specialization = specialization;
    this->skills = skills;


    commands_list[0][0] = "Decryption Alghoritms";
    commands_list[0][1] = "Hash Functions";
    commands_list[0][2] = "Key Exchange Protocols";

    commands_list[1][0] = "Metadata Analysis";
    commands_list[1][1] = "Searching Files";
    commands_list[1][2] = "Find Patterns";

    commands_list[2][0] = "Network Penetration Testing";
    commands_list[2][1] = "Packet Analysis";
    commands_list[2][2] = "Firewall and Intrusion Detection Bypassing";

    hacker_personality[0] = "CryptoHacker";
    hacker_personality[1] = "ForensicsHacker";
    hacker_personality[2] = "NetworkingHacker";

}
Hacker::Hacker(const Hacker &other) {
    specialization = other.specialization;
    skills = other.skills;

    for(int i = 0; i < 3; i++)
        for(int j=0; j < 3; j++)
            commands_list[i][j] = other.commands_list[i][j];
    for(int i = 0; i < 3; i++)
        hacker_personality[i] = other.hacker_personality[i];
}
Hacker& Hacker::operator=(const Hacker &other) {
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
void Hacker:: printHackerPersonality() const {
    for(int i = 0; i < 3; i++) {
        cout<<i+1<<". "<<hacker_personality[i]<<endl;
    }
}
bool Hacker::checkPersonality(const string &personality) {
    for(const auto & i : hacker_personality)
        if(personality == i)
            return true;
    return false;
}

string Hacker:: getCommands(const int i, const int j) const {return commands_list[i][j];}

bool Hacker:: checkCommandExist(const string &command) {
    ///VERIFICAM DACA EXISTA COMANDA
    for(auto & i : commands_list)
        for(const auto & j : i)
            if(command == j)
                return true;
    return false;
}
void Hacker:: help_commands(const int number) const {
    ///AFISAM COMEZILE DE HELP
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

ostream &operator<<(ostream &os, const Hacker &hacker) {
    os<<"Specialization: "<<hacker.specialization<<"\n";
    os<<"Skills: "<<hacker.skills<<"\n";
    return os;
}
