#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "BusinessAccount.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

Bank::Bank() {
    LoadData();
}

shared_ptr<Customer> Bank::GetCustomer(int index) const {
    if (index < 0 || index >= customers.size()) {
        return nullptr;
    }
    return customers[index];
}

std::vector<std::shared_ptr<Customer>> Bank::SearchCustomer(const std::string& name) const {
    std::vector<std::shared_ptr<Customer>> result;
    for (const auto& customer : customers) {
        if (customer->GetName() == name) {
            result.push_back(customer);
        }
    }
    return result;
}

void Bank::DeleteCustomer(int index) {
    if (index < 0 || index >= customers.size()) {
        std::cout << "Некорректный индекс клиента!" << std::endl;
        return;
    }

    bool hasAccounts = false;
    hasAccounts = false;

    if (hasAccounts) {
        std::cout << "Нельзя удалить клиента, т.к. у него есть открытые счета." << std::endl;
    }
    else {
        customers.erase(customers.begin() + index);
        std::cout << "Клиент удален." << std::endl;
    }
}

void Bank::DeleteAccount(int index) {
    std::shared_ptr<Account> account = GetAccount(index);
    if (account) {
        if (account->GetBalance() != 0) {
            std::cout << "Нельзя удалить аккаунт с балансом не равным 0!" << std::endl;
        }
        else {
            accounts.erase(accounts.begin() + index);
            std::cout << "Аккаунт удален." << std::endl;
        }
    }
    else {
        std::cout << "Некорректный индекс аккаунта." << std::endl;
    }
}

double Bank::CalculateTotalAssets() const {
    double total = 0;
    for (const auto& account : accounts) {
        total += account->GetBalance();
    }
    return total;
}

void Bank::SortAccountsByBalance() {
    std::sort(accounts.begin(), accounts.end(), [](const auto& a, const auto& b) {
        return a->GetBalance() < b->GetBalance();
        });
    std::cout << "Счета отсортированы по балансу (от меньшего к большему)." << std::endl;
}


void Bank::AddCustomer(const std::string& name, const std::string& id) {
    customers.push_back(std::make_shared<Customer>(name, id));
}

void Bank::AddAccount(std::shared_ptr<Account> account) {
    accounts.push_back(account);
}

std::shared_ptr<Account> Bank::GetAccount(int index) const {
    if (index < 0 || index >= accounts.size()) {
        return nullptr;
    }
    return accounts[index];
}

void Bank::ShowAccounts() const {
    std::cout << "-------------------- Счета --------------------" << std::endl;
    for (const auto& account : accounts) {
        std::cout << *account;
        std::cout << "------------------------------------------------" << std::endl;
    }
}

void Bank::ShowCustomers() const {
    std::cout << "------------------ Клиенты -------------------" << std::endl;
    for (const auto& customer : customers) {
        customer->DisplayInfo();
    }
    std::cout << "------------------------------------------------" << std::endl;
}


void Bank::Transfer(std::shared_ptr<Account> from, std::shared_ptr<Account> to, double amount) {
    if (from && to) {
        if (from->GetBalance() >= amount) {
            from->Withdraw(amount);
            to->Deposit(amount);
            std::cout << "Перевод: " << std::fixed << std::setprecision(2) << amount << " выполнен." << std::endl;
        }
        else {
            std::cout << "Недостаточно средств для перевода!" << std::endl;
        }
    }
    else {
        std::cout << "Некорректные счета для перевода!" << std::endl;
    }
}

void Bank::ShowAccountInfo(int index) const {
    std::shared_ptr<Account> account = GetAccount(index);
    if (account) {
        std::cout << "------- Информация об аккаунте #" << index << " -------" << std::endl;
        account->DisplayInfo();
        std::cout << "------------------------------------------------" << std::endl;
    }
    else {
        std::cout << "Аккаунт не найден!" << std::endl;
    }
}

void Bank::DepositToAccount(int index, double amount) {
    std::shared_ptr<Account> account = GetAccount(index);
    if (account) {
        account->Deposit(amount);
    }
    else {
        std::cout << "Аккаунт не найден!" << std::endl;
    }
}

void Bank::WithdrawFromAccount(int index, double amount) {
    std::shared_ptr<Account> account = GetAccount(index);
    if (account) {
        account->Withdraw(amount);
    }
    else {
        std::cout << "Аккаунт не найден!" << std::endl;
    }
}

void Bank::ApplyInterestToSavings() {
    std::cout << "--- Начисление процентов на сберегательные счета ---" << std::endl;
    for (const auto& account : accounts) {
        if (std::dynamic_pointer_cast<SavingsAccount>(account)) {
            std::dynamic_pointer_cast<SavingsAccount>(account)->ApplyInterest();
        }
    }
}

void Bank::UpdateOverdraftLimit(int index, double newLimit) {
    std::shared_ptr<CheckingAccount> account = std::dynamic_pointer_cast<CheckingAccount>(GetAccount(index));
    if (account) {
        account->SetOverdraftLimit(newLimit);
    }
    else {
        std::cout << "Аккаунт не найден или не является расчетным!" << std::endl;
    }
}

void Bank::Transfer(int fromIndex, int toIndex, double amount) {
    std::shared_ptr<Account> fromAccount = GetAccount(fromIndex);
    std::shared_ptr<Account> toAccount = GetAccount(toIndex);

    if (fromAccount && toAccount) {
        if (fromAccount->GetBalance() >= amount) {
            fromAccount->Withdraw(amount);
            toAccount->Deposit(amount);
            std::cout << "Перевод: " << std::fixed << std::setprecision(2) << amount << " выполнен со счета #"
                << fromIndex << " на счет #" << toIndex << std::endl;
        }
        else {
            std::cout << "Недостаточно средств для перевода!" << std::endl;
        }
    }
    else {
        std::cout << "Некорректные счета для перевода!" << std::endl;
    }
}


void Bank::LoadData() {
    std::ifstream customersFile(CUSTOMERS_FILE);
    if (customersFile.is_open()) {
        std::string line;
        while (std::getline(customersFile, line)) {
            std::stringstream ss(line);
            std::string name, id;
            std::getline(ss, name, ',');
            std::getline(ss, id, ',');
            AddCustomer(name, id);
        }
        customersFile.close();
    }

    std::ifstream accountsFile(ACCOUNTS_FILE);
    if (accountsFile.is_open()) {
        std::string line;
        while (std::getline(accountsFile, line)) {
            std::stringstream ss(line);
            std::string typeStr;
            double balance;
            std::string extraValueStr; // Для процентной ставки или лимита

            std::getline(ss, typeStr, ',');
            ss >> balance;
            if (ss.peek() == ',') ss.ignore();
            std::getline(ss, extraValueStr, ',');



            if (typeStr == "1") {
                double interestRate = std::stod(extraValueStr);
                AddAccount(std::make_shared<SavingsAccount>(balance, interestRate));
            }
            else if (typeStr == "2") {
                double overdraftLimit = std::stod(extraValueStr);
                AddAccount(std::make_shared<CheckingAccount>(balance, overdraftLimit));
            }
            else if (typeStr == "3") {
                AddAccount(std::make_shared<BusinessAccount>(balance));
            }
        }
        accountsFile.close();
    }
}

void Bank::SaveData() const {
    std::ofstream customersFile(CUSTOMERS_FILE);
    if (customersFile.is_open()) {
        for (const auto& customer : customers) {
            customersFile << customer->GetName() << "," << customer->GetId() << std::endl;
        }
        customersFile.close();
    }

    std::ofstream accountsFile(ACCOUNTS_FILE);
    if (accountsFile.is_open()) {
        for (const auto& account : accounts) {
            if (auto savings = std::dynamic_pointer_cast<SavingsAccount>(account)) {
                accountsFile << "1," << std::fixed << std::setprecision(2) << savings->GetBalance() << "," << std::fixed << std::setprecision(2) << savings->GetInterestRate() << std::endl;
            }
            else if (auto checking = std::dynamic_pointer_cast<CheckingAccount>(account)) {
                accountsFile << "2," << std::fixed << std::setprecision(2) << checking->GetBalance() << "," << std::fixed << std::setprecision(2) << checking->GetOverdraftLimit() << std::endl;
            }
            else if (auto business = std::dynamic_pointer_cast<BusinessAccount>(account)) {
                accountsFile << "3," << std::fixed << std::setprecision(2) << business->GetBalance() << "," << std::endl;
            }
        }
        accountsFile.close();
    }
}

bool isValidId(const std::string& id) {
    return id.length() == 9 && std::all_of(id.begin(), id.end(), ::isdigit);
}
