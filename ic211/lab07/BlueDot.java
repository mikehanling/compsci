/**
 * Mike Hanling
 *
 * Blue Dot
 * Can change direction after every 10 moves
 */
public class BlueDot extends DirDot {
  
  private int lastChange = 1;

  /**
   * Constructor
   */
  public BlueDot(int r, int c, int d) {
    super(r, c, d);
  }

  /**
   * If it has been ten moves
   *  Change direction
   *  to right left, or stay straight
   */
  public void turn(int t) {
    if (this.lastChange == 10) {
      super.turn(t);
      this.lastChange = 1;
    }else
      this.lastChange++;
  }

  /**
   * How the BlueDot should be printed
   */
  public String toString() {
    return super.toString() + " b";
  }

}
