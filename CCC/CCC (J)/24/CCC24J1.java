//There is a new conveyor belt sushi restaurant in town. Plates of sushi travel around the restaurant on a raised conveyor belt and customers choose what to eat by removing plates.
// Each red plate of sushi costs 3
// each green plate of sushi costs 4  and each blue plate of sushi costs 5


import java.util.*;

public class CCC24J1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int r = input.nextInt();
        int g = input.nextInt();
        int b = input.nextInt();
        int total = r * 3 + g * 4 + b * 5;
        System.out.println(total);
        input.close();
    }
}