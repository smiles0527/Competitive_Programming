//Dusa eats Yobis, but only Yobis of a certain size,
// If Dusa encounters a Yobi that is smaller than itself, it eats the Yobi, and absorbs its size. For example, if Dusa is of size 10
//and it encounters a Yobi of size 6
// Dusa eats the Yobi and expands to size 10+6=16
//If Dusa encounters a Yobi that is larger than itself, it runs away
//The first line of input contains a positive integer, representing Dusa's starting size.
//The remaining lines of input contain positive integers representing the sizes of the Yobis in order.


import java.util.Scanner;

public class CCC24J2 {
    public static void main(String[] args) {
        try (Scanner input = new Scanner(System.in)) {
            int dusa = input.nextInt();
            while (true)
            {
                int yobi = input.nextInt();
                if (dusa>yobi)
                {
                    dusa = dusa + yobi;
                }
                else
                {
                    break;
                }
            }
        }

    }
}
