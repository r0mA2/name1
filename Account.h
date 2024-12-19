
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account {
protected:
    double balance;
public:
    Account(double initialBalance);
    virtual void Deposit(double amount);
    virtual void Withdraw(double amount) = 0;
    double GetBalance() const;
    virtual void DisplayInfo() const = 0;
    virtual ~Account() = default;

    friend std::ostream& operator<<(std::ostream& os, const Account& account);
};

#endif
