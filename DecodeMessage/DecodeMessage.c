// DecodeMessage.c 
// This program reads an encoded message from a .txt file and return its decoded version as a string.
// The file consists of lines, each line is of "key value". E.g. "136 huge", "7 dog"
// The task is to decode a hidden message based on the arrangement of these numbers (bricks) into a "pyramid" structure,
//   with each line of the pyramid having one more number than the line above it.
// The top row  brick=1;
// next row #2: {bricks 2, 3}; 
// next row #3: {bricks 4, 5, 6};
// next row #4: {bricks 7, 8, 9, 10}.  
// The key to decoding the message is to use the words corresponding to the numbers at the end of each pyramid line:
// For example: 1, 3, 6, 10, etc.. 
// All the other words must be ignored.
// 
// Warning: final version of the program must have "error-checking and handling".
// Possible errors:
//    "key value exceeds MAX_BRICK_NUM"
//    "key is not integer"
//    "word is longer than 80", "line is longer than 255"

/* Run cmd
cd \Users\newyo\source\repos\DecodeMessage\x64\Debug
DecodeMessage.exe C:\Temp\decode_input.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include ".\DecodeMessage.h"

/////// Uncomment to Debug
//#define DEBUG
//#define PYRAMID_DEBUG

#define MAX_BRICK_NUM 400 // In release version this can be an argv parameter, e.g "-s400"

// We build a pyramid as a set of "bricks", arranged in "rows": upper layer -> row=1; next layer -> row=2, etc.

// Indicates if the brick is "left-edge, right-edge" etc.
// Only PEAK and RIGHT get decoded
enum BrickPos {PEAK=1, LEFT=2, RIGHT=3, INSIDE=4};

typedef struct Brick
{
    int row;  //Informational - can be of help in debugging: to check if the built pyramid correct.
    int brick_pos;
} Brick;

Brick pyramid[MAX_BRICK_NUM];

///////////char file_name[80] = "C:\\Temp\\decode_input.txt"; // In release version this can be an argv parameter, e.g. "-fC:\Temp\decode_input.txt"
char file_name[80];

int main(int argc, char* argv[]) {

    strcpy_s(file_name, sizeof file_name, argv[1]);

#ifdef DEBUG
    printf("\n<argv %s>", argv[1]);
    printf("\nfile_name <%s>", file_name);
#endif


    int max_index, max_brick_num, rc1, rc2;
  
    max_brick_num = BuildPyramid();

#ifdef DEBUG
    printf("max_brick_num <%d>\n", max_brick_num);
#endif

#ifdef PYRAMID_DEBUG
    PrintPyramid(max_brick_num);
#endif 

    DecodeMessage();
}

BuildPyramid() {
    int curr_brick_num, curr_row, i, j;

    pyramid[1].row = 1;
    pyramid[1].brick_pos = PEAK;       
    
    // Ready to loop through bricks
    curr_brick_num = 2;
    curr_row = 2;

    while (curr_brick_num < MAX_BRICK_NUM) {
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

PrintPyramid(int max_index) {
     int i;

        for (i = 1; i <= max_index; i++)
            printf("index <%3d> row <%d> pos <%d>\n", i, pyramid[i].row, pyramid[i].brick_pos);
}


int DecodeMessage() {
    errno_t error_code;
    FILE* fp;

    char  line[255];
    
    // For Release version it can be placed as an argument to command line (e.g. "-fC:\Temp\decode_input.txt)
 
    error_code = fopen_s(&fp, file_name, "r");
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
        line[strlen(line) - 1] = '\0';  //Get rid of new_line, so when we parse line we'll get "value as a string.
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
            //printf("decoded word <%s>\n", value);
            printf("%s\n", value);
        }
  
    }
    fclose(fp);

#ifdef DEBUG
    printf("max key <%d>\n", max_key);
#endif

     return max_key;
}
