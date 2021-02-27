#include "vector.h"
#include <stdlib.h>
#define INITIAL_VECTOR_SIZE 2

void resize(Vector** vector) {
	(*vector)->elements = (void*)realloc((*vector)->elements, 2 * (*vector)->size * sizeof(void*));
	(*vector)->size *= 2;
}

Vector* vector_CreateVector() {
	Vector* vector = (Vector*)malloc(1*sizeof(Vector));

	vector->elements = (void**)malloc(INITIAL_VECTOR_SIZE * sizeof(void*));
	vector->size = INITIAL_VECTOR_SIZE;
	vector->count = 0;

	return vector;
}

Vector* vector_CreateVectorFromArray(void** initialArray, int size)
{
	Vector* vector = (Vector*)malloc(1 * sizeof(Vector));

	vector->elements = (void**)malloc((size + 1) * sizeof(void*));
	vector->size = size + 1;
	vector->count = size;

	return vector;
}

int vector_AddElement(Vector* vector, void* toBeAdded) {
	if (vector->count >= vector->size - 1) {
		resize(&vector);
	}

	vector->elements[vector->count++] = toBeAdded;

	return SUCCESS_CODE;
}

int vector_RemoveElement(Vector* vector, void* toBeRemoved) {
	for (int i = 0; i < vector->count; ++i) {
		if (vector->elements[i] == toBeRemoved) {

			for (int j = i; j < vector->count - 1; ++j) {
				vector->elements[j] = vector->elements[j + 1];
			}

			free(toBeRemoved);
			--vector->count;
			return SUCCESS_CODE;
		}
	}

	return ERROR_CODE;
}

int vector_DestroyVector(Vector** vector) {
	for (int i = 0; i < (*vector)->count; ++i) {
		free((*vector)->elements[i]);
	}

	free((*vector)->elements);
	free(*vector);
	*vector = NULL;

	return SUCCESS_CODE;
}
