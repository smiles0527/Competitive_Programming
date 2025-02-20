import java.util.*;

public class j5
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);

        int r = input.nextInt();
        int c = input.nextInt();
        int m = input.nextInt();

        int[] prev = new int[c];
        int[] cur = new int[c];  

        for (int j = 0; j < c; j++)
        {
            prev[j] = (j % m) + 1;
        }

        for (int i = 1; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                int cost = (int)(((long)i * c + j) % m) + 1;
                int mn = prev[j];
                if (j > 0)
                {
                    mn = Math.min(mn, prev[j-1]);
                }
                if (j < c - 1)
                {
                    mn = Math.min(mn, prev[j+1]);
                }
                cur[j] = cost + mn;
            }
            int[] temp = prev;
            prev = cur;
            cur = temp;
        }
        
        int ans = prev[0];
        for (int j = 1; j < c; j++)
        {
            ans = Math.min(ans, prev[j]);
        }

        System.out.println(ans);
        input.close();
            
     }   
        
        
        
}

