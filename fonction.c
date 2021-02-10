#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"fonction.h"
#include"conf.h"

void voltcell(volt *voltage,int nbcsu,int nbcell,int start) { //this function create the path for the cell and recuperate the tension for each cell
	char cellule[100] = path;
	int endOfChain = 0;
	char numbrecsu[10];
	sprintf(numbrecsu,"%d",nbcsu);
	strcat(cellule, csu);
		strcat(cellule, numbrecsu);
		strcat(cellule, cell);
		char nombre[10] = "";
		endOfChain = strlen(cellule);
		for (int i = 0; i < nbcell; i++) {
			sprintf(nombre, "%d", i);
			strcat(cellule, nombre);
			voltage->tab[i+start] = readFile(cellule);
			cellule[endOfChain] = '\0';
		}
	
}
void cellDegre(volt *voltage,int nbcsu,int start) { //this function create the path temperate and recuperate the two temperature
	char temp[100] = path;
	int endOfChain = 0;
	char numbrecsu[10] = "";
	strcat(temp, csu);
	sprintf(numbrecsu,"%d",nbcsu);
	strcat(temp,numbrecsu);
	strcat(temp, degre);
	char num[10] = "";
	endOfChain = strlen(temp);
	for (int i = 0; i < 2; i++) {
		sprintf(num, "%d", i);
		strcat(temp, num);
		voltage->degree[i+start] = readFile(temp);
		temp[endOfChain] = '\0';
		cellDegre_check(voltage);
	}
}

void batteriesaffer() { //put the state of charging on off
	FILE *fic = fopen(charge, "w");
	fputc('0', fic);
	fclose(fic);
}

void verification(volt *voltage,int nbcell,int deltaT) { //check that each cell is in the safe zone for the health of the cell
	int batterie_charge = 0;
	for (int i = 0; i < nbcell; i++) {
		if (voltage->tab[i] > Umax) {
			printf(
				"cell number: %d as encountered a problem\nupper voltage problem\nvoltage %f\n",
				i, voltage->tab[i]);
			batteriesaffer();
		} else if (voltage->tab[i] < Umin) {
			printf(
				"cell number: %d as encountered a problem\nunder voltage problem\nvoltage %f\n",
				i, voltage->tab[i]);
			batteriesaffer();
		}
	}
	Coulon_Counting(voltage,nbcell,deltaT);
	batterie_charge = averageVoltage(voltage,nbcell);
	cellState(voltage, batterie_charge,nbcell);
}

int current_state(int state) { //check the state of charging of the batterie
	FILE *fic = fopen(charge, "r");
	state = fgetc(fic) - 48; //conversion from ascii table
	printf("state =%d\n", state);
	fclose(fic);
	return state;
}

void batterie_percent(volt *voltage,int nbcell) { // calcul the curent percent of the batterie

for (int i = 0; i < nbcell; i++) {
	if (voltage->tab[i] < 3.4) {
		voltage->percent[i]=0;
		voltage->percent[i] = (((voltage->tab[i] * 4.44) - 11.1) / 32.5) * 100;
	} else if (voltage->tab[i] < 3.7) {
		voltage->percent[i]=0;
		voltage->percent[i] = (((voltage->tab[i] * 78.33) - 262.322) / 32.5)* 100;
	} else {
		voltage->percent[i]=0;
		voltage->percent[i] = (((voltage->tab[i] * 10) - 9.5) / 32.5) * 100;
		//printf("%d",voltage->percent[i]);

	}
}
}
void Coulon_Counting(volt *voltage,int nbcell,int deltaT) { // calcul the curent percent of the batterie with coulond counting methode
	if (voltage->percent[0]=='\0' || deltaT == 0){
		batterie_percent(voltage,nbcell);
	}else{
		for (int i = 0; i < nbcell; i++) {
			voltage->percent[i] = (((voltage->percent[i]*0.325)+ voltage->tab[i]*deltaT)/32.5)*100; 
	
		}
	}
}
