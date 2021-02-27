package Models.ADTs.MyList;

import java.util.ArrayList;
import java.util.Arrays;

public class MyList<T> extends ArrayList<T> {
    @SafeVarargs
    public static <T> MyList<T> fromArray(T... elements) {
        var list = new MyList<T>();
        list.addAll(Arrays.asList(elements));
        return list;
    }

    @Override
    public String toString() {
        var printValue = new StringBuilder().append("[ ");
        this.forEach(v -> printValue.append(v).append(" "));
        printValue.append("]");
        return printValue.toString();
    }
}
