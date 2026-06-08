// Asset.hpp
#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>

class Asset {
protected:
    std::string name;
    double principal;
    double rate;
public:
    Asset(const std::string& n, double p, double r);
    virtual ~Asset() = default;
    virtual void display() const = 0;
    virtual std::string serialize() const = 0; // Thêm Serialize cho File I/O
};

class Debt : public Asset {
public:
    Debt(const std::string& n, double p, double r);
    void display() const override;
    std::string serialize() const override;
};

class Investment : public Asset {
private:
    std::string riskLevel;
public:
    Investment(const std::string& n, double p, double r, const std::string& risk);
    void display() const override;
    std::string serialize() const override;
};

#endif