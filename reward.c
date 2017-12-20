#include <stdio.h>
#include <stdlib.h>

int main() {
    int reward[100][4] = {{0}}; // four columns represent four actions : l, u, r, d
    int i = 0;
    int j = 0;

    FILE *fp;

    for(i = 0; i < 100; ++i)
        for (j = 0; j < 4; ++j)
            reward[i][j] = -1;

    for (i = 0; i <= 90; i += 10)  // l to edge
        reward[i][0] = -5;

    for (i = 90; i <= 98; ++i)  // u to edge
        reward[i][1] = -5;

    for (i = 9; i <= 89; i += 10)  // r to edge
        reward[i][2] = -5;

    for (i = 0; i <= 9; ++i)  // d to edge
        reward[i][3] = -5;

    // barrier on their left
    reward[11][0] = -5;
    reward[21][0] = -5;
    reward[17][0] = -5;
    reward[27][0] = -5;
    reward[37][0] = -5;
    reward[62][0] = -5;
    reward[72][0] = -5;
    reward[87][0] = -5;


    // barrier above them
    reward[8][1] = -5;
    reward[9][1] = -5;
    reward[21][1] = -5;
    reward[50][1] = -5;
    reward[51][1] = -5;
    reward[77][1] = -5;

    // barrier on their right
    reward[10][2] = -5;
    reward[20][2] = -5;
    reward[16][2] = -5;
    reward[26][2] = -5;
    reward[36][2] = -5;
    reward[61][2] = -5;
    reward[71][2] = -5;
    reward[86][2] = -5;

    // barrier below them
    reward[18][3] = -5;
    reward[19][3] = -5;
    //reward[31][3] = -5;
    reward[60][3] = -5;
    reward[61][3] = -5;
    reward[87][3] = -5;

    // dotted line
    reward[7][1] = -3;
    reward[17][3] = -3;
    reward[81][2] = -3;
    reward[82][0] = -3;
    reward[96][2] = -3;
    reward[97][0] = -3;

    // a, b, c, final cell
    for (j = 0; j < 4; ++j) {
        reward[31][j] = 0;
        reward[14][j] = 0;
        reward[48][j] = 0;
        reward[99][j] = 0;
    }

    reward[89][1] = 100;
    reward[98][2] = 100;

    fp = fopen("reward.csv", "w");

    for (i = 0; i < 100; ++i) {
        for (j = 0; j < 4; ++j) {
            fprintf(fp, "%d", reward[i][j]);
            if(j != 3)
                fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);

    return 0;
}
