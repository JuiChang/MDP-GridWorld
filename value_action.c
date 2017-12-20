#include <stdio.h>

int csv_read_float(char *path, int num_row, int num_col, float array[][num_col]);
int upsidedown_print_float_matrix(int num_row, int num_col, float array[][num_col]);
int upsidedown_print_char_matrix(int num_row, int num_col, char array[][num_col]);

int main(void) {

    int in;

    //  parameters of MDP
    float action_l[100][100] = {{0}}; // prob. of reaching a state(second index) when taking the left action from a state(first index)
    float action_u[100][100] = {{0}};
    float action_r[100][100] = {{0}};
    float action_d[100][100] = {{0}};
    float reward[100][4] = {{0}};

    float action_all[100][100][4] = {{0}};

    unsigned int k = 0;    // time limit start from 0
    float value[10][10] = {{0}};  // each time-limited value = 0 when k = 0
    float prevalue[10][10] = {{0}};

    unsigned int col = 0, row = 0, action = 0, desti = 0, i = 0, j = 0;  // for loops
    float max = -100000000;
    float expected = 0;

    unsigned int value_diff_count = 0;

    char act[10][10] = {{0}};
    char preact[10][10] = {{0}};
    unsigned int act_diff_count = 0;

    csv_read_float("./action_1.csv", 100, 100, action_l);
    csv_read_float("./action_2.csv", 100, 100, action_u);
    csv_read_float("./action_3.csv", 100, 100, action_r);
    csv_read_float("./action_4.csv", 100, 100, action_d);
    csv_read_float("./reward.csv", 100, 4, reward);


    for(i = 0; i < 100; ++i) {
        for(j = 0; j < 100; ++j) {
            action_all[i][j][0] = action_l[i][j];
            action_all[i][j][1] = action_u[i][j];
            action_all[i][j][2] = action_r[i][j];
            action_all[i][j][3] = action_d[i][j];
        }
    }

    while(1) {
        in = fgetc(stdin);
        if(in == 10) {  // input ENTER
            ++k;
            value_diff_count = 0;
            act_diff_count = 0;

            for(i = 0; i < 10; ++i) {
                for(j = 0; j < 10; ++j) {
                    prevalue[i][j] = value[i][j];
                    preact[i][j] = act[i][j];
                }
            }

            for(row = 0; row < 10; ++row) {
                for(col = 0; col <10; ++col) {
                    // each state

                    max = -100000000;
                    for(action = 0; action < 4; ++action) {
                        // each action

                        expected = 0;
                        for(desti = 0; desti < 100; ++desti) {
                            expected += action_all[10*row + col][desti][action] * prevalue[desti/10][desti%10];   // (prob. to a desti) *  (previous(k-1) value of the desti)
                        }

                        if(reward[10*row + col][action] + expected > max) {
                            max = reward[10*row + col][action] + expected;
                            if(!(row == 3 && col == 1) && !(row == 1 && col == 4) && !(row == 4 && col == 8) && !(row == 9 && col == 9)) {
                                switch(action) {
                                    case 0: act[row][col] = 'L';    break;
                                    case 1: act[row][col] = 'U';    break;
                                    case 2: act[row][col] = 'R';    break;
                                    case 3: act[row][col] = 'D';    break;
                                }
                            }
                        }
                    }
                    value[row][col] = max;
                    if(value[row][col] != prevalue[row][col])
                        ++value_diff_count;
                    if(act[row][col] != preact[row][col])
                        ++act_diff_count;
                }
            }
            printf("k = %u\n", k);
            printf("#changed-value states = %u\n", value_diff_count);   // 0 when k >= 72
            printf("#changed-act states = %u\n", act_diff_count);   // 0 when k >= 26
            upsidedown_print_float_matrix(10, 10, value);
            upsidedown_print_char_matrix(10, 10, act);
            /*
            printf("prevalue : \n");
            upsidedown_print_float_matrix(10, 10, prevalue);
            */
        } else {
            printf("error, undefined input\n");
            while(fgetc(stdin) != 10)
                ;
        }
    }
    return 0;
}


int csv_read_float(char *path, int num_row, int num_col, float array[][num_col]) {
    FILE *fp;

    int i = 0, j = 0;

    fp = fopen(path, "r");

    for(i = 0; i < num_row; ++i) {
        for(j = 0; j < num_col; ++j) {
            fscanf(fp, "%f", &(array[i][j]));
            fgetc(fp);  // get the ',' or '\n'
        }
    }
    return 0;
}

int upsidedown_print_float_matrix(int num_row, int num_col, float array[][num_col]) {
    int i = 0, j = 0;
    for(i = num_row-1; i >= 0; --i) {
        for(j = 0; j < num_col; ++j) {
            printf("%8.2f", array[i][j]);
        }
        printf("\n");
    }
}

int upsidedown_print_char_matrix(int num_row, int num_col, char array[][num_col]) {
    int i = 0, j = 0;
    for(i = num_row-1; i >= 0; --i) {
        for(j = 0; j < num_col; ++j) {
            printf("%-4c\t", array[i][j]);
        }
        printf("\n");
    }
}

