package Models.Expressions;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.Operations.RelationalOperation;
import Models.Heap.Heap;
import Models.Types.BoolType;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.BoolValue;
import Models.Values.IValue;
import Models.Values.IntValue;

public class RelationalExpression implements IExpression {
    private final IExpression leftHandSide;
    private final IExpression rightHandSide;
    private final RelationalOperation sign;

    public RelationalExpression(IExpression leftHandSide, RelationalOperation sign, IExpression rightHandSide) {
        this.leftHandSide = leftHandSide;
        this.rightHandSide = rightHandSide;
        this.sign = sign;
    }

    @Override
    public IValue evaluate(MyDictionary<String, IValue> variablesTable, Heap<IValue> heap) throws RuntimeException {
        IValue lhs, rhs;

        lhs = this.leftHandSide.evaluate(variablesTable, heap);
        if (!lhs.getType().equals(new IntType())) {
            throw new InvalidTypeException("Relational operations can only be done on Integers.");
        }

        rhs = this.rightHandSide.evaluate(variablesTable, heap);
        if (!rhs.getType().equals(new IntType())) {
            throw new InvalidTypeException("Relational operations can only be done on Integers.");
        }

        int i1 = ((IntValue) lhs).getValue();
        int i2 = ((IntValue) rhs).getValue();

        return getValueAfterOperation(i1, this.sign, i2);
    }

    @Override
    public IType typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        var lhsType = this.leftHandSide.typeCheck(typeEnvironment);
        var rhsType = this.rightHandSide.typeCheck(typeEnvironment);

        if (!lhsType.equals(new IntType()) || !rhsType.equals(new IntType())){
            throw new InvalidTypeException("Attempted relational expression between non-integer types.");
        }

        return new BoolType();
    }

    private IValue getValueAfterOperation(int operand1, RelationalOperation sign, int operand2) throws RuntimeException {
        return switch (sign) {
            case LessThan -> new BoolValue(operand1 < operand2);
            case LessThanOrEqual -> new BoolValue(operand1 <= operand2);
            case Equal -> new BoolValue(operand1 == operand2);
            case Different -> new BoolValue(operand1 != operand2);
            case GreaterThan -> new BoolValue(operand1 > operand2);
            case GreaterThanOrEqual -> new BoolValue(operand1 >= operand2);
        };
    }

    @Override
    public String toString() {
        return String.format("%s%s%s", this.leftHandSide, this.sign.getMathematicalSign(), this.rightHandSide);
    }
}
