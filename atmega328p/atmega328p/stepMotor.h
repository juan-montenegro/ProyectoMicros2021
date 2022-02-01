/*
 * stepMotor.h
 *
 * Created: 1/02/2022 8:03:15 a. m.
 *  Author: juane
 */ 


#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

int isButtonPressed(unsigned char bitPos);
float driveStepperOclock(float anguloMotor);
float driveStepperAnticlock(float anguloMotor);

#endif /* STEPMOTOR_H_ */