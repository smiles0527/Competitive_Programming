public class insertionSortV2 {
    static void insertSortInc(int[] arr)
    {
        for (int i = 1; i < arr.length; i++)
        {
            int cur = arr[i];

            int j=i-1;

            while (arr[j] > cur && j >= 0)
            {
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = cur;

        }
    }
    static void printArray(int[] arr)
    {
        for (int i : arr)
        {
            System.out.print(i + " ");
        }
        System.out.println();
    }
    public static void main(String[] args) {
        int[] array = {11, 25, 65, 37, 28};
        insertSortInc(array);
        printArray(array);
    }
}
