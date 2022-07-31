#include"Logger.h"


void Logger::log(string request, char* ip, int port){
    if(!os.is_open()){
        os.open(curLogFile, std::ios::out | std::ios::trunc);
    }
    if(curLogNum > maxNum){
        os.close();
        os.open(backupLogFile, std::ios::out | std::ios::trunc);
        
        swap(curLogFile, backupLogFile);
        curLogNum = 0;
    }
    char buffer[200];
    sprintf(buffer, " ip is : %s , port : %d \n",  ip, port);
    string connection(buffer);
    if(!os.is_open()){
            std::cout << "open failed\n";
        }
    os << getCurrentDateTime("now") << std::endl
              << request << " from connection " 
              << connection << std::endl;
    curLogNum++;
}

string Logger::getCurrentDateTime(string s){
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if(s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if(s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return string(buf);
};