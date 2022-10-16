#include <stdio.h>
#include <stdlib.h>	//calloc

int main() {

	// int numofUE[] = { 1000, 5000, 10000, 15000 };
	int numofUE = 1000;
	int UEpersf;
	int candUE=0;

	int leftUE, nextUE;

	int numofpreamble = 54;
	int numofsf = 10;

	int success=0;

//	int RAO = {1,6};
/*
	for(int nUE=0;nUE<4;nUE++){

		int** UE_state = (int**)calloc(numofUE, sizeof(int*));
		for (int i = 0; i < numofUE; i++) UE_state[i] = (int*)calloc(3, sizeof(int));

		leftUE =numofUE;
		candUE=0;
		for(int s=0; s< numofsf; s++){
			UEpersf = (double)rand()/RAND_MAX*leftUE;
			leftUE -= UEpersf;
			candUE += UEpersf;


			if(s==1 ||s==6){
				int** UE_Tx = (int**) calloc(candUE, sizeof(int*));
				for(int i =0; i<candUE; i++) UE_Tx[i] = (int*)calloc(2,sizeof(int));
				
				char* PREAMBLE = (char*)calloc(numofpreamble, sizeof(char));	
				for (int s = 0; s < numofpreamble; s++) PREAMBLE[s] = 'E';


				for(int c =0; c< candUE; c++){
					int selected = rand()%54;
					UE_Tx[c][1]= selected;
					if (PREAMBLE[selected] == 'E')
					PREAMBLE[selected] = 'S';
				else
					PREAMBLE[selected] = 'C';

				}
			for (int ue = 0; ue < candUE; ue++) {

				if (PREAMBLE[UE_Tx[ue][1]] == 'S') {
					printf("success\n");
				}				
			}
		}
	}	
	
}
*/

	

		int** UE_state = (int**)calloc(numofUE, sizeof(int*));
		for (int i = 0; i < numofUE; i++) UE_state[i] = (int*)calloc(3, sizeof(int));

		leftUE =numofUE;
		candUE=0;
		for(int s=0; s< numofsf; s++){
			UEpersf = (double)rand()/RAND_MAX*0.1*leftUE;
			leftUE -= UEpersf;
			candUE += UEpersf;


			if(s==1 ||s==6){
				success =0;

				printf("[candidate: %d]", candUE);
				int** UE_Tx = (int**) calloc(candUE, sizeof(int*));
				for(int i =0; i<candUE; i++) UE_Tx[i] = (int*)calloc(2,sizeof(int));
				
				char* PREAMBLE = (char*)calloc(numofpreamble, sizeof(char));	
				for (int s = 0; s < numofpreamble; s++) PREAMBLE[s] = 'E';


				for(int c =0; c< candUE; c++){
					int selected = rand()%54;
					UE_Tx[c][1]= selected;
					if (PREAMBLE[selected] == 'E')
					PREAMBLE[selected] = 'S';
				else
					PREAMBLE[selected] = 'C';

				}
			for (int ue = 0; ue < candUE; ue++) {

				if (PREAMBLE[UE_Tx[ue][1]] == 'S') {
					success++;
				}				
			}
			printf("success: %d\n", success);
		}
	}	
	
}

