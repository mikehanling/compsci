import java.util.*;
import java.io.*;

/**
 * Driver class for hw 20 in IC211 (Spring 2018)
 * This is a wrapper to take input to then have a mystery class to computation
 * on
 * @author Hanling, Mike - 202430
 */
public class HW20 {
  
  /**
   * This main checks for the number of command line arguments
   * If it is 0, then input will be taken from STDIN
   * If it is 1, then input will come from that one file
   * Otherwise, a usage message is printed, and the process exits
   * The line number of the error (if there is one) will be reported
   * @param args Command line arguments: optional filename (but only one)
   */
  public static void main(String[] args) {
    InputStreamReader i = null;
    if (args.length == 0)
      i = new InputStreamReader(System.in);
    else if (args.length == 1) {
      try {
        i = new InputStreamReader(new FileInputStream(args[0]));
      }catch(FileNotFoundException e) {
        System.out.println("Error: " + args[0] + " could not be found.");
        System.exit(2);
      }
    }else{
      System.out.println("usage: java HW20 [<filename>]");
      System.exit(2);
    }

    LineNumberReader r = new LineNumberReader(i);
    Scanner sc = new Scanner(r);

    try {
      System.out.println(Mystery.compute(sc));
    } catch (Exception e)    {
      System.out.println("Error: " + r.getLineNumber() + ": " + e.getMessage());
    }
  }
}
