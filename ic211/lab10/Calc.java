import java.util.*;
import java.lang.Math;

/**
 * An instance of Calc holds the cost calculated and number of months ot pay off
 * a loan after given its initial values are provided
 * @author Hanling, Mike - 202430
 */
public class Calc {

  private double amt;
  private double rate;
  private double bal;
  private double payment;
  private double cost;
  private int months;

  /**
   * Constructor for Calc, calculates everything upon being created
   * @param amt The double representing the principle of the loan
   * @param rate The double representing the interest rate on the loan
   * @param payment The double representing the planned amount to pay per month
   * @throws BadPlanException If while calculating, it is determined that the
   * specified amount to pay each month will never pay off the loan, then this
   * exception is thrown
   */
  public Calc(double amt, double rate, double payment) throws BadPlanException{
    this.amt = amt;
    this.bal = amt;
    this.rate = rate;
    this.payment = payment;
    this.months = 0;
    this.calcLoan();
  }

  private double calcMonInt() {
    return this.bal*this.rate/1200;
  }

  private void makePayment() {
    this.bal -= this.payment;
  }

  private void calcLoan() throws BadPlanException {
    if (this.payment < this.bal*this.rate/1200) {
      throw new BadPlanException("payment is less than interest accruing");
    }

    while (this.bal > 0) {
      this.bal += this.calcMonInt();
      this.makePayment();
      this.months++;
    }

    this.cost = this.payment*this.months + this.bal - this.amt;
    this.cost = Math.round(this.cost*100)/100.0;
  }

  /**
   * Returns the cost calculated of the loan, which is the amount paid minus the
   * principle
   * @return The double of the cost calculated for the loan
   */
  public double getCost() { return this.cost; }

  /**
   * Returns the number of months predicted to pay off the loan given the
   * payment per month
   * @return The int of the number of months for the loan to be paid off
   */
  public int getMonths() { return this.months; }


  public static void main(String args[]) {

    if (args.length != 3) {
      System.out.println("usage: java Calc <amount> <rate> <payment>");
      System.exit(2);
    }
    
    Calc loan = null;
    double cost = 0;
    try {
      loan = new Calc(new Double(Double.parseDouble(args[0])),
                      new Double(Double.parseDouble(args[1])),
                      new Double(Double.parseDouble(args[2])));
    }catch(BadPlanException e) {
      System.out.println("This plan will not work because " + e.getMessage());
      System.exit(3);
    }

    System.out.println("month = " + loan.getMonths() + 
                       "  cost = " + loan.getCost());
  }
}

