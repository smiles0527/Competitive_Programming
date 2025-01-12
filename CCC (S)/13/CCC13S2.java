import java.util.Scanner;
public class CCC13S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        {
            int weight = input.nextInt();
            int number = input.nextInt();
            int[] cars = new int[number];
            for (int i = 0; i < number; i++)
            {
                int n = input.nextInt();
                cars[i] = n;
            }
            int sum = 0;
            int count = 0;
            int length = cars.length;

            for (int i = 0; i < length; i++)
            {
                sum+=cars[i];
                if (i>4)
                {
                    sum-=cars[i];
                }
                if (sum>weight)
                {
                    break;
                }
                count++;
            }
            System.out.println(count);
        }
    }
}
