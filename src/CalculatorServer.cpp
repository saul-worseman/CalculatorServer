// #include<iostream>
// #include"caculator/CalculatorBasic.h"
// int main(){
//     Calculator* calculator = new CalculatorBasic();
//     vector<string> operators{"+"};
//     vector<int> operands{1, 2};
//     Message message(OP_BIN, operands, operators);
    
//     std::cout << calculator->calculate(message);

    
// }

#include"network/Server.h"

int main(int argc , char *argv[]){  
    Server server;
    server.start();
}  