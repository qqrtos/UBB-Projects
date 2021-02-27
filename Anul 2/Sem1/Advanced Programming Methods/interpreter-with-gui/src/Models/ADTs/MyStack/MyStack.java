package Models.ADTs.MyStack;

import java.util.ArrayDeque;

public class MyStack<T> extends ArrayDeque<T> {
    @Override
    public String toString() {
        var stackCopy = new MyStack<T>();
        stackCopy.addAll(this);

        StringBuilder printValue = new StringBuilder();
        while (!stackCopy.isEmpty()) {
            T currentStatement = stackCopy.pop();
            printValue.append(currentStatement).append(" | ");
        }

        return printValue.toString();
    }
}
