import java.awt.event.*;

/**
 * This class implements ActionListener so that a LoanWindow can calculate upon
 * click of the button in the window
 * @author Hanling, Mike - 202430
 */
public class CalculateListener implements ActionListener {
  
  private LoanWindow w;

  /**
   * Constructor for a CalculateListener, it links the listener to the
   * LoanWindow
   * @param w A LoanWindow for which to link the listener to
   */
  public CalculateListener(LoanWindow w) {
    this.w = w;
  }

  /**
   * Required method to be implemented for ActionListener
   * Upon action (button click), the window will calculate the loan
   * @param e An ActionEvent - in this case a button click
   */
  public void actionPerformed(ActionEvent e) {
    w.calc();
  }
}
