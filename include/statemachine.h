//
// Created by krv on 2/5/17.
//

#ifndef BPANALYSIS_STATEMACHINE_H
#define BPANALYSIS_STATEMACHINE_H

#include <stdbool.h>

/**
 * Enum to keep the state of 2 bit state change of the branches
 */
enum State {
    state00,
    state01,
    state10,
    state11,
};

 /**
  * This function checks the state and return whether the prediction is to be taken or not
 * can be simplified by only checking the 2nd bit only by (sm & 0b10) but due to the clarity implemented as the state
 * machine itself
  * @return
  */
bool isBranchTaken(enum State);


/**
 * Change the 2 bit state machine state according to the actual result of the branch address taken or not
 * @param sm State enum
 * @param isBranchTaken actual outcome of the branch address taken or not
 * @return can ignore this
 */
enum State stateChange(enum State *sm, bool branchTaken);

/**
 * Initialize a array of State enums of given size and with given initial state
 * @param size : size of the array to be created
 * @param initState : initial state which is used to initialize the array
 * @return : a pointer to the created enum State array
 */
enum State * initStateMachineArray(int size, enum State initState);

#endif //BPANALYSIS_STATEMACHINE_H
