import java.util.*;
import java.io.*;
/**
 * Mike Hanling
 * Chris Daves
 *
 * Main driver of this lab
 * Reads in tweets and handles commands from user
 */
public class Lab06 {

  public static void main(String[] args) {
    SearchQueue orig = new SearchQueue();
    SearchQueue curr = new SearchQueue();
    QueueStack stack = new QueueStack();

    if (args.length != 1) {
      System.out.println("usage: java Lab06 <filename>");
      System.exit(1);
    }
    String fname = args[0];
    Scanner sc = null;
    try {
      sc = new Scanner(new FileReader(fname));
    } catch(IOException e) {
      e.printStackTrace(); System.exit(1);
    }
    int count = 0;
    while (sc.hasNextLine()) {
      Tweet t = Tweet.read(sc);
      orig.enqueue(t);
      curr.enqueue(t);
      orig.inc();
      curr.inc();
    }
    System.out.println(curr.getCount() + " tweets");

    sc = new Scanner(System.in);
    System.out.print("> ");
    String cmd = sc.next();
    while (!cmd.equals("quit")) {
      switch (cmd) {
        case "filter":    stack.push(curr);
                          curr = curr.filter(sc.next(), true);
                          System.out.println(curr.getCount() + " tweets");
                          break;

        case "filter!":   stack.push(curr);
                          curr = curr.filter(sc.next(), false);
                          System.out.println(curr.getCount() + " tweets");
                          break;

        case "dump":      curr.dump();
                          System.out.println(curr.getCount() + " tweets");
                          break;

        case "reset":     stack = new QueueStack();
                          curr = orig;
                          System.out.println(curr.getCount() + " tweets");
                          break;

        case "undo":      curr = (stack.empty() ? curr : stack.pop());
                          System.out.println(curr.getCount() + " tweets");
                          break;

        default:          System.out.println("Command not recognized! Please try again.");
      }

      System.out.print("> ");
      cmd = sc.next();
    }
  }
}

