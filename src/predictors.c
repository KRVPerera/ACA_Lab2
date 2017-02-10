
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/predictors.h"
#include "../include/framework.h"
#include "../include/statemachine.h"
#include "../include/fourcoltwobitbht.h"

typedef unsigned int uint32_t;

/* Random prediction */
void random_predictor() {

    /* Variable to store the prediction you predict for this branch. */
    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /* 
     * Variable to store the actual branch result 
     * (obtained from the predictor library)
     */
    bool actual = false;

    /* 
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        /* Do a random prediction */
        prediction = rand() & 1;

        /* 
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }

    }


}

/* Predict always true (taken) or false */
void always_x(bool p) {
    /* Variable to store the prediction you predict for this branch. */
    bool prediction = p;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /* 
     * Variable to store the actual branch result 
     * (obtained from the predictor library)
     */
    bool actual = false;

    /* 
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        /* Do a prediction */
        prediction = p;

        /* 
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }

    }
}

/* Implement assignment 1 here */
void BHT_Simple_8192() {
    bool *BHT = (bool *) malloc(8192 * sizeof(bool));
    memset(BHT, false, 8192);

    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /*
     * Variable to store the actual branch result
     * (obtained from the predictor library)
     */
    bool actual = false;

    /*
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        int index = addr & 0b1111111111111;
        /* Do a prediction */
        prediction = BHT[index];


        /*
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }
        BHT[index] = actual;

    }
    free(BHT);
}

/* Implement assignment 2 here */
void BHT_TwoBit_4096() {

    enum State *BHT = initStateMachineArray(4096, state00);

    enum State curState = state00;
    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /*
     * Variable to store the actual branch result
     * (obtained from the predictor library)
     */
    bool actual = false;

    /*
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        int index = addr & 0b111111111111;
        /* Do a prediction */
        curState = BHT[index];
        prediction = isBranchTaken(curState);
        /*
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }

        stateChange(&BHT[index], actual);

    }
    free(BHT);
}

/* Implement assignment 4 here */
void BHT_TwoBit_4Col_1024() {
    BHT22 *bht22 = init22BHT(2);

    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /*
     * Variable to store the actual branch result
     * (obtained from the predictor library)
     */
    bool actual = false;

    /*
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        prediction = getPrediction(*bht22, addr);
        /*
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }

        updatePrediction(bht22, addr, actual);

    }
    destroyBHT22(bht22);
}

/* Assignment 4: Change these parameters to your needs */
void CustomPredictor() {
    BHT22 *bht22 = init22BHTWithTbleSize(4, 1024);

    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /*
     * Variable to store the actual branch result
     * (obtained from the predictor library)
     */
    bool actual = false;

    /*
     * Prediction loop, until tracefile is empty.
     */
    while (predictor_getState() != DONE) {

        /* Get the next branch address from the state machine. */
        if (predictor_getNextBranch(&addr) != 0) {
            fprintf(stderr, "ERROR: \"predictor_getNextBranch()\" called in "\
                   "a state it shouldn't be called!\n");
        }

        int address = addr & 0b1111111111;
        prediction = getPrediction(*bht22, address);
        /*
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }

        updatePrediction(bht22, address, actual);

    }
    destroyBHT22(bht22);
}

/* Bonus: Change these parameters to your needs */
void bonus_1() {
    always_x(false);
}

/* Bonus: Change these parameters to your needs */
void bonus_2() {
    always_x(false);
}
