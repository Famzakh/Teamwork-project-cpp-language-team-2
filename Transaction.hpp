#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

class Transaction {
protected:
    double amount;
    std::string date;
    std::string category;
public:
    Transaction(double amt, const std::string& dt, const std::string& cat);
    virtual ~Transaction() = default;
    
    virtual void display() const = 0;
    virtual std::string serialize() const = 0;
    
    double getAmount() const;
    std::string getDate() const;
    std::string getCategory() const;
    virtual bool isExpense() const = 0;
};

class Income : public Transaction {
private:
    std::string source;
public:
    Income(double amt, const std::string& dt, const std::string& cat, const std::string& src);
    void display() const override;
    std::string serialize() const override;
    bool isExpense() const override { return false; }
};

class Expense : public Transaction {
private:
    std::string type;
public:
    Expense(double amt, const std::string& dt, const std::string& cat, const std::string& t);
    void display() const override;
    std::string serialize() const override;
    bool isExpense() const override { return true; }
};

#endif