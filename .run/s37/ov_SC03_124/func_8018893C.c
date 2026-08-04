/* func_8018893C — twin of the byte-matched func_8018BCD4 in ov_SC03_001/ov_SC03_001_jr_8017AE2C.c
 * (family of 4: this fn + ov_SC04_018/func_80189214 + ov_SC04_019/func_80189214 +
 * ov_SC05_017/func_80188F14; all normalize byte-identical to this shape). Only the two
 * overlay-local data symbols differ (D_801BC522/D_801BC536 here vs D_801C11BA/D_801C11CE
 * there). Caller in this TU (func_801880E0) already declares the matching prototype:
 *   extern s32 *func_8018893C(s32 *, void *, s32, void *, s32);
 */

extern s32 *func_8018893C(s32 *, void *, s32, void *, s32);

s32 *func_8018893C(out, src, idx, w, col)
    s32 *out;
    void *src;
    s16 idx;
    void *w;
    s32 col;
{
    extern short D_800B9A02;                /* TU-visible spelling (file scope) */
    extern s16 func_8014168C(s16 a0);
    extern u16 D_8011511A;
    extern u16 D_80115116;
    extern u8  D_80115138[];
    extern u8  D_80115140[];
    extern u8  D_80115148[];
    extern u8  D_80115158[];
    extern u16 D_801BC522;
    extern u16 D_801BC536;

    typedef struct {
        u32 *ot;                            /* 0x00 */
        u32 pad[4];                         /* 0x04..0x13 -> 0x14 stride */
    } Env_8018893C;
    extern Env_8018893C D_800AE7BC[];

    typedef struct { u32 addr : 24; u32 len : 8; } PTag_8018893C;

    /* §37 /s-DEP LATTICE: this store MUST be MEM_IN_STRUCT_P. `out[0] = k` folds `out + 0`
     * away and expands as a NON-/s mem, which keeps the true_dependence edge to the incoming
     * 5th-arg slot and pins `lw $v1,0x38($sp)` after it. The target has the arg load AFTER
     * the out[0] store, i.e. the edge must be DROPPED — sched.c's drop clause needs the store
     * /s + varying and the load non-/s + fixed-address. A COMPONENT_REF at offset 0 supplies
     * the /s. */
    typedef struct { u32 w; } W_8018893C;

    s32 c;
    s16 t;
    u16 *q;
    s32 m;
    volatile u16 *pbh;

    c = D_80115138[idx];

    ((W_8018893C *)out)->w = 0x04000000;
    *((u8 *)out + 0xC) = 0x30;
    *((u8 *)out + 0xD) = 0x48;
    *(s16 *)((u8 *)out + 0xE) = 0x4056;
    out[1] = col | 0x64000000;

    if (c < 10) {
        /* §135 idiom 9/T3: the fleet decl returns s16; cast at the CALL so the return feeds
         * `sll $v0,$v0,1` with no `andi`/re-extend. */
        t = ((s32 (*)(s16)) func_8014168C)(idx) * 2;
    } else {
        t = (D_80115148[idx * 2] - D_80115140[idx]) * 2;
    }

    q = (u16 *)(t * 2 + (s32)src);
    pbh = (volatile u16 *)&D_800B9A02;
    *(s16 *)((u8 *)out + 0x8) = q[0] - 8;
    *(s16 *)((u8 *)out + 0xA) = q[1];
    *(s16 *)((u8 *)out + 0x12) = 8;
    *(s16 *)((u8 *)out + 0x10) = 8;

    /* §36 BITFIELD STORE = THE MASK-ORDER DECOUPLER. The head materializes 0x00FFFFFF
     * (lui+ori) BEFORE 0xFF000000 (lui) while the body ANDs the dest first. `volatile` on the
     * index read is what keeps the SECOND *pbh load alive (a plain read cse-folds and the
     * fn loses 5 ins). */
    ((PTag_8018893C *)out)->addr =
        ((PTag_8018893C *)(D_800AE7BC[*pbh].ot + 2))->addr;
    ((PTag_8018893C *)(D_800AE7BC[*pbh].ot + 2))->addr = (u32)out;

    out += 5;
    if (c < 10) {
        return out;
    }

    m = D_8011511A;
    if (m == idx) {
        if ((D_80115116 & 8) != 0) {
            s16 j;
            s32 k;
            s16 y;
            s16 eight;
            u16 *pb;
            /* §137/§36: m24 is a 2-insn constant, but the natural allocno order puts j/k ahead
             * of it and rotates $a2/$a3/$t0. Pinning m24 alone restores the whole rotation. */
            register u32 m24 __asm__("$6");
            u32 mhi;
            s32 vsum;

            j = 0;
            k = m;
            eight = 8;
            pb = (u16 *)&D_800B9A02;
            m24 = 0xFFFFFF;
            mhi = 0xFF000000;
            /* NOTE: the loop deliberately has NO source pointer of its own. gcc's combine_givs
             * folds every `out + K` reference into ONE address giv based at out+0x12; adding a
             * `u8 *p = (u8*)out + 0x12` biv makes `*(s16*)p` use the biv directly, which
             * survives as a SECOND register (the +1-instruction LENGTH-DRIFT). The giv's base
             * is the LAST such reference in source order — hence the +8 (`vsum`) store sits
             * before the 0x10/0x12 stores here even though the scheduler sinks it back. */
            for (; j < 2; j++) {
                if (j == 0) {
                    if (D_80115140[k] == 0) {
                        continue;
                    }
                    *((u8 *)out + 0xD) = 0x30;
                    y = D_801BC522 - 2;
                } else {
                    s32 k2 = k * 2;
                    if ((((s8 *)D_80115158)[k2] - ((s8 *)D_80115140)[k]) < 7) {
                        continue;
                    }
                    *((u8 *)out + 0xD) = 0x38;
                    y = D_801BC536 + 1;
                }
                *(s16 *)((u8 *)out + 0xA) = y;
                __asm__("" ::: "memory");   /* keeps the y store ahead of the 0x64808080 pair */
                *(u32 *)out = 0x04000000;
                *((u8 *)out + 0xC) = 0x78;
                *(u32 *)((u8 *)out + 0x4) = 0x64808080;
                *(s16 *)((u8 *)out + 0xE) = 0x4056;
                vsum = *(s32 *)((u8 *)w + 8) + *(s32 *)((u8 *)w + 0xC) - 0xC;
                *(s16 *)((u8 *)out + 0x8) = vsum;
                *(s16 *)((u8 *)out + 0x10) = eight;
                *(s16 *)((u8 *)out + 0x12) = eight;
                *(u32 *)out = ((*(u32 *)out) & mhi) | (D_800AE7BC[*pb].ot[2] & m24);
                {
                    register u32 *op __asm__("$4");
                    op = D_800AE7BC[*pb].ot;
                    op[2] = (op[2] & mhi) | (((u32)out) & m24);
                }
                out += 5;
            }
        }
    }
    return out;
}
