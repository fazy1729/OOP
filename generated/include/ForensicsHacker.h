#ifndef FORENSICHACKER_H
#define FORENSICHACKER_H

#include "EVERYTHING.h"
using namespace std;

class ForensicHacker {
private:
    string specialization;
public:
    ForensicHacker(const string &specialization) : specialization(specialization) {}
    ForensicHacker() : specialization("General Forensics") {}
    ForensicHacker(const ForensicHacker &other) = default;

    ~ForensicHacker() = default;

    static void ExtractMetadata(const string &fileName, const map<string, vector<string>> &catFiles);
    static void SearchKeyword(const string &fileName, const string &keyword, const map<string, vector<string>> &catFiles);
    static void AnalyzeFilePatterns(const string &fileName, const map<string, vector<string>> &catFiles);


};

#endif