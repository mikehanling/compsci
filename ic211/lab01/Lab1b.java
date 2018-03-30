import java.util.*;

public class Lab1b {
  public static int fact(int x) {
    if (x == 0 || x == 1) return 1;
    else {
      return x * fact(x-1);
    }
  }
  public static int partFact(int x, int y) { 
    int ans = 1;
    for (int i = x; i > (x-y); i--) {
      ans *= i;
    }
    return ans;
  }
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    System.out.print("Enter your name: ");
    String name = in.nextLine();
    System.out.print("Please input an integer ");
    int n = in.nextInt();
    System.out.print("Please input a second integer ");
    int k = in.nextInt();
    System.out.println("The two ints were " + n + " and " + k);
   
    int num = partFact(n, k);
    System.out.println("numerator = " + num);
    int dem = fact(k);
    System.out.println("denominator = " + dem);

    System.out.println("odds = 1 in " + (num/dem) + " = " + (1.0/num*dem));

    System.out.println("Goodbye " + name + ".");
  }
}
