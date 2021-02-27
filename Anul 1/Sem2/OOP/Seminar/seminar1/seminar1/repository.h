#pragma once
#include "planet.h"

#define MAX_DIM 50

typedef Planet TElem;

typedef struct {
	TElem elems[MAX_DIM];
	int length;
}Repository;

Repository* RepoCreate();

void RepoDestroy(Repository* repo);

/*
	Adds a planet to the repository.
	Input: repo -> pointer to Repository
		   p -> planet
	Output: 1 if planet was added succesfully
		    0 otherwise
*/
int RepoAddPlanet(Repository* repo, Planet p);

/*
	Search for a planet in the repository.
	Input: repo -> pointer to repository
		  p -> planet to search
	Output: 1 -> planet was found
		    0 -> otherwise
*/
int findPlanet(Repository* repo, Planet p);

void testRepo();