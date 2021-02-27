package Models.Statements;

import Exceptions.MyException;
import Models.ProgramState;
import Models.Types.IType;

public class VariableDeclarationStatement implements IStatement {
    String name;
    IType type;

    @Override
    public String toString() {
        return this.type + " " + this.name + "\n";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }
}
