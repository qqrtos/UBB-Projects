package Models.Types;

import Models.Values.IValue;
import Models.Values.StringValue;

public class StringType implements IType {
    @Override
    public boolean equals(Object obj) {
        return (obj instanceof StringType);
    }

    @Override
    public String toString() {
        return "String";
    }

    @Override
    public IValue defaultValue() {
        return new StringValue("");
    }
}
