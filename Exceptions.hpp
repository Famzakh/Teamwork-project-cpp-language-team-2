#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class FinanceException : public std::exception {
protected:
    std::string message;
public:
    explicit FinanceException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidAmountException : public FinanceException {
public:
    explicit InvalidAmountException(const std::string& msg = "Amount must be greater than zero.") 
        : FinanceException("[ERROR] Invalid Amount: " + msg) {}
};

class InvalidDateException : public FinanceException {
public:
    explicit InvalidDateException(const std::string& msg = "Date must follow YYYY-MM-DD format and be a valid calendar date.") 
        : FinanceException("[ERROR] Invalid Date: " + msg) {}
};

class FutureDateException : public FinanceException {
public:
    explicit FutureDateException() 
        : FinanceException("[ERROR] Date cannot be in the future. Please enter a current or past date.") {}
};

class FileIOException : public FinanceException {
public:
    explicit FileIOException(const std::string& msg) 
        : FinanceException("[ERROR] File I/O: " + msg) {}
};

#endif