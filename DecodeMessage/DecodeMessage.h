#include <stdio.h>
#include <limits.h>

#define MAX_BRICK_NUM 2000 // In release version this can be an argv parameter, e.g "-s400"

// We build a pyramid as a set of "bricks", arranged in "rows": upper layer -> row=1; next layer -> row=2, etc.

// BrickPos indicates if the brick is "left-edge, right-edge" etc.
// Current version: only PEAK and RIGHT {PEAK;RIGHT} get decoded
// In the future it can change to {PEAK;LEFT}
enum BrickPos { PEAK = 1, LEFT = 2, RIGHT = 3, INSIDE = 4 };

typedef struct Brick
{
    int row;  //Informational - can be of help in debugging: to check if the built pyramid correct.
    int brick_pos;
} Brick;

int BuildPyramid(Brick pyramid[], int max_num);
int DecodeMessage(Brick pyramid[], char file_name[]);
void PrintPyramid(Brick pyramid[], int max_index);
