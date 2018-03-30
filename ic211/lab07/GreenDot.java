import java.util.*;
/**
 * Mike Hanling
 *
 * Green Dot - diagonal movement
 */
public class GreenDot extends DiagDot {

  /**
   * Constructor
   */
  public GreenDot(int r, int c, int d) {
    super(r, c, d);
  }

  /**
   * How the GreenDot will print
   */
  public String toString() {
    return super.toString() + " g";
  }
}
