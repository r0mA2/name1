#include "CheckingAccount.h"
#include <iostream>
#include <iomanip>

CheckingAccount::CheckingAccount(double initialBalance, double overdraftLimit)
    : Account(initialBalance), overdraftLimit(overdraftLimit) {
}

void CheckingAccount::Withdraw(double amount) {
    if (balance + overdraftLimit >= amount) {
        balance -= amount;
        if (balance < 0) {
            std::cout << "Вы вышли в минус на " << std::fixed << std::setprecision(2) << -balance << "!" << std::endl;
        }
        else {
            std::cout << "Снятие: " << std::fixed << std::setprecision(2) << amount << " выполнено." << std::endl;
        }
    }
    else {
        std::cout << "Недостаточно средств для снятия!" << std::endl;
    }
}

void CheckingAccount::DisplayInfo() const {
    std::cout << "Расчетный счет, баланс: " << std::fixed << std::setprecision(2) << balance
        << ", Лимит овердрафта: " << std::fixed << std::setprecision(2) << overdraftLimit << std::endl;
}

void CheckingAccount::SetOverdraftLimit(double newLimit) {
    overdraftLimit = newLimit;
    std::cout << "Лимит овердрафта обновлен до: " << std::fixed << std::setprecision(2) << newLimit << std::endl;
}

double CheckingAccount::GetOverdraftLimit() const {
    return overdraftLimit;
}
