import java.util.*;

public class CCC23J5 {
    static int row;
    static int col;
    static char[][] map;
    static String word;
    static int count;

    public static void backtrack(int r, int c, int index, int dr, int dc, boolean turn) {
        if (r < 0 || r >= row || c < 0 || c >= col || index == word.length() || (map[r][c] != word.charAt(index))) {
            return;
        }
        if (index == word.length()-1)
        {
            count++;
            return;
        }
        if (turn)
        {
            backtrack(r + dr, c + dc, index + 1, dr, dc, true);
        }
        else
        {
            backtrack(r + dr, c + dc, index + 1, dr, dc, false);
            if (index>0)
            {
                if (dr == 1 && dc == 0) //down
                {
                    int ndr = 0;
                    int ndc = -1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = 0;
                    ndc = 1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == -1 && dc == 0) //up
                {
                    int ndr = 0;
                    int ndc = -1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = 0;
                    ndc = 1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == 0 && dc == 1) //left right
                {
                    int ndr = -1;
                    int ndc = 0;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = 1;
                    ndc = 0;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == 0 && dc == -1) //right left
                {
                    int ndr = -1;
                    int ndc = 0;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = 1;
                    ndc = 0;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == -1 && dc == 1) //bottom left top right
                {
                    int ndr = -1;
                    int ndc = -1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = 1;
                    ndc = 1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == 1 && dc == 1) //bottom right top left
                {
                    int ndr = 1;
                    int ndc = -1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = -1;
                    ndc = 1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == 1 && dc == -1) //top right bottom left
                {
                    int ndr = -1;
                    int ndc = -1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = 1;
                    ndc = 1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
                if (dr == -1 && dc == -1) //top left bottom right
                {
                    int ndr = 1;
                    int ndc = -1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                    ndr = -1;
                    ndc = 1;
                    backtrack(r + ndr, c + ndc, index + 1, ndr, ndc, true);
                }
            }
        }

    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        word = input.next();
        row = input.nextInt();
        col = input.nextInt();

        map = new char[row][col];
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                String words = input.next();
                map[r][c] = words.charAt(0);
            }
        }

        count = 0;
        for (int r = 0; r < row; r++) {
            for (int c = 0; c < col; c++) {
                backtrack(r, c, 0, 1, 0, false);   //h lr
                backtrack(r, c, 0, -1, 0, false);  // h rl
                backtrack(r, c, 0, 0, 1, false);   // v tb
                backtrack(r, c, 0, 0, -1, false);  // v bt
                backtrack(r, c, 0, 1, 1, false);   // d tl br
                backtrack(r, c, 0, -1, -1, false); // d br tl
                backtrack(r, c, 0, 1, -1, false);  // d bl tr
                backtrack(r, c, 0, -1, 1, false);  // d tr bl
            }
        }

        System.out.println(count);
        input.close();
    }
}

