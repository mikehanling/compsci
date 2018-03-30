/**
 * Custom exception class for Invalid Characters 
 * (not 42-122 inclusive on ASCII table)
 * @author Hanling, Mike - 202430
 */
public class BadCharException extends RuntimeException{
  private static final long serialVersionUID = 0L;

  /**
   * Constructor for QueueException
   * @param msg String that is the message to associate with this exception
   */
  public BadCharException(String msg){
    super(msg);
  }
}

