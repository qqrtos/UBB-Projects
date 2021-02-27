package Models.Values;

import Models.Types.IType;
import Models.Types.IntType;

public class IntValue implements IValue {
    int value;

    public IntValue(int value){
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    @Override
    public String toString(){
        //TODO: implement this
        return "";
    }

    @Override
    public IType getType() {
        return new IntType();
    }
}
