#include <stdio.h>
#include <stdlib.h>	//calloc

int main() {

	int numofUE[] = { 1000, 5000, 10000, 15000 };
	int UEpertime = 10;
	int leftUE, nextUE;

	int numofslot = 8;

	int time[4] = { 0. };
	int result[4][3] = { 0. };

	int success, fail, total_success = 0, total_fail = 0;
	
	
	/*
	* UE_state
	* [0]: �ʱⰪ 0 ���� 100 ������ 1~9 ���� - 100
	* [1]: Back-off time
	*/
	for (int nUE = 0; nUE < 4; nUE++) {
		leftUE = numofUE[nUE];
		total_success = 0, total_fail = 0;

		int** UE_state = (int**)calloc(numofUE[nUE], sizeof(int*));
		for (int i = 0; i < numofUE[nUE]; i++) UE_state[i] = (int*)calloc(2, sizeof(int));


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
		
			for (int ue = 0; ue < UEpertime; ue++) {	// ���� ������ UE ����
				UE_Tx[ue][0] = -1;
				for (int i = nextUE; i < numofUE[nUE]; i++) {
					if (UE_state[i][0] >= 0 && UE_state[i][0] < 10) {	// ���� ���� (0~9)���� ��
						if (UE_state[i][1] == 0) {	// Back-off time != 0 �� ��� ���� ��� �ƴ� 
							UE_Tx[ue][0] = i;		// ���� ������� ����
							nextUE = i + 1;			// �ش� UE �������� Ž���ϵ��� �ε��� ����
							break;
						}
						else  UE_state[i][1]--;
					}
					else UE_state[i][1]--;
				}// UE ���� �Ϸ� 

				if (UE_Tx[ue][0] == -1) continue;	// ����� UE ������ �Ʒ� ���� ���� & ���� ���´� �ʱⰪ E 

				int selected = rand() % numofslot;
				UE_Tx[ue][1] = selected;

				if (SLOT[selected] == 'E')
					SLOT[selected] = 'S';
				else
					SLOT[selected] = 'C';

			} // UEpertime��ŭ ���� UE ���� �� slot ���� �Ϸ�


			// slot collision ���� �ľ��ؼ� ���� ����, ���� ����
			for (int ue = 0; ue < UEpertime; ue++) {

				if (UE_Tx[ue][0] == -1) continue;

				if (SLOT[UE_Tx[ue][1]] == 'S') {
					UE_state[UE_Tx[ue][0]][0] = 100;
					success++;
				}
				else if (SLOT[UE_Tx[ue][1]] == 'C') {
					if (UE_state[UE_Tx[ue][0]][0] == 9) {
						UE_state[UE_Tx[ue][0]][0] = -100;
						fail++;
					}
					UE_state[UE_Tx[ue][0]][0]++;

					//backoff time ����
					UE_state[UE_Tx[ue][0]][1] = rand() % numofslot + 1;
				}

			}// slot collision ���� �ľ� �Ϸ�


			for (int i = 0; i < UEpertime; i++) free(UE_Tx[i]);
			free(UE_Tx);
			free(SLOT);

			leftUE -= (success + fail);
			total_success += success;
			total_fail += fail;

			time[nUE]++;


		} // while ����

		for (int i = 0; i < numofUE[nUE]; i++) {
			free(UE_state[i]);
		}
		free(UE_state);

		result[nUE][0] = total_success;
		result[nUE][1] = total_fail;
		result[nUE][2] = leftUE;

	} // for numofUE ����


	for (int n = 0; n < 4; n++) {
		printf("[ UE: %d, slot: %d, UEpertime: %d ]\n", numofUE[n], numofslot, UEpertime);
		printf("%d, (success: %d, fail: %d, left UE: %d), %f\n", time[n], result[n][0], result[n][1], result[n][2], (double)result[n][0] / numofUE[n]);
		printf("\n");
	}
}
