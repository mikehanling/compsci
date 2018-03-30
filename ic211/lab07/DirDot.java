/**
 * Mike Hanling
 *
 * Directional Dot
 */
public class DirDot extends Dot {
  
  private int dir; 
  
  /**
   * Constructor
   */
  public DirDot(int r, int c, int d) {
    super(r, c);
    this.dir = d;
  }

  /**
   * Moves the DirDot in the direction it knows
   */
  public void move() {
    if (dir == 0)
      this.incCol();
    else if (dir == 1)
      this.incRow();
    else if (dir == 2)
      this.decCol();
    else if (dir == 3)
      this.decRow();
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
   * How the DirDot will print
   */
  public String toString() {
    return super.toString();
  }

}
