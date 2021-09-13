/*=============================================================================
|    Assignment: HW 03 - Implementing a Hash function
|
|    Author: Musaab Al Jahdhami
|
|    Language: Java
|
|    To Compile: javac Hw03.java
|
|    To Execute: java Hw03 in.txt
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

class Hw03 {

    @SuppressWarnings("unchecked")
    public Hw03(String input_name) {
        try {
            File input_file = new File(input_name);
            Scanner reader = new Scanner(input_file);
            String line;

			while (reader.hasNextLine()) {
				line = reader.nextLine();
                System.out.format("%10x:%s\n", UCFxram(line, line.length()), line);
			}
            System.out.println("Input file processed");

            // close scanner
			reader.close();
		} catch (FileNotFoundException e) {
			System.out.println("An error occurred.");
			e.printStackTrace();
		}
    }

    public int UCFxram(String input, int len) {
        int randVal1 = 0xbcde98ef; // aribtrary value
        int randVal2 = 0x7890face;
        int hashValue = 0xfa01bc96;
        int roundedEnd = len & 0xfffffffc;
        int tempData;

        for (int i = 0; i < roundedEnd; i = i + 4) {
            tempData = (input.charAt(i) & 0xff) | ((input.charAt(i+1) & 0xff) << 8)
                        | ((input.charAt(i+2) & 0xff) << 16) | (input.charAt(i+3) << 24);
            tempData = tempData * randVal1; // Mulitiply
            tempData = Integer.rotateLeft(tempData, 12);// Rotate left 12 bits
            tempData = tempData * randVal2;// Another Multiply
            hashValue = hashValue ^ tempData; //xor
            hashValue = Integer.rotateLeft(hashValue, 13);  // Rotate left 13 bits
            hashValue = hashValue * 5 + 0x46b6456e;
        }

        // Now collect orphan input characters
        tempData = 0;
        if ((len & 0x03) == 3) {
            tempData = (input.charAt(roundedEnd + 2) & 0xff) << 16;
            len = len - 1;
        }
        if ((len & 0x03) == 2) {
            tempData |= (input.charAt(roundedEnd + 1) & 0xff) << 8;
            len = len - 1;
        }
        if ((len & 0x03) == 1) {
            tempData |= (input.charAt(roundedEnd) & 0xff);
            tempData = tempData * randVal1; // Mulitiply
            tempData = Integer.rotateLeft(tempData, 14); // Rotate left 14 bits
            tempData = tempData * randVal2; // Another Multiply
            hashValue = hashValue ^ tempData;
        }

        hashValue = hashValue ^ len;
        hashValue = hashValue & 0xb6acbe58; // AND
        hashValue = hashValue ^ hashValue >>> 13;
        hashValue = hashValue * 0x53ea2b2c; // Another arbitrary value
        hashValue = hashValue ^ hashValue >>> 16;
        return hashValue;
    }

    public static void main(String[] args) {
        if (args[0] == null) {
            System.err.printf("error");
            return ;
        }
        Hw03 g = new Hw03(args[0]);
    }
}
