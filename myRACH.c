#include <stdio.h>
#include <stdlib.h>  //calloc

int main() {
    // int numofUE[] = { 1000, 5000, 10000, 15000 };
    int numofUE = 1000;
    double UEpersf;
    int candUE = 0;

    int leftUE, nextUE;

    int numofpreamble = 54;
    int numofsf = 10;

    int success = 0, fail = 0;

    //	int RAO = {1,6};
    /*
            for(int nUE=0;nUE<4;nUE++){

                    int** UE_state = (int**)calloc(numofUE, sizeof(int*));
                    for (int i = 0; i < numofUE; i++) UE_state[i] =
    (int*)calloc(3, sizeof(int));

                    leftUE =numofUE;
                    candUE=0;
                    for(int s=0; s< numofsf; s++){
                            UEpersf = (double)rand()/RAND_MAX*leftUE;
                            leftUE -= UEpersf;
                            candUE += UEpersf;


                            if(s==1 ||s==6){
                                    int** UE_Tx = (int**)
    calloc(candUE,sizeof(int*)); for(int i =0; i<candUE; i++) UE_Tx[i] =
    (int*)calloc(2,sizeof(int));

                                    char* PREAMBLE =
    (char*)calloc(numofpreamble, sizeof(char)); for (int s = 0; s <
    numofpreamble; s++) PREAMBLE[s] = 'E';


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

    int **UE_state = (int **)calloc(numofUE, sizeof(int *));
    for (int i = 0; i < numofUE; i++)
        UE_state[i] = (int *)calloc(3, sizeof(int));

    leftUE = numofUE;
    int cnt = 0;
    while (leftUE > 0) {
        for (int s = 0; s < numofsf; s++) {
            UEpersf = numofUE / numofsf;
            
            candUE += UEpersf;

            printf("SUBFRAME: %d, UE: %d ) leftUE: %d\n", s, (int)UEpersf, leftUE);

            if (s == 1 || s == 6) {
                success = 0, nextUE = 0;

                printf("[candidate: %d]", candUE);

                //

                int **UE_Tx = (int **)calloc(candUE, sizeof(int *));
                for (int i = 0; i < candUE; i++)
                    UE_Tx[i] = (int *)calloc(2, sizeof(int));

                char *PREAMBLE = (char *)calloc(numofpreamble, sizeof(char));
                for (int s = 0; s < numofpreamble; s++) PREAMBLE[s] = 'E';

                //

                for (int ue = 0; ue < candUE; ue++) {  // 전송 가능한 UE 추출
                    UE_Tx[ue][0] = -1;
                    for (int i = nextUE; i < numofUE; i++) {
                        if (UE_state[i][0] >= 0 &&
                            UE_state[i][0] < 10) {  // 전송 가능 (0~9)여야 함
                            if (UE_state[i][1] == 0) {  // Back-off time != 0 일
                                                        // 경우 전송 대상 아님
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
                for (int ue = 0; ue < candUE; ue++) {
                    if (UE_Tx[ue][0] == -1) continue;

                    if (PREAMBLE[UE_Tx[ue][1]] == 'S') {
                        UE_state[UE_Tx[ue][0]][0] = 100;
                        success++;
                    } else if (PREAMBLE[UE_Tx[ue][1]] == 'C') {
                        if (UE_state[UE_Tx[ue][0]][0] == 9) {
                            UE_state[UE_Tx[ue][0]][0] = -100;
                            fail++;
                        }
                        UE_state[UE_Tx[ue][0]][0]++;
                        // backoff time 지정
                        UE_state[UE_Tx[ue][0]][1] = rand() % 20 + 1;
                    }

                }  // slot collision 여부 파악 완료

                printf("UE: %d, success: %d fail:%d\n", candUE, success, fail);
                leftUE -= success + fail;
            }
        }
        cnt++;
        break;
    }
}
