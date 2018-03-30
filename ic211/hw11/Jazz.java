public class Jazz extends Apple {
  public String foo() {
    return "jazz-foo";
  }

  public static String bar(Apple a) {
    return "bar-" + a.foo();
  }
}
