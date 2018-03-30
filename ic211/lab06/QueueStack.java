/**
 * Mike Hanling
 *
 * Stack to store all of the filter/filter! results up to a reset
 */
public class QueueStack {
  
  private Node head = null;
  private Node tail = null;

  /**
   * Private Node class for each SearchQueue in stack
   */
  private class Node {
    public SearchQueue data;
    public Node next;
    public Node(SearchQueue d, Node n) {
      data = d;
      next = n;
    }
  }

  /**
   * add SearchQueue to top of stack
   * 
   */
  public void push(SearchQueue q) {
    if (this.head == null)
      this.head = this.tail = new Node(q, null);
    else
      this.head = new Node(q, this.head);
  }

  /**
   * returns the top SearchQueue on the stack
   */
  public SearchQueue pop() {
    Node t = this.head;
    this.head = head.next;
    if (this.head == null)
      this.tail = null;

    return t.data;
  }

  /**
   * Returns true if the stack is empty
   * false otherwise
   */
  public boolean empty() {
    return this.head == null;
  }

}


