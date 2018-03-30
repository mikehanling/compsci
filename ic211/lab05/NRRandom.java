import java.util.*;
/**
 * Mike Hanling
 * 202430
 *
 * This class inherits all of Random and
 * changes the nextInt() method such that
 * no consecutive two return value can be repeated numbers
 */
public class NRRandom extends Random {

    private long last;

    /**
     * This constructor takes a seed value
     * sets last equal to -1, as
     * that is not a return value of nextInt()
     */
    public NRRandom(long seed) {
      super(seed);
      this.last = -1;
    }

    /**
     * Takes an int
     * returns a pseudorandom int
     * between [0,int)
     */
    public int nextInt(int upper) {
      int out;
      do {
        out = super.nextInt(upper);
      }while (out == last);

      last = out;
      return out;
    }
}
