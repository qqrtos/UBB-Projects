package Models.Statements;

import Exceptions.MyException;
import Models.ADTs.MyStack.IMyStack;
import Models.ProgramState;

public class CompoundStatement implements IStatement {
    IStatement first;
    IStatement second;

    @Override
    public String toString() {
        return "(" + this.first.toString() + ";" + this.second.toString() + ")\n";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IMyStack<IStatement> stack = state.getStack();
        stack.push(this.second);
        stack.push(this.first);
        return state;
    }
}
