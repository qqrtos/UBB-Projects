package Models;

public class Fish implements IEntity {
    private int _age;

    public Fish(int age) {
        this._age = age;
    }

    @Override
    public int getAge() {
        return this._age;
    }

    @Override
    public boolean equals(Object other) {
        return this._age == ((IEntity) other).getAge();
    }

    @Override
    public String toString() {
        return "Fish is " + this._age + " months old.";
    }
}
