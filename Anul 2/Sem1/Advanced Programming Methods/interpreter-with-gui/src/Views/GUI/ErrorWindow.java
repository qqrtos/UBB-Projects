package Views.GUI;

import javafx.scene.control.Alert;

public class ErrorWindow {
    public static void show(String message){
        Alert errorWindow = new Alert(Alert.AlertType.ERROR);
        errorWindow.setTitle("Error occurred");
        errorWindow.setContentText(message);
        errorWindow.showAndWait();
    }
}
