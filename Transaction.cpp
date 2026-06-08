#include "Transaction.hpp"
#include "Utils.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Transaction::Transaction(double amt, const string& dt, const string& cat)
    : amount(amt), date(dt), category(cat) {}

double Transaction::getAmount() const { return amount; }
string Transaction::getDate() const { return date; }
string Transaction::getCategory() const { return category; }

Income::Income(double amt, const string& dt, const string& cat, const string& src)
    : Transaction(amt, dt, cat), source(src) {}

void Income::display() const {
    cout << left << "| " << setw(11) << "[INCOME]" 
         << "| Date: " << setw(12) << date 
         << "| Amt: " << setw(12) << formatWithDollar(amount) 
         << "| Cat: " << setw(12) << category 
         << "| Src: " << source << "\n";
}

string Income::serialize() const {
    return "INCOME|" + to_string(amount) + "|" + date + "|" + category + "|" + source;
}

Expense::Expense(double amt, const string& dt, const string& cat, const string& t)
    : Transaction(amt, dt, cat), type(t) {}

void Expense::display() const {
    cout << left << "| " << setw(11) << "[EXPENSE]" 
         << "| Date: " << setw(12) << date 
         << "| Amt: " << setw(12) << formatWithDollar(-amount) 
         << "| Cat: " << setw(12) << category 
         << "| Typ: " << type << "\n";
}

string Expense::serialize() const {
    return "EXPENSE|" + to_string(amount) + "|" + date + "|" + category + "|" + type;
}