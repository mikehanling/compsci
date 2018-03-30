import java.util.*;

public class Lab07a
{
  public static Random rand = new Random(System.currentTimeMillis());

  // A "Thing" moves in a grid world. A TypeA Thing randomly 
  // decides to turn left or right (or not turn) every "round",
  // and, afterward, takes a step forward.  A TypeB Thing
  // only considers making a random turn every 10th round.
  public static class Thing
  {
    // dir: 0=North, 1=East, 2=South, 3=West. 
    // timeSinceLast: this is only important for "TypeB" Things.
    public int row, col, dir, timeSinceLast;
    public char lab = 'r';
    public boolean isTypeB;
  }
  
  // This class is for linked lists of Thing's
  public static class Node
  {
    public Thing data;
    public Node next;
  }

  public static void rightTurn(Thing t)
  { 
    t.dir = (t.dir + 1) % 4; 
  }

  public static void leftTurn(Thing t) 
  { 
    t.dir = (t.dir + 3) % 4; 
  }

  public static void maybeTurn(Thing t)
  {
    int i = rand.nextInt(3);
    if (t.isTypeB)
    {
      t.timeSinceLast++; 
      if (t.timeSinceLast == 10)
      {
	t.timeSinceLast = 0;
	if (i == 1) { rightTurn(t); }
	if (i == 2) { leftTurn(t); }
      }
    }
    else
    {
      if (i == 1) { rightTurn(t); }
      if (i == 2) { leftTurn(t); }      
    }
  }

  public static void step(Thing t)
  {
    final int[] dc = {0,1,0,-1}, dr = {-1,0,1,0};
    t.row += dr[t.dir];
    t.col += dc[t.dir];
  }

  public static void main(String[] args)
  {
    int N = 200;
    if (args.length != 0) N = Integer.parseInt(args[0]);
    
    Node L = null;
    int count = 0;
    while(true)
    {
      // every N rounds add another typeA and typeB Thing
      if (count % N == 0)
      {
	// add a typeA thing to the list
	Thing tA = new Thing(); 
	tA.row = 45;
	tA.col = 50;
	Node nA = new Node(); 
	nA.data = tA;
	nA.next = L;
	L = nA;
	
	// add a typeB thing to the list
	Thing tB = new Thing(); 
	tB.row = 55;
	tB.col = 50;
	tB.lab = 'b';
	tB.isTypeB = true;
	Node nB = new Node(); 
	nB.data = tB;
	nB.next = L;
	L = nB;
      }

      // print out each thing
      for(Node T = L; T != null; T = T.next)
	System.out.println(T.data.row + " " + 
			   T.data.col + " " + 
			   T.data.lab);
      System.out.println("done");
      System.out.flush();
      
      // move each thing
      for(Node T = L; T != null; T = T.next)
      {
	maybeTurn(T.data);
	step(T.data);
      }      
      count++;
    }
  }
}
