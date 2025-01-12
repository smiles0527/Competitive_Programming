import java.util.*;

public class CCC18S2 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        boolean yes = false;
        int size = input.nextInt();
        input.nextLine();
        int[][] plants = new int[size][size];

        for (int i = 0; i < size; i++) {
            String[] row = input.nextLine().split(" ");
            for (int j = 0; j < row.length; j++) {
                plants[i][j] = Integer.parseInt(row[j]);
            }
        }
        while (!yes) {
            yes = check(plants, size);
            if (yes) {
                print(plants, size);
                break;
            } else {
                rotate90CW(plants, size);
            }
        }
    }

    public static boolean check(int[][] plants, int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1; j++) {
                if (plants[i][j] >= plants[i][j + 1]) {
                    return false;
                }
            }
        }

        for (int i = 0; i < size - 1; i++)
        {
            if (plants[i][0] >= plants[i+1][0])
            {
                return false;
            }
        }
        return true;
    }


    private static void rotate90CW(int[][] table, int size) {

        int[][] result = new int[size][size];

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                result[c][size - 1 - r] = table[r][c];
            }
        }
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                table[r][c] = result[r][c];
            }
        }
    }

    public static void print(int[][] plants, int size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(plants[i][j] + " ");
            }
            System.out.println();
        }
    }
}