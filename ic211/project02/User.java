import java.util.*;

/**
 * This class emulates a user to the vault
 * Users have a name, a hash of their password, and the type of hash used
 * Each user also has an arraylist of data that the user has
 * @author Hanling, Mike - 202430
 */
public class User {
  private String name;
  private String hashAlg;
  private String passHash;
  private ArrayList<Datum> data = new ArrayList<Datum>();

  /**
   * Constructor for User
   * @param name The string of the name of the user
   * @param hashAlg The string of the hash algorithm used for the password
   * @param passHash The string of the hash of the password for the user
   */
  public User(String name, String hashAlg, String passHash) {
    this.name = name;
    this.hashAlg = hashAlg;
    this.passHash = passHash;
  }

  
  /**
   * Gets the name associated with the User
   * @return The string of the name of the User
   */
  public String getName() { return this.name; }
  
  /**
   * Gets the hash of the password of the User
   * @return The string that is the hash of the password
   */
  public String getHash() { return this.passHash; }
 
  /**
   * Gets the hash algorithm used by this User for the password
   * @return The string of the hash algorithm used for the password
   */
  public String getHashAlg() { return this.hashAlg; }
  
  /**
   * Checks if the given password corresponds to the hash of the password for
   * this User
   * Returns true if the password matches
   * Returns false otherwise
   * Checks if the algorithm is supported
   * @param password This is the plaintext password that needs to be checked
   * @return True for a match; false for not matching
   * @throws UnsupportedHashException If the hash algorithm associated with the
   * User is not supported, this exception is thrown
   */
  public boolean validate(char[] password) throws UnsupportedHashException {
    Hasher hasher = null;
    if (this.hashAlg.equals("clear"))
      hasher = new Clear();
    else if (this.hashAlg.equals("shift+caesar"))
      hasher = new Caesar();
    else if (this.hashAlg.equals("shift+vigenere"))
      hasher = new Vigenere();
    else
      throw new UnsupportedHashException(hashAlg);
    try {
      if (hasher.hash(password).equals(this.passHash))
        return true;
    }catch (BadCharException e) {}

    return false;
  }

  /**
   * Given the encrypted data and the algorithm used to encrypt, this will add a
   * datum to the User's data list
   * @param cipher The string of the encrypted datum
   * @param encAlg The string of the encryption algorithm used on the datum
   */
  public void addDatum(String cipher, String encAlg) {
    this.data.add(new Datum(cipher, encAlg));
  }

  /**
   * Gets the data associated with this User in form of ArrayList
   * @return An ArrayList of Datum of all stored data for this User
   */
  public ArrayList<Datum> getData() { return this.data; }
}
