package Models.Expressions;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.Heap.Heap;
import Models.Types.IType;
import Models.Values.IValue;

public class VariableExpression implements IExpression {
    private final String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    @Override
    public IValue evaluate(MyDictionary<String, IValue> variablesTable, Heap<IValue> heap) throws RuntimeException {
        return variablesTable.lookup(this.id);
    }

    @Override
    public IType typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        return typeEnvironment.lookup(this.id);
    }

    @Override
    public String toString() {
        return String.format("%s", this.id);
    }
}
