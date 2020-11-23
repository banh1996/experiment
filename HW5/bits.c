/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Points: 5
 */
int bitAnd(int x, int y) {
    /* Applied DeMorgan's Law
     * x&y = not ( not x | not y)
     */
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
    /* n<<3 = n*8 (8 bits per byte)
     * x is arithmetically shifted right to n*8
     * Then and with mask 0xFF to return only the least significant byte, byte n.
     */
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
    /*
     * example: x=0x12345678, n=1, m=3
     */
    int n_mask = 0xFF << (n<<3); //set mask at byte n, n_mask=0x0000FF00
    int m_mask = 0xFF << (m<<3); //set mask at byte mn m_mask=0xFF000000
    int n_temp = ((x >> (n<<3)) & 0xFF) << (m<<3); //move byte n to the least significant byte position, and with mask 0xFF, then move back to the byte m position, n_temp=0x56000000
    int m_temp = ((x >> (m<<3)) & 0xFF) << (n<<3); //move byte m to the least significant byte position, and with mask 0xFF, then move back to the byte n position, m_temp=0x00001200
    int x_temp = (~(n_mask | m_mask)) & x; //keep the remaining byte other than m and n, x_temp=0x00340078
    return n_temp | m_temp | x_temp; // 0x56000000|0x00001200|0x00340078=0x56341278
}

/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 15
 */
int logicalShift(int x, int n) {
    /* with x=0x87654321, the most significant bit is 1, then x>>4 is 0xf8765432, we need a mask to remove the f.
     * x >> 31 = 1111 1111 1111 1111 1111 1111 1111 1111
     * x >> 31 << 31 = 1000 0000 0000 0000 0000 0000 0000 0000
     * mask = x >> 31 << 31 >> 4 << 1 = 1111 0000 0000 0000 0000 0000 0000 0000
     * then result is (x>>n)&(~mask) = (x>>n)^mask
     */
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
    int mask1 = 0x11 | (0x11 << 8); //to set mask1 = 0001 0001 0001 0001
    int mask2 = mask1 | (mask1 << 16); //to set mask2 = 0001 0001 0001 0001 0001 0001 0001 0001  
    int sum = x & mask2; //compute the number of bit 1 within the first four bits
    sum = sum + ((x >> 1) & mask2);
    sum = sum + ((x >> 2) & mask2);
    sum = sum + ((x >> 3) & mask2);//now, each nibble(4 bit) of sum represents the total number of bit 1 per nibble of x
    //supposed sum = byte3_byte2_byte1_byte0, set least word of sum = (byte3+byte1)_(byte2+byte0)
    sum = sum + (sum >> 16);
    mask1 = 0xF | (0xF << 8);//to set mask1 = 0x0F0F
    sum = (sum & mask1) + ((sum >> 4) & mask1);//now, supposed sum=nibble3_nibble2_nibble1_nibble0, set sum = 0_(nibble3+nibble1)_0_(nibble2+nibble0)_0, remember sum of 2 nibble is a byte
    return((sum + (sum >> 8)) & 0x3F);//sum = byte2+byte0
}

/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Points: 20
 */
int bang(int x) {
    // set the logical negative value of x
	int neg_x = ~x + 1;

    /* if x!=0, then the most significant bit of either x or -x will be 1
     * XOR the sign bit of x/-x with mask 0x01 = !
     */
	return((((x>>31) & 0x01) | ((neg_x>>31) & 0x01)) ^ 0x01);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Points: 20
 */
int bitParity(int x) {
    /* XOR all the bits of the input number and putting it at the LSB,
     * hence gives 1 if there are odd number of bit 1
     */
	x = x ^ (x>>16);
	x = x ^ (x>>8);//let take example at here, x = x7 x6 x5 x4 x3 x2 x1 x0
	x = x ^ (x>>4);
	x = x ^ (x>>2);
	x = x ^ (x>>1);//now, at the LSB of x = x6^x2^x4^x0^x7^x3^x5^x1

	return (x&1);
}
