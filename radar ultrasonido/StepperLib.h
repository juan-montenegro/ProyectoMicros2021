/*
 * Stepper.h
 *
 * Created: 2019-06-19 10:10:24 a.m.
 *  Author: BladimirBaccaCortes
 */ 

int isButtonPressed(unsigned char bitPos);
float driveStepperOclock(float anguloMotor);
void driveStepperAnticlock(float *angulo, float anguloMotor);
