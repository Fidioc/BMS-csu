#include <stdlib.h>
#include <stdio.h>

#include "fonction.h"
#include "conf.h"

float readFile(char *source) { //function that read a file that is give in parameter
	FILE *fic = fopen(source, "r");
	if (fic == NULL) {
		printf("No file found , %s\n", source);
		return 1;
	}
	float nombre = 0.0;
	char chaine[50];
	while (fgets(chaine, 50, fic) != NULL) {
	}
	nombre = strtod(chaine, NULL);
	fclose(fic);
	return nombre;
}

void cellState(volt *voltage, int batterie_charge,int nbcell) { // show the current state of each state
	for (int i = 0; i < nbcell; i++) {
		printf("cellule %d sort %f volt et est chargé à %d %% \n", i,
				voltage->tab[i], voltage->percent[i]);
	}
	printf("la charge total de la baterie est de %d %% \n", batterie_charge);
}

int averageVoltage(volt *voltage,int nbcell) { // give the average voltage of the batterie
	int averageV = 0;
	for (int i = 0; i < nbcell; i++) {
		averageV = averageV + voltage->percent[i];
	}
	averageV = averageV / nbcell;
	return averageV;
}

void cellDegre_check(volt *voltage) { // check that the two temperature is beetween -13 and 60 for the health
	for (int i = 0; i < 2; i++) {
		if (voltage->degree[i] <= -13) {
			printf("Batteries degree = %f please shut down the batterie\n",
					voltage->degree[i]);
		} else if (voltage->degree[i] >= 60) {
			printf("Batteries degree = %f please shut down the batterie\n",
					voltage->degree[i]);
		}
	}
}
