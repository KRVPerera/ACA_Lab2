
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "predictors.h"
#include "framework.h"


enum State{
    state00,
    state01,
    state10,
    state11,
};

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
    bool * BHT = (bool * )malloc(8192*sizeof(bool));
    memset(BHT,false,8192);

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



    enum State * BHT = (enum State * )malloc(8192*sizeof(enum State));
    memset(BHT,0,4096);

    enum State curState = state00;
    bool prediction = false;

    /* Variable to store the the address of the branch. */
    uint32_t addr = 0;

    /*
     * Variable to store the actual branch result
     * (obtained from the predictor library)
     */
    enum State actual = state00;

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
        if ((curState == state11) || (curState == state10)) {
            prediction = true;
        }else if ((curState == state01) || (curState == state00)){
            prediction = false;
        }

        /*
         * Feed the prediction to the state machine, and get the actual
         * result back.
         */
        if (predictor_predict(prediction, &actual) != 0) {
            fprintf(stderr, "ERROR: \"predictor_predict()\" called in "\
                    " a state it shouldn't be called\n");
        }

        enum State nxtState;
        if(actual){
            if(curState == state00){
                nxtState = state01;
            }else if((curState == state10) || (curState == state01) || (curState == state11)){
                nxtState = state11;
            }
        } else if (actual == false) {
            if(curState == state11){
                nxtState = state10;
            }else if((curState == state10) || (curState == state01) || (curState == state00)){
                nxtState = state00;
            }
        }

        BHT[index] = nxtState;

    }
    free(BHT);
}

/* Implement assignment 4 here */
void BHT_TwoBit_TwoCol_1024() {
  always_x(false);
}

/* Assignment 4: Change these parameters to your needs */
void assignment_4_your_own(int k, int n) {
  always_x(false);
}

/* Bonus: Change these parameters to your needs */
void bonus_1() {
  always_x(false);
}

/* Bonus: Change these parameters to your needs */
void bonus_2() {
  always_x(false);
}
