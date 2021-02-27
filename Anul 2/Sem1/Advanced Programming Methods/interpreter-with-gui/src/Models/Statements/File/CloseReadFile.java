package Models.Statements.File;

import Exceptions.FileException;
import Exceptions.InvalidTypeException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Types.IType;
import Models.Types.StringType;
import Models.Values.IValue;
import Models.Values.StringValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseReadFile implements IStatement {
    private final IExpression expression;

    public CloseReadFile(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        IValue evaluatedExpression = this.expression.evaluate(state.getSymbolTable(), state.getHeap());

        if (!evaluatedExpression.getType().equals(new StringType())) {
            throw new FileException("Cannot open a file of that type.");
        }

        StringValue expressionValue = (StringValue) evaluatedExpression;
        BufferedReader fileReader = state.getFileTable().lookup(expressionValue);
        try {
            fileReader.close();
        } catch (IOException e) {
            throw new FileException(e.getMessage());
        }
        state.getFileTable().remove(expressionValue);

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        if (!this.expression.typeCheck(typeEnvironment).equals(new StringType())){
            throw new InvalidTypeException("Invalid type for a file name.");
        }

        return typeEnvironment;
    }

    @Override
    public String toString() {
        return "CloseReadFile(" + this.expression.toString() + ")";
    }
}
