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
    float max = -1000;
    float expected = 0;

    unsigned int value_diff_count = 0;

    char cur_act[10][10] = {{0}};   // current action
    char new_act[10][10] = {{0}};
    unsigned int act_diff_count = 0;

    unsigned int conti_same_value = 0;

    float factor = 0.8;

    unsigned int policy_count = 1;

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

    //  first policy : always goes left
    for(i = 0; i < 10; ++i)
        for(j = 0; j < 10; ++j) {
                cur_act[i][j] = 'L';
                new_act[i][j] = 'L';
        }


    while(1) {
        in = fgetc(stdin);
        if(in == 10) {  // input ENTER
            ++k;
            value_diff_count = 0;
            act_diff_count = 0;

            for(i = 0; i < 10; ++i)
                for(j = 0; j < 10; ++j)
                    prevalue[i][j] = value[i][j];

            for(row = 0; row < 10; ++row) {
                for(col = 0; col <10; ++col) {
                    // each state

                    max = -1000;
                    for(action = 0; action < 4; ++action) {
                        // each action

                        if((cur_act[row][col] == 'L' && action == 0) || (cur_act[row][col] == 'U' && action == 1) || (cur_act[row][col] == 'R' && action == 2) || (cur_act[row][col] == 'D' && action == 3) || conti_same_value == 20) {    // if conti_same_value == 20 : do in the iteration after the iteration in which conti_same_value add to 20
                            expected = 0;
                            for(desti = 0; desti < 100; ++desti) {
                                expected += action_all[10*row + col][desti][action] * prevalue[desti/10][desti%10];   // (prob. to a desti) *  (previous(k-1) value of the desti)
                            }

                            if(reward[10*row + col][action] + factor*expected > max) {

                                max = reward[10*row + col][action] + factor*expected;
                                if(conti_same_value == 20) {    // do in the iteration after the iteration in which conti_same_value add to 20
                                    if(!(row == 3 && col == 1) && !(row == 1 && col == 4) && !(row == 4 && col == 8) && !(row == 9 && col == 9)) {
                                        switch(action) {
                                            case 0: new_act[row][col] = 'L';  break;
                                            case 1: new_act[row][col] = 'U';  break;
                                            case 2: new_act[row][col] = 'R';  break;
                                            case 3: new_act[row][col] = 'D';  break;
                                        }
                                    }
                                }
                            }
                        }
                    }   // action loop end
                    value[row][col] = max;
                    if(value[row][col] != prevalue[row][col])
                        ++value_diff_count;
                    if(conti_same_value == 20 && new_act[row][col] != cur_act[row][col])    // if conti_same_value == 20 : do in the iteration after the iteration in which conti_same_value add to 20
                        ++act_diff_count;

                    // each state end
                }   // col loop end
            }   // row loop end
            if(value_diff_count == 0) {
                ++conti_same_value;
                if(conti_same_value == 21) {
                    printf("best policy found!!!\n");
                    return 0;
                }
            } else
                conti_same_value = 0;
            printf("k = %u\n", k);
            printf("policy_count == %u\n", policy_count);
            printf("#changed-value states = %u\n", value_diff_count);   // 0 when k >= 72
            printf("#changed-act states when try new policy = %u\n", act_diff_count);   // 0 when k >= 26
            printf("conti_same_value = %u\n", conti_same_value);
            upsidedown_print_float_matrix(10, 10, value);
            printf("current policy : \n");
            upsidedown_print_char_matrix(10, 10, cur_act);
            if(act_diff_count > 0) {    // check the iteration after the iteration in which conti_same_value add to 20
                printf("\nthere is a better policy, we'll apply it from now on....\n");
                for(i = 0; i < 10; ++i)
                    for(j = 0; j < 10; ++j) {
                        cur_act[i][j] = new_act[i][j];
                        value[i][j] = 0;
                        prevalue[i][j] = 0;
                    }
                conti_same_value = 0;
                //factor = 0.8;
                k = 0;
                ++policy_count;
            }
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

