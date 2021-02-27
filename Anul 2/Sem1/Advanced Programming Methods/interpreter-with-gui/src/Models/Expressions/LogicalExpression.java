package Models.Expressions;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.Operations.LogicalOperation;
import Models.Heap.Heap;
import Models.Types.BoolType;
import Models.Types.IType;
import Models.Values.BoolValue;
import Models.Values.IValue;

public class LogicalExpression implements IExpression {
    private final IExpression leftHandSide;
    private final IExpression rightHandSide;
    private final LogicalOperation sign;

    public LogicalExpression(IExpression lhs, IExpression rhs, LogicalOperation sign) {
        this.leftHandSide = lhs;
        this.rightHandSide = rhs;
        this.sign = sign;
    }

    @Override
    public IValue evaluate(MyDictionary<String, IValue> variablesTable, Heap<IValue> heap) throws RuntimeException {
        IValue lhs, rhs;

        lhs = this.leftHandSide.evaluate(variablesTable, heap);
        if (!lhs.getType().equals(new BoolType())) {
            throw new InvalidTypeException("Left hand side is not a boolean value.");
        }

        rhs = this.rightHandSide.evaluate(variablesTable, heap);
        if (!rhs.getType().equals(new BoolType())) {
            throw new InvalidTypeException("Right hand side is not a boolean value");
        }

        boolean b1 = ((BoolValue) lhs).getValue();
        boolean b2 = ((BoolValue) rhs).getValue();

        return this.getValueAfterOperation(b1, this.sign, b2);
    }

    @Override
    public IType typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        var lhsType = this.leftHandSide.typeCheck(typeEnvironment);
        var rhsType = this.rightHandSide.typeCheck(typeEnvironment);

        if (!lhsType.equals(new BoolType()) || !rhsType.equals(new BoolType())){
            throw new InvalidTypeException("Attempted logical expression between non-boolean types.");
        }

        return new BoolType();
    }

    private IValue getValueAfterOperation(boolean lhs, LogicalOperation sign, boolean rhs) {
        return switch (sign) {
            case And -> new BoolValue(lhs && rhs);
            case Or -> new BoolValue(rhs || lhs);
        };
    }

    @Override
    public String toString() {
        return String.format("%s %s %s", this.leftHandSide, this.sign.getMathematicalSign(), this.leftHandSide);
    }
}
