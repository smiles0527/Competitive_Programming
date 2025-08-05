import java.util.Scanner;

public class CCC04J2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        int x = input.nextInt();
        int y = input.nextInt();
        int time = (y - x) / 60;
        System.out.println("All positions change in year " + x);
        for (int i = 0; i < time; i++)
        {
            x += 60;
            System.out.println("All positions change in year " + x);
        }

    }
}