/**
 * This serves as both an Encryptor and Hasher
 * There is no changing of the input when encrypting or decrypting
 * It does ensure that all input and output are of valid characters
 * @author Hanling, Mike - 202430
 */
public class Clear implements Encryptor, Hasher {
  
  /**
   * Gets the name of this type of algorithm
   * @return "clear" as that is the algorithm name
   */
  public String getAlgName() { return "clear"; }

  /**
   * Initialized the encryptor with the given key, so that subsequent use is
   * ready to encrypt/decrypt without entering the key
   * Since this algorithm does not use a key, it ultimately checks for valid
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
  }

  /**
   * Takes a string, ensures that it is in the valid character set, encrypts it,
   * and returns that cipher back
   * @param plain The string of the plain text to be encrypted
   * @return The cipher string (encrypted)
   * @throws BadCharException If any char in the plain text is invalid, this
   * exception is thrown
   */
  public String encrypt(String plain) throws BadCharException{ 
    char[] p = plain.toCharArray();
    for (int i = 0; i < new String(plain).length(); i++) {
      if ((int)p[i] < 42 || (int)p[i] > 122) {
        throw new BadCharException(p[i] + " not allowed in plaintext");
      }
    }
    return plain; 
  }

  /**
   * Takes an encrypted string, ensures all characters are in range, decrypts
   * it, and returns the plain text back
   * @param cipher The string of the cipher to be decryped
   * @return The plain text string (decrypted)
   * @throws BadCharException If any char in the cipher is invalid, this
   * exception is thrown
   */
  public String decrypt(String cipher) throws BadCharException {
    char[] c = cipher.toCharArray();
    for (int i = 0; i < new String(cipher).length(); i++) {
      if ((int)c[i] < 42 || (int)c[i] > 122) {
        throw new BadCharException(c[i] + " not allowed in ciphertext");
      }
    }
    return cipher;
  }


  /**
   * Gets the name of the hash algorithm
   * @return "clear" as that is the hash algorithm
   */
  public String getHashName() { return "clear"; }

  /**
   * Hashes a given char array, and then returns the result as a string
   * @param password The char array that will be hashed
   * @return The string of the hash of password
   * @throws BadCharException If any char in the array is invalid, this exceptio
   * is thrown
   */
  public String hash(char[] password) throws BadCharException {
    this.init(password);
    char[] hash = new char[16];
    for (int i = 0; i < 16; i++) {
      if (i < new String(password).length())
        hash[i] = password[i];
      else
        hash[i] = 'x';
    }
    return new String(hash);
  }
}
