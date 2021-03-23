/*=============================================================================
|    Assignment: HW 01 - Building and managing a BST
|
|    Author: Musaab Al Jahdhami
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
| I Musaab Al Jahdhami (4440750) affirm that this program is
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
import java.util.LinkedList;
import java.util.Random;

class Hw02 {
    private int is_deleted, level=0;
    private Random generator;
    private Column head = null;
    private Column tail = null;

    public class Column {
        int value;
        List<Node> nodes;
        Column(int _v) {
            this.value = _v;
            this.nodes = new LinkedList<>();
        }
        // add(Node n) {
        //     this.nodes.add(n);
        // }
    }

    public class Node {
        Column prev_col;
        Column next_col;
        Node(Column _prev_col, Column _next_col) {
            this.prev_col = _prev_col;
            this.next_col = _next_col;
        }
    }

    @SuppressWarnings("unchecked")
    public Hw02(String input_name, char _R) {
        try {
            File input_file = new File(input_name);
            Scanner reader = new Scanner(input_file);
            String line;
            String[] splited;
            Node root_node = null, node = null;
            long seed = 42;

            if (_R == 0x72 || _R == 0x52) {
                seed = System.currentTimeMillis();
            }
            generator = new Random(seed);

			while (reader.hasNextLine()) {
				line = reader.nextLine();
				splited = line.split("\\s+");
                if (splited[0].equals("i")) {
                    if (splited.length < 2) {
                        System.out.println("i command:missing numeric parameter");
                        continue;
                    }
                    insert(Integer.parseInt(splited[1]));
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
                    delete(Integer.parseInt(splited[1]));
                    if (is_deleted == 0) {
                        System.out.println("d " + Integer.parseInt(splited[1]) + ": integer " + Integer.parseInt(splited[1]) + " NOT found - NOT deleted");
                    }
                }
                else if (splited[0].equals("p")) {
                    print_skip_list(head);
                }
                else if (splited[0].equals("s")) {
                    if (splited.length < 2) {
                        System.out.println("s command:missing numeric parameter");
                        continue;
                    }
                    if(search(Integer.parseInt(splited[1])) == 1)
                        System.out.println(Integer.parseInt(splited[1]) + ": found");
                    else
                        System.out.println("s " + Integer.parseInt(splited[1]) + ": integer " + Integer.parseInt(splited[1]) + " NOT found");
                }
                else if (splited[0].equals("q")) {
			        reader.close();
                    return;
                }
			}

            // close scanner
			reader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		}
    }

    public void insert(int value) {
        Column temp = lower_bound(value);
        if(temp != tail && temp.value == value)
            return;

        Column inserted_column = new Column(value);
        inserted_column.nodes.add(new Node(null, null));

        while(inserted_column.nodes.size() < level && generator.nextInt()%2 == 1) {
            inserted_column.nodes.add(new Node(null, null));
        }

        Column iter = head;
        for(int _level = level - 1; _level >= 0; _level--) {
            while(iter.nodes.get(_level).next_col != tail && iter.nodes.get(_level).next_col.value < value) {
                iter = iter.nodes.get(_level).next_col;
            }
            if(_level < inserted_column.nodes.size()) {
                Column next_iter = iter.nodes.get(_level).next_col;
                iter.nodes.get(_level).next_col = inserted_column;
                next_iter.nodes.get(_level).prev_col = inserted_column;
                inserted_column.nodes.get(_level).prev_col = iter;
                inserted_column.nodes.get(_level).next_col = next_iter;
            }
        }
        level += 1;
    }

    public int empty() {
        return (head.nodes.get(0).next_col == tail)?1:0;
    }

    public void delete(int value) {
        Column del_column = lower_bound(value);
        if(del_column == tail || del_column.value != value)
            return;

        Column iter = head;
        for(int _level = level - 1; _level >= 0; _level--) {
            while(iter.nodes.get(_level).next_col != tail && iter.nodes.get(_level).next_col.value <= value) {
                iter = iter.nodes.get(_level).next_col;
            }
            if(iter == del_column) {
                Column prev_iter = iter.nodes.get(_level).prev_col, next_iter = iter.nodes.get(_level).next_col;
                prev_iter.nodes.get(_level).next_col = next_iter;
                next_iter.nodes.get(_level).prev_col = prev_iter;
            }
        }
        del_column = null;
    }

    public int search(int value) {
        Column iter = head;
        for(int _level = level - 1; _level >= 0; _level--) {
            while(iter.nodes.get(_level).next_col != tail && iter.nodes.get(_level).next_col.value < value) {
                iter = iter.nodes.get(_level).next_col;
            }
            if (iter.nodes.get(_level).next_col.value == value)
                return 1;
            else if (iter.nodes.get(_level).next_col.value > value)
                return 0;
        }
        return 0;
    }

    public Column lower_bound(int value) {
        Column iter = head;
        for(int _level = level - 1; _level >= 0; _level--) {
            while(iter.nodes.get(_level).next_col != tail && iter.nodes.get(_level).next_col.value < value) {
                iter = iter.nodes.get(_level).next_col;
            }
        }
        return iter.nodes.get(0).next_col;
    }

    public Column upper_bound(int value) {
        Column iter = head;
        for(int _level = level - 1; _level >= 0; _level--) {
            while(iter.nodes.get(_level).next_col != tail && iter.nodes.get(_level).next_col.value <= value) {
                iter = iter.nodes.get(_level).next_col;
            }
        }
        return iter.nodes.get(0).next_col;
    }

    public void print_skip_list(Column iter) {
        if (iter == null)
            return;
        print_skip_list(iter.nodes.get(0).next_col);
        for (int i = 0; i < iter.nodes.size(); i++)
            System.out.print(iter.value + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        if (args[0] == null) {
            System.err.printf("error");
            return ;
        }
        Hw02 g = new Hw02(args[0], (char)0);
    }
}
