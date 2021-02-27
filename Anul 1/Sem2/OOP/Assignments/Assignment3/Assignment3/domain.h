#pragma once
#define ERROR_CODE -1
#define SUCCESS_CODE 0

typedef struct {
	int ID;
	char state[32];
	char specialization[32];
	int energyCapacity;
}Bot;

typedef struct {
	Bot* newBot;
	Bot* oldBot;
	void* function;
}Operation;