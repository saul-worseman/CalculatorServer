#ifndef LOGGER_H
#define LOGGER_H
#include<string>
#include<iostream>
#include<fstream>
using std::string;

class Logger{
public:

    Logger(){
        curLogFile = "log1.txt";
        backupLogFile = "log2.txt";
        curLogNum = 0;
    }

    //every time u switch another file to log, wipe out it, and set curLogFile to Backup
    void log(string request, char* ip, int port);

    string getCurrentDateTime(string s);

    


private:
    std::ofstream os;

    string curLogFile;

    string backupLogFile;

    int curLogNum;

    const int maxNum = 2;
};

#endif