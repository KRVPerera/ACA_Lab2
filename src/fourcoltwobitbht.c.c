//
// Created by krv on 2/5/17.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "../include/fourcoltwobitbht.h"
#include "../include/statemachine.h"
#include <math.h>

struct BHT22 *init22BHT(int patnSize) {
    struct BHT22 *bht22;
    if (patnSize <= MAX_PATTERN_BIT_SIZE) {
        bht22 = (BHT22 *) malloc((1) * sizeof(BHT22));
        bht22->patternBitSize = patnSize;
        bht22->bhtTables = pow(2, bht22->patternBitSize);
        bht22->bhtSize = (MAX_SIZE / 2) / bht22->bhtTables;
        bht22->BHT = (enum State *) malloc((MAX_SIZE) * sizeof(enum State));
        bht22->pattern = 0;
    } else {
        fprintf(stderr, "Invalid pattern bit size");
    }
    return bht22;
}

struct BHT22 *init22BHTWithTbleSize(int patnSize, int tableSize) {
    struct BHT22 *bht22;
    if (patnSize <= MAX_PATTERN_BIT_SIZE) {
        bht22 = (BHT22 *) malloc((1) * sizeof(BHT22));
        bht22->patternBitSize = patnSize;
        bht22->bhtTables = pow(2, bht22->patternBitSize);
        bht22->bhtSize = tableSize;
        bht22->BHT = (enum State *) malloc((tableSize * bht22->bhtTables) * sizeof(enum State));
        bht22->pattern = 0;
    } else {
        fprintf(stderr, "Invalid pattern bit size");
    }
    return bht22;
}

int getTableIndex(BHT22 bht22) {
    return bht22.pattern;
}

bool getPrediction(BHT22 bht22, unsigned long int address) {
    int index = getIndex(bht22, address);
    assert(index < bht22.bhtTables * bht22.bhtSize);
    return isBranchTaken(bht22.BHT[index]);
}

void updatePattern(BHT22 *bht22, bool actual) {
    bht22->pattern = bht22->pattern << 1;
    bht22->pattern = bht22->pattern | (actual ? 1 : 0);
    bht22->pattern %= bht22->bhtTables;
    assert(bht22->pattern >= 0);
}

void updatePrediction(BHT22 *bht22, int addr, int actual) {
    int address = addr & bht22->bhtSize - 1;
    if (address < bht22->bhtSize) {
        int index = getIndex(*bht22, addr);
        stateChange(&bht22->BHT[index], actual);
        updatePattern(bht22, actual);
    } else {
        fprintf(stderr, "Invalid address. Address should be 0 - %d\n", bht22->bhtSize);
    }
}

void destroyBHT22(BHT22 *bht22) {
    free(bht22->BHT);
    free(bht22);
}

int getIndex(BHT22 bht22, unsigned long address) {
    int tableIndex = getTableIndex(bht22);
    int sectionIndex = address & (bht22.bhtSize - 1);
    return tableIndex * bht22.bhtSize + sectionIndex;
}