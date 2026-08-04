/* func_80181914 — byte-verified twin of func_8017D77C (src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c:4271),
 * found via §136e/S34 magic-word grep on the `AAA32294` instruction bytes (the
 * D_800AF630+0xA3AA far-offset lhu). func_8017D77C is the banked member of this
 * family; this body was derived by remapping its symbols:
 *   func_8017D77C -> func_80181914       D_801E6F58    -> D_801C12C0
 *   func_8017D9B8 -> func_80181B50       func_8017DAC4 -> func_80181C5C
 *   Ent_8017D6EC  -> Ent_80181914 (own function-suffixed typedef -- same 0x24-stride
 *                     shape as this TU's own Ent_8017D6EC_80181884 at TU:4633-4639,
 *                     given a fresh name/no shared tag so splicing this in below that
 *                     file-scope typedef can't hit the C89 duplicate-typedef error, S33).
 * func_80181C5C is already banked in THIS TU (defined further down as
 * `void func_80181C5C(void *arg0)`), matching the direct call below with no cast
 * needed. func_80181B50 has no declaration anywhere in this TU but its own
 * INCLUDE_ASM stub, so it is declared directly as `void (void *)` (no idiom-9 cast
 * needed, unlike the twin's func_8017D9B8 which was `void (void)`).
 */

extern u8 D_80078EB1;
extern u8 D_80078E78[];
extern u8 D_800AF630[];
extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80181B50(void *arg0);
extern void func_80181C5C(void *arg0);

typedef struct {
    u8  unk00[0x16];
    s16 unk16;
    u8  unk18[4];
    s32 unk1C;
    u8  unk20[4];
} Ent_80181914;

extern Ent_80181914 D_801C12C0[];

void func_80181914(s32 *arg0)
{
    u8 *m = D_800AF630;
    u8 *q = D_80078E78;
    Ent_80181914 *p;
    Ent_80181914 *r;
    s32 i;
    s32 j;
    s32 n;
    s32 h;
    s32 c;
    s32 e;

    if (D_80078EB1 >= 9) {
        n = 0;
        for (j = 0; j < 4; j++) {
            r = &D_801C12C0[j];
            if (r->unk1C == 0) {
                n++;
            }
        }
        if (n == 0) {
            func_8012AD44(arg0, 0);
            return;
        }
    }

    i = 0;
    do {
        p = (Ent_80181914 *)((s32)D_801C12C0 + i * 0x24);
        if (p->unk1C == 0) {
            if (*(s16 *)((s32)p + 0xC) > 0x400) {
                if (*(s32 *)((s32)p + 0x18) != 0) {
                    *(s32 *)((s32)p + 0x18) = *(s32 *)((s32)p + 0x18) - 1;
                } else {
                    *(s16 *)((s32)p + 0xC) = *(s16 *)((s32)p + 0xC) + 11;
                }
            } else {
                *(s16 *)((s32)p + 0xC) = *(s16 *)((s32)p + 0xC) + 11;
            }
            if (*(s16 *)((s32)p + 0xC) > 0x800) {
                *(s16 *)((s32)p + 0xC) = 0;
            }
            c = (func_8004787C(*(s16 *)((s32)p + 0xC)) / 64) & 0xFF;
            c = c | ((c << 16) | (c << 8));
            *(s32 *)((s32)p + 0x4) = c;
            c = (func_8004787C(*(s16 *)((s32)p + 0xC)) / 256) & 0xFF;
            c = c | ((c << 16) | (c << 8));
            *(s32 *)((s32)p + 0x8) = c;
            if ((*(u16 *)(m + 0xA3AA) & 1) == 0) {
                e = *(u16 *)((s32)p + 0xE) + 1;
                *(u16 *)((s32)p + 0xE) = e;
                if ((s16)e >= 0x40) {
                    *(s16 *)((s32)p + 0xE) = 0;
                }
            }
            h = *(s16 *)((s32)p + 0xC);
            if (h == 0) {
                p->unk1C = 1;
            } else if (h > 0x555) {
                if (*(s32 *)((s32)p + 0x20) == 0) {
                    *(s32 *)((s32)p + 0x20) = 1;
                    if (q[0x39] < 9) {
                        func_80181B50(p);
                    }
                }
            }
            func_80181C5C(p);
        }
        i++;
    } while (i < 4);
}
