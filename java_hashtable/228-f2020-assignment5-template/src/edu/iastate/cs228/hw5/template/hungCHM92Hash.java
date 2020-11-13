publichungCHM92Hash
  /*
   * To reduce space usage, remove the key list if it is not needed. The
   * list is not needed for hash table operation. If you hash a value
   * which is not in the table (which you shouldn't), the only way to
   * detect the miss is to compare against the corresponding table index.
   */




  /**
   * Determines the hash code of the given string, which is equal to its
   * index in the key list.
   * Precondition: the given string is within the key list.
   * 
   * @param key
   *   the string for which to calculate a hash
   * @return
   *   the hash code of the given string
   */
  public static int hash(String key) {
    int i, u, v;

    for (u = v = i = 0; i < key.length(); ++i) {
      u = (u + TABLE_1[i % 8][key.charAt(i) % 64])
            % 25;
      v = ((v + TABLE_2[i % 8][key.charAt(i) % 64])
            % 25);
    }

    return (G[u] + G[v]) % 12;
  }

  /*
   * Example main method to test the hash function. Every key should hash
   * to its own index. An error message will be printed if this doesn't
   * hold.
   * 
   * Uncomment to use.
   */
  /*
  public static void main(String[] args) {
    for (int i = 0; i < KEY_LIST.length; ++i) {
      int h = hash(KEY_LIST[i]);
      if (h != i) {
        System.err.printf("Error while hashing \"%s\": expected %d but was %d%n", KEY_LIST[i], i, h);
      }
    }
  }
  */
