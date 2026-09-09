#include "common.h"
#include "../shared/engine_prelude.h"
#include "ov_SC02_005_shared.h"

#include "common.h"

extern u16 D_801E4BBC;
extern s32 D_801959E0[];
extern s32 D_801E43A0;
extern s32 func_801860F4();
extern s32 func_8018AD20(s32 a0);
extern s32 func_8018AC48(s32 a0);
extern s32 func_80186144(void *a0, s32 a1);

s16 func_80185E80(s32 arg0) {
    u16 *p;
    s32 flag;
    s32 res;
    s32 flags;
    u16 val;
    u16 var;
    s16 nxt;
    s16 i;

    p = (u16 *)D_801959E0[D_801E4BBC];
    if (*(s16 *)(arg0 + 0x100) != 0) {
        goto ret0;
    }
    if (*(s32 *)(arg0 + 0xE8) & 0x200) {
        goto ret0;
    }
    var = p[*(s16 *)(arg0 + 0x102) * 2 + 1];
    flag = var & 0x100;
    var = var & 0xFF;
    switch ((s16)(var - 2)) {
    case 0:
        if (func_801860F4(arg0, (s16)var) != 0) {
            if (D_801E43A0 & 0x2000) {
                var = 0;
            }
        } else {
            var = 0;
        }
        break;
    case 1:
        res = func_8018AD20(arg0);
        *(s16 *)(arg0 + 0xE0) = res;
        if ((s16)res < 0) {
            var = 0;
        }
        break;
    case 2:
        res = func_8018AC48(arg0);
        *(s16 *)(arg0 + 0xE0) = res;
        if ((s16)res < 0) {
            var = 1;
        }
        break;
    case 7:
        res = func_80186144((void *)arg0, 9);
        *(s16 *)(arg0 + 0xE0) = res;
        if ((s16)res < 0) {
            var = 1;
        }
        break;
    case 3:
        if (*(s32 *)(arg0 + 0xE8) & 0x408) {
            var = 0;
        }
        break;
    case 4:
    case 5:
        if ((*(s32 *)(arg0 + 0xE8) & 0x800) == 0) {
            if (*(s16 *)(arg0 + 0x76) < 0x81) {
                var = 0;
            }
        }
        break;
    case 6:
        flags = *(s32 *)(arg0 + 0xE8);
        if (flags & 0x800) {
            var = 0;
            break;
        }
        if ((flags & 0x400) == 0) {
            if ((flags & 0xA) != 2) {
                goto ret0;
            }
            *(u16 *)(arg0 + 0xFE) = *(u16 *)(arg0 + 0xFE) + 1;
            goto ret0;
        }
        res = func_80186144((void *)arg0, 8);
        *(s16 *)(arg0 + 0xE0) = res;
        if ((s16)res < 0) {
            var = 6;
        }
        break;
    }
    i = *(u16 *)(arg0 + 0x102) + 1;
    *(u16 *)(arg0 + 0x102) = i;
    nxt = ((s16 *)p)[i * 2];
    if (nxt == -1) {
        val = D_801E4BBC;
        *(s16 *)(arg0 + 0x102) = 0;
        val = *(u16 *)D_801959E0[val];
        *(u16 *)(arg0 + 0x100) = val;
    } else {
        *(u16 *)(arg0 + 0x100) = nxt;
    }
    if (flag != 0) {
        if ((*(s32 *)(arg0 + 0xE8) & 0xA) == 2) {
            *(u16 *)(arg0 + 0xFE) = *(u16 *)(arg0 + 0xFE) + 1;
        }
    }
    return var;
ret0:
    return 0;
}


extern s32 func_80132E6C(s16 *a0);
extern s16 D_80126CB8;

s32 func_801860F4(s16 *arg0) {
    s32 ret;
    s32 lim;
    s32 cmp;

    ret = func_80132E6C(arg0);
    lim = D_80126CB8;
    if (*(s16 *)((s32)arg0 + 0xE) < lim) {
        cmp = 0;
    } else {
        cmp = ret >= 0x6400;
    }
    return cmp;
}


typedef struct {
    s16 f0;
    s16 f1;
    s16 f2;
    s16 f3;
} TBL_80186144;

extern TBL_80186144 D_80195AF8[];

extern u16 D_801E43B4;

s32 func_80186144(void *a0, s32 a1)
{
    s16 idx = D_801E43B4;

    if (D_80195AF8[idx].f0 == a1)
        return idx;
    return -1;
}


#include "common.h"

/* §183 TYPE-adopted-TU.  The destination TU spells this symbol
 *     extern MainStruct *D_801E43A4;
 * (just above func_8018622C).  Both typedefs below are VERBATIM copies of the TU's
 * own definitions — §183.1 name/shape trap respected: same name => same body — so
 * gate_main's strip_dup_typedefs reuses the file's copy and drops these.
 * NOTE FOR THE BANKER: this only works once the TU's SubStruct/MainStruct block sits
 * ABOVE the func_80186178 INCLUDE_ASM stub (TU line 4347); see the immovable report. */




extern MainStruct *D_801E43A4;

void func_80186178(s32 *a0)
{
    s32 *a1 = a0;
    s32 a2 = 0x80000000;
    register s32 *a0_reg asm ("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus10)
    s32 *v0;
    s32 *v1;
    s32 v2;

    // First: access at 0x20
    v1 = *(s32 **)((char *)a1 + 0x20);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Second: access at 0xCC
    v0 = *(s32 **)((char *)a1 + 0xCC);
    v1 = *(s32 **)((char *)v0 + 0x20);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Fourth (source-order moved up): global load. Placing this statement
    // here — between the 0xCC and 0xD0 blocks — lets gcc's scheduler thread
    // the two-instruction lui/lw address computation into the 0xD0 block's
    // load-delay slots instead of stalling on nops (T2: source order drives
    // scheduling for independent setup). Also frees $a0 (dead after the
    // a1=a0 copy) via an explicit register pin, matching the target's reuse
    // of $a0 for the global pointer.
    a0_reg = (s32 *)D_801E43A4;   /* §183 cast at the USE SITE, not on the decl */

    // Third: access at 0xD0
    v0 = *(s32 **)((char *)a1 + 0xD0);
    v1 = *(s32 **)((char *)v0 + 0x20);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Fourth cont'd: from global (no 0x20 indirection, just 0xCC then 0x4)
    v1 = *(s32 **)((char *)a0_reg + 0xCC);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Fifth: conditional at 0xD4
    v2 = *(s32 *)((char *)a1 + 0xE8);
    if ((v2 & 0x2) == 0) {
        v0 = *(s32 **)((char *)a1 + 0xD4);
        v1 = *(s32 **)((char *)v0 + 0x20);
        *(s32 *)((char *)v1 + 0x4) |= a2;
    }
}


#include "common.h"



extern MainStruct *D_801E43A4;

void func_8018622C(MainStruct *a0) {
    register MainStruct *a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus10)
    register SubStruct *v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 a2;

    a1 = a0;
    a2 = 0x7FFFFFFF;

    v1 = a1->f_20;
    v0 = v1->field_4;
    v0 &= a2;
    v1->field_4 = v0;

    v0 = (s32)a1->f_CC;
    v1 = ((MainStruct *)v0)->f_20;
    v0 = v1->field_4;
    v0 &= a2;
    v1->field_4 = v0;

    v0 = (s32)a1->f_D0;
    v1 = ((MainStruct *)v0)->f_20;
    v0 = v1->field_4;

    a0 = D_801E43A4;
    v0 &= a2;
    v1->field_4 = v0;

    v1 = (SubStruct *)a0->f_CC;
    v0 = v1->field_4;
    v0 &= a2;
    v1->field_4 = v0;

    v0 = a1->f_E8;
    if ((v0 & 0x2) == 0) {
        v0 = (s32)a1->f_D4;
        v1 = ((MainStruct *)v0)->f_20;
        v0 = v1->field_4;
        v0 &= a2;
        v1->field_4 = v0;
    }
}


void func_801862E0(s32 *a0) {
        s32 v0 = *(s32 *)((s32)a0 + 0xCC);
        *(s16 *)((s32)a0 + 0x98) = 0;
        *(s16 *)(v0 + 0x98) = 0;
    }


void func_801862F0(void * arg0) {
        *(short *)((char *)arg0 + 0x98) = 1;
        *(short *)(*(int *)((char *)arg0 + 0xcc) + 0x98) = 1;
    }


extern void *D_801959EC[];
extern void *D_801959F0[];
extern void func_80132EC4(void *a0, s16 a1);
extern void func_8012A860(void *a0, s32 a1);

void func_80186304(param_1, param_2, param_3)
void *param_1;
s32 param_2;
s16 param_3;
{
    void **s0;
    s32 sp4;
    register s32 base __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)

    sp4 = 0;
    if (param_2 < 0) {
        param_2 = -param_2;
        sp4 = 1;
    }
    if (param_2 < 0x1A) {
        if (param_3 == 0) {
            param_3 = 2;
            if (*(u32 *)((u8 *)param_1 + 0xE8) & 0x2000) {
                param_3 = 1;
            }
        }
        base = (s32)&D_801959EC;
        s0 = (void **)(base + param_2 * 8);
        func_80132EC4(*s0, param_3);
        if (sp4 != 0) {
            func_8012A860(param_1, (s32)*s0);
        } else {
            func_8012A828((s32)param_1, *s0);
        }
        base = (s32)&D_801959F0;
        s0 = (void **)(base + param_2 * 8);
        func_80132EC4(*s0, param_3);
        if (sp4 != 0) {
            func_8012A860(*(void **)((u8 *)param_1 + 0xCC), (s32)*s0);
        } else {
            func_8012A828((s32)*(void **)((u8 *)param_1 + 0xCC), *s0);
        }
    }
}


extern u8 D_80126B5C;
extern s32 D_80126B60;
extern u16 D_80126B62;
extern s32 D_80126B64;
extern u16 D_80126B66;
extern s32 *D_80126B78;
extern void func_8012F0BC(s32 *a0, s32 *a1, s32 *a2);
extern void func_8012F1A4(s32 *a0, s32 a1, s32 *a2);
extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_80186424(s32 arg0)
{
    if (*(u8 *)(arg0 + 0x74) != 0) {
        extern s32 gVecX __asm__("D_80126B5C");
        s32 in[4];
        s32 out[4];
        s32 tmp[4];
        u16 h;

        in[0] = gVecX;
        in[1] = D_80126B60;
        in[2] = D_80126B64;
        func_8012F0BC((s32 *)(*(s32 *)(arg0 + 0x20) + 0x34), in, tmp);
        func_80132784(arg0, *(s32 *)(arg0 + 0x64), *(u16 *)(arg0 + 0xFC));
        func_8012F1A4((s32 *)(*(s32 *)(arg0 + 0x20) + 0x34), (s32)tmp, out);
        gVecX = out[0];
        D_80126B60 = out[1];
        D_80126B64 = out[2];
        h = *((u16 *)&gVecX + 1);
        *(u16 *)((s32)D_80126B78 + 8) = h;
        *(s32 *)((s32)D_80126B78 + 0x48) = (s32)(s16)h;
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus10)
        *(u16 *)((s32)D_80126B78 + 0xA) = D_80126B62;
        *(s32 *)((s32)D_80126B78 + 0x4C) = (s32)(s16)D_80126B62;
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus10)
        *(u16 *)((s32)D_80126B78 + 0xC) = D_80126B66;
        *(s32 *)((s32)D_80126B78 + 0x50) = (s32)(s16)D_80126B66;
    } else {
        func_80132784(arg0, *(s32 *)(arg0 + 0x64), *(u16 *)(arg0 + 0xFC));
    }
}


#include "common.h"

extern s16 D_80126CB6;

void func_8018655C(s32 a0) {
    if ((*(u32 *)(a0 + 0xE8) & 0x200) == 0) {
        if (D_80126CB6 < *(s16 *)(a0 + 0xA) - 0x30) {
            *(s16 *)(a0 + 0xE6) = *(s16 *)(a0 + 0xE6) + 1;
        } else {
            *(s16 *)(a0 + 0xE6) = 0;
        }
        if (*(s16 *)(a0 + 0xE6) >= 0x30) {
            *(s16 *)(a0 + 0xE4) = 0x10;
            *(u32 *)(a0 + 0xE8) = *(u32 *)(a0 + 0xE8) | 0x200;
        }
    }
}


extern s32 func_8012D714(s32 param_1, u32 param_2);
    extern u16 D_80126B96;
    void func_801865D0(void *arg0) {
        if (func_8012D714((s32)arg0, 0x5)) {
            D_80126B96 = 0x4005;
        }
    }


#include "common.h"

extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_80186F9C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s16 D_801E43B8;

void func_80186600(s32 a0) {
    s32 flags;
    s32 v0;
    s32 s1;

    flags = *(s32 *)(a0 + 0xE8);
    s1 = *(s32 *)(a0 + 0xCC);
    D_801E43B8 = 0;

    if (flags & 1) {
        if (flags & 0x200) {
            s16 fE6 = *(s16 *)(a0 + 0xE6);

            if (fE6 >= 0x55) {
                s16 fE4 = *(s16 *)(a0 + 0xE4);

                if (fE4 != 0) {
                    s32 p = *(s32 *)(s1 + 0x20);
                    u16 t;
                    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x100;
                    t = *(u16 *)(a0 + 0xE4);
                    D_801E43B8 = 0x100;
                    *(s16 *)(a0 + 0xE4) = t - 1;
                } else {
                    v0 = flags & ~0x300;
                    *(s32 *)(a0 + 0xE8) = v0;
                    *(s16 *)(a0 + 0xE6) = 0;
                }
            } else {
                if (fE6 < 0x48) {
                    if ((fE6 & 7) == 0) {
                        func_80186F9C(a0, 0x16);
                        func_80186F9C(a0, 0x19);
                        func_8002D4C8(0x4F0, 0);
                    }
                } else if (fE6 == 0x54) {
                    v0 = flags | 0x100;
                    *(s32 *)(a0 + 0xE8) = v0;
                    func_8002D4C8(0x4EC, 0);
                }
                *(s16 *)(a0 + 0xE6) = *(u16 *)(a0 + 0xE6) + 1;
            }
        } else {
            s32 v0;
            s32 p1;
            s32 p2;
            s32 p3;
            s32 r;

            v0 = func_8012B864(a0);
            p1 = *(s32 *)(s1 + 0x20);
            p2 = *(s32 *)(a0 + 0x20);
            r = func_8012B608(*(s16 *)(p1 + 0x12) + *(s16 *)(p2 + 0x12), v0, 8);
            p3 = *(s32 *)(s1 + 0x20);
            {
                u16 t2 = *(u16 *)(p3 + 0x12);
                D_801E43B8 = r;
                *(u16 *)(p3 + 0x12) = t2 + r;
            }
        }
    }
}


extern u16 D_801E4BBC;
extern u16 D_801E43B4;
extern s32 D_801270C8;
extern u8 D_80195AC4[];
extern s16 D_80195ACE;


extern D_80195AF4_t D_80195AF4[];

s32 func_8018675C(void *a0)
{
    s32 flags = *(s32 *)((u8 *)a0 + 0xE8);

    if (flags & 0x800) {
        s16 t = *(s16 *)((u8 *)a0 + 0xE0);
        if (t >= 0) {
            if (*(s16 *)((u8 *)a0 + 6) < *(s16 *)((u8 *)D_80195AF4 + t * 8)) {
                u16 old = D_801E43B4;
                s32 f6 = *(s16 *)((u8 *)D_80195AF4 + t * 8 + 6);
                D_801E43B4 = old + 1;
                D_801270C8 = f6;
                *(s16 *)((u8 *)a0 + 0xE0) = -1;
            }
        }
        if (*(s32 *)((u8 *)a0 + 0x10) >= 0) {
            return 0;
        }
        if (*(s16 *)((u8 *)a0 + 6) < D_80195ACE) {
            *(s16 *)((u8 *)a0 + 0xFE) = 0;
            *(s32 *)((u8 *)a0 + 0xE8) |= 8;
            return 1;
        }
        return 0;
    } else {
        if (*(s32 *)((u8 *)a0 + 0x18) > 0) {
            s32 phase = D_801E4BBC;
            if (*(s16 *)((u8 *)D_80195AC4 + phase * 4) < *(s16 *)((u8 *)a0 + 0xE)) {
                *(s32 *)((u8 *)a0 + 0xE8) = flags | ((phase == 2) ? 0x400 : 8);
                *(s16 *)((u8 *)a0 + 0xFE) = 0;
                return 1;
            }
        }
    }
    return 0;
}


extern u16 D_801E4BBC;
extern s32 D_80195AD0[];
extern s32 D_80195AD2[];

s32 func_8018687C(s32 a0)
{
    if (*(u32 *)(a0 + 0xE8) & 0x800) {
        return 0;
    }

    if (*(s32 *)(a0 + 0x10) > 0) {
        if (*(s16 *)(D_80195AD2 + D_801E4BBC) < *(s16 *)(a0 + 6)) {
            *(s16 *)(a0 + 6) = *(s16 *)(D_80195AD2 + D_801E4BBC);
            return 1;
        }
    }

    if (*(s32 *)(a0 + 0x10) >= 0) {
        return 0;
    }

    if (*(s16 *)(a0 + 6) >= *(s16 *)(D_80195AD0 + D_801E4BBC)) {
        return 0;
    }
    *(s16 *)(a0 + 6) = *(s16 *)(D_80195AD0 + D_801E4BBC);
    return 1;
}


#include "common.h"

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

s32 func_8018692C(s32 arg0) {
    extern s32 D_801E43CC[];
    extern s32 D_801E4400[];

    s32 count = 0;
    s32 i = 0;
    s32 *p = D_801E43CC;

    for (; i < 13; i++, p++) {
        if ((*p = func_8012C658(0x49, i, arg0)) == 0) {
            count++;
        }
    }

    i = 0;
    p = D_801E4400;
    for (; i < 6; i++, p++) {
        if ((*p = func_8012C658(0x49, i + 13, arg0)) == 0) {
            count++;
        }
    }

    return count;
}


















extern s32 D_80196208;
void func_801869E0(s32 *param_1)
{
  s32 *new_var;
  new_var = (s32 *) (((char *) param_1) + 0x20);
  *((s32 *) ((*new_var) + 0x80)) = (s32) (&D_80196208);
  new_var = (s32 *) ((*((s32 *) ((*((s32 *) (((char *) param_1) + 0xcc))) + 0x20))) + 0x80);
  *new_var = *((s32 *) ((*((s32 *) (((char *) param_1) + 0xcc))) + 0x20));
  param_1++;
  param_1--;
  *((s32 *) ((*new_var) + 0x80)) = (s32) (&D_80196208);
}

#include "common.h"

extern s32 D_801E43A0;
extern u16 D_80195B4C[];
extern s32 D_801961B8;
extern s32 D_801961E0;

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 val;
} Entry_80186A04;

void func_80186A04(s32 arg0) {
    s16 idx;
    s32 flags;
    u32 key;
    Entry_80186A04 *t0;
    Entry_80186A04 *a2;
    Entry_80186A04 *p;
    s32 a1;
    s32 j;
    s16 v0;

    idx = *(s16 *)(arg0 + 0x70);
    if (idx >= 14) {
        return;
    }
    flags = D_801E43A0;
    if ((flags >> (idx + 1)) & 1) {
        return;
    }
    key = D_80195B4C[idx];
    if (key >= 0x16) {
        t0 = (Entry_80186A04 *)&D_801961E0;
        key -= 0x16;
    } else {
        t0 = (Entry_80186A04 *)&D_801961B8;
    }
    /* zero-byte allocno-priority ref-boost (cookbook regalloc "ref-boost", global.c:594):
     * lifts `key`'s n_refs 7 -> 8 across the floor_log2 step so it allocates before the
     * table base -> key=$a3 / base=$t0 as in the target. Emits no instruction. */
    __asm__("" :: "r"(key));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus10)
    for (a1 = 0; a1 < 4; a1++) {
        a2 = &t0[a1];
        v0 = a2->val;
        if (v0 != -1) {
            if (v0 == (s32)(key & 0xFFFF)) {
                return;
            }
            if (!((s32)(key & 0xFFFF) < v0)) {
                continue;
            }
            for (j = 3; a1 < j; j--) {
                p = &t0[j];
                p->val = p[-1].val;
            }
        }
        a2->val = key;
        return;
    }
}


extern s32 D_801961B8;
    extern s32 D_801961E0;
    void func_80186ADC(s32 arg0) {
        *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80) = &D_801961B8;
        *(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0xcc) + 0x20) + 0x80) = &D_801961E0;
    }


#include "common.h"

extern u16 D_80195B4C[];
extern s32 D_801961B8;
extern s32 D_801961E0;

void func_80186B08(s32 param_1)
{
    s16 idx;
    u16 val;
    u8 *base;
    int i;
    int j;

    idx = *(s16 *)(param_1 + 0x70);

    if (idx >= 14)
        return;

    val = D_80195B4C[idx];

    if (val >= 0x16) {
        base = (u8 *)&D_801961E0;
        val -= 0x16;
    } else {
        base = (u8 *)&D_801961B8;
    }

    val &= 0xFFFF;

    for (i = 0; i < 4; i++) {
        if (*(s16 *)(base + i * 8 + 6) == val) {
            for (j = i; j < 4; j++) {
                *(u16 *)(base + j * 8 + 6) = *(u16 *)(base + j * 8 + 14);
            }
            return;
        }
    }
}


void func_80186BB8(void) {
    typedef struct {
        u8 pad[0x5C];
        u16 f5C;
    } F5C_S;
    extern F5C_S *D_801E43CC[];
    extern s8 D_80195ABC[];
    s32 i;
    s32 c;

    i = 0;
    c = D_80195ABC[0];
    while (c >= 0) {
        *(s16 *)((s32)D_801E43CC[c] + 0xAE) = -1;
        i++;
        c = D_80195ABC[i];
    }
}


void func_80186C0C(void *a0) {
    typedef struct { u8 pad[0x5C]; u16 f5C; } F5C_S;
    extern F5C_S *D_801E43CC[];
    extern s8 D_80195ABC[];
    s32 i;
    s32 ent;
    s32 c;

    for (i = 0; (c = D_80195ABC[i]) >= 0; i++) {
        ent = (s32)D_801E43CC[c];
        if (*(s32 *)(ent + 0xDC) == 0) {
            *(u16 *)(ent + 0xAE) = 0;
        }
    }
}


typedef struct {
    u8 pad[0x5C];
    u16 f5C;
} F5C_S;

extern F5C_S *D_801E43CC[];

void func_80186C70(void *a0) {
    s32 i;
    for (i = 0; i < 0x13; i++) {
        D_801E43CC[i]->f5C &= ~0x400;
    }
}


extern F5C_S *D_801E43CC[];

void func_80186CA8(void *a0) {
    s32 i;
    s32 *p;

    i = 0;
    p = ((s32 *)D_801E43CC);
    while (i < 0x13) {
        s32 ent = *p;
        if (*(u16 *)(*(s32 *)(ent + 0x78) + 2) & 0x400) {
            *(u16 *)(ent + 0x5C) |= 0x400;
        }
        i++;
        p++;
    }
}


extern s32 D_801E43DC;
extern s32 D_801E43E0;
extern s32 D_801E43E4;
extern s32 D_801E43E8;

void func_80186D00(void) {
    *(u16 *)(D_801E43DC + 0x5C) &= ~0x800;
    *(u16 *)(D_801E43E0 + 0x5C) &= ~0x800;
    *(u16 *)(D_801E43E4 + 0x5C) &= ~0x800;
    *(u16 *)(D_801E43E8 + 0x5C) &= ~0x800;
}








extern s32 D_801E43DC;
extern s32 D_801E43E0;
extern s32 D_801E43E4;
extern s32 D_801E43E8;

void func_80186D74(void)
{
    *(u16 *)(D_801E43DC + 0x5C) |= 0x800;
    *(u16 *)(D_801E43E0 + 0x5C) |= 0x800;
    *(u16 *)(D_801E43E4 + 0x5C) |= 0x800;
    *(u16 *)(D_801E43E8 + 0x5C) |= 0x800;
}


#include "common.h"

extern s32 D_801E43A0;
extern void func_80186F9C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186DE8(s32 a0) {
    s32 v0;
    s16 state;
    s32 flags;
    s32 a2;

    state = *(s16 *)(a0 + 0xFC);
    if (state == 0) {
        return;
    }
    flags = *(s32 *)(a0 + 0xE8);
    state = state - 1;
    *(s16 *)(a0 + 0xFC) = state;
    if (flags & 0x40) {
        if (state != 0) {
            return;
        }
        v0 = flags & ~0x40;
        *(s32 *)(a0 + 0xE8) = v0;
        v0 = 8;
        *(s16 *)(a0 + 0xFC) = v0;
        return;
    }
    if (flags & 0x200) {
        *(s16 *)(a0 + 0xFC) = 0;
        return;
    }
    a2 = D_801E43A0;
    if ((a2 & 0x1540) == 0x1540) {
        *(s16 *)(a0 + 0xFC) = 0;
        return;
    }
    if (state != 0) {
        return;
    }
    v0 = flags | 0x40;
    *(s32 *)(a0 + 0xE8) = v0;
    v0 = 0xC;
    *(s16 *)(a0 + 0xFC) = v0;
    if ((a2 & 0x40) == 0) {
        func_80186F9C(a0, 5);
    }
    if ((D_801E43A0 & 0x100) == 0) {
        func_80186F9C(a0, 0xA);
    }
    if ((D_801E43A0 & 0x400) == 0) {
        func_80186F9C(a0, 0xF);
    }
    if ((D_801E43A0 & 0x1000) == 0) {
        func_80186F9C(a0, 0x14);
    }
    func_8002D4C8(0x4F0, 0);
}


extern s32 D_801E43A0;

void func_80186F14(void *a0)
{
    if (*(s16*)((s32)a0 + 0xFC) == 0 &&
        (D_801E43A0 & 0x1540) != 0x1540) {
        *(s16*)((s32)a0 + 0xFC) = 8;
        *(s32*)((s32)a0 + 0xE8) &= ~0x40;
    }
}


void func_80186F58(void *a0) {
        *(s16 *)((s32)a0 + 0xFC) = 0;
    }


void func_80186F60(s32 a0) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_8012D714();
    if (func_8012D714(a0, 1)) {
        D_80126B96 = 0x4002;
        D_80126B98 = 10;
    }
}


extern s32 D_801E43A0;
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80186F9C(a0, a1)
    s32 a0;
    u16 a1;
{
    s32 a2;
    s32 v1;

    if (a1 < 0x20) {
        if (a1 < 0x16) {
            func_8012C658(0x51, a1, a0);
        } else {
            a1 -= 0x16;
            a2 = 0x100;
            if (a1 == 0) {
                a2 = 0x200;
                if (D_801E43A0 & 2) {
                    a2 = 0x300;
                }
            }
            if (a1 == 3) {
                a2 = 0x400;
                if (D_801E43A0 & 8) {
                    a2 = 0x500;
                }
            }
            v1 = func_8012C658(0x51, a2 | a1, 0);
            if (v1 != 0) {
                *(s32 *)(v1 + 0x64) = *(s32 *)(a0 + 0xCC);
            }
        }
    }
}


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80187070(s32 arg0) {
    s32 self = arg0;
    s32 v1;

    v1 = func_8012C658(0x56, 5, self);
    if (v1 != 0) {
        *(s32 *)(v1 + 0xCC) = *(s32 *)(self + 0xCC);
    }
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018A7D8(u16 *a0, u16 *a1, s16 *a2, s32 a3);

/* D_80195B78 / D_80195B7A / D_80195B7C / D_80195B7E are each their own top-level data
 * symbol in asm/ov_SC02_005/data/tail.data.s (separate dlabel/enddlabel entries), but the
 * function indexes each with a 16-byte runtime stride (sll ...,4). Model each as an array
 * of a 16-byte-stride row so gcc emits the shift and keeps the relocation on the symbol
 * itself rather than folding an offset into a neighbour's %lo. */
typedef struct {
    s16 v;
    u8 pad[14];
} Row16_t;
extern Row16_t D_80195B78[];
extern Row16_t D_80195B7A[];
extern Row16_t D_80195B7C[];
extern Row16_t D_80195B7E[];

void func_801870BC(void *a0) {
    s32 v1;
    s32 v2;
    u16 a1arr[4];
    s16 a2arr[3];
    s16 idx;

    a1arr[0] = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x48) + 0x10;

    v1 = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x4C);
    a1arr[1] = v1;

    v2 = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x50);
    a1arr[3] = 0x3000;
    a1arr[2] = v2 - 0x10;

    if (*(s16 *)((u8 *)a0 + 0x70) == 3) {
        a1arr[1] = v1 - 0x60;
        a1arr[2] = v2 - 0x20;
    }

    idx = *(s16 *)((u8 *)a0 + 0x70);
    a2arr[0] = (D_80195B7A[idx].v - D_80195B78[idx].v) >> 1;

    idx = *(s16 *)((u8 *)a0 + 0x70);
    a2arr[1] = (D_80195B7E[idx].v - D_80195B7C[idx].v) >> 1;
    a2arr[2] = 0x20;

    func_8018A7D8((u16 *)((u8 *)a0 + 0xE8), a1arr, a2arr, 0);

    if (*(s16 *)((u8 *)a0 + 0x104) != 0) {
        if ((*(u16 *)((u8 *)a0 + 0xE8) & 3) == 0) {
            func_8002D4C8(0x4F4, 0);
        }
    }
}


extern void GsMapModelingData(u32 *);
extern u32 D_801BD9D4[];
extern u8 D_801961BE[];
extern u8 D_801961E6[];

void func_801871E4(void)
{
    u32 *p;
    s32 v;
    s32 i;

    p = D_801BD9D4;
    if (*p != 0) {
        do {
            GsMapModelingData((u32 *)((*p & 0x80FFFFFF) + 4));
            p++;
        } while (*p != 0);
    }
    for (v = -1, i = 0; i < 0x20; i += 8) {
        *(s16 *)&D_801961BE[i] = v;
        *(s16 *)&D_801961E6[i] = v;
    }
}


extern s32 D_801E43A0;
extern s32 D_801E4418[];
extern s32 D_801E4474[];
extern u16 D_80195B4A[];
extern u32 D_801BD9D4[];
extern s32 D_80195CA4[];

void func_80187280(s32 arg0, s32 arg1) {
    u16 var;
    u16 i;
    s32 *p;

    var = arg1;
    if (var < 14) {
        if (var != 0) {
            i = D_80195B4A[var];
            p = D_801E4418;
            if (i >= 0x16) {
                p = D_801E4474;
                i = i - 0x16;
            }
            arg1--;
            if (i == 5) {
                p[5] = 0x1000000;
            } else {
                p[i] = D_801BD9D4[arg1 & 0xFFFF];
            }
            *(s32 *)(arg0 + 0x58) = ((((arg1 & 0xFFFF) << 4) + (u32)D_80195CA4)) | 0x40000000;
        }
        D_801E43A0 |= 1 << var;
    }
}


extern u16 D_80195B4A[];
extern s32 D_801B82F4;
extern s32 D_801BB8DC;
extern u8 D_80195B64;
extern s32 D_801E4418[];
extern s32 D_801E4474[];
extern s32 D_801E43A0;

void func_80187348(s32 a0, s32 a1) {
    u32 a2;
    u16 idx;
    s32 *tab;
    s32 *base;
    s32 flags;

    a2 = a1 & 0xFFFF;
    if (a2 < 14) {
        if (a2 != 0) {
            tab = D_801E4418;
            idx = D_80195B4A[a2];
            base = &D_801B82F4;
            if (idx >= 22) {
                tab = D_801E4474;
                base = &D_801BB8DC;
                idx = idx - 22;
            }
            tab[idx] = base[idx];
            *(s32 *)(a0 + 0x58) = ((a2 << 4) + (s32)&D_80195B64) | 0x40000000;
        }
        flags = D_801E43A0;
        *(s32 *)(a0 + 0xDC) = 0;
        D_801E43A0 = flags & ~(1 << a1);
    }
}


#include "common.h"

/* func_801873FC -- ov_SC02_005 / ov_SC02_005_jr_80181D30
 * Fresh crack (mass lane, no matched exemplar; skeleton-similar seed func_801818D8 in
 * ov_SC03_006 shares the paired-point/func_8012DEB8-collision-test shape but is unrolled,
 * not looped -- structure only, not source).
 *
 * entity->0x58 is a tagged pointer into a box-like struct (min/max x/y/z), recovered with the
 * project's standard masked-pointer idiom (cookbook: src/ov_SC06_029/..._jr_8017C954.c func_80182BC8,
 * src/ov_SC01_077/..._jr_8012ACE0.c func_8012D098) -- entity->0x58 & 0xFFFFFFF | 0x80000000, with
 * %lo(D_8000000N) being literal byte offsets N (4,6,8,0xA,0xC,0xE), NOT real linker symbols.
 * The box fields are read via BOTH lhu (plain copy into a u16 local field: box->min_x/min_z/max_z)
 * and lh (the max_x-min_x width calc, signed) -- same field, different access width per call site,
 * so raw *(u16*)/(s16*) pointer casts are used rather than one consistently-typed struct.
 *
 * Loop tests 3 x-samples (min_x, min_x+step, min_x+2*step where step=(max_x-min_x)>>1) against two
 * fixed z planes (min_z via p1, max_z via p2) at both y=min_y and y=max_y, via func_8012DEB8
 * (fleet-modal (s32,(s32,s32,s32)), no TU-local declaration found -- decl_prior fleet, n=1442).
 * Returns 1 on the first nonzero collision result, else 0.
 */

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
} Vec4h_801873FC;

s32 func_801873FC(s32 a0) {
    Vec4h_801873FC p1;
    Vec4h_801873FC p2;
    u8 *box;
    s32 step;
    s32 x;
    s32 i;

    box = (u8 *)((*(u32 *)(a0 + 0x58) & 0xFFFFFFF) | 0x80000000);

    p1.x = *(u16 *)(box + 4);
    p1.z = *(u16 *)(box + 0xC);
    p2.x = *(u16 *)(box + 4);
    p2.z = *(u16 *)(box + 0xE);
    step = (u32)(*(s16 *)(box + 6) - *(s16 *)(box + 4)) >> 1;

    for (i = 0; i < 3; i++) {
        p1.y = p2.y = *(u16 *)(box + 8);
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
            return 1;
        }

        p1.y = p2.y = *(u16 *)(box + 0xA);
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
            return 1;
        }

        x = p1.x + step;
        p1.x = x;
        p2.x = x;
    }

    return 0;
}


extern s32 D_801963FC;
extern s32 func_80187560();

s32 func_80187508(s32 param_1)
{
    s32 ret;

    if (func_80187560(param_1, (s32)&D_801963FC, -8) == 0) {
        ret = func_80187560(param_1, (s32)&D_801963FC, -0x28);
    } else {
        ret = 1;
    }
    return ret;
}


#include "common.h"

typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
    /* 0x6 */ u16 w;
} Vec4h_80187560;

extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);

s32 func_80187560(s32 a0, s32 a1, s32 a2) {
    Vec4h_80187560 p1;
    Vec4h_80187560 p2;
    s32 result;

    p1.x = *(u16 *)(a0 + 0x6) + *(u16 *)(a1 + 0x4);
    p2.x = *(u16 *)(a0 + 0x6) + *(u16 *)(a1 + 0x6);
    p1.y = p2.y = a2 + (*(u16 *)(a0 + 0xA) + *(u16 *)(a1 + 0xA));

    p1.z = p2.z = *(u16 *)(a0 + 0xE) - 0x30;
    if (func_8012DF34(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.z = p2.z = *(u16 *)(a0 + 0xE) - 0x10;
    if (func_8012DF34(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.z = p2.z = *(u16 *)(a0 + 0xE) + 0x10;
    if (func_8012DF34(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.z = p2.z = *(u16 *)(a0 + 0xE) + 0x30;
    result = func_8012DF34(a0, (s32)&p1, (s32)&p2) != 0;

save:
    return result;
}


extern void func_8018B16C(s32 a0, s32 a1, s32 a2);

typedef struct { char b[8]; } Blob8_80187664;

extern Blob8_80187664 D_801E2EF0;

void func_80187664(s32 arg0)
{
    Blob8_80187664 tmp;

    tmp = D_801E2EF0;
    func_8018B16C(arg0, 6, (s32)&tmp);
}


#include "common.h"

/* D_801E2EF8: 8-byte, alignment-1 blob -- copied with lwl/lwr + swl/swr
 * (gcc's emit_block_move for align < 4), same idiom as the banked twin
 * func_8018A47C's D_801E2F28. */
typedef struct { char b[8]; } Blob8_801876B0;

extern Blob8_801876B0 D_801E2EF8;
extern u8 D_801202A0[];
extern void func_8018B16C(s32 a0, s32 a1, s32 a2);

void func_801876B0(s32 arg0)
{
    Blob8_801876B0 tmp;
    u8 *p;
    s32 i;

    tmp = D_801E2EF8;

    if (arg0 == 0) {
        for (i = 0, p = D_801202A0; i < 0x60; i++, p += 0x10C) {
            if (*(u16 *)p == 0x49 && *(s16 *)(p + 0x70) == 3) {
                arg0 = (s32)p;
                *(s16 *)(p + 0x104) = 1;
            }
        }
    }

    if (arg0 != 0) {
        func_8018B16C(arg0, 8, (s32)&tmp);
    }
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_80186304();
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186F14(void *a0);
extern u8 D_80195B2C[];

void func_80187768(void *a0) {
    s32 s0 = (s32)a0;
    u32 temp;
    s32 v0_val;

    func_8012B23C(s0);

    *(u32*)(s0 + 0xE8) |= 1;
    func_80186304((u8*)s0, 0, 0);

    temp = *(u32*)(s0 + 0xE8);
    if (temp & 0x2000) {
        *(u32*)(s0 + 0x1C) = 0x10;
    } else {
        *(u32*)(s0 + 0x1C) = 0x20;
    }

    v0_val = (s32)D_80195B2C | 0x40000000;
    *(u32*)(s0 + 0x58) = v0_val;
    *(s16*)(s0 + 0x5C) = 0;
    *(s16*)(s0 + 0xAE) = -1;

    func_8012AD44((s32*)s0, 1);
    func_80186F14((void*)s0);
}


extern void func_80182998(void);
extern void func_8018655C(s32 a0);
extern void func_801838A8(u8* a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012CE2C(s32 a0);
extern s32 func_8012CBCC(s32 a0);

void func_801877FC(s32 s0) {
    if (func_8012CE2C(s0) == 0) {
        ((void (*)(s32))func_8012CBCC)(s0);
    }

    if (*(u32 *)(s0 + 0xE8) & 0x60000) {
        ((void (*)(s32))func_80182998)(s0);
        return;
    }

    ((void (*)(s32))func_8018655C)(s0);

    if (*(s16 *)(s0 + 0x100) > 0) {
        *(s16 *)(s0 + 0x100) = *(s16 *)(s0 + 0x100) - 1;
    }

    if (((s32 (*)(s32))func_8012BEE8)(s0) != 0) {
        ((void (*)(u8 *))func_801838A8)((u8 *)s0);
    }

    if ((*(s32 *)(s0 + 0x94) == 4) || (*(s32 *)(s0 + 0x94) == 0xC)) {
        if (*(s16 *)(s0 + 0x98) == 1) {
            func_8002D4C8(0x4F7, 0);
        }
    }
}


void func_801878C0(void *arg0) {
    s32 s0 = (s32)arg0;

    func_80182810((void *)s0);
    if (*(u32 *)(s0 + 0xE8) & 0x2000) {
        *(u32 *)(s0 + 0x1C) = 0x18;
    } else {
        *(u32 *)(s0 + 0x1C) = 0x30;
    }
    func_801828D8((void *)s0);
    *(u32 *)(s0 + 0xE8) = *(u32 *)(s0 + 0xE8) & 0xFFFFFF7F;
}

extern void func_80182810();
extern void func_801828D8();


void func_8018791C(void *a0) {
    s32 s0 = (s32)a0;

    if (*(u32 *)(s0 + 0xE8) & 0x60000) {
        func_80182998();
        return;
    }

    func_80182918(s0);

    if (!(*(u32 *)(s0 + 0xE8) & 0x1000)) {
        if (*(s16 *)(s0 + 0x100) > 0) {
            *(s16 *)(s0 + 0x100) = *(s16 *)(s0 + 0x100) - 1;
        }
    }

    if (func_8018687C((void *)s0) || func_8018675C((void *)s0) || func_8012BEE8(s0)) {
        *(u32 *)(s0 + 0xE8) = *(u32 *)(s0 + 0xE8) & ~0x1000;
        func_801838A8((u8 *)s0);
    }
}


extern void func_80181900(void *a0);
    void func_801879DC(void *a0) {
        *(s32 *)((s32)a0 + 0xE8) |= 1;
        *(s16 *)((s32)a0 + 0xE0) = -1;
        ((void (*)(void *))func_80181900)(a0);
    }


extern void func_80181900(void*);
    void func_80187A0C(s32 *a0) {
        *(s32 *)((s32)a0 + 0xE8) &= ~1;
        ((void (*)(void))func_80181900)();
    }


extern void func_80186F58();
extern void func_80186304();
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80187A38(void *arg0) {
    *(u32 *)((s32)arg0 + 0xE8) |= 1;
    func_80186F58(arg0);
    func_80186304((u8 *)arg0, 0xE, 2);
    func_8012AD44((s32 *)arg0, 4);
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186F58(void *a0);

void func_80187A8C(void *arg0) {
    *(u32 *)((s32)arg0 + 0xE8) &= ~1;
    func_8012AD44((s32 *)arg0, 5);
    func_80186F58(arg0);
}


extern void func_8017DF00(void);
extern void func_80181F04(void *arg0);

void func_80187AD0(s32 arg0) {
    s32 temp_s0 = arg0;
    ((void (*)(void))func_80181F04)();
    *(s16 *)(temp_s0 + 0xDC) = 2;
    *(s16 *)(temp_s0 + 0xE0) = -1;
    ((void (*)(void))func_8017DF00)();
}


extern void func_80181F04(void *arg0);
extern void func_8017DF00(void);

void func_80187B0C(s32 arg0) {
    s32 temp_s0 = arg0;
    ((void (*)(void))func_80181F04)();
    *(s16 *)(temp_s0 + 0xDC) = 3;
    *(s16 *)(temp_s0 + 0xE0) = -1;
    ((void (*)(void))func_8017DF00)();
}


extern void func_80181F04(void *arg0);
extern void func_8017DF28(void);

void func_80187B48(s32 arg0) {
    s32 temp_s0 = arg0;
    ((void (*)(void))func_80181F04)();
    *(s16 *)(temp_s0 + 0xDC) = 1;
    ((void (*)(void))func_8017DF28)();
}


extern s32 func_80185D84(s32 a0);
extern s32 func_80181F70();
void func_80187B7C(int param_1)
{
    if (((int (*)(void))func_80185D84)() != 0) {
        ((void (*)(int))func_80181F70)(param_1);
    }
}


extern void func_80181FA8();
    void func_80187BB4(s32 arg0) {
        if (*(s16 *)((char *)arg0 + 0x98) == 0) {
            ((void (*)(void))func_80181FA8)();
        }
    }


extern void func_80181FE8();
    void func_80187BE4(s32 *a0) {
        if (*(s32 *)((char *)a0 + 0x94) == 0xB) {
            ((void (*)(void))func_80181FE8)();
        }
    }


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018A174(s32 a0);
extern void func_8018203C(s32 a0);

void func_80187C14(s32 a0) {
    s32 temp;

    func_8012AD80(a0);
    if (func_8012BEE8(a0) == 0) {
        temp = *(s32 *)(a0 + 0x1C);
        if (temp % 3 == 1) {
            func_8018A174(a0);
        }
    }
    if (*(s16 *)(a0 + 0xA) < -0xB00) {
        func_8018203C(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80182098();
void func_80187C9C(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_80182098)(param_1);
    }
}


extern s32 func_8012CBCC(s32 a0);
extern s32 func_801820E4(void *a0);
void func_80187CD4(int param_1)
{
    if (((int (*)(void))func_8012CBCC)() != 0) {
        ((void (*)(int))func_801820E4)(param_1);
    }
}


extern void func_801821C8(s32 *a0);
void func_80187D0C(s32 *a0) {
    *(s32 *)((char *)a0 + 0xE8) &= ~0x20;
    if (*(s32 *)((char *)a0 + 0x94) == 6) {
        func_801821C8(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80182284(s32 arg0);
extern void func_8018415C(void *a0);

void func_80187D4C(s32 param_1) {
    if (func_8012BEE8(param_1) != 0) {
        func_80182284(param_1);
        func_8018415C(*(void **)(param_1 + 0xD4));
    }
}




void func_80187D90(void *a0) {

    extern void (*D_80196250[])(void);
    D_80196250[*(u16 *)((s32)a0 + 0x34)]();
}


extern void func_80182998(void);
extern void func_801838A8(u8*);

void func_80187DCC(u8 *arg0) {
    if (*(u32 *)(arg0 + 0xE8) & 0x60000) {
        func_80182998();
        return;
    }

    if (!(*(u32 *)(arg0 + 0xE8) & 0x200)) {
        func_801838A8(arg0);
    }
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern u16 D_801E4BBC;

extern s32 func_80184CA4();
extern void func_801856E4(void);

void func_80187E18(u8 *arg0) {
    if (*(u16 *)(arg0 + 0x34) == 0) {
        if (D_801E4BBC == 2) {
            if (*(s32 *)(arg0 + 0x94) == 0xC) {
                if (*(s16 *)(arg0 + 0x98) == 1) {
                    func_80184CA4(*(s32 *)(arg0 + 0xD0));
                    *(u16 *)(arg0 + 0x5C) |= 0x200;
                }
            }
        } else {
            if (*(s32 *)(arg0 + 0x94) == 0xA) {
                if (*(s16 *)(arg0 + 0x98) == 1) {
                    func_8002D4C8(0xA2F, 0);
                }
            }
        }
        if (*(s16 *)(arg0 + 0x98) == 0) {
            (*(u16 *)(arg0 + 0x34))++;
            *(s32 *)(arg0 + 0x1C) = 0;
            *(s32 *)(arg0 + 0xE8) |= 0x10000;
        }
    } else {
        if (func_8012BEE8((s32)arg0) != 0) {
            func_801856E4();
            *(s32 *)(arg0 + 0x1C) = 0x180;
        }
    }
}



extern void func_8012CBF4(s32 a0);
    extern void func_80182E04();
    void func_80187F1C(void *a0) {
        if ((((s32 (*)(s32))func_8012CBF4)((s32)a0) & 0x2000) != 0) {
            ((void (*)(s32))func_80182E04)((s32)a0);
        }
    }



extern s32 D_801270C8;
extern void func_80182EB0(void);

void func_80187F58(void) {
    if (D_801270C8 == 22) {
        func_80182EB0();
    }
}


void func_80187F88(void) {
}



extern void func_8012CBF4(s32 a0);
    extern void func_80182EB0(void);
    void func_80187F90(void *a0) {
        if ((((s32 (*)(s32))func_8012CBF4)((s32)a0) & 0x2000) != 0) {
            ((void (*)(s32))func_80182EB0)((s32)a0);
        }
    }


extern s32 D_801270C8;
extern void func_80182E78(void *a0);
extern void func_80182DCC(void *a0);

void func_80187FCC(void *a0)
{
    s32 *p = &D_801270C8;

    if (*p == 22) {
        func_80182E78(a0);
    }
    if (*p == 20) {
        func_80182DCC(a0);
    }
}




void func_8018802C(void *a0) {

    extern void (*D_80196274[])(void);
    D_80196274[*(u16 *)((s32)a0 + 0x34)]();
}


extern void func_8012AD80(s32 a0);
extern void func_80182FAC();
extern s32 D_801270C8;

void func_80188068(void *a0) {
    func_8012AD80((s32)a0);
    if (D_801270C8 == 0x1F) {
        func_80182FAC((s32)a0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8018300C(void*);
extern u8 D_8019103C;

void func_801880AC(void *a0)
{
    *(u32 *)((u8 *)a0 + 0xE8) |= 0x4000;
    func_8012AD80((s32)a0);
    if (*(s16 *)((u8 *)a0 + 0xA) >= 0) {
        *(s16 *)((u8 *)a0 + 0xA) = 0;
        func_8013C9C4(&D_8019103C);
        ((void (*)(s32))func_8018300C)((s32)a0);
    }
}


extern s32 func_801830F4(s32 arg0, s32 a1);

void func_8018810C(void *a0) {
    func_801830F4((s32)a0, 1);
    if (func_8012BEE8((s32)a0) != 0) {
        func_80183060(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern u16 D_801E4398;

void func_80188150(void *a0) {
    s32 s0 = (s32)a0;

    func_8012BEE8(s0);
    if (*(s32 *)(s0 + 0x1C) == 1) {
        *(u16 *)(s0 + 0x76) = 0x1E;
        D_801E4398 = 0x1E;
    }
}


extern s32 func_801830F4(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183074(s32 *a0);

void func_80188194(s32 a0) {
    ((void (*)(s32 *, s32))func_801830F4)((s32 *) a0, 0);
    if ((*(u32 *) ((char *) a0 + 0x1C) & 3) == 0) {
        func_8002D4C8(0x504, 0);
    }
    if (func_8012BEE8(a0) != 0) {
        func_80183074((s32 *) a0);
    }
}


#include "common.h"





extern void func_80186178(s32 *a0);
extern void func_8012C218(void *a0);
extern s32 func_801830F4(s32, s32);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183160(void *a0);
extern void func_80019064(void *a0);
extern MainStruct *D_801E43A4;
extern s32 D_80062BC0;

void func_801881F4(s32 a0) {
    s32 s0 = a0;

    if (*(s32 *)(s0 + 0x1C) == 0x68) {
        *(s32 *)(s0 + 0xE8) |= 0x8000;
        func_80186178((s32 *)s0);
        if (D_801E43A4 != 0) {
            func_8012C218((void *)D_801E43A4);
        }
    }

    ((void (*)(void *, s32))func_801830F4)((void *)s0, 0);

    if (func_8012BEE8(s0) != 0) {
        func_80183160((void *)s0);
    } else if ((*(s32 *)(s0 + 0x1C) & 7) == 0) {
        func_80019064(&D_80062BC0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80183174(void *a0);
void func_801882A8(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_80183174)(param_1);
    }
}


void func_801882E0(void) {
}



void func_801882E8(void *a0) {

    extern void (*D_801962A0[])(void);
    D_801962A0[*(u16 *)((s32)a0 + 0x34)]();
}


#include "common.h"

extern void (*D_80196184[])(void);
extern s32 D_801961E0;
extern s32 D_801E4490;
extern s32 D_801E448C;

void func_80188324(s32 a0) {
    s32 v0, v1;
    s32 ret;

    ret = func_8012C354(a0, (s32)D_80196184);
    if (!ret)
        return;

    *(u8 *)(a0 + 0xC1) = 0;
    func_8012AD44((s32 *)a0, 1);

    func_8012B200(a0);

    /* Structure updates */
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x28) = (0xE0 << 16) | 0xE0;

    v0 = *(s32 *)(a0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    *(u16 *)(v0 + 0x2C) = v1 | 0x80;

    v0 = *(s32 *)(a0 + 0x20);
    *(s32 *)(v0 + 0x80) = (s32)&D_801961E0;

    *(u8 *)(a0 + 0x75) = 8;
    D_801E4490 = 0x1000000;
    D_801E448C = 0x1000000;
}


extern s32 *D_80126B78;
extern s16 D_801E43B8;
extern u16 D_801E43BC;

void func_801883C4(void)
{
    s32 p;
    s32 t;

    if (*(s16 *)&D_801E43BC != 0) {
        p = (s32)D_80126B78;
        t = *(u16 *)(p + 0x12) + *(u16 *)&D_801E43B8;
        *(u16 *)&D_801E43BC = 0;
        *(u16 *)(p + 0x12) = t;
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_80183D54(s32 a0);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern s32 D_80196348;
extern s32 D_8019637C;
extern s32 D_801963B8;
extern s32 D_801E44E0;
extern s32 *D_801D6D94;

void func_80188404(void *a0)
{
    if (func_8012C354((s32)a0, (s32)&D_80196348) == 0) {
        func_8012CAE4(a0);
        return;
    }
    *(s32 *)((s32)a0 + 0xC) = 0;
    *(s32 *)((s32)a0 + 0x8) = 0;
    *(s32 *)((s32)a0 + 0x4) = 0;
    func_80132784((s32)a0, *(s32 *)((s32)a0 + 0x64), 0);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x28) = 0xE000E0;
    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019637C;
    *(s32 *)((s32)a0 + 0xB4) = 0;
    *(u8 *)((s32)a0 + 0x75) = 8;
    *(s32 *)((s32)a0 + 0xC4) |= 2;
    func_80183D54((s32)a0);
    func_80132288(&D_801E44E0, &D_801963B8, (*(s32 *)&D_801D6D94));
}


#include "common.h"

extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8013240C(s32 a0, s32 a1, u32 a2);
extern s32 D_801E44E0;

void func_801884C8(s32 a0) {
    ((void (*)(s32))func_8013240C)((s32)&D_801E44E0);
    func_80132784(a0, *(s32 *)(a0 + 0x64), 0);
}


#include "common.h"

extern void func_8013240C(s32 a0, s32 a1, u32 a2);
extern void func_80183FCC();
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 D_801E44E0;
extern u32 D_801E44EC;
extern void (*D_80196338[])(void);

void func_8018850C(s32 *s0) {
    s32 *v1;

    v1 = (s32 *)*(s32 *)((u8 *)s0 + 0x20);
    *(u16 *)((u8 *)v1 + 0x2C) |= 1;
    ((void (*)(s32))func_8013240C)((s32)&D_801E44E0);

    if (D_801E44EC & 0x4000) {
        v1 = (s32 *)*(s32 *)((u8 *)s0 + 0x64);
        *(u32 *)((u8 *)v1 + 0xE8) |= 2;
        func_80183FCC((s32)s0);
        *(u8 *)((u8 *)s0 + 0xC1) = 0;
        *(u16 *)((u8 *)s0 + 0x5E) = 0;
        func_8012AD44(s0, 2);
        *(s32 *)((u8 *)s0 + 0x58) = (s32)&D_80196338 | 0x40000000;
        func_80132784((s32)s0, *(s32 *)((u8 *)s0 + 0x64), 0x15);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80184480(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern u8 D_801BB8F4[];
extern u8 D_8019640C[];
extern u8 D_80196448[];

void func_801885BC(void *a0) {
    s32 v0;
    register void *s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    s0 = a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        *(u32 *)D_8019640C = *(u32 *)D_801BB8F4;
        func_8001C214(*(s32 *)((u8 *)s0 + 0x20), (s32)D_8019640C);
        *(s32 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x28) = 0xE000E0;
        func_80184480((s32)s0);
        *(u8 *)((u8 *)s0 + 0xC0) = 1;
        *(s32 *)((u8 *)s0 + 0xB4) = 4;
        *(s32 *)((u8 *)s0 + 0xBC) = (s32)D_80196448;
        *(s16 *)((u8 *)s0 + 0xAE) = -1;
        *(u8 *)((u8 *)s0 + 0x75) = 8;
        *(u32 *)((u8 *)s0 + 0xC4) |= 2;
        *(u8 *)((u8 *)s0 + 0xC1) = 0;
        *(s32 *)((u8 *)s0 + 0xC) = 0;
        *(s32 *)((u8 *)s0 + 8) = 0;
        *(s32 *)((u8 *)s0 + 4) = 0;
        func_80132784((s32)s0, *(s32 *)(*(s32 *)((u8 *)s0 + 0x64) + 0xCC), 6);
    }
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_80188690(void *a0) {
    func_80132784((s32)a0, *(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xCC), 6);
}


void func_801886BC(void) {
}

#include "common.h"

extern s32 func_8012CBCC(s32 a0);
extern void func_8018AF58(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013C9C4(void *a0);
extern void func_80184D24(void *a0);
extern void (*D_80191060[])(void);

void func_801886C4(void *a0)
{
    if (func_8012CBCC((s32)a0) != 0) {
        func_8018AF58((s32)a0);
        func_8002D4C8(0x4EE, 0);
        func_8013C9C4(D_80191060);
        func_80184D24(a0);
    }
}


extern s32 D_801270C8;

void func_80188720(void *a0) {
    if (D_801270C8 == 31) {
        *(u16 *)((s32)a0 + 0x5C) |= 0x200;
    }
}


#include "common.h"

extern s32 D_801E43A0;
extern void func_80185060(s32 a0, s32 a1);

void func_8018874C(s32 arg0) {
    s16 idx;
    s32 flags;
    s32 st;

    idx = *(s16 *)(arg0 + 0x70);
    if (idx < 13) {
        flags = D_801E43A0;
        if (((flags >> (idx + 1)) & 1) != 0) {
            func_80185060(arg0, 0);
        }
    }
    st = *(s32 *)(*(s32 *)(arg0 + 0xCC) + 0xE8);
    if (st & 0x8000) {
        func_80185214(arg0);
    }
}


void func_801887CC(s32 arg0) {
    register s32 self __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    s16 var;

    self = arg0;
    var = *(s16 *)(self + 0x100);
    if (var != 0) {
        *(s16 *)(self + 0x100) = var - 1;
        func_801870BC(arg0);
    }

    if (*(s32 *)(*(s32 *)(self + 0xCC) + 0xE8) & 0x8000) {
        func_80185214(self);
    }
}


#include "common.h"

extern void func_80189F84(s32 arg0);
extern void func_8012AD80(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_801853CC(s32 a0);

void func_80188830(s32 a0) {
    s16 v0;
    void *v1;
    u16 hw;

    if (*(s16 *)((u8 *)a0 + 0x70) < 12) {
        v1 = *(void **)((u8 *)a0 + 0x20);
        *(u16 *)((u8 *)v1 + 0x14) += 0x300;

        v1 = *(void **)((u8 *)a0 + 0x20);
        *(u16 *)((u8 *)v1 + 0x10) += 0x100;

        hw = *(u16 *)((u8 *)a0 + 0x100);
        hw++;
        *(u16 *)((u8 *)a0 + 0x100) = hw;

        if ((hw & 3) == 0) {
            func_80189F84(a0);
        }

        func_8012AD80(a0);

        if (*(s16 *)((u8 *)a0 + 0xA) >= *(s16 *)((u8 *)a0 + 0x102)) {
            func_8012B200((u8 *)a0);
            func_801853CC(a0);
        }
    }
}


#include "common.h"

extern void func_8018A0E4(s32 arg0);
extern u16 D_800B99D8;

void func_801888EC(void *a0)
{
    if (*(s16 *)((u8 *)a0 + 0x70) < 12 && (D_800B99D8 & 0xF) == (*(s16 *)((u8 *)a0 + 0x70) & 0xF)) {
        func_8018A0E4((s32)a0);
    }
}


extern void func_80181900(void*);
    void func_8018893C(s32 arg0) {
        *(s32 *)(arg0 + 0xe8) &= ~1;
        ((void (*)(void))func_80181900)();
    }


extern void func_8012B23C(s32 a0);
extern void func_801822B4(s32 a0);

void func_80188968(s32 arg0)
{
    if (*(s16 *)(arg0 + 0x98) == 0)
    {
        func_8012B23C(arg0);
        if ((*(s16 *)(arg0 + 0xE0) < 0) && (*(s16 *)(arg0 + 0xDC) != 0))
        {
            *(u16 *)(arg0 + 0x34) = 0;
            return;
        }
        func_801822B4(arg0);
    }
}



extern void (*D_801964BC[])(void);

void func_801889D4(void *a0) {
    D_801964BC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80143994(s32 a0, s32 a1);

void *func_80188A10(void *a0) {
    void *r;
    void *v1;

    r = (void *)((s32 (*)(s32, s32))func_80143994)((s32)a0, 0x7FFF);
    if (r != 0) {
        v1 = *(void **)((u8 *)r + 0xCC);
        *(u16 *)((u8 *)r + 0) = 0x69;
        if (v1 != 0) {
            *(u8 *)((u8 *)v1 + 0x26) = 0xC8;
            *(u8 *)((u8 *)v1 + 0x25) = 0xC8;
            *(u8 *)((u8 *)v1 + 0x24) = 0xC8;
        }
    }
    return r;
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80188A5C(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 1);
    }


#include "common.h"

extern s32 func_8012D714(s32 param_1, u32 param_2);
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s32 func_8012CBCC(s32 a0);
extern void func_8018A658(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s16 D_80126CB8;
extern void func_8018AC10(s32 a0);

extern u8 D_8019103C;

void func_80188A7C(void *a0)
{
    if (func_8012D714((s32)a0, 2) != 0) {
        u16 *p96 = &D_80126B96;
        D_80126B98 = 10;
        *p96 |= 0x4000;
    }

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) < 0x400) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) =
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) + 0x100;
    }
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) + 0x40;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        if (func_8012CBCC((s32)a0) != 0) {
            func_8018A658((s32)a0);
            func_8013C9C4(&D_8019103C);
            *(s32 *)((s32)a0 + 0x48) = 0;
            *(s32 *)((s32)a0 + 0x10) = 0;
            *(s32 *)((s32)a0 + 0x14) = 0;
            *(s32 *)((s32)a0 + 0x18) = (s32)0xFFD80000;
            *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
            func_8002D4C8(0x4FC, 0);
        }
        break;
    case 1:
        func_8012AD80((s32)a0);
        if ((*(s16 *)((s32)a0 + 0xE) - D_80126CB8) < -0x180) {
            func_8018AC10((s32)a0);
        }
        break;
    }
}



extern void (*D_801964FC[])(void);

void func_80188BB4(void *a0) {
    D_801964FC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 func_80143970(s32 a0);

extern u8 D_80196544;
extern u8 D_80196578;
extern s32 D_80196514[];
extern s32 D_80196518[];
extern s16 D_80196534[];
extern s16 D_80196536[];

void func_80188BF0(void *a0)
{
    /* Target frame is 0x28 (vars=16) vs this body's natural 0x18 (vars=0) -- a 16-byte
     * orphan-slot gap (cookbook §162i1/§172) with no $sp reference to the excess in the
     * target .s. No candidate source expression accounts for it, so this is a dead pad
     * in declaration position, not a real local. */
    s32 pad[4];
    s32 idx;
    s32 v0;

    if (func_8012C354((s32)a0, (s32)&D_80196544) == 0) {
        return;
    }

    if (*(s16 *)((u8 *)a0 + 0x70) != 0) {
        *(s16 *)((u8 *)a0 + 0x5C) = 0;
    } else {
        s32 flags = *(s32 *)((u8 *)a0 + 0xC4);
        *(u8 *)((u8 *)a0 + 0xC0) = 1;
        *(s32 *)((u8 *)a0 + 0xBC) = (s32)&D_80196578;
        *(s32 *)((u8 *)a0 + 0xB4) = 0;
        *(u8 *)((u8 *)a0 + 0xC1) = 0;
        *(s16 *)((u8 *)a0 + 0xAE) = -1;
        *(u8 *)((u8 *)a0 + 0x75) = 0;
        *(s32 *)((u8 *)a0 + 0xC4) = flags | 2;
    }

    *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x28) = 0xE000E0;
    func_8012B23C((s32)a0);

    *(s32 *)((u8 *)a0 + 0x14) = 0xFFEC0000;

    idx = (*(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x100) & 1)
        + ((*(u16 *)((u8 *)a0 + 0x70) & 1) << 1);

    *(s32 *)((u8 *)a0 + 0x10) = D_80196514[idx * 2];
    *(s32 *)((u8 *)a0 + 0x18) = D_80196518[idx * 2];
    *(s16 *)((u8 *)a0 + 0xFC) = D_80196534[idx * 2];
    *(s16 *)((u8 *)a0 + 0xFE) = D_80196536[idx * 2];

    v0 = func_80143970((s32)a0);
    *(s32 *)((u8 *)a0 + 0xCC) = v0;
    *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = -0x200;
    func_8012AD50(a0);
}


#include "common.h"

extern s32 func_8012D714(s32 a0, u32 a1);
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s32 func_8012CBCC(s32 a0);
extern void func_8018A47C(s32 a0);
extern void (*D_80191060[])(void);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801439C0(u8 *a0);
extern void func_8012B200(u8 *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_80188D1C(s32 a0)
{
    s32 obj;
    s16 ang;
    s16 v;

    obj = *(s32 *)(a0 + 0xCC);
    if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) != *(s16 *)(a0 + 0xFE)) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) + *(u16 *)(a0 + 0xFC);
    }

    if (obj != 0) {
        v = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        if (v < 0) {
            ang = -v;
        } else {
            ang = v;
        }
        *(s16 *)(*(s32 *)(obj + 0xCC) + 0x18) = ang * 24 + 0x2000;
    }

    if (*(s16 *)(a0 + 0x70) == 0 && obj != 0 && ang == 0x400 &&
        func_8012D714(a0, 2) != 0) {
        D_80126B96 = 0x4002;
        D_80126B98 = 10;
    }

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_8012CBCC(a0) != 0) {
            *(s32 *)(a0 + 0x14) = (s32)0xFFF80000;
            *(u16 *)(a0 + 0x34) += 1;
            func_8018A47C(a0);
            func_8013C9C4(D_80191060);
            func_8002D4C8(0x4F9, 0);
            if (obj != 0) {
                func_801439C0((u8 *)obj);
                *(s32 *)(a0 + 0xCC) = 0;
            }
        }
        break;
    case 1:
        if (func_8012CBCC(a0) != 0) {
            *(u16 *)(a0 + 0x34) += 1;
            func_8012B200((u8 *)a0);
            if (*(s16 *)(a0 + 0x70) != 0) {
                *(s32 *)(a0 + 0x1C) = 0;
            } else {
                *(s32 *)(a0 + 0x1C) = 0x80;
            }
        }
        break;
    case 2:
        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x5C) &= 0xFDFF;
            func_8012AD50((void *)a0);
            *(s32 *)(a0 + 0x1C) = 0x18;
        }
        break;
    }
}


extern void func_80188F38(void);
    void func_80188F08(u8 *a0) {
        *(s8 *)(a0 + 0xC1) = 0;
        *(s8 *)(a0 + 0xC2) = 0;
        *(u16 *)(a0 + 0x5C) &= 0xFFFE;
        func_80188F38();
    }


#include "common.h"



extern Blk20 D_800AE620;
extern s32 *D_80126B78;
extern s32 D_801965A0;
extern void func_8012B21C(void *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80188F38(void)
{
    register s32 a0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus10)
    s32 self;
    Blk20 m;
    s32 p;

    self = a0;
    m = D_800AE620;
    *(u16 *)(self + 0x5C) = 0;
    func_8012B21C((void *)self);

    p = (s32)D_80126B78;
    RotMatrixY(*(s16 *)(p + 0x12), &m);
    func_800484EC((s32)&m, (s32)&D_801965A0, self + 0x10);
    func_8012AD44((s32 *)self, 3);
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_801892CC(s32 a0);
extern void func_8018A47C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012BE54(s32 a0);       /* canonical void -> cast at use */
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012C218(void *a0);

void func_80188FF0(s32 a0) {
    s32 v0;

    func_8012AD80(a0);
    v0 = func_801892CC(a0);

    if (*(s16 *)(a0 + 0x100) == 0 && v0 != 0) {
        *(s16 *)(a0 + 0x102) = 2;
        *(u16 *)(a0 + 0x100) += 1;
    } else if (*(s16 *)(a0 + 0x102) != 0) {
        if (--*(s16 *)(a0 + 0x102) == 0) {
            *(s32 *)(a0 + 0x1C) = 0x18;
            *(s16 *)(a0 + 0x34) = 3;
            *(s16 *)(a0 + 0x100) = -1;
            *(s32 *)(a0 + 0x10) = -(*(s32 *)(a0 + 0x10) >> 1);
            *(s32 *)(a0 + 0x18) = -(*(s32 *)(a0 + 0x18) >> 1);
            *(s32 *)(a0 + 0x14) += -0x80000;
        }
    }

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(s16 *)(a0 + 0xA) >= -0x7FF) {
            func_8018A47C(a0);
            *(s32 *)(a0 + 0x14) = -0x80000;
            *(u16 *)(a0 + 0x34) += 1;
            func_8002D4C8(0xA2E, 0);
        }
        break;
    case 1:
        if (*(s16 *)(a0 + 0xA) >= -0x7FF) {
            *(s32 *)(a0 + 0x48) = 0;
            *(u16 *)(a0 + 0x34) += 1;
        }
        break;
    case 2:
        if (((s32 (*)(s32))func_8012BE54)(a0) > 0x100000) {
            func_8012C218((void *)a0);
        }
        break;
    case 3:
        if (*(s16 *)(a0 + 0xA) >= -0x7FF) {
            func_8012B200((u8 *)a0);
        }
        if (*(s32 *)(a0 + 0x1C) & 1) {
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        } else {
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
        }
        if (func_8012BEE8(a0) != 0) {
            func_8012C218((void *)a0);
        }
        break;
    }
}



extern void (*D_801965B0[])(void);

void func_80189204(void *a0) {
    D_801965B0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 *D_80126B78;

void func_80189240(s32 a0)
{
    *(u16 *)(a0 + 0x5C) &= 0xFFFE;
    *(u16 *)(a0 + 0x104) = *(u16 *)((s32)D_80126B78 + 0x12);
}


extern s32 *D_80126B78;

void func_80189268(s32 a0)
{
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0;
    if (*(u16 *)(*(s32 *)(a0 + 0x64) + 0x100) & 1) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(a0 + 0x104) + *(u16 *)((s32)D_80126B78 + 0x12);
    } else {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(a0 + 0x104) - *(u16 *)((s32)D_80126B78 + 0x12);
    }
}


/* func_801892CC (ov_SC02_005 / ov_SC02_005_jr_80181D30.c, 127 ins) — MATCH.
 *
 * Fresh crack (mass lane). Sweep of the 0x60-entry / stride-0x10C D_801202A0
 * entity table: for every entry whose type word (+0x00) is 0x49, ray-test the
 * two transformed segments (o0->o1 at height D_801964F4, o2->o3 at height
 * D_801964F6) against it; on a hit, latch state 0x1D + the hit point.
 *
 * Three levers were load-bearing (all byte-verified):
 *  1. §176 giv-base: write EVERY entry access as an offset off the SINGLE
 *     pointer `p` (p+0x20 .. p+0xAE, including p+0x80). A source-level second
 *     pointer `q = p + 0x80` makes `*(s16*)q` a DIRECT use of q, which drops
 *     0x80 out of the giv candidate set — combine_givs then bases the giv at
 *     0x7E and keeps q alive as a 3rd induction pointer (129 ins, 69 off).
 *     With 0x80 in the set, gcc picks 0x80 as the representative on its own.
 *  2. The paired-store spelling `v0.a = v1.a = 0; v0.c = v1.c = 0; v0.b = 0;`
 *     reproduces the target's 0x18/0x10/0x1C/0x14/0x12 sh order exactly; three
 *     plain per-struct statements give source order and 5 mismatches.
 *  3. §S1 sched2 LUID: `count = 0; p = D_801202A0;` must sit AFTER the first
 *     func_8012F214 call — the block's leading run is emitted in ascending
 *     LUID (a0,a1,a2,count,lui,addiu,i), so any earlier position puts
 *     `move count,zero` in the bgez delay slot (4 off).
 *     ⚠ A `register s32 count __asm__("$21")` pin ALSO reaches the right
 *     allocation, but a hard-reg pseudo cannot be scheduled across the `jal`,
 *     so it re-pins count to the block head and freezes the residual at 4.
 *     Dropping the pin lets natural allocation land count in $s5 anyway.
 */
#include "common.h"

extern u8 D_801202A0[];
extern u16 D_801964F4;
extern u16 D_801964F6;
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern void func_8002D4C8(s32 a0, s32 a1);

typedef struct { s16 a, b, c, d; } SV892CC;

s32 func_801892CC(s32 arg0)
{
    SV892CC v0;
    SV892CC v1;
    SV892CC o0;
    SV892CC o1;
    SV892CC o2;
    SV892CC o3;
    u8 *p;
    u16 *hit;
    s32 i;
    s32 count;

    if (*(s16 *)(arg0 + 0x100) < 0) {
        return 0;
    }

    v0.a = v1.a = 0;
    v0.c = v1.c = 0;
    v0.b = 0;
    v1.b = D_801964F4;
    func_8012F214(arg0, (s32)&v0, (s32)&o0);
    count = 0;
    p = D_801202A0;

    func_8012F214(arg0, (s32)&v1, (s32)&o1);
    v1.b = D_801964F6;
    func_8012F214(arg0, (s32)&v0, (s32)&o2);
    func_8012F214(arg0, (s32)&v1, (s32)&o3);

    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0x49) {
            continue;
        }
        hit = func_80135260(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), (s16 *)&o0, (s16 *)&o1)
                  ? (u16 *)&o1
                  : (u16 *)0;
        if (func_80135260(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), (s16 *)&o2, (s16 *)&o3)) {
            hit = (u16 *)&o3;
        }
        if (hit == (u16 *)0) {
            continue;
        }
        if (*(s16 *)(p + 0xAE) == 0 && *(u16 *)(p + 0x5E) != 0x1D) {
            u16 f = *(u16 *)(p + 0x5C);
            if ((f & 0xC000) == 0x8000) {
                *(s16 *)(p + 0x5C) = f | 1;
                *(s16 *)(p + 0x60) = 8;
                *(s16 *)(p + 0x62) = 0;
                *(s16 *)(p + 0x5E) = 0x1D;
                *(s16 *)(p + 0x7C) = hit[0];
                *(s16 *)(p + 0x7E) = hit[1];
                *(s16 *)(p + 0x80) = hit[2];
            }
        }
        count++;
    }
    if (count != 0) {
        func_8002D4C8(0xA2D, 0);
    }
    return count;
}



extern void (*D_801965C0[])(void);

void func_801894C8(void *a0) {
    D_801965C0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_80189504(void *a0) {
    func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0xCC), *(u16 *)((u8 *)a0 + 0x70));

    *(s32 *)((u8 *)a0 + 0xDC) =
        (*(s32 *)(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x20) + 0x48) -
         *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x48)) >> 4;
    *(s32 *)((u8 *)a0 + 0xE0) =
        (*(s32 *)(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x20) + 0x4C) -
         *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x4C)) >> 4;
    *(s32 *)((u8 *)a0 + 0xE4) =
        (*(s32 *)(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x20) + 0x50) -
         *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x50)) >> 4;
}



extern void (*D_801965D4[])(void);

void func_801895A4(void *a0) {
    D_801965D4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801895E0(void *a0) {
    s32 *p;
    s32 n;
    s32 arr[3];

    p = *(s32 **)((s32)a0 + 0x2C);
    n = *(s16 *)((s32)a0 + 0x30) + 1;
    arr[0] = *(s32 *)((s32)p + 0xDC);
    arr[1] = *(s32 *)((s32)p + 0xE0);
    arr[2] = *(s32 *)((s32)p + 0xE4);

    *(s16 *)((s32)a0 + 0x06) =
        arr[0] * n + *(s32 *)(*(s32 *)((s32)p + 0x20) + 0x48) - (arr[0] >> 1);
    *(s16 *)((s32)a0 + 0x0A) =
        arr[1] * n + *(s32 *)(*(s32 *)((s32)p + 0x20) + 0x4C) - (arr[1] >> 1);
    *(s16 *)((s32)a0 + 0x0E) =
        arr[2] * n + *(s32 *)(*(s32 *)((s32)p + 0x20) + 0x50) - (arr[2] >> 1);
}


#include "common.h"

extern s32 func_8018B300(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern u8 *func_8012913C(s32 a0);
extern void func_801292C8(u8 *a0);
extern u16 D_801965DC[];
extern u16 D_801965DE[];
extern u16 D_801965E0[];
extern u16 D_801965E2[];
extern u8 D_801E44F8[];

void func_8018968C(void *a0)
{
    s32 arr[12];
    s32 id;
    s32 err;
    s32 flag;
    s32 i;
    s32 c1b8;
    s32 t;
    s32 disp;
    s32 base;

    id = *(s16 *)((u8 *)a0 + 0x102) = func_8018B300();
    err = 0;
    *(s32 *)((u8 *)a0 + 0xC) = 0;
    *(s32 *)((u8 *)a0 + 0x8) = 0;
    *(s32 *)((u8 *)a0 + 0x4) = 0;
    *(s16 *)((u8 *)a0 + 0x100) = *(u16 *)((u8 *)a0 + 0x70) >> 8;
    *(u16 *)((u8 *)a0 + 0x70) = *(u8 *)((u8 *)a0 + 0x70);

    if (id < 0) {
        err = 1;
    } else {
        if (*(s16 *)((u8 *)a0 + 0x100) < 2) {
            *(s16 *)((u8 *)a0 + 0xFE) = 4;
            flag = 0;
        } else {
            *(s16 *)((u8 *)a0 + 0xFE) = 1;
            flag = 1;
        }
        for (i = 0; i < *(s16 *)((u8 *)a0 + 0xFE); i++) {
            t = (s32)func_8012913C(9);
            arr[i] = t;
            if (t != 0) {
                *(s16 *)(*(s32 *)(t + 0x20) + 0x1E) = flag;
            } else {
                err++;
            }
        }
    }

    c1b8 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = c1b8;
    if (c1b8 == 0) {
        err++;
    }

    if (err != 0) {
        for (i = 0; i < *(s16 *)((u8 *)a0 + 0xFE); i++) {
            if (arr[i] != 0) {
                func_801292C8((u8 *)arr[i]);
            }
        }
        func_8012CAE4(a0);
        return;
    }

    func_8001C2C4(c1b8);

    *(s16 *)((u8 *)a0 + 0x6) = D_801965DC[*(s16 *)((u8 *)a0 + 0x100) * 4];
    *(s16 *)((u8 *)a0 + 0xA) = D_801965DE[*(s16 *)((u8 *)a0 + 0x100) * 4];
    *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x10) = D_801965E0[*(s16 *)((u8 *)a0 + 0x100) * 4];
    *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = D_801965E2[*(s16 *)((u8 *)a0 + 0x100) * 4];

    i = 0;
    if (*(s16 *)((u8 *)a0 + 0xFE) > 0) {
        disp = id << 7;
        base = (s32)D_801E44F8;
        do {
            if (i == 0) {
                *(s32 *)(arr[0] + 0x2C) = (s32)a0;
            } else {
                *(s32 *)(arr[i] + 0x2C) = 0;
            }
            *(s32 *)(arr[i] + 0x34) = disp + base;
            base += 0x20;
            i++;
        } while (i < *(s16 *)((u8 *)a0 + 0xFE));
    }

    *(s16 *)((u8 *)a0 + 0xFC) = 0;
    *(u16 *)((u8 *)a0 + 0x2) += 1;
}


#include "common.h"

extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012C218(void *a0);
extern void func_80189B30(s32 a0);
extern u8 D_801E44F0[];
extern u8 D_801E44F8[];

typedef struct { u32 w[8]; } Blk32_801898F4;

void func_801898F4(void *a0) {
    s32 i;
    u8 *base;
    u8 *p;
    s32 v0;

    if (*(s16 *)((u8 *)a0 + 0xFC) == 0) {
        for (i = 0; i < *(s16 *)((u8 *)a0 + 0xFE); i++) {
            *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x2C) &= ~1;
            switch (*(s16 *)((u8 *)a0 + 0x100)) {
            case 0:
                *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = i * 0x400;
                break;
            case 1:
                *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = i * 0x400;
                *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) += 0x200;
                break;
            }
            func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0x64), *(u16 *)((u8 *)a0 + 0x70));
            base = D_801E44F8;
            p = base + *(s16 *)((u8 *)a0 + 0x102) * 128;
            *(Blk32_801898F4 *)(p + i * 32) =
                *(Blk32_801898F4 *)((u8 *)(*(s32 *)((u8 *)a0 + 0x20)) + 0x34);
        }
        if (*(s16 *)((u8 *)a0 + 0x100) == 0) {
            *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) += 0x200;
            *(u16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x2C) &= ~1;
            func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0x64), *(u16 *)((u8 *)a0 + 0x70));
            v0 = *(u16 *)((u8 *)a0 + 0x104) + 1;
            *(u16 *)((u8 *)a0 + 0x104) = v0;
            if ((s32)(s16)v0 < 0xC) {
                if (*(s16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xFC) != 0) {
                    func_80189B30((s32)a0);
                }
            }
        }
    } else {
        D_801E44F0[*(s16 *)((u8 *)a0 + 0x102)] = 0;
        func_8012C218(a0);
    }
}



extern void (*D_8019660C[])(void);

void func_80189AF4(void *a0) {
    D_8019660C[*(u16 *)((s32)a0 + 0x2)]();
}


extern u16 D_80126B62;
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u8 D_80126C38;
extern u8 D_80126C40;
extern u16 D_80126B96;
extern s16 D_80126B9A;
extern s16 D_80126B98;
extern u16 D_80126B94;

/* D_801E2F00 is an 8-byte, alignment-1 blob copied with lwl/lwr (gcc's
 * emit_block_move for align < 4).  Both its shape declaration and its
 * `extern` live in BLOCK scope on purpose (cookbook §100 / §65g): this TU
 * already introduces its own anonymous 8-byte shape for the same global
 * further down the file, and a file-scope copy here collides with it --
 * while merely renaming the shape at file scope only trades that collision
 * for a conflicting-types error on the global itself.  Block scope keeps
 * both declarations draft-local and is byte-neutral. */
void func_80189B30(s32 arg0)
{
    typedef struct { char b[8]; } Blob8_80189B30;
    extern Blob8_80189B30 D_801E2F00;
    Blob8_80189B30 blob;
    s32 sub;
    s32 lim;
    s32 dx;
    s32 dy;

    blob = D_801E2F00;
    sub = *(s32 *)(arg0 + 0x20);
    if ((s16)((u16)D_80126B62 - *(s32 *)(sub + 0x4C)) >= -0x20) {
        lim = *(s16 *)(arg0 + 0x104) * 8 + 0x10;
        dx = (s16)((u16)D_80126B5E - *(s32 *)(sub + 0x48));
        if (dx >= -(s16)lim && dx <= (s16)lim) {
            dy = (s16)((u16)D_80126B66 - *(s32 *)(sub + 0x50));
            if (dy >= -(s16)lim && dy <= (s16)lim) {
                *(Blob8_80189B30 *)&D_80126C38 = blob;
                *(Blob8_80189B30 *)&D_80126C40 = blob;
                D_80126B96 = 0x4005;
                D_80126B9A = 0;
                D_80126B98 = 5;
                D_80126B94 |= 1;
            }
        }
    }
}



extern void (*D_801966A0[])(void);

void func_80189C90(void *a0) {
    D_801966A0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801966B8[])(void);

void func_80189CCC(void *a0) {
    D_801966B8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196760[])(void);

void func_80189D08(void *a0) {
    D_80196760[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801967C4[])(void);

void func_80189D44(void *a0) {
    D_801967C4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801967CC[])(void);

void func_80189D80(void *a0) {
    D_801967CC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196814[])(void);

void func_80189DBC(void *a0) {
    D_80196814[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196868[])(void);

void func_80189DF8(void *a0) {
    D_80196868[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern u16 D_800B99DC;

void func_80189E34(s32 arg0, s32 arg1)
{
    register u8 *s2 __asm__("$18") = (u8 *)arg0;  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus10)
    u8 *s1;
    s32 raw;
    s32 s0;
    s16 v[4];
    u16 out[4];
    s32 obj;
    s16 flagval;

    raw = *(s32 *)(s2 + 0x58);
    s0 = 0;
    if (raw != 0) {
        s0 = (raw & 0xFFFFFFF) | 0x80000000;
    }

    s1 = func_8012913C(0x18);
    if (s1 != NULL && s0 != 0) {
        v[0] = 0;
        v[1] = *(u16 *)((u8 *)s0 + 8);
        v[2] = 0;

        func_8004914C((void *)(*(s32 *)(s2 + 0x20) + 0x34));
        func_800491AC((void *)(*(s32 *)(s2 + 0x20) + 0x34));

        RotTransSV(v, v, out);

        obj = *(s32 *)(s1 + 0x20);
        *(s16 *)(s1 + 6) = v[0];
        *(s16 *)(s1 + 0xA) = v[1];
        *(s16 *)(s1 + 0xE) = v[2];
        *(u16 *)(obj + 0x2C) = 0xC020;

        if (D_800B99DC & 1) {
            flagval = -0x2000;
            obj = *(s32 *)(s1 + 0x20);
            *(s16 *)(obj + 0x1C) = flagval;
        } else {
            obj = *(s32 *)(s1 + 0x20);
            flagval = 0x2000;
            *(s16 *)(obj + 0x1C) = flagval;
        }
        *(s16 *)(obj + 0x1A) = flagval;
        *(s16 *)(obj + 0x18) = flagval;
    }
}


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189F44(s32 arg0) {
        ((void (*)(s32, s32))func_80132EF4)(arg0, 0x16);
    }


extern u8 *func_8012913C(s32 a0);
    void func_80189F64(void) {
        ((void (*)(s32))func_8012913C)(0x15);
    }


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189F84(s32 arg0) {
        ((void (*)(s32, s32))func_80132EF4)(arg0, 0xC);
    }


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189FA4(void *a0) {
        ((void (*)(void *, int))func_80132EF4)(a0, 0x13);
    }


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

typedef struct { s32 w[4]; } Blk16_801E2F08;

extern Blk16_801E2F08 D_801E2F08;
extern Blk20 D_800AE620;

void func_80189FC4(s32 a0) {
    Blk20 localMat;
    Blk16_801E2F08 blk16;
    s32 i;
    u8 *s0;

    blk16 = D_801E2F08;

    for (i = 0; i < 8; i++) {
        s0 = func_8012913C(0xC);
        if (s0 != NULL) {
            func_80129350((s32)s0, a0);
            *(s16 *)(s0 + 0x34) = -1;
            *(u16 *)(s0 + 0x6) -= 0x40;
            *(u16 *)(s0 + 0xA) -= 0x40;
            localMat = D_800AE620;
            RotMatrixY(i << 9, &localMat);
            func_800484EC((s32)&localMat, (s32)&blk16, (s32)(s0 + 0x10));
        }
    }
}


extern u8 *func_8012913C(s32 a0);

void func_8018A0E4(s32 arg0)
{
    u8 *ptr;
    s32 val;

    ptr = func_8012913C(0xC);
    if (ptr != NULL) {
        *(u16 *)(ptr + 0x6) = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x48) + 0x50;
        *(u16 *)(ptr + 0xA) = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4C) - 0x40;
        val = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x50);
        *(u32 *)(ptr + 0x14) = 0xFFF00000;
        *(u32 *)(ptr + 0x18) = 0;
        *(u32 *)(ptr + 0x10) = 0;
        *(s16 *)(ptr + 0x34) = -0x5000;
        *(u16 *)(ptr + 0xE) = val;
    }
}


void func_8018A174(s32 arg0) {
    u8 *ptr;
    s32 i;
    s16 val;

    i = 0;
    val = 0x4000;
    do {
        ptr = func_8018A30C(arg0, i);
        if (ptr != NULL) {
            *(s16 *) (ptr + 0x34) = val;
        }
        i++;
    } while (i < 4);
}


#include "common.h"

/* File-local mirror types: match_one compiles standalone with -Iinclude
 * only, so the TU's real Blk20 (src/shared/engine_types.h) is not
 * reachable here. These mirror the exact byte layout (same pattern as
 * the already-banked func_8018AF58/func_8018A4C4 in this TU).
 * DECL RECONCILIATION (§183 TYPE-adopted-TU, wave Z): the Blk20 typedef is
 * spelled with the AMBIENT name and the exact engine_types.h body, because
 * this TU already declares `extern Blk20 D_800AE620;` at file scope above
 * the splice point (lines 3664/5193/5527) and any private struct name there
 * is a hard `conflicting types` error — block-scoping it errors too (tested
 * against the pinned cc1).  canon_sig_reconcile strips a draft typedef whose
 * name AND body match engine_types.h, so the duplicate definition disappears
 * at bank time and the ambient Blk20 is used. */
typedef struct { s32 w[4]; } Blk16_8018A1D8;


extern Blk16_8018A1D8 D_801E2F18;
extern Blk20 D_800AE620;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern u8 *func_8018A30C(s32 a0, s32 a1);

void func_8018A1D8(s32 a0)
{
    Blk16_8018A1D8 fixedVec;
    s32 outVec[3];
    Blk20 localMatrix;
    s32 i, j;
    u8 *p;

    fixedVec = D_801E2F18;

    for (i = 0; i < 8; i++) {
        localMatrix = D_800AE620;
        RotMatrixY(i << 9, &localMatrix);
        func_800484EC((s32)&localMatrix, (s32)&fixedVec, (s32)outVec);

        for (j = 0; j < 4; j++) {
            p = func_8018A30C(a0, j);
            if (p != NULL) {
                *(s32 *)(p + 0x10) = outVec[0];
                *(s32 *)(p + 0x14) = outVec[1];
                *(s32 *)(p + 0x18) = outVec[2];
            }
        }
    }
}


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);

u8 * func_8018A30C(s32 a0, s32 a1) {
    u8 *s0;

    s0 = func_8012913C(0xC);
    if (s0 != NULL) {
        func_80129350((s32)s0, a0);
        if (a1 & 1) {
            *(u16 *)(s0 + 0x6) += 0x68;
        } else {
            *(u16 *)(s0 + 0x6) -= 0x68;
        }
        if (a1 & 2) {
            *(u16 *)(s0 + 0xE) += 0x68;
        } else {
            *(u16 *)(s0 + 0xE) -= 0x68;
        }
    }
    return s0;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

void func_8018A3B4(void *a0) {
    u8 *v1;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            v1 = (u8 *)func_80132EF4((s32)a0, 0xC);
            if (v1 != NULL) {
                *(u16 *)(v1 + 6) = (i != 0) ? *(u16 *)(v1 + 6) + 0x68 : *(u16 *)(v1 + 6) - 0x68;
                *(u16 *)(v1 + 0xE) = (j != 0) ? *(u16 *)(v1 + 0xE) + 0x82 : *(u16 *)(v1 + 0xE) - 0x1A;
                *(u16 *)(v1 + 0xA) -= 0x10;
            }
        }
    }
}


#include "common.h"

/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern Blob8_8018A47C D_801E2F28;
extern void func_8018A6A0();

void func_8018A47C(s32 a0) {
    Blob8_8018A47C tmp;

    tmp = D_801E2F28;
    func_8018A6A0(a0, &tmp);
}


#include "common.h"

/* Local idiom types (match_one compiles standalone with -Iinclude only, so
 * types normally sourced from src/shared/engine_types.h are kept file-local
 * here, mirroring the already-banked func_8018AF58 in this TU). */

/* D_801E2F30: 8-byte, alignment-1 blob -- copied with lwl/lwr + swl/swr
 * (gcc's emit_block_move for align < 4). Holds 3 x u16 (+ pad). */
typedef struct { char b[8]; } Blob8_8018A4C4;

/* D_801E2F38: 16-byte, word-aligned blob -- copied with plain lw/sw. */
typedef struct { s32 w[4]; } Blk16_8018A4C4;

/* (*(Blk20_8018A4C4 *)&D_800AE620): 32-byte MATRIX-shaped blob (9 x s16 rot + pad + 3 x s32 trans),
 * copied with plain lw/sw -- same shape as the TU's existing Blk20. */
typedef struct { s32 w[8]; } Blk20_8018A4C4;

extern Blob8_8018A4C4 D_801E2F30;
extern Blk16_8018A4C4 D_801E2F38;
extern Blk20 D_800AE620;

extern u8 *func_8012913C(s32 a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018A4C4(s32 a0)
{
    Blk20_8018A4C4 localMat;
    s32 pad[4];
    Blob8_8018A4C4 blobA;
    Blk16_8018A4C4 blobB;
    s32 i;
    u8 *s0;

    blobA = D_801E2F30;
    blobB = D_801E2F38;

    /* gte_SetTransMatrix(&((SomeObj *)a0->0x20)->mat34) -- ctc2 into the GTE
     * translation-vector control regs (5,6,7) from a MATRIX's t[0..2], which
     * live at offset 0x34+0x14/0x18/0x1c inside the object pointed to by
     * a0's field 0x20. Written as raw asm: the target's .s marks these ctc2
     * lines "handwritten instruction" (not a normal codegen mnemonic). */
    __asm__ __volatile__(
        "lw $12, 20(%0)\n"
        "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n"
        "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n"
        "ctc2 $14, $7\n"
        :
        : "r"((u8 *)*(s32 *)(a0 + 0x20) + 0x34)
        : "$12", "$13", "$14", "memory"
    );  // !FAKE: gte direct — clobbers ['memory'] (gte_SetTransMatrix_m) beyond Sony's (P36 T5 gte1)

    for (i = 0; i < 8; i++) {
        s0 = func_8012913C(0xC);
        if (s0 != NULL) {
            *(u16 *)(s0 + 0x6) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) + *(u16 *)&blobA.b[0];
            *(u16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) + *(u16 *)&blobA.b[2];
            *(u16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) + *(u16 *)&blobA.b[4];

            localMat = (*(Blk20_8018A4C4 *)&D_800AE620);
            RotMatrixY(i << 9, &localMat);
            func_800484EC((s32)&localMat, (s32)&blobB, (s32)(s0 + 0x10));
        }
    }
}



/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern void func_8018A6A0();

void func_8018A658(s32 a0) {

    extern Blob8_8018A47C D_801E2F48;
    Blob8_8018A47C tmp;

    tmp = D_801E2F48;
    func_8018A6A0(a0, &tmp);
}


void func_8018A6A0(s32 a0, u16 *a1)
{
    u8 *s0 = (u8 *)a0;
    u16 *s1 = a1;
    u16 vec0[4];
    u16 counter;
    s32 res[3];
    s32 flags;
    u8 *puVar;

    func_8012B2CC(a0);

    gte_SetRotTransMatrix((u8 *)*(s32 *)(s0 + 0x20) + 0x34);

    vec0[2] = 0;
    vec0[0] = 0;
    vec0[1] = counter = *s1;

    goto test;
body:
    puVar = func_8012913C(0xC);
    if (puVar != 0) {
        __asm__ __volatile__(
            "lwc2 $0, 0(%0)\n"
            "lwc2 $1, 4(%0)\n"
            "nop\n"
            "nop\n"
            "mvmva 1, 0, 0, 0, 0\n"
            : : "r"(vec0) : "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldv0+gte_rtv0tr_m) beyond Sony's (P36 T5 gte1)
        gte_stlvnl(res);
        gte_stflg(&flags);
        *(u16 *)(puVar + 6) = (u16)res[0];
        *(u16 *)(puVar + 0xA) = (u16)res[1];
        *(u16 *)(puVar + 0xE) = (u16)(res[2] - 8);
    }
    {
        register u16 tmp __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)
        counter = vec0[1];
        tmp = *(u16 *)(s1 + 2);
        counter += tmp;
        vec0[1] = counter;
    }
test:
    if ((s16)counter < *(s16 *)(s1 + 1)) goto body;
}


void func_8018A7D0(void) {
}

#include "common.h"

extern u8 *func_8012913C(s32 a0);

void func_8018A7D8(u16 *a0, u16 *a1, s16 *a2, s32 a3) {
    u8 *s0;
    s16 mask;
    s32 pad[2];

    mask = (1 << a3) - 1;
    if ((*a0 & mask) == 0) {
        s0 = func_8012913C(0xD);
        if (s0 != 0) {
            *(s16 *)(s0 + 0x6) = a1[0] + rand() % (a2[0] * 2) - a2[0];
            *(s16 *)(s0 + 0xA) = a1[1] + rand() % (a2[1] * 2) - a2[1];
            {
                s32 r = rand();
                s32 t = a2[2];
                s32 base = a1[2];
                *(s32 *)(s0 + 0x18) = 0;
                *(s32 *)(s0 + 0x14) = 0;
                *(s32 *)(s0 + 0x10) = 0;
                *(s16 *)(s0 + 0xE) = base + r % (t * 2) - t;
            }
            *(s16 *)(s0 + 0x34) = a1[3];
        }
    }
    *a0 = *a0 + 1;
}


#include "common.h"

extern s32 func_8012C51C(void *a0, s32 a1);
extern s16 D_80195AC6[];
extern u16 D_80195AD6;
extern s32 D_801E4A58[];

typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} LocalStruct_8018A968;

/* register pins reproduce the target's density-priority regalloc order (cookbook, banked
 * twin md_SC07_004:func_801AD7EC): pos/idx are read+written every iteration (highest density)
 * -> $s0/$s1; p0/p1/i/tab are read/written once per iteration -> $s2/$s3/$s4/$s6; self is the
 * cross-call-live copy of a0 -> $s5. Statement order mirrors the target's prologue schedule. */
void func_8018A968(s32 a0)
{
    s32 pos;
    s32 idx;
    s32 *p0;
    s32 *p1;
    s32 i;
    s32 self = a0;
    u16 *tab;
    LocalStruct_8018A968 local;
    s32 v0;
    s32 v1;
    s32 *pbase;
    u16 tmp;

    i = 0;
    tab = &D_80195AD6;
    pbase = D_801E4A58;
    p1 = pbase + 1;
    idx = 0;
    p0 = pbase;

    tmp = *(u16 *)D_80195AC6;

    local.field_2 = -0x8C0;
    local.field_6 = 0x57;
    local.field_A = 0;
    local.field_8 = 0;
    local.field_E = 0;
    local.field_10 = 0;

    pos = tmp - 0xA8;

    for (; i < 6; i++) {
        v0 = tab[0];
        local.field_4 = pos;
        v0 = v0 + 0xE4;
        local.field_0 = v0;
        v1 = func_8012C51C(&local, 0);
        *p0 = v1;
        if (v1 != 0) {
            *(s32 *)(v1 + 0x64) = self;
            *(s16 *)(v1 + 0x100) = idx;
        }

        v0 = tab[-1];
        local.field_4 = pos;
        v0 = v0 - 0x114;
        local.field_0 = v0;
        v1 = func_8012C51C(&local, 0);
        *p1 = v1;
        if (v1 != 0) {
            *(s32 *)(v1 + 0x64) = self;
            *(s16 *)(v1 + 0x100) = idx + 1;
        }

        pos += 0x150;
        p1 += 2;
        idx += 2;
        p0 += 2;
    }
}


extern s32 D_801E4A84;

void func_8018AA88(void) {
    s32 i;
    s32 *ptr;

    i = 11;
    ptr = &D_801E4A84;
    do {
        *ptr = 0;
        ptr--;
    } while (--i >= 0);
}


extern s32 D_801E4A58[];
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018AAAC(void) {
    s32 *p;
    s32 i;
    s32 ent;

    i = 0;
    p = D_801E4A58;
    do {
        ent = *p;
        if (ent != 0 && *(u16 *)(ent + 2) == 2) {
            func_80132784(ent, *(s32 *)(ent + 0x64), *(u16 *)(ent + 0xFE));
            *(s16 *)(ent + 6) = *(s32 *)(*(s32 *)(ent + 0x20) + 0x48);
            *(s16 *)(ent + 0xA) = *(s32 *)(*(s32 *)(ent + 0x20) + 0x4C);
            *(s16 *)(ent + 0xE) = *(s32 *)(*(s32 *)(ent + 0x20) + 0x50);
            func_8012B23C(ent);
            *(s32 *)(ent + 0x10) = 0x100000;
            *(s32 *)(ent + 0x14) = 0xFFE00000;
            *(s32 *)(ent + 0x18) = 0xFFFC0000;
            *(s32 *)(ent + 0x1C) = 0x20;
            func_8012AD44((s32 *)ent, 5);
        }
        i++;
        p++;
    } while (i < 12);
}


#include "common.h"

extern void func_8012C218(void *a0);
extern s32 D_801E4A58[];

void func_8018AB84(void) {
    s32 *p;
    s32 i;
    s32 val;

    i = 0;
    p = D_801E4A58;
    do {
        val = *p;
        if (val != 0) {
            *p = 0;
            func_8012C218((void *)val);
        }
        i++;
        p++;
    } while (i < 12);
}


extern s32 D_801E4A58[];

void *func_8018ABE0(s32 a0)
{
    if ((u32)(a0 & 0xFFFF) < 12) {
        return D_801E4A58[(s16)a0];
    }
    return 0;
}


extern void func_8012C218(void *a0);
extern s32 D_801E4A58[];

void func_8018AC10(s32 a0)
{
    D_801E4A58[*(s16 *)((u8 *)a0 + 0x100)] = 0;
    func_8012C218(a0);
}


s32 func_8018AC48(s32 a0) {
    extern s32 D_801E4A58[];
    s32 i;
    s32 *p;
    s32 ent;

    for (i = 0, p = D_801E4A58; i < 12; i++, p++) {
        ent = *p;
        if (ent == 0) {
            continue;
        }
        if (*(s16 *)(ent + 0xFC) != 0) {
            continue;
        }
        if ((u16)(*(u16 *)(a0 + 0xE) - *(u16 *)(ent + 0xE) - 0xC1) < 0xFF) {
            return i;
        }
    }
    return -1;
}


extern s32 D_801E4A58[];

s32 func_8018ACB4(void *a0) {
    s32 i;
    s32 *p;
    s32 ent;

    for (i = 0, p = D_801E4A58; i < 12; i++, p++) {
        ent = *p;
        if (ent == 0) {
            continue;
        }
        if (*(s16 *)(ent + 0xFC) != 0) {
            continue;
        }
        if ((u16)(*(u16 *)(ent + 0xE) - *(u16 *)(a0 + 0xE) - 0x81) < 0x1F) {
            return i;
        }
    }
    return -1;
}


extern s32 D_801E4A58[];

s32 func_8018AD20(s32 a0) {
    s32 i;
    s32 *p;
    s32 ent;
    s32 res;

    for (i = 0, p = D_801E4A58; i < 6; i++, p += 2) {
        res = i * 2;
        ent = *p;
        if (ent == 0) {
            continue;
        }
        if (*(s16 *)(ent + 0xFC) != 0) {
            continue;
        }
        if ((u16)(*(u16 *)(a0 + 0xE) - *(u16 *)(ent + 0xE) + 3) < 7) {
            return res;
        }
    }
    return -1;
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8018A4C4(s32 a0);
extern s32 D_801E4A58[];

void func_8018AD8C(s32 arg0, s32 arg1)
{
    s32 s0 = D_801E4A58[arg0];

    if (s0 != 0) {
        *(s16 *)(s0 + 0xFE) = arg1;
        *(s32 *)(s0 + 0xC) = 0;
        *(s32 *)(s0 + 8) = 0;
        *(s32 *)(s0 + 4) = 0;
        *(s16 *)(s0 + 0xFC) = 1;
        func_8012AD44((s32 *)s0, 2);
        func_8018A4C4(s0);
    }
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 D_801E4A58[];

void func_8018ADF0(s32 arg0) {
    s32 s0 = D_801E4A58[arg0];

    if (s0 != 0) {
        func_80132784(s0, *(s32 *)(s0 + 0x64), *(u16 *)(s0 + 0xFE));
        *(s16 *)(s0 + 6) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x48);
        *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4C);
        *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x50) - 0x10;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0x100;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0x200;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x14) = 0;
        func_8012B200((u8 *)s0);
        *(s32 *)(s0 + 0x18) = 0xFFE00000;
        *(s32 *)(s0 + 0x14) = 0x200000;
        *(s32 *)(s0 + 0x10) = 0xFFF00000;
        func_8012AD44((s32 *)s0, 3);
    }
}


#include "common.h"

extern void func_8001C924(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 D_801E4A58[];
extern u8 D_801964D4[];

void func_8018AEB4(s32 a0, s32 a1)
{
    s32 s0;
    s32 s1;
    s32 v1;

    s0 = D_801E4A58[a0];
    if (s0 != 0) {
        s1 = a1;
        *(s16 *)(s0 + 0xFC) = 1;
        func_8001C924(*(s32 *)(s0 + 0x20), D_801964D4);
        func_8012AD44((s32 *)s0, 4);
        func_8012C658(0x60, s1, s0);
        if (s1 != 0) {
            v1 = func_80132EF4(s0, 0xC);
            if (v1 != 0) {
                *(u16 *)(v1 + 0xA) += 0x60;
            }
        }
    }
}


#include "common.h"

/* Local idiom types (mirrors the TU's own MTX_CF90 pattern / shared Vec32,
 * kept file-local since match_one compiles standalone with -Iinclude only). */
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx8_8018AF58;
typedef struct { s32 vx, vy, vz, pad; } Vec32_8018AF58;

extern Blk20 D_800AE620;
extern Blk16_801E2F08 D_801E2F08;

extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018AF58(s32 a0)
{
    Mtx8_8018AF58 localMatrix;
    Vec32_8018AF58 fixedVec;
    s32 i;
    u8 *p;

    fixedVec = (*(Vec32_8018AF58 *)&D_801E2F08);

    for (i = 0; i < 8; i++) {
        p = func_8012913C(0xC);
        if (p != NULL) {
            func_80129350((s32)p, a0);
            localMatrix = (*(Mtx8_8018AF58 *)&D_800AE620);
            RotMatrixY(i << 9, &localMatrix);
            func_800484EC((s32)&localMatrix, (s32)&fixedVec, (s32)p + 0x10);
        }
    }
}


#include "common.h"



/* D_801E2F00: 8-byte, alignment-1 blob -- copied with lwl/lwr (gcc's
 * emit_block_move for align < 4), same idiom as the TU's other Blob8
 * globals (func_8018A4C4's D_801E2F30). Holds 3 x s16 angle (+ pad); the
 * middle field is overwritten right after the copy and re-biased each
 * loop iteration below. */
typedef struct { char b[8]; } Blob8_8018B058;
extern Blob8_8018B058 D_801E2F00;

/* Vec32-shape local (matches the TU's Vec32_8018AF58 pattern): 3 x s32 +
 * pad, passed by address to func_800484EC as its translation-vector arg. */
typedef struct { s32 vx, vy, vz, pad; } Vec32_8018B058;

extern u8 D_80196870[];

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004978C(s16 *a0, void *a1);
extern void func_8012B23C(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018B058(s32 a0)
{
    Blob8_8018B058 angle;
    Vec32_8018B058 vec;
    MTX_CF90 mtx;
    s32 i;
    s32 s0;

    angle = D_801E2F00;

    vec.vx = *(s32 *)(a0 + 0x10) >> 2;
    vec.vy = (s32)0xFFF40000;
    vec.vz = *(s32 *)(a0 + 0x18) >> 2;
    *(s16 *)&angle.b[2] = -0x100;

    for (i = 0; i < 4; i++) {
        s0 = func_8012C658(0x54, D_80196870[i], 0);
        if (s0 != 0) {
            *(s32 *)(s0 + 4) = *(s32 *)(a0 + 4);
            *(s32 *)(s0 + 8) = *(s32 *)(a0 + 8);
            *(s32 *)(s0 + 0xC) = *(s32 *)(a0 + 0xC);
            func_8004978C((s16 *)&angle, &mtx);
            func_8012B23C(s0);
            func_800484EC((s32)&mtx, (s32)&vec, s0 + 0x10);
        }
        *(s16 *)&angle.b[2] += 0x200;
    }
}


#include "common.h"



extern Blk20 D_800AE620;
extern u16 D_800B99DC;
extern u16 D_800B99D8;
extern u8 D_80196880[];
extern u8 D_80196874[];

extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B23C(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018B16C(s32 a0, s32 a1, s32 a2)
{
    s32 s0;
    s32 i;
    Blk20 localMatrix;

    localMatrix = D_800AE620;

    s0 = (s32)&D_800B99DC;
    RotMatrixY(*(u16 *)s0, &localMatrix);
    *(u16 *)s0 = *(u16 *)s0 + D_800B99D8;

    if (a1 > 0) {
        i = 0;
        do {
            s0 = func_8012C658(0x54, *(s32 *)(D_80196880 + i), 0);
            if (s0 != 0) {
                *(s16 *)(s0 + 6) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) + *(u16 *)(a2 + 0);
                *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) + *(u16 *)(a2 + 2);
                *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) + *(u16 *)(a2 + 4);
                func_8012B23C(s0);
                func_800484EC((s32)&localMatrix, (s32)(D_80196874 + i), s0 + 0x10);
            }
            i += 0x10;
        } while (i < (a1 << 4));
    }
}


void func_8018B2DC(void)
{
    extern u8 D_801E44F7;
    s32 i = 7;
    u8 *p = &D_801E44F7;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}


#include "common.h"

extern u8 D_801E44F0[];

s32 func_8018B300(void)
{
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801E44F0;
    do {
        if (*p == 0) {
            *p = v;
            ret = i;
            goto done;
        }
        i++;
        p++;
    } while (i < 8);
    ret = -1;
done:
    return ret;
}


void func_8018B344(void *arg0) {
    u8 *temp_v1 = (u8 *)*(s32 *)((u8 *)arg0 + 0xCC);
    if (temp_v1 != NULL) {
        temp_v1[0x26] = 200;
        temp_v1[0x25] = 200;
        temp_v1[0x24] = 200;
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80188A5C(void *arg0);

extern u8 D_801BB8F8[];
extern u8 D_801964C4[];
extern M2C_UNK D_80190C0C;
extern u8 D_801964DC[];

void func_8018B368(void *a0) {
    s32 v0;
    register void *s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    s0 = a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        *(s32 *)D_801964C4 = *(s32 *)D_801BB8F8;

        func_8001C214(*(s32 *)((u8 *)s0 + 0x20), (s32)D_801964C4);

        *(s32 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x28) = 0xB000D0;

        func_8012A828((s32)s0, (void *)&D_80190C0C);

        *(s32 *)((u8 *)s0 + 0x58) = (s32)D_801964DC;

        *(s16 *)((u8 *)s0 + 0x5C) = 0xC00;

        *(s16 *)((u8 *)s0 + 0xFC) = 0;
        func_80188A5C(s0);
    }
}


void func_8018B408(void) {
}

extern void func_80132784(s32 a0, s32 a1, u32 a2);
    void func_8018B410(u8 *a0) {
        ((void (*)(u8 *, u8 *, u16))func_80132784)(a0, *(u8 **)(a0 + 0x64), *(u16 *)(a0 + 0xfe));
    }


void func_8018B438(void) {
}

extern void func_8012AD80(s32 a0);
extern void func_8018AC10(s32 a0);
extern s32 func_8012BEE8(s32 a0);

void func_8018B440(s32 a0) {
    if (func_8012BEE8(a0) != 0) {
        func_8018AC10(a0);
    } else {
        func_8012AD80(a0);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) = *(s16 *)(a0 + 6);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) = *(s16 *)(a0 + 0xA);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) = *(s16 *)(a0 + 0xE);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) | 1;
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8018B4D0(s32 a0) {
    if (((s32 *)a0)[0x1C / 4] & 1) {
        s32 *ptr1 = (s32 *)((s32 *)a0)[0x20 / 4];
        s32 field1 = ptr1[1];
        field1 |= 0x80000000;
        ptr1[1] = field1;
    } else {
        s32 *ptr2 = (s32 *)((s32 *)a0)[0x20 / 4];
        s32 field2 = ptr2[1];
        field2 &= 0x7FFFFFFF;
        ptr2[1] = field2;
    }

    if (func_8012BEE8(a0) != 0) {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern u8 *func_8012913C(s32 a0);

void func_8018B554(s32 a0) {
    s32 v0;
    s32 i;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    func_8001C2C4(v0);

    for (i = 0; i < 0xF; i++) {
        v0 = (s32)func_8012913C(0xB);
        if (v0 != 0) {
            *(s32 *)(v0 + 0x2C) = a0;
            *(u16 *)(v0 + 0x30) = i;
        }
    }

    *(u16 *)(a0 + 0x2) += 1;
    *(u16 *)(a0 + 0x34) = 0;
}


extern void func_80189504(void *a0);
extern void func_8012C218(void *a0);

void func_8018B5E0(void *a0) {
    if (*(u16 *)((u8 *)a0 + 0x34) == 0) {
        if (*(s16 *)((u8 *)a0 + 0xFC) == 0) {
            func_80189504(a0);
        } else {
            (*(u16 *)((u8 *)a0 + 0x34))++;
        }
    } else {
        func_8012C218(a0);
    }
}


extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void (*D_801965C8[])(void);
extern void func_801895E0();

void func_8018B638(s32 arg0) {
    s32 iVar1;

    iVar1 = *(s32 *)(arg0 + 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_801965C8, 0x2BC, 0x1B0);
    *(u8 *)(iVar1 + 0x27) = 0x59;
    ((void (*)(s32))func_801895E0)(arg0);
    *(u16 *)((s32)arg0 + 2) += 1;
}


extern void func_801292C8(u8 *a0);
extern void func_801895E0();

void func_8018B6A0(s32 arg0) {
    if (*(s16 *)(*(s32 *)(arg0 + 0x2C) + 0xFC) != 0) {
        func_801292C8((u8 *)arg0);
    } else {
        func_801895E0(arg0);
    }
}


#include "common.h"

extern void func_8001CB6C(u8*, s32, s32, s32);
extern u8 D_80196614[];
extern u8 D_80196620[];
extern u8 D_80196660[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018B6E8(s32 param_1) {
    s32 temp;
    s32 var;

    temp = *(s32 *)(param_1 + 0x20);
    func_8001CB6C((u8 *)temp, (s32)&D_80196614, 0x320, 0x100);
    var = *(s32 *)(param_1 + 0x34);
    *(u16 *)(temp + 0x1C) = 0x2800;
    *(u16 *)(temp + 0x1A) = 0x2800;
    *(u16 *)(temp + 0x18) = 0x2800;
    *(u8 *)(temp + 0x27) = 0x5F;
    *(u32 *)(temp + 0x34) = var;
    *(u32 *)(temp + 4) |= 0x50000000;
    if (*(s16 *)(temp + 0x1E) != 0) {
        func_80128EA8(temp, param_1 + 0x24, (s32)&D_80196660);
    } else {
        func_80128EA8(temp, param_1 + 0x24, (s32)&D_80196620);
    }
    *(u16 *)(param_1 + 2) += 1;
}


extern s32 func_80128ED8(s32, s32*);
extern void func_801292C8(u8*);

void func_8018B7A4(s32 param_1)
{
    if (func_80128ED8(*(s32 *)(param_1 + 0x20), (s32 *)(param_1 + 0x24)) != 0) {
        if (*(s32 *)(param_1 + 0x2C) != 0) {
            *(s16 *)(*(s32 *)(param_1 + 0x2C) + 0xFC) = 1;
        }
        func_801292C8((u8 *)param_1);
    }
}


#include "common.h"

extern u8 D_800D387C[];
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018B7F8(s32 param_1)
{
    extern u8 D_80196710[];
    extern u8 D_801966C0[];
    s32 p;
    u16 v;
    s32 a0;
    s32 a1;
    s32 a2;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
    } else {
        p = *(s32 *)(param_1 + 0x20);
        v = 0x6000;
        *(u16 *)(p + 0x1a) = v;
    }
    *(u16 *)(p + 0x18) = v;

    a1 = param_1 + 0x24;
    if (*(s16 *)(param_1 + 0x34) & 0x8000) {
        a0 = *(s32 *)(param_1 + 0x20);
        a2 = (s32)D_80196710;
    } else {
        a0 = *(s32 *)(param_1 + 0x20);
        a2 = (s32)D_801966C0;
    }
    func_80128EA8(a0, a1, a2);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801921F8;

void func_8018B8CC(s32 param_1)
{
    func_8001CB6C((u8 *)*(s32 *)(param_1 + 0x20), (s32)&D_801921F8, 0x250, 0x1A0);
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) = 0x60000000;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x14;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 D_801270C8;
extern void func_801292C8(u8 *a0);

void func_8018B93C(void) {
    if (*(s32 *)&D_801270C8 == 0x13) {
        ((void (*)(void))func_801292C8)();
    }
}


#include "common.h"

extern void func_801439FC(s32 a0);

void func_8018B96C(s32 a0) {
    s32 v0;
    s32 v1;
    s32 s0;
    s32 pad[2];

    v0 = *(s32 *)(*(s32 *)(a0 + 0x64) + 0x20);
    v0 = *(s32 *)(v0 + 4);
    s0 = *(s32 *)(a0 + 0xCC);
    if (v0 < 0) {
        *(u32 *)(s0 + 4) |= 0x80000000;
    } else {
        func_801439FC(a0);
    }

    v0 = *(s32 *)(a0 + 0x64);
    *(u16 *)(s0 + 0x14) = *(u16 *)(*(s32 *)(v0 + 0x20) + 0x12);

    v0 = *(s32 *)(a0 + 0x64);
    v1 = *(u16 *)(s0 + 0xA) - *(u16 *)(v0 + 0xA);
    if ((u16)(v1 + 0x20) >= 0x421) {
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
    } else {
        v1 = v1 << 16;
        v1 = v1 >> 11;
        v0 = -0x8000 - v1;
        *(s16 *)(s0 + 0x1A) = v0;
        *(s16 *)(s0 + 0x18) = v0;
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 rand(void);

extern u8 D_801966A8[];
extern u8 D_801966B0[];
extern M2C_UNK D_80190C0C;

void func_8018BA38(s32 param_1)
{
    s32 s0;
    s32 a0;
    s32 pad[4];
    s32 ret;

    ret = ((s32 (*)(void))func_8012C1B8)();
    s0 = param_1;
    a0 = ret;
    *(s32 *)(s0 + 0x20) = ret;
    if (a0 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }
    func_8001C214(a0, (*(u16 *)(s0 + 0x70) & 1) ? (s32)D_801966B0 : (s32)D_801966A8);
    func_8012A828((s32)s0, (void *)&D_80190C0C);
    *(s16 *)(s0 + 0xFC) = rand() & 0x3F0;
    *(s16 *)(s0 + 0xFE) = rand() & 0x3F0;
    *(s32 *)(s0 + 0x1C) = 0x60;
    *(s16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_8018BAE4(s32 arg0) {
    s32 s0;
    s32 a0;
    s32 a1;

    s0 = arg0;
    a0 = *(s32 *)(s0 + 0x20);
    *(u16 *)(a0 + 0x12) = *(u16 *)(a0 + 0x12) + *(u16 *)(s0 + 0xFC);
    a1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(a1 + 0x10) = *(u16 *)(a1 + 0x10) + *(u16 *)(s0 + 0xFE);
    func_8012AD80(s0);
    if (*(s16 *)(s0 + 0xA) >= -0x7FF) {
        func_8012C218((void *)s0);
    }
}


extern void func_8012931C(void *);
extern s32 func_80128ED8(s32, s32*);
extern void func_801292C8(u8*);

void func_8018BB58(s32 a0) {
    s32 s0 = a0;
    func_8012931C((void *)a0);
    if (((s32 (*)(s32, void *))func_80128ED8)(*(s32 *)(s0 + 0x20), (void *)(s0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(s0);
    }
}


#include "common.h"

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 D_80196768;
extern s32 D_80196774;

void func_8018BB9C(s32 param_1)
{
    s32 v0;
    s32 v1;

    // *(u32*)(*(s32*)(param_1 + 0x20) + 0x20) = (u32)&D_80196768;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_80196768;

    // *(u32*)(*(s32*)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    // *(u8*)(*(s32*)(param_1 + 0x20) + 0x27) = 0x90;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x90;

    // v0 = *(u16*)(param_1 + 0x34) & 0x7FFF;
    v0 = *(u16 *)(param_1 + 0x34) & 0x7FFF;

    if (v0) {
        v1 = *(s32 *)(param_1 + 0x20);
        *(s16 *)(v1 + 0x1A) = v0;
    } else {
        v1 = *(s32 *)(param_1 + 0x20);
        v0 = 0x3000;
        *(s16 *)(v1 + 0x1A) = v0;
    }

    *(s16 *)(v1 + 0x18) = v0;

    // func_80128EA8(*(u32*)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196774);
    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196774);

    // *(u16*)(param_1 + 0x2) = *(u16*)(param_1 + 0x2) + 1;
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}


extern void func_8012931C(void *);
extern s32 func_80128ED8(s32, s32*);
extern void func_801292C8(u8*);

void func_8018BC48(s32 a0) {
    func_8012931C((void *)a0);
    if (((s32 (*)(s32, void *))func_80128ED8)(*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    } else {
        *(u8 *)(*(s32 *)(a0 + 0x20) + 0x27) = *(u8 *)(a0 + 0x28) - 0x70;
    }
}


extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 D_801967D4;

void func_8018BCA4(s32 param_1)
{
    func_80128D60(*(s32 *)(param_1 + 0x20), (s32 *)(param_1 + 0x24), &D_801967D4);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}


extern s32 func_80128DB4(s32 a0, s32 *a1);
    s32 func_8018BCEC(void *a0) {
        ((void (*)(void *, void *))func_80128DB4)(*(void **)((char *)a0 + 0x20), (void *)((char *)a0 + 0x24));
    }


#include "common.h"

extern u8 D_8019681C[];
extern u8 D_80196828[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018BD14(s32 param_1)
{
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_8019681C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x65;

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196828);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8*);
void func_8018BD90(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}


#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801E4918;
extern u8 D_801E491C;
extern u8 D_801E2F50;
extern u8 D_801E2F54;

/* align-1 4-byte block: lowers via emit_block_move (unaligned lwl/lwr + swl/swr)
 * with ZERO memcpy-symbol reference (house idiom, cf. func_8018CE04) */
typedef struct { u8 b[4]; } Blk4_8018BDD0;

void func_8018BDD0(s32 param_1)
{
    func_800233CC(&D_801E4918, 0x50);

    *(Blk4_8018BDD0 *)&D_801E4918 = *(Blk4_8018BDD0 *)&D_801E2F50;
    *(Blk4_8018BDD0 *)&D_801E491C = *(Blk4_8018BDD0 *)&D_801E2F54;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0xD0000000;
    *(s16 *)(param_1 + 0xA) = -0x20;
    *(s16 *)(param_1 + 0xE) = -0x20;
    *(s16 *)(param_1 + 6) = 0;

    /* store lands in the jal delay slot (executes before the callee) */
    *(s32 *)(param_1 + 0x1C) = 0xA;
    func_8012AD44((s32 *)param_1, 1);
}


#include "common.h"

extern u16 D_80126B5E;
extern u16 D_80126B66;

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_8018BE88(s32 arg0) {
    s32 self = arg0;
    s32 i;

    *(s16 *)(self + 0x6) = 0;
    *(s16 *)(self + 0xA) = 0;
    *(s16 *)(self + 0xE) = -0x30;
    func_80132784(self, *(s32 *)(self + 0xCC), *(u16 *)(self + 0x70));

    *(s16 *)(self + 0x6) = *(s32 *)(*(void **)(self + 0x20) + 0x48);
    *(s16 *)(self + 0xA) = *(s32 *)(*(void **)(self + 0x20) + 0x4C);
    *(s16 *)(self + 0xE) = *(s32 *)(*(void **)(self + 0x20) + 0x50);
    i = 0;

    *(u32 *)(*(s32 *)(self + 0x20) + 4) |= 0x80000000;

    for (; i < 8; i++) {
        func_8012C658(0x55, i, self);
    }

    func_8002D4C8(0x4EF, 0);

    {
        s32 t = *(s16 *)&D_80126B5E;
        s32 u = *(s16 *)(self + 0x6);
        *(s32 *)(self + 0x14) = 0;
        *(s32 *)(self + 0x10) = (t - u) << 13;
    }

    {
        s32 t = *(s16 *)&D_80126B66;
        s32 u = *(s16 *)(self + 0xE) + 0x20;
        *(s32 *)(self + 0x1C) = 4;
        *(s32 *)(self + 0x18) = (t - u) << 13;
    }

    func_8012AD44((s32 *)self, 2);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018BF88(u8 *a0) {
        *(s32 *)(a0 + 0x1c) = 0x20;
        *(s16 *)(a0 + 0x102) |= 2;
        ((void (*)(void *, s32))func_8012AD44)(a0, 0x3);
    }




void func_8018BFBC(s32 a0) {
    func_8012AD44((s32 *)a0, 4);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018BFDC(u8 *a0) {
        *(u16 *)(a0 + 0x102) |= 0x1;
        ((void (*)(void *, s32))func_8012AD44)(a0, 0x5);
    }


#include "common.h"

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018C008(s32 arg0) {
    s32 self = arg0;
    s32 i;

    *(u16 *)(self + 0xE) -= 0x14;
    *(u16 *)(self + 0x100) = 0;

    for (i = 0; i < 8; i++) {
        if (func_8012C658(0x55, i + 8, self) != 0) {
            *(u16 *)(self + 0x100) += 1;
        }
    }

    func_8012AD44((s32 *)self, 6);
}



extern void (*D_801968F4[])(void);

void func_8018C08C(void *a0) {
    D_801968F4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern short D_80196B30;

void func_8018C0C8(void *arg0) {
    *(s16 *)((char *)arg0 + 0x5C) = 0;
    func_8012A828((s32)arg0, (void *)&D_80196B30);
    func_8012AD44((s32 *)arg0, 2);
}



extern void (*D_80196B80[])(void);

void func_8018C108(void *a0) {
    D_80196B80[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_80189F44(s32 arg0);
extern s32 D_80196AE8;

void func_8018C144(void *a0) {
    u16 v0, v1;

    *(s16 *)((s32)a0 + 0x5C) = 0;

    v1 = *(u16 *)((s32)a0 + 0x5E);
    if (v1 != 0xC) {
        goto else_block;
    }

    func_8012A828((s32)a0, (void *)&D_80196AE8);
    v0 = *(u16 *)((s32)a0 + 0x70);
    *(u8 *)((s32)a0 + 0xC1) = 1;
    if ((v0 & 0x8) == 0) {
        goto skip_call;
    }

    func_80189F44((s32)a0);

skip_call:
    func_8002D4C8(0x4FE, 0);
    return;

else_block:
    *(s16 *)((s32)a0 + 0x5E) = 0;
    *(u8 *)((s32)a0 + 0xC1) = 0;
}


extern void func_8012C218(void *a0);

void func_8018C1C0(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        void *v1 = *(void **)((s32)a0 + 0x64);
        *(s16 *)((s32)v1 + 0x100) -= 1;
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern u16 D_80126B96;
extern s16 D_80126B98;

void func_8018C204(void *a0) {
    extern u16 D_80196B60;
    extern u16 D_80196B62;
    s16 p1[4];
    s16 p2[4];

    p1[2] = 0;
    p1[0] = 0;
    p2[2] = 0;
    p2[0] = 0;
    p1[1] = D_80196B60;
    p2[1] = D_80196B62;

    if (func_8012DEB8((s32)a0, (s32)p1, (s32)p2)) {
        D_80126B98 = 5;
        D_80126B96 |= 0x4200;
    }
}



extern void (*D_80196B8C[])(void);

void func_8018C274(void *a0) {
    D_80196B8C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

// @stuck: none — MATCH (42 ins), iteration 1, rtu_match clean.
// Saturating add of a 3-byte RGB triple by a signed delta.
// Idioms: (1) `s8` by-value param => entry `sll/sra 24` for the sign test only;
//   combine folds the extension back out of `~a1`/`-a1`/`a0[i]+a1` because every
//   consumer is 8-bit (andi 0xFF / sb), so $a1 is used RAW after the test.
// (2) branch sense read off the target `sltu` operand ORDER (§3-T4): positive arm
//   `sltu lim,p[i]` => store when `p[i] <= lim`; negative arm `sltu p[i],lim`
//   => store when `p[i] >= lim`.
// (3) the third `if` written out in BOTH arms; jump.c cross-jumps the identical
//   tails into the shared `j .L8018C344` (§5a) — do not hoist it after the if/else.
void func_8018C2B0(u8 *a0, s8 a1) {
    u8 lim;

    if (a1 == 0) {
        return;
    }
    if (a1 > 0) {
        lim = ~a1;
        if (a0[0] <= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] <= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] <= lim) {
            a0[2] = a0[2] + a1;
        }
    } else {
        lim = -a1;
        if (a0[0] >= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] >= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] >= lim) {
            a0[2] = a0[2] + a1;
        }
    }
}



extern void (*D_80196B98[])(void);

void func_8018C358(void *a0) {
    D_80196B98[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018C394(s32 *a0) {
    s32 *v0;

    v0 = *(s32 **)(((u8 *)a0) + 0x20);
    *(s16 *)(((u8 *)v0) + 0x1C) = 0;
    *(s16 *)(((u8 *)v0) + 0x1A) = 0;
    *(s16 *)(((u8 *)v0) + 0x18) = 0;
    func_8012AD44(a0, 1);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018C3C4(void * arg0) {
        *(s8 *)((char *)arg0 + 0xfc) = 0x8;
        ((void (*)(s32, s32))func_8012AD44)((int)arg0, 0x2);
    }


















extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801270C8;
void func_8018C3EC(void)
{
  int new_var;
  D_801270C8 = 0x21;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 0x3);
  new_var = 0 & 0xFFu;
}


extern void (*D_80196BA0[])(void);

void func_8018C418(void *a0) {
    D_80196BA0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* MTX_CF90-shape: rotation 3x3 (s16) + translation (s32 x3), 0x20 bytes total.
 * Matches the buffer func_8004978C(angle*, mtx*) fills (rotation only) and
 * that the GTE SetRotMatrix/SetTransMatrix ctc2 sequence below consumes. */


extern void func_8004978C(s16 *a0, void *a1);

void func_8018C454(void *a0)
{
    u8 *s0 = (u8 *)a0;
    MTX_CF90 mtx;
    s16 angle[3];
    s16 vec0[4];
    s32 flags;

    angle[2] = 0;
    angle[0] = 0;
    angle[1] = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xFE)
             + ((*(u16 *)(s0 + 0x70) & 7) << 9);

    vec0[1] = 0;
    vec0[0] = 0;
    vec0[2] = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xFC);

    mtx.t[0] = *(s16 *)(*(s32 *)(s0 + 0x64) + 0x6);
    mtx.t[1] = *(s16 *)(*(s32 *)(s0 + 0x64) + 0xA);
    mtx.t[2] = *(s16 *)(*(s32 *)(s0 + 0x64) + 0xE);

    func_8004978C(angle, &mtx);

    gte_SetRotTransMatrix(&mtx);

    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(vec0) : "memory");  // !FAKE: gte direct — clobbers ['memory'] (gte_ldv0+gte_rtv0tr_m) beyond Sony's (P36 T5 gte1)

    gte_stlvnl(s0 + 4);

    gte_stflg(&flags);

    *(s32 *)(s0 + 4) <<= 16;
    *(s32 *)(s0 + 8) <<= 16;
    *(s32 *)(s0 + 0xC) <<= 16;
}




void func_8018C598(void *a0, s32 a1, s32 a2, s32 *a3, u16 a4, u16 a5)
{
    s32 v0;
    s32 v1;

    v0 = func_8012C588(0x7A, (s32)a0);
    if (v0 == 0) goto L_end;
    *(Blk8 *)(v0 + 0x50) = *(Blk8 *)(a1 + 0);
    v1 = *(s32 *)(v0 + 0x20);
    *(Blk8 *)(v1 + 0x10) = *(Blk8 *)(a2 + 0);
    *(u32 *)(v0 + 0x1C) = a5;
    if (a4 != 0) {
        *(u16 *)(v0 + 0xFC) = a4;
    } else {
        *(u16 *)(v0 + 0xFC) = 1;
    }
    *(u32 *)(v0 + 0xCC) = (s32)a3;
L_end:
    *a3 = v0;
}



extern void (*D_80196BB0[])(void);

void func_8018C66C(void *a0) {
    D_80196BB0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA88(s32 a0, void *a1);
extern void func_8018BDD0();
extern void func_8018C008();
extern u8 D_801E4918;

void func_8018C6A8(void *a0)
{
    s32 v0;

    *(s32 *)((u8 *)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)();

    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001CA88(v0, &D_801E4918);

        if (*(s16 *)((u8 *)a0 + 0x70) != 0) {
            *(s16 *)((u8 *)a0 + 0xFC) = 0;
            *(s16 *)((u8 *)a0 + 0xFE) = 0;
            *(s16 *)((u8 *)a0 + 0x102) = 0;
            func_8018BDD0(a0);
        } else {
            *(s32 *)((u8 *)v0 + 0x4) |= 0x80000000;
            *(s16 *)((u8 *)a0 + 0xFC) = 0x58;
            *(s16 *)((u8 *)a0 + 0xFE) = 0x100;
            *(s16 *)((u8 *)a0 + 0x102) = 0x2;
            func_8018C008(a0);
        }
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 func_80185D6C();
extern void func_8018BE88(s32 a0);

/* 0x801E4918 is an 8-byte block; splat renders the +4/+5 bytes with the
 * next symbol's name (D_801E491C / D_801E491C+1), but the codegen proves
 * ONE base symbol: gcc materialises exactly one `la` per symbol that has a
 * non-foldable address reference, and the target has exactly one (`la $a0,
 * D_801E4918`) covering all four bytes.  Two separate symbols always cost a
 * second `la` (measured: every 2-symbol spelling loses 10-17 instructions of
 * shape).  Declared as the TU already declares it (`extern u8 D_801E4918;`,
 * cf. lines 6425 / 6556) — the array spelling is a HARD conflicting-types
 * error against that file-scope scalar decl. */
extern u8 D_801E4918;

void func_8018C758(void *a0) {
    s32 s0 = *(s32 *)((u8 *)a0 + 0x20);   /* the entity's 0x20 record */
    s32 v0;

    /* Clearing bit31 of rec->0x4 is written as read / mask / store with a
     * ZERO-BYTE sched2 fence between the mask and the store.  Without it,
     * sched2's backward list scheduler picks the call's `move $a0,$s1`
     * (equal priority 1, higher LUID) over the `ori` at the T-5 step and the
     * pair comes out `lui/ori/lw` + a load-delay nop (62 ins).  The fence
     * makes the store depend on it, which defers `move $a0`/the call, so the
     * step order becomes `and`, `ori`, `lw`, `lui` -> emitted
     * `lui / lw / ori / and`, exactly the target.  Placing the fence AFTER
     * the store instead also fixes the order but then the fence is the last
     * insn before the jal and reorg.c:stop_search_p refuses to look past an
     * ASM_INPUT, so the `sw` never reaches the call's delay slot. */
    v0 = *(s32 *)(s0 + 0x4) & 0x7FFFFFFF;
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus10)
    *(s32 *)(s0 + 0x4) = v0;

    if (func_80185D6C(a0) != 0) {
        func_8012C218(a0);
    } else if (func_8012BEE8((s32)a0) != 0) {
        func_8018BE88((s32)a0);
    } else {
        /* p is what forces `la $a0, D_801E4918` (offset 0).  A direct
         * `D_801E4918 += 0x10` folds to the VAR_DECL and emits the inline
         * %hi/%lo form, which hands the single `la` to the +1 byte instead —
         * the mirror image of the target. */
        u8 *p = (u8 *)&D_801E4918;

        v0 = *(u16 *)(s0 + 0x1C) - 0x180;
        *(u16 *)(s0 + 0x1C) = v0;
        *(u16 *)(s0 + 0x1A) = v0;
        *(u16 *)(s0 + 0x18) = v0;

        p[0] += 0x10;
        ((u8 *)&D_801E4918)[1] += 0x10;
        ((u8 *)&D_801E4918)[4] += 0x10;   /* = D_801E491C     */
        ((u8 *)&D_801E4918)[5] += 0x8;    /* = D_801E491C + 1 */

        func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0xCC), *(u16 *)((u8 *)a0 + 0x70));
    }
}


extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8018BF88(u8 *a0);

void func_8018C84C(s32 a0)
{
    s16 temp;
    u16 temp2;
    u16 cnt;
    s32 t;
    s32 u;

    func_8012AD80(a0);
    temp = *(s16 *)(a0 + 0xFC);
    if (temp < 0x80)
    {
        *(s16 *)(a0 + 0xFC) = temp + 0x10;
    }
    temp2 = *(u16 *)(a0 + 0xFE);
    *(u16 *)(a0 + 0xFE) = temp2 - 0x40;
    if (func_8012BEE8(a0) != 0)
    {
        if (*(u16 *)(a0 + 0x34) == 0)
        {
            *(s32 *)(a0 + 0x10) = (*(s16 *)&D_80126B5E - *(s16 *)(a0 + 6)) << 14,
            *(s32 *)(a0 + 0x14) = (*(s16 *)(*(s32 *)(a0 + 0x64) + 0xA) - *(s16 *)(a0 + 0xA)) << 14;
            cnt = *(u16 *)(a0 + 0x34) + 1;
            t = *(s16 *)&D_80126B66;
            u = *(s16 *)(a0 + 0xE) + 0x20;
            *(s32 *)(a0 + 0x1C) = 4;
            *(u16 *)(a0 + 0x34) = cnt;
            *(s32 *)(a0 + 0x18) = (t - u) << 14;
        }
        else
        {
            func_8018BF88(a0);
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8018BFBC(s32 a0);

void func_8018C928(int param_1)
{
    *(unsigned short *)(param_1 + 0x102) |= 4;
    *(unsigned short *)(param_1 + 0xFE) -= 0x40;
    if (func_8012BEE8(param_1) != 0) {
        func_8018BFBC(param_1);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8018BFDC(u8 *a0);

void func_8018C978(s32 arg0)
{
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (*(s16 *)(arg0 + 0xFC) >= 0x51) {
            *(s16 *)(arg0 + 0xFC) -= 2;
        } else {
            *(s32 *)(arg0 + 0x1C) = 0xA0;
            *(u16 *)(arg0 + 0x34) += 1;
        }
        break;
    case 1:
        if (func_8012BEE8(arg0) != 0) {
            func_8018BFDC((u8 *)arg0);
        }
        break;
    }

    *(u16 *)(arg0 + 0xFE) -= 0x40;
}


extern void func_8012C218(void *a0);
    void func_8018CA1C(void) {
        ((s32 (*)(void))func_8012C218)();
    }


extern s32 D_801270C8;
extern void func_8012C218(void *a0);

void func_8018CA3C(s32 a0) {
    if (*(s16 *)(a0 + 0x100) == 0) {
        D_801270C8 = 13;
        func_8012C218((void *)a0);
    }
}


#include "common.h"

/* Fleet-canonical prototypes (ov_SC02_005 / ov_SC03_006 file-scope spelling).
 * func_8012C1B8 is canonically `void` returning; the value in $v0 is taken via a
 * cast at the call site, exactly as the banked family exemplar in
 * src/ov_SC03_006/ov_SC03_006_jr_80140608.c does. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012AD50(void *a0);

extern s32 D_80196910;
extern s32 D_80196B68;
extern s32 D_80196B58;
extern s32 D_80196A60;

void func_8018CA74(s32 param_1)
{
    register s32 d __asm__("$16") = param_1;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus10)
    register s32 obj __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus10)
    /* $a1 pin on the shared `1`: without it the const-1 pseudo and the 0xC4
     * pseudo both land in $v0 (disjoint ranges after sched1), which pins the
     * 0xC4 load below the two sb's in sched2. See notes in the wave report. */
    register u8 one __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus10)
    s32 ret;
    s32 c4v;
    u16 aev;
    u16 f70v;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = ret;
    obj = ret;
    if (ret == 0) {
        func_8012CAE4((void *)d);
        return;
    }
    func_8001CA1C(obj, (s32)&D_80196910);
    *(s16 *)(obj + 0x1c) = 0x2800;
    *(s16 *)(obj + 0x1a) = 0x2800;
    *(s16 *)(obj + 0x18) = 0x2800;
    *(s32 *)(d + 0xbc) = (s32)&D_80196B68;
    *(s32 *)(d + 0x58) = (s32)&D_80196B58 | 0x20000000;
    c4v = *(s32 *)(d + 0xc4);
    one = 1;
    *(u8 *)(d + 0xc0) = one;
    *(u8 *)(d + 0x75) = one;
    *(s32 *)(d + 0xb4) = 0;
    *(u8 *)(d + 0xc1) = 0;
    *(s32 *)(d + 0xc4) = c4v | 2;
    *(s32 *)(*(s32 *)(d + 0x20) + 4) |= 0x50000000;
    aev = *(u16 *)(d + 0xae);
    *(s16 *)(d + 0x5c) = 0;
    aev |= 0xfffd;
    *(s16 *)(d + 0xae) = (s16)aev;
    func_8012A828(d, &D_80196A60);
    f70v = *(u16 *)(d + 0x70);
    *(s16 *)(d + 0x98) = 1;
    f70v &= 7;
    *(s32 *)(d + 0x94) = f70v;
    func_8012AD50((void *)d);
}


extern void func_8018C204(void *a0);
extern void func_8018C0C8(void *a0);

void func_8018CB70(void *arg0) {
    void *v0;
    u16 s1;

    v0 = *(void **)((u8 *)arg0 + 0x64);
    s1 = *(u16 *)((u8 *)v0 + 0x102);

    if (s1 & 4) {
        func_8018C204(arg0);
    }
    if (s1 & 2) {
        *(u16 *)((u8 *)arg0 + 0x5C) |= 0x8000;
    }
    func_8018C454(arg0);
    if (s1 & 1) {
        func_8018C0C8(arg0);
    }
}


extern void func_8012C218(void *a0);
    void func_8018CBF8(s32 *a0) {
        if (*(s16 *)((char *)a0 + 0x98) == 0) {
            ((void (*)(void))func_8012C218)();
        }
    }


#include "common.h"

typedef struct { u8 b[4]; } Blk4_8018CC28;

/* ---- externs ------------------------------------------------------------ */
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4958[];
extern u8 D_801E495C;
extern u8 D_801E2F58;
extern u8 D_801E2F5C;

void func_8018CC28(s32 param_1)
{
    func_8001CD50(*(s32 *)(param_1 + 0x20), (s32)&D_801E4958);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 0x2C) = 0x8;

    func_800233CC(&D_801E4958, 0x8);

    *(Blk4_8018CC28 *)&D_801E4958 = *(Blk4_8018CC28 *)&D_801E2F58;
    *(Blk4_8018CC28 *)&D_801E495C = *(Blk4_8018CC28 *)&D_801E2F5C;

    *(u16 *)(param_1 + 2) += 1;
}


#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4958[];

void func_8018CCF8(s32 param_1)
{
    u8 *s0 = &(*(u8 *)D_801E4958);

    *(u16 *)(param_1 + 0x2C) = *(u16 *)(param_1 + 0x2C) + 0x20;
    func_8018C2B0(s0, -4);
    func_8018C2B0(s0 + 4, -4);
    func_800233CC(s0, *(u16 *)(param_1 + 0x2C));

    if (*(s16 *)(param_1 + 0x2C) >= 0x380) {
        s32 v0;

        v0 = *(u16 *)(param_1 + 2);
        *(s16 *)(param_1 + 2) = v0 + 1;
    }
}


#include "common.h"

extern u8 D_801E4958[];
extern void func_801292C8(u8 *a0);
extern void func_8018C2B0(u8 *a0, s8 a1);
extern void func_800233CC(void *a0, unsigned short a1);

void func_8018CD80(s32 param_1)
{
    u8 *p;

    *(u16 *)(param_1 + 0x2C) -= 0x20;
    if (*(s16 *)(param_1 + 0x2C) <= 0) {
        ((void (*)(void))func_801292C8)();
        return;
    }

    p = D_801E4958;
    func_8018C2B0(p, -4);
    func_8018C2B0(p + 4, -4);
    func_800233CC(p, *(u16 *)(param_1 + 0x2C));
}


#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4918;
extern u8 D_801E491C;
extern u8 D_801E2F60;
extern u8 D_801E2F64;

/* align-1 4-byte block: lowers via emit_block_move (unaligned lwl/lwr + swl/swr)
 * with ZERO memcpy-symbol reference, so the TU's `extern memcpy` cannot turn
 * this into a CALL.  (house idiom, cf. func_8017B238 / func_8017B614) */

void func_8018CE04(s32 param_1)
{
    func_8001CD50(*(s32 *)(param_1 + 0x20), (s32)&D_801E4918);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 0x2C) = 0x10;

    func_800233CC(&D_801E4918, 0x10);

    *(Blk4_8018CE04 *)&D_801E4918 = *(Blk4_8018CE04 *)&D_801E2F60;
    *(Blk4_8018CE04 *)&D_801E491C = *(Blk4_8018CE04 *)&D_801E2F64;

    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1E) = 0xC00;
    *(u16 *)(param_1 + 2) += 1;
}


extern void func_8018C2B0(u8 *a0, s8 a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_801292C8(u8 *a0);
extern u8 D_801E491C;

void func_8018CEE0(void *param_1)
{
    s16 sp18;
    u8 *s0;

    sp18 = *(s16 *)((s32)param_1 + 0x2C);
    if (sp18 < 0x700) {
        s0 = &D_801E491C;
        *(s16 *)((s32)param_1 + 0x2C) = sp18 + 0x30;
        func_8018C2B0(s0, -4);
        func_800233CC(s0 - 4, *(u16 *)((s32)param_1 + 0x2C));
    } else {
        func_801292C8(param_1);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8018C394(s32 *a0);

extern u8 D_801F1988;
extern u8 D_801F2138;

void func_8018CF58(s32 param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }

    ((void (*)(s32, s32))func_8001C810)(v0, (s32)&D_801F1988);

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        v0 = *(s32 *)(param_1 + 0x20);
        *(s16 *)v0 = 0;
        return;
    }

    ((void (*)(s32, s32))func_8001C810)(v0, (s32)&D_801F2138);

    *(s16 *)(param_1 + 0xA) -= 0x100;
    *(u8 *)(param_1 + 0xC0) = 0;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x10;
    *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0xCC) + 0x2C) |= 0x10;

    func_8018C394((s32 *)param_1);
}


#include "common.h"

extern void func_8018C3C4(void *arg0);

void func_8018D04C(s32 param_1)
{
    s32 a1;
    u16 v0;
    u16 v1;

    a1 = *(s32 *)(param_1 + 0xCC);
    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    if (v1 < 0x5000) {
        s32 p20;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = v1 + 0x100;

        p20 = *(s32 *)(param_1 + 0x20);
        v1 = *(u16 *)(p20 + 0x18);
        *(u16 *)(p20 + 0x1C) = v1;
        *(u16 *)(p20 + 0x1A) = v1;

        v0 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = v0 + 0x100;

        *(u16 *)(a1 + 0x12) = *(u16 *)(a1 + 0x12) - 0x100;

        *(u16 *)(a1 + 0x8) = *(u16 *)(param_1 + 0x6) + *(u16 *)(param_1 + 0x50);
        *(u16 *)(a1 + 0xA) = *(u16 *)(param_1 + 0xA) + *(u16 *)(param_1 + 0x52);
        *(u16 *)(a1 + 0xC) = *(u16 *)(param_1 + 0xE) + *(u16 *)(param_1 + 0x54);

        *(u16 *)(a1 + 0x18) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
        *(u16 *)(a1 + 0x1A) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A);
        *(u16 *)(a1 + 0x1C) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1C);
    } else {
        func_8018C3C4((void *)param_1);
    }
}


#include "common.h"

extern void func_8017C048(void);
extern s32 func_8012BEE8(s32 a0);
/* §183 SIGNATURE-cast-at-call.  The destination TU DEFINES this function at line 6190
 * as `void func_8018C3EC(void)` — an explicit ZERO-parameter prototype, ABOVE this
 * insertion point — so the unspecified-list escape (`extern void func_8018C3EC();`)
 * does NOT save the one-argument call: gcc-2.7.2 rejects it with "too many arguments
 * to function `func_8018C3EC'".  Adopt the TU's prototype and cast at the call site
 * through a function pointer (the same idiom the TU's own func_8018C3EC body uses on
 * func_8012AD44).  Byte-identical — re-verified MATCH 54/54. */
extern void func_8018C3EC(void);
extern void func_80016450(s32 a0, s32 a1);

void func_8018D144(s32 param_1)
{
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
    {
        u8 v0 = *(u8 *)(param_1 + 0xFC) + 0x10;
        *(u8 *)(param_1 + 0xFC) = v0;
        if (v0 >= 0xF1) {
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x80000000;
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x34) += 1;
            func_8017C048();
        }
        break;
    }
    case 1:
        if (func_8012BEE8(param_1) != 0) {
            ((void (*)(s32))func_8018C3EC)(param_1);
        }
        break;
    }

    func_80016450(*(u8 *)(param_1 + 0xFC), 1);
}


extern void func_8012C218(void *a0);
extern void func_80016450(s32 a0, s32 a1);

void func_8018D21C(void *a0) {
    u8 v;

    v = *(u8 *)((s32)a0 + 0xFC) - 3;
    *(u8 *)((s32)a0 + 0xFC) = v;
    if (v >= 9) {
        func_80016450(v, 1);
    } else {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s16 D_801BDCD0;

void func_8018D270(void *a0) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
    s32 v1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (!v0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801BDCD0);

        v0 = *(s32 *)((s32)a0 + 0x20);
        *(s32 *)((s32)v0 + 0x20) = (s32)a0 + 0xDC;

        {
            register s32 a1_val __asm__("$5") = *(s32 *)((s32)*(s32 *)((s32)a0 + 0x64) + 0x20);  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus10)
            if (a1_val) {
                func_8001C1E4(*(s32 *)((s32)a0 + 0x20));
                *(s16 *)((s32)a0 + 0xE) = 0;
                *(s16 *)((s32)a0 + 0xA) = 0;
                *(s16 *)((s32)a0 + 0x6) = 0;
            }
        }

        v0 = *(s32 *)((s32)a0 + 0x20);
        *(s32 *)((s32)v0 + 0x4) |= 0x80000000;
        func_8012AD50(a0);
    }
}


void func_8018D318(s32 a0) {
    if (*(s16 *)(a0 + 0xFC) != 0) {
        *(s16 *)(a0 + 0xFC) = *(s16 *)(a0 + 0xFC) - 1;
        if (*(s16 *)(a0 + 0xFC) != 0) {
            return;
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
    } else {
        if (func_8012BEE8(a0) != 0) {
            s32 cc = *(s32 *)(a0 + 0xCC);
            if (cc != 0) {
                *(s32 *)cc = 0;
            }
            func_8012C218((void *)a0);
        } else {
            if (*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) == 0) {
                *(u16 *)(a0 + 6) = *(u16 *)(*(s32 *)(a0 + 0x64) + 6);
                *(u16 *)(a0 + 10) = *(u16 *)(*(s32 *)(a0 + 0x64) + 10);
                *(u16 *)(a0 + 14) = *(u16 *)(*(s32 *)(a0 + 0x64) + 14);
            }
            {
                s32 r = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20);
                *(u16 *)r -= 2;
                if ((s16)(*(u16 *)r) < -0x20) {
                    *(u16 *)r = 0;
                }
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += 0x40;
            }
        }
    }
}


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);

void func_8018D43C(void) {
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    D_801270C8 = 0;
    buf.f06 = 0x52;
    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f0A = 0;
    buf.f08 = 0;
    buf.f0E = 0;
    buf.f10 = 0;
    func_8012C750((s32)&buf);
}


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);

void func_8018D488(void) {
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    D_801270C8 = 0;
    buf.f06 = 0x52;
    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f08 = 1;
    buf.f0A = 0;
    buf.f0E = 0;
    buf.f10 = 0;
    func_8012C750((s32)&buf);
}


extern void (*D_80196C64[])(void);
extern s16 D_80196C44[];
extern u16 D_800B99DA;
extern s32 D_801270C8;
extern void MoveImage(void *a0, s32 a1, s32 a2);

struct imgrect { u16 x; u16 y; u16 w; u16 h; };

void func_8018D4D8(void *param_1)
{
    D_80196C64[*(u16 *)((char *)param_1 + 2)]();
    if (D_801270C8 < 0x17) {
        struct imgrect img;
        u16 *src = (u16 *)((char *)D_80196C44 + (*(u16 *)&D_800B99DA & 7) * 4);
        img.x = src[0];
        img.y = src[1];
        img.w = 6;
        img.h = 0x28;
        MoveImage(&img, 0x298, 0x1C0);
    }
}


extern void func_8018F414(void);
extern void func_8018F444(void);
extern void func_8018F474(void);
extern void func_8018F4A4(void);
extern void func_8018F4D4(void);
extern void func_8018F504(void);
extern void func_8018F534(void);
extern void func_8018F564(void);
extern void func_8018F594(void);
extern void func_8018EA04(s32 a0);

void func_8018D574(void *a0)
{
    s32 pad[10];
    s16 v0;
    register u32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus10)

    func_8018F414();
    func_8018F444();
    func_8018F474();
    func_8018F4A4();
    func_8018F4D4();
    func_8018F504();
    func_8018F534();
    func_8018F564();
    func_8018F594();
    if (*(s16 *)((s32)a0 + 0x70) != 0) {
        v0 = 9;
    } else {
        func_8018EA04(0);
        v1 = 0x30;
        *(u32 *)((s32)a0 + 0x1C) = v1;
        v0 = *(u16 *)((s32)a0 + 0x2) + 1;
    }
    *(s16 *)((s32)a0 + 0x2) = v0;
}


#include "common.h"

extern s32 func_8012C750(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);

typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} LocalStruct;

void func_8018D608(s32 a0)
{
    s32 s0;
    s32 *counter;
    LocalStruct local_struct;
    s32 v0;
    u16 *val;

    s0 = a0;
    counter = (s32 *)(s0 + 0x1C);

    (*counter)--;

    if (*counter != 0) {
        return;
    }

    local_struct.field_6 = 0x58;
    local_struct.field_0 = -0x50;
    local_struct.field_2 = -0x802;
    local_struct.field_4 = -0xF80;
    local_struct.field_A = 0;
    local_struct.field_8 = 0;
    local_struct.field_C = 0;

    v0 = func_8012C750((s32)&local_struct);

    local_struct.field_6 = 0x59;
    local_struct.field_0 = -0x70;
    local_struct.field_4 = 0;
    local_struct.field_2 = 0;
    local_struct.field_E = 0;
    local_struct.field_10 = 0;

    func_8012C51C(&local_struct, v0);

    val = (u16 *)(s0 + 0x2);
    (*val)++;
}


#include "common.h"

extern s32 D_801270C8;
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s32 func_8012C750(s32 a0);

void func_8018D6B0(s32 a0) {
    s32 v1;
    struct {
        u16 f0;
        s16 f1;
        u16 f2;
        s16 f3;
        s16 f4;
        s16 f5;
        s16 f6;
        s16 f7;
        s32 f8;
    } local_var;

    v1 = D_801270C8;
    if (v1 != 8) {
        return;
    }

    local_var.f0 = D_80126B5E;
    local_var.f2 = D_80126B66;
    local_var.f3 = 0x5A;
    local_var.f1 = -0x940;
    local_var.f6 = 0xC0;
    local_var.f5 = 0;
    local_var.f4 = 0;
    local_var.f7 = 0;
    local_var.f8 = 0;

    func_8012C750((s32)&local_var);

    ((u16 *)a0)[1]++;
}


#include "common.h"

extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018D73C(void *a0)
{
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    if (D_801270C8 == 0x12) {
        buf.f06 = 0x5E;
        buf.f04 = 0;
        buf.f02 = 0;
        buf.f00 = 0;
        buf.f0A = 0;
        buf.f0C = 0;
        buf.f08 = 0xF5C0;
        buf.f0E = 0;
        buf.f10 = 0;

        func_8012C750((s32)&buf);

        buf.f08 = 0xF7C0;
        func_8012C750((s32)&buf);

        func_8002D4C8(0x8, 0x2);
        func_8002D4C8(0x50C, 0);

        *(u16*)((u8*)a0 + 0x2) += 1;
    }
}


void func_8018D7DC(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013C9C4(void *a0);
extern void func_8018EA04(s32 a0);
extern u8 D_80196BEC[];

void func_8018D7F0(void *a0)
{
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    if (D_801270C8 != 0x14) {
        s32 v = *(u32 *)((s32)a0 + 0x1C);
        *(u32 *)((s32)a0 + 0x1C) = v - 1;
        if ((v & 7) == 0) {
            func_8013C9C4(&D_80196BEC);
        }
    } else {
        buf.f06 = 0x5C;
        buf.f00 = 0;
        buf.f02 = 0;
        buf.f04 = 0;
        buf.f0A = 0;
        buf.f08 = 0;
        buf.f0C = 0;
        buf.f0E = 0;
        buf.f10 = 0;

        func_8012C750((s32)&buf);

        func_8018EA04(1);

        func_8002D4C8(0x4FA, 0);

        *(u16 *)((s32)a0 + 2) += 1;
    }
}


extern s32 D_801270C8;
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018EA04(s32 a0);

void func_8018D8A8(void *a0)
{
    if (D_801270C8 == 0x15) {
        func_8018EA04(2);
        func_8002D4C8(5, 0);
        *(u32 *)((s32)a0 + 0x1C) = 0xE;
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_8018D904(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


extern void func_8018F414(void);
extern s32 D_801270C8;

void func_8018D918(void *a0) {
    if (D_801270C8 >= 0x16) {
        func_8018F414();
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
}


#include "common.h"

extern s32 func_8012C588(s32 a0, s32 a1);

void func_8018D964(void *a0)
{
    func_8012C588(0x68, (s32)a0);
    *(u16 *)((s32)a0 + 0x2) += 1;
}


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);

void func_8018D9A4(void *a0)
{
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;
    s16 i;

    if (D_801270C8 == 0x18) {
        i = 0;
        buf.f06 = 0x5D;
        buf.f04 = 0;
        buf.f02 = 0;
        buf.f00 = 0;
        buf.f0A = 0;
        buf.f0C = 0;
        buf.f0E = 0;
        buf.f10 = 0;

        do {
            buf.f08 = i;
            func_8012C750((s32)&buf);
            i++;
        } while (i < 4);

        *(u16 *)((s32)a0 + 2) += 1;
    }
}


extern void func_80180A7C(void);
extern s32 D_801270C8;

void func_8018DA40(void *a0) {
    if (D_801270C8 == 0x1B) {
        func_80180A7C();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


extern void func_8018F704(void);
extern s32 D_801270C8;

void func_8018DA8C(void *a0) {
    if (D_801270C8 == 0x21) {
        func_8018F704();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_8018DAD8(void) {
}


extern void (*D_80196C9C[])(void);

void func_8018DAE0(void *a0) {
    D_80196C9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_80196C14;

void func_8018DB1C(s32 arg0) {
    *(s32 *)(arg0 + 0x58) = &D_80196C14;
    *(s32 *)(arg0 + 0x1C) = 0x18;
    *(s16 *)(arg0 + 0x2) += 1;
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8001C97C(s32 *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(s32);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80143994(s32 a0, s32 a1);

extern s32 D_80196BBC;
extern u8 D_801D852C[];
extern u8 D_801D8B8C[];
extern M2C_UNK D_80190C0C;
extern s32 D_800636C8;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_80126B6A;
extern u16 D_80126B72;

void func_8018DB40(void *a0) {
    void *s1;
    void *s2;
    void *s0;
    s32 v0;

    s1 = a0;
    v0 = *(s32 *)((u8 *)s1 + 0x1C);
    s2 = *(void **)((u8 *)s1 + 0x20);

    if (v0 != 0) {
        *(s32 *)((u8 *)s1 + 0x1C) = v0 - 1;
        return;
    }

    if (s2 == 0) {
        s32 *p = &D_80196BBC;
        *p = (s32)D_801D852C;
        if (func_8012C354((s32)s1, (s32)(p - 1)) == 0) {
            return;
        }
    }

    s2 = (void *)((s32 (*)(void))func_8012C1B8)();
    if (s2 == 0) {
        return;
    }

    s0 = D_801D8B8C;
    func_8001C97C((s32 *)s0);
    func_8001C214((s32)s2, (s32)s0);

    *(s16 *)((u8 *)s2 + 0x12) = -0x200;
    ((void (*)(s32, s32))func_8001C1E4)((s32)s2, *(s32 *)((u8 *)s1 + 0x20));

    *(s32 *)((u8 *)s2 + 0x20) = (s32)&D_800636C8;
    *(s16 *)((u8 *)s2 + 0xA) = -0x38;
    *(void **)((u8 *)s1 + 0xD0) = s2;
    func_8012A828((s32)s1, (void *)&D_80190C0C);

    if (*(s16 *)((u8 *)s1 + 0x70) != 0) {
        u16 t2;
        u16 t70;
        *(s16 *)((u8 *)s1 + 0x6) = -0x80;
        *(s16 *)((u8 *)s1 + 0xA) = -0xA40;
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus10)
        t2 = *(u16 *)((u8 *)s1 + 0x2);
        t70 = *(u16 *)((u8 *)s1 + 0x70);
        t2 = t2 + 2;
        *(u16 *)((u8 *)s1 + 0xE) = t70;
        *(u16 *)((u8 *)s1 + 0x2) = t2;
    } else {
        register s32 g __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus10)
        *(s16 *)((u8 *)s1 + 0x6) = D_80126B5E;
        *(s16 *)((u8 *)s1 + 0xA) = D_80126B62 - 0x200;
        g = D_80126B66;
        *(s16 *)((u8 *)s1 + 0xE) = g;
        g = D_80126B6A;
        *(s16 *)((u8 *)s1 + 0x16) = 4;
        *(s16 *)((u8 *)s1 + 0x12) = (s16)g >> 1;
        *(s16 *)((u8 *)s1 + 0x1A) = (s16)D_80126B72 >> 1;
        *(s32 *)((u8 *)s1 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)((s32)s1, 0x3000);
    }

    *(u16 *)((u8 *)s1 + 0x2) = *(u16 *)((u8 *)s1 + 0x2) + 1;
}


#include "common.h"

extern s32 func_8012D714(s32 a0, u32 a1);
extern u16 D_80126B96;
extern s16 D_80126B98;
extern void func_8012AD80(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8001C97C(s32 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801D9044;

void func_8018DCD8(s32 a0)
{
    s32 s3;
    s16 i;

    s3 = *(s32 *)(a0 + 0x20);
    if (func_8012D714(a0, 2) != 0) {
        D_80126B96 = 0x4001;
        D_80126B98 = 5;
    }
    func_8012AD80(a0);
    if (*(s16 *)(a0 + 0xA) >= -0x802) {
        *(s16 *)(a0 + 0xA) = -0x802;
        **(s16 **)(a0 + 0xD0) = 0;
        for (i = 0; i < 8; i++) {
            func_8012C658(99, i, a0);
            func_8012C658(100, i, a0);
        }
        func_8001C97C((s32 *)&D_801D9044);
        *(s32 *)(s3 + 0x24) = &D_801D9044;
        *(s32 *)(a0 + 0x1C) = 0x10;
        func_8002D4C8(0x4FF, 0);
        *(u16 *)(a0 + 2) += 1;
    } else {
        *(s32 *)(a0 + 0x14) += 0x1C000;
    }
}


extern void func_801439C0(u8 *a0);
extern void func_8012C218(void *a0);

void func_8018DDFC(void *a0) {
    s32 var;
    void *p;

    var = *(s32 *)((s32)a0 + 0x1C);
    var = var - 1;
    *(s32 *)((s32)a0 + 0x1C) = var;
    if (var == -1) {
        p = *(void **)((s32)a0 + 0xD0);
        if (p != NULL) {
            *(s16 *)((s32)p + 0) = 0;
        }
        func_801439C0((u8 *)*(s32 *)((s32)a0 + 0xCC));
        func_8012C218((void *)a0);
    }
}


extern s32 D_801270C8;
extern void func_801439C0(u8 *a0);
extern void func_8012C218(void *a0);

void func_8018DE5C(void *a0) {
    void *p;

    if (D_801270C8 > 0x15) {
        p = *(void **)((s32)a0 + 0xD0);
        if (p != NULL) {
            *(s16 *)((s32)p + 0) = 0;
        }
        func_801439C0((u8 *)*(s32 *)((s32)a0 + 0xCC));
        func_8012C218((void *)a0);
    }
}


void func_8018DEB8(s16 param_1) {
    struct {
        s16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    buf.f0A = 0;
    buf.f0C = 0;
    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f0E = 0;
    buf.f10 = 0;

    switch (param_1) {
    case 0:
        func_8018EA04(3);
        break;
    case 1:
        func_8018EA04(4);
        buf.f04 = 0xB80;
        break;
    case 2:
        func_8018EA04(5);
        buf.f00 = -0xC00;
        buf.f04 = 0xC00;
        break;
    }

    buf.f06 = 0x5C;
    buf.f08 = param_1 + 1;
    func_8012C750((s32)&buf);
}



extern void (*D_80196CB0[])(void);

void func_8018DF88(void *a0) {
    D_80196CB0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8018F5C4(void);
extern void func_8018F5EC(void);
extern void func_8018F614(void);
extern void func_8018F6DC(void);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018E7E4();
extern void func_8012C1B8(void);
extern void func_8012C218(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);

extern u8 D_80196C00[];
extern s32 D_801E7ECC[];
extern s32 D_801EA378[];
extern s32 D_801EC6FC[];
extern s32 D_801EEA80[];
extern u8 D_801E7F24[];
extern u8 D_801EEAAC[];

void func_8018DFC4(void *a0) {
    /* Block scope on purpose (this TU's own house style, used a few functions
       up): the file-scope declarations of these two arrays sit BELOW this stub
       and carry an anonymous struct typedef that cannot be forward-referenced
       or re-spelled here.  At block scope gcc-2.7.2 downgrades the clash to a
       warning; at file scope it is a hard "conflicting types" error. */
    typedef struct { u32 f0; u32 f4; } Pair8;
    extern Pair8 D_801E4998[];
    extern Pair8 D_801E499C[];
    struct { s16 f00, f02, f04, f06, f08, f0A, f0C, f0E; s32 f10; u8 pad14[0x14]; } sp18;
    struct { s16 f00, f02, f04, f06, f08, f0A, f0C, f0E; s32 f10; u8 pad14[0x14]; } sp40;
    void *s0;
    s32 *tbl;
    s16 count;
    void *vecs;
    s16 i;
    s32 val;
    s32 obj;

    s0 = a0;

    switch (*(s16 *)((u8 *)s0 + 0x70)) {
    case 0:
        func_8018F5C4();
        tbl = D_801E7ECC;
        break;
    case 1:
        func_8018F5EC();
        tbl = D_801EA378;
        break;
    case 2:
        func_8018F614();
        tbl = D_801EC6FC;
        break;
    case 3:
        func_8018F6DC();
        tbl = D_801EEA80;
        break;
    }

    if (*(s16 *)((u8 *)s0 + 0x70) == 0) {
        count = 0x15;
        vecs = D_801E7F24;
        sp40.f00 = -0x80;
        sp40.f02 = -0xDE0;
        sp40.f04 = -0xC50;
    } else {
        count = 0xA;
        vecs = D_801EEAAC;
        sp40.f00 = -0x64;
        sp40.f02 = -0x884;
        sp40.f04 = -0x8B0;
    }

    if (*(s16 *)((u8 *)s0 + 0x70) < 4) {
        func_8013C9C4(D_80196C00);
        func_8002D4C8(0x500, 0);
        for (i = 0; i < count; i++) {
            val = tbl[i];
            D_801E499C[i].f0 = 0;
            D_801E4998[i].f0 = val;
        }
        sp18.f0C = 0;
        sp18.f0A = 0;
        if (*(s16 *)((u8 *)s0 + 0x70) == 3) {
            sp18.f0C = -0x400;
        } else {
            sp18.f0C = 0;
        }
        sp18.f10 = 0;
        sp18.f06 = 0x5C;
        sp18.f08 = *(u16 *)((u8 *)s0 + 0x70) + 4;
        func_8018E7E4((s32)s0, &sp18, vecs, &sp40, count);
        func_8012C218(s0);
    } else {
        obj = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)((u8 *)s0 + 0x20) = obj;
        if (obj == 0) {
            func_8012C218(s0);
        } else {
            func_8001C214(obj, (s32)&D_801E4998[*(s16 *)((u8 *)s0 + 0xFC)]);
            func_8001D0E8(*(s32 *)((u8 *)s0 + 0x20), 0x7FFF, 0x7FFF);
            *(s16 *)((u8 *)s0 + 2) = 3;
        }
    }
}


void func_8018E22C(void) {
}

extern void func_8012C218(void *a0);

void func_8018E234(void *a0) {
    s32 var;
    void *p;

    var = *(s32 *)((s32)a0 + 0x1C);
    p = *(void **)((s32)a0 + 0x20);
    var = var - 1;
    *(s32 *)((s32)a0 + 0x1C) = var;
    if (var != 0) {
        if (var < 0x10) {
            *(s32 *)((s32)p + 4) ^= 0x80000000;
        }
    } else {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_8018E288(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x1C);

    if (v1 < 0x24) {
        v1 = v1 + 1;
        *(s32 *)((s32)a0 + 0x1C) = v1;
        if (v1 == 1) {
            return;
        }
        if (*(s16 *)((s32)a0 + 0x70) == 4) {
            if (*(s16 *)((s32)a0 + 0xA) < -0x800) {
                void *p;

                *(s32 *)((s32)a0 + 0x48) = 0x1C000;
                func_8012AD80((s32)a0);

                p = *(void **)((s32)a0 + 0x20);
                *(s16 *)((s32)p + 0x10) -= (*(s32 *)((s32)a0 + 0x18) << 4) >> 16;

                p = *(void **)((s32)a0 + 0x20);
                *(s16 *)((s32)p + 0x14) -= (*(s32 *)((s32)a0 + 0x10) << 4) >> 16;
            }
        } else {
            if (*(s16 *)((s32)a0 + 0x6) < -0x5FF || *(s16 *)((s32)a0 + 0xA) < -0x7FF) {
                if (*(s16 *)((s32)a0 + 0xA) >= -0x3FF) {
                    func_8012C218((void *)a0);
                } else {
                    void *p;
                    s32 t;

                    *(s32 *)((s32)a0 + 0x48) = 0x1C000;
                    func_8012AD80((s32)a0);

                    p = *(void **)((s32)a0 + 0x20);
                    *(s16 *)((s32)p + 0x10) -= (*(s32 *)((s32)a0 + 0xDC) << 4) >> 16;

                    if (*(s16 *)((s32)a0 + 0x70) != 7) {
                        t = *(s32 *)((s32)a0 + 0x10);
                    } else {
                        t = *(s32 *)((s32)a0 + 0x18);
                    }
                    p = *(void **)((s32)a0 + 0x20);
                    *(s16 *)((s32)p + 0x12) += (t << 4) >> 16;
                }
            }
        }
    } else {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) - 1;
    }
}



extern void (*D_80196CC0[])(void);

void func_8018E400(void *a0) {
    D_80196CC0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018E43C(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


extern s32 D_801270C8;
extern void func_8012C1B8(void);
extern void func_8012C218(void *a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8018EA04(s32 a0);
extern void func_8018F63C(void);
extern void func_8018F664();
extern void func_8018F68C();
extern void func_8018F6B4();
extern void func_8018E7E4();
extern u32 D_801F01D4[];
extern u8 D_801F0220[];
extern u8 D_80196C00[];

typedef struct { u32 f0; u32 f4; } E8_8018E450;
extern E8_8018E450 D_801E499C[];
extern E8_8018E450 D_801E4998[];

void func_8018E450(void *a0)
{
    struct { s16 f00, f02, f04, f06, f08, f0A, f0C, f0E; s32 f10; } buf;
    s16 arr[3];
    s16 i;
    s32 lim;
    s32 bound;
    u32 *p;
    s32 ret;
    u16 w0;

    switch (*(s16 *)((s32)a0 + 0x70)) {
    case 0:
        if (D_801270C8 != 0x19) {
            return;
        }
        func_8018F63C();
        func_8018EA04(6);
        break;
    case 1:
        if (D_801270C8 != 0x1A) {
            return;
        }
        func_8018F664();
        func_8018EA04(7);
        *(s16 *)((s32)a0 + 6) = -0x600;
        w0 = 0x700;
        goto store;
    case 2:
        if (D_801270C8 != 0x1C) {
            return;
        }
        func_8018F68C();
        func_8018EA04(8);
        w0 = 0x400;
        goto store;
    case 3:
        if (D_801270C8 != 0x1D) {
            return;
        }
        func_8018F6B4();
        func_8018EA04(9);
        *(s16 *)((s32)a0 + 6) = -0x180;
        w0 = 0x400;
    store:
        *(s16 *)((s32)a0 + 0xE) = w0;
        break;
    }
    if (*(s16 *)((s32)a0 + 0x70) < 4) {
        func_8013C9C4(&D_80196C00);
        func_8002D4C8(0x502, 0);
        lim = 0x12;
        p = D_801F01D4;
        i = 0;
        bound = 0x12;
        arr[0] = -0x204;
        arr[1] = -0x804;
        arr[2] = 0x73E;
        do {
            u32 v = p[i];
            D_801E499C[i].f0 = 0;
            D_801E4998[i].f0 = v;
            i++;
        } while (i < bound);
        buf.f0C = 0;
        buf.f0A = 0;
        if (*(s16 *)((s32)a0 + 0x70) == 1) {
            buf.f0C = 0x400;
        } else {
            buf.f0C = 0;
        }
        buf.f10 = 0;
        buf.f06 = 0x5D;
        buf.f08 = *(u16 *)((s32)a0 + 0x70) + 4;
        func_8018E7E4((s32)a0, &buf, &D_801F0220, arr, lim);
    } else {
        ret = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)((s32)a0 + 0x20) = ret;
        if (ret != 0) {
            goto nonzero;
        }
    }
    func_8012C218(a0);
    return;
nonzero:
    func_8001C214(ret, (s32)&D_801E4998[*(s16 *)((s32)a0 + 0xFC)]);
    func_8001D0E8(*(s32 *)((s32)a0 + 0x20), 0x7FFF, 0x7FFF);
    *(s16 *)((s32)a0 + 2) = 4;
}


void func_8018E6D4(void) {
}

extern void func_8012C218(void *a0);

void func_8018E6DC(void *a0) {
    s32 var;
    void *p;

    var = *(s32 *)((s32)a0 + 0x1C);
    p = *(void **)((s32)a0 + 0x20);
    var = var - 1;
    *(s32 *)((s32)a0 + 0x1C) = var;
    if (var != 0) {
        if (var < 0x10) {
            *(s32 *)((s32)p + 4) ^= 0x80000000;
        }
    } else {
        func_8012C218((void *)a0);
    }
}


extern void func_8012AD80(s32 a0);

void func_8018E730(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x1C);

    if (v1 < 0x28) {
        v1 = v1 + 1;
        *(s32 *)((s32)a0 + 0x1C) = v1;
        if (v1 == 1) {
            return;
        }
        if (*(s16 *)((s32)a0 + 0xA) < -0x800) {
            void *p;

            *(s32 *)((s32)a0 + 0x48) = 0x38000;
            func_8012AD80((s32)a0);

            p = *(void **)((s32)a0 + 0x20);
            *(s16 *)((s32)p + 0x10) -= (*(s32 *)((s32)a0 + 0x18) << 4) >> 16;

            p = *(void **)((s32)a0 + 0x20);
            *(s16 *)((s32)p + 0x14) -= (*(s32 *)((s32)a0 + 0x10) << 4) >> 16;
        }
    } else {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) - 1;
    }
}




extern Blk20 D_800AE620;
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 func_8012C750(s32 a0);
extern void RotMatrixY(s32 a0, void *a1);

void func_8018E7E4(arg0, arg1, arg2, arg3, count)
    s32 arg0;
    void *arg1;
    void *arg2;
    void *arg3;
    s16 count;
{
    Blk20 mat;
    u16 vec[3];
    s16 out[3];
    s16 i;
    s32 prim;
    s32 val;

    mat = D_800AE620;
    RotMatrixY(*(s16 *)((s32)arg1 + 0xC), &mat);
    for (i = 0; i < count; i++) {
        vec[0] = *(u16 *)((s32)arg2 + i * 12);
        vec[1] = *(u16 *)((s32)arg2 + i * 12 + 2);
        vec[2] = *(u16 *)((s32)arg2 + i * 12 + 4);
        ApplyMatrixSV(&mat, vec, out);
        *(u16 *)((s32)arg1 + 0) = *(u16 *)((s32)arg0 + 6) + out[0];
        *(u16 *)((s32)arg1 + 2) = *(u16 *)((s32)arg0 + 0xA) + out[1];
        *(u16 *)((s32)arg1 + 4) = *(u16 *)((s32)arg0 + 0xE) + out[2];
        *(u16 *)((s32)arg1 + 0xE) = i;
        prim = func_8012C750((s32)arg1);
        if (prim != 0) {
            out[0] = vec[0] - *(u16 *)((s32)arg3 + 0);
            out[1] = vec[1] - *(u16 *)((s32)arg3 + 2);
            out[2] = vec[2] - *(u16 *)((s32)arg3 + 4);
            VectorNormalSS(out, out);
            ApplyMatrixSV(&mat, out, out);
            val = (out[0] << 9) + (out[0] << 8);
            *(s32 *)(prim + 0x10) = val;
            val = (out[1] << 9) + (out[1] << 8);
            *(s32 *)(prim + 0xDC) = val;
            *(s32 *)(prim + 0x14) = val;
            val = (out[2] << 9) + (out[2] << 8);
            *(s32 *)(prim + 0x18) = val;
        }
    }
}
