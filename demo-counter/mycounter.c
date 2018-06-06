#include "mycounter.h"


int next_counter(int current)
{
    if(current>99)
        current = 1;
    else
        current++;

    return current;
}