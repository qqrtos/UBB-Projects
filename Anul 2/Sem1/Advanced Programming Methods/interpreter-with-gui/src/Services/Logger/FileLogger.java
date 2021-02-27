package Services.Logger;

import Exceptions.FileException;

import java.io.FileWriter;
import java.io.IOException;

public class FileLogger implements ILogger {
    private final String path;
    private final StringBuilder message = new StringBuilder();

    public FileLogger(String path) throws FileException {
        this.path = path;
    }

    @Override
    public void append(String message) {
        this.message.append(message);
    }

    @Override
    public void log() throws Exception {
        FileWriter file = new FileWriter(path);
        file.write(this.message.toString());
        this.flushBuffer();
        file.close();
    }

    @Override
    public void flushBuffer() {
        this.message.setLength(0);
    }
}
