package Repository;

import Exceptions.CustomException;
import Models.IEntity;

public interface IRepository {
    IEntity[] getAll();

    int getSize();

    void add(IEntity element) throws CustomException;

    void remove(IEntity element) throws CustomException;
}
