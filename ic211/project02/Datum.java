public class Datum {
  private String cipher;
  private Encryptor enc;

  public Datum(String encAlg, String cipher) {
    if (encAlg.equals("clear"))
      this.enc = new Clear();
    else if (encAlg.equals("caesar"))
      this.enc = new Caesar();
    else if (encAlg.equals("vigenere"))
      this.enc = new Vigenere();

    this.cipher = cipher;
  }

  public String getCipher() { return this.cipher; }
  public String getEncAlg() { return this.enc.getAlgName(); }
  public Encryptor getEnc() { return this.enc; }

}
