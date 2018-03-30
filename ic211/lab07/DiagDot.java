/**
 * Mike Hanling
 *
 * Diagoinal Dot
 */
public class DiagDot extends DirDot {
  
  private int dir; 
  
  /**
   * Constructor
   */
  public DiagDot(int r, int c, int d) {
    super(r, c, d);
    this.dir = d;
  }

  /**
   * Moves the Green Dot
   * Changes both the column and row
   * Basically, N is now NE
   */
  public void move() {
    if (dir == 0) {
      this.incCol();
      this.incRow();
    }else if (dir == 1) {
      this.incRow();
      this.decCol();
    }else if (dir == 2) {
      this.decCol();
      this.decRow();
    }else if (dir == 3) {
      this.decRow();
      this.incCol();
    }
  }

  /**
   * Takes 0, 1, or 2
   * 0: Straight
   * 1: Right
   * 2: Left
   */
  public void turn(int t) {
    if (t == 1)
      this.dir = (this.dir + 1) % 4;
    else if (t == 2)
      this.dir = (this.dir + 3) % 4;
  }

  /**
   * How the DiagDot will print
   */
  public String toString() {
    return super.toString();
  }

}
