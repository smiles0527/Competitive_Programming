import java.util.Scanner;

public class CCC09J4 {
        public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        String[] words = {"WELCOME", "TO", "CCC", "GOOD", "LUCK", "TODAY"};

        int w = input.nextInt();

        String s = words[0];
        int i = 1;

        while (i < words.length) {
            while (i < words.length && s.length() + words[i].length() + 1 <= w) {
                s += "." + words[i];
                i++;
            }

            System.out.println(full(s, w));
            if (i < words.length) {
                s = words[i];
            } else {
                s = "";
            }

            i++;
        }

        if (s.length() > 0) {
            System.out.println(full(s, w));
        }

        input.close();
    }

        public static String full(String s, int w) {
            StringBuilder t = new StringBuilder(s);
            int i = 0;

            if (t.indexOf(".") > 0) {
                while (t.length() < w) {
                    while (i < t.length() && t.charAt(i) != '.') {
                        i++;
                    }
    
                    if (i >= t.length()) {
                        i = 0;
                    }
    

                    t.insert(i, '.');
                    i++;
    
                    while (i < t.length() && t.charAt(i) == '.') {
                        i++;
                    }
    
                    if (i >= t.length()) {
                        i = 0; 
                    }
                }
            } else {
                while (t.length() < w) {
                    t.append('.');
                }
            }
    
            return t.toString();
        }
    
}
