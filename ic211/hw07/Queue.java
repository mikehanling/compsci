/**
 * This represents a queue
 * It can add to the back
 * And remove from the front
 */
public class Queue {
  
  private Node head;
  private Node tail;
  /**
   * This is Node that stores some data and
   * a "next" which points to the next Node in line
   */
  private class Node {
    public String data;
    public Node next;
    public Node(String d, Node n) {
      data = d;
      next = n;
    }
    public Node(String d) {
      data = d;
    }
  }

  /**
   * adds s to the back of the queue
   */
  public void enqueue(String s) {
    Node n = new Node(s);
    if (this.head == null) this.head = n;
    if (this.tail != null) this.tail.next = n;
    this.tail = n;
  }

  /**
   * removes and returns string from the front of the queue
   */
  public String dequeue() {
    String out = this.head.data;
    this.head = this.head.next;
    return out;
  }

  /**
   * returns true if the queue is empty
   * otherwise false
   */
  public boolean empty() {
    return (this.head == null);

  }

}
