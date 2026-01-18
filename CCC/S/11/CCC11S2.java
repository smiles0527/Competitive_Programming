import java.util.Scanner;

public class CCC11S2
{
    public static void main(String[] args)
    {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        String[] student = new String[n];
        String[] teacher = new String[n];
        for (int i = 0; i < n; i++)
        {
            String answer = input.next();
            student[i] = answer;
        }
        for (int i = 0; i < n; i++)
        {
            String answer = input.next();
            teacher[i] = answer;
        }
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (student[i].equals(teacher[i]))
            {
                count++;
            }
        }
        System.out.println(count);
        input.close();
    }
}
