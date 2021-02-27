package Services.Logger;

public class ScreenLogger implements ILogger {
    private final StringBuilder message;

    public ScreenLogger() {
        this.message = new StringBuilder();
    }

    @Override
    public void append(String message) {
        this.message.append(message);
    }

    @Override
    public void log() {
        System.out.println(message);
        this.flushBuffer();
    }

    @Override
    public void flushBuffer() {
        this.message.setLength(0);
    }
}
