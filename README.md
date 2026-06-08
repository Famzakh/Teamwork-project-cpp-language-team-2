# Smart Finance Tracker

A robust, console-based personal finance management application written in C++17. This application helps users track their incomes, expenses, debts, and investments while providing analytical tools like category reports, transaction sorting using a Binary Search Tree (BST), and savings strategy calculations.

## 🚀 Features

* **Income & Expense Tracking:** Record daily transactions with specific categories, sources, and dates.
* **Asset & Debt Management:** Track debts and investments with principal amounts, interest/return rates, and risk levels.
* **Comprehensive Dashboard:** View your current total balance along with nicely formatted tables of recent transactions and active assets.
* **Category Reporting:** Automatically group and calculate total expenses by category using `std::map`.
* **Advanced Sorting & Filtering:** Utilizes a custom Binary Search Tree (BST) to quickly view transactions sorted by amount or filter them above a specific threshold.
* **Savings Strategy:** Automatically calculates your current savings rate based on total income and expenses.
* **Data Persistence:** Automatically saves your financial state to a local `data.txt` file and restores it upon the next startup.
* **Robust Input Handling:** Safeguards against invalid inputs (e.g., negative amounts, future dates, invalid characters) and includes safety `(y/n)` confirmations for menu selections.

## 🛠 Prerequisites

* **C++ Compiler:** GCC (g++) with support for the C++17 standard.
* **Make Utility:** A `make` tool installed on your system (e.g., MinGW32-make for Windows) to utilize the provided `makefile`.

## ⚙️ How to Build and Run

This project includes a `makefile` to simplify the compilation and execution process. Open your terminal or command prompt in the root directory of the project and use the following commands:

### 1. Build and Launch
To compile all source code files and automatically run the application, simply type:
```bash
make
