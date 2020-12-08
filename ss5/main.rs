use std::env; // to get arugments passed to the program
use std::collections::LinkedList;
use std::thread;

/*
* Print the number of partitions and the size of each partition
* @param vs A vector of vectors
*/
fn print_partition_info(vs: &Vec<Vec<usize>>){
    println!("Number of partitions = {}", vs.len());
    for i in 0..vs.len(){
        println!("\tsize of partition {} = {}", i, vs[i].len());
    }
}

/*
* Create a vector with integers from 0 to num_elements -1
* @param num_elements How many integers to generate
* @return A vector with integers from 0 to (num_elements - 1)
*/
fn generate_data(num_elements: usize) -> Vec<usize>{
    let mut v : Vec<usize> = Vec::new();
    for i in 0..num_elements {
        v.push(i);
    }
    return v;
}

/*
* Partition the data in the vector v into 2 vectors
* @param v Vector of integers
* @return A vector that contains 2 vectors of integers

*/
fn partition_data_in_two(v: &Vec<usize>) -> Vec<Vec<usize>>{
    let partition_size = v.len() / 2;
    // Create a vector that will contain vectors of integers
    let mut xs: Vec<Vec<usize>> = Vec::new();

    // Create the first vector of integers
    let mut x1 : Vec<usize> = Vec::new();
    // Add the first half of the integers in the input vector to x1
    for i in 0..partition_size{
        x1.push(v[i]);
    }
    // Add x1 to the vector that will be returned by this function
    xs.push(x1);

    // Create the second vector of integers
    let mut x2 : Vec<usize> = Vec::new();
    // Add the second half of the integers in the input vector to x2
    for i in partition_size..v.len(){
        x2.push(v[i]);
    }
    // Add x2 to the vector that will be returned by this function
    xs.push(x2);
    // Return the result vector
    xs
}

/*
* Sum up the all the integers in the given vector
* @param v Vector of integers
* @return Sum of integers in v
* Note: this function has the same code as the reduce_data function.
*       But don't change the code of map_data or reduce_data.
*/
fn map_data(v: &Vec<usize>) -> usize{
    let mut sum = 0;
    for i in v{
        sum += i;
    }
    sum
}

/*
* Sum up the all the integers in the given vector
* @param v LinkedList of integers
* @return Sum of integers in v
*/
fn reduce_data(v: &LinkedList<usize>) -> usize{
    let mut sum = 0;
    for i in v{
        sum += i;
    }
    sum
}

fn multi_map_data(vector_list: &LinkedList<Vec<usize>>) -> LinkedList<usize>{
    let mut list: LinkedList<usize> = LinkedList::new();
    let mut t = LinkedList::new();
    for v in vector_list{
        let v_clone = v.clone();
        // create multi threads to cal map_data
        t.push_back(thread::spawn(move || map_data(&v_clone)));
    }
    for j in t{
        list.push_back(j.join().unwrap());
    }
    return list;
}

/*
* A single threaded map-reduce program
*/
fn main() {

    // Use std::env to get arguments passed to the program
    let args: Vec<String> = env::args().collect();
    if args.len() != 3 {
        println!("ERROR: Usage {} num_partitions num_elements", args[0]);
        return;
    }
    let num_partitions : usize = args[1].parse().unwrap();
    let num_elements : usize = args[2].parse().unwrap();
    if num_elements < num_partitions{
        println!("ERROR: num_elements cannot be smaller than num_partitions");
        return;
    }

    // Generate data.
    let v = generate_data(num_elements);
    let v_clone = v.clone();
    // CHANGE CODE: Add code that does the following:
    // create child thread to run the original code, calculate partition_data_in_two
    let child_thread = thread::spawn(move || {
        let xs2 = partition_data_in_two(&v);
        print_partition_info(&xs2);
        // because I modify parameter type in reduce function, so declare LinkedList type
        let mut intermediate_sum2: LinkedList<usize> = LinkedList::new();
        intermediate_sum2.push_back(map_data(&xs2[0]));
        intermediate_sum2.push_back(map_data(&xs2[1]));
        println!("Intermediate sums = {:?}", intermediate_sum2);
        let sum2 = reduce_data(&intermediate_sum2);
        println!("Sum = {}", sum2);
    });
    child_thread.join().unwrap();

    // parent thread
    // 1. Calls partition_data to partition the data into equal partitions
    let xs = partition_data(num_partitions, &v_clone);
    // 2. Calls print_partiion_info to print info on the partitions that have been created
    print_partition_info(&xs);
    // 3. Creates one thread per partition and uses each thread to process one partition
    let mut vector_list: LinkedList<Vec<usize>> = LinkedList::new();
    for i in 0..num_partitions{
        vector_list.push_back(xs[i].clone());
    }

    //create thread in function multi_map_data
    let intermediate_sums = multi_map_data(&vector_list);

    // 4. Prints information about the intermediate sums
    println!("Intermediate sums = {:?}", intermediate_sums);
    // 5. Calls reduce_data to process the intermediate sums
    let sum = reduce_data(&intermediate_sums);
    // 6. Prints the final sum computed by reduce_data
    println!("Sum = {}", sum);
}

/*
* CHANGE CODE: code this function
* Note: Don't change the signature of this function
*
* Partitions the data into a number of partitions such that
*   - the returned partitions contain all elements that are in the input vector
*   - all partitions (except possibly the the last one) have equal number 
*      of elements. The last partition may have either the same number of
*      elements or fewer elements than the other partitions.
*
* @param num_partitions The number of partitions to create
* @param v The data to be partitioned
* @return A vector that contains vectors of integers
* 
*/
fn partition_data(num_partitions: usize, v: &Vec<usize>) -> Vec<Vec<usize>>{
    // Remove the following line which has been added to remove a compiler error
    let partition_size = v.len() / num_partitions;
    let mut remain = v.len() - partition_size*num_partitions;
    let mut start_index = 0;
    let mut xs: Vec<Vec<usize>> = Vec::new();

    for _j in 0..num_partitions{
        let mut x : Vec<usize> = Vec::new();
        for i in start_index..(start_index+partition_size){
            x.push(v[i]);
        }
        start_index += partition_size;
        if remain > 0{
            x.push(start_index);
            start_index += 1;
            remain -= 1;
        }
        xs.push(x);
    }

    xs
}
