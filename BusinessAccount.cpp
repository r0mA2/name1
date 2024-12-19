#include "BusinessAccount.h"
#include <iostream>
#include <iomanip>

BusinessAccount::BusinessAccount(double initialBalance) : Account(initialBalance) {}

void BusinessAccount::Withdraw(double amount) {
    if (amount <= GetBalance()) {
        balance -= amount;
        std::cout << "Снятие: " << std::fixed << std::setprecision(2) << amount << " выполнено." << std::endl;
    }
    else {
        std::cout << "Недостаточно средств для снятия!" << std::endl;
    }
}

void BusinessAccount::DisplayInfo() const {
    std::cout << "Бизнес-счет, баланс: " << std::fixed << std::setprecision(2) << balance << std::endl;
}
