//
// Created by krv on 2/5/17.
//
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/statemachine.h"

bool isBranchTaken(enum State sm) {
    bool prediction = false;
    if ((sm == state11) || (sm == state10)) {
        prediction = true;
    } else if ((sm == state01) || (sm == state00)) {
        prediction = false;
    }
    return prediction;
}

enum State stateChange(enum State *sm, bool isBranchTaken) {
    enum State nxtState;
    enum State curState = *sm;
    if (isBranchTaken) {
        if (curState == state00) {
            nxtState = state01;
        } else if ((curState == state10) || (curState == state01) || (curState == state11)) {
            nxtState = state11;
        }
    } else if (isBranchTaken == false) {
        if (curState == state11) {
            nxtState = state10;
        } else if ((curState == state10) || (curState == state01) || (curState == state00)) {
            nxtState = state00;
        }
    }
    *sm = nxtState;
}

enum State *initStateMachineArray(int size, enum State initState) {
    enum State *tmp = (enum State *) malloc(4096 * sizeof(enum State));
    memset(tmp, initState, 4096);
    return tmp;
}