#include <stdio.h>
#include <stdlib.h>	//calloc
#include "../#HEADER/myDistribution.h"

int main() {

	int numofUE = 5000;
	int leftUE = numofUE;
	int UEpertime = 10;

	int numofslot = 8;
	int time = 0;

	
	//int** SLOT = (int**)calloc(numofslot, sizeof(int*));
	//for (int i = 0; i < numofslot; i++) {
	//	SLOT[i] = (int*)calloc(2, sizeof(int));
	//}

	// �ʱⰪ 0 ���� 100 ������ 1~9 ���� -100
	int* UE_state = (int*)calloc(numofUE, sizeof(int));

	int nextUE;
	int success, fail, total_success =0;
	while (leftUE > 0) {
		success = 0;
		fail = 0;

		//int* SLOT = (int*)calloc(numofslot, sizeof(int));

		int** UE_Tx = (int**)calloc(UEpertime, sizeof(int*));
		for (int i = 0; i < UEpertime; i++) {
			UE_Tx[i] = (int*)calloc(3, sizeof(int));
		}

		//int UE_Tx;

		nextUE = 0;
		// UE�� ���� ���ϱ�
		// �� ������ ��� 0 / �� UE�� ������ ��� 1 / �� �� �̻� UE ������ ���(�浹) -1
		for (int ue = 0; ue < UEpertime; ue++) {

			for (int i = nextUE; i < numofUE; i++) {
				//printf("%4d: %4d |", i, UE_state[i]);
				if (UE_state[i] >= 0 && UE_state[i] != 100) {
					UE_Tx[ue][0] = i;
					nextUE = i + 1;
					//printf("\npicked UE: %d\n", i);
					break;
				}
			}

			int selected = rand() % numofslot;

			////UE_select[ue] = selected;
			//if (SLOT[selected] == 0) {
			//	SLOT[selected] = 1;
			//	UE_Tx[ue][1] = 1;
			//}
			//else if (SLOT[selected] == 1)
			//	UE_Tx[ue][1] = -1;
			//printf("%4d: %d [%d] |", UE_Tx[ue][0],selected, UE_Tx[ue][1]);
			//printf("\n");
			
			UE_Tx[ue][1] = selected;

		}
		int collision;
		for (int s = 0; s < numofslot; s++) {
			collision = 0; 
			for (int ue = 0; ue < UEpertime; ue++) {
				if (UE_Tx[ue][1] == s) {
					collision++;
				}
			}
			if (collision == 1) {
				for (int ue = 0; ue < UEpertime; ue++) {
					if (UE_Tx[ue][1] == s) {
						UE_state[UE_Tx[ue][0]] = 100;
						success++;
					}
				}
			}
			else {
				for (int ue = 0; ue < UEpertime; ue++) {
					if (UE_Tx[ue][1] == s) {
						UE_state[UE_Tx[ue][0]]++;
						if (UE_state[UE_Tx[ue][0]] == 10){
							UE_state[UE_Tx[ue][0]] = -100;
							fail++;
						}
					}
				}

			}
		}
		//printf("\n");

/*
		for (int s = 0; s < numofslot; s++)
			printf("| %2d |", s);
		printf("\n");
		for (int s = 0; s < numofslot; s++) {
			printf("| %2d |", SLOT[s][0]);
		}
		printf("\n");		printf("\n");


		// �� ���Կ� �� UE�� ������ ��� �������� �Ǵ�
		printf("success: ");

		for (int ue = 0; ue < UEpertime; ue++) {
			if (UE_Tx[ue][1] = 1) {
				UE_state[UE_Tx[ue][0]] = 100;
				success++;
				printf("%d, ", UE_Tx[ue][0]);
			}

			else {
				UE_state[UE_Tx[ue][0]]++;
				if (UE_state[UE_Tx[ue][0]] == 10)
					UE_state[UE_Tx[ue][0]] = -100;
			}
		}

	
		printf("\n");
	*/
		leftUE -= success+fail;
		total_success += success;
		printf("%d: %d [%d]\n", time, success, leftUE);
		time++;
		
	}
	printf("\n");
	printf("%d, %f", time ,(double)total_success / numofUE);
}