#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
private:
    std::string name;
    std::string id;
public:
    Customer(const std::string& name, const std::string& id);
    std::string GetName() const;
    std::string GetId() const;
    void DisplayInfo() const;
};

#endif
