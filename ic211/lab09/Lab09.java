import java.util.*;
import java.io.*;
/**
 * Driver class for <a href="http://faculty.cs.usna.edu/IC211/calendar.php?type=lab&event=9">IC211 Lab09</a>
 * @author Hanling, Mike - 202430
 * @author IC211
 */
public class Lab09 {
  
  /**
   * This is the main/driver for the Lab
   * Optional first argument "-v" is for verbose mode (useful error output)
   * Optional file argument will read from a file for all commands
   * STDIN will be read otherwise
   * Commands:
   *  add <em>string</em> : adds <em>string</em> to the end of the ModQueue
   *  dump : reports all strings in the queue to STDOUT
   *  clearto <em>string</em> : clears the queue in reverse input order up to
   *  and including <em>string</em>
   *  quit : exits process
   * @param args String[] arguments to Lab09 (optional -v / optional filename)
   */
  public static void main(String[] args) {
    boolean verbose = false;
    boolean fromFile = false;
    if (args.length > 0 && args[0].equals("-v"))
      verbose = true;

    Scanner sc = null;
    try {
      sc = new Scanner(new FileReader(verbose ? args[1] : args[0]));
      fromFile = true;
    } catch(IOException e) {
      System.out.println("File '" + (verbose ? args[1] : args[0]) + 
                         "' could not be opened; switching input to standard in.");
      sc = new Scanner(System.in);
    }catch(ArrayIndexOutOfBoundsException e) {
      sc = new Scanner(System.in);
    } 

    ModQueue Q  = new ModQueue();

    do {
      System.out.print(fromFile ? "" : "> ");
      String s = null;
      try {
        s = sc.next();
      }catch(NoSuchElementException e) {
        System.out.println();
        break;
      }

      if (s.equals("quit")) {
        
        break;
      
      }else if (s.equals("clearto")) {
        
        try {
          s = sc.next();
          Q.dequeue(s);
        }catch(QueueException e) {
          System.out.print(verbose ? "String '" + s + "' not found!\n" : "");
        }catch(NoSuchElementException e) {
          System.out.println("Unexpected end of input.");
          break;
        }

      } else if (s.equals("add"))   {
      
        try {
          Q.enqueue(sc.next());
        }catch(NoSuchElementException e) {
          System.out.println("Unexpected end of input.");
          break;
        }

      } else if (s.equals("dump"))   {
      
        try {
          System.out.println(Q.dump());
        }catch(QueueException e) {}

      }else {
        System.out.print(verbose ? "Unknown command '" + s + "'.\n" : "");
      }
    } while (true);
  }
}
