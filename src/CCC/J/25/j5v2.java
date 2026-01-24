import java.util.Scanner;

public class j5v2 {
     public static void main(String[] args) 
     {
        Scanner input = new Scanner(System.in);
        int R = input.nextInt();
        int C = input.nextInt();
        int M = input.nextInt();

        int[] arr = new int[C];
        for (int c = 0; c < C; c++)
        {
            arr[c] = c%M+1;
        }
 
        for (int r = 1; r < R; r++)
        {
            int[] temp = new int[C];
            for (int c = 0; c < C; c++)
            {
                int cur = (r*C + c)%M+1;

                if (c>0 && c<C-1)
                {
                    temp[c] = cur + Math.min(arr[c-1], Math.min(arr[c], arr[c+1]));
                }
                else if (c<1)
                {
                    temp[c] = cur + Math.min(arr[c], arr[c+1]);
                }
                else
                {
                    temp[c] = cur + Math.min(arr[c-1], arr[c]);
                }
            }
            arr = temp;
        }

        int min = Integer.MAX_VALUE;

        for (int i = 0; i < C;i++)
        {
            min = Math.min(min, arr[i]);
        }
        System.out.println(min);
        input.close();
     }
}



