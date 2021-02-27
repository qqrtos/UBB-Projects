package Controllers;

import Exceptions.CustomException;
import Models.IEntity;
import Repository.IRepository;

public class Controller {
    private IRepository _repository;

    public Controller(IRepository repository) {
        this._repository = repository;
    }

    public void add(IEntity element) throws CustomException {
        this._repository.add(element);
    }

    public IEntity[] getAll() {
        return this._repository.getAll();
    }

    public IEntity[] filterByAge(int maxAge) {
        IEntity[] filtered = new IEntity[this._repository.getSize()];
        int filteredSize = 0;

        for (var entity : this._repository.getAll()) {
            if (entity.getAge() > maxAge) {
                filtered[filteredSize++] = entity;
            }
        }

        return filtered;
    }
}
