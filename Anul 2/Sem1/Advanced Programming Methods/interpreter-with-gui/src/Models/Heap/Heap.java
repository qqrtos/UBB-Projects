package Models.Heap;

import Exceptions.HeapException;
import Models.ADTs.MyDictionary.MyDictionary;

import java.util.Map;
import java.util.concurrent.atomic.AtomicInteger;

public class Heap<T> extends MyDictionary<Integer, T> {
    private final AtomicInteger firstAvailableLocation;

    public Heap() {
        this.firstAvailableLocation = new AtomicInteger(1);
    }

    public boolean isAvailableSpot(int address) {
        return !this.isDefined(address);
    }

    public int allocate(T value) {
        int newLocation = this.firstAvailableLocation.incrementAndGet();
        this.put(newLocation, value);
        return newLocation;
    }

    public T getValueAtAddress(int address) {
        return this.get(address);
    }

    public void update(int address, T newValue) {
        if (!this.isDefined(address)) {
            throw new HeapException("Can't update an address that hasn't been allocated yet.");
        }
        this.put(address, newValue);
    }

    public void setContent(Map<Integer, T> map) {
        this.clear();
        map.forEach(this::put);
    }

    @Override
    public String toString() {
        StringBuilder printedHeap = new StringBuilder();
        printedHeap.append("{");
        this.forEach((key, value) -> {
            printedHeap
                    .append(key)
                    .append("->")
                    .append(value)
                    .append(" ");
        });
        printedHeap.append("}");
        return printedHeap.toString();
    }
}
