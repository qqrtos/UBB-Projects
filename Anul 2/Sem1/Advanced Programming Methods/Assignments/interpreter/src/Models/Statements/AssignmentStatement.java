package Models.Statements;

import Exceptions.MyException;
import Models.ADTs.MyDictionary.IMyDictionary;
import Models.ADTs.MyStack.IMyStack;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Types.IType;
import Models.Values.IValue;

public class AssignmentStatement implements IStatement {
    String id;
    IExpression expression;

    @Override
    public String toString() {
        return this.id + "=" + this.expression.toString() + "\n";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        IMyStack<IStatement> stack = state.getStack();
        IMyDictionary<String, IValue> symbolTable = state.getSymbolTable();

        if (symbolTable.isDefined(this.id)) {
            IValue value = this.expression.evaluate(symbolTable);
            IType definedType = (symbolTable.lookup(this.id)).getType();

            if (value.getType().equals(definedType)) {
                symbolTable.update(this.id, value);
            } else {
                throw new MyException("Declared type of the variable `" + this.id + "` and the assigned type don't match.");
            }
        } else {
            throw new MyException("The used variable `" + this.id + "` was not declared.");
        }

        return state;
    }
}
