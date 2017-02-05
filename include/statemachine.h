//
// Created by krv on 2/5/17.
//

#ifndef BPANALYSIS_STATEMACHINE_H
#define BPANALYSIS_STATEMACHINE_H

#include <stdbool.h>

enum State {
    state00,
    state01,
    state10,
    state11,
};

bool isBranchTaken(enum State);

enum State stateChange(enum State *sm, bool branchTaken);

enum State *initStateMachineArray(int size, enum State initState);

#endif //BPANALYSIS_STATEMACHINE_H
