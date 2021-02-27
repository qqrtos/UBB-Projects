package Models.Types;

public class BoolType implements IType {
    @Override
    public boolean equals(Object other) {
        return (other instanceof BoolType);
    }

    @Override
    public String toString(){
        return "bool";
    }
}
