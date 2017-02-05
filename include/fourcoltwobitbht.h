//
// Created by krv on 2/5/17.
//

#ifndef BPANALYSIS_FOURCOLTWOBITBHT_H
#define BPANALYSIS_FOURCOLTWOBITBHT_H

#define MAX_SIZE 8192
#define MAX_PATTERN_BIT_SIZE 4

typedef struct BHT22 {
    enum State *BHT;
    int pattern;
    int patternBitSize;
    int bhtSize;
    int bhtTables;
} BHT22;

BHT22 * init22BHT(int patnSize);

bool getPrediction(BHT22 bht22, int address);

void updatePrediction(BHT22 *bht22, int address, int actual);

void destroyBHT22(BHT22 * bht22);

#endif //BPANALYSIS_FOURCOLTWOBITBHT_H
