package Models.Statements.Heap;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.IType;
import Models.Types.ReferenceType;
import Models.Values.IValue;
import Models.Values.ReferenceValue;

public class NewAllocationStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public NewAllocationStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        var variableType = state.getSymbolTable().lookup(this.variableName).getType();
        if (!(variableType instanceof ReferenceType)) {
            throw new InvalidTypeException("Attempt to allocate to heap a variable of invalid type."); //TODO: complete this
        }
        var variable = (ReferenceValue) state.getSymbolTable().lookup(this.variableName);

        IValue evaluatedExpression = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        IType evaluatedExpressionType = this.expression.evaluate(state.getSymbolTable(), state.getHeap()).getType();
        if (!evaluatedExpressionType.equals(variable.getReferencedType())) {
            throw new InvalidTypeException("Wrong type of referenced variable."); //TODO: complete this
        }

        int newAddress = state.getHeap().allocate(evaluatedExpression);
        variable.setAddress(newAddress);
        variable.setReferencedType(evaluatedExpressionType);
        state.getSymbolTable().update(this.variableName, variable);

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        var variableType = typeEnvironment.lookup(this.variableName);
        var expressionType = this.expression.typeCheck(typeEnvironment);

        if (!variableType.equals(new ReferenceType(expressionType))){
            throw new InvalidTypeException(""); //TODO: this message.
        }

        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "New(" + this.variableName + ", " + this.expression.toString() + ")";
    }
}
