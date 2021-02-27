package Views.GUI.ProgramRunner;

import Controllers.Controller;
import Models.ADTs.MyDictionary.MyDictionary;
import Models.ProgramState;
import Models.Statements.IStatement;
import Models.Values.IValue;
import Models.Values.StringValue;
import Views.GUI.ErrorWindow;
import javafx.beans.property.ReadOnlyStringWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;

import java.net.URL;
import java.util.Map;
import java.util.ResourceBundle;

public class ProgramRunnerController implements Initializable {
    private final Controller controller;
    private final ProgramState program;

    @FXML
    Button nextStepButton;
    @FXML
    Button typeCheckButton;
    @FXML
    Label currentProgram;
    @FXML
    ListView<IValue> outputList;
    @FXML
    ListView<StringValue> fileTableList;
    @FXML
    ListView<IStatement> executionStackList;

    @FXML
    TableView<Map.Entry<Integer, IValue>> heapTable;
    @FXML
    TableColumn<Map.Entry<Integer, IValue>, String> heapAddressCell;
    @FXML
    TableColumn<Map.Entry<Integer, IValue>, String> heapReferenceCell;

    @FXML
    TableView<Map.Entry<String, IValue>> symbolTable;
    @FXML
    TableColumn<Map.Entry<String, IValue>, String> symbolNameCell;
    @FXML
    TableColumn<Map.Entry<String, IValue>, String> symbolValueCell;

    @FXML
    TableView<Map.Entry<Integer, Integer>> latchTableView;
    @FXML
    TableColumn<Map.Entry<Integer, Integer>, String> latchTableIndexCell;
    @FXML
    TableColumn<Map.Entry<Integer, Integer>, String> latchTableValueCell;



    public ProgramRunnerController(Controller controller, ProgramState program) {
        this.controller = controller;
        this.program = program;
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        initialRun();

        this.nextStepButton.setOnAction(actionEvent -> {
            try {
                oneStepGUI();
            } catch (Exception e) {
                ErrorWindow.show(e.getMessage());
            }
        });

        this.typeCheckButton.setOnAction(actionEvent -> {
            try {
                this.program
                        .getExecutionStack()
                        .forEach(statement -> statement.typeCheck(new MyDictionary<>()));
                this.typeCheckButton.setStyle("-fx-background-color: #48FF7D");
                this.typeCheckButton.setDisable(true);
            } catch (Exception ex) {
                ErrorWindow.show(ex.getMessage());
            }
        });
    }

    private void initialRun() {
        this.symbolTable.setEditable(false);
        this.controller.setProgram(program);

        this.currentProgram.setText("Current running program: " + this.program.getId());

        this.updateLists();
    }


    private void updateLists() {
        updateFileTableUI();

        updateOutputListUI();

        updateExecutionStackUI();

        updateSymbolTable();

        updateHeapTable();

        updateLatchTable();
    }

    private void updateLatchTable() {
        ObservableList<Map.Entry<Integer, Integer>> latchTableList = FXCollections.observableArrayList();
        latchTableList.addAll(this.program.getLatchTable().entrySet());
        this.latchTableIndexCell.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey().toString()));
        this.latchTableValueCell.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
        this.latchTableView.getItems().setAll(latchTableList);
    }

    private void updateHeapTable() {
        ObservableList<Map.Entry<Integer, IValue>> heapList = FXCollections.observableArrayList();
        heapList.addAll(this.program.getHeap().entrySet());
        this.heapAddressCell.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey().toString()));
        this.heapReferenceCell.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
        this.heapTable.getItems().setAll(heapList);
    }

    private void updateSymbolTable() {
        ObservableList<Map.Entry<String, IValue>> symbolTableList = FXCollections.observableArrayList();
        symbolTableList.addAll(this.program.getSymbolTable().entrySet());
        this.symbolNameCell.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getKey()));
        this.symbolValueCell.setCellValueFactory(cellData -> new ReadOnlyStringWrapper(cellData.getValue().getValue().toString()));
        this.symbolTable.getItems().setAll(symbolTableList);
    }

    private void updateExecutionStackUI() {
        ObservableList<IStatement> executionStackElements = FXCollections.observableArrayList();
        executionStackElements.addAll(this.program.getExecutionStack());
        this.executionStackList.setItems(executionStackElements);
    }

    private void updateOutputListUI() {
        ObservableList<IValue> outputListElements = FXCollections.observableArrayList();
        outputListElements.addAll(this.program.getOutputList());
        this.outputList.setItems(outputListElements);
    }

    private void updateFileTableUI() {
        ObservableList<StringValue> fileTableListElements = FXCollections.observableArrayList();
        this.program.getFileTable().forEach((k, v) -> fileTableListElements.add(k));
        this.fileTableList.setItems(fileTableListElements);
    }

    private void oneStepGUI() throws Exception {
        if (this.program.getExecutionStack().isEmpty()) {
            this.nextStepButton.setDisable(true);
            this.controller.log();
        }
        else {
            this.controller.oneStep(program);
        }
        this.updateLists();
    }
}
