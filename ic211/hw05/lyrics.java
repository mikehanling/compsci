//Mike Hanling

import java.util.*;


public class lyrics {
  
  public static void bottles(int start) {
    Countdown nums = new Countdown(start, 1);
    String cur = nums.next();
    String bottles = "bottles";

    for (int i = start; i > -1; i--) {
      if (i == 0) {
        System.out.println("no more bottles of beer on the wall.");
        System.out.println();
      }else {
        if (i == 1) bottles = "bottle";
        if (i != start) {
          System.out.println(cur + " " + bottles + " of beer on the wall.");
          System.out.println();
        }
        System.out.println(cur.substring(0,1).toUpperCase() + cur.substring(1)
                         + " " + bottles + " of beer on the wall, " + cur 
                         + " " + bottles + " of beer.");
        System.out.print("Take one down and pass it around, ");
        cur = nums.next();
      }
    }
  }


  public static void main(String[] args) {
    bottles(99);
  }


}
