/*Bessie is using her nifty telescope to take photos of all the stars in the night sky. Her telescope can capture an N×N
1≤N≤1000 photo of the stars where each pixel is either a star or empty sky. Each star will be represented by exactly one pixel,
and no two distinct stars share the same pixel.
 Overnight, something strange happens to the stars in the sky. 
 Every star either disappears or moves A pixels to the right, and B
 pixels downwards (0≤A,B≤N
If a star disappears or moves beyond the photo boundary,
 it no longer appears in the second photo.
 
Bessie took photos before and after the shifting positions, 
but after experimenting in Mootoshop, she accidentally superimposed one photo onto the other.
Now, she can see white pixels where both photos were empty,
gray pixels where stars existed in exactly one photo, 
and black pixels where there was a star in both photos. Bessie also remembers that no new stars moved into the frame of the second photo, so her first photo contains all of the stars in the night sky.
 
Given the final photo, determine the minimum possible number
 of stars in the sky before the shifting incident for T
(1≤T≤1000
) independent test cases. If no arrangement of stars can produce the given final photo, output −1


The first line of input contains T and T test cases will follow.
The first line of each test case will contain NAB

Then follow N lines each representing one row of the superimposed photo. The i
th row from the top is represented by a string ci,1ci,2…ci, where each ci,j∈{W,G,B}
representing the colors white, gray, and black respectively.

It is guaranteed that the sum of N2
 over all test cases will not exceed 107
*/

import java.util.Scanner;

public class USACO24B1 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int t = input.nextInt();
        char[][] array = new char[t][t];

        for (int i = 0; i < t; i++) {
            String n = input.next();
            for (int j = 0; j < t; j++) {
                array[i][j] = n.charAt(j);
            }
        }
        int count = 0;
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                if (array[i][j] == 'B')
                {
                    count++;
                }
                if (array[i][j] == 'G')
                {
                    if (i + 1 < t && array[i + 1][j] == 'G')
                    {
                        count = -1;
                        break;
                    }
                    if (j + 1 < t && array[i][j + 1] == 'G')
                    {
                        count = -1;
                        break;
                    }
                }
            }
        }
        System.out.println(count);

        input.close();
    }
}
