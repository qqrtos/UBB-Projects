package Views.GUI.ProgramSelector;

import Models.ProgramState;
import javafx.scene.control.Label;
import javafx.scene.control.ListCell;

public class ExecutionStackCell extends ListCell<ProgramState> {
    @Override
    public void updateItem(ProgramState item, boolean empty){
        super.updateItem(item, empty);
        if (item !=null){
            String executionStackString = item.getExecutionStack().toString();
            setGraphic(new Label(executionStackString));
        }
    }
}
