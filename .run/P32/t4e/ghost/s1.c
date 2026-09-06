#include "common.h"
extern u8 tab[]; extern s32 out[]; extern s32 g;
void s1(u8 *src, s32 n) {
    s32 b2 = src[0]; s32 i; u16 vbase; u32 vol; s32 pan;
    for (i = 0; i < n; i++) {
        vbase = b2 * 0x100;
        if (src[i] == 0) continue;
        pan = src[i + 1];
        vol = vbase;
        if (pan >= 0x41) vol = vbase + (pan - 0x40) * tab[i] * 4;
        else if (pan < 0x40) vol = vbase - (0x40 - pan) * tab[i + 1] * 4;
        vol -= tab[i + 2];
        out[i] = (u16)vol;
        if (g == 2) out[i + 1] = 0;
    }
}
