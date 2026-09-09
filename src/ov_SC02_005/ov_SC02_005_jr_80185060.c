#include "common.h"
#include "../shared/engine_prelude.h"
#include "ov_SC02_005_shared.h"

#include "common.h"

extern void func_80187280(s32 a0, s32 a1);
extern void func_80189F64(void);
extern void func_801876B0(s32 arg0);
extern void func_80187664(s32 arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern u16 D_801E4BBC;
extern s32 D_801E43D0[];

void func_80185060(s32 a0, s32 a1)
{
    u16 t;
    s32 flag;

    t = *(u16 *)(a0 + 0x70) + 1;
    func_80187280(a0, t);
    *(u8 *)(a0 + 0xC1) = 0;
    *(s32 *)(a0 + 0xDC) = 1;
    if (*(s16 *)(a0 + 0x104) == 0) {
        *(s16 *)(a0 + 0x104) = (s16)a1;
    }

    flag = 0;
    switch ((s16)(*(u16 *)(a0 + 0x70) - 3)) {
    case 0:
        *(u32 *)(*(s32 *)(a0 + 0xCC) + 0xE8) |= 0x2000;
        func_80189F64();
        flag = 1;
        break;
    case 5:
    case 7:
        *(u16 *)(D_801E43D0[*(s16 *)(a0 + 0x70)] + 0x5C) = 0x8800;
        break;
    case 6:
        *(u32 *)(*(s32 *)(a0 + 0x64) + 0xE8) |= 0x20000;
        break;
    case 8:
        *(u32 *)(*(s32 *)(a0 + 0x64) + 0xE8) |= 0x40000;
        break;
    }

    if (flag) {
        *(s16 *)(a0 + 0x100) = 0x18;
        if (a1 != 0) {
            func_801876B0(a0);
        }
    } else {
        *(s16 *)(a0 + 0x100) = 0x10;
        if (a1 != 0) {
            func_80187664(a0);
        }
        if (D_801E4BBC == 0) {
            *(s16 *)(*(s32 *)(a0 + 0xCC) + 0xFE) += 1;
        }
    }

    *(s16 *)(a0 + 0xAE) = -1;
    func_8012AD44((s32 *)a0, 2);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801851E0(s32 a0)
{
    *(s32 *)(a0 + 0xDC) = 1;
    *(u8 *)(a0 + 0xC1) = 0;
    *(s16 *)(a0 + 0xAE) = -1;
    func_8012AD44((s32 *)a0, 2);
}


#include "common.h"

/* func_80185214 — ov_SC02_005 (jr_80181D30 TU), 110 ins, byte-exact.
 *
 * Second-pass crack.  Structure was already right in pass 1; the whole residual
 * (25 ins) was register-allocation + list-scheduling.  Four levers, in order of
 * how much each bought:
 *
 *  1. state pinned to $4, and the `state << 3` result pinned to $2 (`idx`).
 *     With ONLY the $4 pin, gcc reuses the dead hard reg for the shift result
 *     (`sll $a0,$a0,3`); the target wants a fresh `$v0`.  Pinning the shift
 *     destination is what forces `sll $v0,$a0,3` + `addu $at,$at,$v0`.
 *     (Dropping the $4 pin instead moves `state` to $a1 — worse.)
 *
 *  2. `lo`/`hi` temps around each subtraction, and — load-bearing — a SEPARATE
 *     pair (`lo2`/`hi2`) for the second block.  Reusing lo/hi merges the pseudo
 *     webs and flips the subu operands to `subu $v1,$a2,$v1` (+11 ins).  The
 *     `hi` (pointer-chased) load is written BEFORE the `lo` load in block 2 —
 *     that ordering is what yields `lh $v1,0xE($a0)` / `lh $a2,0xE($v0)`.
 *
 *  3. `p = self` placed between the two operand loads and the subtraction: the
 *     target materialises `addu $a0,$s0,$zero` only at its first use, so the
 *     0x14 store and the 0xCC/0x6 loads still address off $s0.
 *
 *  4. §17 scheduling barrier (`__asm__ __volatile__("")`) between the 0x10
 *     fixed-point block and its store.  Without it sched1 hoists block-2's
 *     `lhu 0x70` / `lh 0xE` up into the load-delay slots of block 1 and the
 *     whole tail drifts (20 ins wrong).  Zero bytes emitted.
 */

extern s32 D_801E4474[];
extern s32 D_801E4418[];
extern u8 D_801E4AA0[];
extern u8 D_801E4AA4[];
extern u8 D_80063548[];

extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012B21C(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801853CC(s32 a0);

void func_80185214(s32 arg0) {
    register s32 self __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 state __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 idx __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 acc;
    s32 lo;
    s32 hi;
    s32 lo2;
    s32 hi2;
    void *tgt;

    self = arg0;
    state = *(s16 *)(self + 0x70);

    if (state < 12) {
        s32 p;

        if (*(s16 *)(self + 0xFE) == 1) {
            acc = D_801E4474[*(s16 *)(self + 0xFC)];
        } else {
            acc = D_801E4418[*(s16 *)(self + 0xFC)];
        }

        idx = state << 3;
        *(s32 *)(D_801E4AA0 + idx) = acc;
        *(s32 *)(D_801E4AA4 + (*(s16 *)(self + 0x70) << 3)) = 0;

        *(s32 *)(*(void **)(self + 0x20) + 0x24) =
            (s32)(D_801E4AA0 + (*(s16 *)(self + 0x70) << 3));

        *(s32 *)(*(void **)(self + 0x20) + 0x20) = (s32)D_80063548;

        func_80132784(self, *(s32 *)(self + 0x64), *(u16 *)(self + 0xFC));

        *(s16 *)(self + 0x6) = *(s32 *)(*(void **)(self + 0x20) + 0x48);
        *(s16 *)(self + 0xA) = *(s32 *)(*(void **)(self + 0x20) + 0x4C);
        *(s16 *)(self + 0xE) = *(s32 *)(*(void **)(self + 0x20) + 0x50);
        *(s16 *)(self + 0x102) = *(u16 *)(self + 0xA);

        func_8012B21C((void *)self);

        *(s32 *)(self + 0x14) = 0xFFE80000;

        lo = *(s16 *)(self + 0x6);
        hi = *(s16 *)(*(s32 *)(self + 0xCC) + 0x6);
        p = self;
        acc = lo - hi;
        acc = (acc << 12) + ((*(u16 *)(p + 0x70) & 7) << 16) + 0x40000;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
        *(s32 *)(p + 0x10) = acc;

        tgt = *(void **)(p + 0xCC);
        hi2 = *(s16 *)((s32)tgt + 0xE);
        lo2 = *(s16 *)(p + 0xE);
        acc = lo2 - hi2;
        *(s16 *)(p + 0x100) = *(u16 *)(p + 0x70);
        acc = (acc << 12) - ((*(u16 *)(p + 0x70) & 7) << 16) + 0x20000;
        *(s32 *)(p + 0x18) = acc;

        func_8012AD44((s32 *)p, 3);
    } else {
        *(s32 *)(*(void **)(self + 0x20) + 4) |= 0x80000000;
        func_801853CC(self);
    }
}


void func_801853CC(s32 a0) {
    func_8012AD44((s32 *)a0, 4);
}


extern void func_80186A04(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void func_80185060(s32 a0, s32 a1);
extern void func_80186B08(s32 param_1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801853EC(s32 arg0) {
    s32 s0;
    s32 r76;
    s32 r60;
    s32 flags;
    s32 cnt;

    s0 = arg0;
    r76 = *(u16 *)(s0 + 0x76);
    r60 = *(u16 *)(s0 + 0x60);
    cnt = r76 - r60;
    flags = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(u16 *)(s0 + 0x76) = cnt;
    *(u16 *)(s0 + 0x5C) = flags;
    func_8016AA50(arg0, *(s16 *)(s0 + 0x60));

    if (*(s16 *)(s0 + 0x76) <= 0) {
        *(u16 *)(s0 + 0x5E) = 0;
        func_80185060(arg0, 1);
        func_80186B08(arg0);
    } else {
        *(u8 *)(s0 + 0xC1) = 1;
        *(s32 *)(s0 + 0x1C) = 8;
        func_80186A04(arg0);
    }

    if (*(u16 *)(s0 + 0x5E) != 0x1D) {
        func_8002D4C8(0x4F3, 0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80186B08(s32 param_1);
extern void func_80186424(s32 arg0);
extern u16 D_801E43BC;

void func_8018548C(void *a0)
{
    u8 flags;

    if (func_8012BEE8((s32)a0) != 0) {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(u16 *)((s32)a0 + 0x5E) = 0;
        func_80186B08((s32)a0);
    }

    func_80186424((s32)a0);

    flags = *(u8 *)((s32)a0 + 0x74);
    if (flags != 0) {
        if (*(u16 *)((s32)a0 + 0xFE) & 1) {
            D_801E43BC = D_801E43BC | flags;
        }
    }
}


#include "common.h"

extern void (*D_801964A8[])(void);
extern void func_80186424(s32 arg0);
extern void func_80132F40(s32 arg0);
extern void func_80186F60(s32 arg0);
extern void func_801865D0(void *arg0);
extern void func_80189E34(s32 arg0, s32 arg1);
extern void func_8018A0E4(s32 arg0);
extern u16 D_801E43BC;
extern u16 D_801E4BBC;
extern u16 D_800B99D8;

void func_8018550C(void *a0)
{
    s32 flags;
    u8 v1;

    D_801964A8[*(u16 *)((u8 *)a0 + 0x2)]();

    flags = *(s32 *)(*(s32 *)((u8 *)a0 + 0xCC) + 0xE8);

    if ((flags & 0x8000) == 0) {
        func_80186424((s32)a0);

        v1 = *(u8 *)((u8 *)a0 + 0x74);
        if (v1 != 0) {
            if (*(u16 *)((u8 *)a0 + 0xFE) & 0x1) {
                D_801E43BC = D_801E43BC | v1;
            }
        }

        if (*(s16 *)((u8 *)a0 + 0x70) == 0x11) {
            if (*(u16 *)((u8 *)a0 + 0x5C) & 0x400) {
                func_80132F40((s32)a0);
            }
        }

        if ((*(u16 *)((u8 *)a0 + 0xFE) & 0x2) && (flags & 0x20)) {
            func_80186F60((s32)a0);
        } else if ((*(u16 *)((u8 *)a0 + 0xFE) & 0x1) && (flags & 0x100)) {
            func_801865D0(a0);
        }

        if (flags & 0x10000) {
            if ((D_800B99D8 & 0x3) == 0) {
                if ((rand() & 0x1F) == (*(s16 *)((u8 *)a0 + 0x70) & 0x1F)) {
                    func_80189E34((s32)a0, D_801E4BBC);
                }
            }
        } else if (flags & 0x4000) {
            if ((D_800B99D8 % 60) == (*(s16 *)((u8 *)a0 + 0x70) * 2)) {
                func_8018A0E4((s32)a0);
            }
        }
    }
}


#include "common.h"



extern void func_801858C4();
extern void func_80185858(s32 a0, void *a1, void *a2);

extern Blk8 D_801E2E9C;
extern Blk8 D_801E2EA4;

void func_801856E4(void)
{
    Blk8 blk1;
    Blk8 blk2;

    blk1 = D_801E2E9C;
    blk2 = D_801E2EA4;

    ((void (*)(void))func_801858C4)();
    func_80185858(0x11, &blk1, &blk2);
}


#include "common.h"



extern void func_801858C4();
extern void func_80185858(s32 a0, void *a1, void *a2);

extern Blk8 D_801E2EAC;
extern Blk8 D_801E2EB4;
extern Blk8 D_801E2EBC;
extern Blk8 D_801E2EC4;

void func_80185764(void *a0)
{
    Blk8 blk1;
    Blk8 blk2;

    func_801858C4(a0);

    blk1 = D_801E2EAC;
    blk2 = D_801E2EB4;
    func_80185858(8, &blk1, &blk2);

    blk1 = D_801E2EBC;
    blk2 = D_801E2EC4;
    func_80185858(0xA, &blk1, &blk2);
}


extern s32 D_801E43C0;

void func_80185858(s32 arg0, void *arg1, void *arg2) {
    typedef struct { u8 pad[0x5C]; u16 f5C; } F5C_S;
    extern F5C_S *D_801E43CC[];
    s32 *p = &D_801E43C0;

    if ((*p != 0) && (*(p++ + 1) != 0)) {
        return;
    }
    func_8018C598(D_801E43CC[(arg0 << 16) >> 16], arg1, arg2, p, 0x20, 0x80);
}


#include "common.h"

extern void func_8012C218(void *a0);
extern s32 D_801E43C0;
extern s32 D_801E43C4;

void func_801858C4(void) {
    s32 *ptr = &D_801E43C0;

    if (*ptr != 0) {
        func_8012C218((void *)*ptr);
        *ptr = 0;
    }
    if (D_801E43C4 != 0) {
        func_8012C218((void *)D_801E43C4);
        D_801E43C4 = 0;
    }
}


#include "common.h"

extern u16 D_801E4BBC;
extern u16 D_801E4398;
extern u16 D_801E439C;
extern s16 D_80195B24[];

extern void func_8017BFF0(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801900E0(void);
extern void func_8018AB84(void);

void func_8018592C(u8 *arg0) {
    s16 val;
    register u8 *a2 __asm__("$6");  // !FAKE: pin $6 — NEEDED DIFFERS (P36 rung B tus9)
    u32 idx;
    register s32 flags __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    a2 = arg0;
    flags = *(s32 *)(a2 + 0xE8);
    idx = D_801E4BBC;
    *(s16 *)(a2 + 0x102) = 0;
    flags &= ~8;
    *(s32 *)(a2 + 0xE8) = flags;

    if (idx < 2) {
        D_801E4BBC++;
    }

    val = D_80195B24[D_801E4BBC];
    *(s16 *)(a2 + 0x76) = val;
    D_801E439C = val;
    D_801E4398 = val;

    func_8017BFF0((s32)&D_801E4398, (s32)&D_801E439C, 0x60);

    switch (D_801E4BBC) {
        case 1:
            func_8002D4C8(0x11, 0);
            func_801900E0();
            break;
        case 2:
            func_8018AB84();
            break;
    }
}


extern s32 func_80185A88(s32 arg0, s32 arg1);

void func_80185A04(s32 param_1, s32 param_2, s16 param_3) {
    s32 ret;

    if ((*(u32 *)(param_2 + 0xE8) & 4) == 0) {
        *(u32 *)(param_2 + 0xE8) |= 0x10;
        ret = func_80185A88(param_2, param_3);
        *(u16 *)(param_2 + 0x60) = *(u16 *)(param_2 + 0x60) + ret;
        func_8016AA50(param_1, (s16)ret);
        *(s16 *)(param_2 + 0xDE) = 8;
        func_801869E0((s32 *)param_2);
    }
}


extern u16 D_801E4BBC;
extern s16 D_80195B24[];

s32 func_80185A88(s32 param_1, s32 param_2) {
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)
    int t;
    int x;
    int m;
    int h;
    int d;
    t = (u16)*(u16 *)(param_1 + 0x76) - (u16)*(u16 *)(param_1 + 0x60);
    x = t - param_2;
    d = t + zr;
    m = x + zr;
    if (D_801E4BBC == 2) {
        if (*(u32 *)(param_1 + 0xE8) & 0x800) goto RET;
        if ((s16)x < 0x80) m = 0x80;
    } else {
        if (*(u32 *)(param_1 + 0xE8) & 0x80000) goto RET;
        h = (s16)D_80195B24[D_801E4BBC] >> 1;
        if ((s16)x < h) m = h;
    }
RET:
    return (s16)(d - m);
}


#include "common.h"





extern D_80195AF4_t D_80195AF4[];
extern D_80195AF6_t D_80195AF6[];
extern s16 D_80126CB4;
extern s16 D_80126CB8;
extern s16 D_80195ACC;
extern s16 D_801E43A8;
extern s16 D_801E43B0;

void func_80185B38(s32 a0)
{
    s32 pad[2];
    s16 q;
    s16 d;
    s16 e;
    s16 n6;
    s16 nE;

    if (*(s16 *)(a0 + 0xE0) < 0) {
        if (*(s16 *)(a0 + 0xDC) != 1) {
            if (*(s32 *)(a0 + 0xE8) & 0x800) {
                q = ((s16)(D_80126CB4 - *(s16 *)(a0 + 0x6)) + 0x2A) / 0x54;
                d = D_80126CB8 - D_80195ACC;
                if (q >= 4) {
                    q = 3;
                } else if (q < 0) {
                    q = 0;
                }
                *(s16 *)(a0 + 0x6) = *(s16 *)(a0 + 0x6) + q * 0x54;
                *(s16 *)(a0 + 0xE) = D_80195ACC;
                if (d < -0x2A) {
                    *(s16 *)(a0 + 0xE) = D_80195ACC - 0x54;
                } else if (d > 0x2A) {
                    *(s16 *)(a0 + 0xE) = D_80195ACC + 0x54;
                }
            } else {
                e = D_80126CB4 + 0x80;
                d = D_80126CB8 - *(s16 *)(a0 + 0xE);
                *(s16 *)(a0 + 0x6) = -0x80;
                if (e < -0x2A) {
                    *(s16 *)(a0 + 0x6) = -0x80 - 0x54;
                } else if (e > 0x2A) {
                    *(s16 *)(a0 + 0x6) = -0x80 + 0x54;
                }
                q = (d + 0x2A) / 0x54;
                if (q < -3) {
                    q = -3;
                } else if (q > 0) {
                    q = 0;
                }
                *(s16 *)(a0 + 0xE) = *(s16 *)(a0 + 0xE) + q * 0x54;
            }
        } else {
            n6 = D_801E43A8;
            nE = D_801E43B0;
            *(s16 *)(a0 + 0x6) = n6;
            *(s16 *)(a0 + 0xE) = nE;
        }
    } else {
        *(s16 *)(a0 + 0x6) = D_80195AF4[*(s16 *)(a0 + 0xE0)].f0;
        *(s16 *)(a0 + 0xE) = D_80195AF6[*(s16 *)(a0 + 0xE0)].f0;
    }
}






extern s32 D_801270CC;

s32 func_80185D6C() {
    return ((MainStruct *)D_801270CC)->f_E8 & 4;
}


s32 func_80185D84(s32 arg0) {
    s32 var;

    var = *(s32 *)(arg0 + 0xCC);
    func_80185DD0(0, (u16 *)(*(s32 *)(var + 0x20) + 0x12), 0x100);
    return *(s16 *)(*(s32 *)(var + 0x20) + 0x12) == 0;
}


#include "common.h"

void func_80185DD0(s32 target, u16 *cur, s32 step)
{
    s32 t;
    s32 diff;
    s32 mag;

    t = (target - *cur) & 0xFFF;
    if (t < 0x800) {
        diff = t;
    } else {
        diff = t | 0xF000;
    }
    mag = diff;
    if ((s16)diff < 0) {
        mag = -diff;
    }
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    if ((s16)mag > (u16)step) {
        if ((s16)diff < 0) {
            *cur = *cur - step;
        } else {
            *cur = *cur + step;
        }
    } else {
        *cur = target;
    }
}


#include "common.h"

extern u16 D_801E4BBC;
extern s32 D_801959E0[];

u16 func_80185E54(s32 arg0)
{
    u16 val;

    val = D_801E4BBC;
    *(s16 *)(arg0 + 0x102) = 0;
    val = *(u16 *)D_801959E0[val];
    *(u16 *)(arg0 + 0x100) = val;
    return val;
}


