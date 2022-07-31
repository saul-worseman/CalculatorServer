#ifndef MESSAGE_H
#define MESSAGE_H

#include<vector>
#include<string>

using std::string;
using std::vector;

enum OperationKind{OP_BIN, OP_SINGLE, OP_MULT};



class Message{
public:
    Message(OperationKind operationKind, vector<int>& operands, vector<string>& operators){
        this->operationKind = operationKind;
        this->operands = operands;
        this->operators = operators;
    }

    OperationKind getOperationKind(){return operationKind;} 

    void setOperationKind(OperationKind opertionKind){this->operationKind = operationKind;}


    vector<int> getOperands(){return operands;}

    void setOperands(vector<int>& operands){this->operands = operands;}

    vector<string> getOperators(){return operators;}

    void setOperators(vector<string>& operators){this->operators = operators;}

private:
    OperationKind operationKind;
    
    vector<int> operands;

    vector<string> operators;
};

#endif