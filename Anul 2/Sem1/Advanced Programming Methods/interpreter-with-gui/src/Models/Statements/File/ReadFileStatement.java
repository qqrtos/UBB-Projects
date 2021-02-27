package Models.Statements.File;

import Exceptions.FileException;
import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.IType;
import Models.Types.IntType;
import Models.Types.StringType;
import Models.Values.IValue;
import Models.Values.IntValue;
import Models.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStatement implements IStatement {
    private final IExpression expression;
    private final String variableName;

    public ReadFileStatement(IExpression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        if (!state.getSymbolTable().isDefined(this.variableName)) {
            throw new FileException("Variable for which you wanted to read a value is not defined.");
        }

        IValue expressionValue = this.expression.evaluate(state.getSymbolTable(), state.getHeap());
        if (!expressionValue.getType().equals(new StringType())) {
            throw new FileException("Invalid type provided for a file.");
        }

        StringValue file = (StringValue) expressionValue;

        BufferedReader fileReader = state.getFileTable().lookup(file);

        if (fileReader == null) {
            throw new FileException("File is not open.");
        }

        String line = null;
        try {
            line = fileReader.readLine();
        } catch (IOException e) {
            throw new FileException(e.getMessage());
        }
        int readValueToInt = line == null ? 0 : Integer.parseInt(line);
        state.getSymbolTable().update(this.variableName, new IntValue(readValueToInt));

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        var variableType = typeEnvironment.lookup(this.variableName);
        var expressionType = this.expression.typeCheck(typeEnvironment);

        if (!expressionType.equals(new StringType())){
            throw new InvalidTypeException("Invalid type for a file name.");
        }

        if (!variableType.equals(new IntType())){
            throw new InvalidTypeException("Can only read integers from file.");
        }

        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "ReadFile(" + this.expression.toString() + ", " + this.variableName + ")";
    }
}
