/*
 * stepMotor.h
 *
 * Created: 1/02/2022 8:03:15 a. m.
 *  Author: juane
 */ 


#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

/* Define constants */
#define DELAY_BASE	170
#define PERIOD 10
#define STEP 512
#define angle (float)360/STEP

//int isButtonPressed(unsigned char bitPos);
float dsOclock(float aMotor);
float dsAnticlock(float aMotor);

#endif /* STEPMOTOR_H_ */