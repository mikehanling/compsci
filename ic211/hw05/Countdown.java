public class Countdown {
  // initializes Countdown with "startat" as the first value in the countdown,
  // and "endat" as the last value.  Should have 1,000,000 > startat >= endat >=
  // 0.
  public Countdown(int startat,
                   int endat) {
    ctr  = startat;
    last = endat;
  }

  // returns string of the "next" countdown number (e.g. "nine") and counts
  // down.
  // so, for example, if next() gives "ten", the next call to next() gives
  // "nine"
  // any calls after the "endat" value will return null.
  public String next() {
    if (ctr < 0) {
      return null;
    }
    String res = ctrToString();
    ctr--;
    return res;
  }

  // returns true if the "endat" value has been returned by a call to next()
  public boolean done() {
    return ctr < last;
  }

  private int ctr, last;
  private String ctrToString() {
    return numToString(ctr);
  }

  private static String numToString(int num) {
    String A[] = {
      "zero",     "one",         "two",         "three",    "four",     "five",
      "six",
      "seven",     "eight", "nine",
      "ten",      "eleven", "twelve", "thirteen", "fourteen", "fifteen",
      "sixteen", "seventeen",
      "eighteen", "nineteen"
    };
    String B[] = {
      "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty",
      "ninety"
    };

    if (num < 20) {
      return A[num];
    }

    if (num < 100) {
      return B[num / 10] + (num % 10 == 0 ? "" : " " + A[num % 10]);
    }

    if (num < 1000) {
      return numToString(num /
                         100) + " hundred" +
             (num % 100 == 0 ? "" : " " + numToString(num % 100));
    }

    if (num < 1000000) {
      return numToString(num /
                         1000) + " thousand" +
             (num % 1000 == 0 ? "" : " " + numToString(num % 1000));
    }
    return "";
  }

  public static void main(String[] args) {
    Countdown A = new Countdown(10, 1);

    while (!A.done()) {
      System.out.println(A.next());
    }
    System.out.println("Blastoff!");
  }
}
