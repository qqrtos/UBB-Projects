package Models.Statements;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.ADTs.MyList.MyList;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Types.IType;
import Models.Values.IValue;

public class PrintStatement implements IStatement {
    private final IExpression expression;

    public PrintStatement(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public String toString() {
        return "print (" + this.expression.toString() + ")";
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        MyList<IValue> outputList = state.getOutputList();
        outputList.add(expression.evaluate(state.getSymbolTable(), state.getHeap()));
        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        this.expression.typeCheck(typeEnvironment);
        return typeEnvironment;
    }
}
