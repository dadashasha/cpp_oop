#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
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

        if (parts[0] != "mute" && parts[0] != "mix") {
            std::cout << "Error: Ignoring incorrect configuration file contents." << std::endl;
            continue;
        }
        operation.action = parts[0];
        operation.outputFileName = parts[1];
        operation.inputFileName = parts[2];

        if (operation.action == "mute") {
            if (parts.size() < 5) {
                std::cerr << "Error: Insufficient arguments for mute operation." << std::endl;
                continue;
            }

            if (!parts[3].empty() && std::all_of(parts[3].begin(), parts[3].end(), ::isdigit)) {
                operation.startSec = std::stoi(parts[3]);
            }
            else {
                std::cerr << "Error: Invalid startSec value." << std::endl;
                continue;
            }
            if (!parts[4].empty() && std::all_of(parts[4].begin(), parts[4].end(), ::isdigit)) {
                operation.endSec = std::stoi(parts[4]);
            }
            else {
                std::cerr << "Error: Invalid endSec value." << std::endl;
                continue;
            }
        }
        else if (operation.action == "mix") {
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
