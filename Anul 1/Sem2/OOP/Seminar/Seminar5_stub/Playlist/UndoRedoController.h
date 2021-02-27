#pragma once
#include <stack>
#include <memory>
#include "Action.h"
#include "ActionAdd.h"
#include "ActionRemove.h"

class UndoRedoController {
private:
	Repository& repository;
	std::stack<std::shared_ptr<Action>> undoStack{}, redoStack{};;

public:
	UndoRedoController(Repository& repository) : repository{ repository } {}

	void addUndoAction(Action* undoAction);

	void addRedoAction(Action* redoAction);

	void undo();

	void redo();
};

