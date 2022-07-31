#include"ServerUtils.h"
#include"../caculator/CalculatorBasic.h"
#include<regex>

Message ServerUtils::parseRequest(string s){
    std::regex opeartorPattern("[+\\-*/]");
    std::smatch opeartorMatch;
    std::regex_search(s, opeartorMatch, opeartorPattern);
    vector<string> operators;

    for(auto v: opeartorMatch){
        operators.push_back(v);
    }

    string delimiter = operators[0];
    vector<int> operands;
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        operands.push_back(std::stoi(token.c_str()));
        s.erase(0, pos + delimiter.length());
    }
    operands.push_back(std::stoi(s.c_str()));


    return Message(OP_BIN, operands, operators);
};

string ServerUtils::processMessage(Message& message){
    CalculatorBasic calculatorBasic;
    return calculatorBasic.calculate(message);
}
