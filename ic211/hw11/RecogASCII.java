public class RecogASCII {
  /**
   * Returns the name of the category this tests for.
   */
  public String getName() {
    return "ASCII";
  }

  /**
   * Processes the next bye of the file.
   */
  public void feed(int nextByte) {
    if ((nextByte < 0) || (127 < nextByte)) {
      setState(0);
    }
  }

  /**
   * Returns true if the file (as processed so far) is an
   * ASCII file.
   */
  boolean decision() {
    return state != 0;
  }

  /**
   * The recognizer's states are 0, 1 and 2.
   * 2 means status of file unknown, 0 means definitely not a
   * a match (e.g. not an ASCII file), and 1 means definitely
   * a match.  This method returs the current state of the
   * recognizer.
   */
  public int getState() {
    return state;
  }

  /**
   * Sets the recognizer's state (see above).
   */
  public void setState(int v) {
    state = v;
  }

  private int state = 2; // 2 : unknown, 1 : match, 0 : not match
}
