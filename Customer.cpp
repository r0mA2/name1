#include "Customer.h"

Customer::Customer(const std::string& name, const std::string& id) : name(name), id(id) {}
std::string Customer::GetName() const { return name; }
std::string Customer::GetId() const { return id; }
void Customer::DisplayInfo() const {
    std::cout << "Клиент: " << name << ", ID: " << id << std::endl;
}
