package Models.Statements;

import Exceptions.MyException;
import Models.ProgramState;

public class NopStatement implements IStatement {
    @Override
    public String toString() {
        return "Nop statement.\n";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return state;
    }
}
