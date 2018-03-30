/**
 * Mike Hanling
 * Chris Daves
 *
 * Extension of TweetQueue
 * Adds functions in order to filter and print selected Tweets
 * ADDED FROM ORIGINAL:
 *  each SearchQueue has a count field in order to facilitate reporting the
 *  number of tweets at a current time
 */
public class SearchQueue extends TweetQueue {

  private int count = 0;

  /**
   * Getter function for count
   */
  public int getCount() { return this.count; }

  /**
   * Setter function for incrementing count
   */
  public void inc() { this.count++; }
  
  /**
   * Filters Tweets out of a SearchQueue into a new SearchQueue
   * Filters based on substring provided
   * Will keep the Tweets that DO contain if keep == true
   * Will keep the Tweets that DO NOT contain if keep == false
   */
  public SearchQueue filter(String match, boolean keep) {
    SearchQueue newQ = new SearchQueue();
    TweetQueue.Iter iter = this.iterator();
    Tweet t = null;

    while (iter.hasNext()) {
      t = iter.next();
      if (keep) {
        if (t.getText().contains(match)) {
          newQ.enqueue(t);
          newQ.count++;
        }
      }
      else {
        if (!t.getText().contains(match)) {
          newQ.enqueue(t);
          newQ.count++;
        }
      }
    }
    return newQ;
  }
  
  /**
   * Runs through a SearchQueue
   * Prints each Tweet
   * No return
   */
  public void dump() {
    TweetQueue.Iter iter = this.iterator();

    while (iter.hasNext()) 
      System.out.println(iter.next());

  }

}
