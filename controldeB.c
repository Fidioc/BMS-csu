#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "fonction.h"

void controlB() { // main function of the API that regroup all the functionnality
	volt voltage;
	int state = 0;
	int batterie_charge = 0;
	int nbcsu=0;
	int* csu = NULL;//this taab will have the size of the number of csu 
	int nbcell=0;// number use for know where to start in the tab of tension
	int nbdegreecheck=0;// same utility of nbcell but for degree
	int nballcell=0; // number of cell in the batterie
	int deltaT=0;// variable of time for coulon counting methode
	FILE *fic=fopen("setting.txt","r");
	fscanf(fic,"%d",&nbcsu);
	csu = malloc(nbcsu * sizeof(int));
	if (csu == NULL){
		exit(0);
	}
	for (int i=0;i<nbcsu;i++){
		fscanf(fic,"%d",&(csu[i]));
		if (csu[i]==' '){
			csu[i]='\0';
			i=i-1;
		}else{
			nballcell+=csu[i];
		}
	}
	fclose(fic);
	while (true) {
		for(int i=0;i<nbcsu;i++){
			voltcell(&voltage,i,csu[i],nbcell);
			cellDegre(&voltage,i,nbdegreecheck);
			nbcell+=csu[i];
			nbdegreecheck+=2;
		}
		nbcell=0;
		nbdegreecheck=0;
		batterie_percent(&voltage,nballcell);
		batterie_charge = averageVoltage(&voltage,nballcell);
		state = current_state(state);
		if (state != 0) {
			verification(&voltage,nballcell,deltaT);
		} else {
			deltaT = 0;
			cellState(&voltage, batterie_charge,nballcell);
		}
		sleep(2);
		deltaT+=2;
		
	}
	free(csu);
}