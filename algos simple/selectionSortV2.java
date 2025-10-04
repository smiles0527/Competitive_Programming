public class selectionSortV2 {


    static void selectSortInc(int[] arr)
    {
        for (int i = 0; i < arr.length - 1; i++)
        {
            int minIndex = i;
            
            for (int j = i; j < arr.length; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
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

        selectSortInc(array);
        printArray(array);
    }
}
