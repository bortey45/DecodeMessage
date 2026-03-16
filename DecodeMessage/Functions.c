#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include ".\DecodeMessage.h"

int BuildPyramid(Brick pyramid[], int max_num) {
    int curr_brick_num, curr_row, i, j;

    pyramid[1].row = 1;
    pyramid[1].brick_pos = PEAK;

    // Ready to loop through bricks
    curr_brick_num = 2;
    curr_row = 2;

    while (curr_brick_num < max_num) {
        for (i = 1; i <= curr_row; i++) {  //each row has "row" number of bricks
            pyramid[curr_brick_num].row = curr_row;
            if (i == 1) pyramid[curr_brick_num].brick_pos = LEFT; //first brick in the row
            else if (i == curr_row) pyramid[curr_brick_num].brick_pos = RIGHT; //last brick in the row
            else pyramid[curr_brick_num].brick_pos = INSIDE;
            curr_brick_num++;
        }
        curr_row++;
    }
    curr_brick_num--;
    return curr_brick_num;
}

void PrintPyramid(Brick pyramid[], int max_index) {
    int i;

    for (i = 1; i <= max_index; i++)
        printf("index <%3d> row <%d> pos <%d>\n", i, pyramid[i].row, pyramid[i].brick_pos);
}


int DecodeMessage(Brick pyramid[], char file_name[]) {
    errno_t error_code; //Zero if successful; an error code on failure
    FILE* fp;

    char  line[255];

    error_code = fopen_s(&fp, file_name, "r");
    // Check if error_code >0 and report the problem
    char value[80];
    char key[80];

    char* token1;
    char* next_token1;
    char seps[] = " ";
    int len;
    int int_key;
    int max_key = 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strlen(line) - 1] = '\0';  //Get rid of new_line, so when we parse line we'll get "value" as a string.
        len = strlen(line);

#ifdef DEBUG
        printf("line <%s> len <%d>\n", line, len);
#endif

        token1 = NULL;
        next_token1 = NULL;

        token1 = strtok_s(line, seps, &next_token1);
        if (token1 != NULL)
        {
            strcpy_s(key, sizeof key, token1);
            token1 = strtok_s(NULL, seps, &next_token1);
            strcpy_s(value, sizeof value, token1);

#ifdef DEBUG
            printf("key <%s> value <%s>\n", key, value);
#endif

        }

        int_key = atoi(key);
        if ((pyramid[int_key].brick_pos == RIGHT) || (pyramid[int_key].brick_pos == PEAK))
        {
             printf("%s\n", value);
        }

    }
    fclose(fp);

#ifdef DEBUG
    //printf("max key <%d>\n", max_key);
    printf("hello, world!");
#endif

    return max_key;
}
