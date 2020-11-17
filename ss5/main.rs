use std::env; // to get arugments passed to the program
use std::thread;
use std::collections::LinkedList;

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

fn calculate_from_list(list: &LinkedList<Vec<usize>>) -> LinkedList<usize> {
    let mut result: LinkedList<usize> = LinkedList::new();
    let mut join_handles = LinkedList::new();
    for v in list {
        let v_clone = v.clone();
        // spawn thread
        join_handles.push_back(thread::spawn(move || map_data(&v_clone)));
    }
    for j in join_handles {
        result.push_back(j.join().unwrap());
    }
    return result;
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

    // CHANGE CODE: Add code that does the following:
    // 1. Calls partition_data to partition the data into equal partitions
    let xs = partition_data(num_partitions, &v);
    // 2. Calls print_partiion_info to print info on the partitions that have been created
    print_partition_info(&xs);
    // 3. Creates one thread per partition and uses each thread to process one partition
    let mut list: LinkedList<Vec<usize>> = LinkedList::new();
    //let mut intermediate_sums : Vec<usize> = Vec::new();

    for items in 0..num_partitions{
        list.push_back(xs[items].clone());
    }

    //create thread in calculate_from_list
    let result = calculate_from_list(&list);

    // 4. Prints information about the intermediate sums
    println!("Intermediate sums = {:?}", result);
    // 5. Calls reduce_data to process the intermediate sums
    let sum = reduce_data(&result);
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
    let mut xs: Vec<Vec<usize>> = Vec::new();

    for j in 0..(num_partitions-1){
        let mut x1 : Vec<usize> = Vec::new();
        for i in j*partition_size..(j+1)*partition_size{
            x1.push(v[i]);
        }
        xs.push(x1);
    }

    let mut x2 : Vec<usize> = Vec::new();
    for i in partition_size*(num_partitions-1)..v.len(){
        x2.push(v[i]);
    }
    xs.push(x2);

    xs
}
