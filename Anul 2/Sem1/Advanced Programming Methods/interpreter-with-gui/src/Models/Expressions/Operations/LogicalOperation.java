package Models.Expressions.Operations;

public enum LogicalOperation implements IOperation{
    Or,
    And;

    @Override
    public String getMathematicalSign() {
        return switch (this){
            case Or -> "||";
            case And -> "&&";
        };
    }
}
