import java.util.*;

public class test {


    
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        input.nextLine();

        for (int i = 0; i < n; i++) {
            String str = input.next();
            String upper = "";

            int value = 0;
            boolean isNegative = false;

            for (int j = 0; j < str.length(); j++) {
                char c = str.charAt(j);
                if (Character.isUpperCase(c)) {
                    upper += c;
                }
            }
            
            String[] numbers = str.split("[^\\d]+|-");
            for (String num : numbers) {
                if (!num.isEmpty()) {
                    if (str.contains("-" + num)) {
                        value -= Integer.parseInt(num);
                        isNegative = true;
                    } else {
                        value += Integer.parseInt(num);
                    }
                }
            }   

            if (isNegative) {
                System.out.println(upper + "-" + Math.abs(value));
            } else {
                System.out.println(upper + value);
            }
        }

        input.close();
    }
}