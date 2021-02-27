package Models.Statements;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.ProgramState;
import Models.Types.IType;

public interface IStatement {
    ProgramState execute(ProgramState state) throws RuntimeException, InterruptedException;

    MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException;
}
