import java.util.*;
public class CCC19S1
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        String sequence = input.nextLine();
        input.close();
        String[] instructions = sequence.split("");
        int h = 0;
        int v = 0;
        for (String instruction : instructions)
        {
            if (instruction.equals("H"))
            {
                h++;
            }
            else if (instruction.equals("V"))
            {
                v++;
            }
        }
        if (h%2==0)
        {
            if (v%2==0)
            {
                System.out.println("1 2\n3 4");
            }
            else
            {
                System.out.println("2 1\n4 3");
            }
        }
        else {
            if (v%2==0)
            {
                System.out.println("3 4\n1 2");
            }
            else {
                System.out.println("4 3\n2 1");
            }
        }

    }
}
