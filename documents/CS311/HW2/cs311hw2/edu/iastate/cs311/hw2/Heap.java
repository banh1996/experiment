package edu.iastate.cs311.hw2;

/**
 * @author 
 *  A simple priority queue interface and a class template implementing
 *  the interface with a heap and a heap sort algorithm. This code template is
 *  written by Xiaoqiu Huang for Com S 311 in Spring 2021.
 */

import java.util.List;
import java.util.ArrayList;
import java.util.NoSuchElementException;

interface ExtendedPriorityQueue<E>
{
  int size();
  boolean isEmpty();
  void add(E element);

  // Returns a high-priority element without removing it.
  E getMin();

  // Removes a high-priority element.
  E removeMin();

  // Returns an element at the last nonleaf node in the heap
  E getLastInternal();

  // Removes all elements at each leaf node in the heap
  void trimEveryLeaf();

  // Shows the heap as a binary tree in plain text
  void showHeap();
}

public class Heap<E extends Comparable<? super E>>
   implements ExtendedPriorityQueue<E>
{
  private static final int INIT_CAP = 10; // A default size of list
  private ArrayList<E> list; // used as an array to keep the elements in the heap
  // list.size() returns the number of elements in the list,
  // which is also the size of the heap.
  // For 0 <= k < list.size(), list.get(k) returns the element at position k of list
  // list.remove( list.size() - 1 ) removes the last element from the list;
  // note that there is no need to remove any element before the last element.

  public Heap()
  {
    list = new ArrayList<E>(INIT_CAP);
  }

  public Heap(int aSize)
  {
     if ( aSize < 1 )
	throw new IllegalStateException();
     list = new ArrayList<E>(aSize);
  }

  // Builds a heap from a list of elements.
  public Heap(List<E>  aList)
  {
     int j, k;
     int len = aList.size();
     if ( len < 1 )
	throw new IllegalArgumentException();
     list = new ArrayList<E>(len);
     for ( E t : aList )
        list.add(t);
     if ( len < 2 ) return;
     j = (len - 2) / 2; // j is the largest index of an internal node with a child.
     for ( k = j; k >= 0; k-- )
        percolateDown(k);
  }  // O(n) time

  public int size()
  {
    return list.size();
  }

  public boolean isEmpty()
  {
    return list.isEmpty();
  }

  public void add(E element)
  {
    if ( element == null )
      throw new NullPointerException("add");
    list.add(element); // append it to the end of the list
    percolateUp(); // move it up to the proper place
  }

  // TODO: O(log n)
  // Moves the last element up to the proper place so that the heap property holds.
  private void percolateUp()
  {
    int parent = (list.size() - 2)/2, child = list.size() - 1;
    while (parent >= 0 && list.get(child).compareTo(list.get(parent)) > 0) {
      swap(parent, child);
      child = parent;
      parent = (parent - 1)/2;
    }
  }

  // Swaps the elements at the parent and child indexes.
  private void swap(int parent, int child)
  {
    E tmp = list.get(parent);
    list.set( parent, list.get(child) );
    list.set(child, tmp);
  }

  public E getMin()
  {
    if ( list.isEmpty() )
      throw new NoSuchElementException();
    return list.get(0);
  }

  // TODO: O(1)
  // Returns an element at the last nonleaf node in the heap
  // If the size of the heap is less than 2, it throws new NoSuchElementException().
  public  E getLastInternal()
  {
    return list.get((list.size() - 2)/2);
  }

  public E removeMin()
  {
    if ( list.isEmpty() )
      throw new NoSuchElementException();
    E minElem = list.get(0); // get the min element at the root
    list.set(0, list.get(list.size() - 1) ); // copy the last element to the root
    list.remove( list.size() - 1 ); // remove the last element from the list
    if ( ! list.isEmpty() )
     percolateDown(0); // move the element at the root down to the proper place
    return minElem;
  }

  // TODO: O(n)
  // If the heap contains internal (nonleaf) nodes, trim every leaf element.
  // If the size of the heap is less than 2, it throws new NoSuchElementException().
  public void trimEveryLeaf()
  {

  }

  // TODO: O(log n)
  // Move the element at index start down to the proper place so that the heap property holds.
  private void percolateDown(int start)
  {
    if ( start < 0 || start >= list.size() )
      throw new RuntimeException("start < 0 or >= n");
    while (start >= (list.size() - 2)/2) {
      int leftChild = 2*start + 1;
      int rightChild = 2*start + 2;

      if ()
    }
  }

  // Shows the tree used to implement the heap with the root element at the leftmost column
  // and with 'null' indicating no left or right child.
  // This method is used to help check if the heap is correctly constructed.
  public void showHeap()
  {
    if ( list.isEmpty() ) return;
    recShowHeap(0, ">");
  }

  public void recShowHeap(Integer r, String level)
  {
    int len = list.size();
    if ( r >= len )
    {
      System.out.println(level + "null");
      return;
    }
    System.out.println(level + list.get(r) ); // get the min element at the root
    recShowHeap(2 * r + 1, " " + level);
    recShowHeap(2 * r + 2, " " + level);
  }

  // This method repeatedly removes the smallest element in the heap and add it to the list.
  public static <E extends Comparable<? super E>> void heapSort(List<E> aList)
  {
    if ( aList.isEmpty() ) return;
    Heap<E> aHeap = new Heap<E>(aList);
    aList.clear();
    while ( ! aHeap.isEmpty() )
      aList.add( aHeap.removeMin() );
  }
} // Heap
