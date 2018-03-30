/**
 * PDF Header is %PDF or 25 50 44 46
 * This recognizer check whether the first 4 bytes match this header
 */
public class RecogPDF extends RecogASCII {

  private static int[] header = { 0x25, 0x50, 0x44, 0x46 };
  private int i = 0;

  /**
   * Returns the name of this type
   * "PDF"
   */
  public String getName() {
    return "PDF";
  }

  /**
   * Function to ensure that header either matches or not matches a PDF
   */
  public void feed(int nextByte) {
    if (getState() == 2) {
      if (nextByte != header[i]) {
        setState(0);
      }
    }
    i++;

    if ((i > 3) && (getState() != 0)) {
      setState(1);
    }
  }

  /**
   * Returns whether or not this is a PDF or not
   */
  boolean decision() {
    return getState() == 1;
  }
}
