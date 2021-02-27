#include "tests.h"
#include <assert.h>
#include "controller.h"
#include "repository.h"
#include <string.h>


//#################################################################//


void repository_StoreElement__ValidInput__ElementAdded() {
	Repository* r = repository_CreateRepository();

	Bot* el = createNewBot(1, "good", "cleaning", 3);
	assert(SUCCESS_CODE == repository_StoreElement(r, el));

	double* el2 = (double*)malloc(1 * sizeof(double));
	*el2 = 2.5;
	assert(SUCCESS_CODE == repository_StoreElement(r, el2));

	repository_DestroyRepository(r);
}

void repository_StoreElement__DuplicateID__ReturnsError() {
	Repository* r = repository_CreateRepository();

	Bot* el = createNewBot(1, "dolphin", "jumping", 5);
	repository_StoreElement(r, el);

	Bot* el2 = createNewBot(1, "elephant", "trumpet", 2);

	assert(ERROR_CODE == repository_StoreElement(r, el));

	free(el2);
	repository_DestroyRepository(r);
}

void repository_UpdateElement__NonexistentElement__ReturnsError() {
	Repository* r = repository_CreateRepository();

	Bot* el = createNewBot(1, "no state", "not special", 5);

	Bot* el2 = createNewBot(2, "state", "special", 6);

	assert(ERROR_CODE == repository_UpdateElement(r, el, el2));

	free(el);
	free(el2);
	repository_DestroyRepository(r);
}

void repository_UpdateElement__ValidElement__ElementUpdated() {
	Repository* r = repository_CreateRepository();

	Bot* el = createNewBot(1, "no state", "not special", 5);
	repository_StoreElement(r, el);

	Bot* el2 = createNewBot(1, "state", "special", 10);

	assert(SUCCESS_CODE == repository_UpdateElement(r, el, el2));

	free(el);
	repository_DestroyRepository(r);
}

void repository_RemoveElement__NonexistentElement__ReturnsError() {
	Repository* r = repository_CreateRepository();

	Bot* el = createNewBot(2, "no state", "not special", 5);
	repository_StoreElement(r, el);

	Bot* el2 = createNewBot(1, "state", "special", 5);

	assert(ERROR_CODE == repository_RemoveElement(r, el2));

	assert(r->vector->count == 1);

	free(el2);
	repository_DestroyRepository(r);
}

void repository_RemoveElement__ValidElement__ElementRemoved() {
	Repository* r = repository_CreateRepository();

	Bot* el = createNewBot(1, "no state", "not special", 5);
	repository_StoreElement(r, el);

	assert(SUCCESS_CODE == repository_RemoveElement(r, el));

	assert(r->vector->count == 0);

	repository_DestroyRepository(r);
}

void test_repository() {
	repository_StoreElement__ValidInput__ElementAdded();
	repository_StoreElement__DuplicateID__ReturnsError();
	repository_UpdateElement__NonexistentElement__ReturnsError();
	repository_UpdateElement__ValidElement__ElementUpdated();
	repository_RemoveElement__NonexistentElement__ReturnsError();
}


//#################################################################//


void controller_UndoOperation_HistoryOfChanges__UndoStore__Success() {
	Repository* r = repository_CreateRepository();
	Controller* c = controller_CreateController(r);

	controller_StoreBot(c, 1, "this", "that", 5);

	controller_UndoOperation_HistoryOfChanges(c);

	assert(c->repository->vector->count == 0);

	controller_DestroyController(c);
}

void controller_UndoOperation_HistoryOfChanges__UndoStore__NoMoreUndos() {
	Repository* r = repository_CreateRepository();
	Controller* c = controller_CreateController(r);

	controller_StoreBot(c, 1, "this", "that", 5);

	controller_UndoOperation_HistoryOfChanges(c);

	assert(ERROR_CODE == controller_UndoOperation_HistoryOfChanges(c));

	controller_DestroyController(c);
}

void controller_UndoOperation_HistoryOfChanges__UndoRemove__Success() {
	Repository* r = repository_CreateRepository();
	Controller* c = controller_CreateController(r);

	controller_StoreBot(c, 1, "this", "that", 5);
	controller_RemoveBot(c, 1);

	controller_UndoOperation_HistoryOfChanges(c);

	assert(((Bot*)c->repository->vector->elements[0])->ID == 1);
	assert(c->repository->vector->count == 1);

	controller_DestroyController(c);
}

void controller_UndoOperation_HistoryOfChanges__UndoRemove__NoMoreUndos() {
	Repository* r = repository_CreateRepository();
	Controller* c = controller_CreateController(r);

	controller_StoreBot(c, 1, "this", "that", 5);
	controller_RemoveBot(c, 1);

	controller_UndoOperation_HistoryOfChanges(c);
	controller_UndoOperation_HistoryOfChanges(c);

	assert(ERROR_CODE == controller_UndoOperation_HistoryOfChanges(c));

	controller_DestroyController(c);
}


void test_controller() {
	controller_UndoOperation_HistoryOfChanges__UndoStore__Success();
	controller_UndoOperation_HistoryOfChanges__UndoStore__NoMoreUndos();
	controller_UndoOperation_HistoryOfChanges__UndoRemove__Success();
	controller_UndoOperation_HistoryOfChanges__UndoRemove__NoMoreUndos();
}


//#################################################################//