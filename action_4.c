// print the transition probability table of action : 4(down) to ./action_4.csv
#include <stdio.h>
#include <stdlib.h>

int main() {
    float action_1[100][100] = {{0}};
    int i = 0;
    int j = 0;
    FILE *fp;

    for(i = 10; i <= 99; ++i)      // assume all get into the down cell when taking action : 4(down)
        action_1[i][i - 10] = 1;

    for (i = 0; i <= 9; ++i) // down edge
        action_1[i][i] = 1;

    for(i = 0; i < 100; ++i) {     // down barrier
        if(i == 18 || i == 19 || i == 60 || i == 61 || i == 87) { // discard i == 31 (cell a)
            action_1[i][i - 10] = 0;
            action_1[i][i] = 1;
        }
    }

    action_1[99][89] = 0; // final state

    action_1[31][21] = 0; // a
    action_1[41][31] = 0;
    action_1[41][71] = 0.6;
    action_1[41][9] = 0.4;

    action_1[14][4] = 0; // b
    action_1[24][14] = 0;
    action_1[24][57] = 0.4;
    action_1[24][12] = 0.6;

    action_1[48][38] = 0; // c
    action_1[58][48] = 0;
    action_1[58][96] = 0.7;
    action_1[58][25] = 0.3;

    fp = fopen("action_4.csv", "w");

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
