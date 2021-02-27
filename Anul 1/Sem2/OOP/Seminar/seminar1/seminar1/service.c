#include "service.h"
#include <stdlib.h>

Service* ServiceCreate(Repository* repo)
{
	Service* serv = (Service*)malloc(1 * sizeof(Service));
	serv->repo = repo;
	return serv;
}

void ServiceDestroy(Service* serv)
{
	free(serv);
}

void ServiceAddPlanet(Service* serv, char* name, char* type, double dist)
{
	Planet p = CreatePlanet(name, type, dist);
	RepoAddPlanet(serv->repo, p);
}
