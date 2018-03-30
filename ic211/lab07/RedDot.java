/**
 * Mike Hanling
 *
 * Red Dot
 * Can change direction after every move
 */
public class RedDot extends DirDot {
  
  /**
   * Constructor
   */
  public RedDot(int r, int c, int d) {
    super(r, c, d);
  }

  /**
   * How the RedDot should be printed
   */
  public String toString() {
    return super.toString() + " r";
  }

}
