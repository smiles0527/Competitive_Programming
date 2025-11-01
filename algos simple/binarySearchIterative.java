class binarySearchIterative { //array MUST be sorted
  
    static int binarySearch(int arr[], int x) {
        int low = 0, high = arr.length - 1; //arr.length returns the length in 1-based indexing 
        while (low <= high) {
            int mid = low + (high - low) / 2; // same formula as merge sort, save memory space 

            if (arr[mid] == x)
                return mid;

            if (arr[mid] < x)
                low = mid + 1;

            else
                high = mid - 1;
        }
        
        return -1;
    }

    public static void main(String args[]) {
        int arr[] = { 2, 3, 4, 10, 40 };
        int x = 10;
        int result = binarySearch(arr, x);
        if (result == -1)
            System.out.println(
                "Element is not present in array");
        else
            System.out.println("Element is present at "
                               + "index " + result);
    }
}