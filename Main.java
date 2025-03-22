public class Main {
    public static void main(String[] args) {
        java.util.Scanner sc = new java.util.Scanner(System.in);
        int N = sc.nextInt();
        int Q = sc.nextInt();
        sc.nextLine();
        String S = sc.nextLine();
        char[] arr = S.toCharArray();

        int[] minMprefix = new int[N + 1];
        int[] maxOsuffix = new int[N + 2];
        java.util.Arrays.fill(minMprefix, -1);
        java.util.Arrays.fill(maxOsuffix, -1);

        int current = -1;
        for (int i = 1; i <= N; i++) {
            if (arr[i - 1] == 'm') {
                if (current == -1) {
                    current = i;
                }
            }
            minMprefix[i] = current;
        }

        current = -1;
        for (int i = N; i >= 1; i--) {
            if (arr[i - 1] == 'o') {
                if (current == -1) {
                    current = i;
                }
            }
            maxOsuffix[i] = current;
        }

        while (Q-- > 0) {
            int l = 1;
            int r = N;
            long ans = -1;
            for (int j = l; j <= r; j++) {
                if (arr[j - 1] == 'o') {
                    int iPos = (j - 1 >= l) ? minMprefix[j - 1] : -1;
                    int kPos = (j + 1 <= r) ? maxOsuffix[j + 1] : -1;
                    if (iPos >= l && iPos != -1 && kPos != -1 && kPos <= r) {
                        long area = (long) (j - iPos) * (kPos - j);
                        if (area > ans) {
                            ans = area;
                        }
                    }
                }
            }
            System.out.println(ans);
        }
    }
}
