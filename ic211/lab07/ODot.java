import java.util.*;
/**
 * Mike Hanling
 *
 * Orange/Out-of-control Dot will move in a diagonal pattern 
 * every 50th cycle for 20 cycles
 */
public class ODot extends DirDot {

  private int lastDiag = 1;
  private int curr = 0;
  private int initT;
  private int secondT;
  private int color = 3;
  private static String[] colors= { " r", " g", " b", 
                                    " o", " y", " m", " p" };

  /**
   * Constructor
   */
  public ODot(int r, int c, int d) {
    super(r, c, d);
  }

  /**
   * Turns ODot 30 cycles after a diagonal run
   * Diagonal runs are 20 cycles
   */
  public void turn(int t) {
    //once the end of a straight leg has been reached...
    if (this.lastDiag == 30) {
      //turn, reset length, setup diagnol leg
      super.turn(t);
      this.lastDiag = 1;
      this.curr = 1;
      this.initT = (t == 0 ? 1 : t);
      this.secondT = (this.initT == 1 ? 2 : 1);
    //when in a diagonal leg...
    }else if (curr != 0 && curr < 21) {
      //choose the correct turn, make it, change color, update length
      if (this.curr % 2 == 1)
        super.turn(this.secondT);
      else
        super.turn(this.initT);
      this.color = (this.color+1)%7;
      this.curr++;
    //when in a straigh leg...
    }else {
      //update length
      this.lastDiag++;
      this.curr = 0;
    }
  }

  /**
   * How the ODot should be printed
   */
  public String toString() {
    return super.toString() + ODot.colors[this.color];
  }

}

