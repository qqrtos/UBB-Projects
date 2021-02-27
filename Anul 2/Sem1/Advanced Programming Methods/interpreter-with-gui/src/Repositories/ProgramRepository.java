package Repositories;

import Exceptions.EmptyCollectionException;
import Models.ADTs.MyList.MyList;
import Models.ProgramState;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class ProgramRepository implements IProgramRepository {
    private final MyList<ProgramState> programs = new MyList<>();
    private MyList<ProgramState> threads = new MyList<>();

    public ProgramRepository(ProgramState... programs) {
        this.programs.addAll(Arrays.asList(programs));
    }

    @Override
    public ProgramState getProgram(int id) {
        var program = programs.stream()
                .filter(p -> p.getId().get() == id)
                .findFirst();

        if (program.isEmpty()){
            throw new EmptyCollectionException("Program with provided Id not found.");
        }

        return program.get();
    }

    @Override
    public List<ProgramState> getPrograms() {
        return this.programs;
    }

    @Override
    public void addProgram(ProgramState state) {
        this.programs.add(state);
    }

    @Override
    public MyList<ProgramState> getThreads() {
        return this.threads;
    }

    @Override
    public void setThreads(MyList<ProgramState> newThreadsList) {
        this.threads = newThreadsList;
    }
}
