package Views.MenuView.Commands;

import Controllers.Controller;

public class RunCommand extends Command {
    private final Controller controller;

    public RunCommand(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            this.controller.allSteps(Integer.parseInt(this.getKey()));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
