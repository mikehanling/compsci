import java.util.*;
import java.io.*;

public class Vault {
  
  public static void main(String[] args) {
    // check for correct usage
    if (args.length < 1) {
      System.out.println("usage: java Vault [-au] <filename>");
      System.exit(1);
    }

    // check for au option
    boolean addUser = false;
    if (args.length == 2)
      addUser = true;

    // open the file, or print error and exit
    Scanner sc = null;
    try {
      sc = new Scanner(new FileReader((addUser ? args[1] : args[0])));
    }catch (IOException e) {
      System.out.println("Error! File '" + (addUser ? args[1] : args[0]) + "' could not be opened.");
      System.exit(2);
    }
    
    // read each line of the file, storing each user in users
    ArrayList<User> users = new ArrayList<User>();
    String flagName = null;
    String flagHash = null;
    while (sc.hasNextLine()) {
      String[] line = sc.nextLine().split(" ");
      
      boolean legit = true;
      if ( line.length == 4 ) {
        if (line[0].equals("user")) {
          try {
            users.add(new User(line[1], line[2], line[3]));
          }catch (UnsupportedHashException e) {
            flagName = line[1];
            flagHash = line[2];
          }
        }else if (line[0].equals("data")) {
          for (int i = 0; i < users.size(); i++) {
            if (users.get(i).getName().equals(line[1])) {
              users.get(i).addDatum(line[2], line[3]);
            }
          }
        }else {
          System.out.println("Error! File '" + (addUser ? args[1] : args[0]) + "' improperly formatted.");
          System.exit(3);
        }
      }else {
        System.out.println("Error! File '" + (addUser ? args[1] : args[0]) + "' improperly formatted.");
        System.exit(3);
      }

    }
    //close read file
    sc.close();

    // ask user for username and password
    System.out.print("username: ");
    String name = System.console().readLine();
    System.out.print("password: ");
    char[] password = System.console().readPassword();

    // if au option, collect info and add to file, then quit
    if (addUser) {
      PrintWriter pw = null;
      try {
        pw = new PrintWriter(new File((addUser ? args[1] : args[0])));
      } catch (FileNotFoundException fnfe) {
        fnfe.printStackTrace();
        System.exit(6);
      }

      System.out.print("Hash algorithm: ");
      String hashAlg = System.console().readLine();

      // perform checks and hash password
      for (char c : password) {
      //for (int i = 0; i < new String(password).length(); i++) {
        if ((int)c < 42 || (int)c > 122) {
          System.out.println("Error! Invalid symbol '" + c + "' in password.");
          System.exit(7);
        }
      }
      Hasher hasher = null;
      String passhash = null;
      if (hashAlg.equals("clear")) {
        hasher = new Clear();
      }else if (hashAlg.equals("shift+caesar")) {
        hasher = new Caesar();
      }else if (hashAlg.equals("shift+vigenere")) {
        hasher = new Vigenere();
      }else {
        System.out.println("Error! Hash algorithm '" + hashAlg + "' not supported.");
        System.exit(8);
      }
      passhash = hasher.hash(password);
      for (User u : users) {
      //for (int i = 0; i < users.size(); i++) {
        if (u.getName().equals(name)) {
          System.out.print("Error! Username '" + name + "' already in use.");
          System.exit(9);
        }
      }
      
      users.add(new User(name, hashAlg, passhash));
      for (User u : users) {
      //for (int i = 0; i < users.size(); i++) {
        pw.println(String.join(" ", "user", u.getName(), u.getHashAlg(), u.getHash()));
      }

      pw.close();
      System.exit(0);
    }

    // determine access, exit if denied
    boolean access = false;
    User curr = null;
    for (User u : users) {
    //for (int i = 0; i < users.size(); i++) {
      if (u.getName().equals(name)) {
        if (u.validate(password)) {
          if (flagHash != null && flagName.equals(name)) {
            System.out.println("Error! Hash algorithm '" + flagHash + 
                               "' not supported.");
            System.exit(4);
          }
          System.out.println("Access granted!");
          access = true;
          curr = u;
        }
        break;
      }
    }
    if (!access) {
      System.out.println("Access denied!");
      System.exit(5);
    }

    // if granted access, open prompt for commands
    System.out.print("> ");
    sc = new Scanner(System.in);
    String cmd = null;
    ArrayList<Datum> data = curr.getData();
    while (!(cmd = sc.next()).equals("quit")) {
      switch(cmd) {
        case "labels":    for (Datum d : data) {
                            d.getEnc().init(password);
                            try {
                              String plain = d.getEnc().decrypt(d.getCipher());
                              System.out.println(plain.split("_")[0]);
                            }catch (Exception e) {
                              System.out.println("Error! Corrupted entry '" + d.getCipher() + "' in vault file.");
                            }
                          }
                          break;

        case "get":       cmd = sc.next();
                          for (Datum d : data) {
                            d.getEnc().init(password);
                            try {
                              String plain = d.getEnc().decrypt(d.getCipher());
                              if (plain.split("_", 2)[0].equals(cmd))
                                System.out.println(plain.split("_", 2)[1]);
                            }catch (Exception e) {
                              System.out.println("Error! Corrupted entry '" + d.getCipher() + "' in vault file.");
                            }
                          }
                          break;                  

        default:          System.out.println("Unknown command '" + cmd + "'.");
                          break;
      }
      System.out.print("> ");

    }

   

  }
}
