/**
 * This is the driver class for Lab10 in IC211 (found <a href="http://faculty.cs.usna.edu/IC211/calendar.php?type=lab&event=10">here</a>
 * The lab creates a window to calculate expected loan costs
 * @author Hanling, Mike - 202430
 */
public class Lab10 {

  /**
   * This main simply creates a LoanWindow and then sets its visibility to true,
   * all other functionality is coming from the LoanWindow structure
   * @param args Command line arguments: not used in this class
   */
  public static void main(String[] args) {

    LoanWindow lw = new LoanWindow();

    lw.setVisible(true);
  }

}
