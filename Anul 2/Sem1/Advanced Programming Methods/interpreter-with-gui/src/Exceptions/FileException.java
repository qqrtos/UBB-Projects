package Exceptions;

import java.io.IOException;

public class FileException extends RuntimeException {
    public FileException(String message) {
        super(message);
    }
}
