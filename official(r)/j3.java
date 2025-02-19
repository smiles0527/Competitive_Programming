import java.util.*;

public class j3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();

        for (int i = 0; i < n; i++) 
        {
            String str = input.next();
            String answer = "";
            int value = 0;

            for (int j = 0; j < str.length(); j++)
            {
                if (Character.isUpperCase(str.charAt(j)))
                {
                    answer += str.charAt(j);
                }
            }

            String dValue = "";

            for (int j = 0; j < str.length(); j++)
            {
                if (Character.isDigit(str.charAt(j)) && !Character.isDigit(str.charAt(j)) && str.charAt(j-1) != '-')
                {
                    value -= str.charAt(j) - '0';
                }
                if (Character.isDigit(str.charAt(j)) && !Character.isDigit(str.charAt(j-1)) && !Character.isDigit(str.charAt(j+1)))
                {
                    value -= str.charAt(j) - '0'; 
                }
                if (Character.isDigit(str.charAt(j)) && Character.isDigit(str.charAt(j+1)))
                {
                    dValue += str.charAt(j);
                }
                if (Character.isDigit(str.charAt(j)) && Character.isDigit(str.charAt(j+1)) && Character.isDigit(str.charAt(j-1)))
                {
                    dValue += str.charAt(j);
                }
                if (!Character.isDigit(str.charAt(j+1)) && !Character.isDigit(str.charAt(j-1)))
                {
                    value += Integer.parseInt(dValue);
                    dValue = "";
                }

            }



            System.out.println(answer + value);
        }


        input.close();
    }
}   