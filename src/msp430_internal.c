/* msp430_internal.h
 * Copyright (c) 2013 David Bender. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:

 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * */


enum {
	INTERNAL_2_POWER_COUNT = 16
	,INTERNAL_8_POWER_COUNT = 6
	,INTERNAL_10_POWER_COUNT = 5
	,INTERNAL_16_POWER_COUNT = 4


	,INTERNAL_MID_EXPONENT = 127

};

static const reprint_uint_t s_8_powers[INTERNAL_8_POWER_COUNT] = {
	 0x0001
	,0x0008
	,0x0040
	,0x0200
	,0x1000
	,0x8000
};

static const reprint_uint_t s_10_powers[INTERNAL_10_POWER_COUNT] = {
	1
	,10
	,100
	,1000
	,10000
};

static const reprint_uint_t s_16_powers[INTERNAL_16_POWER_COUNT] = {
	 0x0001
	,0x0010
	,0x0100
	,0x1000
};

static inline reprint_reg_t s_arch_calc_msb(reprint_uint_t v){
	/* Power of 2 base. Determine greatest 1 bit position.
	 * Shamelessly ripped from bit twiddling hacks:
	 * http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog
	 *
	 * */

	uint8_t r;
	uint8_t shift;
	r = (v > 0xFF) << 3; v >>= r;
	shift = (v > 0xF) << 2; v >>= shift; r |= shift;
	shift = (v > 0x3) << 1; v >>= shift; r |= shift;

	r |= (v >> 1);

	return r;
}

static inline reprint_reg_t s_arch_calc_r10_digits(reprint_uint_t v){
	unsigned tmp = INTERNAL_10_POWER_COUNT;
	while(tmp > 0){
		if(v >= s_10_powers[tmp - 1])
			break;
		--tmp;
	}
	return tmp;
}


/* NOTE expecting all our data types to be limited to 16 bits. */
static inline const void* s_arch_align_ptr(const void* p, size_t size){
	if(1 == size)
		return p;

	uintptr_t x = (uintptr_t)p;
	++x;
	x &= ~1;
	return (const void*)x;
}

