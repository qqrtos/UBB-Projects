package Models.Expressions.Operations;

public enum RelationalOperation implements IOperation {
    LessThan,
    LessThanOrEqual,
    Equal,
    Different,
    GreaterThan,
    GreaterThanOrEqual;

    public String getMathematicalSign() {
        return switch (this) {
            case LessThan -> "<";
            case LessThanOrEqual -> "<=";
            case Equal -> "==";
            case Different -> "!=";
            case GreaterThan -> ">";
            case GreaterThanOrEqual -> ">=";
        };
    }
}