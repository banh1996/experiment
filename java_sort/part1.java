import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;

class MergeSort {
    void merge(int arr[], int l, int m, int r) {
        /* Find sizes of two subarrays to be merged */
        int left_size = m - l + 1;
        int right_size = r - m;
        int L[] = new int[left_size];
        int R[] = new int[right_size];
        int i, j, k;

        /* Copy data to L, R arrays */
        for (i = 0; i < left_size; ++i)
            L[i] = arr[l + i];
        for (j = 0; j < right_size; ++j)
            R[j] = arr[m + 1 + j];

        i = 0; j = 0; k = l;
        /* merge L&R */
        while (i < left_size && j < right_size) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        /* Copy remaining elements of L to arr if any */
        while (i < left_size) {
            arr[k] = L[i];
            i++;
            k++;
        }

        /* Copy remaining elements of R to arr if any */
        while (j < right_size) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    int find_subarray(int arr[], int l, int r) {
        int m = l;
        if (l < r) {
            if (arr[l] <= arr[l+1]) {
                /* non-decreasing */
                for (int i = l; i < r; i++) {
                    if (arr[i] <= arr[i+1]) {
                        m = i+1;
                    }
                    else
                        break;
                }
            }
            else {
                /* decreasing */
                for (int i = l; i < r; i++) {
                    if (arr[i] > arr[i+1]) {
                        m = i+1;
                    }
                    else
                        break;
                }

                /* Reverse */
                for (int i = l; i < l + (m-l+1)/2; i++) {
                    int temp = arr[i];
                    arr[i] = arr[m-i+l];
                    arr[m-i+l] = temp;
                }
            }
        }
        return m;
    }

    void sort(int arr[], int first, int last) {
        int l = first, m = first, r = first;

        /* find non-decreasing or decreasing segments */
        m = find_subarray(arr, l, last);
        while (m < last) {
            r = find_subarray(arr, m+1, last);

            // Merge the sorted array
            merge(arr, l, m, r);
            m = r;
        }
    }

    static void printArray(int arr[]) {
        int n = arr.length;
        for (int i = 0; i < n; ++i)
            System.out.print(arr[i] + " ");
        System.out.println();
    }

    public static void main(String args[]) {
        //int arr[] = { 12, 11, 13, 5, 6, 7 };
        int arr[] = { 2, 3, 6, 1, 9, 7, 5, 4 };
 
        System.out.println("Given Array");
        printArray(arr);
 
        MergeSort t = new MergeSort();
        t.sort(arr, 0, arr.length - 1);
 
        System.out.println("\nSorted array");
        printArray(arr);
    }
}