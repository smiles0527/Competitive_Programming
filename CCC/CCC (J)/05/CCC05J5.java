import java.util.Scanner;

public class CCC05J5 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        while (true) {
            String s = input.nextLine().trim();
            if (s.equals("X")) {
                break;
            }

            if (isMonkeyWord(s)) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }

        input.close();
    }

        public static boolean aWord(String s) {
            if (s.equals("A")) {
                return true;
            } 
            if (s.length() >= 3 && s.charAt(0) == 'B' && s.charAt(s.length() - 1) == 'S') {
                String innerWord = s.substring(1, s.length() - 1);
                return isMonkeyWord(innerWord);
            }
            return false;
        }

        public static boolean isMonkeyWord(String s) {
            if (aWord(s)) {
                return true;
            }
    
            for (int i = 1; i < s.length(); i++) {
                if (aWord(s.substring(0, i)) && s.charAt(i) == 'N') {
                    String secondPart = s.substring(i + 1);
                    if (isMonkeyWord(secondPart)) {
                        return true;
                    }
                }
            }

            return false;
        }
}