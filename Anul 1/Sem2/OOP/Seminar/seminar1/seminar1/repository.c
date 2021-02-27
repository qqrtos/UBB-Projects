#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Repository* RepoCreate()
{
	Repository* repo = (Repository*)malloc(1 * sizeof(Repository));
	repo->length = 0;
	return repo;
}

void RepoDestroy(Repository* repo)
{
	free(repo);
}

int findPlanet(Repository* repo, TElem p)
{
	for (int i = 0; i < repo->length; ++i) {
		if (strcmp(getName(&repo->elems[i]), getName(&p)) == 0) {
			return 1;
		}
	}
	return 0;
}

int RepoAddPlanet(Repository* repo, TElem p)
{
	if (findPlanet(repo, p) == 1) {
		return 0;
	}

	repo->elems[repo->length] = p;
	repo->length += 1;

	return 1;
}

void testRepo() {
	Repository* repo = RepoCreate();
	TElem p = CreatePlanet("Pluto", "Still not a planet.", 6.8);
	
	assert(RepoAddPlanet(repo, p) == 1);
	assert(RepoAddPlanet(repo, p) == 0);

	RepoDestroy(repo);
}