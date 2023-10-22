#include <iostream>
#include <fstream>
#include <vector>

struct WAVHeader {
    char chunkID[4];//идентификатор формата файла RIFF
    uint32_t chunkSize;//размер данных аудиофайла, без первых 8 байтов заголовка

    char format[4];//формат WAVE

    //идентификатор первой подчасти заголовка,
    // "fmt", что указывает на начало части заголовка,
    // содержащей информацию о формате аудио
    char subchunk1ID[4];

    //размер первой подчасти заголовка
    //(части, содержащей информацию о формате аудио) в байтах
    uint32_t subchunk1Size;

    //аудиоформат, значение 1 обычно означает PCM
    //(самый распространенный формат для аудиофайлов)
    uint16_t audioFormat;

    //количество аудиоканалов, значение 1 обозначает моно, 2 стерео
    uint16_t numChannels;

    //частоту дискретизации аудио, то есть количество выборок аудио в секунду, количество сэмплов, записанных за одну секунду
    uint32_t sampleRate;

    //скорость передачи данных в байтах в секунду
    uint32_t byteRate;

    //размер блока данных в байтах
    uint16_t blockAlign;

    //количество битов на сэмпл
    //это значение указывает на разрешение (глубину) аудиофайла
    uint16_t bitsPerSample;
};

//Заглушение аудио в указанных временных рамках
void mute(const std::string& inputFileName, const std::string& outputFileName, int startSec, int endSec) {//вместо char* - std::string
    std::ifstream input(inputFileName, std::ios::binary);
    std::ofstream output(outputFileName, std::ios::binary);
    WAVHeader header = {};

    //Чтение заголовка из входного файла и запись его в выходной файл
    input.read(reinterpret_cast<char*>(&header), sizeof(header));
    output.write(reinterpret_cast<char*>(&header), sizeof(header));

    int16_t sample = 0;
    int32_t sampleCount = (header.sampleRate * (endSec - startSec));

    for (int i = 0; i < sampleCount; ++i) {
        //Чтение сэмпла из входного файла
        input.read(reinterpret_cast<char*>(&sample), sizeof(sample));

        //Проверка, находится ли текущий сэмпл в указанных временных интервалах
        if (i >= (startSec * header.sampleRate) && i < (endSec * header.sampleRate)) {
            sample = 0;//Заглушаем аудио, устанавливая сэмпл в 0
        }

        //Запись сэмпла в выходной файл
        output.write(reinterpret_cast<char*>(&sample), sizeof(sample);
    }
    //необязательно
    input.close();
    output.close();
}

//Смиксование двух файлов
void mix(const std::string& inputFileName1, const std::string& inputFileName2, const std::string& outputFileName, int startSec) {
    std::ifstream input1(inputFileName1, std::ios::binary);
    std::ifstream input2(inputFileName2, std::ios::binary);
    std::ofstream output(outputFileName, std::ios::binary);
    WAVHeader header = {};
    
    //Чтение заголовка из входного файла и запись его в выходной файл
    input.read(reinterpret_cast<char*>(&header), sizeof(header));
    output.write(reinterpret_cast<char*>(&header), sizeof(header));

    int16_t sample1 = 0;
    int16_t sample2 = 0;
    int16_t mixSample = 0;
    
    //количество сэмплов в одной секунде
    int32_t sampleCount = header.sampleRate * (header.bitsPerSample / 8) * (header.numChannels);

    //количество сэмплов, которые нужно пропустить в начале первого файла
    int32_t samplesToSkip = startSec * sampleCount;

    //пропуск первых секунд в первом файле
    input1.seekg(samplesToSkip, std::ios::beg);

    for (int i = 0; i < sampleCount; ++i) {
        input1.read(reinterpret_cast<char*>(&sample1), sizeof(sample1));
        input2.read(reinterpret_cast<char*>(&sample2), sizeof(sample2));

        //смешивание сэмплов
        mixedSample = (sample1 + sample2) / 2;
        output.write(reinterpret_cast<char*>(&mixedSample), sizeof(mixedSample));
    }

    input1.close();
    input2.close();
    output.close();
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "bad input" << endl;
        return 1;
    }

    const char* configFileName = argv[1];

    // Открываем файл с конфигурацией и выполняем действия в соответствии с ним
    std::ifstream configFile(configFileName);
    std::string line;
    while (std::getline(configFile, line)) {
        std::vector<std::string> parts;
        std::string part;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, part, ' ')) {
            parts.push_back(part);
        }

        if (parts.size() < 3) {
            continue;  // Пропускаем некорректные строки в конфигурации
        }

        const std::string& action = parts[0];
        const std::string& inputFileName = parts[1];

        if (action == "mute") {
            int startSec = std::stoi(parts[2]);
            int endSec = std::stoi(parts[3]);
            muteAudio(inputFileName.c_str(), "output.wav", startSec, endSec);
        }
        else if (action == "mix") {
            int startSec = std::stoi(parts[2]);
            const std::string& inputFileName2 = parts[3];
            mixAudio(inputFileName.c_str(), inputFileName2.c_str(), "output.wav", startSec);
        }
    }

    return 0;
}
