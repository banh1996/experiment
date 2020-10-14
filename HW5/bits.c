/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Points: 5
 */
int bitAnd(int x, int y) {
  return ~((~x)|(~y));
}

/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 10
 */
int getByte(int x, int n) {
  return (x >> (n<<3)) & 0xFF;
}

/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Points: 10
 */
int byteSwap(int x, int n, int m) {
    int n_mask = 0xFF << (n<<3);
    int m_mask = 0xFF << (m<<3);
    int n_temp = ((x >> (n<<3)) & 0xFF) << (m<<3);
    int m_temp = ((x >> (m<<3)) & 0xFF) << (n<<3);
    int x_temp = (~(n_mask | m_mask)) & x;
    return n_temp | m_temp | x_temp;
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 15
 */
int logicalShift(int x, int n) {
    int mask = x >> 31 << 31 >> n << 1;
    return ((x >> n) ^ mask);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 20
 */
int bitCount(int x) {
    int mask1 = 0x11 | (0x11 << 8);
    int mask2 = mask1 | (mask1 << 16);
    int sum = x & mask2;
    sum = sum + ((x >> 1) & mask2);
    sum = sum + ((x >> 2) & mask2);
    sum = sum + ((x >> 3) & mask2);
    sum = sum + (sum >> 16);
    mask1 = 0xF | (0xF << 8);
    sum = (sum & mask1) + ((sum >> 4) & mask1);
    return((sum + (sum >> 8)) & 0x3F);
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Points: 20
 */
int bang(int x) {
	int neg_x = ~x + 1;
	return((((x >> 31) & 0x01) | ((neg_x >> 31) & 0x01)) ^ 0x01);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 20
 */
int bitParity(int x) {
	x = x ^ (x >> 16);
	x = x ^ (x >> 8);
	x = x ^ (x >> 4);
	x = x ^ (x >> 2);
	x = x ^ (x >> 1);
	return (x&1);
}
