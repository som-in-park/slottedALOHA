#include <stdio.h>
#include <stdlib.h> //calloc
#include <memory.h>
#include <string.h>
#include <math.h>
#include <time.h>



struct UEinfo {
    int id_num;
    int preamble;

};

int maxTime = 6000;


int main() {
    // int numofUE[] = { 1000, 5000, 10000, 15000 };
    int numofUE = 10000;
    int active_UE = 0;

    int leftUE;

    int numofpreamble = 64;
    int numofsf = 10;

    int success = 0, fail = 0;

    int init_nUE(int nUE, int accessTime);
    void initialUE(struct UEinfo* user, int id);

    void UE_preamble(int numofUE);



    leftUE = numofUE;
    int cnt = 0;
 //   for (int time = 0; time < maxTime; time++) { // 1분

        active_UE = init_nUE(numofUE, 5);

        printf("%d", active_UE);
        return 0;

 //   }
}
/*
            if (s == 1 || s == 6) {
                success = 0, nextUE = 0;

                printf("[candidate: %d]", active_UE);

                //

                int** UE_Tx = (int**)calloc(active_UE, sizeof(int*));
                for (int i = 0; i < active_UE; i++)
                    UE_Tx[i] = (int*)calloc(2, sizeof(int));

                char* PREAMBLE = (char*)calloc(numofpreamble, sizeof(char));
                for (int s = 0; s < numofpreamble; s++) PREAMBLE[s] = 'E';

                //

                for (int ue = 0; ue < active_UE; ue++) {  // 전송 가능한 UE 추출
                    UE_Tx[ue][0] = -1;
                    for (int i = nextUE; i < numofUE; i++) {
                        if (UE_state[i][0] >= 0 &&
                            UE_state[i][0] < 10) {  // 전송 가능 (0~9)여야 함
                            if (UE_state[i][1] == 0) {  // Back-off time != 0 일 경우 전송 대상 아님
                                UE_Tx[ue][0] = i;  // 전송 대상으로 설정
                                UE_state[i][2]++;
                                nextUE = i + 1;  // 해당 UE 다음부터 탐색하도록
                                                 // 인덱스 지정
                                break;
                            }
                        }
                    }  // UE 추출 완료

                    int selected = rand() % 54;
                    UE_Tx[ue][1] = selected;
                    if (PREAMBLE[selected] == 'E')
                        PREAMBLE[selected] = 'S';
                    else
                        PREAMBLE[selected] = 'C';
                }

                // slot collision 여부 파악해서 전송 성공, 실패 결정
                for (int ue = 0; ue < active_UE; ue++) {
                    if (UE_Tx[ue][0] == -1) continue;

                    if (PREAMBLE[UE_Tx[ue][1]] == 'S') {
                        UE_state[UE_Tx[ue][0]][0] = 100;
                        success++;
                    }
                    else if (PREAMBLE[UE_Tx[ue][1]] == 'C') {
                        if (UE_state[UE_Tx[ue][0]][0] == 9) {
                            UE_state[UE_Tx[ue][0]][0] = -100;
                            fail++;
                        }
                        UE_state[UE_Tx[ue][0]][0]++;
                        // backoff time 지정
                        UE_state[UE_Tx[ue][0]][1] = rand() % 20 + 1;
                    }

                }  // slot collision 여부 파악 완료

                printf("UE: %d, success: %d fail:%d\n", active_UE, success, fail);
                leftUE -= success + fail;
            }
        }
        cnt++;
        break;
    
}
*/
int init_nUE(int nUE, int accessTime) {
    int numof_aUE = ceil((double)nUE * (double)5 * 1.0 / (double)maxTime);
    
    if (numof_aUE == 0)
        numof_aUE = 1;
}

void initialUE(struct UEinfo* user, int id) {
    user->id_num = id;
    user->preamble = -1;
}
