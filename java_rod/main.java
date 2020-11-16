import java.util.Scanner;
import java.util.Arrays;

class Max_rod {
    private int R, C;
    private int value[];
    private int weigth[];

    public Max_rod()
    {
        read_input();
        System.out.println(knapsack(weigth, value, R, C));
    }

    private void read_input()
    {
        Scanner reader = new Scanner(System.in);
        String line;
        String[] splited;
        int i = 0;

        // read C - amount of weight can carry, R - number of rods
        if (reader.hasNextLine()) {
            line = reader.nextLine();
            splited = line.split("\\s+");
            C = (int)(1000*Float.parseFloat(splited[0]));
            R = Integer.parseInt(splited[1]);
        }

        // init array
        weigth = new int[R];
        value = new int[R];

        // read weight and value
        i = 0;
        while (i < R) {
            line = reader.nextLine();
            splited = line.split("\\s+");
            value[i] = Integer.parseInt(splited[0]);
            weigth[i] = (int)(1000*Float.parseFloat(splited[1]));
            i++;
        }

        // close scanner
        reader.close();
    }

    private int knapsack(int w[], int v[], int len, int max_sum)
    {
        // the complex space is O(max_sum)
        int i, j, max_current_value = 0;
        int K[] = new int[max_sum + 1];
        Arrays.fill(K, 0);

        for (i = 1; i <= len; i++) {
            // use reverse state
            for (j = max_sum; j >= 1; j--) {
                max_current_value = 0;
                // check if the knapsack can fit
                if (j >= w[i - 1]) {
                    max_current_value = v[i - 1];
                    max_current_value += K[j - w[i - 1]];
                }
                K[j] = Math.max(K[j], max_current_value);
            }
        }

        return K[max_sum];
    }

    public static void main(String[] args)
    {
        Max_rod g = new Max_rod();
    }
}
