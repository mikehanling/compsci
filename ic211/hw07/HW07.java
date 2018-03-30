import java.util.*;

/**
 * This is the main for HW07
 * Create a queue
 * Fill it
 * then print it back, one word per line
 * ENDS WITH done FOR INPUT
 */
public class HW07 {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    Queue q = new Queue();
    String cur = sc.next();
    while (!cur.equals("done")) {
      q.enqueue(cur);
      cur = sc.next();
    }
    while (!q.empty()) {
      System.out.println(q.dequeue());
    }
  }
}
