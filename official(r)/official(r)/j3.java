import java.util.*;

public class j3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        input.nextLine();

        for (int i = 0; i < n; i++)
        {
            String str = input.next();
            String upper = "";

            int value = 0;

            for (char c : str.toCharArray())
            {
                if (Character.isUpperCase(c))
                {
                    upper += c;
                }
            }

            String[] numbers = str.split("[^-0-9]+");
            for (String num : numbers)
            {
                if (!num.isEmpty())
                {
                    value += Integer.parseInt(num);
                }
                
            }   

            System.out.println(upper + value);

        }
    }
}   