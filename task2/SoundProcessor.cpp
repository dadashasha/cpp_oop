#include "SoundProcessor.h"

void SoundProcessor::mute(Operation& operation) {
    {

        std::ifstream input(operation.inputFileName.c_str(), std::ios::binary);
        std::ofstream output(operation.outputFileName, std::ios::binary);

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
        int32_t samplesToSkip = operation.startSec * sampleRate;
        int32_t samplesToMute = (operation.endSec - operation.startSec) * sampleRate;

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
}


void SoundProcessor::mix(Operation& operation) {

    std::ifstream input1(operation.inputFileName.c_str(), std::ios::binary);
    std::ifstream input2(operation.inputFileName2.c_str(), std::ios::binary);
    std::ofstream output(operation.outputFileName, std::ios::binary);

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
    output.write(reinterpret_cast<char*>(&header1), sizeof(header1));

    int32_t bytesPerSample = header1.bitsPerSample / 8;
    int16_t sample1 = 0;
    int16_t sample2 = 0;
    int16_t mixSample = 0;

    int32_t sampleSize = header1.numChannels * (header1.bitsPerSample / 8);
    int32_t samplesToSkip = operation.startSec * header1.sampleRate * sampleSize;

    // Пропустить семплы до startSec + промотать 2й файл до нужного места
    for (int32_t i = 0; i < samplesToSkip; ++i) {
        input2.read(reinterpret_cast<char*>(&sample2), bytesPerSample);
        input1.read(reinterpret_cast<char*>(&sample1), bytesPerSample);
        output.write(reinterpret_cast<char*>(&sample1), bytesPerSample);
    }

    // делаем микс
    while (input1.read(reinterpret_cast<char*>(&sample1), bytesPerSample) &&
        input2.read(reinterpret_cast<char*>(&sample2), bytesPerSample)) {
        mixSample = (sample1 + sample2) / 2;
        output.write(reinterpret_cast<char*>(&mixSample), bytesPerSample);
    }

    std::cout << "Mix operation completed." << std::endl;

}
