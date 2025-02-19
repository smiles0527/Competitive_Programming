import java.util.Scanner;

public class j3 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        int n = input.nextInt();
        input.nextLine(); 
        
        for (int i = 0; i < n; i++) {
            String code = input.nextLine();
            String uppercase = "";
            int sum = 0;
        
            for (char c : code.toCharArray()) {
                if (Character.isUpperCase(c)) {
                    uppercase += c;
                }
            }
            
            String[] numbers = code.split("[^-0-9]+");
            for (String num : numbers) {
                if (!num.isEmpty()) {
                    sum += Integer.parseInt(num);
                }
            }
            
            System.out.println(uppercase + sum);
        }
        
        input.close();
    }
}