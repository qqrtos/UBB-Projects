package Models.Expressions.Operations;

public enum ArithmeticalOperation implements IOperation{
    Addition,
    Subtraction,
    Multiplication,
    Division;

    public String getMathematicalSign() {
        return switch (this) {
            case Addition -> "+";
            case Subtraction -> "-";
            case Multiplication -> "*";
            case Division -> "/";
        };
    }
}
