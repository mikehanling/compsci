//Mike Hanling
//Point class

import java.util.*;

public class Point{
  private double X;
  private double Y;

  public Point(double x, double y) {
    X = x;
    Y = y;
  }

  public static Point read(Scanner sc) {
    Point p = new Point(sc.nextDouble(), sc.nextDouble());
    return p;
  }

  public String toString() {
    return this.X + " " + this.Y;
  }

  public double getX() {
    return this.X;
  }

  public double getY() {
    return this.Y;
  }



  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    String in = "";
    Point p;

    while (sc.hasNextDouble()) {
      p = read(sc);
      System.out.println("Your latest point prints as: " + p.toString());
      System.out.println("getX() returns: " + p.getX());
      System.out.println("getY() returns: " + p.getY());
    }
  }

}
