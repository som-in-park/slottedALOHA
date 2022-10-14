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
	* [0]: 초기값 0 성공 100 재전송 1~9 실패 - 100
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
		
			for (int ue = 0; ue < UEpertime; ue++) {	// 전송 가능한 UE 추출
				UE_Tx[ue][0] = -1;
				for (int i = nextUE; i < numofUE[nUE]; i++) {
					if (UE_state[i][0] >= 0 && UE_state[i][0] < 10) {	// 전송 가능 (0~9)여야 함
						if (UE_state[i][1] == 0) {	// Back-off time != 0 일 경우 전송 대상 아님 
							UE_Tx[ue][0] = i;		// 전송 대상으로 설정
							nextUE = i + 1;			// 해당 UE 다음부터 탐색하도록 인덱스 지정
							break;
						}
						else  UE_state[i][1]--;
					}
					else UE_state[i][1]--;
				}// UE 추출 완료 

				if (UE_Tx[ue][0] == -1) continue;	// 추출된 UE 없으면 아래 과정 생략 & 슬롯 상태는 초기값 E 

				int selected = rand() % numofslot;
				UE_Tx[ue][1] = selected;

				if (SLOT[selected] == 'E')
					SLOT[selected] = 'S';
				else
					SLOT[selected] = 'C';

			} // UEpertime만큼 전송 UE 선택 후 slot 선택 완료


			// slot collision 여부 파악해서 전송 성공, 실패 결정
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

					//backoff time 지정
					UE_state[UE_Tx[ue][0]][1] = rand() % numofslot + 1;
				}

			}// slot collision 여부 파악 완료


			for (int i = 0; i < UEpertime; i++) free(UE_Tx[i]);
			free(UE_Tx);
			free(SLOT);

			leftUE -= (success + fail);
			total_success += success;
			total_fail += fail;

			time[nUE]++;


		} // while 종료

		for (int i = 0; i < numofUE[nUE]; i++) {
			free(UE_state[i]);
		}
		free(UE_state);

		result[nUE][0] = total_success;
		result[nUE][1] = total_fail;
		result[nUE][2] = leftUE;

	} // for numofUE 종료


	for (int n = 0; n < 4; n++) {
		printf("[ UE: %d, slot: %d, UEpertime: %d ]\n", numofUE[n], numofslot, UEpertime);
		printf("%d, (success: %d, fail: %d, left UE: %d), %f\n", time[n], result[n][0], result[n][1], result[n][2], (double)result[n][0] / numofUE[n]);
		printf("\n");
	}
}
