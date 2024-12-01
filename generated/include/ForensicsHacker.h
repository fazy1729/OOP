#ifndef FORENSICHACKER_H
#define FORENSICHACKER_H

#include <Hacker.h>
#include "EVERYTHING.h"

// ForensicHacker class definition
// This class represents a hacker specialized in forensic analysis, focusing on tasks like metadata extraction, file pattern analysis, and keyword search.

class ForensicHacker : public Hacker {
private:
    // The specialization of the forensic hacker (e.g., "File Metadata Extraction").
    std::string specialization;

public:
    // Constructor that initializes ForensicHacker with a specific specialization.
    // @param specialization A string representing the forensic specialization.
    ForensicHacker(const std::string &specialization) : Hacker("Forensic Investigator", specialization) {}

    // Default constructor that initializes specialization to "General Forensics".
    ForensicHacker() : specialization("General Forensics") {}

    // Copy constructor for ForensicHacker.
    ForensicHacker(const ForensicHacker &other) = default;

    // Overrides the hack method to perform forensic analysis (e.g., metadata extraction).
    // This method simulates the extraction of metadata from files.
    void hack() override {
        std::cout << "Performing forensic analysis..." << std::endl;
        std::cout << "Extracting metadata from the file..." << std::endl;
        std::cout << "Metadata extracted! Investigating file history..." << std::endl;
    }

    // Displays the specialization of the ForensicHacker.
    void display() const override {
        std::cout << "ForensicHacker specializing in digital forensics!" << std::endl;
    }

    // Creates a clone of the current ForensicHacker object.
    // @return A pointer to a new ForensicHacker object.
    Hacker* clone() const override {
        return new ForensicHacker(*this);
    }

    // Destructor for ForensicHacker
    ~ForensicHacker() = default;

    // Static method that extracts metadata from a given file.
    // @param fileName The name of the file to extract metadata from.
    // @param catFiles A map containing files and their associated content.
    static void ExtractMetadata(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles);

    // Static method to search for a specific keyword in a file's content.
    // @param fileName The name of the file to search within.
    // @param keyword The keyword to search for in the file.
    // @param catFiles A map containing files and their associated content.
    static void SearchKeyword(const std::string &fileName, const std::string &keyword, const std::map<std::string, std::vector<std::string>> &catFiles);

    // Static method to analyze file patterns in a given file.
    // @param fileName The name of the file to analyze.
    // @param catFiles A map containing files and their associated content.
    static void AnalyzeFilePatterns(const std::string &fileName, const std::map<std::string, std::vector<std::string>> &catFiles);
};

#endif
