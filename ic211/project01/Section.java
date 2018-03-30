import java.util.*;
/**
 * Mike Hanling
 * 202430
 *
 * USED JAVA 8 DOCUMENTATION FOR STRING METHODS
 *
 * This class is to replicate one section
 * It will hold its meeting times with location
 */
public class Section {
  private String course;
  private String number;
  private String periods;
  private String rooms;

  /**
   * This constructor takes the section's
   * course (string)
   * number (string)
   * periods meeting (string) and
   * rooms meeting (string)
   */
  public Section(String c, String n, String p, String r) {
    this.course = c;
    this.number = n;
    this.periods = p;
    this.rooms = r;
  }
  /**
   * This constructor takes a scanner,
   * reads a line from the file,
   * stores all the section's info,
   * and returns the new Section
   */
  public Section(Scanner sc) {
    String[] data = sc.nextLine().split("\\s");
    this.course = data[0];
    this.number = data[1];
    this.periods = data[2];
    this.rooms = data[3];
  } 


  /**
   * Returns course (string) of this section
   */
  public String getCourse() {
    return this.course;
  }

  /**
   * Returns number (string) of this section
   */
  public String getNumber() {
    return this.number;
  }

  /**
   * Returns the periods meeting (string) of this section
   */
  public String getPeriods() {
    return this.periods;
  }

  /**
   * Returns the rooms (string) that this section meets in
   */
  public String getRooms() {
    return this.rooms;
  }

  /**
   * returns true if the COURSE and SECTION match
   * false otherwise
   */
  public boolean matches(String course, String number) {
    if (this.course.equals(course) && this.number.equals(number))
      return true;
    return false;
  }

  /**
   * formats the section info into a string to print out
   */
  public String toString() {
    return this.course + " " + this.number + " " 
         + this.periods + " " + this.rooms;
  }
  
}
