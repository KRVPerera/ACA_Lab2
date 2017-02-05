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

struct BHT22 * init22BHT(int patnSize) {
    struct BHT22 *bht22;
    if(patnSize <= MAX_PATTERN_BIT_SIZE) {
        bht22 = (BHT22 *) malloc((1) * sizeof(BHT22));
        bht22->patternBitSize = patnSize;
        bht22->bhtTables = pow(2,  bht22->patternBitSize);
        bht22->bhtSize = (MAX_SIZE/2) / bht22->bhtTables;
        bht22->BHT = (enum State *) malloc((MAX_SIZE) * sizeof(enum State));
        bht22->pattern = 0;
    }else{
        fprintf(stderr, "Invalid pattern bit size");
    }
    return bht22;
}

int getTableIndex(BHT22 bht22) {
    return bht22.pattern;
}

bool getPrediction(BHT22 bht22, int address) {
    int tableIndex = getTableIndex(bht22);
    assert(address * tableIndex <= MAX_SIZE);
    return bht22.BHT[tableIndex * address];
}

void updatePattern(BHT22 * bht22, bool actual) {
    bht22->pattern = bht22->pattern << 1;
    bht22->pattern = bht22->pattern | (actual ? 1 : 0);
    bht22->pattern %= bht22->bhtTables;
    assert(bht22->pattern >= 0);
}

void updatePrediction(BHT22 *bht22, int address, int actual) {
    if (address < bht22->bhtSize) {
        int tableIndex = getTableIndex(*bht22);
        stateChange(&bht22->BHT[tableIndex * address], actual);
        updatePattern(bht22, actual);
    }else{
        fprintf(stderr, "Invalid address. Address should be 0 - %d\n", bht22->bhtSize);
    }
}

void destroyBHT22(BHT22 * bht22){
    free(bht22->BHT);
    free(bht22);
}