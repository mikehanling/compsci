/**
 * INTERFACE
 * This interface is for any hashing algorithm
 * The algorithm must have a name, and a method to hash must be implemented for
 * this interface
 * There is a static method available for shifting characters, which is usually
 * used in hashing
 * @author Hanling, Mike - 202430
 */
public interface Hasher {

  public String getHashName();
  public String hash(char[] password);

  /**
   * Given a char array, this will shift the characters to the left by the
   * specified number
   * @param str The char array to be shifted
   * @param shift The int of how many times to shift
   * @return The shifted char array
   */
  static char[] shift(char[] str, int shift) {
    int len = new String(str).length();
    char[] shifted = new char[len];
    for (int i = 0; i < len; i++) {
      shifted[i] = str[(i+shift)%len];
    }
    return shifted;
  }
}
