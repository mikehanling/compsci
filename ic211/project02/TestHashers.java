import java.util.*;

/**
 * This class is used to test that the Hashers are operating as intended
 * To add a new type of Hasher, add a similar "add" statement at MARK
 * @author Hanling, Mike - 202430
 * @author IC211
 */
public class TestHashers {
  
  /**
   * This main creates an ArrayList of all types of Hashers, then asks the
   * user for which type to test, along with a pasword; the
   * password is encrypted and printed back to the screen for testing
   * capabilities
   * @param args Not utilized in this class
   * @throws Exception If the given algorithm is not supported, this exception
   * is thrown
   */
  public static void main(String[] args) throws Exception {
    // Create ArrayList of all supported hasherss
    ArrayList<Hasher> E = new ArrayList<Hasher>();
    E.add(new Clear());
    E.add(new Caesar());
    E.add(new Vigenere());
    // MARK

    // Get alg,psw,msg from user
    System.out.print("algorithm: ");
    String encalg = System.console().readLine();
    System.out.print("password : ");
    char[] password = System.console().readPassword();

    // Find index of encryptor (throw exception if not found)
    int i = -1;
    try { while(!E.get(++i).getHashName().equals(encalg)); }
    catch(Exception e) { throw new Exception("Unknown algorithm '" + encalg +"'."); }

    // Encrypt, decrypt print sumamry of results
    String hash = E.get(i).hash(password);
    System.out.println("password read : " + new String(password));
    System.out.println("hash computed : " + hash);
  }
}
