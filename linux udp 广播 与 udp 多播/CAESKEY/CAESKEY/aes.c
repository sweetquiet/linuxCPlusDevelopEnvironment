/*
 ---------------------------------------------------------------------------
 Copyright (c) 1998-2008, Brian Gladman, Worcester, UK. All rights reserved.

 LICENSE TERMS

 The redistribution and use of this software (with or without changes)
 is allowed without the payment of fees or royalties provided that:

  1. source code distributions include the above copyright notice, this
	 list of conditions and the following disclaimer;

  2. binary distributions include the above copyright notice, this list
	 of conditions and the following disclaimer in their documentation;

  3. the name of the copyright holder is not used to endorse products
	 built using this software without specific written permission.

 DISCLAIMER

 This software is provided 'as is' with no explicit or implied warranties
 in respect of its properties, including, but not limited to, correctness
 and/or fitness for purpose.
 ---------------------------------------------------------------------------
 Issue 09/09/2006

 This is an AES implementation that uses only 8-bit byte operations on the
 cipher state (there are options to use 32-bit types if available).

 The combination of mix columns and byte substitution used here is based on
 that developed by Karl Malbrain. His contribution is acknowledged.
 */

/* define if you have a fast memcpy function on your system */

#include "aes.h"
#include "SuanFa.h"

#if defined( AES_ENC_PREKEYED ) || defined( AES_DEC_PREKEYED )

/*  Set the cipher key for the pre-keyed version */

return_type aes_set_key( const unsigned char key[], length_type keylen, aes_context ctx[1] )
{
	uint_8t cc, rc, hi;

	switch( keylen )
	{
	case 16:
	case 24:
	case 32:
		break;
	default:
		ctx->rnd = 0;
		return -1;
	}
	block_copy_nn(ctx->ksch, key, keylen);
	hi = (keylen + 28) << 2;
	ctx->rnd = (hi >> 4) - 1;
	for( cc = keylen, rc = 1; cc < hi; cc += 4 )
	{   uint_8t tt, t0, t1, t2, t3;

		t0 = ctx->ksch[cc - 4];
		t1 = ctx->ksch[cc - 3];
		t2 = ctx->ksch[cc - 2];
		t3 = ctx->ksch[cc - 1];
		if( cc % keylen == 0 )
		{
			tt = t0;
			t0 = s_box(t1) ^ rc;
			t1 = s_box(t2);
			t2 = s_box(t3);
			t3 = s_box(tt);
			rc = f2(rc);
		}
		else if( keylen > 24 && cc % keylen == 16 )
		{
			t0 = s_box(t0);
			t1 = s_box(t1);
			t2 = s_box(t2);
			t3 = s_box(t3);
		}
		tt = cc - keylen;
		ctx->ksch[cc + 0] = ctx->ksch[tt + 0] ^ t0;
		ctx->ksch[cc + 1] = ctx->ksch[tt + 1] ^ t1;
		ctx->ksch[cc + 2] = ctx->ksch[tt + 2] ^ t2;
		ctx->ksch[cc + 3] = ctx->ksch[tt + 3] ^ t3;
	}
	return 0;
}

#endif

#if defined( AES_ENC_PREKEYED )

/*  Encrypt a single block of 16 bytes */

return_type aes_encrypt( const unsigned char in[N_BLOCK], unsigned char  out[N_BLOCK], const aes_context ctx[1] )
{
	if( ctx->rnd )
	{
		uint_8t s1[N_BLOCK], r;
		copy_and_key( s1, in, ctx->ksch );

		for( r = 1 ; r < ctx->rnd ; ++r )
#if defined( VERSION_1 )
		{
			mix_sub_columns( s1 );
			add_round_key( s1, ctx->ksch + r * N_BLOCK);
		}
#else
		{   uint_8t s2[N_BLOCK];
			mix_sub_columns( s2, s1 );
			copy_and_key( s1, s2, ctx->ksch + r * N_BLOCK);
		}
#endif
		shift_sub_rows( s1 );
		copy_and_key( out, s1, ctx->ksch + r * N_BLOCK );
	}
	else
		return -1;
	return 0;
}

/* CBC encrypt a number of blocks (input and return an IV) */

return_type aes_cbc_encrypt( const unsigned char *in, unsigned char *out,
						 int n_block, unsigned char iv[N_BLOCK], const aes_context ctx[1] )
{

	while(n_block--)
	{
		xor_block(iv, in);
		if(aes_encrypt(iv, iv, ctx) != EXIT_SUCCESS)
			return EXIT_FAILURE;
		//memcpy(out, iv, N_BLOCK);
		block_copy(out, iv);
		in += N_BLOCK;
		out += N_BLOCK;
	}
	return EXIT_SUCCESS;
}

#endif

#if defined( AES_DEC_PREKEYED )

/*  Decrypt a single block of 16 bytes */

return_type aes_decrypt( const unsigned char in[N_BLOCK], unsigned char out[N_BLOCK], const aes_context ctx[1] )
{
	if( ctx->rnd )
	{
		uint_8t s1[N_BLOCK], r;
		copy_and_key( s1, in, ctx->ksch + ctx->rnd * N_BLOCK );
		inv_shift_sub_rows( s1 );

		for( r = ctx->rnd ; --r ; )
#if defined( VERSION_1 )
		{
			add_round_key( s1, ctx->ksch + r * N_BLOCK );
			inv_mix_sub_columns( s1 );
		}
#else
		{   uint_8t s2[N_BLOCK];
			copy_and_key( s2, s1, ctx->ksch + r * N_BLOCK );
			inv_mix_sub_columns( s1, s2 );
		}
#endif
		copy_and_key( out, s1, ctx->ksch );
	}
	else
		return -1;
	return 0;
}

/* CBC decrypt a number of blocks (input and return an IV) */

return_type aes_cbc_decrypt( const unsigned char *in, unsigned char *out,
						 int n_block, unsigned char iv[N_BLOCK], const aes_context ctx[1] )
{
	while(n_block--)
	{   uint_8t tmp[N_BLOCK];

		//memcpy(tmp, in, N_BLOCK);
		block_copy(tmp, in);
		if(aes_decrypt(in, out, ctx) != EXIT_SUCCESS)
			return EXIT_FAILURE;
		xor_block(out, iv);
		//memcpy(iv, tmp, N_BLOCK);
		block_copy(iv, tmp);
		in += N_BLOCK;
		out += N_BLOCK;
	}
	return EXIT_SUCCESS;
}

#endif

#if defined( AES_ENC_128_OTFK )

/*  The 'on the fly' encryption key update for for 128 bit keys */

static void update_encrypt_key_128( uint_8t k[N_BLOCK], uint_8t *rc )
{   uint_8t cc;

	k[0] ^= s_box(k[13]) ^ *rc;
	k[1] ^= s_box(k[14]);
	k[2] ^= s_box(k[15]);
	k[3] ^= s_box(k[12]);
	*rc = f2( *rc );

	for(cc = 4; cc < 16; cc += 4 )
	{
		k[cc + 0] ^= k[cc - 4];
		k[cc + 1] ^= k[cc - 3];
		k[cc + 2] ^= k[cc - 2];
		k[cc + 3] ^= k[cc - 1];
	}
}

/*  Encrypt a single block of 16 bytes with 'on the fly' 128 bit keying */

void aes_encrypt_128( const unsigned char in[N_BLOCK], unsigned char out[N_BLOCK],
					 const unsigned char key[N_BLOCK], unsigned char o_key[N_BLOCK] )
{   uint_8t s1[N_BLOCK], r, rc = 1;

	if(o_key != key)
		block_copy( o_key, key );
	copy_and_key( s1, in, o_key );

	for( r = 1 ; r < 10 ; ++r )
#if defined( VERSION_1 )
	{
		mix_sub_columns( s1 );
		update_encrypt_key_128( o_key, &rc );
		add_round_key( s1, o_key );
	}
#else
	{   uint_8t s2[N_BLOCK];
		mix_sub_columns( s2, s1 );
		update_encrypt_key_128( o_key, &rc );
		copy_and_key( s1, s2, o_key );
	}
#endif

	shift_sub_rows( s1 );
	update_encrypt_key_128( o_key, &rc );
	copy_and_key( out, s1, o_key );
}

#endif

#if defined( AES_DEC_128_OTFK )

/*  The 'on the fly' decryption key update for for 128 bit keys */

static void update_decrypt_key_128( uint_8t k[N_BLOCK], uint_8t *rc )
{   uint_8t cc;

	for( cc = 12; cc > 0; cc -= 4 )
	{
		k[cc + 0] ^= k[cc - 4];
		k[cc + 1] ^= k[cc - 3];
		k[cc + 2] ^= k[cc - 2];
		k[cc + 3] ^= k[cc - 1];
	}
	*rc = d2(*rc);
	k[0] ^= s_box(k[13]) ^ *rc;
	k[1] ^= s_box(k[14]);
	k[2] ^= s_box(k[15]);
	k[3] ^= s_box(k[12]);
}

/*  Decrypt a single block of 16 bytes with 'on the fly' 128 bit keying */

void aes_decrypt_128( const unsigned char in[N_BLOCK], unsigned char out[N_BLOCK],
					  const unsigned char key[N_BLOCK], unsigned char o_key[N_BLOCK] )
{
	uint_8t s1[N_BLOCK], r, rc = 0x6c;
	if(o_key != key)
		block_copy( o_key, key );

	copy_and_key( s1, in, o_key );
	inv_shift_sub_rows( s1 );

	for( r = 10 ; --r ; )
#if defined( VERSION_1 )
	{
		update_decrypt_key_128( o_key, &rc );
		add_round_key( s1, o_key );
		inv_mix_sub_columns( s1 );
	}
#else
	{	uint_8t s2[N_BLOCK];
		update_decrypt_key_128( o_key, &rc );
		copy_and_key( s2, s1, o_key );
		inv_mix_sub_columns( s1, s2 );
	}
#endif
	update_decrypt_key_128( o_key, &rc );
	copy_and_key( out, s1, o_key );
}

#endif

#if defined( AES_ENC_256_OTFK )

/*  The 'on the fly' encryption key update for for 256 bit keys */

static void update_encrypt_key_256( uint_8t k[2 * N_BLOCK], uint_8t *rc )
{   uint_8t cc;

	k[0] ^= s_box(k[29]) ^ *rc;
	k[1] ^= s_box(k[30]);
	k[2] ^= s_box(k[31]);
	k[3] ^= s_box(k[28]);
	*rc = f2( *rc );

	for(cc = 4; cc < 16; cc += 4)
	{
		k[cc + 0] ^= k[cc - 4];
		k[cc + 1] ^= k[cc - 3];
		k[cc + 2] ^= k[cc - 2];
		k[cc + 3] ^= k[cc - 1];
	}

	k[16] ^= s_box(k[12]);
	k[17] ^= s_box(k[13]);
	k[18] ^= s_box(k[14]);
	k[19] ^= s_box(k[15]);

	for( cc = 20; cc < 32; cc += 4 )
	{
		k[cc + 0] ^= k[cc - 4];
		k[cc + 1] ^= k[cc - 3];
		k[cc + 2] ^= k[cc - 2];
		k[cc + 3] ^= k[cc - 1];
	}
}

/*  Encrypt a single block of 16 bytes with 'on the fly' 256 bit keying */

void aes_encrypt_256( const unsigned char in[N_BLOCK], unsigned char out[N_BLOCK],
					  const unsigned char key[2 * N_BLOCK], unsigned char o_key[2 * N_BLOCK] )
{
	uint_8t s1[N_BLOCK], r, rc = 1;
	if(o_key != key)
	{
		block_copy( o_key, key );
		block_copy( o_key + 16, key + 16 );
	}
	copy_and_key( s1, in, o_key );

	for( r = 1 ; r < 14 ; ++r )
#if defined( VERSION_1 )
	{
		mix_sub_columns(s1);
		if( r & 1 )
			add_round_key( s1, o_key + 16 );
		else
		{
			update_encrypt_key_256( o_key, &rc );
			add_round_key( s1, o_key );
		}
	}
#else
	{   uint_8t s2[N_BLOCK];
		mix_sub_columns( s2, s1 );
		if( r & 1 )
			copy_and_key( s1, s2, o_key + 16 );
		else
		{
			update_encrypt_key_256( o_key, &rc );
			copy_and_key( s1, s2, o_key );
		}
	}
#endif

	shift_sub_rows( s1 );
	update_encrypt_key_256( o_key, &rc );
	copy_and_key( out, s1, o_key );
}

#endif

#if defined( AES_DEC_256_OTFK )

/*  The 'on the fly' encryption key update for for 256 bit keys */

static void update_decrypt_key_256( uint_8t k[2 * N_BLOCK], uint_8t *rc )
{   uint_8t cc;

	for(cc = 28; cc > 16; cc -= 4)
	{
		k[cc + 0] ^= k[cc - 4];
		k[cc + 1] ^= k[cc - 3];
		k[cc + 2] ^= k[cc - 2];
		k[cc + 3] ^= k[cc - 1];
	}

	k[16] ^= s_box(k[12]);
	k[17] ^= s_box(k[13]);
	k[18] ^= s_box(k[14]);
	k[19] ^= s_box(k[15]);

	for(cc = 12; cc > 0; cc -= 4)
	{
		k[cc + 0] ^= k[cc - 4];
		k[cc + 1] ^= k[cc - 3];
		k[cc + 2] ^= k[cc - 2];
		k[cc + 3] ^= k[cc - 1];
	}

	*rc = d2(*rc);
	k[0] ^= s_box(k[29]) ^ *rc;
	k[1] ^= s_box(k[30]);
	k[2] ^= s_box(k[31]);
	k[3] ^= s_box(k[28]);
}

/*  Decrypt a single block of 16 bytes with 'on the fly'
	256 bit keying
*/
void aes_decrypt_256( const unsigned char in[N_BLOCK], unsigned char out[N_BLOCK],
					  const unsigned char key[2 * N_BLOCK], unsigned char o_key[2 * N_BLOCK] )
{
	uint_8t s1[N_BLOCK], r, rc = 0x80;

	if(o_key != key)
	{
		block_copy( o_key, key );
		block_copy( o_key + 16, key + 16 );
	}

	copy_and_key( s1, in, o_key );
	inv_shift_sub_rows( s1 );

	for( r = 14 ; --r ; )
#if defined( VERSION_1 )
	{
		if( ( r & 1 ) )
		{
			update_decrypt_key_256( o_key, &rc );
			add_round_key( s1, o_key + 16 );
		}
		else
			add_round_key( s1, o_key );
		inv_mix_sub_columns( s1 );
	}
#else
	{   uint_8t s2[N_BLOCK];
		if( ( r & 1 ) )
		{
			update_decrypt_key_256( o_key, &rc );
			copy_and_key( s2, s1, o_key + 16 );
		}
		else
			copy_and_key( s2, s1, o_key );
		inv_mix_sub_columns( s1, s2 );
	}
#endif
	copy_and_key( out, s1, o_key );
}

#endif
