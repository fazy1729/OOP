#ifndef HACKEREXCEPTIONS_H
#define HACKEREXCEPTIONS_H

#include <exception>
#include <string>

// Base class for all exceptions related to Hacker operations
class HackerException : public std::exception {
public:
    explicit HackerException(const std::string& message) : msg_(message) {}
    const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


class InvalidCommandException : public HackerException {
public:
    explicit InvalidCommandException(const std::string& command)
        : HackerException("Invalid command: " + command) {}
};

// Exception for uninitialized hacker state
class UninitializedHackerException : public HackerException {
public:
    explicit UninitializedHackerException(const std::string& hackerType)
        : HackerException("Uninitialized hacker state: " + hackerType) {}
};

// Exception for invalid hacker operation
class InvalidHackerOperationException : public HackerException {
public:
    explicit InvalidHackerOperationException(const std::string& operation)
        : HackerException("Invalid hacker operation: " + operation) {}
};

#endif
