/*=============================================================================
|    Assignment: HW 01 - Building and managing a BST
|
|    Author: Your name here
|
|    Language: Java
|
|    To Compile: javac Hw01.java
|
|    To Execute: java Hw01 in.txt
|
|    Class: COP3503 - CS II Spring 2021
|    Instructor: McAlpin
|    Due Date: per assignment
|
+=============================================================================*/

/*=============================================================================
|
| I [your name] ([your NID]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList; 
import java.util.List;

class Hw01 {
    public static class Node {
        int val;
        Node left;
        Node right;

        Node(int val) {
            this.val = data;
        }
    }

    public static Node minimum_node(Node root_node) {
        if (root_node.left == null)
            return root_node;
        else {
            return minimum_node(root_node.left);
        }
    }

    public static Node insert_node(Node root_node, Node node_insert) {
        if (root_node == null) {
            root_node = node_insert;
            return root_node;
        }
        
        if (root_node.val > node_insert.val) {
            if (root_node.left == null)
            root_node.left = node_insert;
            else
            insert_node(root_node.left, node_insert);
        }
        else if (root_node.val < node_insert.val)
            if (root_node.right == null)
            root_node.right = node_insert;
        else
        insert_node(root_node.right, node_insert);
        return root_node;
    }

    public static Node delete_node(Node root_node, int val) {
        Node temp_node, min_right_node;
        if (root_node == null)
            return null;
        if (root_node.val > val) {
            root_node.left = delete_node(root_node.left, val);
        } else if (root_node.val < val) {
            root_node.right = delete_node(root_node.right, val);
        } else {
            if (root_node.left != null && root_node.right != null) {
                temp_node = root_node;
                min_right_node = minimum_node(temp_node.right);
                root_node.val = minNodeForRight.val;
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

    public static void sort_node(Node root_node) {
        if (root_node == null)
            return;
        sort_node(root_node.left);
        System.out.print(root_node.data + " ");
        sort_node(root_node.right);
    }

    public Hw01()
    {
        init_BST();
    }
    @SuppressWarnings("unchecked")
    private void init_BST()
    {
        try {
            File input_file = new File("in.txt");
            Scanner reader = new Scanner(input_file);
            String line;
            String[] splited;
            Node root_node = null, node = null;

            // insert root node - the first node
            if (reader.hasNextLine()) {
                line = reader.nextLine();
                splited = line.split("\\s+");
                if (splited[0].equal("i")) {
                    root_node = new Node(Integer.parseInt(splited[1]));
                    insert_node(null, root_node);
                }
                else {
                    System.err.printf("error root node");
                }
            }

			while (reader.hasNextLine()) {
				line = reader.nextLine();
				splited = line.split("\\s+");
                if (splited[0].equal("i")) {
                    node = new Node(Integer.parseInt(splited[1]));
                    insert_node(root_node, node);
                }
                else if (splited[0].equal("d")) {
                    node = new Node(Integer.parseInt(splited[1]));
                    delete_node(root_node, node);
                }
                else if (splited[0].equal("p")) {
                    System.out.print("An error occurred.");
                }
			}

            // read q - number of archeologists
            if (reader.hasNextLine()) {
                line = reader.nextLine();
                q = Integer.parseInt(line);
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

    public static void main(String[] args)
    {
        Hw01 g = new Hw01();
    }
}
