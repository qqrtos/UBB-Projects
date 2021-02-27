package Models.Expressions;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Heap.Heap;
import Models.Types.IType;
import Models.Types.ReferenceType;
import Models.Values.IValue;
import Models.Values.ReferenceValue;

public class ReadHeapExpression implements IExpression {
    private final IExpression expression;

    public ReadHeapExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue evaluate(MyDictionary<String, IValue> variablesTable, Heap<IValue> heap) throws RuntimeException {
        IValue evaluatedExpression = this.expression.evaluate(variablesTable, heap);
        if (!(evaluatedExpression instanceof ReferenceValue)) {
            throw new InvalidTypeException("Can not read the heap for this expression.");
        }

        ReferenceValue variableReference = (ReferenceValue) evaluatedExpression;
        return heap.getValueAtAddress(variableReference.getAddress());
    }

    @Override
    public IType typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        IType type = this.expression.typeCheck(typeEnvironment);

        if (!(type instanceof ReferenceType)){
            throw new InvalidTypeException("Attempted read heap using non-reference type.");
        }

        return ((ReferenceType)type).getInnerType();
    }

    @Override
    public String toString() {
        return "ReadHeap(" + this.expression.toString() + ")";
    }
}
