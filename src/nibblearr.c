// nibblearr.c

#include "nibblearr.h"

uint8_t nibblearr_get(uint8_t *arr, size_t i)
{
	return (arr[i>>1] >> ((i & 1) << 2)) & 15;
}

void nibblearr_set(uint8_t *arr, size_t i, uint8_t v)
{
	arr[i>>1] &= 15 << ((~i & 1) << 2);
	arr[i>>1] |= (v & 15) << ((i & 1) << 2);
}
