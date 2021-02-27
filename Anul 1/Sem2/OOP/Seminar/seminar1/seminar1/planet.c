#include "planet.h"
#include <string.h>
#include <assert.h>

Planet CreatePlanet(char name[], char type[], double distance)
{
	Planet newPlanet;
	newPlanet.distanceFromEarth = distance;
	strcpy(newPlanet.name, name);
	strcpy(newPlanet.type, type);
	return newPlanet;
}

double GetDistance(Planet p)
{
	return p.distanceFromEarth;
}

char* getName(Planet* p)
{
	return p->name;
}

void testPlanet()
{
	Planet p = CreatePlanet("Pluto", "Not a planet", 5.5);
	assert(GetDistance(p) == 5.5);
	assert(strcmp(getName(&p), "Pluto") == 0);
}
