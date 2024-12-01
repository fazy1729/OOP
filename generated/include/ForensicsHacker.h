#ifndef FORENSICHACKER_H
#define FORENSICHACKER_H

#include <Hacker.h>

#include "EVERYTHING.h"
using namespace std;

class ForensicHacker:public Hacker {
private:
    string specialization;
public:
    ForensicHacker(const string &specialization) : Hacker("Forensic Investigator", specialization){}
    ForensicHacker() : specialization("General Forensics") {}
    ForensicHacker(const ForensicHacker &other) = default;
    void hack() override {
        cout << "Performing forensic analysis..." << endl;
        // Simulate extracting metadata from a file
        cout << "Extracting metadata from the file..." << endl;
        // (Again, just a print message for now)
        cout << "Metadata extracted! Investigating file history..." << endl;
    }

    void display() const override {
        cout << "ForensicHacker specializing in digital forensics!" << endl;
    }

    Hacker* clone() const override {
        return new ForensicHacker(*this);  // Returnează o clonă a obiectului ForensicHacker
    }

    ~ForensicHacker() = default;

    static void ExtractMetadata(const string &fileName, const map<string, vector<string>> &catFiles);
    static void SearchKeyword(const string &fileName, const string &keyword, const map<string, vector<string>> &catFiles);
    static void AnalyzeFilePatterns(const string &fileName, const map<string, vector<string>> &catFiles);


};

#endif