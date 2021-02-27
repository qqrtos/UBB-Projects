package Models.Statements.Heap;

import Exceptions.HeapException;
import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.BoolType;
import Models.Types.IType;
import Models.Types.ReferenceType;
import Models.Values.IValue;
import Models.Values.ReferenceValue;

public class WriteToHeapStatement implements IStatement {
    private final String variableName;
    private final IExpression expression;

    public WriteToHeapStatement(String variableName, IExpression expression) {
        this.variableName = variableName;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        IValue variableValue = state.getSymbolTable().lookup(this.variableName);
        if (!(variableValue.getType() instanceof ReferenceType)) {
            throw new InvalidTypeException("Attempt to write to heap a variable of invalid type."); //TODO: complete this
        }

        ReferenceValue variableReferenceValue = (ReferenceValue) variableValue;
        if (state.getHeap().isAvailableSpot(variableReferenceValue.getAddress())) {
            throw new HeapException("MEMORY ACCESS VIOLATION!!!!!!!!!!!!!");
        }

        IValue evaluatedExpression = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!evaluatedExpression.getType().equals(variableReferenceValue.getReferencedType())) {
            throw new InvalidTypeException("Wrong type of referenced variable."); //TODO: complete this
        }

        state.getHeap().update(variableReferenceValue.getAddress(), evaluatedExpression);
        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        var variableType = typeEnvironment.lookup(this.variableName);
        var expressionType = this.expression.typeCheck(typeEnvironment);

        if (!(variableType instanceof ReferenceType)){
            throw new InvalidTypeException("Invalid type of variable for heap writing operation.");
        }

        if (!expressionType.equals(((ReferenceType)variableType).getInnerType())){
            throw new InvalidTypeException(""); //TODO: complete this
        }

        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "Write(" + this.variableName + ", " + this.expression.toString() + ")";
    }
}
