package Models.Types;

import Models.Values.IValue;
import Models.Values.IntValue;

public class IntType implements IType {
    @Override
    public boolean equals(Object other) {
        return (other instanceof IntType);
    }

    @Override
    public String toString(){
        return "int";
    }

    @Override
    public IValue defaultValue() {
        return new IntValue(0);
    }
}
