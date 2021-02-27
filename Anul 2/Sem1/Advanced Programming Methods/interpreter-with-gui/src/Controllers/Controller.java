package Controllers;

import Exceptions.ThreadRunException;
import Models.ADTs.MyList.MyList;
import Models.ProgramState;
import Models.Values.IValue;
import Models.Values.ReferenceValue;
import Repositories.IProgramRepository;
import Services.Logger.ILogger;

import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private final IProgramRepository repository;
    private final ILogger logger;
    private ExecutorService executor;

    public Controller(IProgramRepository repository, ILogger logger) {
        this.repository = repository;
        this.logger = logger;
    }

    public void setProgram(ProgramState program){
        this.repository.getThreads().add(program);
    }

    public void oneStep(ProgramState program) throws Exception{
        this.executor = Executors.newFixedThreadPool(2);

        this.oneStepForEachThread(this.repository.getThreads());

        this.logger.append(program.toString());
        this.removeCompletedPrograms(this.repository.getThreads());

        this.executor.shutdownNow();
    }

    public void log() throws Exception {
        this.logger.log();
    }

    public void allSteps(int programId) throws Exception {
        this.executor = Executors.newFixedThreadPool(2);
        this.repository.getThreads().add(repository.getProgram(programId));
        MyList<ProgramState> programsList = this.repository.getThreads();

        while (programsList.size() > 0) {
            programsList.forEach(p -> this.logger.append(p.toString()));
            programsList = this.removeCompletedPrograms(programsList);
            this.oneStepForEachThread(programsList);
        }

        logger.log();
        this.executor.shutdownNow();
    }

    private void oneStepForEachThread(MyList<ProgramState> threads) throws InterruptedException {
        threads.forEach(prg -> prg.getHeap().setContent(this.conservativeCollectGarbage(
                    this.getReferencedAddressesFromSymbolTable(prg.getSymbolTable(), prg.getHeap()),
                    prg.getHeap())
                )
        );

        MyList<Callable<ProgramState>> callList = new MyList<>();
        callList.addAll(threads.stream()
                .map((ProgramState p) -> (Callable<ProgramState>) (p::executeOneInstruction))
                .collect(Collectors.toList()));

        MyList<ProgramState> newProgramsList = new MyList<>();
        newProgramsList.addAll(this.executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (Exception e) {
                        //return null;
                        throw new ThreadRunException(e.getMessage());
                    }
                })
                .filter(Objects::nonNull)
                .collect(Collectors.toList()));

        threads.addAll(newProgramsList);
    }

    public Map<Integer, IValue> conservativeCollectGarbage(List<Integer> symbolTableAddresses, Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(e -> symbolTableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private List<Integer> getReferencedAddressesFromSymbolTable(Map<String, IValue> symbolTable, Map<Integer, IValue> heap) {
        return Stream.concat(
                symbolTable.values().stream()
                        .filter(v -> v instanceof ReferenceValue)
                        .map(v -> ((ReferenceValue) v).getAddress()),
                heap.values().stream()
                        .filter(v -> v instanceof ReferenceValue)
                        .map(v -> ((ReferenceValue) v).getAddress())
        ).collect(Collectors.toList());
    }

    MyList<ProgramState> removeCompletedPrograms(MyList<ProgramState> inProgressPrograms) {
        MyList<ProgramState> runningPrograms = new MyList<>();
        runningPrograms.addAll(inProgressPrograms.stream()
                .filter(ProgramState::isNotCompleted)
                .collect(Collectors.toList()));
        return runningPrograms;
    }
}
