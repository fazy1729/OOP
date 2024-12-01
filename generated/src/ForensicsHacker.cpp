#include "ForensicsHacker.h"

using namespace std;

void ForensicHacker::ExtractMetadata(const string &fileName, const map<string, vector<string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        cout << "File not found" << endl;
        return;
    }

    const vector<string> &fileContent = it->second;
    size_t numLines = fileContent.size();
    size_t numWords = 0;
    size_t numChars = 0;

    for (const auto &line : fileContent) {
        numChars += line.size();
        numWords += count_if(line.begin(), line.end(), [](char c) { return isspace(c); }) + 1; // Rough word count
    }

    cout << "File Metadata: " << endl;
    cout << "Lines: " << numLines << ", Words: " << numWords << ", Characters: " << numChars << endl;
}

void ForensicHacker::SearchKeyword(const string &fileName, const string &keyword, const map<string, vector<string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        cout << "File not found" << endl;
        return;
    }
    const vector<string> &fileContent = it->second;
    bool found = false;
    cout << "Searching for keyword '" << keyword << "' in file: " << fileName << endl;
    for (size_t lineNum = 0; lineNum < fileContent.size(); ++lineNum) {
        if (fileContent[lineNum].find(keyword) != string::npos) {
            found = true;
            cout << "Found at line " << lineNum + 1 << ": " << fileContent[lineNum] << endl;
        }
    }

    if (!found) {
        cout << "Keyword '" << keyword << "' not found in file." << endl;
    }
}
void ForensicHacker::AnalyzeFilePatterns(const string &fileName, const map<string, vector<string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        cout << "File not found" << endl;
        return;
    }

    const vector<string> &fileContent = it->second;

    // Define regex patterns for email, IP address, and URLs
    regex emailRegex(R"(([\w\.-]+)@([\w\.-]+)\.([\w\.]{2,6}))");
    regex ipRegex(R"((\b\d{1,3}(\.\d{1,3}){3}\b))");
    regex urlRegex(R"((https?:\/\/[^\s]+))");

    cout << "Analyzing patterns in file: " << fileName << endl;

    bool patternFound = false; // Tracks if any pattern was matched

    for (size_t lineNum = 0; lineNum < fileContent.size(); ++lineNum) {
        const string &line = fileContent[lineNum];

        // Match email addresses
        for (sregex_iterator matches(line.begin(), line.end(), emailRegex), end; matches != end; ++matches) {
            cout << "Email found at line " << lineNum + 1 << ": " << matches->str() << endl;
            patternFound = true;
        }

        // Match IP addresses
        for (sregex_iterator matches(line.begin(), line.end(), ipRegex), end; matches != end; ++matches) {
            cout << "IP address found at line " << lineNum + 1 << ": " << matches->str() << endl;
            patternFound = true;
        }

        // Match URLs
        for (sregex_iterator matches(line.begin(), line.end(), urlRegex), end; matches != end; ++matches) {
            cout << "URL found at line " << lineNum + 1 << ": " << matches->str() << endl;
            patternFound = true;
        }
    }

    if (!patternFound) {
        cout << "No patterns (email, IP address, URL) were found in the file." << endl;
    }
}