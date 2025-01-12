//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.


import java.util.Scanner;

public class CCC12J1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int speedLimit = input.nextInt();
        int carSpeed = input.nextInt();
        int overLimit = carSpeed - speedLimit;
        if (overLimit <= 0)
        {
            System.out.println("Congratulations, you are within the speed limit!");
        }
        else if (1 <= overLimit && overLimit <= 20)
        {
            System.out.println("You are speeding and your fine is $100.");
        }
        else if (21 <= overLimit && overLimit <= 30)
        {
            System.out.println("You are speeding and your fine is $270.");
        }
        else
        {
            System.out.println("You are speeding and your fine is $500.");
        }
    }
}
