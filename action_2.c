// print the transition probability table of action : 2(up) to ./action_2.csv
#include <stdio.h>
#include <stdlib.h>

int main() {
    float action_1[100][100] = {{0}};
    int i = 0;
    int j = 0;
    FILE *fp;

    for(i = 0; i <= 89; ++i)      // assume all get into the upper cell when taking action : 2(up)
        action_1[i][i + 10] = 1;

    for (i = 90; i <= 99; ++i) // up edge
        action_1[i][i] = 1;

    for(i = 0; i < 100; ++i) {     // upper barrier
        if(i == 8 || i == 9 || i == 21 || i == 50 || i == 51 || i == 77) {
            action_1[i][i + 10] = 0;
            action_1[i][i] = 1;
        }
    }


    action_1[31][41] = 0; // a

    action_1[14][24] = 0; // b
    action_1[4][14] = 0;
    action_1[4][57] = 0.4;
    action_1[4][12] = 0.6;

    action_1[48][58] = 0; // c
    action_1[38][48] = 0;
    action_1[38][96] = 0.7;
    action_1[38][25] = 0.3;

    fp = fopen("action_2.csv", "w");

    for (i = 0; i < 100; ++i) {
        for (j = 0; j < 100; ++j) {
            if(action_1[i][j] != 0 && action_1[i][j] != 0)
                fprintf(fp, "%.1f", action_1[i][j]);
            else
                fprintf(fp, "%.0f", action_1[i][j]);
            if(j != 99)
                fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
