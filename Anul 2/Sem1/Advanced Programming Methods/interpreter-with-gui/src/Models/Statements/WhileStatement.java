package Models.Statements;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Types.BoolType;
import Models.Types.IType;
import Models.Values.BoolValue;

public class WhileStatement implements IStatement {
    private final IExpression expression;
    private final IStatement executionStatement;

    public WhileStatement(IExpression expression, IStatement executionStatement) {
        this.expression = expression;
        this.executionStatement = executionStatement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        var evaluatedExpression = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!evaluatedExpression.getType().equals(new BoolType())){
            throw new InvalidTypeException("While expression does not evaluate to bool.");
        }

        BoolValue expressionValue =(BoolValue)evaluatedExpression;
        if (expressionValue.getValue()){
            state.getExecutionStack().push(new CompoundStatement(this.executionStatement, this));
        }

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        var expressionType = this.expression.typeCheck(typeEnvironment);
        if (!expressionType.equals(new BoolType())){
            throw new InvalidTypeException("Condition in 'while' statement doesn't evaluate to bool.");
        }
        this.executionStatement.typeCheck(typeEnvironment.deepCopy());
        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "(While(" + this.expression.toString() + ") " + this.executionStatement.toString() + ")";
    }
}
