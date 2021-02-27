#pragma once
#include "vector.h"

typedef struct {
	Vector* vector;
}Repository;

Repository* repository_CreateRepository();

Vector* repository_GetAllElemets(Repository* repository);

void repository_ReplaceRepositoryList(Repository* repository, Vector* newList);

int repository_StoreElement(Repository* repository, void* element);

int repository_RemoveElement(Repository* repository, void* toBeRemoved);

int repository_UpdateElement(Repository* repository, void* toBeReplaced, void* newElement);

int repository_DestroyRepository(Repository* repository);