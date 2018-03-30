public class DrBrown
{
  private static class Node { 
    String data; 
    Node next; 
    public Node(String d, Node n) { data = d; next = n; }    
  }

  // explode(pat) takes a valid meeting time pattern (in USNA format)
  // and returns an array of the indvidual meetings defined by the pattern.
  // For example: if pat is "MWF1,R12" explode(pat) returns the array
  // {"M1","W1","F1","R1","R2"}
  // If pat is "TR9" explode(pat) returns the array {"T34","R34"}.
  public static String[] explode(String pat)
  {
    int N = 0;
    Node head = null;
    String[] L = pat.split(",");
    for(int i = 0; i < L.length; i++)
    {
      // Set j to the first non-letter index & pull out the period substring
      int j = 0; while('A' <= L[i].charAt(j) && L[i].charAt(j) <= 'Z') j++;
      String per = L[i].substring(j);
      if (per.equals("8"))  per = "12";
      if (per.equals("9"))  per = "34";
      if (per.equals("10")) per = "56";

      // For each letter, concat letter and period and add to output
      for(int k = 0; k < j; k++)
      {
	N++;
	head = new Node("" + L[i].charAt(k) + per.charAt(0),head);
	if (per.length() > 1) {
	  head = new Node("" + L[i].charAt(k) + per.charAt(1),head);
	  N++; }
      }
    }
    String[] output = new String[N];
    for(int i = N-1; head != null; head = head.next)
      output[i--] = head.data;
    return output;
  }
  public static void main(String[] args)
  {
    String[] A = explode(args[0]);
    for(int i = 0; i < A.length; i++)
      System.out.println(A[i]);
    
  }
}
