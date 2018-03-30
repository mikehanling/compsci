import java.util.*;

public class Lab05 {
  public static void main(String[] args) {
    if (args.length!=1) {
      System.out.println("Usage: 'java Lab05 seedValue' where 'seedvalue' is a long");
      System.exit(1);
    }
    Random rand = new NRRandom(Long.parseLong(args[0]));
    for(int i = 0; i < 70; i++) {
      System.out.print(1 + rand.nextInt(6));
    }
    System.out.println();
  }
}
