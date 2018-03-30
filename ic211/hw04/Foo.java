import java.util.*;

public class Foo {
  public static void main(String[] args) {
    Time A = new Time();
    A.hh = 20;
    A.mm = 20;
    A.ss = 20;
    Time B = new Time();
    B.hh = 20;
    B.mm = 20;
    B.ss = 20;
    System.out.println(A.equal(B));
    System.out.println(Time.equal(A,B));
  }
}
