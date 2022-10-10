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
	* [0]: 초기값 0 성공 100 재전송 1~9 실패 - 100
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
		* E = empty(초기값) S = selected C = collision
		*/
		char* SLOT = (char*)calloc(numofslot, sizeof(char));
		for (int s = 0; s < numofslot; s++) SLOT[s] = 'E';

		/*
		* UE_Tx
		* [0]: UE 번호
		* [1]: 선택한 slot 번호
		*/
		int** UE_Tx = (int**)calloc(UEpertime, sizeof(int*));
		for (int i = 0; i < UEpertime; i++) {
			UE_Tx[i] = (int*)calloc(2, sizeof(int));
		}


		// UE별 슬롯 정하기
		// 빈 슬롯일 경우 0 / 한 UE만 배정된 경우 1 / 두 개 이상 UE 배정된 경우(충돌) -1
		for (int ue = 0; ue < UEpertime; ue++) {

			for (int i = nextUE; i < numofUE; i++) {
				if (UE_state[i][0] != -100 && UE_state[i][0] != 100) {	// 전송 가능 (0~9)여야 함
					if (UE_state[i][1] != 0)	// Back-off time != 0 일 경우 전송 대상 아님 
						UE_state[i][1]--;
					else{
						UE_Tx[ue][0] = i;		// 전송 대상으로 설정
						nextUE = i + 1;			// 해당 UE 다음부터 탐색하도록 인덱스 지정
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

		} // UEpertime만큼 전송 UE 선택 후 slot 선택 완료

		// slot collision 여부 파악해서 전송 성공, 실패 결정
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
						//backoff time 지정
						UE_state[UE_Tx[ue][0]][1] = rand() % numofslot; // backoff 얼마나 해야 할까....

					}
				}
			}
		} // slot collision 여부 파악 완료


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


		// 한 슬롯에 한 UE가 배정된 경우 성공으로 판단
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