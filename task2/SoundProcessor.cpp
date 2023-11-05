#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct WAVHeader {
    char chunkID[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};

void mute(const std::string& inputFileName, const std::string& outputFileName, int startSec, int endSec) {
    std::ifstream input(inputFileName, std::ios::binary);
    std::ofstream output(outputFileName, std::ios::binary);

    if (!input.is_open()) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return;
    }
    if (!output.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    WAVHeader header = {};

    input.read(reinterpret_cast<char*>(&header), sizeof(header));
    output.write(reinterpret_cast<char*>(&header), sizeof(header));

    int16_t sample = 0;

    // Вычислите общее количество семплов между startSec и endSec
    int32_t sampleRate = header.sampleRate;
    int32_t bytesPerSample = header.bitsPerSample / 8;
    int32_t samplesToSkip = startSec * sampleRate;
    int32_t samplesToMute = (endSec - startSec) * sampleRate;

    // Пропустить семплы до startSec
    for (int32_t i = 0; i < samplesToSkip; ++i) {
        input.read(reinterpret_cast<char*>(&sample), bytesPerSample);
        output.write(reinterpret_cast<char*>(&sample), bytesPerSample);
    }

    // Заглушить семплы в интервале [startSec, endSec)
    for (int32_t i = 0; i < samplesToMute; ++i) {
        sample = 0;
        output.write(reinterpret_cast<char*>(&sample), bytesPerSample);
    }

    // Скопировать оставшиеся семплы
    while (input.read(reinterpret_cast<char*>(&sample), bytesPerSample)) {
        output.write(reinterpret_cast<char*>(&sample), bytesPerSample);
    }

    std::cout << "Mute operation completed." << std::endl;
}

void mix(const std::string& inputFileName1, const std::string& inputFileName2, const std::string& outputFileName, int startSec) {
    std::ifstream input1(inputFileName1, std::ios::binary);
    std::ifstream input2(inputFileName2, std::ios::binary);
    std::ofstream output(outputFileName, std::ios::binary);

    if (!input1.is_open()) {
        std::cerr << "Error: Unable to open input file 1." << std::endl;
        return;
    }
    if (!input2.is_open()) {
        std::cerr << "Error: Unable to open input file 2." << std::endl;
        return;
    }
    if (!output.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    WAVHeader header1 = {};
    WAVHeader header2 = {};

    input1.read(reinterpret_cast<char*>(&header1), sizeof(header1));
    input2.read(reinterpret_cast<char*>(&header2), sizeof(header2));

    if (header1.sampleRate != header2.sampleRate || header1.numChannels != header2.numChannels || header1.bitsPerSample != header2.bitsPerSample) {
        std::cerr << "Error: Audio parameters do not match." << std::endl;
        return;
    }

    output.write(reinterpret_cast<char*>(&header1), sizeof(header1));

    int16_t sample1 = 0;
    int16_t sample2 = 0;
    int16_t mixSample = 0;

    int32_t sampleSize = header1.numChannels * (header1.bitsPerSample / 8);
    int32_t samplesToSkip = startSec * header1.sampleRate * sampleSize;

    // Пропустить начальные семплы
    input1.seekg(samplesToSkip, std::ios::cur);
    input2.seekg(samplesToSkip, std::ios::cur);

    while (input1.read(reinterpret_cast<char*>(&sample1), sizeof(sample1)) &&
        input2.read(reinterpret_cast<char*>(&sample2), sizeof(sample2))) {
        mixSample = (sample1 + sample2) / 2;
        output.write(reinterpret_cast<char*>(&mixSample), sizeof(mixSample));
    }

    std::cout << "Mix operation completed." << std::endl;
}

int main(int argc, char* argv[]) {  
    if (argc < 3) {
        std::cout << "bad input" << std::endl;
        return 1; 
    }

    const std::string& configFileName = argv[1];
    const std::string& outputFileName = argv[2];

    std::ifstream configFile(configFileName);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (!configFile.is_open()) {
        std::cerr << "Error: Unable to open config file." << std::endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, part, ' ')) {
            parts.push_back(part);
        }

        if (parts.size() < 3) {
            std::cerr << "Error: Invalid line in config file." << std::endl;
            continue;
        }

        const std::string& action = parts[0];
        const std::string& inputFileName = parts[1];

        if (action == "mute") {
            if (parts.size() < 4) {
                std::cerr << "Error: Insufficient arguments for mute operation." << std::endl;
                continue;
            }
            int startSec = std::stoi(parts[2]);
            int endSec = std::stoi(parts[3]);
            mute(inputFileName.c_str(), outputFileName, startSec, endSec);
        }
        else if (action == "mix") {
            if (parts.size() < 4) {
                std::cerr << "Error: Insufficient arguments for mix operation." << std::endl;
                continue;
            }
            const std::string& inputFileName2 = parts[2];
            int startSec = std::stoi(parts[3]);
            mix(inputFileName.c_str(), inputFileName2.c_str(), outputFileName, startSec);
        }
    }

    return 0;
}
