import java.util.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class LoanWindow {
  private static Double[] rates = { 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0, 5.25, 
                                    5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5 };


  public static void main(String args[]) {
    JFrame f = new JFrame();

    f.setTitle("Hanling, Mike - 202430");
    f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    JPanel input = new JPanel(new FlowLayout());
    input.add(new JLabel("loan amount"));
    JTextField amt = new JTextField(30);
    input.add(amt);
    input.add(new JLabel("interest rate"));
    JComboBox<Double> iRates = new JComboBox<Double>(rates);
    input.add(iRates);
    input.add(new JLabel("monthly payment"));
    JTextField pay = new JTextField(30);
    input.add(pay);
    f.add(input, BorderLayout.NORTH);

    JPanel month = new JPanel(new FlowLayout());
    month.add(new JLabel("months to payoff"));
    JTextField months = new JTextField(30);
    months.setEditable(false);
    month.add(months);
    f.add(month, BorderLayout.CENTER);

    JPanel cost = new JPanel(new FlowLayout());
    cost.add(new JLabel("cost"));
    JTextField dollars = new JTextField(30);
    dollars.setEditable(false);
    cost.add(dollars);
    f.add(cost, BorderLayout.SOUTH);

    JPanel calc = new JPanel(new FlowLayout());
    JButton b = new JButton("calculate");
    calc.add(b);
    f.add(calc, BorderLayout.EAST);

    f.pack();
    f.setVisible(true);
  }
}


