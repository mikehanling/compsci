/**
 * Mike Hanling
 *
 * Basic Dot Class
 */
public class Dot {

  private int row;
  private int col;

  /**
   * Constructor
   */
  public Dot(int r, int c) {
    this.row = r;
    this.col = c;
  }

  /**
   * Increments the row number
   */
  public void incRow() {
    this.row++;
  }

  /**
   * Decrements the row number
   */
  public void decRow() {
    this.row--;
  }

  /**
   * Increments the column number
   */
  public void incCol() {
    this.col++;
  }

  /**
   * Decrements the column number
   */
  public void decCol() {
    this.col--;
  }

  /**
   * How the Dot will print to the screen
   */
  public String toString() {
    return this.row + " " + this.col;
  }

}
