public class test {
  public static int sum(int k) {
    if (k > 0) {
      int t1 = sum(k-1);
      return k + t1;
    } 
    else {
      return 0;
    }
  }

  public static void main(String[] args) {
    int result = sum(10);
    System.out.println(result);
  }
}
