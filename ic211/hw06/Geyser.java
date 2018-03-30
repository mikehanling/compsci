public class Geyser {
  private String name;
  private double baseProbFactor;
  private int    daysSinceLastBlow;

  public String name() { return this.name; }

  public double baseProb() { return this.baseProbFactor; }

  public int daySince() { return this.daysSinceLastBlow; }
}
