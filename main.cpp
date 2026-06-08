#include "FinanceManager.hpp"
#include "Utils.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    FinanceManager app;
    app.loadData("data.txt"); 

    printHeader("WELCOME TO SMART FINANCE TRACKER");

    int choice = 0;
    while (choice != 9) {
        drawMenuFrame("MAIN MENU", {
            "1. Add Income",
            "2. Add Expense",
            "3. Add Debt / Investment",
            "4. View Full Dashboard",
            "5. Category Expense Report (Map)",
            "6. View Transactions Sorted (BST)",
            "7. Search Transactions by Amount",
            "8. Savings Strategy Report",
            "9. Save Data & Exit"
        });
        
        choice = getSafeInt();
        clearInput(); 

        // Kiểm tra xác nhận Yes/No đối với Menu chính
        if (choice >= 1 && choice <= 9) {
            string optionName = "";
            if (choice == 1) optionName = "Add Income";
            else if (choice == 2) optionName = "Add Expense";
            else if (choice == 3) optionName = "Add Debt / Investment";
            else if (choice == 4) optionName = "View Full Dashboard";
            else if (choice == 5) optionName = "Category Expense Report (Map)";
            else if (choice == 6) optionName = "View Transactions Sorted (BST)";
            else if (choice == 7) optionName = "Search Transactions by Amount";
            else if (choice == 8) optionName = "Savings Strategy Report";
            else if (choice == 9) optionName = "Save Data & Exit";

            if (!getSafeConfirmation("Are you sure you want to select '" + optionName + "'?")) {
                cout << "  [INFO] Action cancelled. Returning to Main Menu...\n";
                continue;
            }
        }

        try {
            if (choice == 1) {
                printHeader("ADD INCOME");
                cout << "Amount (e.g., 1500.50): $"; double amt = getSafeDouble(false);
                if (amt <= 0) throw InvalidAmountException("Income must be greater than $0.");
                
                cout << "Date (YYYY-MM-DD, e.g., 2026-06-08) or type 't' for today: "; string dt; cin >> dt;
                if (dt == "t" || dt == "today") {
                    dt = getCurrentDate();
                    cout << "  -> Auto-filled with Real-time Date: " << dt << "\n";
                } else {
                    validateDate(dt);
                }
                
                cout << "Category (e.g., Salary, Freelance, Gift): "; string cat; getline(cin >> ws, cat);
                cout << "Source (e.g., Company Name, Client A): "; string src; getline(cin, src);
                
                app.addTransaction(make_unique<Income>(amt, dt, toTitleCase(cat), toTitleCase(src)));
                cout << "\n  [SUCCESS] Income Recorded.\n";
            }
            else if (choice == 2) {
                printHeader("ADD EXPENSE");
                cout << "Amount (e.g., 45.00): $"; double amt = getSafeDouble(false);
                if (amt <= 0) throw InvalidAmountException("Expense must be greater than $0.");
                
                cout << "Date (YYYY-MM-DD, e.g., 2026-06-08) or type 't' for today: "; string dt; cin >> dt;
                if (dt == "t" || dt == "today") {
                    dt = getCurrentDate();
                    cout << "  -> Auto-filled with Real-time Date: " << dt << "\n";
                } else {
                    validateDate(dt);
                }
                
                cout << "Category (e.g., Food, Transport, Rent): "; string cat; getline(cin >> ws, cat);
                cout << "Type (e.g., Fixed, Variable): "; string t; getline(cin, t);
                
                app.addTransaction(make_unique<Expense>(amt, dt, toTitleCase(cat), toTitleCase(t)));
                cout << "\n  [SUCCESS] Expense Recorded.\n";
            }
            else if (choice == 3) {
                printHeader("ADD DEBT / INVESTMENT");
                
                int assetChoice = 0;
                bool verifiedAsset = false;
                
                while (!verifiedAsset) {
                    cout << "Select Asset Type:\n1. Debt\n2. Investment\nEnter your choice (1 or 2): ";
                    assetChoice = getSafeInt();
                    clearInput();
                    
                    if (assetChoice == 1 || assetChoice == 2) {
                        string assetTypeName = (assetChoice == 1) ? "Debt" : "Investment";
                        if (getSafeConfirmation("Are you sure you want to add a new '" + assetTypeName + "'?")) {
                            verifiedAsset = true; 
                        } else {
                            cout << "  [INFO] Asset type selection cancelled. Back to choice point...\n";
                        }
                    } else {
                        cout << "  [ERROR] Invalid choice. Please select either 1 or 2.\n";
                    }
                }
                
                cout << "Name (e.g., Student Loan, S&P 500 Index): "; string name; getline(cin >> ws, name);
                cout << "Principal Amount (e.g., 5000): $"; double p = getSafeDouble(false);
                cout << "Interest/Return Rate (%, e.g., 5.5): "; double r = getSafeDouble(true);
                
                if (assetChoice == 1) {
                    app.addAsset(make_unique<Debt>(toTitleCase(name), p, r));
                    cout << "\n  [SUCCESS] Debt Added.\n";
                } else {
                    cout << "Risk Level (e.g., Low, Med, High): "; string risk; getline(cin >> ws, risk);
                    app.addAsset(make_unique<Investment>(toTitleCase(name), p, r, toTitleCase(risk)));
                    cout << "\n  [SUCCESS] Investment Added.\n";
                }
            }
            else if (choice == 4) app.displayDashboard();
            else if (choice == 5) app.generateCategoryReport();
            else if (choice == 6) app.showTransactionsSorted();
            else if (choice == 7) {
                printHeader("FILTER TRANSACTIONS");
                cout << "Enter minimum amount to search (e.g., 100): $"; double minAmt = getSafeDouble(false);
                app.searchTransactionsByAmount(minAmt);
            }
            else if (choice == 8) app.calculateSavingsRate();
            else if (choice == 9) {
                printHeader("EXITING PROGRAM");
                app.saveData("data.txt");
                cout << "  Goodbye!\n";
            }
            else {
                cout << "  [ERROR] Please select a number from 1 to 9.\n";
            }
        } 
        catch (const FinanceException& e) {
            cerr << "\n  " << e.what() << "\n";
            clearInput();
        } 
        catch (const exception& e) {
            cerr << "\n  [CRITICAL ERROR] " << e.what() << "\n";
            clearInput();
        }
    }
    return 0;
}