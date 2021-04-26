import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList; 
import java.util.List;

class BinSearch {
    private int is_deleted;
    public class Node {
        int val;
        Node left;
        Node right;

        Node(int data) {
            this.val = data;
        }
    }

    @SuppressWarnings("unchecked")
    public BinSearch(String input_name) {
        try {
            File input_file = new File(input_name);
            Scanner reader = new Scanner(input_file);
            String line;
            String[] splited;
            Node root_node = null, node = null;

			while (reader.hasNextLine()) {
				line = reader.nextLine();
				splited = line.split("\\s+");
                if (splited[0].equals("i")) {
                    if (splited.length < 2) {
                        System.out.println("i command:missing numeric parameter");
                        continue;
                    }
                    node = new Node(Integer.parseInt(splited[1]));
                    insert_node(root_node, node);
                    if (root_node == null) {
                        root_node = node;
                    }
                }
                else if (splited[0].equals("d")) {
                    if (splited.length < 2) {
                        System.out.println("d command:missing numeric parameter");
                        continue;
                    }
                    is_deleted = 0;
                    delete_node(root_node, Integer.parseInt(splited[1]));
                    if (is_deleted == 0) {
                        System.out.println("d " + Integer.parseInt(splited[1]) + ": integer " + Integer.parseInt(splited[1]) + " NOT found - NOT deleted");
                    }
                }
                else if (splited[0].equals("p")) {
                    print_sort_node(root_node);
                    System.out.println();
                }
                else if (splited[0].equals("s")) {
                    if (splited.length < 2) {
                        System.out.println("s command:missing numeric parameter");
                        continue;
                    }
                    if(search_node(root_node, Integer.parseInt(splited[1])) == 1)
                        System.out.println(Integer.parseInt(splited[1]) + ": found");
                    else
                        System.out.println("s " + Integer.parseInt(splited[1]) + ": integer " + Integer.parseInt(splited[1]) + " NOT found");
                }
                else if (splited[0].equals("q")) {
                    System.out.println("left children: " + get_num_node(root_node.left));
                    System.out.println("left depth: " + get_depth(root_node.left));
                    System.out.println("right children: " + get_num_node(root_node.right));
                    System.out.println("right depth: " + get_depth(root_node.right));
			        reader.close();
                    return ;
                }
			}

            // close scanner
			reader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		}
    }

    public Node minimum_node(Node root_node) {
        if (root_node.left == null)
            return root_node;
        else {
            return minimum_node(root_node.left);
        }
    }

    public Node insert_node(Node root_node, Node node_insert) {
        if (root_node == null) {
            return node_insert;
        }

        if (root_node.val >= node_insert.val) {
            if (root_node.left == null)
                root_node.left = node_insert;
            else
                insert_node(root_node.left, node_insert);
        }
        else if (root_node.val < node_insert.val) {
            if (root_node.right == null)
                root_node.right = node_insert;
            else
                insert_node(root_node.right, node_insert);
        }
        return root_node;
    }

    public Node delete_node(Node root_node, int val) {
        Node temp_node, min_right_node;
        if (root_node == null)
            return null;
        /* search in left side */
        if (root_node.val > val) {
            root_node.left = delete_node(root_node.left, val);
        /* search in right side */
        } else if (root_node.val < val) {
            root_node.right = delete_node(root_node.right, val);
        /* found it, delete */
        } else {
            is_deleted = 1;
            if (root_node.left != null && root_node.right != null) {
                temp_node = root_node;
                min_right_node = minimum_node(temp_node.right);
                root_node.val = min_right_node.val;
                root_node.right = delete_node(root_node.right, min_right_node.val);
            }
            else if (root_node.left != null) {
                root_node = root_node.left;
            }
            else if (root_node.right != null) {
                root_node = root_node.right;
            }
            else
                root_node = null;
        }
        return root_node;
    }

    public int search_node(Node root_node, int val) {
        if (root_node == null) {
            return 0;
        }

        while(root_node != null) {
            /* search in left side */
            if (root_node.val > val) {
                root_node = root_node.left;
            }
            /* search in right side */
            else if (root_node.val < val) {
                root_node = root_node.right;
            }
            /* found */
            else {
                return 1;
            }
        }
        return 0;
    }

    public void print_sort_node(Node root_node) {
        if (root_node == null)
            return;
        print_sort_node(root_node.left);
        System.out.print(root_node.val + " ");
        print_sort_node(root_node.right);
    }

    int get_depth(Node node) {
        int left_depth, right_depth;
        if (node == null)
            return 0;
        else {
            left_depth = get_depth(node.left);
            right_depth = get_depth(node.right);

            if (left_depth > right_depth)
                return (left_depth + 1);
            else
                return (right_depth + 1);
        }
    }

    int get_num_node(Node node) {
        if (node == null)
            return 0;
        else {
            return 1 + get_num_node(node.left) + get_num_node(node.right);
        }
    }

    public static void main(String[] args) {
        if (args[0] == null) {
            System.err.printf("error");
            return ;
        }
        BinSearch g = new BinSearch(args[0]);
    }
}
