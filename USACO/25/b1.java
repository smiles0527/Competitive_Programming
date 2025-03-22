import java.util.*;

public class b1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        int m = input.nextInt();

        char[][] game = new char[n][n];


        for (int i = 0; i < n; i++)
        {
            String line = input.next();
            for (int j = 0; j <= i; j++)
            {
                game[i][j] = line.charAt(j);

                if (game[i][j] == 'W')
                {
                    game[j][i] = 'L';
                }
                else if (game[i][j] == 'L')
                {
                    game[j][i] = 'W';
                }
                else
                {
                    game[j][i] = 'D';
                }
            }
        }


        int[][] winCount = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                winCount[i][j] = (game[i][j] == 'W') ? 1 : 0;
            }
        }

        for (int move = 0; move < m; move++) {
            int s1 = input.nextInt() - 1;
            int s2 = input.nextInt() - 1;

            int count = 0;


            for (int l = 0; l < n; l++) {
                for (int r = 0; r < n; r++) {
                    if ((winCount[l][s1] == 1 && winCount[l][s2] == 1) ||
                            (winCount[r][s1] == 1 && winCount[r][s2] == 1)) {
                        count++;
                    }
                }
            }

            System.out.println(count);
        }
    }
}
