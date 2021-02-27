package Models.Statements;

import Exceptions.InvalidTypeException;
import Exceptions.UndefinedVariableException;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.Expressions.IExpression;
import Models.ProgramState;
import Models.Types.BoolType;
import Models.Types.IType;

public class ConditionalStatement implements IStatement {
    private final String variableId;
    private final IExpression conditionExpression;
    private final IExpression trueConditionExpression;
    private final IExpression falseConditionExpression;

    public ConditionalStatement(String variableId,
                                IExpression conditionExpression,
                                IExpression trueConditionExpression,
                                IExpression falseConditionExpression) {
        this.variableId = variableId;
        this.conditionExpression = conditionExpression;
        this.trueConditionExpression = trueConditionExpression;
        this.falseConditionExpression = falseConditionExpression;
    }

    @Override
    public ProgramState execute(ProgramState state) throws RuntimeException {
        try {
            state.getSymbolTable().lookup(this.variableId);
        } catch (Exception e) {
            throw new UndefinedVariableException(e.getMessage());
        }

        state.getExecutionStack()
                .push(new IfStatement(this.conditionExpression,
                        new AssignmentStatement(this.variableId, this.trueConditionExpression),
                        new AssignmentStatement(this.variableId, this.falseConditionExpression))
                );

        return null;
    }

    @Override
    public MyDictionary<String, IType> typeCheck(MyDictionary<String, IType> typeEnvironment) throws RuntimeException {
        if (!this.conditionExpression.typeCheck(typeEnvironment).equals(new BoolType())){
           throw new InvalidTypeException("Type of the conditional expression is not bool.");
        }

        IType variableType;
        try{
            variableType = typeEnvironment.lookup(this.variableId);
        }catch(Exception e){
            throw new UndefinedVariableException(e.getMessage());
        }

        if(!this.trueConditionExpression.typeCheck(typeEnvironment).equals(variableType)){
            throw new InvalidTypeException("Type of the conditional true branch is not bool.");
        }

        if(!this.falseConditionExpression.typeCheck(typeEnvironment).equals(variableType)){
            throw new InvalidTypeException("Type of the conditional true branch is not bool.");
        }

        return typeEnvironment;
    }

    @Override
    public String toString(){
        return "(" +
                this.conditionExpression +
                "? "+
                this.trueConditionExpression+
                " : "+
                this.falseConditionExpression+
                ")";
    }
}
