#include <iostream>
#include <fstream>
#include <vector>

// Структура для хранения заголовка WAV-файла
struct WAVHeader {
    char chunkID[4];//идентификатор формата файла
    uint32_t chunkSize;//размер данных аудиофайла, без первых 8 байтов заголовка

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

//Входны параметры: имя выходного и выходного файла, начальное и конечное время для заглушения
void muteAudio(const char* inputFileName, const char* outputFileName, int startSec, int endSec) {
    std::ifstream input(inputFileName, std::ios::binary);//Открываем входной файл для чтения в бинарном режиме
    std::ofstream output(outputFileName, std::ios::binary);//Создаем выходной файл для записи в бинарном режиме
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

    //Закрытие файлов
    input.close();
    output.close();
}

