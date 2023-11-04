#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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

void mute(const std::string& inputFileName, const std::string& outputFileName, int startSec, int endSec) {//вместо char* - std::string
    std::ifstream input(inputFileName, std::ios::binary);
    std::ofstream output(outputFileName, std::ios::binary);
    WAVHeader header = {};

    input.read(reinterpret_cast<char*>(&header), sizeof(header));
    output.write(reinterpret_cast<char*>(&header), sizeof(header));

    int16_t sample = 0;
    int32_t sampleCount = (header.sampleRate * (endSec - startSec));

    for (int i = 0; i < sampleCount; ++i) {
        input.read(reinterpret_cast<char*>(&sample), sizeof(sample));

        if (i >= (startSec * header.sampleRate) && i < (endSec * header.sampleRate)) {
            sample = 0;
        }

        output.write(reinterpret_cast<char*>(&sample), sizeof(sample));
    }
}

void mix(const std::string& inputFileName1, const std::string& inputFileName2, const std::string& outputFileName, int startSec) {
    std::ifstream input1(inputFileName1, std::ios::binary);
    std::ifstream input2(inputFileName2, std::ios::binary);
    std::ofstream output(outputFileName, std::ios::binary);
    WAVHeader header = {};

    input2.read(reinterpret_cast<char*>(&header), sizeof(header));
    output.write(reinterpret_cast<char*>(&header), sizeof(header));

    int16_t sample1 = 0;
    int16_t sample2 = 0;
    int16_t mixSample = 0;

    int32_t sampleCount = header.sampleRate * (header.bitsPerSample / 8) * (header.numChannels);

    int32_t samplesToSkip = startSec * sampleCount;

    input1.seekg(samplesToSkip, std::ios::beg);

    for (int i = 0; i < sampleCount; ++i) {
        input1.read(reinterpret_cast<char*>(&sample1), sizeof(sample1));
        input2.read(reinterpret_cast<char*>(&sample2), sizeof(sample2));

        mixSample = (sample1 + sample2) / 2;
        output.write(reinterpret_cast<char*>(&mixSample), sizeof(mixSample));
    }
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

    std::string line;
    while (std::getline(configFile, line)) {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, part, ' ')) {
            parts.push_back(part);
        }

        if (parts.size() < 3) {
            continue;
        }

        const std::string& action = parts[0];
        const std::string& inputFileName = parts[1];

        if (action == "mute") {
            int startSec = std::stoi(parts[2]);
            int endSec = std::stoi(parts[3]);
            mute(inputFileName.c_str(), outputFileName, startSec, endSec);
        }
        else if (action == "mix") {
            int startSec = std::stoi(parts[2]);
            const std::string& inputFileName2 = parts[3];
            mix(inputFileName.c_str(), inputFileName2.c_str(), outputFileName, startSec);
        }
    }

    return 0;
}
