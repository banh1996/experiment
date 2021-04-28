// import java.io.File;
// import java.io.FileNotFoundException;
// import java.io.IOException;
// import java.io.FileWriter;
// import java.util.Scanner;

class QuickSort {
    public void swap(int arr[], int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    public int partition(int arr[], int left, int right, int pivot) {
        int leftPointer = left - 1;
        int rightPointer = right;

        while (true) {
            while (arr[++leftPointer] < pivot);
            while (rightPointer > 0 && arr[--rightPointer] > pivot);

            if (leftPointer >= rightPointer) {
                break;
            } else {
                //System.out.println(" swap " + leftPointer + " " + rightPointer);
                swap(arr, leftPointer, rightPointer);
            }
        }

        //System.out.println(" swap2 " + leftPointer + " " + right);
        swap(arr, leftPointer, right);
        //showarr(arr);
        return leftPointer;
    }

    public int getmedian(int arr[], int a, int b, int c) {
        if ((arr[a] > arr[b]) ^ (arr[a] > arr[c]))
            return a;
        else if ((arr[b] < arr[a]) ^ (arr[b] < arr[c]))
            return b;
        else
            return c;
    }

    public void sort(int arr[], int left, int right) {
        int[] stack = new int[right - left + 1];
        int top = 0;
        int size, pivot, partition_num, index;

        stack[top] = left;
        stack[++top] = right;

        while (top >= 0) {
            right = stack[top--];
            left = stack[top--];
            size = right - left + 1;

            if (size <= 7) {
                index = left + size/2;
            }
            else if (size <= 40) {
                index = getmedian(arr, left, left + size/2, right);
            }
            else {
                int a = getmedian(arr, 0*(size-1)/8, 1*(size-1)/8, 2*(size-1)/8);
                int b = getmedian(arr, 3*(size-1)/8, 4*(size-1)/8, 5*(size-1)/8);
                int c = getmedian(arr, 6*(size-1)/8, 7*(size-1)/8, 8*(size-1)/8);
                index = getmedian(arr, a, b, c);
            }

            pivot = arr[index];
            swap(arr, index, right);

            //System.out.println(" pivot " + pivot + " " + left + " " + right );
            partition_num = partition(arr, left, right, pivot);
            //System.out.println(" partition_num " + partition_num);

            if (partition_num - 1 > left) {
                stack[++top] = left;
                stack[++top] = partition_num - 1;
            }

            if (partition_num + 1 < right) {
                stack[++top] = partition_num + 1;
                stack[++top] = right;
            }
        }
    }

    static void showarr(int arr[]) {
        int i;
        for (i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.print("\n");
    }
 
    public static void main(String[] args) {
        int arr[] = { 4, 2, 1, 8, 5 ,0, 9, 6, 7, 3 };
        System.out.println("Given Array: ");
        showarr(arr);

        QuickSort t = new QuickSort();
        t.sort(arr, 0, arr.length - 1);

        System.out.println("\nSorted array: ");
        showarr(arr);
    }
}