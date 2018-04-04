/**
 * This class emulated one datum
 * Each Datum has its own Encryptor and the encrypted version of the data
 * @author Hanling, Mike - 202430
 */
public class Datum {
  private String cipher;
  private Encryptor enc;

  /**
   * Constructor for one Datum
   * @param encAlg The string of the encryption algorithm used of the data
   * @param cipher The string of the data (encrypted)
   */
  public Datum(String encAlg, String cipher) {
    if (encAlg.equals("clear"))
      this.enc = new Clear();
    else if (encAlg.equals("caesar"))
      this.enc = new Caesar();
    else if (encAlg.equals("vigenere"))
      this.enc = new Vigenere();

    this.cipher = cipher;
  }

  /**
   * Gets the encrypted cipher that this Datum holds
   * @return The string of the cipher stored in this Datum
   */
  public String getCipher() { return this.cipher; }
  
  /**
   * Gets the name of the encryption algorithm used
   * @return The String of the encryption algorithm used on this Datum
   */
  public String getEncAlg() { return this.enc.getAlgName(); }
  
  /**
   * Gets the Encryptor for this Datum
   * @return The Encyptor assoicated with this Datum
   */
  public Encryptor getEnc() { return this.enc; }

}
