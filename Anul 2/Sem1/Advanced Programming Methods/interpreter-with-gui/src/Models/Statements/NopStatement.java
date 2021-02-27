package Models.Statements;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.ProgramState;
import Models.Types.IType;

public class NopStatement implements IStatement {
    @Override
    public String toString() {
        return "Nop";
    }

    @Override
    public ProgramState execute(ProgramState state) {
        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        return typeEnvironment;
    }
}
