import java.io.*;
import java.util.*;

public class Caesar implements Encryptor, Hasher {

  private String algName = "caesar";
  private int shift;


  public String getAlgName() { return this.algName; }

  public void   init(char[] key) throws BadCharException {
    int sc = 18;
    for (int i = 0; i < new String(key).length(); i++) {
      if ((int)key[i] < 42 || (int)key[i] > 122) {
        throw new BadCharException(key[i] + " not allowed in key");
      }
      sc += (int)key[i]-42;
    }
    sc %= 81;
    sc += 42;

    this.shift = sc;

  }

  public String encrypt(String plain) throws BadCharException {
    char[] cipher = plain.toCharArray();
    for (int i = 0; i < plain.length(); i++) {
      if ((int)cipher[i] < 42 || (int)cipher[i] > 122) {
        throw new BadCharException(cipher[i] + " not allowed in plaintext");
      }
      int k = this.shift - 42;
      int p = (int)cipher[i] - 42;
      int c = (p + k) % 81;
      cipher[i] = (char)(42 + c);
    }

    return new String(cipher);
  }

  public String decrypt(String cipher) {
    char[] plain = cipher.toCharArray();
    for (int i = 0; i < cipher.length(); i++) {
      int k = this.shift - 42;
      int c = (int)plain[i] - 42;
      int p = (c + (81 - k)) % 81;
      plain[i] = (char)(42 + p);
    }

    return new String(plain);
  }



  public String getHashName() { return "shift+" + this.algName; }

  public String hash(char[] password) throws BadCharException {
    this.init(password);
    char[] vector = "GO_NAVY_2018^mid".toCharArray();
    for (int i = 0; i < 16; i++) {
      char c = vector[i];
      int k = (int)c % 16;
      vector = Hasher.shift(vector, k);
      vector = this.encrypt(new String(vector)).toCharArray();
    }
     return new String(vector);
  }
}
