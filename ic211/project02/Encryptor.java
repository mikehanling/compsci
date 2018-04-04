/**
 * INTERFACE
 * This interface is for any algorithm for encrypting
 * The algorithm has to have a name, the Encryptor needs to be initialized, and
 * methods for encrypting and decrypting must be implemneted for this interface
 * @author Hanling, Mike - 202430
 */
public interface Encryptor {
  public String getAlgName();
  public void   init(char[] key);
  public String encrypt(String plain);
  public String decrypt(String cipher);
}
