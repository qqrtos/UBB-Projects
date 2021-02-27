package Models.Values;

import Models.Types.BoolType;
import Models.Types.IType;

public class BoolValue implements IValue {
    private final boolean value;

    public BoolValue(boolean value) {
        this.value = value;
    }

    public boolean getValue() {
        return this.value;
    }

    @Override
    public String toString() {
        return (this.value ? "true" : "false");
    }

    @Override
    public IType getType() {
        return new BoolType();
    }
}
