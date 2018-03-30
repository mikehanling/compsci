/**
 * JPG file header is FF D8 FF E0 xx xx 4A 46 49 46 00
 * This recognizer checks whether the first 11 bytes
 * match this header.
 */
public class RecogJPG extends RecogASCII {
  // NOTE: 0x starts of hex integer literals, so 0xFF is the int 255.
  private static int[] header =
  {
    0xFF, 0xD8, 0xFF, 0xE0, -1, -1, 0x4A, 0x46, 0x49, 0x46, 0x00
  };

  // 0     1     2     3     4   5   6     7     8     9     10
  private int i = 0;

  public String getName() {
    return "JPG";
  }

  public void feed(int nextByte) {
    if (getState() == 2) { // 2 : unkown
      if ((header[i] >= 0) && (nextByte != header[i])) {
        setState(0);       // 0 : not match
      }
    }
    i++;

    if ((i > 10) && (getState() != 0)) {
        setState(1); // 1 : match
    }
  }

  boolean decision() {
    return getState() == 1;
  }
}
