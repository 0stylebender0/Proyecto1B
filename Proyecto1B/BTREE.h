#pragma once
#include "Lista.h"

#define MAX 4
#define MIN 2

struct NodoBtree {
	int val[MAX + 1], count;
	NodoBtree* link[MAX + 1];
};