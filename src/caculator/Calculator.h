#ifndef CACULATOR_H
#define CACULATOR_H

#include<string>
#include<iostream>
#include<tuple>
#include"../message/Message.h"

class Calculator{
public:
    virtual std::string calculate(Message& message) = 0;

    
};

#endif