//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(~x&y)&~(x&~y));
 // return ~(x&y)&~(~x&~y);
}

/*
	德摩根定律
	~(P&Q) = (~P) | (~Q)
	~(P|Q) = (~P) & (~Q)
	1. 直接换算
	a^b = (~a & b) | (a & ~b) = ~(~(~a & b) & ~(a & ~b))

	2 .同或的非 a XNOR b = ~((a & b) | (~a & ~b))
	a^b = ((a & b) | (~a & ~b)) = ~(a & b) & ~(~a & ~b)
*/

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return !(x^~(1<<31));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
   int a = 0xAA;
  int b = (a << 8) + a; //0xAA AA
  int c = (b << 8) + a; //0xAA AA AA
  int d = (c << 8) + a; //0xAA AA AA AA
  return !((x & d)^d);
}
/* 
	十六进制A用二进制表示：1010
	x&0 = 0, x | 0 = x。
*/

/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
   return (~x+1);
}
//	补码+1

//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
   return(!((x+~48+1)>>31))&!!((x+~58+1)>>31);
}
/*
	0x30 = 48, 0x39 = 57. (进制转换)
	x - 48 不为负同时x - 58为负。
*/

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	return ((!x+~1+1)&y)|((~!x+1)&z);
}
/*
	!逻辑取反，～按位取反。
	将x转换为全0或者全1。(取0,-1)
	x=0时，!x = 1，~!x = -2。
	x!=0时，!x = 0, ~!x = -1。
	(A & y)|(B & z), x = 0时，A = 0, B = -1; x != 0时，A = -1, B = 0;
	A = !x - 1, B = ~!x + 1。
*/
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int xs = ((x>>31)&1);
	int ys = ((y>>31)&1);
	return (xs&!ys)|(!(xs^ys)&(!(x^y)|(x+~y+1>>31)&1));
}
/*
	1. 同号时，x - y <= 0 返回1， 否则返回0。
	2. 异号时，x < 0 返回1， 否则返回0。（都是返回x的符号位 xs & ! ys）
	先判断是否同号:!(xs^xy)，是同号则看&的另一边，否则返回0。
	判断x-y<=0是否成立,即x-y的符号位是否为1，为1则返回1，否则返回0。
	x-y<0:x-y = x+~y+1, 符号位(x+~y+1>>31)&1。
 	x=y: !(x^y)
*/
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	 return ~((x|(~x+1))>>31)&1;
}
/*
	实现逻辑取反运算符。
	x!=0, 返回 0。
	x=0, 返回 1。
	利用补码：-x = ~x + 1。
	x!=0, x &-x 符号位为 0, x | -x 符号位为 1; 
	x=0, x & -x 符号位为 0, x | -x 符号位为 0。
	
*/
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
		int sign = x >> 31;
		x = (sign&~x)|(~sign&x);
/*
	去除符号位
	~!非零 = ffffffff，~!0 = fffffffe
	x < 0, x >> 31 = ffffffff
	x > 0, x >> 31 = 0
	x > 0 不变，x < 0则按位取反
*/
	int h16,h8,h4,h2,h1,y;
	
	y = x>>16; // 二分法，32位先从中间16开始判断
	h16 = !!y<<4; // 如果左边16位存在1，则!!y = 1，h16 = 16；如果没有则!!y = 0, h16 = 0。
	x = x>>h16; // 如果左边存在1，则x右移16位(因为左边16位有，所以右边不用看了)；如果左边没有，则不动。
	
	y = x>>8;
	h8 = !!y<<3;
	x = x>>h8;
	
	y = x>>4;
	h4 = !!y<<2;
	x = x>>h4;
	
	y = x>>2;
	h2 = !!y<<1;
	x = x>>h2;
	
	y = x>>1;
	h1 = !!y<<0;
	x = x>>h1;
	
	return h16+h8+h4+h2+h1+1+x;

}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
 int exp = (uf&0x7f800000)>>23;
  int sign = uf&(1<<31);
  if(exp==0) return uf<<1|sign;  
  if(exp==255) return uf;
  exp++;
  if(exp==255) return 0x7f800000|sign;
  return (exp<<23)|(uf&0x807fffff);
}

/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	int s = uf>>31;
	int exp = (uf>>23)&0xff;
	int frac = uf&0x007fffff;
	if(exp<0x7f){
		return 0;
	}else if(exp>157){
		return 0x80000000;
	}else{
		int abs;
		if(exp - 150>0){
			abs = 0x00800000 + frac<<exp - 150;
		}else{
			abs = 0x00800000 + frac>>150 - exp;
		}
		if(s){
			return -abs;
		}else{
			return abs;
		}
	}

}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	 int INF = 0xff<<23;
  int exp = x + 127;
  if(exp <= 0) return 0;
  if(exp >= 255) return INF;
  return exp << 23;

}

