#ifndef BANK_H
#define BANK_H

#include <vector>
#include <memory>
#include <string>

#include "Customer.h"
#include "Account.h"

using namespace std;

class Bank {
private:
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Account>> accounts;
    const std::string CUSTOMERS_FILE = "data/customers.txt";
    const std::string ACCOUNTS_FILE = "data/accounts.txt";
public:
    Bank();
    shared_ptr<Customer> GetCustomer(int index) const;
    std::vector<std::shared_ptr<Customer>> SearchCustomer(const std::string& name) const;
    void DeleteCustomer(int index);
    void DeleteAccount(int index);
    double CalculateTotalAssets() const;
    void SortAccountsByBalance();
    void AddCustomer(const std::string& name, const std::string& id);
    void AddAccount(std::shared_ptr<Account> account);
    std::shared_ptr<Account> GetAccount(int index) const;
    void ShowAccounts() const;
    void ShowCustomers() const;
    void Transfer(std::shared_ptr<Account> from, std::shared_ptr<Account> to, double amount);
    void ShowAccountInfo(int index) const;
    void DepositToAccount(int index, double amount);
    void WithdrawFromAccount(int index, double amount);
    void ApplyInterestToSavings();
    void UpdateOverdraftLimit(int index, double newLimit);
    void Transfer(int fromIndex, int toIndex, double amount);
    void LoadData();
    void SaveData() const;
};

bool isValidId(const std::string& id);

#endif
