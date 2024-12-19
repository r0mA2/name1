#include <iostream>
#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include "BusinessAccount.h"
#include <iomanip>


int main() {
    setlocale(LC_ALL, "rus");

    Bank bank;

    int choice;
    do {
        std::cout << "\n----- Меню -----" << std::endl;
        std::cout << "1. Добавить клиента" << std::endl;
        std::cout << "2. Добавить аккаунт" << std::endl;
        std::cout << "3. Показать клиентов" << std::endl;
        std::cout << "4. Показать счета" << std::endl;
        std::cout << "5. Удалить клиента" << std::endl;
        std::cout << "6. Удалить счет" << std::endl;
        std::cout << "7. Вывести общий баланс" << std::endl;
        std::cout << "8. Сортировать счета по балансу" << std::endl;
        std::cout << "9. Показать информацию об аккаунте" << std::endl;
        std::cout << "10. Внести деньги на счет" << std::endl;
        std::cout << "11. Снять деньги со счета" << std::endl;
        std::cout << "12. Начислить проценты на сберегательные счета" << std::endl;
        std::cout << "13. Обновить лимит овердрафта" << std::endl;
        std::cout << "14. Перевести деньги между счетами" << std::endl;
        std::cout << "0. Выйти и сохранить" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, id;
            std::cout << "Введите имя клиента: ";
            std::cin >> name;
            do {
                std::cout << "Введите ID клиента (ровно 9 чисел): ";
                std::cin >> id;
                if (!isValidId(id)) {
                    std::cout << "Ошибка: ID должен состоять ровно из 9 цифр!" << std::endl;
                }
            } while (!isValidId(id));
            bank.AddCustomer(name, id);
            break;
        }
        case 2: {
            double initialBalance;
            int accountType;
            std::cout << "Введите начальный баланс для аккаунта: ";
            std::cin >> initialBalance;
            while (true) {
                std::cout << "Введите тип аккаунта (1-Сберегательный, 2-Расчетный, 3-Бизнес): ";
                std::cin >> accountType;

                if (accountType >= 1 && accountType <= 3) {
                    break;
                }
                else {
                    std::cout << "Такого варианта нет, попробуйте заново." << std::endl;
                }
            }

            if (accountType == 1) {
                double interestRate;
                std::cout << "Введите процентную ставку: ";
                std::cin >> interestRate;
                bank.AddAccount(std::make_shared<SavingsAccount>(initialBalance, interestRate));
            }
            else if (accountType == 2) {
                double overdraftLimit;
                std::cout << "Введите лимит овердрафта (максимальная сумма, на которую можно уходить в минус.): ";
                std::cin >> overdraftLimit;
                bank.AddAccount(std::make_shared<CheckingAccount>(initialBalance, overdraftLimit));
            }
            else if (accountType == 3) {
                bank.AddAccount(std::make_shared<BusinessAccount>(initialBalance));
            }
            break;
        }
        case 3: {
            bank.ShowCustomers();
            break;
        }
        case 4: {
            bank.ShowAccounts();
            break;
        }
        case 5: {
            int index;
            std::cout << "Введите индекс клиента для удаления: ";
            std::cin >> index;
            bank.DeleteCustomer(index);
            break;
        }
        case 6: {
            int index;
            std::cout << "Введите индекс счета для удаления: ";
            std::cin >> index;
            bank.DeleteAccount(index);
            break;
        }
        case 7: {
            std::cout << "------------------------------------------------" << std::endl;
            std::cout << "Всего средств в банке: " << std::fixed << std::setprecision(2) << bank.CalculateTotalAssets() << std::endl;
            std::cout << "------------------------------------------------" << std::endl;
            break;
        }
        case 8: {
            bank.SortAccountsByBalance();
            break;
        }
        case 9: {
            int index;
            std::cout << "Введите индекс аккаунта для просмотра информации: ";
            std::cin >> index;
            bank.ShowAccountInfo(index);
            break;
        }
        case 10: {
            int index;
            double amount;
            std::cout << "Введите индекс аккаунта для пополнения: ";
            std::cin >> index;
            std::cout << "Введите сумму для внесения: ";
            std::cin >> amount;
            bank.DepositToAccount(index, amount);
            break;
        }
        case 11: {
            int index;
            double amount;
            std::cout << "Введите индекс аккаунта для снятия: ";
            std::cin >> index;
            std::cout << "Введите сумму для снятия: ";
            std::cin >> amount;
            bank.WithdrawFromAccount(index, amount);
            break;
        }
        case 12: {
            bank.ApplyInterestToSavings();
            break;
        }
        case 13: {
            int index;
            double newLimit;
            std::cout << "Введите индекс расчетного счета для изменения лимита овердрафта: ";
            std::cin >> index;
            std::cout << "Введите новый лимит овердрафта: ";
            std::cin >> newLimit;
            bank.UpdateOverdraftLimit(index, newLimit);
            break;
        }
        case 14: {
            int fromIndex, toIndex;
            double amount;
            std::cout << "Введите индекс счета, с которого нужно перевести деньги: ";
            std::cin >> fromIndex;
            std::cout << "Введите индекс счета, на который нужно перевести деньги: ";
            std::cin >> toIndex;
            std::cout << "Введите сумму для перевода: ";
            std::cin >> amount;
            bank.Transfer(fromIndex, toIndex, amount);
            break;
        }
        case 0: {
            std::cout << "Сохранение и выход..." << std::endl;
            bank.SaveData();
            break;
        }

        default: {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
        }
    } while (choice != 0);

    return 0;
}
