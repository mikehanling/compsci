import java.util.*;

public class User {
  private String name;
  private Hasher hasher;
  private String passHash;
  private ArrayList<Datum> data = new ArrayList<Datum>();

  public User(String name, String hashAlg, String passHash) throws UnsupportedHashException {
    this.name = name;
    if (hashAlg.equals("clear"))
      this.hasher = new Clear();
    else if (hashAlg.equals("shift+caesar"))
      this.hasher = new Caesar();
    else if (hashAlg.equals("shift+vigenere"))
      this.hasher = new Vigenere();
    else
      throw new UnsupportedHashException(hashAlg);
    this.passHash = passHash;
  }

  public String getName() { return this.name; }
  public String getHash() { return this.passHash; }
  public String getHashAlg() { return this.hasher.getHashName(); }
  
  public boolean validate(char[] password) {
    try {
      if (this.hasher.hash(password).equals(this.passHash))
        return true;
    }catch (BadCharException e) {}
    return false;
  }

  
  public void addDatum(String cipher, String encAlg) {
    this.data.add(new Datum(cipher, encAlg));
  }

  public ArrayList<Datum> getData() { return this.data; }
}
