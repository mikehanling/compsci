import java.util.*;

public class Ex1 {
  public static void main(String[] args) {
    Scanner sc   = new Scanner(System.in);
    PeekaQueue Q = new PeekaQueue();
    String     s = sc.next();

    while (!s.equals(";")) {
      if (Q.empty() || !s.equals(Q.peek())) {
        Q.enqueue(s);
      } else {
        Q.dequeue();
      }
      s = sc.next();
    }
    System.out.println(Q.empty() ?
                       "success" :
                       "failure");
  }
}
