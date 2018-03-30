import java.util.*;

/**
 * Driver for HW14
 * adapted from given source code <a href="http://faculty.cs.usna.edu/IC211/calendar.php?key=d23572f0088fdc0821b77dd414d4ca4b22f7d51a&type=class&event=14">
 * @author Hanling, Mike - 202430
 */
public class HW14 {
  /**
   * The main function from HW14:
   * Determine whether to work in verbose mode or not
   * Output instructions if in verbose mode
   * Read in three ints
   * Save the value from doing computation on those three ints in MyMath.modexp
   * Print the result back to the terminal
   * Error checking is done for read in of ints, and value checking for the
   * computation
   * @param -v Optional - will put in verbose mode
   */
  public static void main(String[] args) {
    boolean verbose = args.length > 0 && args[0].equals("-v");
    Scanner sc      = new Scanner(System.in);

    if (verbose) {
      System.out.print("Enter x, k, m: ");
    }
    Integer x = null;
    Integer k = null;
    Integer m = null;
    Integer r = null;
    try{
      x = sc.nextInt();
      k = sc.nextInt();
      m = sc.nextInt();
      r = MyMath.modexp(x, k, m);
    }catch(Throwable e) {
      System.out.print( (verbose ? "Error in HW14! invalid input\n" : ""));
      System.exit(1);
    }

    if (verbose) {
      System.out.print(x + "^" + k + " % " + m + " = ");
    }
    System.out.println(r);
  }
}
