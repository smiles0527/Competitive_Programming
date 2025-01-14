import java.util.*;

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
        int i = 0;
        String result = s;

        if (result.indexOf(".") > 0) {
            while (result.length() < w) {
                while (i < result.length() && result.charAt(i) != '.') {
                    i++;
                }

                if (i >= result.length()) {
                    i = 0;
                }

                result = result.substring(0, i) + "." + result.substring(i);
                i++;

                while (i < result.length() && result.charAt(i) == '.') {
                    i++;
                }

                if (i >= result.length()) {
                    i = 0;
                }
            }
        } else {
            while (result.length() < w) {
                result += ".";
            }
        }

        return result;
    }
}
