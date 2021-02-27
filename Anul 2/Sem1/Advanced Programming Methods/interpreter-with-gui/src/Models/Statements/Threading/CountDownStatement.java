package Models.Statements.Threading;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IntValue;

public class CountDownStatement implements IStatement {
    private final String variableId;

    public CountDownStatement(String variableId) {
        this.variableId = variableId;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException, InterruptedException {
        var foundIndex = state.getSymbolTable().lookup(this.variableId);
        if(!foundIndex.getType().equals(new IntType())){
            throw new InvalidTypeException("Type of the CountDown variable is not Integer");
        }

        var variableValue = state.getLatchTable().lookup(((IntValue)foundIndex).getValue());
        if(state.getLatchTable().lookup(variableValue) > 0){
            state.getLatchTable().update(((IntValue) foundIndex).getValue(), variableValue - 1);
        }

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        if(!typeEnvironment.lookup(this.variableId).equals(new IntType())){
            throw new InvalidTypeException("Invalid type for the countDown variable");
        }

        return typeEnvironment;
    }

    @Override
    public String toString(){
        return "CountDown("+this.variableId+")";
    }
}
