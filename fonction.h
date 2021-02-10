#include <stdio.h>
#include <string.h>

#define true 1
#define false 0

typedef struct volt volt;
struct volt {
	float tab[6];
	int percent[6];
	float degree[4];
};

void controlB();
float readFile(char*);
void voltcell(volt*,int ,int ,int );
void cellState(volt*,int,int);
void verification(volt*,int,int);
void batteriesaffer();
int current_state(int);
void cellDegre(volt *,int,int);
void batterie_percent(volt *,int);
int averageVoltage(volt *,int);
void cellDegre_check(volt *);
void Coulon_Counting(volt *,int ,int );