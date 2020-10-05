import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList; 
import java.util.List;

class Graph {
    private int m, n, q;
    private ArrayList<Integer>[] graph_data;
    private ArrayList<Integer>[] weigths;
    private ArrayList<Integer>[] archeologist_paths;
    private boolean[] result;

    public Graph()
    {
        init_graph();
        try {
            File output_file = new File("ouput.txt");
            output_file.createNewFile();
            FileWriter myWriter = new FileWriter("ouput.txt");

            for (int i = 0; i < q; i++) {
                check_path(i, archeologist_paths[i].get(0), archeologist_paths[i].get(1), archeologist_paths[i].get(2));
                if (result[i]) {
                    myWriter.write("Yes\n");
                }
                else {
                    myWriter.write("No\n");
                }
            }
            myWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
    @SuppressWarnings("unchecked")
    private void init_graph()
    {
        try {
            File input_file = new File("extra_input.txt");
            Scanner reader = new Scanner(input_file);
            String line;
            String[] splited;
            int i = 0;

            // read m - line number, n - pedestal number
            if (reader.hasNextLine()) {
                line = reader.nextLine();
                splited = line.split("\\s+");
                n = Integer.parseInt(splited[0]);
                m = Integer.parseInt(splited[1]);
            }

            // init null array for graph
            graph_data = new ArrayList[n];
            weigths = new ArrayList[n];
            for (i = 0; i < n; i++) {
                graph_data[i] = new ArrayList<>();
                weigths[i] = new ArrayList<>();
            }

            // read graph from input.txt to array
            i = 0;
			while (reader.hasNextLine() && i < m) {
				line = reader.nextLine();
				splited = line.split("\\s+");
				graph_data[Integer.parseInt(splited[0]) - 1].add(Integer.parseInt(splited[1]) - 1);
                graph_data[Integer.parseInt(splited[1]) - 1].add(Integer.parseInt(splited[0]) - 1);
				weigths[Integer.parseInt(splited[0]) - 1].add(Integer.parseInt(splited[2]));
                weigths[Integer.parseInt(splited[1]) - 1].add(Integer.parseInt(splited[2]));
				i++;
			}

            // read q - number of archeologists
            if (reader.hasNextLine()) {
                line = reader.nextLine();
                q = Integer.parseInt(line);
            }

            // init null array for archeologist_paths
            archeologist_paths = new ArrayList[q];
            for (i = 0; i < q; i++) {
                archeologist_paths[i] = new ArrayList<>();
            }

            // read archeologist paths
            i = 0;
            while (reader.hasNextLine() && i < q) {
				line = reader.nextLine();
				splited = line.split("\\s+");
				archeologist_paths[i].add(Integer.parseInt(splited[0]) - 1); // read s
				archeologist_paths[i].add(Integer.parseInt(splited[1]) - 1); // read e
				archeologist_paths[i].add(Integer.parseInt(splited[2])); // read w
				i++;
			}

            result = new boolean[q];
            Arrays.fill(result, false);

            // close scanner
			reader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		}
    }

    public void check_path(int index, int s, int e, int w)
    {
        boolean[] isVisited = new boolean[n];
        bfs(index, s, e, w, isVisited);
    }

    private void bfs(int index, Integer s, Integer e, Integer w,
                     boolean[] isVisited)
    {
        int que[] = new int[n];
        Arrays.fill(que, 0); 

        int front = -1, rear = -1;
        Arrays.fill(isVisited, false);
        isVisited[s] = true;

        // To add any non isVisited node we will increment the rear
        // and add that vertex to the end of the array (enqueuing)
        que[++rear] = s;

        int k;
        // The loop will continue till the rear and front are equal
        while (front != rear) {
            // Here Dequeuing is nothing but to increment the front
            k = que[++front];
            for (int i = 0; i < graph_data[k].size(); i++) {
                int j = graph_data[k].get(i);
                if (!isVisited[j] && weigths[k].get(i) >= w) {
                    // Exit when visit pedestal 'e'
                    if (j == e) {
                        result[index] = true;
                        return;
                    }
                    que[++rear] = j;
                    isVisited[j] = true;
                }
            }
        }
    }

    public static void main(String[] args)
    {
        Graph g = new Graph();
    }
}
