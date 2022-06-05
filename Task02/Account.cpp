/**
 * @author: Yonatan Vega
 * @id: 318233616
 */
#include "Account.h"

Account::Account() {
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    m_persons = nullptr;
    m_totalPersons = 0;
    m_accountNumber = 0;
    m_balance = 0;
}

Account::Account(const Account &other) {
    m_numberOfTransaction = other.m_numberOfTransaction;
    m_totalPersons = other.GetTotalPersons();
    m_accountNumber = other.GetAccountNumber();
    m_balance = other.GetBalance();
    m_transactionList = new Transaction*;
    m_persons = new Person*;
    for (int i = 0; i < m_numberOfTransaction; i++) {
        m_transactionList[i] = new Transaction(*other.m_transactionList[i]);
    }
    for (int i = 0; i < m_totalPersons; i++) {
        m_persons[i] = new Person(*other.GetPersons()[i]);
    }
}

Account::Account(const Person &person, double balance) {
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    m_persons = new Person*;
    m_persons[0] = new Person(person);
    m_totalPersons = 1;
    m_accountNumber = person.GetId();
    m_balance = balance;
}

Account::Account(Person **persons, int count, double balance) {
    m_persons = persons;
    m_totalPersons = count;
    m_balance = balance;
    m_transactionList = nullptr;
    m_numberOfTransaction = 0;
    m_accountNumber = 0;
}

Account::~Account() {
    this->clearTransactions();
    this->clearPersons();
}

// Getters, Setters
void Account::SetPersons(Person **persons, int count) {
    m_persons = persons;
    m_totalPersons = count;
}

void Account::SetAccountNumber(int number) {
    m_accountNumber = number;
}

void Account::SetBalance(double balance) {
    m_balance = balance;
}

void Account::SetTransactions(Transaction **newTransaction, int count) {
    m_transactionList = newTransaction;
    m_numberOfTransaction = count;
}

Transaction** Account::GetTransactions() {
    return m_transactionList;
}

int Account::GetNumOfTransactions() {
    return m_numberOfTransaction;
}

Person** Account::GetPersons() const {
    return m_persons;
}

int Account::GetTotalPersons() const {
    return m_totalPersons;
}

int Account::GetAccountNumber() const {
    return m_accountNumber;
}

double Account::GetBalance() const {
    return m_balance;
}

// Public Functions
void Account::Withdraw(double amount, const char *date) {
    if (m_transactionList == nullptr)
        m_transactionList = new Transaction*;
    m_transactionList[m_numberOfTransaction++] = new Transaction(this, this, amount, date);
    m_balance -= amount;
}

void Account::Deposit(double amount, const char *date) {
    if (m_transactionList == nullptr)
        m_transactionList = new Transaction*;
    m_transactionList[m_numberOfTransaction++] = new Transaction(this, this, amount, date);
    m_balance += amount;
}

void Account::AddPerson(const Person &newPerson, double amount) {
    bool exists = false;
    for (int i = 0; i < m_totalPersons; i++) {
        if (m_persons[i]->GetId() == newPerson.GetId()) {
            exists = true;
            break;
        }
    }
    if (exists) return;
    if (m_persons == nullptr) {
        m_persons = new Person*;
    }
    m_persons[m_totalPersons++] = new Person(newPerson);
    m_balance += amount;
    // Only update the account number when a person is being added to the account
    // If a person is removed from the account, it's still the same account
    if (m_accountNumber == m_persons[0]->GetId()) {
        int newAccountNumber = m_accountNumber;
        newAccountNumber = (newAccountNumber + newPerson.GetId())
                * (1 + newAccountNumber + newPerson.GetId())
                + newPerson.GetId();
        newAccountNumber /= 2;
        this->SetAccountNumber(newAccountNumber);
    }
}

void Account::DeletePerson(const Person &oldPerson) {
    if (m_persons == nullptr) return;
    bool exists = false;
    int i = 0;
    for (; i < m_totalPersons; i++) {
        if (m_persons[i]->GetId() == oldPerson.GetId()) {
            exists = true;
            break;
        }
    }
    if (!exists) return;
    delete m_persons[i];
    if (--m_totalPersons == 0) {
        delete [] m_persons;
        m_persons = nullptr;
        return;
    }
    if (i != m_totalPersons) { // Not the last item in the array
        // Move the following items into the position of the indx we removed
        for (;i < m_totalPersons; i++) {
            m_persons[i] = m_persons[i + 1];
        }
        // Remove the last item in the list, it was moved by the loop above
        delete m_persons[m_totalPersons];
        // Set the last item to the nullptr
        m_persons[m_totalPersons] = nullptr;
    }
}

void Account::AddTransaction(const Transaction &newTransaction) {
    // Source is the payer
    // Destination is the receiver
    // Withdraw
    if (newTransaction.GetSource()->GetAccountNumber() == newTransaction.GetDes()->GetAccountNumber()) {
        if (newTransaction.GetAmount() > 0) {
            newTransaction.GetSource()->Withdraw(newTransaction.GetAmount(), newTransaction.GetDate());
        } else {
            newTransaction.GetSource()->Deposit(newTransaction.GetAmount(), newTransaction.GetDate());
        }
        return;
    }
    Account* source = newTransaction.GetSource();
    Account* dest = newTransaction.GetDes();
    // Add the transaction to the Source account
    source->m_transactionList[source->m_numberOfTransaction++] = new Transaction(newTransaction);
    source->SetBalance(source->GetBalance() - newTransaction.GetAmount());
    dest->m_transactionList[dest->m_numberOfTransaction++] = new Transaction(newTransaction);
    dest->SetBalance(dest->GetBalance() + newTransaction.GetAmount());
}

// Private functions
void Account::clearPersons() {
    if (m_persons == nullptr) return;
    for (int i = 0; i < m_totalPersons ; i++) {
        delete m_persons[i];
    }
    delete [] m_persons;
    m_persons = nullptr;
}

void Account::clearTransactions() {
    if (m_transactionList == nullptr) return;
    for (; m_numberOfTransaction > 0; --m_numberOfTransaction) {
        delete m_transactionList[m_numberOfTransaction];
    }
    delete[] m_transactionList;
    m_transactionList = nullptr;
}