import javax.swing.*;
import java.awt.*;

/**
 * This is the custom frame for this hw, HW19
 * @author MIDN Hanling, Mieke - 202430
 */
public class HW1Frame extends JFrame {
  /**
   * Constructor for this type of frame
   * Adds a button that monitors itself
   * The button will be the only thing (placed in NORTH)
   */
  public HW1Frame() {
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    CBn b = new CBn("click me");

    addWindowListener(b);
    add(b, BorderLayout.NORTH);
    pack();
  }
}
