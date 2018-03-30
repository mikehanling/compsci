/**
 * Custom exception class for Unsupported Hash Algorithms 
 * @author Hanling, Mike - 202430
 */
public class UnsupportedHashException extends RuntimeException{
  private static final long serialVersionUID = 0L;

  /**
   * Constructor for QueueException
   * @param msg String that is the message to associate with this exception
   */
  public UnsupportedHashException(String msg){
    super(msg);
  }
}

