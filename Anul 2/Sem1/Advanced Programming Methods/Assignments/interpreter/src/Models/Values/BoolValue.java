package Models.Values;

import Models.Types.BoolType;
import Models.Types.IType;

public class BoolValue implements IValue {
    boolean value;

    public BoolValue(boolean value){
        this.value = value;
    }

    public boolean getValue() {
        return this.value;
    }

    @Override
    public String toString(){
        //TODO: implement this
        return "";
    }

    @Override
    public IType getType() {
        return new BoolType();
    }
}
