// Asset.cpp
#include "Asset.hpp"
#include "Utils.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Asset::Asset(const string& n, double p, double r) : name(n), principal(p), rate(r) {}

Debt::Debt(const string& n, double p, double r) : Asset(n, p, r) {}

void Debt::display() const {
    stringstream ssRate;
    ssRate << fixed << setprecision(1) << rate << "%";

    cout << left << "| " << setw(14) << "[DEBT]" 
         << "| " << setw(18) << name 
         << "| Principal: " << setw(12) << formatWithDollar(principal) 
         << "| Rate/Yr: " << setw(8) << ssRate.str() << " |\n";
}

string Debt::serialize() const {
    return "DEBT|" + name + "|" + to_string(principal) + "|" + to_string(rate);
}

Investment::Investment(const string& n, double p, double r, const string& risk)
    : Asset(n, p, r), riskLevel(risk) {}

void Investment::display() const {
    stringstream ssRate;
    ssRate << fixed << setprecision(1) << rate << "%";

    cout << left << "| " << setw(14) << "[INVESTMENT]" 
         << "| " << setw(18) << name 
         << "| Principal: " << setw(12) << formatWithDollar(principal) 
         << "| Return: " << setw(7) << ssRate.str() 
         << "| Risk: " << riskLevel << "\n";
}

string Investment::serialize() const {
    return "INVESTMENT|" + name + "|" + to_string(principal) + "|" + to_string(rate) + "|" + riskLevel;
}