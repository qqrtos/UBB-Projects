package Models.Values;

import Models.Types.IType;
import Models.Types.ReferenceType;

import javax.xml.crypto.URIReferenceException;

public class ReferenceValue implements IValue {
    private int address;
    private IType referencedType;

    public ReferenceValue(int address, IType refType) {
        this.address = address;
        this.referencedType = refType;
    }

    public int getAddress() {
        return this.address;
    }

    public IType getReferencedType() {
        return this.referencedType;
    }

    public void setAddress(int newAddress) {
        this.address = newAddress;
    }

    public void setReferencedType(IType newType) {
        this.referencedType = newType;
    }

    @Override
    public IType getType() {
        return new ReferenceType(referencedType);
    }

    @Override
    public String toString() {
        return "(" + this.address + ", " + this.referencedType.toString() + ")";
    }
}
