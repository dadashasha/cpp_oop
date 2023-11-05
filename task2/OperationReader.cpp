#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "OperationReader.h"

std::vector<Operation> OperationReader::createOperationList(std::ifstream& configFile) {

    std::string line;
    std::vector<Operation> operations;

    while (std::getline(configFile, line)) {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, part, ' ')) {
            parts.push_back(part);
        }

        if (parts.size() < 4) {
            std::cerr << "Error: Invalid line in config file." << std::endl;
            continue;
        }

        Operation operation = {};
        operation.action = parts[0];
        operation.outputFileName = parts[1];
        operation.inputFileName = parts[2];

        if (operation.action == "mute") {
            if (parts.size() < 5) {
                std::cerr << "Error: Insufficient arguments for mute operation." << std::endl;
                continue;
            }
            operation.startSec = std::stoi(parts[3]);
            operation.endSec = std::stoi(parts[4]);

        } else if (operation.action == "mix") {
            if (parts.size() < 5) {
                std::cerr << "Error: Insufficient arguments for mix operation." << std::endl;
                continue;
            }
            operation.inputFileName2 = parts[3];
            operation.startSec = std::stoi(parts[4]);
        }

        operations.push_back(operation);
    }
    return operations;
}