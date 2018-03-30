/**
 * Mike Hanling
 * 202430
 *
 * A Schedule Combines a Queue of Sections with a Week
 */
public class Schedule extends Queue {

  //initialize now in order to have an empty week to start
  private Week week = new Week();

  /**
   * This adds to the enqueue function from super to update week
   */
  public void enqueue(Section s) {
    super.enqueue(s);
    this.week = this.week.mergeWith(s.getPeriods());
  }

  /**
   * returns the schedule in list view
   */
  public String toString() {
    return super.toString();
  }

  /**
   * returns the schedule in list view
   */
  public String toWeek() {
    return this.week.toString();
  }
}
