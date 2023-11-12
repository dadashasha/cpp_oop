#include "SoundProcessor.h"
#include "OperationReader.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {//проверка на то, подан ли файл конфигурации(хотя бы он)
        std::cout << "bad input" << std::endl;
        return 1;
    }

    const std::string& configFileName = argv[1];
    std::ifstream configFile(configFileName);

    if (!configFile.is_open()) {//проверка на открытие файла конфигурации
        std::cerr << "Error: Unable to open config file." << std::endl;
        return 1;
    }

    OperationReader operationReader;
    std::vector<Operation> operations = operationReader.createOperationList(configFile);

    //вывод списка операций для отладки(можно удалить)
    for (const Operation& operation : operations) {
        std::cout << "Action: " << operation.action << std::endl;
        std::cout << "outputFileName: " << operation.outputFileName << std::endl;
        std::cout << "Input File Name: " << operation.inputFileName << std::endl;
        std::cout << "Input File Name 2: " << operation.inputFileName2 << std::endl;
        std::cout << "Start Second: " << operation.startSec << std::endl;
        std::cout << "End Second: " << operation.endSec << std::endl;
        std::cout << std::endl;
    }

    SoundProcessor soundProcessor;
    for (Operation exampleOperation : operations) {
        if (exampleOperation.action == "mute") {
            soundProcessor.mute(exampleOperation);
        }
        else if (exampleOperation.action == "mix") {
            soundProcessor.mix(exampleOperation);
        }
    }

    return 0;
}
