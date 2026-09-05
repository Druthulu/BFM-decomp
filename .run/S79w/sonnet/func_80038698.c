typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef signed char s8; typedef short s16; typedef int s32; typedef float f32;
typedef unsigned long long u64; typedef long long s64; typedef double f64;
typedef s32 M2C_UNK; typedef s8 M2C_UNK8; typedef s16 M2C_UNK16; typedef s32 M2C_UNK32; typedef s64 M2C_UNK64;
#define NULL ((void*)0)
  
   
  
    
#define NULL ((void*)0)
s32 func_80038698(void *arg0) {
    register u8 *a3 asm("$7");
    register u32 a2 asm("$6");
    register u32 hi asm("$5");
    u16 v1;
    s32 a0;

    a3 = *(u8 **)(arg0);
    *(u8 **)(arg0) = a3 + 1;
    a2 = a3[0];
    *(u8 **)(arg0) = a3 + 2;
    a2 |= (a3[1] << 8);
    *(u8 **)(arg0) = a3 + 3;
    a2 |= (a3[2] << 16);
    *(u8 **)(arg0) = a3 + 4;
    a2 |= (a3[3] << 24);
    if (a2 != 0x6468544D) {
        return -1;
    }
    *(u8 **)(arg0) = a3 + 5;
    a2 = a3[4];
    *(u8 **)(arg0) = a3 + 6;
    a2 = (a2 << 8) | a3[5];
    *(u8 **)(arg0) = a3 + 7;
    a2 = (a2 << 8) | a3[6];
    *(u8 **)(arg0) = a3 + 8;
    hi = a3[8];
    a2 = (a2 << 8) | a3[7];
    {
        u16 v0 = (hi << 8) | a3[9];
        if (v0 != 0) {
            return -1;
        }
    }
    v1 = (a3[10] << 8) | a3[11];
    if ((s16)v1 != 1) {
        return -1;
    }
    a0 = (s16)((a3[12] << 8) | a3[13]);
    if (a0 & 0x8000) {
        return -1;
    }
    *(u16 *)((char *)(arg0) + 0x1E6) = a0 & 0x7FFF;
    *(u8 **)(arg0) += a2;
    return 0;
}
