import java.util.Scanner;

public class j5v3 {
    public static void main(String[] args) 
    {
        Scanner input = new Scanner(System.in);
        int R = input.nextInt();
        int C = input.nextInt();
        int M = input.nextInt();

        int[] arr = new int[C];

        int sum = Integer.MAX_VALUE;

        for (int c = 0; c < C; c++)
        {
            for (int i = -1; i<=1; i++)
            {
                if (c==0)
                {
                    continue;
                }
                else if (c==C-1 && i==1)
                {
                    break;
                }
                int cur = 0;
                for (int r = 0; r < R; r++)
                {
                    cur += ((r+1)*C+c+1)%M + i;               
                }
                sum = Math.min(cur, sum);
            }
        }
        System.out.println(sum);
        input.close();
    }
    
}
