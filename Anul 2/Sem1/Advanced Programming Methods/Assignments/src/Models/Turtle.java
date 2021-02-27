package Models;

public class Turtle implements IEntity {
    private int _age;

    public Turtle(int age) {
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
        return "Turtle is " + this._age + " years old.";
    }
}
