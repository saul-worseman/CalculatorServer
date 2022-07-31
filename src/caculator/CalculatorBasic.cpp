#include"CalculatorBasic.h"
#include<limits.h>


using std::string;
using std::vector;



//it may overflow or underflow, I take add as an example and skip others
//the tuple will elaborate whether the answer is right
//if not, it will return a message
std::string CalculatorBasic::calculate(Message& message){
    if(message.getOperationKind() == OP_BIN){
        vector<int> operands = message.getOperands();
        vector<string> operators = message.getOperators();
        std::tuple<bool, int> res;
        int lhs = operands[0];
        int rhs = operands[1];
        bool correctness = true;
        int answer = 0;


        if(operators[0] == "+"){
            std::tie(correctness, answer) = add(lhs, rhs);
        }
        else if(operators[0] == "-"){
            std::tie(correctness, answer) = minus(lhs, rhs);
        }
        else if(operators[0] == "*"){
            std::tie(correctness, answer) = mult(lhs, rhs);
        }
        else if(operators[0] == "/"){
            std::tie(correctness, answer) = divide(lhs, rhs);
        }


        if(correctness == false){
            return "the answer may overflow or underflow\nor the divisor may be 0 \n";
        }
        else{
            return std::to_string(answer);
        }
    }
    else{
        return "Not implemented\n";
    }
}

std::tuple<bool, int> CalculatorBasic::add(int lhs, int rhs){
    bool correctness = true;
    if (rhs > 0 && lhs > INT_MAX - rhs) // `a + x` would overflow
        correctness = false;
    if (rhs < 0 && lhs < INT_MIN - rhs) // `a + x` would underflow
        correctness = false;

    return std::make_tuple(correctness, lhs + rhs);
}

std::tuple<bool, int> CalculatorBasic::minus(int lhs, int rhs){
    return std::make_tuple(true, lhs - rhs);
}

std::tuple<bool, int> CalculatorBasic::mult(int lhs, int rhs){
    return std::make_tuple(true, lhs * rhs);
}

std::tuple<bool, int> CalculatorBasic::divide(int lhs, int rhs){
    if(rhs == 0){
        return std::make_tuple(false, 0);
    }
    else{
        return std::make_tuple(true, lhs / rhs);
    }
}
