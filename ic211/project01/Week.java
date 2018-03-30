import java.util.*;
/**
 * Mike Hanling
 * 202430
 * 
 * This class is to represent a week and busy times
 * based on USNA class periods
 */
public class Week {

  private boolean[][] busyPeriods; 

  /**
   * Constructor for empty schedule
   */
  public Week() {
    this.busyPeriods = new boolean[5][6];
  }

  /**
   * COnstructor that takes one class
   */
  public Week(String meetingTimes) {
    this.busyPeriods = new boolean[5][6];
    String[] exTimes = DrBrown.explode(meetingTimes);
    for (int i = 0; i < exTimes.length; i++) {
      int day = -1;
      switch (exTimes[i].charAt(0)) {
        case 'M':   day = 0;
                    break;
        case 'T':   day = 1;
                    break;
        case 'W':   day = 2;
                    break;
        case 'R':   day = 3;
                    break;
        case 'F':   day = 4;
                    break;
      }

      this.busyPeriods[day][exTimes[i].charAt(1) - '0' - 1] = true;
    }
  }

  /**
   * This will merge two Weeks together
   * Basically an OR with busy = 1
   */
  public Week mergeWith(Week w) {
    Week merged = new Week();

    for (int i = 0; i < this.busyPeriods.length; i++) {
      for (int k = 0; k < this.busyPeriods[0].length; k++) {
        if (this.busyPeriods[i][k] || w.busyPeriods[i][k])
          merged.busyPeriods[i][k] = true;
      }
    }

    return merged;
  }

  /**
   * This will merge two Weeks together
   * given a string to create the second Week
   */
  public Week mergeWith(String meetingTimes) {
    Week merged = new Week(meetingTimes);

    for (int i = 0; i < this.busyPeriods.length; i++) {
      for (int k = 0; k < this.busyPeriods[0].length; k++) {
        if (this.busyPeriods[i][k] || merged.busyPeriods[i][k])
          merged.busyPeriods[i][k] = true;
      }
    }

    return merged;
  }
  /**
   * This will print the schedule in the correct format
   */
  public String toString() {
    String out = "  M T W R F\n";
    for (int i = 0; i < 6; i++) {
      out += (i+1);
      for (int k = 0; k < 5; k++) {
        out += (this.busyPeriods[k][i] ? " x" : "  ");
      }
      out += "\n";
    }
    return out;
  }

  public static void main(String[] args) {
    Week w = new Week();
    System.out.print(w);

    Scanner sc = new Scanner(System.in);
    String in = null;
    in = sc.next();
    Week next;
    while (!in.equals("quit")) {
      next = new Week(in);
      w = w.mergeWith(next);
      System.out.print(w);
      in = sc.next();
    }

  }

}
