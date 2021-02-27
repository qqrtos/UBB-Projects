package Models.Statements;

import Models.ADTs.MyDictionary.MyDictionary;
import Models.ADTs.MyStack.MyStack;
import Models.ProgramState;
import Models.Types.IType;

import java.util.concurrent.atomic.AtomicInteger;

public class ForkStatement implements IStatement {
    private final IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        var newExecutionStack = new MyStack<IStatement>();
        newExecutionStack.push(this.statement);
        var newId = new AtomicInteger(ProgramState.getNewId().get());

        return new ProgramState(
                newId,
                newExecutionStack,
                state.getSymbolTable().deepCopy(),
                state.getOutputList(),
                state.getFileTable(),
                state.getHeap(),
                state.getLatchTable());
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        this.statement.typeCheck(typeEnvironment.deepCopy());
        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "Fork(" + this.statement.toString() + ")";
    }
}
