#include <stdio.h>
#include <stdlib.h>	//calloc

int main() {

	int numofUE = 7000;
	int leftUE = numofUE;
	int UEpertime = 10;
	
	int numofslot = 8;
	int time = 0;


	/*
	* UE_state
	* [0]: �ʱⰪ 0 ���� 100 ������ 1~9 ���� - 100
	* [1]: Back-off time
	*/
	int** UE_state = (int**)malloc(numofUE* sizeof(int*));
	for (int i = 0; i < numofUE; i++) {
		UE_state[i] = (int*)calloc(2, sizeof(int));
	}


	int nextUE;
	int success, fail, total_success = 0;


	while (leftUE > 0) {
		success = 0, fail = 0;
		nextUE = 0;

		/*
		* SLOT
		* E = empty(�ʱⰪ) S = selected C = collision
		*/
		char* SLOT = (char*)calloc(numofslot, sizeof(char));
		for (int s = 0; s < numofslot; s++) SLOT[s] = 'E';

		/*
		* UE_Tx
		* [0]: UE ��ȣ
		* [1]: ������ slot ��ȣ
		*/
		int** UE_Tx = (int**)calloc(UEpertime, sizeof(int*));
		for (int i = 0; i < UEpertime; i++) {
			UE_Tx[i] = (int*)calloc(2, sizeof(int));
		}


		// UE�� ���� ���ϱ�
		// �� ������ ��� 0 / �� UE�� ������ ��� 1 / �� �� �̻� UE ������ ���(�浹) -1
		for (int ue = 0; ue < UEpertime; ue++) {

			for (int i = nextUE; i < numofUE; i++) {
				if (UE_state[i][0] != -100 && UE_state[i][0] != 100) {	// ���� ���� (0~9)���� ��
					if (UE_state[i][1] != 0)	// Back-off time != 0 �� ��� ���� ��� �ƴ� 
						UE_state[i][1]--;
					else{
						UE_Tx[ue][0] = i;		// ���� ������� ����
						nextUE = i + 1;			// �ش� UE �������� Ž���ϵ��� �ε��� ����
						break;
					}
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

			if (SLOT[selected] == 'E')
				SLOT[selected] = 'S';
			else 
				SLOT[selected] = 'C';

		} // UEpertime��ŭ ���� UE ���� �� slot ���� �Ϸ�

		// slot collision ���� �ľ��ؼ� ���� ����, ���� ����
		for (int s = 0; s < numofslot; s++) {

			if (SLOT[s] == 'S') {
				for (int ue = 0; ue < UEpertime; ue++) {
					if (UE_Tx[ue][1] == s) {
						UE_state[UE_Tx[ue][0]][0] = 100;
						success++;
					}
				}
			}
			else if (SLOT[s] == 'C') {
				for (int ue = 0; ue < UEpertime; ue++) {
					if (UE_Tx[ue][1] == s) {
						UE_state[UE_Tx[ue][0]][0]++;
						if (UE_state[UE_Tx[ue][0]][0] == 10) {
							UE_state[UE_Tx[ue][0]][0] = -100;
							fail++;
						}
						//backoff time ����
						UE_state[UE_Tx[ue][0]][1] = rand() % numofslot; // backoff �󸶳� �ؾ� �ұ�....

					}
				}
			}
		} // slot collision ���� �ľ� �Ϸ�


		for (int i = 0; i < UEpertime; i++) {
			free(UE_Tx[i]);
		}
		free(UE_Tx);
		free(SLOT);

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

		leftUE -= success + fail;
		total_success += success;

		printf("%d: %d %d [%d]\n", time, success, fail, leftUE);
		
		time++;
		
	}
	printf("\n");
	printf("[ UE: %d, slot: %d, UEpertime: %d ]\n", numofUE, numofslot, UEpertime);
	printf("%d, %f", time ,(double)total_success / numofUE);
	
	for (int i = 0; i < numofUE; i++) {
		free(UE_state[i]);
	}
	free(UE_state);
}

// back-off X
// 2292, 0.971143