#include "ForensicsHacker.h"

/**
 * @brief Extracts metadata from a file.
 *
 * The method calculates the number of lines, words, and characters in the file content.
 * The word count is estimated by counting spaces and adding 1 for each line.
 *
 * @param fileName The name of the file to extract metadata from.
 * @param catFiles The map of files and their contents.
 */
void ForensicHacker::ExtractMetadata(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        std::cout << "File not found" << std::endl;
        return;
    }

    const std::vector<std::string> &fileContent = it->second;
    size_t numLines = fileContent.size();
    size_t numWords = 0;
    size_t numChars = 0;

    for (const auto &line : fileContent) {
        numChars += line.size();
        numWords += std::count_if(line.begin(), line.end(), [](char c) { return std::isspace(c); }) + 1;
    }

    std::cout << "File Metadata: " << std::endl;
    std::cout << "Lines: " << numLines << ", Words: " << numWords << ", Characters: " << numChars << std::endl;
}

/**
 * @brief Searches for a keyword in a file.
 *
 * This function looks for a specific keyword in a file's content. If found,
 * it prints the lines where the keyword appears along with their line numbers.
 *
 * @param fileName The name of the file to search in.
 * @param keyword The keyword to search for.
 * @param catFiles The map of files and their contents.
 */
void ForensicHacker::SearchKeyword(const std::string &fileName, const std::string &keyword, const std::map<std::string, std::vector<std::string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        std::cout << "File not found" << std::endl;
        return;
    }
    const std::vector<std::string> &fileContent = it->second;
    bool found = false;
    std::cout << "Searching for keyword '" << keyword << "' in file: " << fileName << std::endl;
    for (size_t lineNum = 0; lineNum < fileContent.size(); ++lineNum) {
        if (fileContent[lineNum].find(keyword) != std::string::npos) {
            found = true;
            std::cout << "Found at line " << lineNum + 1 << ": " << fileContent[lineNum] << std::endl;
        }
    }

    if (!found) {
        std::cout << "Keyword '" << keyword << "' not found in file." << std::endl;
    }
}

/**
 * @brief Analyzes a file for patterns such as email addresses, IP addresses, and URLs.
 *
 * This method uses regular expressions to detect email addresses, IP addresses,
 * and URLs in the content of the file. If any pattern is found, it prints the matching
 * strings along with their line numbers.
 *
 * @param fileName The name of the file to analyze.
 * @param catFiles The map of files and their contents.
 */
void ForensicHacker::AnalyzeFilePatterns(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles) {
    auto it = catFiles.find(fileName);
    if (it == catFiles.end()) {
        std::cout << "File not found" << std::endl;
        return;
    }

    const std::vector<std::string> &fileContent = it->second;

    std::regex emailRegex(R"(([\w\.-]+)@([\w\.-]+)\.([\w\.]{2,6}))");
    std::regex ipRegex(R"((\b\d{1,3}(\.\d{1,3}){3}\b))");
    std::regex urlRegex(R"((https?:\/\/[^\s]+))");

    std::cout << "Analyzing patterns in file: " << fileName << std::endl;

    bool patternFound = false;

    for (size_t lineNum = 0; lineNum < fileContent.size(); ++lineNum) {
        const std::string &line = fileContent[lineNum];

        for (std::sregex_iterator matches(line.begin(), line.end(), emailRegex), end; matches != end; ++matches) {
            std::cout << "Email found at line " << lineNum + 1 << ": " << matches->str() << std::endl;
            patternFound = true;
        }

        for (std::sregex_iterator matches(line.begin(), line.end(), ipRegex), end; matches != end; ++matches) {
            std::cout << "IP address found at line " << lineNum + 1 << ": " << matches->str() << std::endl;
            patternFound = true;
        }

        for (std::sregex_iterator matches(line.begin(), line.end(), urlRegex), end; matches != end; ++matches) {
            std::cout << "URL found at line " << lineNum + 1 << ": " << matches->str() << std::endl;
            patternFound = true;
        }
    }

    if (!patternFound) {
        std::cout << "No patterns (email, IP address, URL) were found in the file." << std::endl;
    }
}
