import java.util.Scanner;

public class j4v2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numberOfDays = scanner.nextInt();
        char[] weatherSequence = new char[numberOfDays];

        for (int i = 0; i < numberOfDays; i++) {
            weatherSequence[i] = scanner.next().charAt(0);
        }

        int[] consecutiveSunnyFromLeft = new int[numberOfDays];

        if (weatherSequence[0] == 'S') {
            consecutiveSunnyFromLeft[0] = 1;
        } else {
            consecutiveSunnyFromLeft[0] = 0;
        }

        for (int i = 1; i < numberOfDays; i++) {
            if (weatherSequence[i] == 'S') {
                consecutiveSunnyFromLeft[i] = consecutiveSunnyFromLeft[i - 1] + 1;
            } else {
                consecutiveSunnyFromLeft[i] = 0;
            }
        }

        int[] consecutiveSunnyFromRight = new int[numberOfDays];

        if (weatherSequence[numberOfDays - 1] == 'S') {
            consecutiveSunnyFromRight[numberOfDays - 1] = 1;
        } else {
            consecutiveSunnyFromRight[numberOfDays - 1] = 0;
        }

        for (int i = numberOfDays - 2; i >= 0; i--) {
            if (weatherSequence[i] == 'S') {
                consecutiveSunnyFromRight[i] = consecutiveSunnyFromRight[i + 1] + 1;
            } else {
                consecutiveSunnyFromRight[i] = 0;
            }
        }

        int longestPossibleStreak = 0;
        boolean hasPartlyCloudy = false;

        for (int i = 0; i < numberOfDays; i++) {
            if (weatherSequence[i] == 'P') {
                hasPartlyCloudy = true;

                int sunnyDaysBefore = 0;
                if (i > 0) {
                    sunnyDaysBefore = consecutiveSunnyFromLeft[i - 1];
                }

                int sunnyDaysAfter = 0;
                if (i < numberOfDays - 1) {
                    sunnyDaysAfter = consecutiveSunnyFromRight[i + 1];
                }

                int possibleStreak = sunnyDaysBefore + 1 + sunnyDaysAfter;
                if (possibleStreak > longestPossibleStreak) {
                    longestPossibleStreak = possibleStreak;
                }
            }
        }

        if (!hasPartlyCloudy) {
            longestPossibleStreak = numberOfDays - 1;
        }

        System.out.println(longestPossibleStreak);
        scanner.close();
    }
}
