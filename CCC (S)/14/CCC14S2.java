import java.util.Scanner;

public class CCC14S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int students = input.nextInt();
        input.nextLine();
        String names = input.nextLine();
        String good = input.nextLine();
        int count = 0;
        String[] first = names.split(" ");
        String[] second = good.split(" ");
        for (int i = 0; i < first.length; i++)
        {
            for (int j = second.length-1; j >=0 ; j--)
            {
                if (first[i].equals(second[j]) && i!=j)
                {
                    if (first[j].equals(second[i]))
                    {
                        count++;
                    }
                    else {
                        System.out.println("bad");
                        return;
                    }
                }
            }
        }
        if (count==students)
        {
            System.out.println("good");
        }
        else {
            System.out.println("bad");
        }
    }
}
