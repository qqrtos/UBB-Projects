package Models.Statements;

import Exceptions.MyException;
import Models.ProgramState;

public interface IStatement {
    ProgramState execute(ProgramState state) throws MyException;
}
