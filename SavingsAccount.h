#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(double initialBalance, double interestRate = 0.01);
    void Withdraw(double amount) override;
    void ApplyInterest();
    void DisplayInfo() const override;
    double GetInterestRate() const;
};

#endif
