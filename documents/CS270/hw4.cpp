#include <iostream>  
#include <cstring>  
#include <cmath>
#include <bits/stdc++.h>

using namespace std;  

static int **gp_cities;
static int **gp_build;
static int **gp_destroy;
static int **gp_MST;
static int g_city_number = 0;

static int get_min_key(int *key, bool *MST_arr, int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int i = 0; i < V; i++)
        if (MST_arr[i] == false && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }

    return min_index;
}

static void printresult(int *parent, int V)
{
    int result = 0;

    //calculate destroy cost
    for (int i = 0; i < V-1; i++) {
        for (int j = i+1; j < V; j++)
        {
            if (gp_cities[i][j] == 1) // if this path is built
            {
                result += gp_destroy[i][j];
            }
        }
    }

    //calculate build cost and subtract destroy cost
    for (int i = 1; i < V; i++)
    {
        if (gp_cities[i][parent[i]] == 1) // if this path is built
            result -= gp_destroy[i][parent[i]];
        else
            result += gp_build[i][parent[i]];
    }

    cout<<result<<endl;
}

static void primMST(int **graph, int V)
{
    int parent[V]; //MST array
    int key[V];
    bool MST_arr[V];
 
    // Initialize all keys are MAX_INT
    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        MST_arr[i] = false;
    }

    key[0] = 0;
    parent[0] = -1; //root node

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Get the minimum key vertex that not yet included in MST
        int u = get_min_key(key, MST_arr, V);
 
        // Add this vertex to the MST arr
        MST_arr[u] = true;
 
        // Update key value and parent index
        for (int v = 0; v < V; v++)
        {
            if (MST_arr[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
        }
    }

    printresult(parent, V);
}
 
int main(int argc, char **argv)
{
    char str[10000]; // declare the size of string
    char *p_cities, *p_build, *p_destroy; // declare pointer
    int i, line_index = 0;

    cin.getline(str, 10000);
    p_cities = strtok(str, " "); // get cities
    p_build = strtok(NULL, " "); // get build cost
    p_destroy = strtok(NULL, " "); // get destroy cost
    g_city_number = sqrt(strlen(p_cities)); // get city number

    // allocate cities matrixes
    gp_cities = new int* [g_city_number];
    gp_build = new int* [g_city_number];
    gp_destroy = new int* [g_city_number];
    gp_MST = new int* [g_city_number];
    for (i = 0; i < g_city_number; i++) {
        gp_cities[i] = new int[g_city_number];
        gp_build[i] = new int[g_city_number];
        gp_destroy[i] = new int[g_city_number];
        gp_MST[i] = new int[g_city_number];
    }

    // assign values to matrixes
    line_index = 0;
    for (i = 0; i < strlen(p_cities); i++) {
        if (p_cities[i] == ',')
            line_index++;
        else
        {
            gp_cities[line_index][i%(g_city_number+1)] = p_cities[i] - '0';
            if (p_build[i] >= 'A' && p_build[i] <= 'Z')
                gp_build[line_index][i%(g_city_number+1)] = p_build[i] - 'A';
            else
                gp_build[line_index][i%(g_city_number+1)] = p_build[i] - 'a' + 26;

            if (p_destroy[i] >= 'A' && p_destroy[i] <= 'Z')
                gp_destroy[line_index][i%(g_city_number+1)] = p_destroy[i] - 'A';
            else
                gp_destroy[line_index][i%(g_city_number+1)] = p_destroy[i] - 'a' + 26;

            if (p_cities[i] == '0') //check this road is not-build?
                gp_MST[line_index][i%(g_city_number+1)] = gp_build[line_index][i%(g_city_number+1)];
            else //this road is built
                gp_MST[line_index][i%(g_city_number+1)] = -gp_destroy[line_index][i%(g_city_number+1)];
        }
    }

    // cout << "1:" << p_cities << " " <<endl;
    // cout << "2:" << p_build <<endl;
    // cout << "3:" << p_destroy <<endl;

    primMST(gp_MST, g_city_number);

    // free memory
    for (int i = 0; i < g_city_number; i++)
    {
        delete[] gp_cities[i];
        delete[] gp_build[i];
        delete[] gp_destroy[i];
        delete[] gp_MST[i];
    }
    delete[] gp_cities;
    delete[] gp_build;
    delete[] gp_destroy;
    delete[] gp_MST;

    return 0;  
}  
