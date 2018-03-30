/**
 * Currently, this cclass holds one function for computation
 * Static method, no fields
 * adapted from given source code <a href="http://faculty.cs.usna.edu/IC211/calendar.php?key=d23572f0088fdc0821b77dd414d4ca4b22f7d51a&type=class&event=14">
 * @author Hanling, Mike - 202430
 */
public class MyMath {
  /**
   * Returns x^k mod m
   * Note: k must be non-negative, and m must be positive
   * @param x Int for the base of the expression
   * @param k Int for the exponent (must be non-neg)
   * @param m Int for the modulo (must be positive)
   * @return r Int answer to x^k % m
   * @throws Throwable for divide by zero
   * @throws Throwable if the three inputs do not meet specification
   */
  public static int modexp(int x, int k, int m) throws Throwable{
    if (k < 0 || m < 1)
      throw new Throwable();

    int r = 1;

    for (int i = 0; i < k; i++) {
      r = r * x % m;
    }
    return r;
  }
}
