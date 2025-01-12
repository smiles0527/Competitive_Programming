import java.util.Scanner;
import java.util.ArrayList;

public class CCC10J4
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        input.close();
        ArrayList<Integer> numbers = new ArrayList<>();
        while (true)
        {
            String[] inputs = input.nextLine().split(" ");
            numbers.clear();
            for (String i : inputs)
            {
                numbers.add(Integer.parseInt(i));
            }
            if (numbers.get(0) == 0)
            {
                break;
            }
            int nsize = numbers.size();
            ArrayList<Integer> difference = new ArrayList<>();
            for (int i = 1; i + 1 < nsize; i++)
            {
                int n = numbers.get(i + 1) - numbers.get(i);
                difference.add(n);
            }
            int count = getPattern(difference);
            System.out.println(count);
        }
    }

    private static int getPattern(ArrayList<Integer> difference)
    {
        int size = difference.size();
        for (int len = 1; len <= size; len++)
        {
            int j = 0;
            boolean good = true;
            for (int i = 0; i < size; i++)
            {
                if (difference.get(i) == difference.get(j))
                {
                    j++;
                    if (j == len)
                    {
                        j = 0;
                    }
                }
                else
                {
                    good = false;
                    break;
                }
            }
            if (good)
            {
                return len;
            }
        }
        return difference.size();
    }
}

