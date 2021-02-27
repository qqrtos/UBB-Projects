package Models.Statements;

import Exceptions.InvalidTypeException;
import Exceptions.UndefinedVariableException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Types.IType;
import Models.Values.IValue;

public class AssignmentStatement implements IStatement {
    private final String id;
    private final IExpression expression;

    public AssignmentStatement(String id, IExpression expression) {
        this.id = id;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        MyDictionary<String, IValue> symbolTable = state.getSymbolTable();

        if (!symbolTable.isDefined(this.id)) {
            throw new UndefinedVariableException("The used variable `" + this.id + "` was not declared.");
        }

        IValue value = this.expression.evaluate(symbolTable, state.getHeap());
        IType definedType = (symbolTable.lookup(this.id)).getType();

        if (!value.getType().equals(definedType)) {
            throw new InvalidTypeException("Declared type of the variable `" + this.id + "` and the assigned type don't match.");
        }

        symbolTable.update(this.id, value);

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        IType variableType = typeEnvironment.lookup(this.id);
        IType expressionType = this.expression.typeCheck(typeEnvironment);

        if (!variableType.equals(expressionType)) {
            throw new InvalidTypeException("Assigned type doesn't match variable type.");
        }

        return typeEnvironment;
    }

    @Override
    public String toString() {
        return this.id + "=" + this.expression.toString();
    }
}
