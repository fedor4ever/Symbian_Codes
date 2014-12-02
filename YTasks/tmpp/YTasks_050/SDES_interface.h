/* Copyright (c) 2001 - 2003 , J.P. Silvennoinen. All rights reserved */

#ifndef __INTTESTFORMYDSA_H__
#define __INTTESTFORMYDSA_H__

#include <e32std.h>
#include <e32base.h>

class CMD5_Handler;

_LIT8(KeyStuffing, "ASDFGHJKLPOIUYTR");


typedef struct {
    TUint32 k0246[16], k1357[16];
    TUint32 eiv0, eiv1;
    TUint32 div0, div1;
} DESContext;

class CDESHandler : public CBase
    {
public:
	static CDESHandler* NewL(void);
    static CDESHandler* NewLC(void);
     ~CDESHandler();
 	void DES_encryptLC(TDes& aKey,  TDes& aData);
	void DES_decryptLC(TDes& aKey,  TDes& aData);
	void DES_encryptLC(TDes& aKey,  TDes8& aData);
	void DES_decryptLC(TDes& aKey,  TDes8& aData);
	void DES_encryptLC(TDes8& aKey, TDes8& aData);
	void DES_decryptLC(TDes8& aKey, TDes8& aData);
private:
	void ConstructL(void);
    CDESHandler();
	void DES_encryptLC(TUint8 *aKey,TUint8 *aData,TInt aLength);
	void DES_decryptLC(TUint8 *aKey,TUint8 *aData,TInt aLength);
	void des_key_setup(TUint32 key_msw, TUint32 key_lsw, DESContext * sched);
	void des_3cbc_encrypt(TUint8 *dest, const TUint8 *src,TUint len, DESContext * scheds);
    void des_3cbc_decrypt(TUint8 *dest, const TUint8 *src,TUint len, DESContext * scheds);
    void des_cbc_encrypt(TUint8 *dest, const TUint8 *src, TUint len, DESContext * sched);
   	void des_cbc_decrypt(TUint8 *dest, const TUint8 *src,TUint len, DESContext * sched);
    TUint32 bitsel(TUint32 * input, const TInt *bitnums, TInt size);
    void des_encipher(TUint32 * output, TUint32 L, TUint32 R, DESContext * sched);
	void des_decipher(TUint32 * output, TUint32 L, TUint32 R, DESContext * sched);
private:
	CMD5_Handler* iMD5_Handler;
    };
    
#define rotl28(x, c) ( ( (x << c) | (x >> (28-c)) ) & 0x0FFFFFFF)

#define GET_32BIT_MSB_FIRST(cp) \
  (((TUint32)(TUint8)(cp)[3]) | \
  ((TUint32)(TUint8)(cp)[2] << 8) | \
  ((TUint32)(TUint8)(cp)[1] << 16) | \
  ((TUint32)(TUint8)(cp)[0] << 24))
 
#define PUT_32BIT_MSB_FIRST(cp, value) do { \
  (cp)[3] = (value); \
  (cp)[2] = (value) >> 8; \
  (cp)[1] = (value) >> 16; \
  (cp)[0] = (value) >> 24; } while (0)
  
#define bitswap(L, R, n, mask) (\
    swap = mask & ( (R >> n) ^ L ), \
    R ^= swap << n, \
    L ^= swap)
    
/* Initial permutation */
#define IP(L, R) (\
    bitswap(R, L,  4, 0x0F0F0F0F), \
    bitswap(R, L, 16, 0x0000FFFF), \
    bitswap(L, R,  2, 0x33333333), \
    bitswap(L, R,  8, 0x00FF00FF), \
    bitswap(R, L,  1, 0x55555555))

/* Final permutation */
#define FP(L, R) (\
    bitswap(R, L,  1, 0x55555555), \
    bitswap(L, R,  8, 0x00FF00FF), \
    bitswap(L, R,  2, 0x33333333), \
    bitswap(R, L, 16, 0x0000FFFF), \
    bitswap(R, L,  4, 0x0F0F0F0F))
    
#define rotl(x, c) ( (x << c) | (x >> (32-c)) )

#define f(R, K0246, K1357) (\
    s0246 = R ^ K0246, \
    s1357 = R ^ K1357, \
    s0246 = rotl(s0246, 28), \
    SPboxes[0] [(s0246 >> 24) & 0x3F] | \
    SPboxes[1] [(s1357 >> 24) & 0x3F] | \
    SPboxes[2] [(s0246 >> 16) & 0x3F] | \
    SPboxes[3] [(s1357 >> 16) & 0x3F] | \
    SPboxes[4] [(s0246 >>  8) & 0x3F] | \
    SPboxes[5] [(s1357 >>  8) & 0x3F] | \
    SPboxes[6] [(s0246      ) & 0x3F] | \
    SPboxes[7] [(s1357      ) & 0x3F])
    
       
static const TUint32 SPboxes[8][64] = {
    {0x01010400, 0x00000000, 0x00010000, 0x01010404,
     0x01010004, 0x00010404, 0x00000004, 0x00010000,
     0x00000400, 0x01010400, 0x01010404, 0x00000400,
     0x01000404, 0x01010004, 0x01000000, 0x00000004,
     0x00000404, 0x01000400, 0x01000400, 0x00010400,
     0x00010400, 0x01010000, 0x01010000, 0x01000404,
     0x00010004, 0x01000004, 0x01000004, 0x00010004,
     0x00000000, 0x00000404, 0x00010404, 0x01000000,
     0x00010000, 0x01010404, 0x00000004, 0x01010000,
     0x01010400, 0x01000000, 0x01000000, 0x00000400,
     0x01010004, 0x00010000, 0x00010400, 0x01000004,
     0x00000400, 0x00000004, 0x01000404, 0x00010404,
     0x01010404, 0x00010004, 0x01010000, 0x01000404,
     0x01000004, 0x00000404, 0x00010404, 0x01010400,
     0x00000404, 0x01000400, 0x01000400, 0x00000000,
     0x00010004, 0x00010400, 0x00000000, 0x01010004L},

    {0x80108020, 0x80008000, 0x00008000, 0x00108020,
     0x00100000, 0x00000020, 0x80100020, 0x80008020,
     0x80000020, 0x80108020, 0x80108000, 0x80000000,
     0x80008000, 0x00100000, 0x00000020, 0x80100020,
     0x00108000, 0x00100020, 0x80008020, 0x00000000,
     0x80000000, 0x00008000, 0x00108020, 0x80100000,
     0x00100020, 0x80000020, 0x00000000, 0x00108000,
     0x00008020, 0x80108000, 0x80100000, 0x00008020,
     0x00000000, 0x00108020, 0x80100020, 0x00100000,
     0x80008020, 0x80100000, 0x80108000, 0x00008000,
     0x80100000, 0x80008000, 0x00000020, 0x80108020,
     0x00108020, 0x00000020, 0x00008000, 0x80000000,
     0x00008020, 0x80108000, 0x00100000, 0x80000020,
     0x00100020, 0x80008020, 0x80000020, 0x00100020,
     0x00108000, 0x00000000, 0x80008000, 0x00008020,
     0x80000000, 0x80100020, 0x80108020, 0x00108000L},

    {0x00000208, 0x08020200, 0x00000000, 0x08020008,
     0x08000200, 0x00000000, 0x00020208, 0x08000200,
     0x00020008, 0x08000008, 0x08000008, 0x00020000,
     0x08020208, 0x00020008, 0x08020000, 0x00000208,
     0x08000000, 0x00000008, 0x08020200, 0x00000200,
     0x00020200, 0x08020000, 0x08020008, 0x00020208,
     0x08000208, 0x00020200, 0x00020000, 0x08000208,
     0x00000008, 0x08020208, 0x00000200, 0x08000000,
     0x08020200, 0x08000000, 0x00020008, 0x00000208,
     0x00020000, 0x08020200, 0x08000200, 0x00000000,
     0x00000200, 0x00020008, 0x08020208, 0x08000200,
     0x08000008, 0x00000200, 0x00000000, 0x08020008,
     0x08000208, 0x00020000, 0x08000000, 0x08020208,
     0x00000008, 0x00020208, 0x00020200, 0x08000008,
     0x08020000, 0x08000208, 0x00000208, 0x08020000,
     0x00020208, 0x00000008, 0x08020008, 0x00020200L},

    {0x00802001, 0x00002081, 0x00002081, 0x00000080,
     0x00802080, 0x00800081, 0x00800001, 0x00002001,
     0x00000000, 0x00802000, 0x00802000, 0x00802081,
     0x00000081, 0x00000000, 0x00800080, 0x00800001,
     0x00000001, 0x00002000, 0x00800000, 0x00802001,
     0x00000080, 0x00800000, 0x00002001, 0x00002080,
     0x00800081, 0x00000001, 0x00002080, 0x00800080,
     0x00002000, 0x00802080, 0x00802081, 0x00000081,
     0x00800080, 0x00800001, 0x00802000, 0x00802081,
     0x00000081, 0x00000000, 0x00000000, 0x00802000,
     0x00002080, 0x00800080, 0x00800081, 0x00000001,
     0x00802001, 0x00002081, 0x00002081, 0x00000080,
     0x00802081, 0x00000081, 0x00000001, 0x00002000,
     0x00800001, 0x00002001, 0x00802080, 0x00800081,
     0x00002001, 0x00002080, 0x00800000, 0x00802001,
     0x00000080, 0x00800000, 0x00002000, 0x00802080L},

    {0x00000100, 0x02080100, 0x02080000, 0x42000100,
     0x00080000, 0x00000100, 0x40000000, 0x02080000,
     0x40080100, 0x00080000, 0x02000100, 0x40080100,
     0x42000100, 0x42080000, 0x00080100, 0x40000000,
     0x02000000, 0x40080000, 0x40080000, 0x00000000,
     0x40000100, 0x42080100, 0x42080100, 0x02000100,
     0x42080000, 0x40000100, 0x00000000, 0x42000000,
     0x02080100, 0x02000000, 0x42000000, 0x00080100,
     0x00080000, 0x42000100, 0x00000100, 0x02000000,
     0x40000000, 0x02080000, 0x42000100, 0x40080100,
     0x02000100, 0x40000000, 0x42080000, 0x02080100,
     0x40080100, 0x00000100, 0x02000000, 0x42080000,
     0x42080100, 0x00080100, 0x42000000, 0x42080100,
     0x02080000, 0x00000000, 0x40080000, 0x42000000,
     0x00080100, 0x02000100, 0x40000100, 0x00080000,
     0x00000000, 0x40080000, 0x02080100, 0x40000100L},

    {0x20000010, 0x20400000, 0x00004000, 0x20404010,
     0x20400000, 0x00000010, 0x20404010, 0x00400000,
     0x20004000, 0x00404010, 0x00400000, 0x20000010,
     0x00400010, 0x20004000, 0x20000000, 0x00004010,
     0x00000000, 0x00400010, 0x20004010, 0x00004000,
     0x00404000, 0x20004010, 0x00000010, 0x20400010,
     0x20400010, 0x00000000, 0x00404010, 0x20404000,
     0x00004010, 0x00404000, 0x20404000, 0x20000000,
     0x20004000, 0x00000010, 0x20400010, 0x00404000,
     0x20404010, 0x00400000, 0x00004010, 0x20000010,
     0x00400000, 0x20004000, 0x20000000, 0x00004010,
     0x20000010, 0x20404010, 0x00404000, 0x20400000,
     0x00404010, 0x20404000, 0x00000000, 0x20400010,
     0x00000010, 0x00004000, 0x20400000, 0x00404010,
     0x00004000, 0x00400010, 0x20004010, 0x00000000,
     0x20404000, 0x20000000, 0x00400010, 0x20004010L},

    {0x00200000, 0x04200002, 0x04000802, 0x00000000,
     0x00000800, 0x04000802, 0x00200802, 0x04200800,
     0x04200802, 0x00200000, 0x00000000, 0x04000002,
     0x00000002, 0x04000000, 0x04200002, 0x00000802,
     0x04000800, 0x00200802, 0x00200002, 0x04000800,
     0x04000002, 0x04200000, 0x04200800, 0x00200002,
     0x04200000, 0x00000800, 0x00000802, 0x04200802,
     0x00200800, 0x00000002, 0x04000000, 0x00200800,
     0x04000000, 0x00200800, 0x00200000, 0x04000802,
     0x04000802, 0x04200002, 0x04200002, 0x00000002,
     0x00200002, 0x04000000, 0x04000800, 0x00200000,
     0x04200800, 0x00000802, 0x00200802, 0x04200800,
     0x00000802, 0x04000002, 0x04200802, 0x04200000,
     0x00200800, 0x00000000, 0x00000002, 0x04200802,
     0x00000000, 0x00200802, 0x04200000, 0x00000800,
     0x04000002, 0x04000800, 0x00000800, 0x00200002L},

    {0x10001040, 0x00001000, 0x00040000, 0x10041040,
     0x10000000, 0x10001040, 0x00000040, 0x10000000,
     0x00040040, 0x10040000, 0x10041040, 0x00041000,
     0x10041000, 0x00041040, 0x00001000, 0x00000040,
     0x10040000, 0x10000040, 0x10001000, 0x00001040,
     0x00041000, 0x00040040, 0x10040040, 0x10041000,
     0x00001040, 0x00000000, 0x00000000, 0x10040040,
     0x10000040, 0x10001000, 0x00041040, 0x00040000,
     0x00041040, 0x00040000, 0x10041000, 0x00001000,
     0x00000040, 0x10040040, 0x00001000, 0x00041040,
     0x10001000, 0x00000040, 0x10000040, 0x10040000,
     0x10040040, 0x10000000, 0x00040000, 0x10001040,
     0x00000000, 0x10041040, 0x00040040, 0x10000040,
     0x10040000, 0x10001000, 0x10001040, 0x00000000,
     0x10041040, 0x00041000, 0x00041000, 0x00001040,
     0x00001040, 0x00040040, 0x10000000, 0x10041000L}
};    


#endif // __INTTESTFORMYDSA_H__
