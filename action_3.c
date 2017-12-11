// print the transition probability table of action : 3(right) to ./action_3.csv
#include <stdio.h>
#include <stdlib.h>

int main() {
    float action_1[100][100] = {{0}};
    int i = 0;
    int j = 0;
    FILE *fp;

    for(i = 1; i <= 98; ++i)      // assume all get into the right cell when taking action : 3(right)
        action_1[i][i + 1] = 1;

    for (i = 9; i <= 89; i += 10) {  // right edge
        action_1[i][i + 1] = 0;
        action_1[i][i] = 1;
    }

    for(i = 0; i < 100; ++i) {     // barrier on their right
        if(i == 10 || i == 20 || i == 16 || i == 26 || i == 36 || i == 61 || i == 71 || i == 86) {
            action_1[i][i + 1] = 0;
            action_1[i][i] = 1;
        }
    }

    action_1[31][32] = 0; // a
    action_1[30][31] = 0;
    action_1[30][71] = 0.6;
    action_1[30][9] = 0.4;

    action_1[14][15] = 0; // b
    action_1[13][14] = 0;
    action_1[13][57] = 0.4;
    action_1[13][12] = 0.6;

    action_1[48][49] = 0; // c
    action_1[47][48] = 0;
    action_1[47][96] = 0.7;
    action_1[47][25] = 0.3;

    fp = fopen("action_3.csv", "w");

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
