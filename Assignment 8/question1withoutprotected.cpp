/*
Shivam Walia
*/

#include <iostream>
#include <iomanip>

using namespace std;

// Main Class
class BankProduct
{
public:
    BankProduct(float initalBalance, string newAccountName);
    void setBalance(float newBalance);
    float getBalance();
    string getAccountName();

private:
    float balance;
    string accountName;
};

BankProduct::BankProduct(float newInitalBalance, string newAccountName)
{
    balance = newInitalBalance;
    accountName = newAccountName;
};

void BankProduct::setBalance(float newBalance)
{
    balance = newBalance;
}

float BankProduct::getBalance()
{
    return balance;
}

string BankProduct::getAccountName()
{
    return accountName;
}

// Loan
class BankLoan : public BankProduct
{
private:
    float loanRate;

public:
    BankLoan(float initalBalance, string newAccountName, float newloanRate);
    float getAnnualInterest();
    void makePayment(float payment);
};

BankLoan::BankLoan(float initalBalance, string newAccountName, float newloanRate) : BankProduct(initalBalance, newAccountName)
{
    loanRate = newloanRate;
}

float BankLoan ::getAnnualInterest()
{
    return (loanRate / 100) * getBalance();
}

void BankLoan ::makePayment(float payment)
{
    setBalance(getBalance() - payment);
    cout << "Payment of $" << payment << " made from " << getAccountName() << endl;
}

// Bank Account
class BankAccount : public BankProduct
{
private:
    float withdrawalCharge;

public:
    BankAccount(float initalBalance, string newAccountName, float newWithdrawalCharge);
    void withdrawMoney(float withdrawAmount);
    void depositMoney(float depositAmount);
};
BankAccount::BankAccount(float initalBalance, string newAccountName, float newWithdrawalCharge) : BankProduct(initalBalance, newAccountName)
{
    withdrawalCharge = newWithdrawalCharge;
}
void BankAccount ::withdrawMoney(float withdrawAmount)
{
    setBalance(getBalance() - (withdrawAmount + withdrawalCharge));
    cout << "Withdrawal of $" << withdrawAmount << " made from " << getAccountName() << endl;
}
void BankAccount ::depositMoney(float depositAmount)
{
    setBalance(getBalance() + depositAmount);
    cout << "Deposit of $" << depositAmount << " made from " << getAccountName() << endl;
}

// Checking Account
class CheckingAccount : public BankAccount
{
public:
    CheckingAccount(float initialBalance, string accountName);
};

CheckingAccount::CheckingAccount(float initialBalance, string accountName) : BankAccount(initialBalance, accountName, 0)
{
}

// Savings Account
class SavingsAccount : public BankAccount
{
private:
    float savingInterestRate;

public:
    SavingsAccount(float initialBalance, string accountName, float interestRate);
    void addInterest();
};
SavingsAccount::SavingsAccount(float initialBalance, string accountName, float interestRate) : BankAccount(initialBalance, accountName, 100)
{
    savingInterestRate = interestRate;
}
void SavingsAccount::addInterest()
{
    setBalance(getBalance() * (1 + (savingInterestRate / 100)));
}

// Functions
void printFunction(BankLoan *loan, CheckingAccount *checking, SavingsAccount *savings)
{
    cout << loan->getAccountName() << " balance is $" << loan->getBalance() << endl;
    cout << checking->getAccountName() << " balance is $" << checking->getBalance() << endl;
    cout << savings->getAccountName() << " balance is $" << savings->getBalance() << endl;
}

void payInterest(BankLoan *loan, CheckingAccount *checking)
{
    float interest = loan->getAnnualInterest();
    if (interest > checking->getBalance())
    {
        cout << "Insufficient funds in checking account to pay loan interest." << endl;
        return;
    }
    checking->withdrawMoney(interest);
}

void savingsInterest(SavingsAccount *savings)
{
    savings->addInterest();
}

void depositSalary(CheckingAccount *checking, float salary)
{
    checking->depositMoney(salary);
}

void payLoan(BankLoan *loan, CheckingAccount *checking, float payment)
{
    if (payment > loan->getBalance())
    {
        cout << "Payment excees loan balance, paying off completely." << endl;
        payment = loan->getBalance();
    }
    checking->withdrawMoney(payment);
    loan->makePayment(payment);
}

void addSavings(CheckingAccount *checking, SavingsAccount *savings, float addSavings)
{
    if (addSavings > checking->getBalance())
    {
        cout << "Amount being moved excees checking balance, moving all the money" << endl;
        addSavings = checking->getBalance();
    }
    checking->withdrawMoney(addSavings);
    savings->depositMoney(addSavings);
}

// main class
int main()
{
    BankLoan *loan = new BankLoan(20000, "Loan Account", 6);
    CheckingAccount *checking = new CheckingAccount(10000, "Checking Account");
    SavingsAccount *savings = new SavingsAccount(20000, "Saving Account", 5);
    cout << fixed << setprecision(2);
    savingsInterest(savings);

    payInterest(loan, checking);

    depositSalary(checking, 30000);

    payLoan(loan, checking, 10000);

    addSavings(checking, savings, 5000);

    printFunction(loan, checking, savings);
}
/*
OUTPUT
Withdrawal of $1200.00 made from Checking Account
Deposit of $30000.00 made from Checking Account
Withdrawal of $10000.00 made from Checking Account
Payment of $10000.00 made from Loan Account
Withdrawal of $5000.00 made from Checking Account
Deposit of $5000.00 made from Saving Account
Loan Account balance is $10000.00
Checking Account balance is $23800.00
Saving Account balance is $26000.00
*/