#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

std::string toTitleCase(std::string s);
std::string formatWithDollar(double value, int width = 0);
std::string trim(const std::string& s);

void drawMenuFrame(const std::string& title, const std::vector<std::string>& options);
void printHeader(const std::string& title);

void clearInput();
double getSafeDouble(bool allowNegative = false);
int getSafeInt();
bool getSafeConfirmation(const std::string& prompt); // Hàm xác nhận Yes/No mới

// Xử lý ngày tháng nâng cao
std::string getCurrentDate();
void validateDate(const std::string& date);
std::vector<std::string> splitString(const std::string& str, char delimiter);

#endif