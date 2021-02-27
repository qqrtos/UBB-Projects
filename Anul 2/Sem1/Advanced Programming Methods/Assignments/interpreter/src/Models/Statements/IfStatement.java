package Models.Statements;

import Exceptions.MyException;
import Models.Expressions.IExpression;
import Models.ProgramState;

public class IfStatement implements IStatement {
    IExpression expression;
    IStatement thenStatement;
    IStatement elseStatement;

    public IfStatement(IExpression exp, IStatement thenStatement, IStatement elseStatement) {
        this.expression = exp;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public String toString() {
        return "(if (" + this.expression.toString() + ")" +
                "\n\t then (" + this.thenStatement.toString() + ")" +
                "\n\t else (" + this.elseStatement.toString() + "))\n";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }
}
