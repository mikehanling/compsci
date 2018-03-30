//Mike Hanling
//class Box

import java.util.*;

public class Box {
  private ArrayList<Point> ps = new ArrayList<Point>();
  private double xmin;
  private double xmax;
  private double ymin;
  private double ymax;

  // constructor for Box that consists of a single point
  public Box(Point p) {
    ps.add(p);
    xmin = xmax = p.getX();
    ymin = ymax = p.getY();
  }

  // constructor for the Box containing two initial points
  public Box(Point a, Point b) {
    ps.add(a);
    ps.add(b);
    if (a.getX() > b.getX()) {
      xmin = b.getX();
      xmax = a.getX();
    }else {
      xmin = a.getX();
      xmax = b.getX();
    }
    if (a.getY() > b.getY()) {
      ymin = b.getY();
      ymax = a.getY();
    }else {
      ymin = a.getY();
      ymax = b.getY();
    }
  }

  // growBy(p) expands the bounding box (if needed) to include point p
  public void growBy(Point p) {
    ps.add(p);
    if (p.getX() < xmin) xmin = p.getX();
    if (p.getX() > xmax) xmax = p.getX();
    if (p.getY() < ymin) ymin = p.getY();
    if (p.getY() > ymax) ymax = p.getY();
  }

  // given point p in the bounding box, returns associated point in the
  // unit square (see notes); returns null if p is not inside the bounding box.
  public Point mapIntoUnitSquare(Point p) {
    if (p.getX() >= xmin && p.getX() <= xmax &&
        p.getY() >= ymin && p.getY() <= ymax) {
      double newx = (p.getX() - xmin) / (xmax-xmin);
      double newy = (p.getY() - ymin) / (ymax-ymin);
      return new Point(newx, newy);
    }
    return null;
  }

  // returns string representation like: 2.0 < x < 9.0, 3.0 < y < 7.0
  public String toString() {
    return xmin + " < x < " + xmax + ", " + ymin + " < y < " + ymax;
  }

  public static void main(String[] args) {
    System.out.println("Enter points. Points must take two doubles.");
    Scanner sc = new Scanner(System.in);
    Point a = new Point(sc.nextDouble(), sc.nextDouble());
    Box b = new Box(a);
    Point map = new Point(5,5);

    while (sc.hasNextDouble()) {
      b.growBy(new Point(sc.nextDouble(), sc.nextDouble()));
      System.out.println("Current Box: " + b.toString());
      System.out.println("Mapping of (5,5): "
          + b.mapIntoUnitSquare(map).toString());
    }
  }

}
