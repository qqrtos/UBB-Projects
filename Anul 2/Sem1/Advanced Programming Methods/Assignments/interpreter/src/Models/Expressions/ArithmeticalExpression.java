package Models.Expressions;

import Exceptions.MyException;
import Models.ADTs.MyDictionary.IMyDictionary;
import Models.Expressions.Operations.ArithmeticalOperation;
import Models.Types.IntType;
import Models.Values.IValue;
import Models.Values.IntValue;

public class ArithmeticalExpression implements IExpression {
    IExpression expression1;
    IExpression expression2;
    ArithmeticalOperation sign;

    //TODO: implement constructor and toString()

    @Override
    public IValue evaluate(IMyDictionary<String, IValue> variablesTable) throws MyException {
        IValue val1, val2;
        val1 = expression1.evaluate(variablesTable);

        if (val1.getType().equals(new IntType())) {
            val2 = expression2.evaluate(variablesTable);
            if (val2.getType().equals(new IntType())) {
                IntValue i1 = (IntValue) val1;
                IntValue i2 = (IntValue) val2;
                int n1 = i1.getValue(), n2 = i2.getValue();
                return this.getValueAfterOperation(n1, n2, this.sign);
            } else {
                throw new MyException("Second operand is not an integer.");
            }
        } else {
            throw new MyException("First operand is not an integer.");
        }
    }

    private IValue getValueAfterOperation(int operand1, int operand2, ArithmeticalOperation sign) throws MyException {
        if (operand2 == 0 && sign == ArithmeticalOperation.Division) {
            throw new MyException("Division by zero.");
        }

        return switch (this.sign) {
            case Addition -> new IntValue(operand1 + operand2);
            case Subtraction -> new IntValue(operand1 - operand2);
            case Multiplication -> new IntValue(operand1 * operand2);
            case Division -> new IntValue(operand1 / operand2);
        };
    }
}
