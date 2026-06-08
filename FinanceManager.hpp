// FinanceManager.hpp
#ifndef FINANCEMANAGER_HPP
#define FINANCEMANAGER_HPP

#include "Transaction.hpp"
#include "Asset.hpp"
#include "TransactionBST.hpp"
#include <vector>
#include <memory>
#include <map>
#include <string>

class FinanceManager {
private:
    std::vector<std::unique_ptr<Transaction>> transactions;
    std::vector<std::unique_ptr<Asset>> portfolio;
    TransactionBST bst; 
    double balance;

public:
    FinanceManager();
    
    void addTransaction(std::unique_ptr<Transaction> t);
    void addAsset(std::unique_ptr<Asset> a);
    
    void displayDashboard() const;
    void showTransactionsSorted() const;
    void searchTransactionsByAmount(double minAmount) const;
    void calculateSavingsRate() const;
    void generateCategoryReport() const; // Dùng std::map
    
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);
};

#endif