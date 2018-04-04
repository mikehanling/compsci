import java.io.*;
import java.util.*;

/**
 * This serves as both an Encryptor and Hasher
 * The Vigenere Cipher algorithm is applied, given the key to do so
 * It does ensure that all input and output are of valid characters
 * @author Hanling, Mike - 202430
 */
public class Vigenere implements Encryptor, Hasher {

  private String algName = "vigenere";
  private char[] key;
  private int keyLen;

  /**
   * Gets the name of this type of algorithm
   * @return "caesar" as that is the algorithm name
   */
  public String getAlgName() { return this.algName; }

  /**
   * Initialized the encryptor with the given key, so that subsequent use is
   * ready to encrypt/decrypt without entering the key
   * characters
   * @param key A char array of the key to be saved
   * @throws BadCharException If any char in the key is not in the valid range,
   * this exception is thrown
   */
  public void   init(char[] key) throws BadCharException {
    for (int i = 0; i < new String(key).length(); i++) {
      if ((int)key[i] < 42 || (int)key[i] > 122) {
        throw new BadCharException(key[i] + " not allowed in key");
      }
    }
    this.key = key;
    this.keyLen = new String(key).length();
  }

  /**
   * Takes a string, ensures that it is in the valid character set, encrypts it,
   * and returns that cipher back
   * @param plain The string of the plain text to be encrypted
   * @return The cipher string (encrypted)
   * @throws BadCharException If any char in the plain text is invalid, this
   * exception is thrown
   */
  public String encrypt(String plain) throws BadCharException {
    char[] cipher = plain.toCharArray();
    for (int i = 0; i < plain.length(); i++) {
      if ((int)cipher[i] < 42 || (int)cipher[i] > 122) {
        throw new BadCharException(cipher[i] + " not allowed in plaintext");
      }
      int k = (int)this.key[i%this.keyLen] - 42;
      int p = (int)cipher[i] - 42;
      int c = (p + k) % 81;
      cipher[i] = (char)(42 + c);
    }

    return new String(cipher);
  }

  /**
   * Takes an encrypted string, ensures all characters are in range, decrypts
   * it, and returns the plain text back
   * @param cipher The string of the cipher to be decryped
   * @return The plain text string (decrypted)
   * @throws BadCharException If any char in the cipher is invalid, this
   * exception is thrown
   */
  public String decrypt(String cipher) throws BadCharException{
    char[] plain = cipher.toCharArray();
    for (int i = 0; i < cipher.length(); i++) {
      if ((int)plain[i] < 42 || (int)plain[i] > 122) {
        throw new BadCharException(plain[i] + " not allowed in ciphertext");
      }
      int k = (int)this.key[i%this.keyLen] - 42;
      int c = (int)plain[i] - 42;
      int p = (c + (81 - k)) % 81;
      plain[i] = (char)(42 + p);
    }

    return new String(plain);
  }


  /**
   * Gets the name of the hash algorithm
   * @return "shift+vigenere" as that is the hash algorithm
   */
  public String getHashName() { return "shift+" + this.algName; }

  /**
   * Hashes a given char array, and then returns the result as a string
   * @param password The char array that will be hashed
   * @return The string of the hash of password
   * @throws BadCharException If any char in the array is invalid, this exceptio
   * is thrown
   */
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
