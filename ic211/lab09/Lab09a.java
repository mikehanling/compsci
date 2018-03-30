import java.util.*;

public class Lab09a {
  public static void main(String[] args) {
    Scanner  sc = new Scanner(System.in);
    ModQueue Q  = new ModQueue();

    do {
      System.out.print("> ");
      String s = sc.next();

      if (s.equals("quit")) {
        break;
      } else if (s.equals("clearto")) {
        Q.dequeue(sc.next());
      } else if (s.equals("add"))   {
        Q.enqueue(sc.next());
      } else if (s.equals("dump"))   {
        System.out.println(Q.dump());
      }
    } while (true);
  }
}
