import java.io.IOException;
import java.util.Scanner;
import java.util.Arrays;

class Site_exploration {
    private int N, Max_dis = 0;
    private int[] site_distance;
    private int[] site_time;
    private int[] raw_tree;
    private int[] left_lower_tree;
    private int[] right_upper_tree;

    public Site_exploration() {
        init();

        // sort time&distance array follow time x-component
        sort(site_time, site_distance, 0, N-1);

        // create Fenwick Tree with distance array, y-component
        FenwickTree(N);

        // calculate result
        System.out.println(cal_sites());
    }

    private void init() {
        Scanner reader = new Scanner(System.in);
        String line;
        String[] splited;
        int i = 0;
        int[] temp_arr;

        // read possible site number
        if (reader.hasNextLine()) {
            line = reader.nextLine();
            N = Integer.parseInt(line);
        }

        // init array
        site_distance = new int [N];
        site_time = new int [N];

        // read distance and time
        i = 0;
        while (i < N) {
            line = reader.nextLine();
            splited = line.split("\\s+");
            site_distance[i] = Integer.parseInt(splited[0]);
            site_time[i] = Integer.parseInt(splited[1]);
            Max_dis = Math.max(site_distance[i], Max_dis);
            i++;
        }

        // init BIT
        temp_arr = new int [Max_dis+1];
        raw_tree = new int [N+1];
        left_lower_tree = new int [N+1];
        right_upper_tree = new int [N+1];
        for (i = 0; i <= N; i++) {
            raw_tree[i] = 0;
            left_lower_tree[i] = 0;
            right_upper_tree[i] = 0;
        }
        Arrays.fill(temp_arr, 0);
        for (i = 0; i < N; i++) {
            temp_arr[site_distance[i]]++;
        }
        for (i = 0; i < N; i++) {
            raw_tree[i+1] = temp_arr[site_distance[i]];
        }

        // close scanner
        reader.close();
    }

    /* This function takes last element as pivot, places the pivot element at its correct
       position in sorted array, and places all smaller (smaller than pivot) to left of
       pivot and all greater elements to right of pivot */
    private int partition(int arr1[], int arr2[], int low, int high) {
        int pivot = arr1[high], temp;
        int i = low - 1; // index of smaller element
        for (int j = low; j < high; j++) {
            // If current element is smaller than the pivot
            if (arr1[j] < pivot) {
                i++;
                temp = arr1[i];
                arr1[i] = arr1[j];
                arr1[j] = temp;
                temp = arr2[i];
                arr2[i] = arr2[j];
                arr2[j] = temp;
            }
        }
        // swap
        temp = arr1[i+1];
        arr1[i+1] = arr1[high];
        arr1[high] = temp;
        temp = arr2[i+1];
        arr2[i+1] = arr2[high];
        arr2[high] = temp;
        return i+1;
    }

    /* The function to sort arr1&arr2 based on arr1 */
    private void sort(int arr1[], int arr2[], int low, int high) {
        if (low < high) {
            /* index is partitioning index, arr[index] is
              now at right place */
            int index = partition(arr1, arr2, low, high);
            // Recursively sort elements before partition and after partition
            sort(arr1, arr2, low, index-1);
            sort(arr1, arr2, index+1, high);
        }
    }

    private int getBIT(int arr[], int index) {
        int sum = 0, i = index + 1;

        // Traverse ancestors of BITree[index]
        while(i > 0) {
            //if (site_distance[index] > site_distance[i - 1])
                // Add current element of BITree to sum
                sum += arr[i]; 
                //System.out.println("test " + site_distance[i - 1]);
            // Move index to parent node
            i -= i & (-i); 
        }
        return sum; // I want to get the only points that lower index
    }

    private void updateBIT(int []arr, int n, int index, int val) {
        // Traverse all ancestors and add 'val'
        int i = index;
        while(index <= n) {
            // Add 'val' to current node of BIT Tree
            arr[index] += val;

            // Update index to that of parent in update View
            index += index & (-index);
        }
    }

    /* Function to construct fenwick tree from given array */
    private void FenwickTree(int n) {
        // Store the actual values in tree[] using update()
        for(int i = 1; i <= N; i++)
            updateBIT(left_lower_tree, N, i, raw_tree[i]);
    }

    private int cal_sites() {
        int result = 0;
        for (int i = 0; i < N; i++) {
            //result += 
            System.out.print(getBIT(left_lower_tree, i) + " ");
            //System.out.print(left_lower_tree[i] + " ");
        }
        System.out.println();
        return result;
    }

    public static void main(String[] args) {
        Site_exploration t = new Site_exploration();
    }
}
