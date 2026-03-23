// DecodeMessage.c 
// This program reads an encoded message from a .txt file and return its decoded version as a string.
// The file consists of lines, each line is of "key value". E.g. "136 huge", "7 dog"
// The task is to decode a hidden message based on the arrangement of these numbers (bricks) into a "pyramid" structure,
//   with each line of the pyramid having one more number than the line above it.
// The top layer (row #1):  brick=1;
// next layer (row #2): {bricks 2, 3}; 
// next row #3: {bricks 4, 5, 6};
// next row #4: {bricks 7, 8, 9, 10}.  
// The key to decoding the message is to use the words corresponding to the numbers at the end of each pyramid line:
// For example: 1, 3, 6, 10, etc.. 
// All the other words must be ignored.
// 
// Warning: final version of the program must have "error-checking and handling":
//    "key value exceeds MAX_BRICK_NUM"
//    "key is not integer"
//    "word is longer than 80", "line is longer than 255"

/* Run cmd
cd \Users\newyo\source\repos\DecodeMessage\x64\Debug OR \Release
DecodeMessage.exe C:\Temp\decode_input.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include ".\DecodeMessage.h"

/////// Uncomment to Debug
#define DEBUG
//#define PYRAMID_DEBUG
#define PRINT_MAX_BRICK_NUM

int main(int argc, char* argv[]) {

    Brick pyramid[MAX_BRICK_NUM];
    char file_name[80];
    int max_brick_num;

    strcpy_s(file_name, sizeof file_name, argv[1]);

    max_brick_num = BuildPyramid(pyramid, MAX_BRICK_NUM);

#ifdef PRINT_MAX_BRICK_NUM
    printf("max_brick_num <%d>\n", max_brick_num);
#endif

#ifdef PYRAMID_DEBUG
    PrintPyramid(pyramid, max_brick_num);
#endif 

#ifdef DEBUG
    printf("before DecodeMessage\n");
#endif 
    DecodeMessage(pyramid, file_name);
}
