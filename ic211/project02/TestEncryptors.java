import java.util.*;

/**
 * This class is used to test that the Encryptors are operating as intended
 * To add a new type of Encryptor, add a similar "add" statement at MARK
 * @author Hanling, Mike - 202430
 * @author IC211
 */
public class TestEncryptors {
  
  /**
   * This main creates an ArrayList of all types of Encryptors, then asks the
   * user for which type to test, along with a pasword and a message; the
   * message is encrypted and printed back to the screen for testing
   * capabilities
   * @param args Not utilized in this class
   * @throws Exception If the given algorithm is not supported, then this
   * Exception is thrown
   */
  public static void main(String[] args) throws Exception {
    // Create ArrayList of all supported encryptors
    ArrayList<Encryptor> E = new ArrayList<Encryptor>();
    E.add(new Clear());
    E.add(new Caesar());
    E.add(new Vigenere());
    // MARK
    

    // Get alg,psw,msg from user
    System.out.print("algorithm: ");
    String encalg = System.console().readLine();
    System.out.print("password : ");
    char[] password = System.console().readPassword();
    System.out.print("message  : ");
    String plaintext = System.console().readLine();

    // Find index of encryptor (throw exception if not found)
    int i = -1;
    try { while(!E.get(++i).getAlgName().equals(encalg)); }
    catch(Exception e) { throw new Exception("Unknown algorithm '" + encalg +"'."); }

    // Encrypt, decrypt print sumamry of results
    E.get(i).init(password);
    String ciphertext = E.get(i).encrypt(plaintext);
    String hopefully = E.get(i).decrypt(ciphertext);
    System.out.println("plain : " + plaintext);
    System.out.println("cipher: " + ciphertext);
    System.out.println("decryp: " + hopefully);
  }
}
