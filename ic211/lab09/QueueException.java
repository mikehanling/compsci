/**
 * Custom exception class for Queue
 * @author Hanling, Mike - 202430
 */
public class QueueException extends RuntimeException{
  private static final long serialVersionUID = 0L;

  /**
   * Constructor for QueueException
   * @param msg String that is the message to associate with this exception
   */
  public QueueException(String msg){
    super(msg);
  }
}

