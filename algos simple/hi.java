public class hi {

    static int add(int[] arr, int i)
    {
        int sum = arr[i];
        if (i < arr.length-1)
        {
            sum += add(arr, i+1);
        }
        return sum;
        
    }
    static void main(String[] args) {
        int[] arr = {1,2,3,4,5,6,7,8,9};
        int sum = add(arr, 0);
        System.out.println(sum);
    }
}