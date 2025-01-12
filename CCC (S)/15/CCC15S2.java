import java.util.ArrayList;
import java.util.Scanner;

public class CCC15S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int j = input.nextInt();
        int a = input.nextInt();
        ArrayList<String> jerseys = new ArrayList<>();
        for (int i = 0; i < j; i++)
        {
            String n = input.next();
            jerseys.add(n);
        }
        int happyAth = 0;
        input.nextLine();
        for (int i = 0; i < a; i++)
        {
            String[] order = input.nextLine().split(" ");
            int index = Integer.parseInt(order[1])-1;
            if (order[0].equals("S") && jerseys.get(index) != null)
            {
                happyAth++;
                jerseys.set(index, null);
            }
            else if (order[0].equals("M") && jerseys.get(index) != null && (jerseys.get(index).equals("M") || jerseys.get(index).equals("L")))
            {
                happyAth++;
                jerseys.set(index, null);
            }
            else if (order[0].equals("L") && jerseys.get(index) != null && (jerseys.get(index).equals("L")))
            {
                happyAth++;
                jerseys.set(index, null);
            }
        }
        System.out.println(happyAth);
    }
}
