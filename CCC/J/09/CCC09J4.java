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

            System.out.println(justify(s, w));

            if (i < words.length) {
                s = words[i];
            } else {
                s = "";
            }

            i++;
        }

        if (s.length() > 0) {
            System.out.println(justify(s, w));
        }

        input.close(); 
    }


    public static String justify(String s, int w) {

        if (s.indexOf('.') > 0) {
            String[] str = s.split("\\.");  
            int totalChars = 0;

            for (int i = 0; i < str.length; i++) {
                String word = str[i];
                totalChars += word.length();
            }           
            int totalDots = w - totalChars;  
            int gaps = str.length - 1;  


            if (gaps > 0) {
                int dotGap = totalDots / gaps; 
                int dotRem = totalDots % gaps; 

                String result = str[0];

                for (int i = 1; i < str.length; i++) {
                    
                    result += dots(dotGap);

                    
                    if (dotRem > 0) {
                        result += ".";
                        dotRem--;
                    }

                    result += str[i];
                }
                return result;
            } else {
                return s + dots(totalDots); 
            }
        } else {
           
            return s + dots(w - s.length());
        }
    }


    private static String dots(int count) {
        String result = "";
        for (int i = 0; i < count; i++) {
            result += "."; 
        }
        return result;
    }
}
