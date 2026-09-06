#include "common.h"
extern u8 tab[]; extern s32 out[]; extern s32 g;
void r9(u8 *src, s32 n) {
    s32 b2 = src[0]; s32 i; s32 vbase; u32 vol; s32 pan;
    for (i = 0; i < n; i++) {
        if (src[i] == 0) continue;
        pan = src[i + 1];
        vol = b2 * 0x100;
        if (pan >= 0x41) vol = (b2 * 0x100) + (pan - 0x40) * tab[i] * 4;
        else if (pan < 0x40) vol = (b2 * 0x100) - (0x40 - pan) * tab[i + 1] * 4;
        vol -= tab[i + 2];
        out[i] = (u16)vol;
        if (g == 2) out[i + 1] = 0;
    }
}
