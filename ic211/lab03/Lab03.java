//Mike Hanling
//class Lab03

import java.util.*;

public class Lab03 {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String cmd = sc.next();
    Box b = null;
    int started = 0;

    while (!cmd.equals("done")) {
      if (cmd.equals("add")) {      
        if (started == 0) {
          Point init = Point.read(sc);
          b = new Box(init);
          started =1;
        }else b.growBy(Point.read(sc));
      }else if (cmd.equals("box")) {
        System.out.println(b.toString());
      }else if (cmd.equals("map")) {
        try {
          System.out.println(b.mapIntoUnitSquare(Point.read(sc)).toString());
        }catch(NullPointerException e) {
          System.out.println("error");
        }
      }else {
        System.out.println("Error! Unknown command \"" + cmd + "\"!");
        String trash = sc.nextLine();
      }
      cmd = sc.next();
    }
  }
}
