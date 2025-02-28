import java.util.*;

public class j3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        input.nextLine(); // Consume the newline

        for (int i = 0; i < n; i++) {
            String original = input.nextLine();
            String answer = convert(original);
            System.out.println(answer);
        }

        input.close();
    }

    public static String convert(String original) {
        // Extract uppercase letters
        String upper = "";
        for (int i = 0; i < original.length(); i++) {
            if (Character.isUpperCase(original.charAt(i))) {
                upper += original.charAt(i);
            }
        }

        int sum = 0;
        int i = 0;
        while (i < original.length()) {
            if (Character.isDigit(original.charAt(i)) || 
                (original.charAt(i) == '-' && i + 1 < original.length() && Character.isDigit(original.charAt(i + 1)))) {
                
                // Extract the number as a string
                String numStr = "";
                if (original.charAt(i) == '-') {
                    numStr += '-';
                    i++;
                }
                while (i < original.length() && Character.isDigit(original.charAt(i))) {
                    numStr += original.charAt(i);
                    i++;
                }
                sum += Integer.parseInt(numStr);
            } else {
                i++;
            }
        }

        if (sum < 0) {
            return upper + "-" + Math.abs(sum);
        }
        return upper + sum;
    }
}
