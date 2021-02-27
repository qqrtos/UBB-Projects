package Models;

public interface IEntity {
    int getAge();

    @Override
    boolean equals(Object other);
}
