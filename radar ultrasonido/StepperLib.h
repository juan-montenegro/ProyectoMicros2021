/*
 * Stepper.h
 *
 * Created: 2019-06-19 10:10:24 a.m.
 *  Author: Chavez, Montenegro
 */ 

int isButtonPressed(unsigned char bitPos);
void driveStepperOclock(float *angulo,float anguloMotor);
void driveStepperAnticlock(float *angulo, float anguloMotor);
