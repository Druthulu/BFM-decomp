/* func_80140958 - ov_SC01_077 @ 0x80140958, 260 ins, -O2.
 *
 * STATUS: NEAR - 260/260 instructions, 10 mismatched (match_one --json:
 *   {"status":"near","closeness":10,"nins":260,"verdict":{"klass":"ADDRESSING","profile":"cse"}}).
 *
 * Canonical sig_hints decls are used VERBATIM. Everything else is derived from the asm:
 *   func_80140D68  - jal target, 5 args (5th at 0x10($sp)); ret is the new OT ptr
 *   D_80115143     - lbu %lo(D_80115143)
 *   D_8018793C[]   - Prim4, indexed by (s16)i (stride 4)
 *   D_80187E9C[] / D_80187EAC[]  - s16 tables, indexed by (D_80115116 & 7)
 *   D_801879BC / D_801879BE      - u16 scalars
 *   D_800AE7BC[]   - Env (u32 *ot; u32 pad[4]) 0x14 stride; the addPrim OT array
 *                    (same object resident.c calls Env_800D29F8)
 *
 * KEY FINDINGS (worth a cookbook entry):
 *  1. The 0x80115110 block is reached through THREE held base pointers, not through
 *     separate externs: $s4=&D_80115110, $s5=$s4+0xA, $s7=$s4+6 (and $s6=&D_801879BE).
 *     Separate externs can never produce `addiu $s5,$s4,0xA` (no %hi CSE across symbols),
 *     so the source must own real pointer variables.
 *  2. The `if (i < n) { <preheader assigns>; do {...} while (i < n); }` shape is what puts
 *     the base-pointer setup AFTER the loop-guard `beqz` (a plain `while` puts explicit
 *     assignments in the entry block instead, shifting the whole prologue).
 *  3. `t` must be `s16` and func_8014168C must be CALLED THROUGH an (s32(*)(s16)) cast:
 *     with the canonical `s16` return gcc emits `sll 16 / srl 15` instead of the target's
 *     single `sll $v0,$v0,1`, and the s16 truncation then lands at the AC8 merge point.
 *  4. `((s8 *)D_80115158)[k * 2]` materialises the address into a register (and LICM hoists
 *     it). Hoisting `k*2` into its own local (`s32 k2 = k * 2;`) restores the target's
 *     in-loop `lb $v0, D_80115158($v0)` form. (cookbook: computed index vs. plain reg index.)
 *  5. The SPRT biv must be anchored ONE ABOVE the highest field (ot+0x14, all-negative
 *     offsets) or gcc splits it into two bivs; it then re-anchors to ot+0x10 by itself.
 *
 * RESIDUAL (10 ins, all one root cause - contiguous idx 134..149):
 *   gcc constant-folds `m == 3` so `k = m` becomes `li $a3,3` and `m*4` becomes `li $t3,12`,
 *   where the target keeps `addu $a3,$v1,$zero` + `sll $t3,$v1,2`. Because $v1 then dies
 *   early, gcc also fills two delay slots (`li $v0,3`, `addiu $v1,$s3,1`) that the target
 *   leaves as nops. Writing `m == i` (or `m == c3`) defeats the fold but makes gcc coalesce
 *   j/k into the wrong pair ($a2 <-> $a3 swapped) - 16 mismatched instead of 10. Tried:
 *   pinning k/$a3, pinning j/$a2, pinning m/$v1, an "=r"/"0" opaque barrier on m,
 *   re-reading b[0], `m == i`, `m == c3`, `m == (s32)i`, volatile load. None reach 0.
 */
/* DRAFT-ONLY: Hw4/Prim4 come from engine_types.h in the real TU (via engine_core.h).
 * They are reproduced here ONLY so the standalone match_one compile has them.
 * DROP THESE TWO LINES WHEN BANKING. */
typedef struct { s16 x; s16 y; } Hw4;
typedef struct { u16 f0; s16 f2; } Prim4;

extern s16 func_8014168C(s16);

extern short D_800B9A02;
extern u16 D_80115110;
extern u8 D_80115140[];
extern s16 D_8011514E;
extern u8 D_80115158[];
extern Hw4 D_8011516A[];
extern Prim4 D_8018798C[];
extern Prim4 *D_80187A80[];

/* derived from asm */
extern u8    D_80115143;                 /* lbu %lo(D_80115143)   */
extern Prim4 D_8018793C[];               /* base + ((s16)i)*4     */
extern s16   D_80187E9C[];               /* lh  %lo + (f6&7)*2    */
extern s16   D_80187EAC[];               /* lh  %lo + (f6&7)*2    */
extern u16   D_801879BC;                 /* lhu %lo               */
extern u16   D_801879BE;                 /* lhu 0($s6) - held ptr */
/* jal target; 5 args, 5th on the stack at 0x10($sp) */
extern s32 *func_80140D68(s32 *, Prim4 *, s32, s32, s32);

s32 *func_80140958(ot, i, n)
s32 *ot;
s16 i;
s16 n;
{
    typedef struct {
        u32 *ot;
        u32 pad[4];
    } Env_80140958;
    extern Env_80140958 D_800AE7BC[];

    Prim4 *p;
    s16 t;
    s32 c3;
    /* three held bases into the 0x80115110 block ($s4 / $s5=+0xA / $s7=+6) */
    register u16 *a __asm__("$20");
    register u16 *b __asm__("$21");
    register u16 *c __asm__("$23");
    register u16 *e __asm__("$22");
    register u16 *pb __asm__("$10");
    register u32 m24 __asm__("$8");
    register u32 mhi __asm__("$9");
    register s32 eight __asm__("$2");

    if (i < n) {
        c3 = 3;
        a = &D_80115110;
        b = a + 5;
        c = a + 3;
        e = &D_801879BE;
        do {
        if (a[0] == 0 && a[1] != c3 && a[1] < 6) {
            if (i == a[5]) {
                ot = func_80140D68(ot, &D_8018793C[i], i, D_80187E9C[a[3] & 7], 0);
            }
        } else {
            p = D_80187A80[i];
            if (p != 0 && i == b[0] && i != 6) {
                if (i == 2 && *(s16 *)(b + 7) != 0) {
                    p = D_8018798C;
                }
                if (i != c3) {
                    t = ((s32 (*)(s16))func_8014168C)(i) * 2;
                } else {
                    t = (*(u8 *)&D_8011514E - D_80115143) * 2;
                }
                ot = func_80140D68(ot, p, i, D_80187EAC[c[0] & 7], t);
                if (i == 2 && *(s16 *)(c + 9) == 1 && *(s16 *)(c + 12) != 0) {
                    ot = func_80140D68(ot, p, 2, 8, (*(s16 *)(c + 12) & 0xF) * 2);
                }
            }
        }
        if (i == c3) {
            s32 m = b[0];

            if (m == 3 && (b[-2] & 8) != 0) {
                s32 k;
                u8 *q = (u8 *)ot + 0x14;
                s16 j;
                s16 y;

                j = 0;
                k = m;
                pb = (u16 *)&D_800B9A02;
                m24 = 0xFFFFFF;
                mhi = 0xFF000000;

                for (; j < 2; j++) {
                    if (j == 0) {
                        if (D_80115140[k] == 0) {
                            continue;
                        }
                        q[-7] = 0x30;
                        y = *e - 4;
                    } else {
                        s32 k2 = k * 2;

                        if (((s8 *)D_80115158)[k2] - ((s8 *)D_80115140)[k] < 2) {
                            continue;
                        }
                        q[-7] = 0x38;
                        y = *e + 3;
                    }
                    *(s16 *)(q - 10) = y;
                    __asm__("" ::: "memory");
                    *(u32 *)ot = 0x4000000;
                    q[-8] = 0x78;
                    *(u32 *)(q - 0x10) = 0x64808080;
                    *(s16 *)(q - 6) = 0x4056;
                    *(s16 *)(q - 0xC) = D_801879BC + (u16)D_8011516A[m].x + 0x4A;
                    eight = 8;
                    *(s16 *)(q - 2) = eight;
                    *(s16 *)(q - 4) = eight;

                    *(u32 *)ot = (*(u32 *)ot & mhi) |
                                 (D_800AE7BC[*pb].ot[2] & m24);
                    {
                        register u32 *op __asm__("$4");

                        op = D_800AE7BC[*pb].ot;

                        op[2] = (op[2] & mhi) | ((u32)ot & m24);
                    }
                    q += 0x14;
                    ot += 5;
                }
            }
        }
        i = i + 1;
        } while (i < n);
    }
    return ot;
}
