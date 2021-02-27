package Views.MenuView;

import Models.ADTs.MyDictionary.MyDictionary;
import Views.MenuView.Commands.Command;
import Views.IView;

import java.util.Scanner;

public class TextMenuView implements IView {
    private final MyDictionary<String, Command> commands = new MyDictionary<>();

    public TextMenuView() {
    }

    public TextMenuView addCommand(Command command) {
        this.commands.put(command.getKey(), command);
        return this;
    }

    @Override
    public void run() {
        while (true) {
            this.printMenu();

            var userInput = this.getInput();
            try {
                this.commands.lookup(userInput).execute();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }

    public void printMenu() {
        System.out.println("\n");
        this.commands.forEach(
                (key, command) -> System.out.println(key + ". " + command.getDescription())
        );
    }

    private String getInput() {
        Scanner scan = new Scanner(System.in);
        System.out.print(">");
        return scan.next();
    }
}
