public class Clear implements Encryptor, Hasher {
  
  public String getAlgName() { return "clear"; }

  public void   init(char[] key) {
    for (int i = 0; i < new String(key).length(); i++) {
      if ((int)key[i] < 42 || (int)key[i] > 122) {
        throw new BadCharException(key[i] + " not allowed in key");
      }
    }
  }
  public String encrypt(String plain) { 
    char[] p = plain.toCharArray();
    for (int i = 0; i < new String(plain).length(); i++) {
      if ((int)p[i] < 42 || (int)p[i] > 122) {
        throw new BadCharException(p[i] + " not allowed in plaintext");
      }
    }
    return plain; 
  }
  public String decrypt(String cipher){ return cipher; }


  public String getHashName() { return "clear"; }

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
