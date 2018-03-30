import java.util.*;
import java.lang.*;

public class HW02 {
  public static int maxLength(String[] A) {
    int max = 0;
    for (int i = 0; i < A.length; i++) {
      if (A[i].length() > max) max = A[i].length();
    }
    return max;
  }
  
  public static void main(String[] args) {
    //first take the number of words to be read in
    Scanner in = new Scanner(System.in);
    int numw = in.nextInt();

    //create an array for that many strings
    String[] words = new String[numw];

    //read in words and store in array
    for (int i = 0; i < words.length; i++) {
      words[i] = in.next();
    }

    //for each letter in the longest word...
    for (int i = 0; i < maxLength(words); i++) {
      //start an empty string
      String print = "";

      //grab the indexed letter from each word
      for (int j = 0; j < words.length; j++) {
        //if the word is long enough then add that character to the string
        if (i < words[j].length()) print += words[j].charAt(i);
        //otherwise add a space
        else print += " ";
        //add another space as long as that was not the last word
        if (j < (words.length - 1)) print += " ";
      }
      
      //print out the set of characters for this index
      System.out.println(print);
    }
  }
}
