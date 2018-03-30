import java.util.*;

public class Time {
  int hh,mm,ss;
  public boolean equal(Time t) {
    if (this.hh == t.hh && this.mm == t.mm && this.ss == t.ss) return true;
    return false;
  }
  public static boolean equal(Time t1, Time t2) {
    if (t1.hh == t2.hh && t1.mm == t2.mm && t1.ss == t2.ss) return true;
    return false;
  }
}
