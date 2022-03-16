// Tower operation functions.

#define		F_CPU	8000000L
#include	<util/delay.h>
#define		TRIGGER		10

void configPWMTower();
void configDistanceTower();
void setTrigger();
void setTowerMotion(unsigned char towerPos);
