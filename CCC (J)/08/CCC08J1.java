import java.util.Scanner;

public class CCC08J1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        double weight = input.nextDouble();
        double height = input.nextDouble();
        double bmi = (weight / (height * height));
        if (bmi > 25)
        {
            System.out.println("Overweight");
        }
        else if (bmi <= 25 && bmi >= 18.5)
        {
            System.out.println("Normal weight");

        }
        else
        {
            System.out.println("Underweight");

        }
    }
}
