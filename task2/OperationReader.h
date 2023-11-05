#ifndef DASHA_OPERATIONREADER_H
#define DASHA_OPERATIONREADER_H

#include <string>
#include <vector>

struct Operation {
    std::string action;
    std::string outputFileName;
    std::string inputFileName;
    std::string inputFileName2;
    int startSec;
    int endSec;
};


class OperationReader {


public:
    std::vector<Operation> createOperationList(std::ifstream& configFile);
};


#endif //DASHA_OPERATIONREADER_H
