import java.util.*;
import java.io.*;
/**
 * This class is the main driver for Project 2 from IC211 (2018)
 * <a href="http://faculty.cs.usna.edu/IC211/calendar.php?type=project&event=2">This</a>
 * is the lab webpage.
 * Vault is the interface between a user and a database of account holders with
 * data stored for each.
 *
 * @author Hanling, Mike - 202430
 */
public class Vault {

  /**
   * Vault is intended to be used for its main
   * The given filename will be opened and read in to be used throughout
   * An option of -au will allowed for an user to be added to the vault file
   * In normal mode, the user will be asked for a username and password
   * Both must match an entry from the vault file in order to be granteed access
   * Three commands (labels, get, and quit) are recognized
   * "labels" returns labels for each datum of current user
   * "get" followed by a label will retrieve the text of the datum
   * "quit" terminates the session
   * @param args Either filename or -au filename for adding an user
   */
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
      System.out.println("Error! File '" + (addUser ? args[1] : args[0]) + 
                         "' could not be opened.");
      System.exit(2);
    }
    
    // read each line of the file, storing each user in users
    ArrayList<User> users = new ArrayList<User>();
    while (sc.hasNextLine()) {
      String[] line = sc.nextLine().split(" ");
      
      if (line.length == 4 && line[0].equals("user")) {
        users.add(new User(line[1], line[2], line[3]));

      }else if (line.length == 4 && line[0].equals("data")) {
        for (int i = 0; i < users.size(); i++) {
          if (users.get(i).getName().equals(line[1]))
            users.get(i).addDatum(line[2], line[3]);
        }

      }else {
        System.out.println("Error! File '" + (addUser ? args[1] : args[0]) + 
                           "' improperly formatted.");
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
        pw = new PrintWriter(new File(args[1]));
      } catch (FileNotFoundException fnfe) {
        fnfe.printStackTrace();
        System.exit(6);
      }

      System.out.print("Hash algorithm: ");
      String hashAlg = System.console().readLine();

      // perform checks and hash password
      for (char c : password) {
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
        if (u.getName().equals(name)) {
          System.out.print("Error! Username '" + name + "' already in use.");
          System.exit(9);
        }
      }
      
      users.add(new User(name, hashAlg, passhash));
      for (User u : users) {
        pw.println(String.join(" ", "user", u.getName(), u.getHashAlg(), u.getHash()));
      }

      pw.close();
      System.exit(0);
    }

    // determine access, exit if denied
    boolean access = false;
    User curr = null;
    for (User u : users) {
      if (u.getName().equals(name)) {
        try {
          if (u.validate(password)) {
            System.out.println("Access granted!");
            access = true;
            curr = u;
          }
          break;
        }catch (UnsupportedHashException e) {
          System.out.println("Error! Hash algorithm '" + u.getHashAlg() + 
                             "' not supported.");
          System.exit(4);
        }
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
        case "labels":  for (Datum d : data) {
                          d.getEnc().init(password);
                          try {
                            String plain = d.getEnc().decrypt(d.getCipher());
                            if (!plain.contains("_")) throw new Exception();
                            System.out.println(plain.split("_")[0]);
                          }catch (Exception e) {
                            System.out.println("Error! Corrupted entry '" +
                                                d.getCipher() + 
                                                "' in vault file.");
                          }
                        }
                        break;

        case "get":     cmd = sc.next();
                        for (Datum d : data) {
                          d.getEnc().init(password);
                          try {
                            String plain = d.getEnc().decrypt(d.getCipher());
                            if (!plain.contains("_")) throw new Exception();
                            if (plain.split("_", 2)[0].equals(cmd))
                              System.out.println(plain.split("_", 2)[1]);
                          }catch (Exception e) {
                            System.out.println("Error! Corrupted entry '" + 
                                                d.getCipher() + 
                                                "' in vault file.");
                          }
                        }
                        break;                  

        default:        System.out.println("Unknown command '" + cmd + "'.");
                        break;
      }
      System.out.print("> ");

    }

   

  }
}
