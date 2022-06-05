#include "Person.h"

Person::Person() {
    m_id = 0;
    m_name = nullptr;
}

Person::Person(const Person &other): m_id(other.m_id) {
    m_name = new char[strlen(other.m_name) + 1];
    strcpy(m_name, other.m_name);
}

Person::Person(const char *name, int id): m_id(id) {
    m_name = new char[strlen(name) + 1];
    strcpy(m_name, name);
}

Person::~Person() {
    if (m_name) {
        delete m_name;
    }
}

// Setters

void Person::SetId(int newId) {
    m_id = newId;
}

void Person::SetName(const char *newName) {
    m_name = new char[strlen(newName) + 1];
    strcpy(m_name, newName);
}

// Getters

int Person::GetId() const {
    return m_id;
}

char* Person::GetName() const {
    return m_name;
}