import java.util.*;

public class HW03 {
  public static Mid createMid() {
    Scanner in = new Scanner(System.in);
    System.out.print("Alpha? ");
    String alpha = in.next();

    System.out.print("First name? ");
    String first = in.next();

    System.out.print("Last name? ");
    String last = in.next();

    System.out.print("Company? ");
    int company = in.nextInt();

    Mid mid = new Mid();
    mid.alpha = alpha;
    mid.firstName = first;
    mid.lastName = last;
    mid.company = company;

    return mid;
  }
  
  public static void printMid(Mid mid) {
    System.out.println(mid.alpha + " " + mid.firstName + " "
                      + mid.lastName + " " + mid.company);
  }

  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    System.out.print("How many mids? ");
    int num = in.nextInt();

    Mid[] mids = new Mid[num];
    for (int i = 0; i < mids.length; i++) {
      mids[i] = createMid();
    }

    System.out.print("What company would like to print out? ");
    int compr = in.nextInt();
    for (int i = 0; i < mids.length; i++) {
      if (mids[i].company == compr) printMid(mids[i]);
    }
  }
}
