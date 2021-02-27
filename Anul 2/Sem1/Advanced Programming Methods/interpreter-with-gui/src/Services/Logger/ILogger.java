package Services.Logger;

public interface ILogger {
    void append(String message);

    void log() throws Exception;

    void flushBuffer();
}