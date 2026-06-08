// FinanceManager.cpp
#include "FinanceManager.hpp"
#include "Utils.hpp"
#include "Exceptions.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

FinanceManager::FinanceManager() : balance(0.0) {}

void FinanceManager::addTransaction(unique_ptr<Transaction> t) {
    if (t->isExpense()) balance -= t->getAmount();
    else balance += t->getAmount();
    
    bst.insert(t.get());
    transactions.push_back(move(t));
}

void FinanceManager::addAsset(unique_ptr<Asset> a) {
    portfolio.push_back(move(a));
}

void FinanceManager::displayDashboard() const {
    printHeader("FINANCIAL DASHBOARD");
    cout << "  Current Total Balance:  " << formatWithDollar(balance) << "\n";
    cout << "+" << string(75, '-') << "+\n";
    
    cout << "\n>>> RECENT TRANSACTIONS (Unit: USD | Date: YYYY-MM-DD):\n";
    cout << string(77, '=') << "\n";
    if (transactions.empty()) cout << "  No transactions recorded.\n";
    for (const auto& t : transactions) t->display();
    cout << string(77, '-') << "\n";
    
    cout << "\n>>> ASSETS & DEBTS (Unit: USD | Rate: %/year):\n";
    cout << string(77, '=') << "\n";
    if (portfolio.empty()) cout << "  No assets or debts recorded.\n";
    for (const auto& a : portfolio) a->display();
    cout << string(77, '-') << "\n";
}

void FinanceManager::generateCategoryReport() const {
    printHeader("EXPENSE CATEGORY REPORT (STD::MAP)");
    map<string, double> categorySums;
    double totalExpenses = 0.0;

    for (const auto& t : transactions) {
        if (t->isExpense()) {
            categorySums[t->getCategory()] += t->getAmount();
            totalExpenses += t->getAmount();
        }
    }

    if (categorySums.empty()) {
        cout << "  [INFO] No expenses to report.\n";
        return;
    }

    cout << left << setw(20) << "CATEGORY" << "TOTAL SPENT\n";
    cout << string(40, '-') << "\n";
    for (const auto& pair : categorySums) {
        cout << left << setw(20) << pair.first << formatWithDollar(pair.second) << "\n";
    }
    cout << string(40, '-') << "\n";
    cout << left << setw(20) << "TOTAL:" << formatWithDollar(totalExpenses) << "\n";
}

void FinanceManager::calculateSavingsRate() const {
    printHeader("SAVINGS STRATEGY");
    double totalIncome = 0.0, totalExpense = 0.0;
    for (const auto& t : transactions) {
        if (t->isExpense()) totalExpense += t->getAmount();
        else totalIncome += t->getAmount();
    }
    if (totalIncome == 0) {
        cout << "  [INFO] Add income to calculate savings rate.\n";
        return;
    }
    double rate = ((totalIncome - totalExpense) / totalIncome) * 100;
    cout << "  Total Income:   " << formatWithDollar(totalIncome) << "\n";
    cout << "  Total Expenses: " << formatWithDollar(totalExpense) << "\n";
    cout << "  Savings Rate:   " << fixed << setprecision(2) << rate << "%\n";
}

void FinanceManager::showTransactionsSorted() const {
    printHeader("TRANSACTIONS SORTED BY AMOUNT (BST)");
    bst.displaySortedByAmount();
}

void FinanceManager::searchTransactionsByAmount(double minAmount) const {
    printHeader("SEARCH TRANSACTIONS >= " + formatWithDollar(minAmount));
    bst.displayAboveAmount(minAmount);
}

void FinanceManager::saveData(const string& filename) const {
    try {
        ofstream file(filename);
        if (!file.is_open()) throw FileIOException("Could not open " + filename + " for writing.");
        
        // --- TRANG TRÍ FILE TEXT KHI MỞ BẰNG NOTEPAD ---
        file << "=========================================================\n";
        file << "           SMART FINANCE TRACKER - DATA BACKUP           \n";
        file << "  Currency Unit: USD ($)  |  Date Format: YYYY-MM-DD     \n";
        file << "=========================================================\n\n";

        file << "--- TRANSACTIONS (Format: Type|Amount|Date|Category|Source/Type) ---\n";
        for (const auto& t : transactions) file << t->serialize() << "\n";
        
        file << "\n--- ASSETS & DEBTS (Format: Type|Name|Principal|Rate|Risk) ---\n";
        for (const auto& a : portfolio) file << a->serialize() << "\n";
        
        cout << "  [SUCCESS] System state securely backed up to " << filename << ".\n";
    } catch (const exception& e) {
        cerr << "  " << e.what() << "\n";
    }
}

void FinanceManager::loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return; 

    string line;
    while (getline(file, line)) {
        // Bỏ qua các dòng trống hoặc các dòng trang trí Header
        if (line.empty() || line[0] == '=' || line[0] == '-') continue;

        vector<string> tokens = splitString(line, '|');
        if (tokens.size() < 4) continue; // Bỏ qua dòng lỗi

        try {
            string type = tokens[0];
            if (type == "INCOME" && tokens.size() == 5) {
                addTransaction(make_unique<Income>(stod(tokens[1]), tokens[2], tokens[3], tokens[4]));
            } 
            else if (type == "EXPENSE" && tokens.size() == 5) {
                addTransaction(make_unique<Expense>(stod(tokens[1]), tokens[2], tokens[3], tokens[4]));
            }
            else if (type == "DEBT" && tokens.size() == 4) {
                addAsset(make_unique<Debt>(tokens[1], stod(tokens[2]), stod(tokens[3])));
            }
            else if (type == "INVESTMENT" && tokens.size() == 5) {
                addAsset(make_unique<Investment>(tokens[1], stod(tokens[2]), stod(tokens[3]), tokens[4]));
            }
        } catch (...) { 
            cerr << "  [WARNING] Skipped a corrupted line in data file.\n";
        }
    }
}