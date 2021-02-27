package Repositories;

import Models.ADTs.MyList.MyList;
import Models.ProgramState;

import java.util.List;


public interface IProgramRepository {
    ProgramState getProgram(int id);

    List<ProgramState> getPrograms();

    void addProgram(ProgramState state);

    MyList<ProgramState> getThreads();

    void setThreads(MyList<ProgramState> newThreadsList);
}
