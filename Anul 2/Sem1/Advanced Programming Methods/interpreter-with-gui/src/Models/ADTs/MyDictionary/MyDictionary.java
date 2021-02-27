package Models.ADTs.MyDictionary;

import Exceptions.UndefinedVariableException;

import java.util.HashMap;

public class MyDictionary<K, V> extends HashMap<K, V> {
    public boolean isDefined(K id) {
        return this.containsKey(id);
    }

    public V lookup(K id) throws RuntimeException {
        var found = this.get(id);
        if (found == null) {
            throw new UndefinedVariableException(String.format("Variable '%s' is not defined in the table.", id));
        }
        return this.get(id);
    }

    public void update(K id, V value) throws RuntimeException {
        if (this.get(id) == null) {
            throw new UndefinedVariableException(String.format("Variable '%s' can not be updated.", id));
        }
        this.put(id, value);
    }

    public MyDictionary<K, V> deepCopy(){
        var newDictionary = new MyDictionary<K, V>();
        this.forEach(newDictionary::put);
        return newDictionary;
    }

    @Override
    public String toString() {
        var printValue = new StringBuilder().append("{  ");
        this.forEach((key, value) -> {
            printValue
                    .append(key)
                    .append("->")
                    .append(value)
                    .append("  ");
        });
        printValue.append("}");
        return printValue.toString();
    }
}
