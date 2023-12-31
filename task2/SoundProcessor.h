#ifndef DASHA_SOUNDPROCESSOR_H
#define DASHA_SOUNDPROCESSOR_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "OperationReader.h"

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


class SoundProcessor {

public:
    void mute(Operation& operation);
    void mix(Operation& operation);
private:

};


#endif //DASHA_SOUNDPROCESSOR_H
