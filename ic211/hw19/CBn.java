import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * CBn is a button as well as an action listener for itself and is a
 * window listener for a frame
 * @author MIDN Hanling, Mike - 202430
 */
public class CBn extends JButton implements ActionListener, WindowListener {
  private int count = 0;
  
  /**
   * Constructor for a CBn
   * @param label The string label that will show on the button
   */
  public CBn(String label) {
    super(label);
    this.addActionListener(this);
  }

  /**
   * implementation of ActionListener
   * whenever the button is clicked, the private count is incremented
   */
  public void actionPerformed(ActionEvent e) {
    count++;
  }

  public void windowActivated(WindowEvent e){}
  public void windowClosed(WindowEvent e){}
  
  /**
   * Only part of the WindowListener interface needed
   * When the window is closed the number of times it was clicked is printed to
   * stdout
   */
  public void windowClosing(WindowEvent e){
    System.out.println("Button clicked " + this.count + " times.");
  }
  public void windowDeactivated(WindowEvent e){}
  public void windowDeiconified(WindowEvent e){}
  public void windowIconified(WindowEvent e){}
  public void windowOpened(WindowEvent e){}
}
