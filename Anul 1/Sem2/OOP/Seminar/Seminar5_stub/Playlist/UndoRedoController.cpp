#include "UndoRedoController.h"

void UndoRedoController::addUndoAction(Action* undoAction) {
	this->undoStack.push(std::make_shared<Action>(undoAction));
}

void UndoRedoController::addRedoAction(Action* redoAction) {
	this->redoStack.push(std::make_shared<Action>(redoAction));
}

void UndoRedoController::undo() {
	if (!this->undoStack.empty()) {
		this->undoStack.top().get()->executeUndo();
		this->redoStack.push(this->undoStack.top());
		this->undoStack.pop();
	}
}

void UndoRedoController::redo() {
	if (!this->redoStack.empty()) {
		this->redoStack.top().get()->executeRedo();
		this->redoStack.pop();
	}
}


