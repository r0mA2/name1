#include "Account.h"
#include <iomanip>

Account::Account(double initialBalance) : balance(initialBalance) {}

void Account::Deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Депозит: " << std::fixed << std::setprecision(2) << amount << " выполнен." << std::endl;
    }
    else {
        std::cout << "Сумма депозита должна быть положительной." << std::endl;
    }
}

double Account::GetBalance() const { return balance; }

std::ostream& operator<<(std::ostream& os, const Account& account) {
    account.DisplayInfo();
    return os;
}
