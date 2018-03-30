public class Apple {
  public String foo() {
    return "apple-foo";
  }

  public String foo(char c) {
    return foo() + "-" + c;
  }

  public String foo(int i) {
    return "red-foo";
  }
}
