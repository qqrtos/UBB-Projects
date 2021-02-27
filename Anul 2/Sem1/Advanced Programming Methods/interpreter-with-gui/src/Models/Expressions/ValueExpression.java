package Models.Expressions;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.Heap.Heap;
import Models.Types.IType;
import Models.Values.IValue;

public class ValueExpression implements IExpression {
    private final IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public IValue evaluate(MyDictionary<String, IValue> variablesTable, Heap<IValue> heap) {
        return this.value;
    }

    @Override
    public IType typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        return this.value.getType();
    }

    @Override
    public String toString() {
        return String.format("%s", this.value);
    }
}
