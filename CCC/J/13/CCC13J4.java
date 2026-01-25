import java.util.Arrays;
import java.util.Scanner;
public class CCC13J4
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        int minutes = input.nextInt();
        int chores = input.nextInt();
        int[] total = new int[chores];
        for (int i = 0; i < chores; i++)
        {
            int n = input.nextInt();
            total[i] = n;
        }
        Arrays.sort(total);
        int sum = 0;
        int count = 0;
        for (int i = 0; sum<=minutes; i++)
        {
            sum = sum+total[i];
            count++;
        }
        System.out.println(count-1);
    }

}
