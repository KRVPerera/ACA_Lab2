//
// Created by krv on 2/5/17.
//
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/statemachine.h"

/**
 * This function checks the state and return whether the prediction is to be taken or not
 * can be simplified by only checking the 2nd bit only by (sm & 0b10) but due to the clarity implemented as the state
 * machine itself
 */
bool isBranchTaken(enum State sm) {
    bool prediction = false;
    if ((sm == state11) || (sm == state10)) { // (sm == state11) || (sm == state10)
        prediction = true;
    } else if ((sm == state01) || (sm == state00)) { // (sm == state01) || (sm == state00)
        prediction = false;
    }
    return prediction;
}

/**
 * Change the 2 bit state machine state according to the actual result of the branch address taken or not
 * @param sm State enum
 * @param isBranchTaken actual outcome of the branch address taken or not
 * @return can ignore this
 */
enum State stateChange(enum State *sm, bool isBranchTaken) {
    enum State nxtState;
    enum State curState = *sm;

    if (isBranchTaken == true) {
        if (curState == state00) {
            nxtState = state01;
        } else if ((curState == state10) || (curState == state01) || (curState == state11)) { // can be just else here
            nxtState = state11;
        }
    } else if (isBranchTaken == false) {
        if (curState == state11) {
            nxtState = state10;
        } else if ((curState == state10) || (curState == state01) || (curState == state00)) { // can be just else here
            nxtState = state00;
        }
    }
    *sm = nxtState;
}

/**
 * Initialize a array of State enums of given size and with given initial state
 * @param size
 * @param initState
 * @return
 */
enum State *initStateMachineArray(int size, enum State initState) {
    enum State *tmp = (enum State *) malloc(size * sizeof(enum State));
    memset(tmp, initState, size * sizeof(enum State));
    return tmp;
}