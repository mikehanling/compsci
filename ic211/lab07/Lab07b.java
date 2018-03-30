import java.util.*;
/**
 * Mike Hanling
 * Lab07b
 *
 * Main driver for Part 1 - OOP Version of Plotting Program
 */
public class Lab07b {

  public static void main(String[] args) {

    Random rand = new Random(System.currentTimeMillis());

    ArrayList<DirDot> dots = new ArrayList<DirDot>(2);

    int count = 0;
    while (true) {
      //add two new dots every 200 cycles
      if (count % 200 == 0) {
        dots.add(new RedDot( 45, 50, rand.nextInt(3)));
        dots.add(new BlueDot(55, 50, rand.nextInt(3)));
      }

      //print each dot and move
      for (int i = 0; i < dots.size(); i++) {
        System.out.println(dots.get(i));
        dots.get(i).move();
        dots.get(i).turn(rand.nextInt(3));
      }
      System.out.println("done");

      count++;
    }
  }
  
}
