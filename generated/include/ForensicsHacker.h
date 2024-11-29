
#ifndef FORENSICSHACKER_H
#define FORENSICSHACKER_H
#ifndef FORENSICHACKER_H
#define FORENSICHACKER_H

#include "EVERYTHING.h"

class ForensicHacker {
public:
    static void ExtractMetadata(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles);
    static void SearchKeyword(const std::string &fileName, const std::string &keyword, const std::map<std::string, std::vector<std::string>> &catFiles);
    static void AnalyzeFilePatterns(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles);
};

#endif

#endif
