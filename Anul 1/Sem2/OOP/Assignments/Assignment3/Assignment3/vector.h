#pragma once
#include "domain.h"

typedef struct {
	void** elements;
	int count;
	int size;
}Vector;

Vector* vector_CreateVector();

Vector* vector_CreateVectorFromArray(void** initialArray, int size);

int vector_AddElement(Vector* vector, void* toBeAdded);

int vector_RemoveElement(Vector* vector, void* toBeRemoved);

int vector_DestroyVector(Vector** vector);