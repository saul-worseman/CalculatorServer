#ifndef CALCULATORBASIC_H
#define CALCULATORBASIC_H

#include"Calculator.h"

class CalculatorBasic : public Calculator{
public:

    std::string calculate(Message& message) override;

private:

    std::tuple<bool, int> add(int lhs, int rhs);

    std::tuple<bool, int> minus(int lhs, int rhs);

    std::tuple<bool, int> mult(int lhs, int rhs);

    std::tuple<bool, int> divide(int lhs, int rhs);
};

#endif