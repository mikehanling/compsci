import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * This class creates the structure for a LoanWindow, which asks for values of
 * the principle, interest rate, and monthly payment of a loan;
 * It includes a button to activate the calculations
 * @author Hanling, Mike - 202430
 */
public class LoanWindow extends JFrame {
  private static Double[] rates = { 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0, 5.25, 
                                    5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5 };
  private JTextField amount;
  private JComboBox<Double> iRate;
  private JTextField pay;
  private JTextField months;
  private JTextField dollars;

  /**
   * Constructor for a LoanWindow;
   * JPanels are used to then inject into the normal JFrame;
   * No parameters necessary
   */
  public LoanWindow() {
  //public static void main(String args[]) {

    this.setTitle("Hanling, Mike - 202430");
    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    JPanel input = new JPanel(new FlowLayout());
    input.add(new JLabel("loan amount"));
    this.amount = new JTextField(30);
    input.add(amount);
    input.add(new JLabel("interest rate"));
    this.iRate = new JComboBox<Double>(rates);
    input.add(iRate);
    input.add(new JLabel("monthly payment"));
    this.pay = new JTextField(30);
    input.add(pay);
    this.add(input, BorderLayout.NORTH);

    JPanel month = new JPanel(new FlowLayout());
    month.add(new JLabel("months to payoff"));
    this.months = new JTextField(30);
    months.setEditable(false);
    month.add(months);
    this.add(month, BorderLayout.CENTER);

    JPanel cost = new JPanel(new FlowLayout());
    cost.add(new JLabel("cost"));
    this.dollars = new JTextField(30);
    dollars.setEditable(false);
    cost.add(dollars);
    this.add(cost, BorderLayout.SOUTH);

    JPanel calc = new JPanel(new FlowLayout());
    JButton b = new JButton("calculate");
    b.addActionListener(new CalculateListener(this));
    calc.add(b);
    this.add(calc, BorderLayout.EAST);

    this.pack();
    //f.setVisible(true);
  }

  /**
   * When called, this method will grab the values that are present in the
   * LoanWindow (given by the user), calculate the outputs, and place the
   * outputs in their respective fields;
   * No parameters necessary
   */
  public void calc() {
    //parse inputs in window
    double amt = Double.parseDouble(this.amount.getText());
    double rate = ((Double)this.iRate.getSelectedItem()).doubleValue();;
    double payment = Double.parseDouble(this.pay.getText());
   
    //construct the loan, and set the text boxes
    try {
      Calc loan = new Calc(amt, rate, payment);
      this.months.setText("" + loan.getMonths());
      this.dollars.setText("" + loan.getCost());
    }catch(BadPlanException e) {
      this.months.setText("Error!");
      this.dollars.setText("Monthly payment is too stingy!");
    }
    
  }

}


