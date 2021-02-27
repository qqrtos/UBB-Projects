package Models.Expressions;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.Heap.Heap;
import Models.Types.IType;
import Models.Values.IValue;

public interface IExpression {
    IValue evaluate(MyDictionary<String, IValue> variablesTable, Heap<IValue> heap) throws RuntimeException;

    IType typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException;
}
