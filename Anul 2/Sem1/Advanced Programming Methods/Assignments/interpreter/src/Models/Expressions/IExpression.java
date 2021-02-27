package Models.Expressions;

import Exceptions.MyException;
import Models.ADTs.MyDictionary.IMyDictionary;
import Models.Values.IValue;

public interface IExpression {
    IValue evaluate(IMyDictionary<String, IValue> variablesTable) throws MyException;
}
