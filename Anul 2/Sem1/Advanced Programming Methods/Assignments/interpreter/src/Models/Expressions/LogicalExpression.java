package Models.Expressions;

import Exceptions.MyException;
import Models.ADTs.MyDictionary.IMyDictionary;
import Models.Expressions.Operations.LogicalOperation;
import Models.Values.IValue;

public class LogicalExpression implements IExpression {
    IExpression expression1;
    IExpression expression2;
    LogicalOperation sign;

    @Override
    public IValue evaluate(IMyDictionary<String, IValue> variablesTable) throws MyException {
        //TODO: same as arithmetical expression but with bool.
        return null;
    }
}
