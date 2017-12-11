// print the transition probability table of action : 1(left) to ./action_1.csv
#include <stdio.h>
#include <stdlib.h>

int main() {
    float action_1[100][100] = {{0}};
    int i = 0;
    int j = 0;
    FILE *fp;

    for(i = 1; i < 100; ++i)      // assume all get into the left cell when taking action : 1(left)
        action_1[i][i - 1] = 1;

    for (i = 0; i <= 90; i += 10) {  // left edge
        action_1[i][i - 1] = 0;
        action_1[i][i] = 1;
    }

    for(i = 0; i < 100; ++i) {     // barrier on their left
        if(i == 11 || i == 21 || i == 17 || i == 27 || i == 37 || i == 62 || i == 72 || i == 87) {
            action_1[i][i - 1] = 0;
            action_1[i][i] = 1;
        }
    }

    action_1[99][98] = 0; // final state

    action_1[31][30] = 0; // a
    action_1[32][31] = 0;
    action_1[32][71] = 0.6;
    action_1[32][9] = 0.4;

    action_1[14][13] = 0; // b
    action_1[15][14] = 0;
    action_1[15][57] = 0.4;
    action_1[15][12] = 0.6;

    action_1[48][47] = 0; // c
    action_1[49][48] = 0;
    action_1[49][96] = 0.7;
    action_1[49][25] = 0.3;

    fp = fopen("action_1.csv", "w");

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
