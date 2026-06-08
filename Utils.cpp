#include "Utils.hpp"
#include "Exceptions.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <ctime>

using namespace std;

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == string::npos) return "";
    return s.substr(start, end - start + 1);
}

string toTitleCase(string s) {
    s = trim(s);
    if (s.empty()) return s;
    for (char &c : s) c = tolower(static_cast<unsigned char>(c));
    s[0] = toupper(static_cast<unsigned char>(s[0]));
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i-1] == ' ' && isalpha(static_cast<unsigned char>(s[i]))) {
            s[i] = toupper(static_cast<unsigned char>(s[i]));
        }
    }
    return s;
}

string formatWithDollar(double value, int width) {
    stringstream ss;
    ss << "$" << fixed << setprecision(2) << value;
    string formattedValue = ss.str();
    while (formattedValue.length() < (size_t)width) {
        formattedValue += " ";
    }
    return formattedValue;
}

void drawMenuFrame(const string& title, const vector<string>& options) {
    int width = 55;
    cout << "\n+" << string(width - 2, '=') << "+\n";
    int pad = (width - 2 - title.length()) / 2;
    cout << "|" << string(pad, ' ') << title << string(width - 2 - title.length() - pad, ' ') << "|\n";
    cout << "+" << string(width - 2, '=') << "+\n";
    
    for (const auto& opt : options) {
        cout << "| " << opt << string(width - 4 - opt.length(), ' ') << " |\n";
    }
    cout << "+" << string(width - 2, '-') << "+\n";
    cout << "Enter your choice: ";
}

void printHeader(const string& title) {
    int width = 55;
    cout << "\n+" << string(width - 2, '*') << "+\n";
    int pad = (width - 2 - title.length()) / 2;
    cout << "|" << string(pad, ' ') << title << string(width - 2 - title.length() - pad, ' ') << "|\n";
    cout << "+" << string(width - 2, '*') << "+\n";
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double getSafeDouble(bool allowNegative) {
    double value;
    while (true) {
        if (!(cin >> value)) {
            cout << "[ERROR] Invalid input. Please enter a numeric value: ";
            clearInput();
            continue;
        }

        while (cin.peek() == ' ' || cin.peek() == '\t') {
            cin.get();
        }

        if (cin.peek() != '\n' && cin.peek() != '\r' && cin.peek() != EOF) {
            cout << "[ERROR] Invalid input. Please enter only a numeric value: ";
            clearInput();
            continue;
        }

        if (!allowNegative && value < 0) {
            cout << "[ERROR] Value cannot be negative. Please enter again: ";
            clearInput();
            continue;
        }

        return value;
    }
}

int getSafeInt() {
    int value;
    while (true) {
        if (!(cin >> value)) {
            cout << "[ERROR] Invalid input. Please enter an integer: ";
            clearInput();
            continue;
        }

        while (cin.peek() == ' ' || cin.peek() == '\t') {
            cin.get();
        }

        if (cin.peek() != '\n' && cin.peek() != '\r' && cin.peek() != EOF) {
            cout << "[ERROR] Invalid input. Please enter only an integer: ";
            clearInput();
            continue;
        }

        return value;
    }
}

bool getSafeConfirmation(const string& prompt) {
    string input;
    while (true) {
        cout << prompt << " (y/n): ";
        if (!(cin >> input)) {
            clearInput();
            continue;
        }
        
        if (input.empty()) continue;
        char check = tolower(static_cast<unsigned char>(input[0]));
        
        if (check == 'y') {
            // Dọn dẹp ký tự thừa còn lại trên luồng dòng nhập nếu có
            while (cin.peek() == ' ' || cin.peek() == '\t') cin.get();
            if (cin.peek() == '\n' || cin.peek() == '\r') cin.get();
            return true;
        } else if (check == 'n') {
            while (cin.peek() == ' ' || cin.peek() == '\t') cin.get();
            if (cin.peek() == '\n' || cin.peek() == '\r') cin.get();
            return false;
        }
        
        cout << "[ERROR] Invalid input. Please enter 'y' for Yes or 'n' for No.\n";
    }
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setfill('0') << setw(2) << ltm->tm_mday;
    return ss.str();
}

void validateDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        throw InvalidDateException("Format must be exactly YYYY-MM-DD.");
    }
    
    try {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        
        if (year < 2000 || year > 2100) throw InvalidDateException("Year out of realistic range.");
        if (month < 1 || month > 12) throw InvalidDateException("Month must be between 01 and 12.");
        if (day < 1 || day > 31) throw InvalidDateException("Day must be between 01 and 31.");
        
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            throw InvalidDateException("This month only has 30 days.");
            
        if (month == 2) {
            bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (isLeap && day > 29) throw InvalidDateException("February has 29 days in a leap year.");
            if (!isLeap && day > 28) throw InvalidDateException("February has 28 days in a non-leap year.");
        }

        time_t now = time(0);
        tm* ltm = localtime(&now);
        int curYear = 1900 + ltm->tm_year;
        int curMonth = 1 + ltm->tm_mon;
        int curDay = ltm->tm_mday;

        if (year > curYear || 
           (year == curYear && month > curMonth) || 
           (year == curYear && month == curMonth && day > curDay)) {
            throw FutureDateException();
        }

    } catch (const FinanceException&) {
        throw; 
    } catch (...) {
        throw InvalidDateException("Contains non-numeric characters.");
    }
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}