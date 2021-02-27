package Models.Types;

import Models.Values.ReferenceValue;

public class ReferenceType implements IType {
    IType innerType;

    public ReferenceType(IType inner) {
        this.innerType = inner;
    }

    public IType getInnerType() {
        return this.innerType;
    }

    @Override
    public boolean equals(Object obj) {
        return obj instanceof ReferenceType
                && this.innerType.equals(((ReferenceType) obj).getInnerType());
    }

    public ReferenceValue defaultValue() {
        return new ReferenceValue(0, this.innerType);
    }

    @Override
    public String toString() {
        return "Reference(" + this.innerType.toString() + ")";
    }
}
