import java.util.*;

public class HWa
{
  public static class APair
  {
    Object x, y;
    public APair(Object o1, Object o2)
    {
      x = o1;
      y = o2;
    }
    public Object first() { return x; }
    public Object second() { return y; }
  }

  public static class BPair<T>
  {
    T x, y;
    public BPair(T o1, T o2)
    {
      x = o1;
      y = o2;
    }
    public T first() { return x; }
    public T second() { return y; }
  }

  public interface Fooable
  {
    public String foo();
  }

  public static class CPair
  {
    Fooable x, y;
    public CPair(Fooable o1, Fooable o2)
    {
      x = o1;
      y = o2;
    }
    public Fooable first() { return x; }
    public Fooable second() { return y; }
  }

  public static class Bat implements Fooable
  {
    int val;
    public Bat(int k) { val = k; }
    public String foo() { return "Bat" + val; }
    public int bar() { return val*val; }
  }

  public static class Pig implements Fooable
  {
    String lab;
    public Pig(String s) { lab = s; }
    public String foo() { return "Pig" + lab; }
  }

  public static void main(String[] args)
  {
    APair a = new APair(new Bat(7), new Pig("Q"));
    BPair<Bat> b = new BPair<Bat>(new Bat(8), new Bat(9));
    CPair c = new CPair(new Bat(5), new Pig("Z"));;
    System.out.println(((Fooable)(a.first())).foo());
    System.out.println(b.first().foo());
    System.out.println(c.first().foo());
    System.out.println(((Bat)(a.first())).bar());
    System.out.println(b.first().bar());
    System.out.println(((Bat)(c.first())).bar());
  }
}
