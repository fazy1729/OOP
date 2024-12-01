#ifndef HACKEREXCEPTIONS_H
#define HACKEREXCEPTIONS_H

#include "EVERYTHING.h"

/**
 * @brief Base class for all exceptions related to Hacker operations.
 */
class HackerException : public std::exception {
public:
    /**
     * @brief Construct a new HackerException object.
     *
     * @param message The error message for the exception.
     */
    explicit HackerException(const std::string& message) : msg_(message) {}

    /**
     * @brief Get the error message for the exception.
     *
     * @return const char* The error message.
     */
    const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

/**
 * @brief Exception class for invalid command.
 */
class InvalidCommandException : public HackerException {
public:
    /**
     * @brief Construct a new InvalidCommandException object.
     *
     * @param command The invalid command that caused the exception.
     */
    explicit InvalidCommandException(const std::string& command)
        : HackerException("Invalid command: " + command) {}
};

/**
 * @brief Exception class for uninitialized hacker state.
 */
class UninitializedHackerException : public HackerException {
public:
    /**
     * @brief Construct a new UninitializedHackerException object.
     *
     * @param hackerType The type of hacker that is uninitialized.
     */
    explicit UninitializedHackerException(const std::string& hackerType)
        : HackerException("Uninitialized hacker state: " + hackerType) {}
};

/**
 * @brief Exception class for invalid hacker operation.
 */
class InvalidHackerOperationException : public HackerException {
public:
    /**
     * @brief Construct a new InvalidHackerOperationException object.
     *
     * @param operation The invalid operation that caused the exception.
     */
    explicit InvalidHackerOperationException(const std::string& operation)
        : HackerException("Invalid hacker operation: " + operation) {}
};

#endif
