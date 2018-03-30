public interface Hasher {

  public String getHashName();
  public String hash(char[] password);
  static char[] shift(char[] str, int shift) {
    int len = new String(str).length();
    char[] shifted = new char[len];
    for (int i = 0; i < len; i++) {
      shifted[i] = str[(i+shift)%len];
    }
    return shifted;
  }
}
