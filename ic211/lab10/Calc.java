import java.util.*;
import java.lang.Math;

public class Calc {

  private double amt;
  private double rate;
  private double bal;
  private double payment;
  private int months;

  public Calc(double amt, double rate, double payment){
    this.amt = amt;
    this.bal = amt;
    this.rate = rate;
    this.payment = payment;
    this.months = 0;
  }

  public double calcMonInt() {
    return this.bal*this.rate/1200;
  }

  public void makePayment() {
    this.bal -= this.payment;
  }

  private void calcLoan() throws BadPlanException {
    if (this.payment < this.bal*this.rate/1200) {
      throw new BadPlanException("payment is less than interest accruing");
    }
    System.out.println("Here");

    while (this.bal > 0) {
      this.bal += this.calcMonInt();
      this.makePayment();
      this.months++;
    }
  }

  public double calcCost() {
    this.calcLoan();
    double cost = this.payment*this.months + this.bal - this.amt;
    return Math.round(cost*100)/100.0;
  }

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
      cost = loan.calcCost();
    }catch(BadPlanException e) {
      System.out.println("This plan will not work because " + e.getMessage());
      System.exit(3);
    }

    System.out.println("month = " + loan.getMonths() + "  cost = " + cost);
  }
}

