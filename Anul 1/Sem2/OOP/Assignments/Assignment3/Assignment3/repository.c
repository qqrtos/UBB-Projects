#include "repository.h"

///Check if an element is already in the repo. Return the index if it's there, -1 otherwise.
int searchElement(Repository* repository, void* element) {
	for (int index = 0; index < repository->vector->count; ++index) {
		if (repository->vector->elements[index] == element) {
			return index;
		}
	}
	return ERROR_CODE;
}

Repository* repository_CreateRepository() {
	Repository* repository = (Repository*)malloc(1 * sizeof(Repository));
	repository->vector = vector_CreateVector();
	return repository;
}

Vector* repository_GetAllElemets(Repository* repository) {
	return repository->vector;
}

void repository_ReplaceRepositoryList(Repository* repository, Vector* newList) {
	repository->vector = newList;
}

int repository_StoreElement(Repository* repository, void* toBeAdded) {
	if (ERROR_CODE != searchElement(repository, toBeAdded)) {
		///Element already in repo.
		return ERROR_CODE;
	}

	vector_AddElement(repository->vector, toBeAdded);

	return SUCCESS_CODE;
}

int repository_RemoveElement(Repository* repository, void* toBeRemoved) {
	if (ERROR_CODE == searchElement(repository, toBeRemoved)) {
		///Element not in repo.
		return ERROR_CODE;
	}

	vector_RemoveElement(repository->vector, toBeRemoved);

	return SUCCESS_CODE;
}

int repository_UpdateElement(Repository* repository, void* toBeReplaced, void* newElement) {
	for (int index = 0; index < repository->vector->size; ++index) {
		if (repository->vector->elements[index] == toBeReplaced) {
			repository->vector->elements[index] = newElement;
			return SUCCESS_CODE;
		}
	}

	///Element not in repo.
	return ERROR_CODE;
}

int repository_DestroyRepository(Repository* repository) {
	vector_DestroyVector(&repository->vector);
	free(repository);

	return SUCCESS_CODE;
}

