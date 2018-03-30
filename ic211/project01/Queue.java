/**
 * Mike Hanling
 * 202430
 *
 * TAKEN AND ADAPTED FROM HW07
 *
 * This represents a queue
 * It can add to the back
 * And remove from the front
 */
public class Queue {

  /**
   * This class is the unit of the Queue
   * Holds data and points to next in line
   */
  private class Node {
    public Section data;
    public Node next;
    
    /**
     * This constructor takes the
     * string to be the data and
     * the next node to point to (or null)
     */
    public Node(Section d, Node n) {
      data = d;
      next = n;
    }
  }
  
  //*********FIELDS***********
  private Node head;
  private Node tail;

  /**
   * adds s (Section) to the back of the queue
   */
  public void enqueue(Section s) {
    Node n = new Node(s, null);
    if (this.head == null) this.head = n;
    if (this.tail != null) this.tail.next = n;
    this.tail = n;
  }

  /**
   * returns the Node with data from the Node that matches
   * course and section number
   * if no match, return null
   */
  public Section getNodeMatching(String course, String section) {
    Node cur = this.head;
    while (cur != null) {
      if (cur.data.matches(course, section))
        return cur.data;
      cur = cur.next;
    }
    return null;
  }

  /**
   * returns true if the queue is empty
   * otherwise false
   */
  public boolean empty() {
    return (this.head == null);

  }

  /**
   * This takes the Course name as input and 
   * will print out each Section of that course in the Queue
   */
  public void printSectionsOf(String course) {
    Node cur = this.head;
    while (cur != null) {
      if (cur.data.getCourse().equals(course)) {
        System.out.println(cur.data);
      }
      cur = cur.next;
    }
  }

  /**
   * This will print the data of each node to the terminal
   */
  public String toString() {
    Node cur = this.head;
    String out = "";
    while (cur != null) {
      out += (cur.data + "\n");
      //System.out.println(cur.data);
      cur = cur.next;
    }
    return out;
  }
}
