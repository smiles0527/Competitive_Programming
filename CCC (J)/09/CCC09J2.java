 import java.util.Scanner;

    public class CCC09J2
    {
        public static void main(String[] args)
        {
            Scanner input = new Scanner(System.in);
            int trout = input.nextInt();
            int pike = input.nextInt();
            int pickerel = input.nextInt();
            int total = input.nextInt();
            int ways = 0;
            for (int i = 0; i <= total/trout; i++) {
                for (int j = 0; j <= total/pike; j++) {
                    for (int k = 0; k <= total/pickerel; k++) {
                        if ((i*trout + j*pike + k*pickerel)<=total && i+j+k>0){
                            System.out.print(i + " Brown Trout, ");
                            System.out.print(j + " Northern Pike, ");
                            System.out.print(k + " Yellow Pickerel");
                            System.out.println();
                            ways++;
                        }
                    }
                }
            }
            System.out.println("Number of ways to catch fish: " + ways);
            // i = trout; j = pike; k = pickerel;
        }
    }
