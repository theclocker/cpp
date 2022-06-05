cmake_minimum_required(VERSION 3.21)
project(Task02)

set(CMAKE_CXX_STANDARD 11)

add_executable(
        Main
        Account.cpp Account.h
        Bank.cpp Bank.h
        MainTrain.cpp
        Person.cpp Person.h
        Transaction.cpp Transaction.h
)
