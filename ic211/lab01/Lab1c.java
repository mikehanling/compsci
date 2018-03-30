import java.util.*;

public class Lab1c {
  public static void main(String[] args) {
    Random rand = new Random(System.currentTimeMillis());
    rand = new Random(42);
    int ans = rand.nextInt(11);

    String[] snarky = {"That was a guess. Can't say it was a good one.",
                       "Getting warmer...",
                       "SOOO close...",
                       "I actually have no clue how close you are. Still wrong.",
                       "You use atom don't you?",
                       "Correct!! Just kidding you bafoon.",
                       "So you are purposely trying to get this wrong?",
                       "The more we chat the more I think you're a wanker.",
                       "50/50 shot.  Don't screw this up...",
                       "Only a manky git would fail now...",
                       "Seriously?!"};
    Scanner in = new Scanner(System.in);
    System.out.print("Guess a number between 0 and 10: ");
    int guess = in.nextInt();
    int tries = 1;
    while (guess != ans) {
      int comment = tries-1;
      if (tries > snarky.length) comment = (snarky.length-1);
      System.out.print(snarky[comment] + " Guess again: ");
      guess = in.nextInt();
      tries++;
    }
    System.out.println("Right after " + tries + " guesses!");
  }
}
