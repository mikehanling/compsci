import java.util.*;
import java.io.*;
/**
 * Mike Hanling
 * 202430
 *
 * This class is to tie together the whole project
 */
public class Proj01 {

  public static void main(String[] args) {
    if (args.length < 1) {
      System.out.println("usage: java Proj01 <sectionsfile>\n");
      System.exit(1);
    }
    
    Queue sections = new Queue();
    Schedule schedule = new Schedule();
    Scanner sc = null;
    //for each filename given...
    for (int i = 0; i < args.length; i++) {

      //make scanner for file
      try {
        sc = new Scanner(new FileReader(args[i]));
      } catch(IOException e) {
        e.printStackTrace();
        System.exit(1);
      } 
      
      //read in the file, saving into Sections
      while (sc.hasNextLine()) {
        Section cur = new Section(sc);
        sections.enqueue(cur);
      }
    }

    //take input from user
    System.out.print("> ");
    sc = new Scanner(System.in);
    String cmd = sc.next();
    while (!cmd.equals("quit")) {
      switch (cmd) {
        case "sections":  sections.printSectionsOf(sc.next());
                          break;
        
        case "add":       String course = sc.next();
                          String section = sc.next();
                          Section add = sections.getNodeMatching(course, section);
                          if (add == null) {
                            System.out.println("Error! Section not found!");
                          }else {
                            schedule.enqueue(add);
                          }break;

        case "show":      System.out.print(schedule);
                          break;

        case "week":      System.out.print(schedule.toWeek());
                          break;

        default:          System.out.println("Command not recognized.");
      }
      System.out.print("> ");
      cmd = sc.next();
    }
  }
}
