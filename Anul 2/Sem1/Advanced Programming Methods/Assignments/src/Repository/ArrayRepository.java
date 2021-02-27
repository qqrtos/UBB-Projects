package Repository;

import Exceptions.CustomException;
import Models.IEntity;

public class ArrayRepository implements IRepository {
    private IEntity[] _elements;
    private int _count;

    public ArrayRepository(int maxCapacity) {
        this._elements = new IEntity[maxCapacity];
    }

    @Override
    public IEntity[] getAll() {
        return this._elements;
    }

    @Override
    public int getSize() {
        return this._elements.length;
    }

    @Override
    public void add(IEntity element) throws CustomException {
        if (this._count >= this._elements.length) {
            throw new CustomException("");
        }
        this._elements[this._count++] = element;
    }

    @Override
    public void remove(IEntity element) throws CustomException {
        for (int i = 0; i < this._count; ++i) {
            if (!this._elements[i].equals(element)) {
                for (int j = i; j < this._count - 1; ++j) {
                    this._elements[j] = this._elements[j + 1];
                }
                return;
            }
        }
        throw new CustomException("Element wasn't found");
    }
}
