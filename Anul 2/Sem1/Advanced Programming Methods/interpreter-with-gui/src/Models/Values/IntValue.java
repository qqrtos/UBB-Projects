package Models.Values;

import Models.Types.IType;
import Models.Types.IntType;

public class IntValue implements IValue {
    private final int value;

    public IntValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    @Override
    public String toString() {
        return Integer.toString(this.value);
    }

    @Override
    public IType getType() {
        return new IntType();
    }
}
