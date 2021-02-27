package Views.GUI.ProgramSelector;

import Controllers.Controller;
import Models.ADTs.LatchTable;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.ADTs.MyList.MyList;
import Models.ADTs.MyStack.MyStack;
import Models.Expressions.*;
import Models.Expressions.Operations.ArithmeticalOperation;
import Models.Expressions.Operations.RelationalOperation;
import Models.Heap.Heap;
import Models.ProgramState;
import Models.Statements.*;
import Models.Statements.File.CloseReadFile;
import Models.Statements.File.OpenReadFileStatement;
import Models.Statements.File.ReadFileStatement;
import Models.Statements.Heap.NewAllocationStatement;
import Models.Statements.Heap.WriteToHeapStatement;
import Models.Statements.Threading.AwaitStatement;
import Models.Statements.Threading.CountDownStatement;
import Models.Statements.Threading.NewLatchStatement;
import Models.Types.*;
import Models.Values.BoolValue;
import Models.Values.IntValue;
import Models.Values.StringValue;
import Repositories.ProgramRepository;
import Services.Logger.FileLogger;
import Views.GUI.ErrorWindow;
import Views.GUI.ProgramRunner.ProgramRunnerController;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.stage.Stage;
import javafx.util.Callback;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.concurrent.atomic.AtomicInteger;

public class ProgramSelectorController implements Initializable {
    @FXML
    Button runButton;
    @FXML
    ListView<ProgramState> programsListView;

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        var logger = new FileLogger("output.log");

        var repository = new ProgramRepository();
        var programs = this.getProgramsList();

        programs.forEach(repository::addProgram);

        var controller = new Controller(repository, logger);

        this.runButton.setOnAction(new EventHandler<>() {
                                       @Override
                                       public void handle(ActionEvent e) {
                                           Stage programStage = new Stage();
                                           Parent programRoot;
                                           Callback<Class<?>, Object> controllerFactory = type -> {
                                               if (type == ProgramRunnerController.class) {
                                                   return new ProgramRunnerController(controller, programsListView.getSelectionModel().getSelectedItem());
                                               } else {
                                                   try {
                                                       return type.newInstance();
                                                   } catch (Exception exception) {
                                                       System.err.println("Could not create controller for " + type.getName());
                                                       throw new RuntimeException(exception);
                                                   }
                                               }
                                           };

                                           try {
                                               FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("../ProgramRunner/ProgramRunner.fxml"));
                                               fxmlLoader.setControllerFactory(controllerFactory);
                                               programRoot = fxmlLoader.load();
                                               Scene programScene = new Scene(programRoot);
                                               programStage.setTitle("Toy Language - Program running");
                                               programStage.setScene(programScene);
                                               programStage.show();
                                           } catch (IOException ex) {
                                               ErrorWindow.show(ex.getMessage());
                                           }
                                       }
                                   }
        );

        ObservableList<ProgramState> observableStatements = FXCollections.observableArrayList(programs);
        this.programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        this.programsListView.getSelectionModel().selectFirst();
        this.programsListView.setItems(observableStatements);
        this.programsListView.setCellFactory(programStateListView -> new ExecutionStackCell());
    }

    private List<ProgramState> getProgramsList() {
        ArrayList<ProgramState> programs = new ArrayList<>();
        LatchTable latchTable = new LatchTable();

        /* int v; v = 2; Print(v) */
        MyStack<IStatement> stack1 = new MyStack<>();
        IStatement ex1 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("v", new IntType()),
                        new AssignmentStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))
                }
        );
        stack1.push(ex1);
        ProgramState ex1_state = new ProgramState(
                new AtomicInteger(1), stack1, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex1_state);


        /* int a;int b; a=2+3*5;b=a+1;Print(b) */
        MyStack<IStatement> stack2 = new MyStack<>();
        IStatement ex2 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("a", new IntType()),
                        new VariableDeclarationStatement("b", new IntType()),
                        new AssignmentStatement("a",
                                new ArithmeticalExpression(new ValueExpression(new IntValue(2)), ArithmeticalOperation.Addition,
                                        new ArithmeticalExpression(new ValueExpression(new IntValue(3)), ArithmeticalOperation.Multiplication, new ValueExpression(new IntValue(5))))),
                        new AssignmentStatement("b",
                                new ArithmeticalExpression(new VariableExpression("a"), ArithmeticalOperation.Addition, new ValueExpression(new IntValue(1)))),
                        new PrintStatement(new VariableExpression("b"))
                }
        );
        stack2.push(ex2);
        ProgramState ex2_state = new ProgramState(
                new AtomicInteger(2), stack2, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex2_state);


        /*bool a; int v; a = true; (If a Then v = 2 Else v = 3); Print(v)*/
        MyStack<IStatement> stack3 = new MyStack<>();
        IStatement ex3 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("a", new BoolType()),
                        new VariableDeclarationStatement("v", new IntType()),
                        new AssignmentStatement("a", new ValueExpression(new BoolValue(true))),
                        new IfStatement(
                                new VariableExpression("a"), // condition
                                new AssignmentStatement("v", new ValueExpression(new IntValue(2))), // then
                                new AssignmentStatement("v", new ValueExpression(new IntValue(3))) // else
                        ),
                        new PrintStatement(new VariableExpression("v"))
                }
        );
        stack3.push(ex3);
        ProgramState ex3_state = new ProgramState(
                new AtomicInteger(3), stack3, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex3_state);

        /*int a; a=false*/
        MyStack<IStatement> stack4 = new MyStack<>();
        IStatement ex4 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("a", new IntType()),
                        new AssignmentStatement("a", new ValueExpression(new BoolValue(false)))
                }
        );
        stack4.push(ex4);
        ProgramState ex4_state = new ProgramState(
                new AtomicInteger(4), stack4, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex4_state);


        /*string f;
        f="test.in";
        OpenReadFile(f);
        int c;
        ReadFile(f, c); print(c);
        ReadFile(f, c)l print(c);
        CloseReadFile(f)*/
        MyStack<IStatement> stack5 = new MyStack<>();
        IStatement ex5 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("f", new StringType()),
                        new AssignmentStatement("f", new ValueExpression(new StringValue("test.in"))),
                        new OpenReadFileStatement(new VariableExpression("f")),
                        new VariableDeclarationStatement("c", new IntType()),
                        new ReadFileStatement(new VariableExpression("f"), "c"),
                        new PrintStatement(new VariableExpression("c")),
                        new ReadFileStatement(new VariableExpression("f"), "c"),
                        new PrintStatement(new VariableExpression("c")),
                        new CloseReadFile(new VariableExpression("f"))
                }
        );
        stack5.push(ex5);
        ProgramState ex5_state = new ProgramState(
                new AtomicInteger(5), stack5, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex5_state);

        /*int a; int b=a+1; print(a>b)*/
        MyStack<IStatement> stack6 = new MyStack<>();
        IStatement ex6 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("a", new IntType()),
                        new VariableDeclarationStatement("b", new IntType()),
                        new AssignmentStatement("b",
                                new ArithmeticalExpression(
                                        new VariableExpression("a"),
                                        ArithmeticalOperation.Addition,
                                        new ValueExpression(new IntValue(1))
                                )
                        ),
                        new PrintStatement(
                                new RelationalExpression(
                                        new VariableExpression("a"),
                                        RelationalOperation.LessThan,
                                        new VariableExpression("b")
                                )
                        )
                }
        );
        stack6.push(ex6);
        ProgramState ex6_state = new ProgramState(
                new AtomicInteger(6), stack6, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex6_state);

        /*
         * Reference int v;
         * new(v,20);
         * Reference Reference int a;
         * new(a, v);
         * WriteToHeap(v, 30)
         * print(v)
         * new(v, 40);
         * print(ReadHeap(ReadHeap(a)) + 5)
         */
        MyStack<IStatement> stack7 = new MyStack<>();
        IStatement ex7 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("v", new ReferenceType(new IntType())),
                        new NewAllocationStatement("v", new ValueExpression(new IntValue(20))),
                        new VariableDeclarationStatement("a", new ReferenceType(new ReferenceType(new IntType()))),
                        new NewAllocationStatement("a", new VariableExpression("v")),
                        new WriteToHeapStatement("v", new ValueExpression(new IntValue(30))),
                        new PrintStatement(new VariableExpression("v")),
                        new NewAllocationStatement("v", new ValueExpression(new IntValue(40))),
                        new PrintStatement(new ArithmeticalExpression(
                                new ReadHeapExpression(new ReadHeapExpression(new VariableExpression("a"))),
                                ArithmeticalOperation.Addition,
                                new ValueExpression(new IntValue(5))
                        )
                        )
                }
        );
        stack7.push(ex7);
        ProgramState ex7_state = new ProgramState(
                new AtomicInteger(7), stack7, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex7_state);


        /*
         * int a;
         * a = 1;
         * int b;
         * b = 3;
         * while (a < b) print a; a = a+1
         */
        MyStack<IStatement> stack8 = new MyStack<>();
        IStatement ex8 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("a", new IntType()),
                        new AssignmentStatement("a", new ValueExpression(new IntValue(1))),
                        new VariableDeclarationStatement("b", new IntType()),
                        new AssignmentStatement("b", new ValueExpression(new IntValue(3))),
                        new WhileStatement(
                                new RelationalExpression(
                                        new VariableExpression("a"),
                                        RelationalOperation.LessThan,
                                        new VariableExpression("b")
                                ),
                                new CompoundStatement(
                                        new PrintStatement(new VariableExpression("a")),
                                        new AssignmentStatement("a",
                                                new ArithmeticalExpression(
                                                        new VariableExpression("a"),
                                                        ArithmeticalOperation.Addition,
                                                        new ValueExpression(new IntValue(1))
                                                )
                                        )
                                )
                        )
                }
        );
        stack8.push(ex8);
        ProgramState ex8_state = new ProgramState(
                new AtomicInteger(8), stack8, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex8_state);


        MyStack<IStatement> stack9 = new MyStack<>();
        IStatement ex9 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("v", new IntType()),
                        new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                        new AssignmentStatement("v", new ValueExpression(new IntValue(10))),
                        new NewAllocationStatement("a", new ValueExpression(new IntValue(22))),
                        new ForkStatement(CompoundStatement.fromArray(new IStatement[]{
                                        new WriteToHeapStatement("a", new ValueExpression(new IntValue(30))),
                                        new AssignmentStatement("v", new ValueExpression(new IntValue(32))),
                                        new PrintStatement(new VariableExpression("v")),
                                        new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                                }
                        )
                        ),
                        new PrintStatement(new VariableExpression("v")),
                        new PrintStatement(new ReadHeapExpression(new VariableExpression("a")))
                }
        );
        stack9.push(ex9);
        ProgramState ex9_state = new ProgramState(
                new AtomicInteger(9), stack9, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex9_state);


        /*
        Ref int a; Ref int b; int v;
        new(a,0); new(b,0);
        wh(a,1); wh(b,2);
        v=(rh(a)<rh(b))?100:200;
        print(v);
        v= ((rh(b)-2)>rh(a))?100:200;
        print(v);
        */
        MyStack<IStatement> stack10 = new MyStack<>();
        IStatement ex10 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("a", new ReferenceType(new IntType())),
                        new VariableDeclarationStatement("b", new ReferenceType(new IntType())),
                        new VariableDeclarationStatement("v", new IntType()),
                        new NewAllocationStatement("a", new ValueExpression(new IntValue(0))),
                        new NewAllocationStatement("b", new ValueExpression(new IntValue(0))),
                        new WriteToHeapStatement("a", new ValueExpression(new IntValue(1))),
                        new WriteToHeapStatement("b", new ValueExpression(new IntValue(2))),
                        new ConditionalStatement("v",
                                new RelationalExpression(
                                        new ReadHeapExpression(new VariableExpression("a")),
                                        RelationalOperation.LessThan,
                                        new ReadHeapExpression(new VariableExpression("b"))
                                ),
                                new ValueExpression(new IntValue(100)),
                                new ValueExpression(new IntValue(200))
                        ),
                        new PrintStatement(new VariableExpression("v")),
                        new ConditionalStatement("v",
                                new RelationalExpression(
                                        new ArithmeticalExpression(
                                                new ReadHeapExpression(new VariableExpression("b")),
                                                ArithmeticalOperation.Subtraction,
                                                new ValueExpression(new IntValue(2))
                                        ),
                                        RelationalOperation.GreaterThan,
                                        new ReadHeapExpression(new VariableExpression("a"))
                                ),
                                new ValueExpression(new IntValue(100)),
                                new ValueExpression(new IntValue(200))
                        ),
                        new PrintStatement(new VariableExpression("v"))
                }
        );
        stack10.push(ex10);
        ProgramState ex10_state = new ProgramState(
                new AtomicInteger(10), stack10, new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                latchTable);
        programs.add(ex10_state);


        /*
        Ref int v1; Ref int v2; Ref int v3; int cnt;
        new(v1,2);new(v2,3);new(v3,4);newLatch(cnt,rH(v2));
        fork(wh(v1,rh(v1)*10));print(rh(v1));countDown(cnt);
               fork(wh(v2,rh(v2)*10));print(rh(v2));countDown(cnt);
                      fork(wh(v3,rh(v3)*10));print(rh(v3));countDown(cnt))));
        await(cnt);
        print(100);
        countDown(cnt);
        print(100)
         */
        MyStack<IStatement> stack11 = new MyStack<>();
        IStatement ex11 = CompoundStatement.fromArray(new IStatement[]{
                        new VariableDeclarationStatement("v1", new ReferenceType(new IntType())),
                        new VariableDeclarationStatement("v2", new ReferenceType(new IntType())),
                        new VariableDeclarationStatement("v3", new ReferenceType(new IntType())),
                        new VariableDeclarationStatement("cnt", new IntType()),
                        new NewAllocationStatement("v1", new ValueExpression(new IntValue(2))),
                        new NewAllocationStatement("v2", new ValueExpression(new IntValue(3))),
                        new NewAllocationStatement("v3", new ValueExpression(new IntValue(4))),
                        new NewLatchStatement("cnt", new ReadHeapExpression(new VariableExpression("v2"))),
                        new ForkStatement(
                                CompoundStatement.fromArray(new IStatement[]{
                                                new WriteToHeapStatement("v1",
                                                        new ArithmeticalExpression(
                                                                new ReadHeapExpression(new VariableExpression("v2")),
                                                                ArithmeticalOperation.Multiplication,
                                                                new ValueExpression(new IntValue(10))
                                                        )
                                                ),
                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                                new CountDownStatement("cnt"),
                                                new ForkStatement(CompoundStatement.fromArray(new IStatement[]{
                                                                new WriteToHeapStatement("v1",
                                                                        new ArithmeticalExpression(
                                                                                new ReadHeapExpression(new VariableExpression("v1")),
                                                                                ArithmeticalOperation.Multiplication,
                                                                                new ValueExpression(new IntValue(10))
                                                                        )
                                                                ),
                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v1"))),
                                                                new CountDownStatement("cnt"),
                                                                new ForkStatement(CompoundStatement.fromArray(new IStatement[]{
                                                                                new WriteToHeapStatement("v2",
                                                                                        new ArithmeticalExpression(
                                                                                                new ReadHeapExpression(new VariableExpression("v2")),
                                                                                                ArithmeticalOperation.Multiplication,
                                                                                                new ValueExpression(new IntValue(10))
                                                                                        )
                                                                                ),
                                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v2"))),
                                                                                new CountDownStatement("cnt"),
                                                                                new ForkStatement(CompoundStatement.fromArray(new IStatement[]{
                                                                                                new WriteToHeapStatement("v3",
                                                                                                        new ArithmeticalExpression(
                                                                                                                new ReadHeapExpression(new VariableExpression("v3")),
                                                                                                                ArithmeticalOperation.Multiplication,
                                                                                                                new ValueExpression(new IntValue(10))
                                                                                                        )
                                                                                                ),
                                                                                                new PrintStatement(new ReadHeapExpression(new VariableExpression("v3"))),
                                                                                                new CountDownStatement("cnt")
                                                                                        }
                                                                                )
                                                                                )
                                                                        }
                                                                )
                                                                )
                                                        }
                                                )
                                                ),
                                                new AwaitStatement("cnt"),
                                                new PrintStatement(new ValueExpression(new IntValue(100))),
                                                new CountDownStatement("cnt"),
                                                new PrintStatement(new ValueExpression(new IntValue(100))),
                                        }
                                )
                        ),


                }
        );
        stack11.push(ex11);
        ProgramState ex11_state = new ProgramState(
                new AtomicInteger(11),
                stack11,
                new MyDictionary<>(), new MyList<>(), new MyDictionary<>(), new Heap<>(),
                new LatchTable());
        programs.add(ex11_state);

        return programs;
    }
}
