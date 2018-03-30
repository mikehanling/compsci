public class PeekaQueue extends Queue {
  public String peek() {
    Iter i = iterator();

    return i.next();
  }
}
