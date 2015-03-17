#pragma once
#include <stdlib.h>

inline bool oddsHit(float odds)
{
	return rand()%100 < odds*100;
}

inline int randomRange(int low, int high)
{
	return (rand() % (high - low + 1)) + low;
}