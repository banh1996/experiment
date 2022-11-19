// Java implementation of the approach
import java.io.BufferedReader;
import java.util.*;
import java.io.*;
 
class compare
{
static boolean CompareUtil(char[] str1,
                                   char[] str2)
{
    int i=0, j=0;

    int len1 = str1.length, len2 = str2.length;
 

    while (i <= len1 && j <= len2)
    {
        while (i < len1 && (!((str1[i] >= 'a' && str1[i] <= 'z') ||
                              (str1[i] >= 'A' && str1[i] <= 'Z') ||
                              (str1[i] >= '0' && str1[i] <= '9'))))
        {
            i++;
        }

        while (j < len2 && (!((str2[j] >= 'a' && str2[j] <= 'z') ||
                              (str2[j] >= 'A' && str2[j] <= 'Z') ||
                              (str2[j] >= '0' && str2[j] <= '9'))))
        {
            j++;
        }
        if (i == len1 && j == len2)
        {
            return true;
        }
        else if (str1[i] != str2[j])
        {
            return false;
        }
        else
        {
            i++;
            j++;
        }
    }

    return false;
}

static void Compareresult(String str1,
                                    String str2)
{
    boolean res;
 
    res = CompareUtil(str1.toCharArray(),
                              str2.toCharArray());

    if (res == true)
    {
        System.out.println("2 strings are equal: success");
    }

    else
    {
        System.out.println("Unequal: fail");
    }
}

public static void main(String[] args)
{
    String allstr1 = "", allstr2 = "";

    try{
        BufferedReader filereader = new BufferedReader(new FileReader(args[0]));
        String readline;
        while ((readline = filereader.readLine()) != null) {
            allstr1 += readline;
        }
        filereader.close();

        BufferedReader filereader2 = new BufferedReader(new FileReader(args[1]));
        while ((readline = filereader2.readLine()) != null) {
            allstr2 += readline;
        }
        filereader2.close();
    } catch(IOException e){
        e.printStackTrace();
    }

    Compareresult(allstr1, allstr2);
}
}