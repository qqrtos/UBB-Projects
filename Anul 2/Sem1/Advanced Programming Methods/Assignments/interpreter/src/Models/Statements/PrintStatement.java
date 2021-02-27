package Models.Statements;

import Exceptions.MyException;
import Models.Expressions.IExpression;
import Models.ProgramState;

public class PrintStatement implements IStatement {
    IExpression expression;

    @Override
    public String toString(){
        return "print ("+this.expression.toString()+")\n";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }
}
