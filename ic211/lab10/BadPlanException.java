/**
 * Custom exception class for when the loan will never be paid off
 * @author Hanling, Mike - 202430
 */
public class BadPlanException extends RuntimeException{
  private static final long serialVersionUID = 0L;

  /**
   * Constructor for BadPlanException
   * @param msg String that is the message to associate with this exception
   */
  public BadPlanException(String msg){
    super(msg);
  }
}

