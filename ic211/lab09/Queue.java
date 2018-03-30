/**
 * Queue is a first in, first out structure i.e. new nodes are added to the end
 * @author Hanling, Mike - 202430
 * @author IC211
 */
public class Queue {

  /**
   * Takes a string and will make a Node at the back of the Queue
   * @param s String that will be the data of the Node
   */
  public void enqueue(String s) {
    if (head == null) {
      head = tail = new Node(s, null);
    } else {
      tail.next = new Node(s, null);
      tail      = tail.next;
    }
  }

  /**
   * Takes the first Node out of the Queue and returns the data
   * @return String data of the first Node in the Queue
   * @throws QueueException When the Queue is empty, but is attempts to dequeue
   */
  public String dequeue() throws QueueException{
    Node t = head;

    try {
      head = head.next;
    }catch(NullPointerException e) {
      throw new QueueException("dequeue empty queue");
    }

    if (head == null) {
      tail = null;
    }
    return t.data;
  }

  /**
   * Checks if the Queue is empty or not
   * @return True if there is at least one element; false otherwise
   */
  public boolean empty() {
    return head == null;
  }

  /**
   * Function to make an iterator for this Queue
   * @return Iter pointing to the head of the Queue
   */
  public Iter iterator() {
    return new Iter(head);
  }

  /**
   * Class for an iterator to walk down a queue safely
   * @author Hanling, Mike - 202430
   * @author IC211
   */
  protected class Iter {
    private Node curr;
    
    /**
     * Constructor for an iterator through the Queue
     * @param start The starting Node of the Queue
     */
    public Iter(Node start) {
      curr = start;
    }

    /**
     * Checks if there is a next Node of not
     * @return true if there is a Node after the current one; false otherwise
     */
    public boolean hasNext() {
      return curr != null;
    }

    /**
     * Gets the next Node, and returns its data
     * @return String data of the next Node
     * @throws QueueException If there is not a next Node
     */
    public String next() throws QueueException{
      String s = null;
      try {
        s = curr.data;
      }catch(NullPointerException e) {
        throw new QueueException("iterator past end of queue");
      }

      curr = curr.next;
      return s;
    }
  }

  /**
   * Node class for storing a package of information in a Queue
   * @author IC211
   */
  private class Node {
    public String data;
    public Node   next;
    
    /**
     * Constructor for Node that takes a string as data and another Node as next
     * @param d String which is the data of the Node
     * @param n Node that is next (may be null if last one)
     */
    public Node(String d,
                Node   n) {
      data = d;
      next = n;
    }
  }

  private Node head = null, tail = null;
}
