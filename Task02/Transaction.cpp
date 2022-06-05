/**
 * @author: Yonatan Vega
 * @id: 318233616
 */
#include "Transaction.h"

/**
 * Takes in two accounts, a source and a destination, the amount of the transaction and its date
 * Initiates a transaction based on the details given
 * Both the destination and source accounts are not duplicated
 * @param s
 * @param d
 * @param amount
 * @param date
 */
Transaction::Transaction(Account *s, Account *d, double amount, const char *date) {
    m_source = s;
    m_destination = d;
    m_amount = amount;
    m_date = new char[strlen(date) + 1];
    strcpy(m_date, date);
}

/**
 * Given a reference to another transaction, create a new transaction with the same details
 * @param other
 */
Transaction::Transaction(const Transaction &other) {
    m_source = other.m_source;
    m_destination = other.m_destination;
    m_amount = other.m_amount;
    m_date = new char[strlen(other.m_date) + 1];
    strcpy(m_date, other.m_date);
}

/**
 * Update the source account for the transaction
 * @param src
 */
void Transaction::SetSource(Account *src) {
    m_source = src;
}

/**
 * Update the destination account for the transaction
 * @param dst
 */
void Transaction::SetDes(Account *dst) {
    m_destination = dst;
}

/**
 * Update the amount of the transaction
 * @param amount
 */
void Transaction::SetAmount(double amount) {
    m_amount = amount;
}

/**
 * Update the Date of the transaction
 * @param date
 */
void Transaction::SetDate(const char *date) {
    m_date = new char[strlen(date) + 1];
    strcpy(m_date, date);
}

// Getters

/**
 * Get a pointer to the source Account of the transaction
 * @return
 */
Account* Transaction::GetSource() const {
    return m_source;
}

/**
 * Get a pointer to the destination Account of the transaction
 * @return
 */
Account* Transaction::GetDes() const {
    return m_destination;
}

/**
 * Get the amount of the transaction
 * @return
 */
double Transaction::GetAmount() const {
    return m_amount;
}

/**
 * Get the date of the transaction
 * @return
 */
char* Transaction::GetDate() const {
    return m_date;
}