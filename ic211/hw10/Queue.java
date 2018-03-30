public class Queue {

  private String[] elements = new String[1024];
  private int head = 0;
  private int tail = -1;

  public void enqueue(String s) {
    this.tail++;
    this.elements[tail] = s;
  }

  public String dequeue() {
    if (this.head > this.tail) return null;
    return this.elements[head++];
  }

  public boolean empty() {
    return head > tail;
  }

  public Iter iterator() {
    return new Iter(elements, head);
  }

  protected class Iter {
    private String[] elements;
    private int curr;
    public Iter(String[] elements, int start) {
      this.elements = elements;
      curr = start;
    }

    public boolean hasNext() {
      return this.elements[curr] != null;
    }

    public String next() {
      String s = this.elements[curr];

      curr++;
      return s;
    }
  }
}
