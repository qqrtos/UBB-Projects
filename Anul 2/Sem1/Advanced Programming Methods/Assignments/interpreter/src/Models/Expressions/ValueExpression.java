package Models.Expressions;

import Exceptions.MyException;
import Models.ADTs.MyDictionary.IMyDictionary;
import Models.Values.IValue;

public class ValueExpression implements IExpression {
    IValue value;

    @Override
    public IValue evaluate(IMyDictionary<String, IValue> variablesTable) throws MyException {
        return this.value;
    }
}
