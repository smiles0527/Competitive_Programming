import java.util.Scanner;

public class CCC00J1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        int weekday = input.nextInt();
        int totalDays = input.nextInt();
        int spaces = 4 * (weekday-1) - 1;
        System.out.println("Sun Mon Tue Wed Thr Fri Sat");
        for (int i = 0; i < spaces; i++)
        {
            System.out.print(" ");
        }
        for (int d = 1; d <= totalDays ; d++)
        {
            if (weekday> 1)
            {
                System.out.print(" ");
            }
                if (d<10){
                    System.out.print("  " + d);
                }
                else{
                    System.out.print(" " + d);
                }
                if (weekday == 7 ){
                    System.out.println();
                    weekday = 1;
                }
                else {
                    weekday++;
                }
            }
        if (weekday < 7 ){
            System.out.println();
        }
    }
}