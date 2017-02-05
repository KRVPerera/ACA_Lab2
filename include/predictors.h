
#ifndef PREDICTORS_H
#define PREDICTORS_H

#include <stdbool.h>

/* Random prediction */
void random_predictor();

/* Predict always true (taken) or false */
void always_x(bool p);

/* Implement assignment 1 here */
void BHT_Simple_8192();

/* Implement assignment 2 here */
void BHT_TwoBit_4096();

/* Implement assignment 4 here */
void BHT_TwoBit_4Col_1024();

/* Assignment 4: Change these parameters to your needs */
void CustomPredictor(int k, int n);

/* Bonus: Change these parameters to your needs */
void bonus_1();

/* Bonus: Change these parameters to your needs */
void bonus_2();

#endif
