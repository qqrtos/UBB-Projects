package Models.Statements;

import Exceptions.VariableAlreadyDeclaredException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.ProgramState;
import Models.Types.BoolType;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Types.StringType;
import Models.Values.*;

public class VariableDeclarationStatement implements IStatement {
    private final String name;
    private final IType type;

    public VariableDeclarationStatement(String name, IType type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public String toString() {
        return this.type + " " + this.name;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        MyDictionary<String, IValue> symbolTable = state.getSymbolTable();

        if (symbolTable.isDefined(this.name)) {
            throw new VariableAlreadyDeclaredException("Variable is already declared.");
        }

        symbolTable.put(this.name, this.type.defaultValue());

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        typeEnvironment.put(this.name, this.type);
        return typeEnvironment;
    }
}
