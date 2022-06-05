/**
 * @author: Yonatan Vega
 * @id: 318233616
 */
#include "Bank.h"

/**
 * Initiate a basic bank with default arguments
 */
Bank::Bank() {
    m_name = nullptr;
    m_bankCode = 0;
    m_numbeOfAccounts = 0;
    m_totalBalance = 0;
    m_account = nullptr;
}

/**
 * Initiate a bank with a name and a code
 * @param name
 * @param code
 */
Bank::Bank(const char *name, int code) {
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
    m_bankCode = code;
    m_numbeOfAccounts = 0;
    m_totalBalance = 0;
    m_account = nullptr;
}

Bank::~Bank() {
    if (m_name)
        delete m_name;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        delete m_account[i];
    }
    delete [] m_account;
}

// Setters
void Bank::SetBankName( const char* name ) {
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}

void Bank::SetAccount( Account** account, int numbeOfAccounts ) {
    m_account = account;
    m_numbeOfAccounts = numbeOfAccounts;
}

void Bank::SetTotal( double total ) {
    m_totalBalance = total;
}

void Bank::SetCode( int code ) {
    m_bankCode = code;
}

// Getters

const char* Bank::GetBankName() const {
    return m_name;
}

Account** Bank::GetAccounts() const {
    return m_account;
}

int Bank::GetNumberOfAccounts() const {
    return m_numbeOfAccounts;
}

double Bank::GetTotal() const {
    return m_totalBalance;
}

int Bank::GetCode() const {
    return m_bankCode;
}

// Public methods


void Bank::AddAccount( const Account& account ) {
    bool exists = false;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
            exists = true;
            break;
        }
    }
    if (exists) return;
    if (m_account == nullptr) m_account = new Account*;
    m_account[m_numbeOfAccounts++] = new Account(account);
    m_totalBalance += account.GetBalance();
}

void Bank::AddAccount( const Person& per, double amount ) {
    if (m_account == nullptr) m_account = new Account*;
    m_account[m_numbeOfAccounts++] = new Account(per, amount);
    m_totalBalance += amount;
}

/**
 * If the account exists in the bank, and the person exists in the account, do nothing
 * If the account exists in the bank, and the person is not in the account, add it
 * If the account does not exist in the bank, create it, add the person to it
 * @param newPerson
 * @param account
 * @param amount
 */
void Bank::AddPerson( const Person& newPerson, const Account& account, double amount ) {
    // If the bank has no accounts, initiate the account pointer array
    if (m_account == nullptr) {
        m_account = new Account*;
    } else { // If the m_account is already initiated, you can search through it
        // If you find the account at the bank, add the person to it
        for (int i = 0; i < m_numbeOfAccounts; i++) {
            if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
                // No need to test if the person exists in the account
                // this is done in the AddPerson method
                m_account[i]->AddPerson(newPerson, amount);
                // Return, we added a person, no need to extend the account pointer
                return;
            }
        }
    }
    // If you did not find the account at the bank, create one for the person and add it to it
    m_account[m_numbeOfAccounts++] = new Account(newPerson, amount);
}

/**
 * Removes an account from the bank
 * If the account does not exist at the bank, do nothing
 * If the account exists, remove it, update the totalBalance at the bank
 * If the account was the last one at the bank, clear the account array
 * @param account
 */
void Bank::DeleteAccount( const Account& account ) {
    if (m_account == nullptr) return; // No accounts exist
    int index = -1;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        if (m_account[i]->GetAccountNumber() == account.GetAccountNumber()) {
            index = i;
            break;
        }
    }
    if (index == -1) return; // Person not found
    // Reduce the bank's balance based on the account's balance
    m_totalBalance -= m_account[index]->GetBalance();
    delete m_account[index];
    m_account[index] = nullptr;
    // If the number of accounts is now 0, delete the accounts array
    if (--m_numbeOfAccounts == 0) {
        delete [] m_account;
        return;
    }
    // If the account removed is not the last one in the accounts array, move the last account to the current
    // position, as to not break the array's sequence
    if (index != m_numbeOfAccounts) {
        m_account[index] = m_account[m_numbeOfAccounts];
        delete m_account[m_numbeOfAccounts];
    }

}

/**
 * Removes the person given from all of the accounts at the bank
 * If the person removed from an account was the last person in the account remove the account and update
 * the balance at the bank
 * @param p
 */
void Bank::DeletePerson( const Person& p ) {
    if (m_account == nullptr) return;
    for (int i = 0; i < m_numbeOfAccounts; i++) {
        // Should probably remove invalid accounts here / before?
        if (m_account[i]->GetTotalPersons() > 0) {
            // Would have been nice to have a Has function
            for (int j = 0; j < m_account[i]->GetTotalPersons(); j++) {
                // Is the same person?
                if (m_account[i]->GetPersons()[j]->GetId() == p.GetId()) {
                    m_account[i]->DeletePerson(p); // Get this person out of my sight
                    if (m_account[i]->GetTotalPersons() == 0) {
                        m_totalBalance -= m_account[i]->GetBalance();
                        this->DeleteAccount(*m_account[i]);
                        // If this is not the last account in the loop
                        // Subtract from i, since the DeleteAccount method also moves the last
                        // Item in the pointer to the current position, we want to reread this position
                        // Since it now points to a different account
                        if ((i + 1) < m_numbeOfAccounts) i--;
                    }
                    break;
                }
            }
        }
    }
    // What if all the accounts were removed?
    if (m_numbeOfAccounts == 0) {
        delete [] m_account;
        m_account = nullptr;
    }
}
