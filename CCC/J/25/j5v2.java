import java.util.Scanner;

public class j5v2 {
     public static void main(String[] args) 
     {
        Scanner input = new Scanner(System.in);
        int r = input.nextInt();
        int c = input.nextInt();
        int m = input.nextInt();

        int[] prev = new int[c];
        int[] cur = new int[c];

        for (int i = 0; i < c; i++)
        {
            prev[i] = i%m+1;
        }
        
        for (int i = 1; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                int cost = (i*c+j)%m+1;
                int good = prev[j];

                if (j>=1)
                {
                    good = Math.min(good, )
                }
            }
        }
     }

     
}
