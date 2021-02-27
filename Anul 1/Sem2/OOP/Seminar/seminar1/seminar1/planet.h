#pragma once
#define NULL ((void*)0)


typedef struct {
	char name[50];
	char type[50];
	double distanceFromEarth;
}Planet;

Planet CreatePlanet(char name[], char type[], double distance);

double GetDistance(Planet p);

char* getName(Planet* p);

void testPlanet();