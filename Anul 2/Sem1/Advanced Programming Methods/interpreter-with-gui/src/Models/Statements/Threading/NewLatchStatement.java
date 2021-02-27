package Models.Statements.Threading;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IntValue;

import java.util.concurrent.atomic.AtomicInteger;

public class NewLatchStatement implements IStatement {
    private final String variableId;
    private final IExpression expression;
    public static AtomicInteger freeLocation = new AtomicInteger(0);

    public NewLatchStatement(String variableId,
                             IExpression expression) {
        this.variableId = variableId;
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        var num1 = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!num1.getType().equals(new IntType())) {
            throw new InvalidTypeException("Type of the expression for a new countDownLatch is not an integer.");
        }
        synchronized (state.getLatchTable()) {
            if (!state.getSymbolTable().lookup(this.variableId).getType().equals(new IntType())){
                throw new InvalidTypeException("Variable of the countDownLatch is not an Integer.");
            }
            state.getLatchTable().put(NewLatchStatement.freeLocation.get(), ((IntValue) num1).getValue());
            state.getSymbolTable().update(this.variableId, new IntValue(NewLatchStatement.freeLocation.get()));
        }
        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        if(!typeEnvironment.lookup(this.variableId).equals(new IntType())){
            throw new InvalidTypeException("Invalid type of countDown variable.");
        }

        if(!this.expression.typeCheck(typeEnvironment).equals(new IntType())){
            throw new InvalidTypeException("Invalid type assigned to the countDown variable.");
        }

        return typeEnvironment;
    }

    @Override
    public String toString(){
        return "NewLatch("+this.variableId+", "+this.expression+")";
    }
}
