#pragma once
#include "repository.h"

typedef struct {
	Repository* repo;
}Service;

Service* ServiceCreate(Repository* repo);

void ServiceDestroy(Service* serv);

void ServiceAddPlanet(Service* serv, char* name, char* type, double dist);
