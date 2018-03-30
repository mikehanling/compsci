import java.io.*;
public class Categorizer {
  /**
   * Adds a RecogASCII object to the Categorizer, so that when
   * an input file is processed, it is one of the categories
   * that gets tested for.
   */
  public void add(RecogASCII r) {
    Q.enqueue(r);
  }

  /**
   * Takes an input stream (assumed to be a file) and
   * runs it through all the RecogASCII's that have been
   * added, and prints any matches discovered.
   */
  public void printCategories(InputStream is) {
    try {
      int n;

      while ((n = is.read()) != -1) {
        for (Queue.Iter i = Q.iterator(); i.hasNext(); i.next().feed(n)) {}
      }

      for (Queue.Iter i = Q.iterator(); i.hasNext();) {
        RecogASCII r = i.next();

        if (r.decision()) {
          System.out.println(r.getName());
        }
      }
    } catch (Exception e) {
      System.exit(1);
    }
  }

  private Queue Q = new Queue();

  private class Queue {
    public void enqueue(RecogASCII s) {
      if (head == null) {
        head = tail = new Node(s, null);
      } else {
        tail.next = new Node(s, null);
        tail      = tail.next;
      }
    }

    public RecogASCII dequeue() {
      Node t = head;

      head = head.next;

      if (head == null) {
        tail = null;
      }
      return t.data;
    }

    public boolean empty() {
      return head == null;
    }

    public Iter iterator() {
      return new Iter(head);
    }

    protected class Iter {
      private Node curr;
      public Iter(Node start) {
        curr = start;
      }

      public boolean hasNext() {
        return curr != null;
      }

      public RecogASCII next() {
        RecogASCII s = curr.data;

        curr = curr.next;
        return s;
      }
    }

    private class Node {
      public RecogASCII data;
      public Node next;
      public Node(RecogASCII d,
                  Node       n) {
        data = d;
        next = n;
      }
    }

    private Node head = null, tail = null;
  }
}
