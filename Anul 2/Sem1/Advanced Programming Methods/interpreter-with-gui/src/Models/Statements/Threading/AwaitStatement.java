package Models.Statements.Threading;

import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Values.IntValue;

public class AwaitStatement implements IStatement {
    private final String variableId;

    public AwaitStatement(String variableId) {
        this.variableId = variableId;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException, InterruptedException {
        var findIndex = state.getSymbolTable().lookup(this.variableId);
        if(!findIndex.getType().equals(new IntType())){
            throw new InvalidTypeException("Type of the await variable is not Integer");
        }

        if(state.getLatchTable().lookup(((IntValue) findIndex).getValue()) != 0){
            // do smth to await the countdown variable.
            state.getExecutionStack().push(this);
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
        return "Await("+this.variableId+")";
    }
}
