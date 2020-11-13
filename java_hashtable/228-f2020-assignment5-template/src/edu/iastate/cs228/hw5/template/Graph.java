package edu.iastate.cs228.hw5.template;


import java.util.ArrayList;
import java.util.Collection;


/**
 * A graph used to generate a perfect hash table.
 *
 * @author
 */
public
class
Graph
{
  /**
   * The vertices of the graph.
   */
  private
  final
  Vertex[]
  vertices;


  /**
   * Initializes the graph to have the given number of vertices.
   *
   * @param vertexCount
   *   the number of vertices in the graph
   *
   * @throws IllegalArgumentException
   *   if {@code vertexCount} is negative
   */
  public
  Graph(int vertexCount)
    throws IllegalArgumentException
  {
    if (0 > vertexCount)
    {
      throw new IllegalArgumentException(String.valueOf(vertexCount));
    }


    this.vertices = new Vertex[vertexCount];

    for (int i = 0; i < vertexCount; ++i)
    {
      this.vertices[i] = new GraphVertex(i);
    }
  }

  /**
   * Initializes the graph to use the given vertex array.
   * Performs no other initialization.
   *
   * @param vertexArray
   *   the vertex array to use
   */
  public
  Graph(Vertex[] vertexArray)
  {
    /*
     * For grading.
     * Do not change this constructor.
     */

    this.vertices = vertexArray;
  }


  /**
   * Returns the array of vertices used by this graph.
   *
   * @return
   *   the array of vertices used by this graph
   */
  public
  Vertex[]
  getVertices()
  {
    /*
     * For grading.
     * Do not change this method.
     */

    return vertices;
  }

  /**
   * Adds an undirected edge between the two indicated vertices.
   *
   * @param fromIdx
   *   the index of the from vertex
   * @param toIdx
   *   the index of the to vertex
   * @param index
   *   the index of the data of the edge to add
   * @param word
   *   the data of the edge to add
   *
   * @throws IndexOutOfBoundsException
   *   if either of {@code fromIdx} and {@code toIdx} are invalid vertex
   *   indices
   * @throws NullPointerException
   *   if {@code word} is {@code null}
   */
  public
  void
  addEdge(int fromIdx, int toIdx, int index, String word)
    throws IndexOutOfBoundsException,
           NullPointerException
  {
    // TODO
    System.out.println("addEdge " + fromIdx + " " + toIdx + " " + index + " " + word);
    // GraphVertex from = new GraphVertex(fromIdx);
    // GraphVertex to = new GraphVertex(toIdx);
    GraphEdge edge = new GraphEdge(index, word, this.vertices[fromIdx], this.vertices[toIdx]);
    this.vertices[index].setedge(edge);
  }

  /**
   * Marks all vertices and edges within the graph as unvisited.
   */
  public
  void
  unvisitAll()
  {
    // TODO
  }

  /**
   * Creates and fills a G array for this graph.
   *
   * @param words
   *   the number of keys in the hash table
   * @return
   *   the populated G array
   */
  public
  int[]
  fillGArray(int words)
  {
    unvisitAll();

    int[] toRet = new int[vertices.length];

    for (Vertex v : vertices)
    {
      if (!v.isVisited())
      {
        toRet[v.index()] = 0;
        v.fillGArray(toRet, words);
      }
    }

    return toRet;
  }

  /**
   * Returns true if and only if this graph contains a cycle.
   *
   * @return
   *   whether this graph contains a cycle
   */
  public
  boolean
  hasCycle()
  {
    // TODO
    return false;
  }

  @Override
  public
  String
  toString()
  {
    StringBuilder build = new StringBuilder();

    build.append("Graph with ")
         .append(vertices.length)
         .append(" vertices:")
         .append(System.lineSeparator());

    for (Vertex v : vertices)
    {
      build.append("  ")
           .append(v)
           .append(System.lineSeparator());
    }

    if (vertices.length > 0)
    {
      // remove trailing newline
      build.setLength(build.length() - System.lineSeparator().length());
    }

    return build.toString();
  }

  private
  class
  GraphVertex
    implements Vertex
  {
    /**
     * Whether this vertex is marked as visited.
     */
    private
    boolean
    visited;

    /**
     * The index of this vertex within the vertices array.
     */
    private
    final
    int
    index;

    /**
     * Outgoing edges from this vertex.
     */
    private
    final
    Collection<Edge>
    edges;


    /**
     * Initializes the vertex.
     *
     * @param index
     *   the index of the vertex within the vertices array
     */
    public
    GraphVertex(int index)
    {
      this.visited = false;
      this.index = index;
      this.edges = new ArrayList<>();
    }

    @Override
    public
    void
    setedge(Edge edge)
    {
      this.edges.add(edge);
    }


    @Override
    public
    boolean
    isVisited()
    {
      return visited;
    }

    @Override
    public
    void
    setVisited(boolean visited)
    {
      // TODO

      /*
       * Don't forget to handle the special false case.
       */
    }

    @Override
    public
    int
    index()
    {
      return index;
    }

    @Override
    public
    Collection<Edge>
    edges()
    {
      return edges;
    }

    @Override
    public
    void
    fillGArray(int[] g, int words)
      throws IndexOutOfBoundsException
    {
      this.visit();

      for (Edge edge : edges())
      {
        if (!edge.isVisited())
        {
          edge.visit();

          // mark other direction of the edge as visited
          for (Edge neighborEdge : edge.getTo().edges())
          {
            if (this == neighborEdge.getTo())
            {
              neighborEdge.visit();

              break;
            }
          }

          // visit neighbor
          if (!edge.getTo().isVisited())
          {
            g[edge.getTo().index()]
              = (edge.index() - g[index()] + words) % words;

            edge.getTo().fillGArray(g, words);
          }
        }
      }
    }

    @Override
    public
    boolean
    hasCycle(Vertex from)
    {
      // TODO
      return false;
    }

    @Override
    public
    String
    toString()
    {
      return "v[" + index() + "]: " + edges().toString();
    }
  }

  private
  class
  GraphEdge
    implements Edge
  {
    /**
     * Whether this edge is marked as visited.
     */
    private
    boolean
    visited;

    /**
     * The index of the data of this edge.
     */
    private
    final
    int
    index;

    /**
     * The data of this edge.
     */
    private
    final
    String
    data;

    /**
     * The vertex from which this edge is outgoing.
     */
    private
    final
    Vertex
    from;

    /**
     * The vertex to which this edge is incoming.
     */
    private
    final
    Vertex
    to;


    /**
     * Initializes the edge.
     *
     * @param index
     *   the index of the data of the edge
     * @param data
     *   the data of the edge
     * @param from
     *   the vertex from which the edge is outgoing
     * @param to
     *   the vertex to which the edge is incoming
     */
    public
    GraphEdge(int index, String data, Vertex from, Vertex to)
    {
      this.visited = false;
      this.index = index;
      this.data = data;
      this.from = from;
      this.to = to;
    }


    @Override
    public
    boolean
    isVisited()
    {
      return visited;
    }

    @Override
    public
    void
    setVisited(boolean visited)
    {
      this.visited = visited;
    }

    @Override
    public
    int
    index()
    {
      return index;
    }

    @Override
    public
    String
    data()
    {
      return data;
    }

    @Override
    public
    Vertex
    getFrom()
    {
      return from;
    }

    @Override
    public
    Vertex
    getTo()
    {
      return to;
    }

    @Override
    public
    String
    toString()
    {
      StringBuilder build = new StringBuilder();

      build.append("GraphEdge@")
           .append(hashCode()) // address (unique per instance)
           .append(": ")
           .append(data())
           .append(" (")
           .append(index())
           .append("), v[")
           .append(getFrom().index())
           .append("]-v[")
           .append(getTo().index())
           .append("]");


      return build.toString();
    }
  }
}
