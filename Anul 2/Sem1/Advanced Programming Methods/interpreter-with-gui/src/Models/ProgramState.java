package Models;

import Exceptions.EmptyCollectionException;
import Models.ADTs.LatchTable;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.ADTs.MyList.MyList;
import Models.ADTs.MyStack.MyStack;
import Models.Heap.Heap;
import Models.Statements.IStatement;
import Models.Values.IValue;
import Models.Values.StringValue;

import java.io.BufferedReader;
import java.util.concurrent.atomic.AtomicInteger;

public class ProgramState {
    private static final AtomicInteger id = new AtomicInteger(1);
    private final MyStack<IStatement> executionStack;
    private final MyDictionary<String, IValue> symbolTable;
    private final MyList<IValue> outputList;
    private final MyDictionary<StringValue, BufferedReader> fileTable;
    private final Heap<IValue> heap;
    private final LatchTable latchTable;
    private final AtomicInteger currentProgramId;


    public ProgramState(AtomicInteger currentProgramId,
                        MyStack<IStatement> stack,
                        MyDictionary<String, IValue> table,
                        MyList<IValue> output,
                        MyDictionary<StringValue, BufferedReader> fileTable,
                        Heap<IValue> heap,
                        LatchTable latchTable) {
        this.executionStack = stack;
        this.symbolTable = table;
        this.outputList = output;
        this.fileTable = fileTable;
        this.heap = heap;
        this.currentProgramId = currentProgramId;
        this.latchTable = latchTable;
        id.set(currentProgramId.get());
    }

    public static synchronized AtomicInteger getNewId() {
        return new AtomicInteger(id.addAndGet(1));
    }

    public synchronized AtomicInteger getId() {
        return new AtomicInteger(this.currentProgramId.get());
    }

    public MyDictionary<String, IValue> getSymbolTable() {
        return this.symbolTable;
    }

    public MyStack<IStatement> getExecutionStack() {
        return this.executionStack;
    }

    public MyList<IValue> getOutputList() {
        return this.outputList;
    }

    public MyDictionary<StringValue, BufferedReader> getFileTable() {
        return this.fileTable;
    }

    public LatchTable getLatchTable() {
        return this.latchTable;
    }

    public Heap<IValue> getHeap() {
        return this.heap;
    }

    public boolean isNotCompleted() {
        return !this.executionStack.isEmpty();
    }

    public ProgramState executeOneInstruction() throws RuntimeException, InterruptedException {
        if (this.executionStack.isEmpty()) {
            throw new EmptyCollectionException("Execution stack is empty");
        }

        IStatement currentStatement = this.executionStack.pop();
        return currentStatement.execute(this);
    }

    @Override
    public String toString() {
        return "========== ID: " + this.currentProgramId.toString() + " ==========\n" +
                "========== Execution stack ==========\n" + this.executionStack + "\n" +
                "========== Symbol table ==========\n" + this.symbolTable + "\n" +
                "========== File table ==========\n" + this.fileTable + "\n" +
                "========== Output list ==========\n" + this.outputList + "\n" +
                "========== Heap ==========\n" + this.heap + "\n\n";
    }
}
