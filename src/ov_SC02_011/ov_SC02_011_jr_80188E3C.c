#include "common.h"
#include "../shared/engine_core.h"
#include "ov_SC02_011_shared.h"

/* P31 S74 — split out of src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c at a jtbl-span TU boundary
 * (vram 0x80188E3C-end of code, file 0x60CE4-0x68B8C). This TU owns .rodata span C
 * (0x801E9E3C-0x801E9E68, the TWO tables of func_80188E3C); the parent TU owns span A and its
 * sibling owns span B, and one object contributes exactly ONE contiguous .rodata run. See
 * config/splat.ov_SC02_011.yaml and cookbook §426/§431. Declarations shared with the sibling
 * TUs live in src/ov_SC02_011/ov_SC02_011_shared.h. */

#include "common.h"

extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012A828(s32 a0, void *a1);
extern void func_801890C8(s32 a0);

extern u8  D_801960A0[];
extern u8  D_801D3ACC[];
extern s16 D_801D3B74;
extern s16 D_801D3F84;
extern s16 D_801D458C;

void func_80188E3C(s32 a0) {
    s32 v0;
    s32 v1;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        v1 = *(s32 *)(a0 + 0x1C);
        v0 = 7;
        goto cmpA;
    case 1:
        v0 = func_8012B8E4(a0, 6);
        v1 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + v0;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = v1;
        break;
    case 2:
        v1 = *(s32 *)(a0 + 0x1C);
        v0 = 0xA;
    cmpA:
        if (v1 == v0) {
            func_8012D5E4(a0, (s32)D_801960A0, (s32)(D_801960A0 + 8), 0xB);
        }
        break;
    case 3:
        if (*(s32 *)(a0 + 0x1C) == 0xB) {
            func_8012D5E4(a0, (s32)D_801960A0, (s32)(D_801960A0 + 8), 0x11);
        }
        break;
    case 4:
        v0 = func_8012B8E4(a0, 6);
        v1 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + v0;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = v1;
        if (*(s32 *)(a0 + 0x1C) == 0xC) {
            func_801890C8(a0);
        }
        break;
    }

    if (func_8012BEE8(a0) != 0) {
        switch (*(u16 *)(a0 + 0x34)) {
        case 0:
            if (func_8012BD3C(a0, 0x400, 0x4000) != 0) {
                *(u16 *)(a0 + 0x34) = 1;
                func_8012A828(a0, D_801D3ACC);
                *(s32 *)(a0 + 0x1C) = 0xA;
            } else {
                *(u16 *)(a0 + 0x2) = 2;
                *(u16 *)(a0 + 0x34) = 0;
                func_8012A828(a0, &D_801D3B74);
            }
            break;
        case 1:
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0x1C) = 0x18;
            func_8012A828(a0, &D_801D3F84);
            break;
        case 2:
            *(u16 *)(a0 + 0x2) = 2;
            *(u16 *)(a0 + 0x34) = 0;
            func_8012A828(a0, &D_801D3B74);
            break;
        case 3:
            break;
        case 4:
            v0 = *(u16 *)(a0 + 0x100);
            v0 -= 1;
            *(u16 *)(a0 + 0x100) = v0;
            if ((v0 << 16) == 0) {
                *(u16 *)(a0 + 0x2) = 8;
                func_8012A828(a0, &D_801D458C);
            } else {
                *(s32 *)(a0 + 0x1C) = 0x1E;
            }
            break;
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 D_801960B4[];

void func_80189050(s32 param_1) {
    register s32 s0 __asm__("$16") = param_1;
    s32 *s1;

    __asm__ __volatile__("" : "=r"(s0) : "0"(s0));

    if ((*(u16 *)(s0 + 0x70) & 0x2000) == 0) {
        s1 = &D_801960B4[3];
    } else {
        s1 = &D_801960B4[0];
    }
    *(s16 *)(s0 + 2) = 7;
    func_8012A828(s0, (void *)s1[0]);
    func_8012B200((u8 *)s0);
    func_8012B178(s0, s1[1]);
    *(s32 *)(s0 + 0x1C) = s1[2];
}


#include "common.h"
#include "../shared/engine_core.h"

extern s16 D_801960CC;
extern s16 D_801960CE;
extern s16 D_801960D0;

extern s32 func_8018F488(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_801890C8(s32 a0) {
    struct S8012C658 sp;
    s32 vec[3];
    s32 out[3];
    s16 *p = &D_801960CC;

    func_8018F488(a0, (s32)p);

    vec[0] = *p << 8;
    vec[1] = D_801960CE << 8;
    vec[2] = D_801960D0 << 8;

    func_800484EC(*(s32 *)(a0 + 0x20) + 0x34, (s32)vec, (s32)out);

    out[0] += *(s16 *)(a0 + 0x6) << 8;
    out[1] += *(s16 *)(a0 + 0xA) << 8;
    out[2] += *(s16 *)(a0 + 0xE) << 8;

    sp.unk0 = out[0] / 256;
    sp.unk2 = out[1] / 256;
    sp.unk4 = out[2] / 256;
    sp.unk6 = 0x20;
    sp.unk8 = 1;
    sp.unkA = 0;
    sp.unk10 = 0;
    sp.unkE = 0;

    func_8012C51C(&sp, a0);
}


#include "common.h"

/* match_one's standalone common.h does not reach src/shared/engine_types.h where the
 * real TU's SV3 {short a,b,c} lives (via ../shared/engine_core.h); function-local name. */
typedef struct { s16 a, b, c; } SV3_801891E8;

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s16 D_801D3D64;
extern s16 D_801D3DEC;

extern void Square0(s32 *a0, s32 *a1);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

void func_801891E8(s32 param_1) {
    SV3_801891E8 pt;
    s32 v[4];

    if (*(u16 *)(param_1 + 0x34) == 0) {
        pt.a = D_80126B5E;
        pt.c = D_80126B66;
        v[0] = *(s16 *)(param_1 + 0x6) - pt.a;
        v[1] = 0;
        v[2] = *(s16 *)(param_1 + 0xE) - pt.c;
        Square0(&v[0], &v[0]);
        if (v[0] + v[2] <= 0x19000) {
            *(s16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
        }
    } else if ((func_8012CBCC(param_1) & 0x2000) != 0) {
        *(s16 *)(param_1 + 0x2) = 3;
        if ((*(u16 *)(param_1 + 0x86) & 2) != 0) {
            *(s16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x28;
            func_8012A828(param_1, &D_801D3D64);
            *(s16 *)(param_1 + 0xFE) = 0;
        } else {
            *(s16 *)(param_1 + 0x34) = 0;
            func_8012A828(param_1, &D_801D3DEC);
            *(s32 *)(param_1 + 0x1C) = 0x19;
            *(u16 *)(param_1 + 0x86) |= 2;
        }
    }
}


/* func_80189324 (ov_SC02_011) -- MATCH, 111/111 ins, match_one standalone.
 *
 * Second-pass fix of the first agent's 9-ins residual (schedule-loadhoist-regchoice).
 * The whole residual was gcc-2.7.2 sched1's LUID tie-break (sched.md S1): every insn in
 * the post-rand() block ties at INSN_PRIORITY 1 except the load-fed subu/sw pairs (pri 2),
 * so the emitted order inside the pri-1 group is exactly ASCENDING LUID = RTL expansion
 * order. Reading the target's block back as statement order gives the required LUID chain
 *     &d  <  (r & 0x1F)  <  lh 0x6  <  lh 0x88  <  (+0x28 / sw 0x1C)  <  d.vy = 0
 * i.e. the frame-address `p = &d` must expand FIRST after the call (that is what puts
 * `addiu $a0,$sp,0x10` at the block top instead of letting it fall into the load->subu
 * wedge), the mask must be split off from the +0x28 add, and both distance loads must be
 * their own statements ahead of the 0x1C store. No pins were needed for the hoist; the
 * $17 pin below is the first agent's (still load-bearing for the func_8012B744 arg).
 *
 * TU check (src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c): no existing decl of func_80189324
 * (INCLUDE_ASM only, L7901), so the definition signature is free. All callee decls copied
 * verbatim from the TU -- func_8012B030 L2607, func_8012B744 L2608, func_8012C354 L3721,
 * func_8012A828 L3723, func_80143970 L4283, rand L949, D_801D3B74 L7864. Square0 uses the
 * canonical engine_core.h form. D_80195FF0 / D_80196058 / (*(short *)D_801D3CBC) are absent from the
 * TU -- typed by access width (address-only lui/addiu).
 */
#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern void Square0(s32 *a0, s32 *a1);
extern s32 rand(void);

extern u8 D_80195FF0[];
extern void (*D_80196058[])(void);
extern short D_801D3B74;
extern u8 D_801D3CBC[];

typedef struct {
    s32 vx, vy, vz;
} Vec3_189324;

void func_80189324(s32 a0) {
    s32 idx;
    s32 v0;
    s32 sum;
    Vec3_189324 d;
    s32 r;
    Vec3_189324 *p;
    s32 dx, dz;
    s32 x;
    s32 v1;
    register void *s1_ptr __asm__("$17");

    idx = (*(u16 *)(a0 + 0x70) & 0xF00) >> 8;

    if (func_8012C354(a0, (s32)(D_80195FF0 + idx * 0x34)) == 0) {
        return;
    }

    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = -1;
    *(u8 *)(a0 + 0xC1) = 0;
    *(s32 *)(a0 + 0xBC) = (s32)D_80196058;
    func_80143970(a0);
    func_8012B030((u8 *)a0);

    if ((*(u16 *)(a0 + 0x70) & 0x6000) != 0) {
        *(s16 *)(a0 + 0x2) = 6;
        func_8012A828(a0, (void *)&D_801D3B74);
        return;
    }

    if ((*(u16 *)(a0 + 0x70) & 0x1) != 0) {
        *(s16 *)(a0 + 0x2) = 0xF;
        return;
    }

    if ((*(u16 *)(a0 + 0x70) & 0x100) != 0) {
        *(s16 *)(a0 + 0x2) = 9;
        return;
    }

    *(s16 *)(a0 + 0x2) = 1;
    *(s16 *)(a0 + 0x34) = 0;
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    r = rand();
    p = &d;
    r = r & 0x1F;
    dx = *(s16 *)(a0 + 0x6);
    dz = *(s16 *)(a0 + 0x88);
    *(s32 *)(a0 + 0x1C) = r + 0x28;

    p->vy = 0;
    p->vx = dx - dz;
    p->vz = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&p->vx, &p->vx);

    sum = d.vx + d.vz;
    s1_ptr = (void *)(a0 + 0x88);
    if (sum > 0x8FFFF) {
        *(s16 *)(a0 + 0xFC) = (s16)func_8012B744((void *)(a0 + 4), s1_ptr);
    } else {
        x = rand() & 0x3FF;
        v1 = x - 0x200;
        if (v1 >= 0) {
            v1 = x + 0x100;
        } else {
            v1 = x - 0x500;
        }
        v0 = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        v0 = (v0 + v1) & 0xFFF;
        *(s16 *)(a0 + 0xFC) = v0;
    }

    func_8012A828(a0, (void *)&(*(short *)D_801D3CBC));
}



extern void (*D_801960D4[])(void);

void func_801894E0(void *a0) {
    D_801960D4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_80188DF4();
extern void func_8012A828(s32 a0, void *a1);

extern short D_801D3B74;
extern short D_801D4494;

void func_8018951C(s32 param_1) {
    register s32 s0 __asm__("$16");
    s32 v0;

    s0 = param_1;
    if ((*(u16 *)(s0 + 0x72) & 0x4000) != 0) {
        *(u16 *)(s0 + 0x100) = 3;
        if (func_8012BD3C(s0, 0x400, 0x40000) != 0) {
            func_80188DF4(s0, 4, 0x1E, &D_801D4494);
        } else {
            *(u16 *)(s0 + 0x2) = 2;
            *(u16 *)(s0 + 0x34) = 0;
            func_8012A828(s0, &D_801D3B74);
        }
    }
}



extern void func_8012A828(s32, void*);
    extern short D_801D3B74;
    void func_801895A0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 10;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D3B74);
    }


void func_801895CC(s32 a0) {
    s32 v0;
    if (*(s16 *)(a0 + 0x100) == 0) {
        v0 = 0xB;
    } else {
        if (func_8012BD3C(a0, 0x400, 0x40000) == 0) {
            return;
        }
        v0 = 0xD;
    }
    *(s16 *)(a0 + 0x2) = v0;
}



extern void func_8012A828(s32, void*);
    extern short D_801D458C;
    void func_80189620(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 12;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&D_801D458C);
    }


void func_8018964C(void *arg0) {
    if (*(u16 *)((s32)arg0 + 0x72) & 0x4000) {
        *(u16 *)((s32)arg0 + 0x2) = 9;
        *(u16 *)((s32)arg0 + 0x100) = 3;
    }
}


extern short D_801D4494;
extern void func_8012A828(s32 a0, void *a1);

void func_80189674(a0)
s32 a0;
{
    *(s16 *)(a0 + 0x2) = 14;
    func_8012A828(a0, &(*(u8 *)&D_801D4494));
    *(s32 *)(a0 + 0x1C) = 0x1e;
}


#include "common.h"

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801890C8(s32 a0);

void func_801896B4(s32 param_1)
{
    s32 v;
    unsigned short *p;
    unsigned short val;

    v = func_8012B8E4(param_1, 6);
    p = (unsigned short *)(*(s32 *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);

    if (*(s32 *)(param_1 + 0x1C) == 0xC) {
        func_801890C8(param_1);
    }

    if (func_8012BEE8(param_1) == 0) {
        return;
    }

    val = *(unsigned short *)(param_1 + 0x100);
    val--;
    *(unsigned short *)(param_1 + 0x100) = val;

    {
        s32 v0_shifted = (s32)val << 16;
        if (v0_shifted == 0) {
            *(unsigned short *)(param_1 + 0x2) = 0xB;
        } else {
            *(s32 *)(param_1 + 0x1C) = 0x1E;
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801D3ACC[];

void func_8018974C(s32 a0) {
    s32 s0 = a0;
    func_8012A828(a0, D_801D3ACC);
    *(u16 *)(s0 + 2) = 0x10;
    func_8012B23C(s0);
    *(s32 *)(*(s32 *)(s0 + 0x20) + 4) |= 0x80000000;
}


#include "common.h"

extern void func_8002A04C(void);
extern void func_8012CBF4(s32);
extern void func_8012C098(void);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80188554(s32 a0);

void func_801897A4(s32 a0) {
    s16 field_a;
    s16 field_102;
    s32 result;

    field_a = *(s16 *)(a0 + 0xA);
    if (field_a >= 0x10) {
        field_102 = *(s16 *)(a0 + 0x102);
        if (field_102 == 0) {
            ((void (*)(s32))func_8002A04C)(a0);
        }
        ((void (*)(s32))func_8012C098)(a0);
    } else {
        result = ((s32 (*)(s32))func_8012CBF4)(a0);
        if ((result & 0x2000) != 0) {
            if ((result & 0x1000) != 0) {
                func_80131E00((struct S80131E00 *)a0, 0x12);
            } else {
                func_80188554(a0);
            }
        }
    }
}


extern void func_8012CBF4(s32);
extern void func_80188554(s32 a0);

void func_8018983C(s32 a0) {
    s32 s0;

    s0 = a0;
    ((void (*)(s32))func_8012CBF4)(a0);
    if (*(u16 *)(s0 + 0x72) & 0x4000) {
        func_80188554(s0);
    }
}


extern s32 func_8012BCCC(s32 a0);
extern void func_80189050(s32 a0);
extern s32 D_801960B0;

void func_80189880(void *a0) {
    s32 s0 = (s32)a0;
    if (func_8012BCCC(s0) < D_801960B0) {
        func_80189050(s0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

extern s16 D_801D3D64;
extern s16 D_801D3DEC;

void func_801898C8(s32 a0) {
    s32 v0;

    func_8012AD80(a0);
    if (*(u16 *)(a0 + 0x70) & 0x2000) {
        v0 = *(u16 *)(a0 + 0xFE) - 1;
        *(u16 *)(a0 + 0xFE) = v0;
        if ((s16)v0 <= 0) {
            func_80143B6C(a0, 0);
            *(u16 *)(a0 + 0xFE) = 8;
        }
    }
    if (func_8012BEE8(a0)) {
        *(u16 *)(a0 + 0x86) |= 2;
        *(s16 *)(a0 + 0x2) = 3;
        if (*(u16 *)(a0 + 0x86) & 2) {
            *(s16 *)(a0 + 0x34) = 1;
            *(s32 *)(a0 + 0x1C) = 0x28;
            func_8012A828(a0, &D_801D3D64);
            *(u16 *)(a0 + 0xFE) = 0;
        } else {
            *(s16 *)(a0 + 0x34) = 0;
            func_8012A828(a0, &D_801D3DEC);
            *(s32 *)(a0 + 0x1C) = 0x19;
            *(u16 *)(a0 + 0x86) |= 2;
        }
    }
}


#include "common.h"

extern void func_80189A50(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801EB9F4;
extern s32 D_801EB9F8;

void func_801899B4(void) {
    s32 v0;
    s32 v1;

    func_8013CB84();
    func_80189A50();

    v1 = D_801EB9F8;

    if (v1 == 1) goto L_handle_v0_1;

    if (v1 >= 2) {
        return;
    }

    if (v1 != 0) {
        return;
    }

    // v1 == 0
    func_8002D4C8(0x5E4, 0);
    v0 = D_801EB9F8;
    v0++;
    D_801EB9F8 = v0;
    return;

L_handle_v0_1:
    v0 = D_801EB9F4;
    v0++;
    D_801EB9F4 = v0;

    if (v0 < 0x97) {
        return;
    }

    func_8002D4C8(0xD, 0x5E4);
    v0 = D_801EB9F8;
    v0++;
    D_801EB9F8 = v0;
}


#include "common.h"

extern u16 D_8019611C[];
extern u16 D_8019615C[];
extern u16 D_801EB56C[];
extern u16 D_801EB5AC[];
extern s32 D_801EB568;
extern u8  D_8019617C[];
extern void func_800183E0(s32 a0);

void func_80189A50(void) {
    u32 i;
    u32 t;

    t = (u32)D_801EB568 >> 8;
    for (i = 0; i < 0x20; i++) {
        D_801EB56C[i] = D_8019611C[(t + i) & 0x1F] | 0x8000;
    }

    t = (u32)D_801EB568 >> 8;
    for (i = 0; i < 0x10; i++) {
        D_801EB5AC[i] = D_8019615C[(t + i) & 0xF] | 0x8000;
    }

    func_800183E0((s32)D_8019617C);

    D_801EB568 += 0x100;
}



extern void (*D_801961D4[])(void);

void func_80189B28(void *a0) {
    D_801961D4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029178(s32 arg);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012A828(s32 a0, void *a1);

void func_80189B64(s32 a0) {
    extern u8 D_801D4E54;
    extern u8 D_8019105C[];
    extern s16 D_801961AC;
    s32 h;
    if ((func_80029178(0x9F) & 0xFF) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    *(s16 *)(a0 + 0x5C) = 0x800;
    h = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = h;
    if (h == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(h, (s32)&D_801D4E54);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x140, 0xF0);
    *(s32 *)(a0 + 0x58) = (s32)&D_801961AC | 0x10000000 | 0x40000000;
    *(u8 *)(a0 + 0x75) = 1;
    *(u16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0x1C) = 0x1F;
    func_8012A828(a0, (void *)D_8019105C);
}


void func_80189C20(s32 arg0) {
    if (func_8012E778(arg0, 0x8200AA) != 1) {
        return;
    }
    if ((func_8014CB2C() & 0x7FFFFFFF) != 2) {
        return;
    }
    *(u16 *)((s32)arg0 + 0x2) = 2;
    *(u16 *)((s32)arg0 + 0xFC) = 1;
    *(s32 *)((s32)arg0 + 0x1C) = 0x3C;
}


void func_80189C90(s32 s0)
{
    s32 a0;
    s32 v1;
    s32 v0;
    s32 s1;
    s32 s2;

    s1 = *(s32 *)(s0 + 0x20);
    s2 = s1 + 0x10;
    if (rand() & 1) {
        v1 = rand();
        a0 = *(s16 *)(s0 + 0xFC);
        *(s16 *)(s1 + 0x10) = *(u16 *)(s1 + 0x10) + a0 * (v1 % 8 + 1);
    }
    v1 = *(s16 *)s2;
    if (v1 >= 0x39) {
        *(s16 *)(s0 + 0xFC) = -1;
        *(s16 *)s2 = 0x38;
        *(u16 *)(s0 + 0x100) += 1;
        func_8018A084(s0);
        func_80189F30(s0);
        *(s16 *)(s0 + 0xFE) = 5;
        func_8002D4C8(0x661, 0);
    } else {
        if (v1 < 0) {
            *(s16 *)(s0 + 0xFC) = 1;
            *(s16 *)s2 = 0;
        }
    }
    if (*(s16 *)(s0 + 0xFE) != 0) {
        func_80189F30(s0);
        *(u16 *)(s0 + 0xFE) -= 1;
    }
    if (*(s16 *)(s0 + 0x100) >= 2) {
        func_8012B2CC(s0);
        func_8012B200((u8 *)s0);
        func_8012B178(s0, 0xFFFE0000);
        *(s16 *)(s0 + 2) = 3;
        *(s32 *)(s0 + 0x1C) = 10;
        *(s32 *)(s0 + 0xDC) = 0x1F;
        func_8002D4C8(0x61D, 0);
    }
}


void func_80189E00(s32 a0) {
    extern u8 D_801961BC[];
    register s32 s0 __asm__("$16") = a0;
    s32 v0, v1;

    v0 = *(s32 *)(s0 + 0xDC);
    if (v0 != 0) {
        v0 = v0 - 1;
        *(s32 *)(s0 + 0xDC) = v0;
        func_800D0C48(1);
    }

    if (*(u16 *)(s0 + 0x34) == 0) {
        v1 = *(s32 *)(s0 + 0x20);
        v0 = *(u16 *)(v1 + 0x10) + 0x20;
        *(u16 *)(v1 + 0x10) = v0;
        func_8012B178(s0, 0xFFFE0000);
        func_8012AD80(s0);
        v1 = *(s32 *)(s0 + 0x20);
        v0 = *(s16 *)(v1 + 0x10);
        if (v0 < 0x400) goto end;
        *(s16 *)(v1 + 0x10) = 0x400;
        v0 = *(u16 *)(s0 + 0x34) + 1;
        *(u16 *)(s0 + 0x34) = v0;
        func_8012B23C(s0);
    } else {
        v0 = func_8012CBCC(s0);
        if ((v0 & 0x2000) != 0) {
            func_8013C9C4((void *)&D_801961BC);
            func_80029124(0x9F, 1);
            func_8002D4C8(0x61C, 0);
            *(s16 *)(s0 + 2) = 4;
        }
    }
end:
    return;
}


extern s32 func_800D0CE0(void);
    extern void func_8012C218(void *a0);
    void func_80189EF4(void *a0) {
        if (((s32 (*)(s32))func_800D0CE0)((s32)a0) == 1) {
            ((void (*)(s32))func_8012C218)((s32)a0);
        }
    }


extern u16 D_801961CE;
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_80143BDC(u16 *a0);
extern s32 rand(void);

#define SRM_80189F30(r0) __asm__ volatile (          \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define STM_80189F30(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_80189F30(void *param_1) {
    s16 v[8];
    register s32 i __asm__("$17");
    s32 r;
    s32 t;
    s32 flag;
    s32 *m;

    v[1] = D_801961CE;
    m = (s32 *)(*(s32 *)((s32)param_1 + 0x20) + 0x34);
    SRM_80189F30(m);
    STM_80189F30(m);
    for (i = 0; i < 10; i++) {
        r = rand() % 144;
        if (rand() & 1) {
            t = r;
        } else {
            t = -r;
        }
        v[0] = t;
        r = rand() % 48;
        v[2] = ((rand() & 1) ? r : -r) - 48;
        RotTransSV(&v[0], &v[4], &flag);
        func_80143BDC((u16 *)&v[4]);
    }
}


#include "common.h"

extern u16 D_801961CE;
extern void func_8017C294(s32 a0, s16 *a1, s16 a2);

void func_8018A084(s32 a0) {
    s16 v[3];
    register s32 i __asm__("$17");
    s32 r;

    v[1] = D_801961CE;
    for (i = 0; i < 5; i++) {
        s32 t;

        r = rand() % 144;
        if (rand() & 1) {
            t = r;
        } else {
            t = -r;
        }
        v[0] = t;
        r = rand() % 48;
        v[2] = ((rand() & 1) ? r : -r) - 48;
        func_8017C294(a0, v, 1);
    }
}


extern s32 D_8012704C;

s32 func_8018A184(void) {
    if (D_8012704C == 0) {
        return 0x18;
    }
    return 0x2B;
}


#include "common.h"

extern void func_8012A418(void);
extern void func_8012A598(void);
extern void func_8012A018(s32, s32);

extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s32 D_801269E4;

void func_8018A284(void *a0);

typedef struct { u16 a, b, c, d; } __attribute__((aligned(2))) DataBlock;

void func_8018A1A4(void *a0) {
    u8 *s1;
    u8 *s0;
    register u8 *a1 __asm__("$5");

    s1 = (u8 *)a0;
    s0 = *(u8 **)(s1 + 0xDC);

    func_8012A418();
    func_8012A598();

    D_80126954 = *(s32 *)(void *)s0;
    D_8012695C = *(s32 *)(void *)(s0 + 4);

    /* Load address of D_80126968 into a1 */
    a1 = (u8 *)&D_80126968;

    /* Direct struct assignment for 8-byte unaligned copy */
    *(DataBlock *)(void *)a1 = *(DataBlock *)(void *)(s0 + 8);

    D_80126976 = *(s16 *)(s0 + 0x10);
    D_80126978 = *(s16 *)(s0 + 0x12);
    D_8012697A = *(s16 *)(s0 + 0x14);

    ((void (*)(void *, s32))func_8012A018)((void *)func_8018A284, 0);

    D_801269E4 = *(s32 *)(void *)(s1 + 0xDC);
}


extern void func_8012A4BC(void);
    void func_8018A264(void) {
        ((s32 (*)(void))func_8012A4BC)();
    }



extern void (*D_801D6268[])(void);

void func_8018A284(void *a0) {
    D_801D6268[*(u8 *)((s32)a0 + 0x4)]();
}


extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern void func_8018A438(s32);

void func_8018A2C0(s32 param_1)
{
    s32 iVar1;

    iVar1 = *(s32 *)(param_1 + 0x9C);
    if ((*(u16 *)(iVar1 + 0x1E) & 1) != 0) {
        s16 *p = &D_80126940;
        if (*(s16 *)(iVar1 + 0x18) < *p) {
            *p = *(s16 *)(iVar1 + 0x18);
        }
    }
    if ((*(u16 *)(iVar1 + 0x1E) & 2) != 0) {
        s16 *p = &D_80126942;
        if (*(s16 *)(iVar1 + 0x1A) < *p) {
            *p = *(s16 *)(iVar1 + 0x1A);
        }
    }
    if ((*(u16 *)(iVar1 + 0x1E) & 4) != 0) {
        s16 *p = &D_80126944;
        if (*(s16 *)(iVar1 + 0x1C) < *p) {
            *p = *(s16 *)(iVar1 + 0x1C);
        }
    }
    if ((*(u16 *)(iVar1 + 0x26) & 1) != 0) {
        s16 *p = &D_80126940;
        if (*p < *(s16 *)(iVar1 + 0x20)) {
            *p = *(s16 *)(iVar1 + 0x20);
        }
    }
    if ((*(u16 *)(iVar1 + 0x26) & 2) != 0) {
        s16 *p = &D_80126942;
        if (*p < *(s16 *)(iVar1 + 0x22)) {
            *p = *(s16 *)(iVar1 + 0x22);
        }
    }
    if ((*(u16 *)(iVar1 + 0x26) & 4) != 0) {
        s16 *p = &D_80126944;
        if (*p < *(s16 *)(iVar1 + 0x24)) {
            *p = *(s16 *)(iVar1 + 0x24);
        }
    }
    func_8018A438(param_1);
}


#include "../shared/engine_core.h"  /* match_one-only: gives MATRIX/SVECTOR; the real TU already includes this */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;

void func_8018A438(s32 param_1) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    s16 *p;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    p = &D_80126940;
    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)*p;
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)D_80126942;
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)D_80126944;
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + *p;
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + D_80126942;
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + D_80126944;
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}



extern void (*D_801D626C[])(void);

void func_8018A5E4(void *a0) {
    D_801D626C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_8018A620(void) {
        ((void (*)(void))func_8012AD50)();
    }


extern s32 D_80126B58;
extern s32 func_80172688(s32 *a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);
void func_8018A1A4(void *a0);

void func_8018A640(s32 *a0) {
    if (func_80172688(&D_80126B58)) {
        func_8018A1A4(a0);
        func_8012BF4C(a0, 0x20);
        func_8012AD50(a0);
    }
}


extern s32 D_80126B58;
extern s32 func_80172688(s32 *a0);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018A264(void);

void func_8018A698(s32 *a0) {
    if (func_80172688(&D_80126B58) == 0) {
        if (func_8012BEE8((s32)a0) != 0) {
            func_8018A264();
            (*(u16 *)((s32)a0 + 2))--;
        }
        return;
    }
    func_8012BF4C(a0, 0x20);
}


void func_8018A708(void) {

    extern s16 D_801EB6E4;
    s16 *p = &D_801EB6E4;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_8018A72C — cookbook §71 (sibling-first).
 * func_8018A7CC is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_8018A7CC(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_8018A8E8 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
 * lh+6 => the sp+0x10 local is a 4 x s16 record.
 *
 * Two levers took it 32 -> 2 -> 0 (match_one MATCH, rtu_match MATCH):
 *  1. LENGTH-DRIFT (-2, cookbook §78): writing `sp10.unk2 = i * 0x100`
 *     leaves gcc-2.7.2 recomputing `sll v0,s1,8` instead of building the
 *     strength-reduced giv, so only s0..s3 get saved and the frame is two
 *     instructions short.  An EXPLICIT accumulator (`ang += 0x100`) forces
 *     the second callee-saved register ($s2) and restores sw/lw $s4.
 *  2. REGALLOC-PERM $s1>$s2 (cookbook §3-T2, source order drives emission):
 *     `ang = 0;` on its own line before the loop emits the $s2 zero-init
 *     FIRST.  Folding it into the for-init (`for (i = 0, ang = 0; ...)`)
 *     puts $s1's zero-init first, which is the target order.
 */


extern void func_8018A7CC(s32 arg0, s32 arg1, s32 arg2);
extern void func_8018A8E8(s32 arg0, Rec_8018A6A4_8018A72C *arg1, s32 arg2, s32 arg3);

void func_8018A72C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_8018A72C sp10;
    s32 i;
    s32 ang;

    func_8018A7CC(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_8018A8E8(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}



    extern s16 D_801EB6DE;
    extern s16 D_801EB6E0;
    extern s16 D_801EB6E2;
    void func_8018A7CC(s32 arg0, s32 arg1, s32 arg2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_801EB6DC;
        D_801EB6DC = *(u16 *)((s32)arg0 + 0x0);
        D_801EB6DE = *(u16 *)((s32)arg0 + 0x2);
        D_801EB6E0 = arg1;
        D_801EB6E2 = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018A7FC(s32 a0) {

    extern u8 D_800AF648;
    extern s16 D_801EB6DC;
    extern s16 D_801EB6DE;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801EB6DC = sxy[0];
    D_801EB6DE = sxy[1];
}



extern s16 D_801EB6E2;
    void func_8018A874(s32 arg0) {
        *(s16 *)((s32)&D_801EB6E2 + 0x0) += arg0;
    }


extern s32 func_8018A9BC(void);
extern void func_8018A8E8();

void func_8018A890(s32 a0, s32 a1, s32 a2) {
    s32 v0 = func_8018A9BC();
    if (v0 >= 0) {
        func_8018A8E8(v0, (void *)a0, a1, a2);
    }
}



/* func_8018A8E8 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
 *
 * THREE in-TU collisions, all fixed without touching an emitted instruction
 * (src/ov_SC03_014/ov_SC03_014_jr_801848E4.c):
 *
 * (1) memcpy — cookbook §2959 / the sibling note at TU L3742.  The TU declares
 *     memcpy THREE times: L81 + L1518 with the builtin-compatible signature
 *     (void*, const void*, unsigned) and then L1524 as
 *     `extern void *memcpy(void *dst, void *src, s32 n);`.  L1524 disagrees with
 *     gcc's built-in, so duplicate_decls "throws away the built-in" (warning only,
 *     because the old decl was still DECL_BUILT_IN) and installs a PLAIN function
 *     decl.  Two consequences at the splice point (L3635):
 *       a. my own builtin-shaped redeclaration now conflicts with a plain decl —
 *          hard error ("conflicting types for `memcpy'", :3637 vs :1524);
 *       b. even if it compiled, the identifier `memcpy` is no longer a builtin
 *          here, so both copies would lower to `jal memcpy` — but the TARGET
 *          bytes are the INLINE block move (lwl 3 / lwr 0 / swl / swr, no jal).
 *     Fix = do not name memcpy at all: a 4-byte STRUCT ASSIGN through an
 *     ALIGN-1 struct (u8 x4).  That is exactly the sibling func_8018ADA8 lever
 *     in this same TU (TU L3736-3744, cookbook §48-C2): align 1 routes
 *     mips.c expand_block_move, which copy_addr_to_reg's the source into one
 *     held register -> the identical lwl/lwr + swl/swr pair, zero memcpy ref.
 *     The typedef is BLOCK-scoped so it cannot collide with the TU's own
 *     block-scoped `V4` at L3758.
 *
 * (2) func_8018A8E8 itself — the TU prototypes it at L3570 as
 *     `extern void func_8018A8E8(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_8018A8E8") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_801EB6E4 / rand — declared VERBATIM as the TU already has them
 *     (D_801EB6E4: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_8018A8E8");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_801EB6E4;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801EB6E4);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_8018A8E8 *)((u8 *)s1 + 6) = *(B4_8018A8E8 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_8018A8E8 *)((u8 *)s1 + 10) = *(B4_8018A8E8 *)a3;
    *(u8 *)((u8 *)s1 + 13) = 0;

    v0 = rand() & 0x3f;
    temp_u16 = *(u16 *)((u8 *)a1 + 2);
    *(u16 *)((u8 *)s1 + 2) = temp_u16 + v0 - 0x20;

    v0 = rand() & 0x7f0;
    temp_s16 = *(s16 *)((u8 *)a1 + 4);
    temp_s32 = temp_s16 * (v0 + 0xc00);
    v0 = (s32)(temp_s32 >> 12);
    *(s16 *)((u8 *)s1 + 4) = (s16)v0;

    v0 = *(s16 *)((u8 *)a1 + 6);
    if (v0 != 0) {
        u16 v1 = *(u16 *)((u8 *)s1 + 4);
        *(u8 *)((u8 *)s1 + 9) = 1;
        *(u16 *)((u8 *)s1 + 4) = 0;
        *(u8 *)((u8 *)s1 + 13) = (u8)v1;
    }
}




s32 func_8018A9BC(void) {

    extern s16 D_801EB6E4;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801EB6E4 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_8018A9F8(s32 a0, s32 a1) {

    extern s16 D_801EB6E4;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801EB6E4);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



/* func_8018AA44 — 16-entry table walk, stride 0xE, over D_801EB6E4.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_801EB6E4; s16 *p = &D_801EB6E4; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_8018AB20(s32 arg0);

void func_8018AA44(void) {

    extern s16 D_801EB6E4;
    s16 *p = &D_801EB6E4;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_8018AB20(i);
            switch (*(u8 *)((s32)p + 9)) {
            case 1:
                if (*(s16 *)((s32)p + 4) < *(u8 *)((s32)p + 13)) {
                    *(s16 *)((s32)p + 4) = *(s16 *)((s32)p + 4) + 8;
                } else {
                    *(u8 *)((s32)p + 9) = 0;
                }
                break;
            case 2:
                t = *(s16 *)((s32)p + 4);
                if (t != 0) {
                    t -= 0x10;
                    *(s16 *)((s32)p + 4) = t;
                    if (t > 0) {
                        break;
                    }
                }
                *p = 0;
                break;
            }
        }
        i++;
        p = (s16 *)((s32)p + 0xe);
    } while (i < 0x10);
}



/* func_8018AB20 — draws one entry of the 16-slot D_801EB6E4 particle table:
 * bump-allocates a 0x1C-byte GPU packet out of D_800A5E60, fills it from the
 * table entry, runs two RotMatrixZ/ApplyMatrixSV passes to place the two
 * endpoints, then link-ins the packet into the current double-buffer's OT
 * (the PSY-Q `addPrim` macro pair) and calls func_80016638.
 *
 * STATUS: byte-MATCH, 177/177 instructions (match_one standalone AND spliced
 * into the real TU — the in-TU compile adds ZERO new cc1 diagnostics over the
 * unmodified TU baseline).
 *
 * ---------------------------------------------------------------------------
 * LEVERS (each byte-checked against asm/.../func_8018AB20.s)
 *
 *  §48  STRUCT ASSIGN, not a hand-rolled temp copy.  `m = D_800AE620;` on a
 *       32-byte aggregate routes expr.c move_by_pieces, which emits the exact
 *       lw/lw/lw + sw/sw/sw (x2) + lw/lw + sw/sw grouping AND picks the
 *       target's registers ($a2 = source address, $v0/$v1/$a1 = carriers), and
 *       keeps the arg0*14 allocator chain OUT of the copy.  The manual
 *       three-temp form (DEFINE_func_8012B4B8, engine_core.h L29487) emits the
 *       same instruction MIX but a different allocation (+60 mismatches).
 *
 *  §21/T6  The double-buffer index D_800B9A02 is read at ALL THREE use sites
 *       (three `lhu`s off ONE materialised `la`).  A PLAIN read is CSEd down to
 *       two AND keeps -G0 symbol addressing (lui+lhu per read, +1 insn); a
 *       POINTER local gives the `la` but lets cse fold the third read.  The
 *       `volatile u16 *` pointer local reproduces BOTH properties and leaves
 *       the TU's own `extern s16 D_800B9A02;` untouched.
 *
 *  T6   The OT base is bound to an s32 local (`ot`) so the tag read/write keep
 *       the `0x40($v1)` displacement form instead of folding into the pointer.
 *
 *  L4   `mp`, a pointer local bound to &m, is what puts the matrix address in a
 *       callee-saved register ($s2) and turns each argument setup into a move;
 *       passing the array directly re-materialises `addiu $aN,$sp,0x10` at
 *       every call site and drops $s6 from the frame entirely.
 *
 *  S1   `t = *(u16 *)ent;` is hoisted ABOVE the two `sh $zero` stores — the
 *       sp-relative stores are not disambiguated from the $s0-based load, so
 *       only SOURCE ORDER moves it (4 mismatches).
 *
 *  T-form  `u16 bx/by` (not s32) is what makes `addu $v0,$s3,$v0` come out with
 *       the accumulator first; through s32 locals combine canonicalises the
 *       zero_extend into operand 0 and both adds emit reversed.
 *
 *  §83c-inverse  FRAME: 0x70 = 16 args + 56 declared vars + 32 saved regs + an
 *       8-byte COMPILER TEMP that gcc allocates for the two `symbol+register`
 *       memory references (both D_800A651C).  So the DECLARED locals must total
 *       56, not 60: m(32)@0x10, sv(8)@0x30, out(8)@0x38, v(8)@0x40 — the third
 *       word of the vector handed to func_8004901C (sp+0x48) lands INSIDE that
 *       compiler temp.  `s32 v[3]` gives a 0x78 frame and 19 extra mismatches.
 *       Do NOT invent a dead local to reach the frame size.
 *
 * ---------------------------------------------------------------------------
 * THE TWO RESIDUAL CLUSTERS AND WHAT ACTUALLY CLOSED THEM
 * (both are gcc-2.7.2-map/sched.md §1 rule 7 "BIRTHING BOOST" + rule 5(b)
 *  "potential hazard"; diagnosed from the cc1 `-dS` ready-list trace, which
 *  names the decision verbatim: `;; insn 245 has a greater potential hazard`.)
 *
 *  (a) The three symbol loads before the first RotMatrixZ came out E4,EA,E6
 *      instead of EA,E4,E6.  `lh $a0,D_801EB6E2` is a single-set SET(REG,…) —
 *      the sched1 birthing boost sinks it to just before its consumer (the
 *      jal), i.e. one slot too late.  Statement order CANNOT fix this: written
 *      as a plain local the load is combined into the call's arg setup, so its
 *      LUID is the call's either way (verified: two source orders, identical
 *      bytes).  `register s32 ang __asm__("$4")` keeps the load a separate insn
 *      AT its source position — zero extra instructions, +0 bytes.
 *
 *  (b) The tail's `lw $v1,0($s1)` (`*(u32 *)p`) belongs in the load-delay slot
 *      of `lhu $a0,0($a2)`; ours landed 7 insns later with `lui $a0,0xff00`
 *      taking the slot.  sched1 trace: at T-27 the ready list is
 *      `247 (7f000001) 245 (7f000001)` — BOTH boosted — and the tie goes to the
 *      LOAD via `potential_hazard` (memory-unit users beat ALU insns), so the
 *      load is picked first = placed LAST.  TWO edits are needed and neither
 *      works alone:
 *        1. KILL the boost on the load's destination — `pv` gets a second SET
 *           from a zero-byte dead `__asm__ __volatile__("" : "=r"(pv));` at the
 *           end of the function (sched.md S2: a plain C reassignment does not
 *           work, cse/flow removes it; reusing one local across BOTH addPrim
 *           halves does kill the boost but makes `pv` a 2-death GLOBAL allocno
 *           that loses $v1, §136).  With the boost dead, sched1 emits the
 *           target order exactly (proved with -fno-schedule-insns2).
 *        2. PIN `pv` to $v1 (`register u32 pv __asm__("$3")`).  Without it,
 *           local-alloc gives $v1 to the shorter, denser index quantity and
 *           `pv` lands in $a1/$t0; sched2 then re-applies rule 5(b) and undoes
 *           sched1's order.  With `pv` in $v1 the index is pushed to $a0, the
 *           0xFF000000 constant reuses $a0, and its output-dependence on the
 *           index's `sll/addu` FREEZES it after them — which is precisely the
 *           target's shape, and what makes sched2 leave sched1's order alone.
 *
 *      Pin-trim log (all re-scored): dropping the $a2 `bidx` pin — MATCH;
 *      dropping the $a3 0xFFFFFF pin — MATCH; dropping `ang` — 4 mismatches
 *      (a dead-volatile boost-kill on `ang` does NOT substitute); dropping
 *      `pv` — 11; dropping the dead `pv` asm — 11.  Two pins are the minimum
 *      found.
 *
 * ---------------------------------------------------------------------------
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_801EB6DC/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_801EB6E0, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_8018AB20 is byte-identical.
 */

void func_8018AB20(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_8018AB20 D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_801EB6DC;
    extern s16 D_801EB6DE;
    extern s16 D_801EB6E0;
    extern s16 D_801EB6E4;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_8018AB20 m;                    /* sp+0x10 */
    s16 sv[4];                           /* sp+0x30 */
    s16 out[4];                          /* sp+0x38 */
    s32 v[2];                            /* sp+0x40 — 3rd word lives in the temp area */
    void *mp;
    u8 *p;
    u8 *ent;
    s32 ot;
    u16 bx;
    u16 by;
    register s32 ang __asm__("$4");      /* §17 pin — see residual (a) */
    volatile u16 *bidx;
    s32 t;
    register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */

    m = D_800AE620;
    mp = &m;

    ent = (u8 *)((arg0 * 14) + (s32)&D_801EB6E4);
    p = (u8 *)D_800A5E60;
    D_800A5E60 = (s32)p + 0x1C;

    p[3] = 6;
    p[7] = 0x32;
    p[4] = ent[6];
    p[5] = ent[7];
    p[6] = ent[8];
    p[0xC] = ent[0xA];
    p[0xD] = ent[0xB];
    p[0xE] = ent[0xC];
    p[0x14] = ent[0xA];
    p[0x15] = ent[0xB];
    p[0x16] = ent[0xC];

    ang = D_801EB6E2;
    bx = (u16)D_801EB6DC;
    by = (u16)D_801EB6DE;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_801EB6E0;
    v[1] = *(s32 *)((u8 *)v + 8);
    v[0] = v[1];
    func_8004901C(mp, v);

    t = *(u16 *)ent;
    sv[2] = 0;
    sv[1] = 0;
    sv[0] = t;
    *(s16 *)(p + 8) = bx;
    *(s16 *)(p + 0xA) = by;

    RotMatrixZ(*(s16 *)(ent + 2) - (((s32)*(u16 *)(ent + 4) << 16) >> 17), mp);
    ApplyMatrixSV(mp, sv, out);
    *(s16 *)(p + 0x10) = bx + (u16)out[0];
    *(s16 *)(p + 0x12) = by + (u16)out[1];

    RotMatrixZ(*(s16 *)(ent + 4), mp);
    ApplyMatrixSV(mp, sv, out);
    bx += (u16)out[0];
    *(s16 *)(p + 0x18) = bx;
    by += (u16)out[1];
    *(s16 *)(p + 0x1A) = by;

    /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
    bidx = (volatile u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (*(u32 *)(*(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)) + 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
    __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
}


void func_8018ADE4(void) {

    extern s16 D_801EB5DC;
    s16 *p = &D_801EB5DC;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8018AE30(s32 a0);

void func_8018AE08(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_8018AE30((s32)pv);
}



/* func_8018AE30 — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_801E9E68 instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_8018AEB8 arg0
 *   sp+0x18  s32 pv[4]   (16 bytes) -> pv[0] = copy dest, &pv[2]/&pv[3] = 0x20/0x24
 *
 * The lwl 0x3 / lwr 0x0 / swl 0x1B / swr 0x18 block move: a 4-byte struct assign
 * whose type has ALIGNMENT 1 (cookbook §48-C2).  Align 1 (not 2) is load-bearing —
 * it is what pushes the copy off the move_by_pieces path (which keeps the SYMBOL
 * in the address and emits a fresh `lui $at,%hi` per reference) onto mips.c
 * expand_block_move, which copy_addr_to_reg's the source address into ONE held
 * register first -> `lui $a1,%hi; addiu $a1,$a1,%lo; lwl 3($a1); lwr 0($a1)`.
 * A {u16,u16} (align 2) struct compiles to the same opcode sequence but with the
 * folded-symbol addressing: 4 mismatches.  Struct assign, NOT memcpy (memcpy
 * byte-matches in isolation but lowers to `jal memcpy` in any TU that declares
 * it — §2959).
 *
 * All four callee prototypes are copied VERBATIM from this TU (func_8004914C /
 * func_800491AC / RotTransPers at file scope L3484-3486; func_8018AEB8 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_801E9E68 appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8018AEB8(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_8018AE30(s32 a0) {
    extern u8 D_800AF648;
    extern V4_8018AE30 D_801E9E68;
    u16 sxy[4];
    s32 pv[4];

    *(V4_8018AE30 *)pv = D_801E9E68;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_8018AEB8(sxy, pv, 0x10, 0x18);
}



extern void func_8018AF24(void *a0, void *a1, s16 a2);
extern void func_8018B058(s32 a0, s16 a1, u16 a2);

void func_8018AEB8(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_8018AF24(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_8018B058(i, j, arg3);
    }
}





void func_8018AF24(void *a0, void *a1, s16 a2) {

    extern s16 D_801EB5D0;
    extern s16 D_801EB5D2;
    extern u8 D_801EB5D8;
    extern u8 D_801EB5D9;
    extern u8 D_801EB5DA;
    extern u32 D_801EB5D4;
    if (a0 != NULL) {
        D_801EB5D0 = *(u16 *)a0;
        D_801EB5D2 = *(u16 *)((s32)a0 + 2);
    } else {
        D_801EB5D0 = 0;
        D_801EB5D2 = 0;
    }

    D_801EB5D8 = *(u8 *)a1;
    D_801EB5D9 = *(u8 *)((s32)a1 + 1);
    D_801EB5DA = *(u8 *)((s32)a1 + 2);
    D_801EB5D4 = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018AF94(s32 a0) {

    extern u8 D_800AF648;
    extern s16 D_801EB5D0;
    extern s16 D_801EB5D2;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801EB5D0 = sxy[0];
    D_801EB5D2 = sxy[1];
}




extern s32 func_8018B174(void);
extern void func_8018B058(s32 a0, s16 a1, u16 a2);

void func_8018B00C(s32 a0, s32 a1) {
    s32 result = func_8018B174();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_8018B058(result, ext_a0, (u16)a1);
    }
}



/* func_8018B058 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_801EB5DC.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_801EB5DC : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_801EB5D6 : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_8018B058(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_8018B058");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_801EB5DC;
    extern s16 D_801EB5D6[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_8018B058 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_8018B058 *)((s32)&D_801EB5DC + (a0 << 4));

    rad = a2;
    rad = a2 + (rand() % (rad >> 2) - (rad >> 3));

    ang = a1 + (rand() & 0x3f) - 0x20;
    p->f6 = ang;

    m = rad;
    t8 = (func_80047948(p->f6) * m) >> 12;
    tC = (func_8004787C(p->f6) * m) >> 12;
    p->f8 = t8 << 16;
    p->fC = tC << 16;

    p->f0 = (rand() & 0xf) + 0x10;
    p->f2 = m << 6;
    p->f4 = (s32)D_801EB5D6[0] * 64;
}




s32 func_8018B174(void) {

    extern s16 D_801EB5DC;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801EB5DC + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_8018B1B0 — the 16-slot particle/effect stepper over D_801EB5DC[16]
 * (0x10-byte records; slot 0 = the `active` u16 that func_8018AD5C clears and
 * func_8018B0EC scans).  Layout used here, all as byte-offsets off ONE walked
 * base pointer:
 *   +0x0 u16 active   +0x2 s16 angle   +0x4 u16 dangle
 *   +0x6 s16 dir      +0x8 s32 x       +0xC s32 z
 *
 * IV shape (cookbook §3-Giv / gcc-map L1): the target has ONE biv (the walked
 * base, kept alive by the bare +0x0 accesses, which find_mem_givs excludes from
 * giv formation) plus ONE combined DEST_ADDR giv anchored at base+2
 * (`addiu $s1, $s2, 0x2`).  combine_givs takes g1 from the list HEAD and
 * record_giv PREPENDS, so *the last-emitted offset reference anchors*: the
 * `+= dangle` statement (which ends on a +0x2 store) must therefore come LAST
 * in the body.  Written before the two s32 updates it anchors at base+0xC
 * instead -> 14 mismatched immediates.
 *
 * Both rsin/rcos products are computed BEFORE any store because gcc-2.7.2's
 * sched.c makes every mem ref depend on last_function_call — a store emitted
 * between the two `jal`s could not have floated below the second one.
 *
 * `i++` precedes the pointer bump in the for-increment: that emission order is
 * what puts `addiu $s4,$s4,1` ahead of the giv's `addiu $s1,$s1,0x10` (the
 * biv's own bump then fills the branch delay slot).
 *
 * func_80047948 / func_8004787C keep this TU's file-scope prototypes verbatim
 * (L2197-2198, `s32` param) — the s16 field is sign-extended at the call site
 * by the `lh`, so the narrower m2c-style `s16` prototype is not needed (§17a-1).
 * D_801EB5DC uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018B1B0(void) {

    extern s16 D_801EB5D6;
    extern s16 D_801EB5DC;
    extern void func_8018B2C4(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_801EB5D6;
    p = &D_801EB5DC;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_8018B2C4(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_8018B2C4 — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_801EB5DC[a0] record, projects the
 * four corner offsets into the packet, then links the packet into the OT.
 *
 * Byte-verified levers (all three were needed; each is worth 8-31 insns):
 *
 *  A. THE OT LINK IS THE libgpu P_TAG BITFIELD, NOT HAND-MASKING.  Writing
 *     `*(u32*)q = (*(u32*)q & 0xFF000000) | (ot & 0xFFFFFF)` is byte-correct
 *     arithmetic but gives the WRONG register assignment (16 mismatches: the
 *     0xFFFFFF / 0xFF000000 / &D_800B9A02 pseudos land in a0/a2/a3 permuted,
 *     and the `lw $v1,0($s3)` gets serialised behind the index load).  The
 *     `unsigned addr:24; unsigned len:8` bitfield insert reproduces both the
 *     allocation and the schedule exactly.  This is just `addPrim(ot, q)`.
 *
 *  B. THE OT TABLE MUST BE AN ARRAY_REF (`D_800A651C[i].a`), NOT
 *     `*(s32*)((u8*)&D_800A651C + i*20)`.  With the pointer-arith spelling gcc
 *     allocates a phantom 8-byte stack temp that is never referenced, pushing
 *     the frame from 0x68 to 0x70 (cookbook D6 in reverse: the frame is too
 *     BIG).  The temp only appears when the SAME lookup expression occurs in
 *     two statements; the ARRAY_REF form (engine_core.h `OtBlk`) kills it.
 *
 *  C. THE LAST ApplyMatrixSV RECOMPUTES THE MATRIX ADDRESS.  The first four
 *     matrix arguments come out of $s4 (`addu $aX,$s4,$zero`), but the fifth is
 *     `addiu $a0,$sp,0x10`.  cse.c cannot be talked out of folding a fifth
 *     `&m` into the existing pseudo: the conditional above it is a
 *     "branch around a block", so cse_end_of_basic_block EXTENDS the basic
 *     block through the join label (status AROUND) and the equivalence class
 *     for (plus fp 16) is still live.  Every source-level attempt to break it
 *     (pointer local, `mp = m` in the skipped arm, a §21 zero-byte re-tie,
 *     do{}while(0) loop notes) either changed nothing or cost 3 insns by
 *     turning the pointer into a two-def global allocno.  Pinning a reader to
 *     $sp makes the expression `(plus (reg 29) 16)` — a different rtx from
 *     `(plus (reg fp) 16)`, so cse never looks it up, and the single-use pseudo
 *     is folded by combine into the one `addiu` the target has.
 *
 *  The svp/outp block around the FIRST ApplyMatrixSV is load-bearing too:
 *  removing it costs 6 insns and two extra callee-saved registers.
 */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_80016638(void *a0, s32 a1, s32 a2);


/* 0x10-byte-stride record table at D_801EB5DC (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_8018B2C4(s32 a0) {

    extern s16 D_801EB5D0;
    extern s16 D_801EB5D2;
    extern u8 D_801EB5D8;
    extern u8 D_801EB5D9;
    extern u8 D_801EB5DA;

    extern s16 D_801EB5DC;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_8018B2C4 D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_8018B2C4 *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_8018B2C4 *)m = *(Mat32_8018B23C_8018B2C4 *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801EB5D8;
    *(u8 *)(q + 5) = D_801EB5D9;
    *(u8 *)(q + 6) = D_801EB5DA;

    p = (Rec_8018B23C_8018B2C4 *)((s32)&D_801EB5DC + (a0 << 4));
    x = p->fA + (u16)D_801EB5D0;
    y = p->fE + (u16)D_801EB5D2;
    RotMatrixZ(p->f6, m);

    scale[0] = *(s16 *)((s32)p + 2);
    scale[1] = *(s16 *)((s32)p + 2);
    scale[2] = *(s16 *)((s32)p + 2);
    func_8004901C(m, scale);

    *(s16 *)(sv + 4) = 0;
    *(s16 *)(sv + 2) = 0;
    *(s16 *)(sv + 0) = p->f0;
    {
        void *svp = sv;
        void *outp = out;
        ApplyMatrixSV(m, svp, outp);
        __asm__ __volatile__("" : "=r"(svp));
        __asm__ __volatile__("" : "=r"(outp));
    }

    *(s16 *)(q + 0x8) = x + ((s16)out[0] >> 1) * 3;
    *(s16 *)(q + 0xA) = y + ((s16)out[1] >> 1) * 3;
    *(s16 *)(q + 0xC) = x - ((s16)out[0] >> 1);
    *(s16 *)(q + 0xE) = y - ((s16)out[1] >> 1);
    x = x + out[0];
    *(s16 *)(q + 0x10) = x;
    y = y + out[1];
    *(s16 *)(q + 0x12) = y;

    ang = -0x400;
    if (p->f0 & 1) {
        ang = 0x400;
    }
    RotMatrixZ(ang, m);

    *(s16 *)(sv + 0) = 2;
    {
        /* lever C: sp+0x10 IS &m, but spelled so cse cannot fold it to $s4 */
        register u8 *spr __asm__("$29");
        ApplyMatrixSV(spr + 0x10, sv, out);
    }

    *(s16 *)(q + 0x10) = *(u16 *)(q + 0x10) + out[0];
    *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + out[1];

    {
        Bidx_8018B23C_8018B2C4 *bp = (Bidx_8018B23C_8018B2C4 *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_8018B2C4 *)q)->addr =
            ((PTag_8018B23C_8018B2C4 *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_8018B2C4 *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}


#include "common.h"

/* func_8018B5A8 — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_8018B60C((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8018B60C();

void func_8018B5A8(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_8018B60C)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}


s32 func_8018BA0C(u32 a0v);
s16 func_8018B950(u32 a0);

void func_8018B60C(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_8018BA0C(s0);
    sin_val = func_8018B950(s0);

    /* Build rotation matrix on stack */
    v1 = 0x7FF8;
    *(short *)((s32)matrix_stack + 0x04) = sin_val;
    *(short *)((s32)matrix_stack + 0x00) = cos_val;
    *(short *)((s32)matrix_stack + 0x02) = 0;
    *(short *)((s32)matrix_stack + 0x06) = 0;
    *(short *)((s32)matrix_stack + 0x08) = v1;
    *(short *)((s32)matrix_stack + 0x0A) = 0;
    *(short *)((s32)matrix_stack + 0x0C) = -sin_val;
    *(short *)((s32)matrix_stack + 0x0E) = 0;
    *(short *)((s32)matrix_stack + 0x10) = cos_val;

    __asm__ volatile (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 0x10;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 0x12;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 0x2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 0x14;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu %0, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0)"
        : "=r"(s1)
        : "0"(s1)
        : "$12", "$13", "$14", "$2"
    );
}


#include "common.h"

/* func_8018B76C — RotMatrix: builds a 3x3 fixed-point (1.15) rotation matrix
 * from the three packed 12-bit Euler angles at a0[0..2].
 *   func_8018BA0C = cosine table lookup, func_8018B950 = sine table lookup.
 * Declarations copied VERBATIM from the TU (ov_SC02_011_jr_8017AE2C.c:6928-6929).
 */

s32 func_8018BA0C(u32 a0v);
s16 func_8018B950(u32 a0);

void func_8018B76C(u16 *r, s16 *m) {
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_8018BA0C(r[0] & 0xFFF);
    sx = func_8018B950(r[0] & 0xFFF);
    cy = func_8018BA0C(r[1] & 0xFFF);
    sy = func_8018B950(r[1] & 0xFFF);
    cz = func_8018BA0C(r[2] & 0xFFF);
    sz = func_8018B950(r[2] & 0xFFF);

    cxsz = (cx * sz) >> 15;
    cxcz = (cx * cz) >> 15;
    sxsy = (sx * sy) >> 15;

    m[0] = (cz * cy) >> 15;
    m[1] = ((sxsy * cz) >> 15) - cxsz;
    m[2] = ((cxcz * sy) >> 15) + ((sx * sz) >> 15);
    m[3] = (sz * cy) >> 15;
    m[4] = ((sxsy * sz) >> 15) + cxcz;
    m[5] = ((cxsz * sy) >> 15) - ((sx * cz) >> 15);
    m[6] = -sy;
    m[7] = (cy * sx) >> 15;
    m[8] = (cy * cx) >> 15;
}


#include "common.h"

/* func_8018B950 — quadrant-folded sine lookup over a 0x400-entry u16 table.
 *
 * asm evidence:
 *   Q0 (a<0x400)          : lh   tbl[a]
 *   Q1 (a-0x400 < 0x400)  : lh   tbl[0x7FF - a]
 *   Q2 (a-0x800 < 0x400)  : lhu  tbl[a - 0x800], negu, sll/sra 16
 *   Q3 (a-0xC00 < 0x400)  : lhu  tbl[0xFFF - a],  negu, sll/sra 16
 *   else                  : NO value is produced at all (see below)
 *
 * The `lhu` + `negu` + 16-bit sign-extend in Q2/Q3 pins BOTH types:
 *   - the table element is UNSIGNED (zero-extending load feeding the negate), and
 *   - the result is truncated back to 16 bits => the function returns s16.
 * (An s16 table would give `lh`; an s32 return would drop the sll/sra pair.)
 *
 * Q2's base is D_801D56C8 == D_801D66C8 - 0x1000: gcc folded the `- 0x800`
 * element offset into the symbol addend and indexes with the raw parameter
 * (`sll $v0, $a0, 1`). Writing `tbl[a0 - 0x800]` reproduces that exactly.
 *
 * LOAD-BEARING: there is deliberately NO trailing `return 0;`.  The original
 * falls off the end of a non-void function, so the out-of-range path returns
 * whatever `$v0` happens to hold — which is the failing `sltiu` result, i.e. 0.
 * That is why the target's last test is `beqz $v0, .L8018BA04` + a bare `nop`
 * delay slot (gcc may not clobber $v0 on the taken edge) with no `move $v0,
 * $zero` anywhere.  Adding `return 0;` costs 2 instructions AND lets
 * find_cross_jump tail-merge the Q2/Q3 `negu; sll; sra` tails (cookbook §5a):
 * 45 ins / 19 mismatched instead of MATCH.
 */

extern u16 D_801D66C8[];

s16 func_8018B950(u32 a0)
{
    if (a0 < 0x400) {
        return D_801D66C8[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_801D66C8[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_801D66C8[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_801D66C8[0xFFF - a0];
    }
}


#include "common.h"

/* func_8018BA0C — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_801D66C8); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_801D66C8)[a - 0x400]  ->  base ((s16 *)D_801D66C8)-0x800 = D_801D5EC8, index a*2
 *   ((s16 *)D_801D66C8)[a - 0xC00]  ->  base ((s16 *)D_801D66C8)-0x1800 = D_801D4EC8, index a*2
 * so no extra externs are needed for D_801D5EC8 / D_801D4EC8.
 *
 * Types: the positive quadrants return the `lh` value straight through (already
 * sign-extended, no sll/sra); the negative quadrants take an explicit (s16) cast on
 * the negation, which forces the truncate -> the return's sign-extend becomes the
 * `sll 16 / sra 16` pair, and combine downgrades those loads to `lhu`.  Writing the
 * arms as four flat `return`s (not one shared s16 local) keeps the extension OFF the
 * positive quadrants; cross-jump then merges the two `sll/sra` tails.
 *
 * The tail has NO `return 0`.  A trailing `return 0` costs an extra `move $v0,$zero`
 * block AND lets dbr steal `sll $v0,$a0,1` into the final beqz delay slot (target has
 * a `nop` there).  Falling off the end keeps `expand_function_end`'s `(use $v0)` live
 * over the epilogue, so the delay slot stays empty and the branch lands straight on
 * the shared `jr $ra` with the `sltiu` zero already in $v0 — which IS the 0 the
 * caller observes.  Same shape as the sibling func_8018B950.
 */

extern u16 D_801D66C8[];

s32 func_8018BA0C(u32 a0v)
{
    if (a0v < 0x400) {
        return ((s16 *)D_801D66C8)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_801D66C8)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_801D66C8)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_801D66C8)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}


extern void func_8012C098(void);
    void func_8018BAB8(void) {
        func_8012C098();
    }


void func_8018BAD8(u8 *a0) {
    u16 v1 = *(u16 *)(a0 + 0x5E);
    if (v1 == 0x23) {
        *(u16 *)(a0 + 0xFE) = 1;
        func_8002D4C8(0xAA1, 0);
    } else if (v1 == 0x24) {
        s16 buf[3];
        buf[0] = 2;
        buf[1] = 0xF;
        buf[2] = -2;
        func_80190C84((s32)a0, (u16 *)buf, 0xD);
    }
}


#include "common.h"

/* func_8018BB44 — light/colour ramp-up on the entity's attached prim block.
 *
 * If the s16 flag at 0xFE is set, bump the three u16 colour words at
 * 0x18/0x1A/0x1C of the block pointed to by the word at 0x20 by 0x40 each,
 * then clamp all three to 0x1800 once the first one reaches it.
 *
 * Widths pinned off the target: `lh` at 0xFE and at 0x18 (the signed compare),
 * `lhu` for the three read-modify-writes, `sh` for every store.  The pointer at
 * 0x20 is re-loaded before each RMW (the `sh` stores may alias it), which is
 * exactly what writing the deref inline gives.
 */
void func_8018BB44(int param_1) {
    int v1;

    if (*(short *)(param_1 + 0xfe) != 0) {
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x18) += 0x40;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1a) += 0x40;
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x1c) += 0x40;
        v1 = *(int *)(param_1 + 0x20);
        if (*(short *)(v1 + 0x18) >= 0x1800) {
            *(short *)(v1 + 0x1c) = 0x1800;
            *(short *)(v1 + 0x1a) = 0x1800;
            *(short *)(v1 + 0x18) = 0x1800;
        }
    }
}


#include "common.h"

void func_8018BBCC(s32 *param_1) {
    int v1;

    v1 = *(short *)((s32)param_1 + 0xaa);
    *(short *)((s32)param_1 + 0x5c) = 0;
    *(short *)((s32)param_1 + 0x98) = 0;
    *(int *)((s32)param_1 + 0x1c) = 0;
    if (v1 == 0) {
        *(short *)((s32)param_1 + 0x100) = *(unsigned short *)(*(int *)((s32)param_1 + 0x20) + 0x18);
    } else {
        *(short *)((s32)param_1 + 0x102) = *(unsigned short *)(*(int *)((s32)param_1 + 0x20) + 0x18);
    }
}


#include "common.h"

// @class: structural (STRENGTH/mflo!=lw -> MATCH)
// @stuck: none - MATCH (41 ins), match_one + rtu_match.
// Three levers, in the order they mattered:
//  1) The `mult` sitting in BOTH branch arms is a dbr DELAY-SLOT STEAL from the
//     join block, not two multiplies in the source. The C selects the
//     MULTIPLICAND in the arms (`m`), and multiplies ONCE after the join.
//     That also makes the product a LOCAL allocno, so local-alloc coalesces
//     expand_divmod's `copy_to_mode_reg` temp away -> no `move v0,a0`, and the
//     bgez/addiu/shift all run in-place on $v0 (this was the whole 8-22 residual).
//  2) `srl` (not `sra`) for the /0x1000: the quotient's ONLY use must be a
//     narrowing store, i.e. hold it in an `s16 t`. combine's force_to_mode then
//     rewrites ASHIFTRT->LSHIFTRT because the high bits are discarded. Storing
//     `v / 0x1000` inline (2 SImode uses) keeps `sra`.
//  3) `m` must be `s32`, not `s16` - a narrow local costs lhu+sll+sra (loose
//     typing); the s32 local keeps the plain `lh`.
//  4) `p` and `q` are two SEPARATE variables so the reloaded 0x20 pointer lands
//     in $a0 rather than re-using $v1.

extern s32 func_8004787C(s32 a0);
extern s16 D_80126CE0;

void func_8018BC10(s32 param_1) {
    s32 v;
    s32 p;
    s32 q;
    s32 m;
    s16 t;

    v = func_8004787C(0x400 - (D_80126CE0 * 8));
    if (*(s16 *)(param_1 + 0xAA) == 0) {
        m = *(s16 *)(param_1 + 0x100);
    } else {
        m = *(s16 *)(param_1 + 0x102);
    }
    p = *(s32 *)(param_1 + 0x20);
    t = (v * m) / 0x1000;
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;
    q = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(q + 0x18) <= 0) {
        *(s16 *)(q + 0x1C) = 1;
        *(s16 *)(q + 0x18) = 1;
    }
}



void func_8018BCB4(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();

void func_8018BCC4(s32 param_1) {
    register s32 a __asm__("$4");
    s32 p;
    s32 q;
    s32 x;
    s32 t;
    u16 h;

    if (func_8012BEE8(param_1) != 0) {
        p = *(s32 *)(param_1 + 0x20);
        h = *(u16 *)(param_1 + 0x100);
        *(s16 *)(p + 0x1C) = h;
        *(s16 *)(p + 0x18) = h;
        a = param_1;
        *(s16 *)(a + 0x5C) |= 1;
        *(s16 *)(a + 0x60) = 0;
        q = *(s32 *)(a + 0x20);
        *(s16 *)(a + 0x62) = *(u16 *)(q + 0x12) + 0x800;
        *(s16 *)(a + 0x5E) = 1;
        ((void (*)(s32, s32))func_80131E00)(a, 1);
    } else {
        a = *(s32 *)(param_1 + 0x20);
        x = *(s16 *)(a + 0x18);
        t = x + (*(s16 *)(param_1 + 0x100) - x) / 4;
        *(s16 *)(a + 0x1C) = t;
        *(s16 *)(a + 0x18) = t;
    }
}



// @class: plumbing
// @stuck: none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);
extern void D_801DEB58;

void func_8018BD70(s32 arg0)
{
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801DEB58)) {
        func_8012A828(arg0, &D_801DEB58);
    }
}


extern void func_8002AC00(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018BDB8(s32 *arg0) {
    func_8002AC00(8);
    if (*(u16 *)((u8 *)arg0 + 0x5E) == 0x1D) {
        func_8002D4C8(0x440, 0);
    } else {
        func_8002D4C8(0x43F, 0);
    }
}



extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DEFE0;

void func_8018BE00(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801DEFE0);
    *(s32 *)(a0 + 0x1C) = 0x14;
}



// @class: schedule
// @stuck: none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_8018BEF0 else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_8018BEF0(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DEF38;

s32 func_8018BE40(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_8018BEF0(param_1);
        return 1;
    }
    sVar1 = *(s16 *)(param_1 + 0xdc) + 1;
    *(s16 *)(param_1 + 0xdc) = sVar1;
    if (sVar1 < 0x79) {
        return 0;
    }
    if (param_3 >= iVar2) {
        return 0;
    }
    *(s16 *)(param_1 + 2) = 1;
    func_8012A828(param_1, &D_801DEF38);
    return 1;
}



// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801DECF8;

void func_8018BEF0(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801DECF8);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_8018BF4C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 5;
        *(int *)((char *)a0 + 0x1c) = 0x14;
    }


extern void func_8012A828(s32 a0, void *a1);
extern void D_801DEB58;

s32 func_8018BF60(void *a0) {
    u16 v;
    *(u16 *)((s32)a0 + 2) = 3;
    func_8012A828((s32)a0, &D_801DEB58);
    v = *(u16 *)(*(s32 *)((s32)a0 + 0x78) + 2);
    *(u16 *)((s32)a0 + 0x5E) = 0;
    *(u16 *)((s32)a0 + 0xDC) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0x3C;
    *(u16 *)((s32)a0 + 0xFE) = 0;
    *(u16 *)((s32)a0 + 0x5C) = v;
}


extern s32 (*D_801D6FBC[])(void);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void);

void func_8018BFBC(u16 *s0)
{
    s32 v0;
    s32 temp;

    // Call function pointer from table indexed by s0[1]
    v0 = D_801D6FBC[s0[1]]();

    // Check if s0[0] is non-zero
    if (s0[0] != 0) {
        // Load from s0 + 0x10 (0x20 bytes due to u16 pointer arithmetic)
        temp = *(s32 *)(s0 + 0x10);
        // Modify u16 at offset 0x2c of temp
        *(u16 *)((char *)temp + 0x2c) = *(u16 *)((char *)temp + 0x2c) | 0x10;

        // Call func_8012C044 and check result
        v0 = func_8012C044((s32)s0);
        if (v0 != 0) {
            // Call func_8012C098
            ((void (*)(s32))func_8012C098)((s32)s0);
        }
    }
}



extern void (*D_801D6FDC[])(void);

void func_8018C040(void *a0) {
    D_801D6FDC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801D7024[])(void);

void func_8018C07C(void *a0) {
    D_801D7024[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (clean if/else, sh into delay slot of func_8001CA88 call)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern void func_80143994(s32 a0, s32 a1);
extern int D_801D6FE4;

void func_8018C0B8(int param_1)
{
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        *(short *)(param_1 + 2) = 1;
        func_8001CA88(*(int *)(param_1 + 0x20), &D_801D6FE4);
        func_80143994(param_1, 0x1000);
    }
}


void func_8018C11C(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    u16 v = *(u16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 0x50;
    *(s16 *)(p + 0x12) = v;
    func_8012B2CC((s32)a0);
    func_8012B200(a0);
    func_8012B178((s32)a0, 0xFFF20000);
}


extern void func_8012CBF4(s32);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012C218(void *a0);

extern u8 D_801D7030[];
extern u8 D_800D3918[];

void func_8018C174(s32 param_1) {
    s32 v0;

    v0 = ((s32 (*)(s32))func_8012CBF4)(param_1);
    if (v0 != 0) {
        func_8012C218((void *)param_1);
        return;
    }

    v0 = func_8012D5E4(param_1, (s32)&D_801D7030, (s32)&D_800D3918, 0xA);
    if (v0 != 0) {
        func_8012C218((void *)param_1);
        return;
    }

    v0 = *(s32 *)(param_1 + 0x1c);
    v0 = v0 - 1;
    *(s32 *)(param_1 + 0x1c) = v0;
    if (v0 == 0) {
        func_8012C218((void *)param_1);
    }
}



extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018BF60(a0);
extern u16 D_80126B96;
extern u8 D_801D6FA4[];
extern u8 D_801D6FB4[];

void func_8018C1E0(s32 arg0) {
    u16 sp10[3];
    u16 sp18[12];

    if (*(s32 *)(arg0 + 0x1C) == 9) {
        if (func_8012D5E4(arg0, (s32)D_801D6FA4, (s32)(D_801D6FA4 + 8), 10) != 0) {
            D_80126B96 |= 0x800;
        }
        if (*(s16 *)(arg0 + 0x70) & 0x8000) {
            func_8012F214(arg0, (s32)D_801D6FB4, (s32)sp10);
            sp18[3] = 0x126;
            sp18[5] = 0;
            sp18[6] = 0x7FFF;
            sp18[0] = sp10[0];
            sp18[1] = sp10[1];
            sp18[2] = sp10[2];
            sp18[7] = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
            func_8012C51C(sp18, arg0);
            sp18[7] = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x100;
            func_8012C51C(sp18, arg0);
            sp18[7] = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) - 0x100;
            func_8012C51C(sp18, arg0);
        }
        func_8002D4C8(0x43E, 0);
    }
    if (func_8012BEE8(arg0) != 0) {
        ((void (*)(void *))func_8018BF60)(arg0);
    }
}


extern s32 func_8012BCCC(s32 a0);

void func_8018C31C(s32 a0) {
    register s32 result __asm__("$2");
    register s32 threshold __asm__("$3");

    if (*(s16 *)(a0 + 0x70) & 0x8000) {
        result = func_8012BCCC(a0);
        threshold = 0x90000;
    } else {
        result = func_8012BCCC(a0);
        threshold = 0x24000;
    }
    threshold = (threshold < result);
    if (threshold) {
        return;
    }
    func_8018BE00(a0);
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018BF60(void *a0);
void func_8018C388(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8018BF60)(param_1);
    }
}


extern s32 func_8012BEE8(s32 a0);

void func_8018C3C0(s32 param_1)
{
    if (func_8012BEE8(param_1) == 1) {
        if (*(s16 *)(param_1 + 0x70) & 0x8000) {
            func_8018BE40(param_1, 0x40000, 0xC4000);
        } else {
            func_8018BE40(param_1, 0x9000, 0x24000);
        }
    }
}



// @class: plumbing
// @stuck: none — MATCH expected (single call-crossing local pins to $s0 naturally; lhu via unsigned short)

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018BF4C(void*);

void func_8018C424(int param_1)
{
    int v;
    unsigned short *p;

    v = func_8012B8E4(param_1, 4);
    p = (unsigned short *)(*(int *)(param_1 + 0x20) + 0x12);
    *p = (unsigned short)(*p + v);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(s32))func_8018BF4C)(param_1);
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void *a1);

extern s32 D_801D6EE8;
extern u8 D_801D6F1C;
extern u8 D_801DEF38;

void func_8018C47C(s32 s0) {
    register s32 v1 __asm__("$3");
    s32 v0;
    s32 a1v;

    v0 = func_8012C354(s0, (s32)&D_801D6EE8);
    if (v0 == 0) {
        return;
    }

    v1 = 0xFFFBFFFD;
    *(s32 *)(s0 + 0xB4) = v1;
    v1 = *(s32 *)(s0 + 0x20);
    *(u8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xBC) = (s32)&D_801D6F1C;
    *(s32 *)(s0 + 0xC4) = 1;
    v0 = *(u16 *)(v1 + 0x2C);
    v0 |= 0x10;
    *(u16 *)(v1 + 0x2C) = v0;

    v0 = *(s32 *)(s0 + 0x20);
    a1v = *(s16 *)(s0 + 0x70);
    v0 = *(u16 *)(v0 + 0x18);
    *(u16 *)(s0 + 0x100) = v0;

    v0 = func_8012C658(0x125, a1v, s0);
    *(s32 *)(s0 + 0x6C) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s0);
    } else {
        *(s16 *)(s0 + 0x2) = 1;
        func_8012A828(s0, (void *)&D_801DEF38);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void*);
extern void func_8001C214(s32, s32);
extern s32 D_801D8AD8;

void func_8018C534(int param_1)
{
    int v0;
    int v1;
    int temp;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801D8AD8);
        temp = *(int *)(param_1 + 0x64);
        v1 = *(unsigned short *)(temp + 0x36);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0xFE) = 0x7FFF;
        *(short *)(param_1 + 0xFC) = v1;
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

extern u8 D_801DF130[];
extern u8 D_801D6FD4[];




void func_8018C5A4(s32 *self)
{
    s32 *tgt = (s32 *)*(s32 *)((s32)self + 0x64);
    SV3 out;

    if (*(s16 *)((s32)self + 0xFE) == 0x7FFF) {
        *(s16 *)((s32)self + 0xFE) =
            *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x12);
    }

    if (*(s16 *)((s32)self + 0xFC) !=
        *(s16 *)(*(s32 *)((s32)self + 0x64) + 0x36)) {
        func_8012C218(self);
        return;
    }

    *(Blk8 *)(*(s32 *)((s32)self + 0x20) + 0x10) =
        *(Blk8 *)(*(s32 *)((s32)tgt + 0x20) + 0x10);

    if (*(s32 *)(*(s32 *)((s32)self + 0x64) + 0x90) != (s32)D_801DF130) {
        *(s16 *)(*(s32 *)((s32)self + 0x20) + 0x12) =
            *(u16 *)((s32)self + 0xFE);
        *(s32 *)((s32)self + 0x4) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0x4);
        *(s32 *)((s32)self + 0x8) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0x8);
        *(s32 *)((s32)self + 0xC) =
            *(s32 *)(*(s32 *)((s32)self + 0x64) + 0xC);
    } else {
        func_8012F214(*(s32 *)((s32)self + 0x64), (s32)D_801D6FD4, (s32)&out);
        *(s16 *)((s32)self + 0x6) = out.a;
        *(s16 *)((s32)self + 0xA) = out.b;
        *(s16 *)((s32)self + 0xE) = out.c;
    }

    *(Blk8 *)(*(s32 *)((s32)self + 0x20) + 0x18) =
        *(Blk8 *)(*(s32 *)((s32)tgt + 0x20) + 0x18);

    {
        u16 flag = *(u16 *)(*(s32 *)((s32)tgt + 0x20) + 0x2C);
        u16 cur = *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x2C);
        flag &= 0x10;
        cur |= flag;
        *(u16 *)(*(s32 *)((s32)self + 0x20) + 0x2C) = cur;
    }

    *(s32 *)(*(s32 *)((s32)self + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)((s32)tgt + 0x20) + 0x4);
}


#include "common.h"

extern s32 D_801DF74C[];
extern s32 func_8012C044(s32);
extern void func_8018DBF4(s32);

void func_8018C734(void *a0)
{
    s32 v0, v1;

    // Indirect call via table indexed by *(ushort*)(a0 + 2)
    v0 = *(u16 *)((u8 *)a0 + 2);
    v0 = v0 << 2;
    v1 = *(s32 *)((s32)D_801DF74C + v0);
    ((void (*)(void))v1)();

    // Check if first ushort is non-zero
    v0 = *(u16 *)a0;
    if (v0 != 0) {
        v0 = *(u16 *)((u8 *)a0 + 0xFE);
        v0 = v0 + 0x80;
        *(u16 *)((u8 *)a0 + 0xFE) = v0;
        v0 = func_8012C044((s32)a0);

        if (v0 == 1) {
            *(u16 *)((u8 *)a0 + 0x100) = 1;
            func_8018DBF4((s32)a0);
        }
    }
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80143994(s32, s32);
extern s32 D_801DF598;
extern s32 D_801E2900;
extern s32 D_801DF6AC;

void func_8018C7B8(s32 a0) {
    s32 v0;
    s32 v1;
    void *a0_val;

    if (func_8012C354(a0, (s32)&D_801DF598) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        v1 = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)&D_801DF6AC;
        *(s32 *)(a0 + 0xB4) = -0x20AD;
        *(s32 *)(a0 + 0xE0) = 0;
        v1 = v1 | 0x1;
        *(s32 *)(a0 + 0xC4) = v1;

        func_8012A828(a0, (void *)&D_801E2900);

        if ((*(u16 *)(a0 + 0x70) & 0x1) != 0) {
            a0_val = (void *)*(s32 *)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 1;
            *(s16 *)(a0 + 0x5C) = 0;
            *(s32 *)(a0_val + 0x4) = *(s32 *)(a0_val + 0x4) | 0x80000000;
        } else {
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
        }
    }
}


#include "common.h"

extern s32 func_8012E778(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012BD14(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_8018C874(s32 a0)
{
    s32 t;
    s32 u;
    register s32 p __asm__("$3");

    if (*(s16 *)(a0 + 0x102) == 0) {
        if (func_8012E778(a0, 0x64008C) == 0) {
            return;
        }
        *(s16 *)(a0 + 0x102) = 1;
    } else {
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x18FFF) {
            return;
        }
    }

    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 8;
    *(u16 *)(a0 + 0x5C) = 0xAA10;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x2C) |= 0x10;

    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(p + 0x4) &= 0x7FFFFFFF;
    t = func_80047948(0x380);

    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;

    u = func_8004787C(0x380);
    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x1A) = (u << 1) + 0x1000;

    *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018C968(s32 s0) {
  s32 v0;
  s32 v1;

  if (func_8012BEE8(s0) != 0) {
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    v1 &= 0xFFEF;
    *(s16 *)(v0 + 0x2C) = v1;
    *(s16 *)(s0 + 0x2) = 3;
  } else {
    s32 a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_80047948(a0);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1C) = v0;
    *(s16 *)(v1 + 0x18) = v0;
    a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_8004787C(a0);
    v0 = v0 << 1;
    v1 = *(s32 *)(s0 + 0x20);
    v0 += 0x1000;
    *(s16 *)(v1 + 0x1A) = v0;
  }
}


extern s32 D_801E2900;
extern void func_8012A828(s32, void*);

void func_8018CA04(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    func_8012A828(param_1, ((u8 *)&D_801E2900));
    *(s32 *)(param_1 + 0x1C) = 0x20;
    if (*(s32 *)(param_1 + 0xE0) != 0) {
        *(s32 *)(param_1 + 0xE0) = 0;
        *(s16 *)(param_1 + 0xA) = *(s16 *)(param_1 + 0xA) + 0x30;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018DD60(s32 a0);

void func_8018CA64(s32 s0) {
  s32 v0;
  s32 v1;

  v0 = *(s32 *)(s0 + 0x20);
  v1 = *(u16 *)(v0 + 0x12) + 0x40;
  *(s16 *)(v0 + 0x12) = v1;
  if (func_8018DD60(s0) != 1) {
    if (func_8012BEE8(s0) != 0) {
      *(s16 *)(s0 + 0x2) = 5;
    }
  }
}


extern s32 D_801E2900;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);

void func_8018CAC4(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 6;
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFE8000);
    func_8012A828(s0, (void *)((u8 *)&D_801E2900));
    *(s32 *)(s0 + 0x1C) = 0x96;
    *(u16 *)(s0 + 0xE6) = 0;
}


extern s32 func_8018DAA8(s32 a0, s32 a1);
extern s32 func_8018DD60(s32 a0);
extern u8 D_800D3918[];

void func_8018CB20(s32 arg0) {
    if (func_8018DD60(arg0) != 1) {
        if (func_8018DAA8(arg0, D_800D3918) == 0) {
            *(s16 *)(arg0 + 2) = 3;
        }
    }
}


extern s32 D_801E29F8;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_8018CB70(a0)
void *a0;
{
    s32 s0 = (s32)a0;
    *(u16 *)(s0 + 2) = 8;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801E29F8);
    *(s32 *)(s0 + 0x1C) = 0x24;
    *(u16 *)(s0 + 0xE6) = 0;
}


#include "common.h"

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8018DAA8();
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);

extern u8 D_800D3918[];

void func_8018CBBC(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 v1 __asm__("$3");
    s32 v0;
    u16 *p;

    s0 = a0;
    __asm__ __volatile__("");
    v0 = func_8012B8E4(s0, 8);
    p = *(u16 **)(s0 + 0x20);
    p[9] = p[9] + (u16)v0;

    if (*(s32 *)(s0 + 0x1C) < 0x19) {
        func_8012B178(s0, 0xFFFC0000);
        v1 = func_8018DAA8(s0, (void *)D_800D3918);

        if (v1 == 0) {
            v0 = 9;
            goto L_store;
        }
        v0 = -1;
        if (v1 == -1) {
            /* target skips the field_2 store entirely on this path */
            return;
        }
        /* else fall through to the common path */
    }

    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        v0 = 9;
    } else {
        v0 = func_8012BCCC(s0);
        if (v0 < 0x2001) {
            v0 = 9;
        } else {
            return;
        }
    }

L_store:
    *(s16 *)(s0 + 0x2) = v0;
}


















void func_8018CC6C(void *a0)
{
  s32 v1 = *((s32 *) (((s32) a0) + 0x20));
  int new_var;
  *((s16 *) (((s32) a0) + 0x2)) = 0xA;
  *((s16 *) (((s32) a0) + 0x5C)) = 0;
  *((s16 *) (((s32) a0) + (new_var = 0x34))) = 0;
  *((s32 *) (((s32) a0) + 0x1C)) = 0x8;
  *((s16 *) (((s32) v1) + 0x2C)) |= 0x10;
}

#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80143BDC(u16 *a0);
extern void func_8018D8B8(s32 a0);

void func_8018CC9C(s32 param_1)
{
    s32 iVar3;
    s32 uVar1;
    s32 sVar2;
    u16 sp10[3];

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x1E;
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) | 0x80000000;
            *(s16 *)(param_1 + 0xE4) = 3;
        } else {
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = uVar1;
            *(s16 *)(iVar3 + 0x18) = uVar1;
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = sVar2 * 2 + 0x1000;
        }
        break;
    case 1:
        uVar1 = *(u16 *)(param_1 + 0xE4) - 1;
        *(u16 *)(param_1 + 0xE4) = uVar1;
        if ((s16)uVar1 == 0) {
            sp10[0] = *(u16 *)(param_1 + 0x6);
            sp10[1] = *(u16 *)(param_1 + 0xA) - 0x38;
            sp10[2] = *(u16 *)(param_1 + 0xE);
            {
                s32 e;
                s32 q;

                e = func_80143BDC(sp10);
                if (e != 0) {
                    q = *(s32 *)(e + 0xCC);
                    if (q != 0) {
                        *(s16 *)(q + 0x1A) = 0x5000;
                        *(s16 *)(q + 0x18) = 0x5000;
                    }
                }
            }
            *(s16 *)(param_1 + 0x34) = 2;
        }
        /* fallthrough */
    case 2:
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x34) = 3;
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) & 0x7FFFFFFF;
            func_8018D8B8(param_1);
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x5C) = 0xAA10;
        }
        break;
    case 3:
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) & 0xFFEF;
            *(s16 *)(param_1 + 0x2) = 0xB;
        } else {
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = sVar2;
            *(s16 *)(iVar3 + 0x18) = sVar2;
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = uVar1 * 2 + 0x1000;
        }
        break;
    }
}


extern s32 D_801E2AD0;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_8018CEB0(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0xC;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801E2AD0);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
    func_8012B23C(s0);
}


#include "common.h"

extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 func_8018DAA8();
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern u8 D_800D3918[];

void func_8018CF04(s32 s0) {
    register s32 v0 __asm__("$2");
    s32 v1;

    v0 = func_8012B8E4(s0, 8);
    v1 = *(s32*)(s0 + 0x20);
    *(s16*)(v1 + 0x12) = (s16)(*(u16*)(v1 + 0x12) + v0);
    func_8012B178(s0, 0xFFFC0000);
    v0 = func_8018DAA8(s0, D_800D3918);
    if (v0 == -1)
        return;
    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        v0 = func_8012BCCC(s0);
        v0 = (v0 < 0x7001);
        if (v0)
            v0 = 0xD;
        else
            v0 = 0x3;
    } else {
        v0 = func_8012BCCC(s0);
        if (v0 < 0x3001)
            v0 = 0xD;
        else
            return;
    }
    *(s16*)(s0 + 0x2) = v0;
}


extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E2BA8[];

void func_8018CFAC(s32 param_1) {
    *(s16 *)(param_1 + 2) = 0xE;
    func_8012A828(param_1, D_801E2BA8);
    *(s32 *)(param_1 + 0x1C) = 0x5A;
    *(s16 *)(param_1 + 0xDC) = 0;
    *(s16 *)(param_1 + 0xFE) = 0;
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018D720();

void func_8018CFF4(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v0;
    s32 s1;

    v0 = func_8012BCCC(s0);
    if (v0 <= 0x14400) {
        if (*(s32 *)(s0 + 0x1C) >= 0x16) {
            v0 = func_8012B8E4(s0, 8);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
        }
        s1 = *(s32 *)(s0 + 0x1C);
        if (s1 == 0x15) {
            func_8002D4C8(0x522, 0);
        }
        if (s1 != 0x15 || *(s32 *)(s0 + 0x1C) != s1) {
            s32 v1 = *(s32 *)(s0 + 0x1C);
            if (v1 == 0xB || v1 == 1) {
                func_8018D720(s0);
            }
        } else {
            func_8018D720(s0);
        }
        v0 = func_8012BEE8(s0);
        if (v0 == 0) {
            return;
        }
        v0 = 3;
    } else {
        v0 = 7;
    }
    *(s16 *)(s0 + 2) = (s16)v0;
}


#include "common.h"

extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 D_801E29F8;

void func_8018D0C8(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x10;
    func_8012B2CC(s0);
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFD0000);
    func_8012A828(s0, (void *)&D_801E29F8);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


extern s32 D_801E29F8;
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8018DAA8(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012A828(s32 a0, void *a1);

void func_8018D128(s32 a0) {
    if (*(s16 *)(a0 + 0xAA) <= 0) {
        *(u16 *)(a0 + 2) = 3;
    } else {
        if (func_8012BEE8(a0) != 0) {
            func_8012A828(a0, (void *)&D_801E29F8);
            *(s32 *)(a0 + 0x1C) = 0x1A;
        }
        func_8018DAA8(a0, (s32)D_800D3918);
    }
}




void func_8018D19C(void *a0)
{
    s32 a1;
    s32 b;
    u16 v1;

    a1 = *(s32 *)((s32)a0 + 0x20);
    v1 = *(u16 *)(a1 + 0x2C);
    __asm__ __volatile__("" : : "r"(v1));
    if (v1 & 0x10) {
        *(u16 *)(a1 + 0x2C) = v1 & 0xFFEF;
        b = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(b + 0x1C) = 0x1000;
        *(u16 *)(b + 0x1A) = 0x1000;
        *(u16 *)(b + 0x18) = 0x1000;
    }
}


extern s32 func_8012B864(s32 a0);

void func_8018D1D8(s32 a0) {
    extern s32 func_8012B864(s32 a0);

    s32 s0 = a0;
    *(s16 *)(s0 + 2) = 0xF;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (func_8012B864(s0) + 0x800) & 0xFFF;
}


extern s32 D_801E3018;
extern void func_8012A828(s32 a0, void *a1);
extern void func_80131B14();

void func_8018D218(s32 s0) {
    s32 a0;
    s32 v1;

    a0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(a0 + 0x2C);
    if (v1 & 0x10) {
        *(u16 *)(a0 + 0x2C) = v1 & 0xFFEF;
        v1 = *(s32 *)(s0 + 0x20);
        *(u16 *)(v1 + 0x1C) = 0x1000;
        *(u16 *)(v1 + 0x1A) = 0x1000;
        *(u16 *)(v1 + 0x18) = 0x1000;
    }
    func_80131B14(s0);
    func_8012A828(s0, (void *)&D_801E3018);
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DF790[];
extern u8 D_801DF79C[];
extern u8 D_801E3098[];

void func_8018D288(s32 param_1) {
    s32 s0 = param_1;
    s32 v0;
    s32 t1;
    s32 t2;
    s32 t3;

    *(u16 *)(s0 + 0x5C) = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (*(u16 *)(s0 + 0x62) + 0x800) & 0xFFF;

    t1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t1 + 0x14) = 0;
    *(u16 *)(t1 + 0x10) = 0;
    func_8012B23C(s0);

    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    *(s32 *)(s0 + 0x1C) = 0;

    t2 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t2 + 0x2C) = *(u16 *)(t2 + 0x2C) & 0xFFEF;

    t3 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t3 + 0x1C) = 0x1000;
    *(u16 *)(t3 + 0x1A) = 0x1000;
    *(u16 *)(t3 + 0x18) = 0x1000;

    if (*(u16 *)(s0 + 0x5E) == 9 || *(u16 *)(s0 + 0x5E) == 0x1C) {
        func_8012B14C(s0, (s32)D_801DF790);
        v0 = 0xCC;
    } else {
        func_8012B14C(s0, (s32)D_801DF79C);
        v0 = 0x100;
    }
    *(u16 *)(s0 + 0xDE) = v0;

    func_8012A828(s0, (void *)D_801E3098);
}


#include "common.h"

extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00();
extern void func_8012B23C(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);

extern s32 D_801DF7A8;

void func_8018D370(void *a0) {
    void *s0 = a0;
    s32 v0;
    s32 v1;
    s32 cnt;

    if (*(u8 *)(s0 + 0xC2) != 0) {
        goto L8018D470;
    }

    func_8012DBD0((s32)a0, 0x50,
                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) + 0x800, 0x1D);

    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) - *(u16 *)(s0 + 0xDE);

    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt >= 0x29) {
        goto L8018D50C;
    }

    v1 = ((s32 (*)(s32, s32))func_8012CC64)((s32)s0, (s32)&D_801DF7A8);
    if ((v1 & 0x2000) == 0) {
        goto L8018D444;
    }
    if ((v1 & 0xFF) != 2) {
        goto L8018D410;
    }
    func_80131E00(s0, 0x12);
    return;

L8018D410:
    if (*(s16 *)(s0 + 0x76) <= 0) {
        func_80131E00(s0, 6);
        return;
    }
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(s16 *)(s0 + 2) = 3;
    *(s32 *)(s0 + 0xE0) = 1;
    return;

L8018D444:
    if ((v1 & 0x4000) == 0) {
        return;
    }
    v0 = *(u8 *)(s0 + 0xC2) + 1;
    *(u8 *)(s0 + 0xC2) = v0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    func_8012B23C((s32)s0);
    *(s32 *)(s0 + 0x1C) = 0;
    return;

L8018D470:
    v1 = ((s32 (*)(s32))func_8012CBA4)((s32)s0);
    if ((v1 & 0x2000) == 0) {
        goto L8018D4D4;
    }
    if ((v1 & 0xFF) != 2) {
        goto L8018D49C;
    }
    func_80131E00(s0, 0x12);
    return;

L8018D49C:
    if (*(s16 *)(s0 + 0x76) > 0) {
        goto L8018D4C0;
    }
    func_80131E00(s0, 6);
    goto L8018D4D4;

L8018D4C0:
    *(s16 *)(s0 + 2) = 3;
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(s32 *)(s0 + 0xE0) = 1;

L8018D4D4:
    if ((*(s32 *)(s0 + 0x1C) & 3) == 3) {
        func_80143B6C((s32)s0, 1);
    }
    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt < 0x3D) {
        return;
    }

L8018D50C:
    func_80131E00(s0, 0xD);
    return;
}


void func_8018D52C(void *a0) {
    extern short D_801DF69C;
    s32 v0;

    v0 = *(s32 *)((char *)a0 + 0x20);
    *(s16 *)((char *)a0 + 0x5C) = 0;
    *(s16 *)((char *)v0 + 0x10) = 0;
    *(s16 *)((char *)a0 + 0x34) = 0;
    func_8012E8A8((u8 *)a0);
    func_8012A828((s32)a0, (s32)&D_801DF69C);
}


#include "common.h"

/* func_8018D574 — ov_SC02_011 (TU: src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c)
 *
 * Second-pass repair of a SCHEDULE-REORDER/2 residual (`addiu $a0,$sp,0x10`
 * vs `addiu $s2,$s2,1` swapped at the ternary merge block).  Root cause, from
 * the cc1 `-dS` sched1 dump (bb9, both insns priority 1, unboosted):
 * `rank_for_schedule` (sched.c:2385) fell all the way through to the LUID
 * tie-break, so forward order = RTL birth order.  The `$a0` insn is born at
 * call-expansion time, so `i++` had to move BELOW the call to lose the tie.
 *
 * That alone is not enough: with `i` pinned to a hard reg, gcc-2.7.2's
 * sched_analyze_1 (sched.c:1704) hits its own bug — `call_used_regs[i]` uses
 * the HARD_REGNO_NREGS sub-word index instead of `regno + i`, so it always
 * reads `call_used_regs[0]` ($zero, always call-used) and hangs a
 * REG_DEP_ANTI on the preceding call for EVERY hard-reg set.  That lifted
 * `i++` to priority 2 and stranded it after the call.  A pseudo takes the
 * other arm (sched.c:1732), which is guarded by `reg_n_calls_crossed == 0`;
 * `i` is live across rand(), so it escapes the anti-dep entirely.
 * => drop the `$18` pin on `i` AND sink `i++` below func_80143BDC.
 *
 * Other levers (kept from pass 1): the two divide blocks are genuine r%48 /
 * r%24; the r1%4096 is hand-expanded as ternary-round + shift (writing `%`
 * makes gcc insert a spurious v0->v1 copy); pins hold $s3/$s4/$s0/$a3/$v1;
 * the func_8012B0B4 stack result is cached into a plain local so it stays in
 * a callee-saved reg instead of being reloaded each use.
 *
 * Decls copied verbatim from the destination TU's file-scope declarations
 * (func_80143BDC returns s32 there, TU L11414 — not void).
 */

extern s32 func_8012BEE8(s32 a0);
extern void func_8002AC00(s32 arg0);
extern void func_80130D48(s32 arg0);
extern void func_8018DBF4(s32);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_80143BDC(u16 *a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_8018D574(s32 a0) {
    register s32 obj __asm__("$19");
    s32 i;
    register s32 t4 __asm__("$20");
    register s32 tmp __asm__("$16");
    register s32 q1 __asm__("$7");
    unsigned int *pbuf;
    s32 r1, r2, r4;
    s32 ang1, dist;
    s32 base, v3;
    s32 buf;
    u16 pos[3];

    obj = a0;

    if (*(u16 *)(obj + 0x34) != 0) {
        if (func_8012BEE8(a0) != 0) {
            func_8002AC00(0xA);
            func_80130D48(obj);
            func_8018DBF4(obj);
        }
        return;
    }

    i = 0;
    pbuf = (unsigned int *)&buf;
    for (; i < 10;) {
        r1 = rand();
        tmp = (r1 >= 0) ? r1 : (r1 + 0xFFF);
        tmp = (tmp >> 12) << 12;
        ang1 = r1 - tmp;

        r2 = rand();
        q1 = r2 / 48;
        dist = r2 - q1 * 48;

        func_8012B0B4(pbuf, ang1, dist);
        t4 = buf;

        pos[0] = *(u16 *)(obj + 0x6) + t4;

        v3 = rand() % 24;

        base = *(s16 *)(obj + 0xA) - 0x34;

        r4 = rand();
        {
            s32 t1 = (r4 & 1) ? (base + v3) : (base - v3);
            pos[1] = t1;

            {
                register s32 hi4 __asm__("$3");
                hi4 = t4 >> 16;
                pos[2] = *(u16 *)(obj + 0xE) + hi4;
            }
            func_80143BDC(pos);
            i++;
        }
    }

    *(s32 *)(obj + 0x1C) = 0x10;
    *(u16 *)(obj + 0x34) += 1;

    for (i = 0; i < 3; i++) {
        func_8012C658(0x240, i, obj);
    }
}


extern void RotTransSV(void *a0, void *a1, void *a2);
extern u8 D_801DF68C[];
extern u8 D_801DF694[];

#define SRM_8018D720(r0) __asm__ volatile (          \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define STM_8018D720(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_8018D720(void *param_1)
{
    s32 *m;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;
    u16 cnt;

    m = (s32 *)(*(s32 *)((s32)param_1 + 0x20) + 0x34);

    SRM_8018D720(m);
    STM_8018D720(m);

    RotTransSV(D_801DF68C, sv0, &flag);
    RotTransSV(D_801DF694, sv1, &flag);

    func_8018D820(*(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12), (s32)sv0,
                  *(s16 *)((s32)param_1 + 0xDC));
    func_8018D820(*(s16 *)(*(s32 *)((s32)param_1 + 0x20) + 0x12), (s32)sv1,
                  *(s16 *)((s32)param_1 + 0xDC));

    cnt = *(u16 *)((s32)param_1 + 0xDC);
    cnt = cnt + 1;
    *(u16 *)((s32)param_1 + 0xDC) = cnt;
    if ((s16)cnt >= 3) {
        *(u16 *)((s32)param_1 + 0xDC) = 2;
    }
}


#include "common.h"

extern u8 * func_801290DC(s32 a0, u8 *a1);
extern void func_8001CD50(s32 a0, s32 a1);
extern u32 D_801DF5CC[];

u8 * func_8018D820(s32 a0, s32 a1, s32 a2) {
    register s32 s0 __asm__("$16") = a2;
    register s32 s2 __asm__("$18") = a0;
    u8 *s1;
    u8 *ret;
    register s32 v1 __asm__("$3");

    s1 = func_801290DC(0x17, (u8 *)a1);

    if (!s1) {
        return NULL;
    }

    s0 = *(s32 *)((char *)s1 + 0x20);
    func_8001CD50(s0, (s32)(&((u8 *)D_801DF5CC)[a2 << 6]));

    /* Force early materialization of the return value into a fresh reg
       (matches target: v0=s1 is scheduled right after the call, before
       the field-init stores). A plain `u8 *ret = s1;` gets copy-propagated
       away by cse and the move sinks to the `return` site instead. */
    __asm__ volatile("move %0, %1" : "=r"(ret) : "r"(s1));

    v1 = 0xC00;
    *(u16 *)((char *)s0 + 0x1E) = v1;
    v1 = 0x1000;
    *(u16 *)((char *)s0 + 0x1A) = v1;
    *(u16 *)((char *)s0 + 0x18) = v1;
    v1 = *(s32 *)((char *)s0 + 0x4);
    *(u16 *)((char *)s0 + 0x12) = s2;
    v1 |= 0x40000000;
    *(s32 *)((char *)s0 + 0x4) = v1;

    return ret;
}


#include "../shared/engine_core.h"  /* match_one-only: gives Mat32_8018A390_8018FE94; the real TU already includes this */

extern u16 D_80126CB4;
extern u16 D_80126CB6;
extern u16 D_80126CB8;
extern s32 *D_80126B78;
extern Mat32_8018A390_8018FE94 D_800AE620;

extern void func_8012B23C(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012B864(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_8018DDD0();
extern s32 func_8018DE30();

void func_8018D8B8(s32 a0) {
    s32 vec[3];                     /* sp+0x10 */
    s32 out[3];                     /* sp+0x20 */
    u16 sp30[3];                    /* sp+0x30 */
    u16 sv[3];                      /* sp+0x38 */
    s32 unused40[2];                /* sp+0x40 -- dead 8-byte slot the frame requires (§193-I) */
    Mat32_8018A390_8018FE94 m;      /* sp+0x48 */
    s32 pos[3];                     /* sp+0x68 (16.16 fixed point) */

    func_8012B23C(a0);

    sp30[0] = *(u16 *)(a0 + 0x3A);
    sp30[1] = *(u16 *)(a0 + 0x3E);
    sp30[2] = *(u16 *)(a0 + 0x42);

    if (func_8018DDD0(a0) != 0) {
        goto body;
    }

    *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x88);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A);
    *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0x8C);
    return;

found:
    *(s16 *)(a0 + 0x6) = sv[0];
    *(s16 *)(a0 + 0xA) = sv[1];
    *(s16 *)(a0 + 0xE) = sv[2];
    *(s32 *)(a0 + 0x14) = 0;
    goto tail;

body:
    *(s16 *)(a0 + 0x6) = D_80126CB4;
    *(s16 *)(a0 + 0xA) = D_80126CB6;
    *(s16 *)(a0 + 0xE) = D_80126CB8;

    vec[2] = (s32)0xFF600000;
    vec[1] = 0;
    vec[0] = 0;

    m = D_800AE620;
    RotMatrixY(*(s16 *)((u8 *)D_80126B78 + 0x12), &m);

    pos[1] = *(s32 *)(a0 + 0x8);
    do {
        pos[0] = *(s32 *)(a0 + 0x4);
        pos[2] = *(s32 *)(a0 + 0xC);
        func_800484EC((s32)&m, (s32)vec, (s32)out);
        pos[0] += out[0];
        pos[2] += out[2];
        sv[0] = *(u16 *)((u8 *)pos + 0x2);
        sv[1] = *(u16 *)((u8 *)pos + 0x6);
        sv[2] = *(u16 *)((u8 *)pos + 0xA);
        if (func_8018DE30(sp30, sv) == 1) {
            goto found;
        }
        vec[2] >>= 1;
    } while (-vec[2] > 0xFFFF);

    func_8012ADE4(a0);

tail:
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B864(a0);
}


#include "common.h"

/* func_8018DAA8 -- mass-lane fresh crack (Phase 31 wave p31f)
 *
 * State-gate then "avoid overlapping same-kind entity" scan of the 0x60-entry
 * table at D_801202A0 (stride 0x10C), same table/stride idiom as
 * func_80190B6C and func_8017CA14 in this TU.
 *
 * func_8012CC1C canonical form (void, $v0 cast) per sibling TUs
 * (ov_SC02_026/027/028's jr_* files): `((s32 (*)(s32,s32))func_8012CC1C)(a0,a1)`.
 * a1 is func_8018DAA8's own second parameter, forwarded untouched -- the
 * target never sets $a1 before the first jal, it just reuses the incoming
 * argument register.
 *
 * func_8012ADE4 / func_8012BC60 / func_8012B6D4 / func_8012B0B4 all already
 * declared in this TU (Law 2) -- reused verbatim.
 */

extern void func_8012ADE4(u8 *a0);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_80131E00(struct S80131E00*, s32);

s32 func_8018DAA8(s32 a0, s32 a1) {
    extern u8 D_801202A0[];
    s32 state;
    u8 *p;
    s32 i;
    s32 ang;
    s32 buf[2];

    state = ((s32 (*)(s32, s32))func_8012CC1C)(a0, a1);

    if ((state & 0xFF) == 2) {
        func_80131E00(a0, 0x12);
        return -1;
    }

    if (state != 0x2000) {
        func_8012ADE4((u8 *)a0);
        return 0;
    }

    for (i = 0, p = D_801202A0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(u16 *)a0 == *(u16 *)p && a0 != (s32)p) {
            if (func_8012BC60((struct Vec *)(a0 + 4), (struct Vec *)(p + 4)) < 0x1000) {
                *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);

                ang = func_8012B6D4((s16 *)(a0 + 4), (s16 *)(p + 4));
                func_8012B0B4((unsigned int *)buf, ang, 0x41);

                {
                    register s32 t1 __asm__("$2") = *(s32 *)(p + 4);
                    register s32 v1 __asm__("$3") = buf[0];
                    register s32 t2 __asm__("$2");
                    register s32 t3 __asm__("$4");
                    register s32 t4 __asm__("$2");

                    *(s32 *)(a0 + 4) = t1;

                    t2 = *(u16 *)(a0 + 6);
                    t3 = *(s32 *)(p + 0xC);
                    t2 = t2 + v1;
                    *(s32 *)(a0 + 0xC) = t3;
                    *(u16 *)(a0 + 6) = t2;

                    t4 = *(u16 *)(a0 + 0xE);
                    v1 = v1 >> 16;
                    t4 = t4 + v1;
                    *(u16 *)(a0 + 0xE) = t4;
                }
                goto found;
            }
        }
    }

found:
    return 1;
}


#include "common.h"

extern void func_8002A04C(void);
extern void func_8002AC00(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_801439C0(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_801E2900;

void func_8018DBF4(s32 a0) {
    u16 v1;

    if (*(s16 *)(a0 + 0x100) == 0) {
        func_8002A04C();
    }

    if (*(u8 *)(a0 + 0xC1) == 0xE) {
        func_8002AC00(0xA);
    }

    v1 = *(u16 *)(a0 + 0x70);
    if ((v1 & 1) == 0) {
        goto LCFC;
    }
    if ((v1 & 0x8000) != 0) {
        goto LD44;
    }
    if (*(u8 *)(a0 + 0xC1) == 0) {
        goto LCFC;
    }

    *(u8 *)(a0 + 0xC1) = 0;
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;

    {
        s32 ent;

        *(s16 *)(a0 + 0x5E) = 0;
        *(s16 *)(a0 + 0x5C) = 0;
        *(s16 *)(a0 + 0x76) = *(u16 *)(*(s32 *)(a0 + 0x78));
        ent = *(s32 *)(a0 + 0x20);
        *(s16 *)(ent + 0x14) = 0;
        *(s16 *)(ent + 0x12) = 0;
        *(s16 *)(ent + 0x10) = 0;
    }

    {
        u16 f88 = *(u16 *)(a0 + 0x88);
        u16 f8A = *(u16 *)(a0 + 0x8A);
        u16 f8C = *(u16 *)(a0 + 0x8C);

        *(s32 *)(a0 + 0x1C) = 0x40;
        *(s16 *)(a0 + 0xAA) = 0;
        *(s16 *)(a0 + 0x6) = f88;
        *(s16 *)(a0 + 0xA) = f8A;
        *(s16 *)(a0 + 0xE) = f8C;
        func_8012A828(a0, (void *)&D_801E2900);
    }

    if (*(s32 *)(a0 + 0xCC) != 0) {
        func_801439C0(*(s32 *)(a0 + 0xCC));
    }

    func_8012B2CC(a0);
    return;

LCFC:
    if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
        s32 v1c = *(s32 *)(a0 + 0x68);
        if (v1c != 0) {
            if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
                u16 v0c = *(u16 *)(v1c + 0xA);
                v0c &= 0x7FFF;
                *(u16 *)(v1c + 0xA) = v0c;
            }
        }
    }
LD44:
    func_8012C218((void *)a0);
}


extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);

s32 func_8018DD60(s32 obj) {
    s32 d = func_8012BCCC(obj);
    if (d < 0x2001) {
        *(s16 *)(obj + 0x2) = 7;
        return 1;
    }
    if (d > 0x24000) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x400) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 7;
    return 1;
}




s32 func_8018DDD0(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


#include "common.h"
#include "../shared/engine_core.h"

extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern s32 func_80134510(s32 arg);

s32 func_8018DE30(void *a0, SVECTOR *a1)
{
    SVECTOR tmp;
    SVECTOR in;
    SVECTOR out;

    if ((func_80133784(1, a0, (s32)a1) & 0x8000) != 0) {
        return 0;
    }

    tmp.vx = a1->vx;
    tmp.vy = a1->vy;
    tmp.vz = a1->vz;

    if (func_80134510((s32)&tmp) == 0) {
        return 0;
    }

    in.vx = tmp.vx;
    in.vy = tmp.vy;
    in.vz = tmp.vz;
    out.vx = tmp.vx;
    out.vy = tmp.vy + 8;
    out.vz = tmp.vz;

    if ((func_80133784(1, &in, (s32)&out) & 0x2000) == 0
        || *((u8 *)&out + 6) != 2) {
        a1->vy = tmp.vy;
        return 1;
    }

    return 0;
}



extern void (*D_801DF7B0[])(void);

void func_8018DF08(void *a0) {
    D_801DF7B0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

   /* 32 bytes, align 4 */
               /* 12 bytes, align 4 */

extern u8 D_80078EAE;
extern Mat32_8018A390_8018FE94 D_800AE620;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018DF44(void *a0)
{
    Mat32_8018A390_8018FE94 m;
    VECTOR vec;
    void *mp;

    vec.vy = 0;
    vec.vx = 0;
    if (!D_80078EAE) {
        vec.vz = (s32)0xFFFB8000;
    } else {
        vec.vz = (s32)0xFFFE8000;
    }

    *(s16 *)((s32)a0 + 0x2C) = 0x3C;
    *(s16 *)((s32)a0 + 0x2) = 1;

    m = D_800AE620;
    mp = &m;

    RotMatrixY(*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12), mp);

    func_800484EC((s32)mp, (s32)&vec, (s32)a0 + 0x10);
}


#include "common.h"

extern u16 D_801270C0;
extern s32 func_8018E0AC();
extern void func_801292C8(u8 *a0);

struct vec;
extern void func_8012931C(struct vec *a0);

void func_8018E014(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;
    s16 v1;
    u16 v0;
    s16 decremented;
    void *ptr_0x20;

    v1 = *(s16 *)&D_801270C0;

    if (v1 == 2) {
        return;
    }

    func_8018E0AC();

    v0 = *(u16 *)(s0 + 0x2C);
    decremented = v0 - 1;
    *(u16 *)(s0 + 0x2C) = decremented;

    if ((s16)v0 < 0) {
        func_801292C8((u8 *)s0);
        return;
    }

    ptr_0x20 = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr_0x20 + 0x18) += 0x100;

    ptr_0x20 = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr_0x20 + 0x1A) += 0x100;

    func_8012931C((struct vec *)s0);
}


extern s32 D_80126B58;
extern s32 func_8014CAFC(void);
extern s32 func_8018E208(void *a0);
extern u8 D_80078E78[];
extern u8 D_80078EAE;
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

s32 func_8018E0AC(arg0)
void *arg0;
{
    
    extern u8 D_80078EAE;
    u8 *base;
    u8 *p;
    s32 flag;
    s16 diff[3];
    s16 pointA[3];
    s32 v0;
    void *ptr;

    base = (u8 *)&D_80126B58;
    p = D_80078E78;
    flag = 0;

    if (func_8014CAFC() != 0) {
        if (D_80078EAE != 0) {
            return 0;
        }
        flag = 1;
    }

    if (func_8018E208(arg0) == 0) {
        return 0;
    }

    pointA[0] = *(u16 *)(base + 0x6);
    pointA[1] = *(u16 *)(base + 0xA);
    pointA[2] = *(u16 *)(base + 0xE);

    diff[0] = pointA[0] - *(u16 *)((u8 *)arg0 + 0x6);
    diff[1] = pointA[1] - *(u16 *)((u8 *)arg0 + 0xA);
    diff[2] = pointA[2] - *(u16 *)((u8 *)arg0 + 0xE);

    VectorNormalSS(diff, diff);

    pointA[1] -= 0x20;

    if (!flag) {
        v0 = p[0x36];
        func_8012F568(1, 0x5001, 0, (v0 ^ 1) * 10, (s32)pointA, (s32)diff);
    } else {
        func_8012F568(1, 0x4001, 0, 0xA, (s32)pointA, (s32)diff);
    }

    ptr = *(void **)((u8 *)arg0 + 0x20);
    *(u16 *)(base + 0x42) = *(u16 *)((u8 *)ptr + 0x12);

    return 1;
}


#include "common.h"

/* func_8018E208 — MATCH (84/84 ins, match_one byte-exact).
 *
 * The TU's already-MATCHED GTE idiom (func_8018F390 / func_801904BC: matrix-set
 * + RotTransSV x2 + func_80135888), extended with a COMPUTED matrix
 * (func_80020DA4 + func_80020F34, translation overwritten from the entity's
 * s16 position) and a 4-iteration loop over two advancing per-overlay
 * vertex-pair pointers (D_801DF7B8 and D_801DF7B8+0x20).  Returns 1 on the
 * first func_80135888 hit, else 0.
 *
 * THREE LEVERS were needed on top of the obvious shape (second-pass notes —
 * the first pass sat at 65 mismatched with this same structure):
 *
 * 1. LOOP-INVARIANT HOISTING IS THE PROLOGUE'S ORDERING ENGINE.  matrix, sv0,
 *    sv1 and &flag are written INLINE inside the loop (never via preheader
 *    pointer variables — exactly the matched sibling func_8018F390's idiom).
 *    loop.c then hoists all four to the preheader IN LOOP-USE ORDER, and sched
 *    lays their `addiu $sN,$sp,K` defs down in that same order: $s6=matrix,
 *    $s5=sv0, $s4=&flag, $s3=sv1.  Preheader POINTER VARIABLES instead
 *    (`sv0p = sv0;` etc.) put those defs in SOURCE order and permute the four
 *    callee-saved registers — the first pass's residual, which no amount of
 *    declaration reordering or register pinning could straighten out.
 *    Corollary the target proves: the two `addiu $aN,$sp,0x10` call arguments
 *    are SEPARATE materializations of &matrix.  Any `m = matrix;` before the
 *    calls lets cse feed that pseudo to both call sites (`move $a1,$s6`) — so
 *    the matrix pointer MUST come from the hoist, not from a source variable.
 *
 * 2. `base` MUST BE ITS OWN LOCAL.  `p1 = D_801DF7B8 + 0x20; p0 = D_801DF7B8;`
 *    folds the +0x20 into the %lo and back-computes p0 as `addiu $s0,$s1,-32`
 *    (3 ins).  Going through `base` keeps the symbol address in its own dead
 *    pseudo ($v1) and gives the target's 4-ins
 *    lui/addiu/`addiu $s1,$v1,0x20`/`addu $s0,$v1,$zero`.
 *
 * 3. THE `do { } while (0)` IS LOAD-BEARING — do not delete it.  It is a
 *    zero-code scheduling barrier (gcc-2.7.2 sched_analyze treats
 *    NOTE_INSN_LOOP_BEG/END as a full barrier, cookbook §164/§162j).  Without
 *    it sched2 hoists `p1 += 8` above the func_80135888 call, which leaves the
 *    conditional branch's delay slot empty; reorg then steals `li $v0,1` from
 *    the branch target and inverts beqz+j into a single bnez — 83 ins, a
 *    permanent LENGTH-DRIFT/-1.  Pinned in place, `addiu $s1,$s1,0x8` fills the
 *    beqz slot itself and the target's redundant `beqz … / j … / li $v0,1`
 *    double-branch survives.
 *
 * (A 4th, smaller one: `i` is initialised in the for-init, NOT earlier — an
 * early `i = 0;` outranks the hoisted `addiu $a1,$sp,0x10` by one slot.)
 */

extern s32 D_80126B58;                                     /* TU:53   verbatim */
extern void func_80020F34(s32 a0, s32 a1);                 /* TU:1656 verbatim */
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); /* TU:582  verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);      /* TU:3116 verbatim */

/* neither is declared anywhere in src/ or include/; func_80020DA4 takes the
 * (s32, s32) form of its TU-declared sibling func_80020F34.  D_801DF7B8 is
 * per-overlay data — a family remap must re-point it. */
extern void func_80020DA4(s32 a0, s32 a1);
extern u8 D_801DF7B8[];

/* NOT named gte_SetRotMatrix/gte_SetTransMatrix: the host TU already defines
 * those two names twice and a third definition would collide. */
#define SRM_8018E208(r0) __asm__ volatile (              \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define STM_8018E208(r0) __asm__ volatile (              \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

s32 func_8018E208(void *a0)
{
    s32 *cfg;
    s32  i;
    u8  *p0;
    u8  *p1;
    u8  *base;
    s32  matrix[8];   /* sp+0x10, MATRIX-shaped: t[] at matrix[5..7] */
    s32  sv0[2];      /* sp+0x30 */
    s32  sv1[2];      /* sp+0x38 */
    s32  flag;        /* sp+0x40 */
    s32  hit;

    cfg = (s32 *)&D_80126B58;
    p0 = (u8 *)*(s32 *)((s32)a0 + 0x20);

    func_80020DA4((s32)p0 + 0x10, (s32)matrix);
    func_80020F34((s32)matrix, (s32)p0 + 0x18);

    matrix[5] = *(s16 *)(p0 + 0x8);
    matrix[6] = *(s16 *)(p0 + 0xA);
    matrix[7] = *(s16 *)(p0 + 0xC);

    base = D_801DF7B8;
    p1 = base + 0x20;
    p0 = base;

    for (i = 0; i < 4; i++) {
        SRM_8018E208(matrix);
        STM_8018E208(matrix);

        RotTransSV(p0, sv0, &flag);
        RotTransSV(p1, sv1, &flag);

        hit = func_80135888(*(s32 *)((u8 *)cfg + 0x20), *(s32 *)((u8 *)cfg + 0x38),
                            (s32)sv0, (s32)sv1);
        do { } while (0);   /* scheduling barrier — see note 3, do not delete */
        p1 += 8;
        if (hit != 0) {
            return 1;
        }
        p0 += 8;
    }
    return 0;
}



extern void (*D_801DF818[])(void);

void func_8018E358(void *a0) {
    D_801DF818[*(u16 *)((s32)a0 + 0x2)]();
}



void func_8018E394(void *a0) {
        *(s16 *)((char *)a0 + 0x2) = 1;
        *(s32 *)((char *)a0 + 0x1c) = 2;
        *(s8 *)((char *)a0 + 0xfc) = 1;
        *(s8 *)((char *)a0 + 0xfe) = 2;
        *(s8 *)((char *)a0 + 0xfd) = 0;
        *(s8 *)((char *)a0 + 0xff) = 4;
        *(s16 *)((char *)a0 + 0xdc) = 0;
    }


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8018E420(s32 a0, u8 *a1);

void func_8018E3C8(u8 *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        func_8018E420(0, arg0 + 0xFD);
        func_8018E420(1, arg0 + 0xFE);
        func_8018E420(2, arg0 + 0xFF);
        *(s32 *)(arg0 + 0x1C) = 2;
    }
}


#include "common.h"

extern u32 D_801DF5CC[];
extern u32 D_801DF7F8[];
extern u32 D_801DF810;

void func_8018E420(s32 a0, u8 *a1) {
    u8 idx;
    u32 *dst;

    idx = *a1;
    if (idx >= 7) {
        *a1 = 0;
    }

    a0 <<= 6;
    idx = *a1;
    dst = (u32 *)((u8 *)D_801DF5CC + a0);
    *dst = D_801DF7F8[idx];

    idx = *a1;
    dst++;
    if (idx - 1 < 0) {
        *dst = D_801DF810;
    } else {
        *dst = D_801DF7F8[idx - 1];
    }

    (*a1)++;
}



extern void (*D_801DF84C[])(void);

void func_8018E4BC(void *a0) {
    D_801DF84C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

extern s32 D_801DF820[];
extern s32 D_801DF82C[];
extern s32 D_801DF844[];

void func_8018E4F8(void *a0)
{
    s32 buf[8];
    u16 out[4];
    register s32 zr __asm__("$0");
    register s32 v0 __asm__("$4");

    v0 = ((s32 (*)(void))func_8012C1B8)() + zr;
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801DF820[*(u16 *)((s32)a0 + 0x70) & 0xF]);

    *(s32 *)((s32)a0 + 0x1C) = 8;
    *(u16 *)((s32)a0 + 0x2) += 1;

    func_8012EC04(*(s32 *)((s32)a0 + 0x64), D_801DF82C[*(u16 *)((s32)a0 + 0x70) & 0xF], buf);
    ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, (s32)D_801DF844, out);

    *(u16 *)((s32)a0 + 0x6) = out[0];
    *(u16 *)((s32)a0 + 0xA) = out[1];
    *(u16 *)((s32)a0 + 0xE) = out[2];

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
}


extern s32 D_801DF838[];
extern s32 func_8012BEE8(s32 a0);

void func_8018E5E4(s32 a0) {
    s32 *p;
    s32 s0;
    s32 r;
    u16 h;

    if (func_8012BEE8(a0) == 0) {
        return;
    }
    s0 = a0;
    *(u16 *)(s0 + 0x2) += 1;
    r = rand();
    h = *(u16 *)(s0 + 0x70);
    p = D_801DF838;
    *(s32 *)(s0 + 0x48) = p[h & 0xF] + r % 1024;
    *(s32 *)(s0 + 0x1C) = 0x100;
    *(s32 *)(s0 + 0xE0) = rand();
}


#include "common.h"

extern s32 func_80047948(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012CBF4(s32);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8018E678(void *a0)
{
    s32 vec[3];
    s16 out[6];
    s16 t5;

    if ((*(u16 *)((s32)a0 + 0x70) & 0xF) == 2) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) -= 0x10;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = -0x400;
        }
    } else {
        vec[0] = func_80047948((*(s32 *)((s32)a0 + 0xE0) << 6) & 0xFC0) << 8;
        vec[1] = 0;
        vec[2] = 0;
        func_800484EC(*(s32 *)((s32)a0 + 0x20) + 0x34, (s32)vec, (s32)out);
        *(s16 *)((s32)a0 + 0x50) = out[1];
        t5 = out[5];
        *(s32 *)((s32)a0 + 0xE0) = *(s32 *)((s32)a0 + 0xE0) + 1;
        *(s16 *)((s32)a0 + 0x54) = t5;
    }

    if (((s32 (*)(s32))func_8012CBF4)((s32)a0) != 0) {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) += 1;
    } else if (func_8012BEE8((s32)a0) != 0) {
        func_8012C218(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_8018E780(s32 param_1)
{
    s32 iVar3;
    s32 uVar1;
    s32 sVar2;

    if (*(u16 *)(param_1 + 0x34) == 0) {
        if ((*(u16 *)(param_1 + 0x70) & 0xF) == 2) {
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
                *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + -0x80;
            if (*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) < -0x400) {
                *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = -0x400;
            }
        }
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 0) {
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) | 0x10;
        }
    } else {
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 0) {
            ((void (*)(s32))func_8012C218)(param_1);
        } else {
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = uVar1;
            *(s16 *)(iVar3 + 0x18) = uVar1;
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = sVar2 * 8 + 0x1000;
        }
    }
}


#include "common.h"

/* func_8018E8A0 — ov_SC02_011 / ov_SC02_011_jr_8017AE2C, 211 ins.
 * STATUS: MATCH (relocation-masked, 211/211; frame 0xC0 / vars=136 / regs=9).
 *
 * Five load-bearing spellings, each byte-proven against gcc-2.7.2 source:
 *
 * 1. TWO INDUCTION REGISTERS, $s6=obj+0xCC (biv) and $s4=obj+0xD4 (reduced giv).
 *    `q = zb + k * 3` makes q a giv of a COUNTER biv, so its add_val is the
 *    invariant pseudo `zb`, not a CONST_INT.  simplify_giv_expr (loop.c) refuses
 *    to fold `(reg) + (const)` into an add_val (both invariant, not CONSTANT_P
 *    => returns 0), so the four MEMs q[-1] q[0] ((s16*)q)[-1] ((s16*)q)[1] are
 *    NOT givs at all and keep their -4/-2/0/+2 offsets off $s4.  Spelling the
 *    same addresses off the pointer biv `p` instead gives CONST_INT add_vals,
 *    combine_givs merges all six into ONE register based at 0xD6, and the two
 *    registers collapse (measured: 210 ins, wrong offsets).
 *
 * 2. `zb = obj+0xD4` is assigned INSIDE the loop so LICM hoists it into the
 *    preheader; the giv init then coalesces with it into a single
 *    `addiu $s4,$s3,0xD4` after `addiu $s7,$sp,0x58`.  Assigned before the loop
 *    it stays in the entry block and costs `addiu $v1,$s3,212` + `move $s4,$v1`.
 *
 * 3. THE SECOND COUNTER `k` IS REQUIRED.  loop.c emits a reduced giv's update
 *    with emit_insn_before(..., biv_increment_insn), i.e. immediately BEFORE the
 *    biv it derives from.  The target's increment order is [i++][$s4+=12][$s6+=12],
 *    so the giv must hang off a biv that increments between i and p.  `k` is a
 *    dead counter that loop.c deletes after reduction, leaving exactly that order
 *    (and letting reorg steal `i++` into the `bne $s5,$v0` delay slot).
 *
 * 4. MEM_IN_STRUCT_P ASYMMETRY unblocks the entry-block schedule.  sched.c's
 *    true_dependence() drops a store->load dependence only when the LOAD is
 *    MEM_IN_STRUCT_P at a varying address and the STORE is neither.  Reading the
 *    trail count through a struct type (Cnt_8018E8A0) and writing prim.c[] through
 *    plain `*(u32 *)` casts is what lets the loop-bound `lh 0x108($s3)` float up
 *    past the colour stores; `prim.code` deliberately STAYS a struct member so it
 *    still pins the lh behind it.  With the natural spelling the lh is chained
 *    behind all five sp stores and lands next to the blez with a nop.
 *
 * 5. THE $a0 PIN TRIO.  `d = obj->x1C - i*4` is a global allocno; global.c marks
 *    REG_DEAD before the store, so the output freely reuses the dying $v1 and gcc
 *    picks `subu $v1,$v0,$v1`.  Pinning d alone makes gcc fold the load into $a0
 *    (`lw $a0` / `subu $a0,$a0,$v0`); pinning only the operands leaves d on $v1.
 *    All three pins together are the minimum that reproduces
 *    `lw $v0` / `sll $v1` / `subu $a0,$v0,$v1`.
 */

/* ---- integration surface (§161c), checked against
 *      src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c (func_8018E8A0 is the
 *      INCLUDE_ASM at line 9393):
 *   func_8012C218(void *a0)            TU:4256 verbatim  (also TU:4984 (void*))
 *   func_8004787C(s32 a0)              TU:2197 verbatim  (also TU:6679)
 *   func_80047948(s32 a0)              TU:2196 verbatim  (also TU:6678)
 *   ratan2(s32, s32)                   TU:243  verbatim  (TU:519 same types)
 *   func_80017758(void *, void *)      TU:1755 verbatim  (also TU:6125)
 *   func_80049CAC(s32, s32)            TU:3113 verbatim -> call site casts,
 *                                      exactly the TU's own idiom at TU:3143
 *   RotTransSV(void *, void *, void *) TU:3116 verbatim
 *   func_8012B414(int a0)              NOT declared in this TU; this is the
 *                                      fleet-canonical form (every other TU
 *                                      uses `int`), so the call site casts.
 *
 *   The GTE macros are named SRM_/STM_8018E8A0, NOT gte_SetRotMatrix /
 *   gte_SetTransMatrix: the host TU already defines those two names twice
 *   (TU:9781 and TU:10513) and a third definition would collide.
 *
 *   DATA (family remap must re-point these per overlay): D_801DF7F8 (u32[8]
 *   colour table) and D_801DF85C (u8[], SVECTOR quad source) have NO existing
 *   declaration anywhere in src/ or include/.
 */
extern void func_8012B414(int a0);
extern void func_8012C218(void *a0);
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern s32  ratan2(s32 a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32  func_80017758(void *a0, void *a1);

extern u32 D_801DF7F8[];
extern u8  D_801DF85C[];

#define SRM_8018E8A0(r0) __asm__ volatile (          \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define STM_8018E8A0(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

typedef struct { s16 vx, vy, vz, pad; } SVec8_8018E8A0;          /* 0x08 */
typedef struct { s32 vx, vy, vz, pad; } Vec16_8018E8A0;          /* 0x10 */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } Mtx_8018E8A0; /* 0x20 */
typedef struct { s16 f[0x86]; } Cnt_8018E8A0;
typedef struct {
    SVec8_8018E8A0 v[4];   /* 0x00 */
    u32            c[4];   /* 0x20 */
    s32            code;   /* 0x30 */
    s32            pad;    /* 0x34 */
} Prim_8018E8A0;           /* 0x38 */

void func_8018E8A0(void *a0)
{
    Vec16_8018E8A0  mv;      /* sp+0x10 */
    Prim_8018E8A0   prim;    /* sp+0x20 */
    Mtx_8018E8A0    mtx;     /* sp+0x58 */
    SVec8_8018E8A0  rot;     /* sp+0x78 */
    s32             flag;    /* sp+0x80 */
    s32            *p;
    s32            *q;
    s32            *zb;
    SVec8_8018E8A0 *src;
    SVec8_8018E8A0 *dst;
    register s32 d __asm__("$4");
    s32 i, j, k, base, ang, t;
    u32 col;

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x40;
    func_8012B414((s32)a0);

    mv.vz  = -0x40000;
    rot.vz = 0;
    col = D_801DF7F8[(*(u16 *)((s32)a0 + 0x10A))++ & 7];
    prim.code = 0x50000000;
    *(u32 *)((s32)&prim + 0x20) = col;
    *(u32 *)((s32)&prim + 0x24) = col;
    *(u32 *)((s32)&prim + 0x28) = col;
    *(u32 *)((s32)&prim + 0x2C) = col;

    p = (s32 *)((s32)a0 + 0xCC);
    for (i = 0, k = 0; i < ((Cnt_8018E8A0 *)a0)->f[0x84]; i++, k++, p += 3) {
        zb = (s32 *)((s32)a0 + 0xD4);
        { register s32 c1 __asm__("$2"); register s32 c2 __asm__("$3");
          c1 = *(s32 *)((s32)a0 + 0x1C); c2 = i * 4; d = c1 - c2; }
        if (d > 0x40) {
            if (i == 4) {
                func_8012C218(a0);
                return;
            }
            continue;
        }
        base = d << 6;
        ang = base & 0xFFF;
        flag = (func_8004787C(ang) << 4) >> 12;

        switch (*(s16 *)((s32)a0 + 0x70)) {
        case 0:
            t = ang;
            goto horiz;
        case 1:
            t = base + 0x800;
            t &= 0xFC0;
        horiz:
            mv.vy = (func_80047948(t) << 4) * flag;
            mv.vx = 0;
            rot.vx = -ratan2(mv.vy, mv.vz);
            rot.vy = 0;
            break;
        case 2:
            t = ang;
            goto vert;
        case 3:
            t = base + 0x800;
            t &= 0xFC0;
        vert:
            mv.vx = (func_80047948(t) << 4) * flag;
            mv.vy = 0;
            rot.vx = 0;
            rot.vy = ratan2(-mv.vz, mv.vx) - 0x400;
            break;
        }
        ((void (*)(void *, void *))func_80049CAC)(&rot, &mtx);

        q = zb + k * 3;
        p[0] += mv.vx;
        q[-1] += mv.vy;
        q[0] += mv.vz;
        mtx.t[0] = ((s16 *)p)[1];
        mtx.t[1] = ((s16 *)q)[-1];
        mtx.t[2] = ((s16 *)q)[1];

        src = (SVec8_8018E8A0 *)(D_801DF85C +
              ((s32)(s16)*(u16 *)((s32)a0 + 0x70) / 2) * 0x20);
        dst = prim.v;

        SRM_8018E8A0(&mtx);
        STM_8018E8A0(&mtx);

        for (j = 0; j < 4; j++, src++, dst++) {
            RotTransSV(src, dst, &flag);
        }
        func_80017758(&prim, (void *)(*(s32 *)((s32)a0 + 0x20) + 0x34));
    }

    *(s32 *)((s32)a0 + 0x1C) += 1;
    if ((*(s32 *)((s32)a0 + 0x1C) & 3) == 0) {
        if (((Cnt_8018E8A0 *)a0)->f[0x84] < 5) {
            ((Cnt_8018E8A0 *)a0)->f[0x84] = ((Cnt_8018E8A0 *)a0)->f[0x84] + 1;
        }
    }
}



extern void (*D_801DF89C[])(void);

void func_8018EBEC(void *a0) {
    D_801DF89C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);

void func_8018EC28(void *a0)
{
    s32 v0;
    s32 v1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, 0);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    func_8012B2CC((s32)a0);

    *(u16 *)((s32)a0 + 0x108) = 1;
    *(u16 *)((s32)a0 + 0x2) += 1;
}



extern void (*D_801E33D8[])(void);

void func_8018ECA8(void *a0) {
    D_801E33D8[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 58, 2524, 2527, 3139,
 * 3222, 3244, 3245).  Type mismatches are resolved by casting AT THE USE. */
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void *a1);
/* not declared anywhere in the TU */
extern void func_8018F390(void);

void func_8018ECE4(void *a0) {

    extern s32 D_801E3130[];
    extern u8 D_801E30C8[];
    extern u8 D_8019105C[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801E30C8);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801E3130[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_8018F390);
        *(s32 *)((s32)a0 + 0xCC) = res2;
    } else {
        val = *(s16 *)((s32)a0 + 0x70);
        val |= 0x4000;
        *(s16 *)((s32)a0 + 0x70) = val;
    }

    res2 = func_8012C658(0x8F, *(s16 *)((s32)a0 + 0x70), (s32)a0);
    *(s32 *)((s32)a0 + 0x6C) = res2;

    if (res2 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8012A828((s32)a0, D_8019105C);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_8018EDB8(void *a0) {
    void *p1, *p2;
    u16 val;
    long x;

    p1 = *(void **)(a0 + 0x20);
    p2 = *(void **)(a0 + 0x6C);
    val = *(u16 *)(p1 + 0x12);
    p2 = *(void **)(p2 + 0x20);
    val += 0x800;
    val &= 0xFFF;
    *(u16 *)(p2 + 0x12) = val;
    x = 2;
    *(u16 *)(a0 + 0x2) = x;
    return x;
}


void func_8018EDE0(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_8018EDE8(void *a0) {

    extern s32 D_801E3314;
    extern s32 D_801E3300;
    extern s32 D_801E32FC;
    extern s32 D_801E3394;
    extern s32 D_801E3328;
    extern s32 D_801E31F4[];
    extern s32 D_801E3278[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801E3314 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801E32FC = 0;
                D_801E3300 = D_801E3278[v0];
            } else {
                D_801E3300 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801E3278[v0], 1);
                D_801E32FC = 2;
            }
        } else {
            D_801E3314 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801E32FC = 0;
            D_801E3300 = D_801E31F4[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801E3328);
    } else {
        p = &D_801E3394;
        *p = *(s32 *)((char *)s0 + 0x0);
        func_80178CBC((s32)a0, (s32)(p - 7));
    }

    *(u16 *)(a0 + 0x2) = 4;
    *(u16 *)(a0 + 0x70) |= 0x8000;
}




/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (lines 43, 45, 58, 65, 2528, 2538, 2712, 3177, 3282).
 * Type mismatches resolved by casting AT THE USE (func_80178D18). */
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern s32 func_80029178(s32 arg);
extern void func_80029514(s32);
extern void func_80029124(s32, s32);
extern void func_80145EE8(s32 param_1);
extern void func_8012C218(void *a0);
extern s32 func_8018F138(void);

void func_8018EF34(void *arg0) {

    extern s32 D_801E3130[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801E3130[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801E3130[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_8018F138() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}



extern void func_8012C218(void *a0);
    s32 func_8018F054(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_8018F080(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_8018F090(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_8018F0A0(void *a0) {

    extern s32 D_801E3130[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801E3130[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_8018F0E0(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_8018F114(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_8018F138(void) {

    extern s32 D_801E3130[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801E3130[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801E3400[])(void);

void func_8018F19C(void *a0) {
    D_801E3400[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_8018F1D8(void *a0) {

    extern u8 D_801E30FC[];
    extern u8 D_801E3AC0[];
    extern u8 D_801E38A0[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801E30FC) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801E3AC0);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801E38A0);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018F260(void *a0) {

    extern u8 D_801E38B0[];
    extern u8 D_801E39B8[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E38B0);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E39B8);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_8018F320 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801E3AC0, else
 * D_801E38A0), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801E3AC0 / D_801E38A0)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_8018F320(void *a0) {

    extern u8 D_801E3AC0[];
    extern u8 D_801E38A0[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801E3AC0);
        } else {
            func_8012A828((s32)a0, D_801E38A0);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801E33F0[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();
#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

s32 aF8018A224() __asm__("func_8018F390");

s32 aF8018A224(param_1)
    void *param_1;
{
    s32 *m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    m = (s32 *)((u8 *)D_80126B78 + 0x34);
    obj = *(s32 *)((s32)param_1 + 0x64);

    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(D_801E33F0, sv0, &flag);
    RotTransSV(D_801E33F0 + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(obj + 0x20), *(s32 *)(obj + 0x58), (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}



extern s32 D_801EB908;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_8018F488(s32 a0, s32 a1) {
    D_801EB908 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801EB908;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_8018F4B8(s32 param_1) {

    extern M2C_UNK D_8019105C;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801E3AE4;
    extern char * D_801E3B18;
    extern char D_801EB8E8[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801E3AE4) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8019105C));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801EB908, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* pool-alloc: gcc routes the loaded pointer through a caller-saved reg ($v0)
       before the callee-saved home ($s1) — pin it to reproduce the extra move. */
    {
        register char *tmp __asm__("$2");
        tmp = D_801E3B18;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801E3B18 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801EB8E8 < puVar4) {
        D_801E3B18 = D_801EB8E8 - 0x120;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, puVar2);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)puVar2);

    uVar3 = *(u16 *)((char *)&s50 + 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)*(s16 *)((char *)&s50 + 2) < 0x80) {
        *(s16 *)((char *)&s50 + 2) = *(s16 *)((char *)&s50 + 2) - 4;
        {
            register char *tmp __asm__("$3");
            tmp = D_801E3B18;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801E3B18 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801EB8E8 < puVar4) {
            D_801E3B18 = D_801EB8E8 - 0x120;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), puVar2);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)puVar2);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(void *a0);


// @class: regalloc-order
// @stuck: none — MATCH (168 ins). Keys: (1) pin param->$s1 via `register int self __asm__("$17")=param_1`
//   (natural alloc put the short loop-counter in $s1); (2) block2's guarded dest via a test-temp
//   `td=load; if(td){dest=td; ...}` forces the range-split `lw $a1; addu $s3,$a1,$0` the target has;
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_8018F6FC(s32 param_1) {

    extern signed char D_801E3AD0[];
    register int self __asm__("$17") = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    iVar1 = *(int *)(self + 0x1c);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_801E3AD0;
        i = 0;
        dest = *(int *)(self + 0xcc);
        t = *(unsigned short *)(self + 0x70);
        *(short *)(buf + 0x0c) = 0;
        *(short *)(buf + 0x0a) = 0;
        *(short *)(buf + 0x08) = 0;
        *(short *)(buf + 0x1c) = 0;
        *(short *)(buf + 0x14) = 0;
        *(short *)(buf + 0x04) = 0;
        buf[0x22] = 0;
        buf[0x21] = 0;
        buf[0x20] = 0;
        buf[0x2a] = 0;
        buf[0x29] = 0;
        buf[0x28] = 0;
        buf[0x2e] = 0;
        buf[0x2d] = 0;
        buf[0x2c] = 0;
        *(int *)(buf + 0x30) = 0x50000000;
        buf[0x25] = t;
        buf[0x26] = t;
        buf[0x24] = t;
        do {
            *(short *)(buf + 0x00) = *p++;
            *(short *)(buf + 0x02) = *p++;
            *(short *)(buf + 0x10) = *p++;
            *(short *)(buf + 0x12) = *p++;
            *(short *)(buf + 0x18) = *p++;
            *(short *)(buf + 0x1a) = *p--;
            func_80017758(buf, (void *)dest);
            i++;
        } while (i < 4);

        td = *(int *)(self + 0xd0);
        if (td != 0) {
            dest = td;
            p = D_801E3AD0;
            i = 0;
            t = *(unsigned short *)(self + 0x70);
            *(short *)(buf + 0x0c) = 0;
            *(short *)(buf + 0x0a) = 0;
            *(short *)(buf + 0x08) = 0;
            *(short *)(buf + 0x1c) = 0;
            *(short *)(buf + 0x14) = 0;
            *(short *)(buf + 0x04) = 0;
            buf[0x22] = 0;
            buf[0x21] = 0;
            buf[0x20] = 0;
            buf[0x2a] = 0;
            buf[0x29] = 0;
            buf[0x28] = 0;
            buf[0x2e] = 0;
            buf[0x2d] = 0;
            buf[0x2c] = 0;
            *(int *)(buf + 0x30) = 0x50000000;
            buf[0x25] = t;
            buf[0x26] = t;
            buf[0x24] = t;
            do {
                *(short *)(buf + 0x00) = *p++;
                *(short *)(buf + 0x02) = *p++;
                *(short *)(buf + 0x10) = *p++;
                *(short *)(buf + 0x12) = *p++;
                *(short *)(buf + 0x18) = *p++;
                *(short *)(buf + 0x1a) = *p--;
                func_80017758(buf, (void *)dest);
                i++;
            } while (i < 4);
        }
        *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1;
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        __asm__ __volatile__("" : "=r"(self) : "0"(self));
        func_8012C218((void *)self);
    }
}



extern void (*D_801E3B1C[])(void);

void func_8018F99C(void *a0) {
    D_801E3B1C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH (94 ins). Keys: (1) cache out[0] in a local `o` before the switch so gcc
//   holds it in $a0 across the case stores (else it reloads/`lh` per case, +3 ins); (2) declare the
//   `in` struct BEFORE `out[2]` so in@sp+0x10 / out@sp+0x20; (3) the 0x14 word is written via
//   `*(s32*)&in.lo = D_80126B60` then the high short RMW'd `in.hi -= 0x20` (memory lhu/sh, not reg);
//   (4) order the three global assigns B60,B5C,B64 (B60 first → v0/v1/a2 alloc); (5) explicit
//   `case 2: break;` after case 3 so gcc emits the `beq $v1,2` test with case1 falling into case3.

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8002D4C8(s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8012B77C(void *, s32, void *);
extern void func_8012B2CC(s32);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_8018F9D8(s32 param_1) {

    extern M2C_UNK D_801E439C;
    extern u8   D_801E4174;
    extern u8 D_80126B5C;
    extern s32  D_80126B60;
    extern s32  D_80126B64;
    s32 iVar1;
    struct In in;
    s32 out[2];
    s32 t;
    s32 o;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_801E439C));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_801E4174);
    *(s16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 100;

    *(s32 *)&in.lo = D_80126B60;
    in.hi -= 0x20;
    in.w0 = (*(s32 *)&D_80126B5C);
    in.w2 = D_80126B64;
    func_8012B77C(out, param_1 + 4, &in);

    o = out[0];
    t = *(u16 *)(param_1 + 0x70) & 0xF;
    switch (t) {
    case 0:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
        break;
    case 1:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
    case 3:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)(o >> 16);
        break;
    case 2:
        break;
    }

    if (*(u16 *)(param_1 + 0x70) & 0x1000) {
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) << 1;
    }
    func_8012B2CC(param_1);
    ((void (*)(s32, s32))func_8012C588)(0xBC, param_1);
}



extern void (*D_801E4210[])(void);

void func_8018FB50(void *a0) {
    D_801E4210[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E4224[])(void);

void func_8018FB8C(void *a0) {
    D_801E4224[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801E41FC;
extern s32 D_801E4208;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_8018FBC8(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801E41FC);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801E4208, (s32)&D_800D3918, 0x19) == 0 &&
            (*(s16 *)(s0 + 0x70) == 2 || D_80126D50 == 0) &&
            func_8012BEE8(s0) == 0) {
            return;
        }
    }
    func_8012C218((void *)s0);
}



// @class: schedule
// @stuck: none — MATCH (71 ins). Tail schedule: read out.c into an explicit temp BEFORE the 0x5a/1 const stores so gcc hoists its lhu early (load-delay filled by li 0x5a) and stores out.c last from a held reg; without the temp gcc instead deferred out.b's store. in/out are two separate SV3{s16 a,b,c} stack slots (sp+0x10, sp+0x18) for ((void (*)(int, void *, void *))func_8012F214)(a0,&in,&out). 0x34 compare reads u16 (lhu, not lh).

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern int D_801E4218;

void func_8018FCA8(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801E4218);
        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        ((void (*)(int, void *, void *))func_8012F214)(param_1, &in, &out);
        *(short *)(param_1 + 6) = out.a;
        *(short *)(param_1 + 0xa) = out.b;
        c = out.c;
        *(int *)(param_1 + 0x1c) = 0x5a;
        *(short *)(param_1 + 0x34) = 1;
        *(short *)(param_1 + 0xe) = c;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - 0x80;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 4;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 5;
    func_8012AD80(param_1);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (expected); 16-bit sh stores via short* casts, s0=param_1 call-crossing

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_801E44CC;

void func_8018FDC4(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801E44CC);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}




extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_8018FE20(s32 a0)
{
    extern Rec8_8018A390_8018FE94 D_801E47C4[];

    s32 i;

    for (i = 0; (s16)D_801E47C4[i].x != 0; i++) {
        func_8012C658(0x10D, i, a0);
    }
}



/* func_8018FE94 — allocates a GTE-projection slot, seeds a random spread
 * vector from a per-index table, rotates it by the model's Y angle, applies
 * it to the object's matrix, adds it to the object's position, and seeds
 * three random spin fields.  MATCH (136/136 ins), match_one standalone.
 *
 * Declarations: func_8012B23C / func_8012AD50 / D_801E47C4 / D_801E484C are
 * NOT declared anywhere else in this TU (whole-TU grep, D2) so they're fresh
 * here; func_8012C1B8 / func_8012CAE4 / func_8001C214 / ApplyMatrixSV ARE
 * already file-scope in the TU (L163, L3160-3162) with these EXACT
 * signatures, so re-declaring them identically merges silently (D3).
 *
 * §48 STRUCT ASSIGN: `m = D_800AE620;` on the 32-byte, 4-aligned matrix
 * routes move_by_pieces to the plain lw/lw/lw+sw/sw/sw grouping (no lwl/lwr).
 *
 * §48-C2: `sv = D_801E47C4[idx];` on the 8-byte, 2-aligned (u16 x,y,z; s16 w)
 * record struct falls through move_by_pieces' align>=4 test and emits the
 * lwl/lwr+swl/swr unaligned block-move pair instead — matches the target's
 * four unaligned loads/stores exactly.
 *
 * REGALLOC LEVER (new, byte-verified this session — candidate for the
 * cookbook): a redundant `void *s1 = a0;` local (never reassigned, used only
 * as an alias for the parameter) made gcc-2.7.2 split the parameter pseudo
 * into TWO allocnos — one for its pre-call uses (landing in $s0) and a
 * SEPARATE one (bridged by an extra `move`) for its post-call/cross-branch
 * uses (landing in $s1) — even though the target uses ONE register ($s1)
 * uniformly from the second prologue instruction on. Referencing the
 * parameter `a0` directly everywhere (no alias local) collapses this back to
 * a single allocno and fixed 6 of the 11 mismatches outright.
 *
 * The remaining 5 (an `addu $a0,$v0,zero` copy scheduled too EARLY, and the
 * alloc-check branch/store testing `$a0` instead of `$v0` directly) were a
 * v0-pseudo/call-arg-copy coalescing difference: gcc folded the store, the
 * branch test, AND the func_8012C1B8 return value into one $a0-homed pseudo.
 * Folding the store and the compare into ONE C expression —
 * `if ((*(s32*)(a0+0x20) = v0 = func_8012C1B8()) == 0)` — instead of two
 * separate statements (assign-then-test) made cc1 keep the store/test on the
 * call's native $v0 and defer the $a0 copy to just before its actual
 * consumer (func_8001C214), matching the target's schedule exactly. No
 * register pins, no permuter, no zero-byte asm barriers needed for either
 * residual — both C-lever-closeable (§136-class local-variable/expression-
 * shape levers).
 */
void func_8018FE94(void *a0)
{
          /* 32B, align 4 */
 /* 8B, align 2 */

    extern Mat32_8018A390_8018FE94 D_800AE620;
    extern Rec8_8018A390_8018FE94 D_801E47C4[];
    extern s32 D_801E484C[];

    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8012B23C(s32 a0);
    extern s32 func_8012AD50(void *a0);
    extern s32 rand(void);

    Mat32_8018A390_8018FE94 m;               /* sp+0x10 */
    Rec8_8018A390_8018FE94 sv;               /* sp+0x30 */
    void *mp;
    void *svp;
    s32 v0;
    s16 w;

    m = D_800AE620;
    sv = D_801E47C4[*(s16 *)((s32)a0 + 0x70)];

    mp = &m;
    svp = &sv;

    if ((*(s32 *)((s32)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(a0);
        return;
    }

    w = sv.w;
    func_8001C214(v0, D_801E484C[w]);

    RotMatrixY(*(s16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12), mp);

    ApplyMatrixSV(mp, svp, svp);

    *(u16 *)((s32)a0 + 0x6) += sv.x;
    *(u16 *)((s32)a0 + 0xA) += sv.y;
    *(u16 *)((s32)a0 + 0xE) += sv.z;
    func_8012B23C((s32)a0);

    *(s16 *)((s32)a0 + 0x12) = (s16)sv.x >> 3;
    *(s16 *)((s32)a0 + 0x16) = (s16)sv.y >> 3;
    *(s16 *)((s32)a0 + 0x1A) = (s16)sv.z >> 3;

    *(s16 *)((s32)a0 + 0xFC) = (s16)((rand() & 0x7FF) - 0x400) >> w;
    *(s16 *)((s32)a0 + 0xFE) = (s16)((rand() & 0x7FF) - 0x400) >> w;
    *(s16 *)((s32)a0 + 0x100) = (s16)((rand() & 0x7FF) - 0x400) >> w;

    func_8012AD50(a0);
}



extern void (*D_801E4858[])(void);

void func_801900B4(void *a0) {
    D_801E4858[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_801900F0(s32 a0) {
    u8 *s0;
    s16 val1;
    s16 val2;

    func_8012AD80(a0);
    s0 = (u8 *)a0;

    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x10) += *(u16 *)(s0 + 0xFC);
    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x12) += *(u16 *)(s0 + 0xFE);
    *(u16 *)(*(u32 *)(s0 + 0x20) + 0x14) += *(u16 *)(s0 + 0x100);

    val1 = *(s16 *)(*(s32 *)(s0 + 0x64) + 0x0A);
    val2 = *(s16 *)(s0 + 0x0A);

    if (val2 > val1) {
        func_8012C218((void *)a0);
    }
}



extern void (*D_801E8654[])(void);

void func_80190184(void *a0) {
    D_801E8654[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern void func_8012A828(s32, void *);
extern void func_801904BC(void);

extern u8 D_801E8554[];
extern u8 D_801E38A0[];

void func_801901C0(s32 param_1) {
    s32 v;

    if (((s32 (*)(s32, void *))func_8012C354)(
            param_1, &D_801E8554[(*(u16 *)(param_1 + 0x70) & 0xF) * 0x34]) != 0) {
        if ((*(u16 *)(param_1 + 0x70) & 1) == 0) {
            v = func_8012C658(0x1E3, 1, param_1);
            *(s32 *)(param_1 + 0x6C) = v;
            if (v == 0) {
                ((void (*)(s32))func_8012CAE4)(param_1);
            } else {
                *(s16 *)(param_1 + 0x2) = 1;
                *(s32 *)(param_1 + 0xCC) =
                    ((s32 (*)(s32, void *))func_801788B8)(param_1, func_801904BC);
            }
        } else {
            *(s16 *)(param_1 + 0x2) = 5;
            *(u16 *)(param_1 + 0x100) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x36);
            func_8012A828(param_1, D_801E38A0);
        }
    }
}




s32 func_80190298(void *a0) {
    void *p1, *p2;
    u16 val;
    long x;

    p1 = *(void **)(a0 + 0x20);
    p2 = *(void **)(a0 + 0x6C);
    val = *(u16 *)(p1 + 0x12);
    p2 = *(void **)(p2 + 0x20);
    val += 0x800;
    val &= 0xFFF;
    *(u16 *)(p2 + 0x12) = val;
    x = 2;
    *(u16 *)(a0 + 0x2) = x;
    return x;
}


void func_801902C0(void) {
}

extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_801E8604;
    void func_801902C8(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_801E8604);
    }



extern s32 func_801789AC(s32);
extern void func_80178D18(void);

void func_801902F4(s32 a0) {
    if (((int (*)(void))func_801789AC)() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 2;
    }
}


extern u8 D_801E38B0[];
extern u8 D_801E39B8[];
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);

void func_80190334(void *a0) {

    extern u8 D_801E38B0[];
    extern u8 D_801E39B8[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0x100) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 6;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E38B0);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 6;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801E39B8);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E38A0[];

void func_801903F4(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        if (*(s16 *)((s32)a0 + 0xFE) == 2) {
            func_8002D4C8(0x888, 0);
            func_8012A828((s32)a0, D_801E38A0);
        }
        *(s16 *)((s32)a0 + 0x2) = 5;
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


void func_80190460(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80190470(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }





s32 func_80190480(void) {

    extern s32 D_801EB924;
    return !(D_801EB924 ^ 1);
}


extern void func_800296F8(void);
    s32 func_80190498(s32 arg0) {
        ((void (*)(s32))func_800296F8)(*(s32 *)(arg0 + 0xdc));
    }


#include "common.h"

extern s32 *D_80126B78;
extern u8 D_801E8670[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();
extern void RotTransSV(void *a0, void *a1, void *a2);

/* local copy of src/shared/engine_types.h's MATRIX (short m[3][3]; long t[3];) --
 * common.h does not pull in engine_types.h, so declare it locally rather than
 * touching the shared header. */


#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

/* §71 sibling: identical shape to func_8018F390 (same TU, this file, D_80126B78/RotTransSV/
 * func_80135888/func_8012BDBC/func_80178BF8/func_80172710 idiom) already MATCHED -- only the
 * per-overlay data symbol (D_801E8670 vs D_801E33F0) differs. §37 asm-label alias avoids the
 * `conflicting types` clash with the fleet's `extern void func_801904BC(void);` used elsewhere
 * in this TU as a state-handler function pointer. */

s32 aF801904E0() __asm__("func_801904BC");

s32 aF801904E0(param_1)
    void *param_1;
{
    MATRIX m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    obj = *(s32 *)((s32)param_1 + 0x64);
    m = *(MATRIX *)((u8 *)D_80126B78 + 0x34);

    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);

    RotTransSV(D_801E8670, sv0, &flag);
    RotTransSV(D_801E8670 + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x20),
                       *(s32 *)(*(s32 *)((s32)param_1 + 0x64) + 0x58),
                       (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_801E86CC[])(void);

void func_80190610(void *a0) {
    D_801E86CC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80190B6C(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80190BC4(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8019064C(s32 a0) {
    extern u8 D_801E8680[];
    extern u8 D_801E868C[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_80190B6C(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801E8680, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801E868C);
        func_80190BC4(a0);
        *(u16 *)(s0 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA);
        t = *(u16 *)(a0 + 0xE);
        *(u16 *)(s0 + 0x1A) = 0x2000;
        *(u16 *)(s0 + 0x18) = 0x2000;
        *(u16 *)(s0 + 0x2C) = 0xC010;
        *(u16 *)(s0 + 0xC) = t;
        v = *(u16 *)(a0 + 0x2) + 1;
        u = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(s32 *)(a0 + 0x1C) = 0x180;
        *(u16 *)(a0 + 0x2) = v;
        *(u16 *)(a0 + 0x10A) = u;
        func_8002D4C8(0xAA0, 0);
    }
}


extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80190BC4(s32 arg0);
extern void func_80190C40(void *arg0);

void func_80190748(s32 arg0) {
    s32 p;
    s32 q;
    s32 r;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;
    s32 t3;
    s32 t4;
    u16 v;
    u16 w;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(arg0 + 0x10A) == *(s16 *)(p + 0x36) && *(s16 *)(p + 0x76) > 0) {
        if (*(s32 *)(arg0 + 0x1C) == (*(s32 *)(arg0 + 0x1C) / 0x30) * 0x30 &&
            *(u8 *)(p + 0xC1) == 0) {
            *(s16 *)(p + 0x60) = 0xA;
            *(u16 *)(p + 0x5C) |= 1;
            v = *(u16 *)(*(s32 *)(p + 0x20) + 0x12);
            *(s16 *)(p + 0x5E) = 1;
            *(u16 *)(p + 0x62) = v + 0x800;
            *(u16 *)(p + 0x7C) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(p + 0x7E) = *(u16 *)(arg0 + 0xA);
            *(u16 *)(p + 0x80) = *(u16 *)(arg0 + 0xE);
        }
        if ((*(s32 *)(arg0 + 0x1C) & 7) == 0) {
            q = func_80132EF4(arg0, 0x22);
            if (q != 0) {
                t0 = rand();
                u0 = *(u16 *)(q + 0x6) - 0x10;
                *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                t1 = rand();
                u1 = *(u16 *)(q + 0xE) - 0x10;
                *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                *(u16 *)(q + 0xA) -= 0x20;
                t2 = rand();
                *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 3) << 16);
                t3 = rand();
                t4 = rand();
                *(s16 *)(q + 0x34) = ((t3 % 0x1800 + 0x1000) & ~0xF) | (t4 & 1);
                *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                *(s32 *)(*(s32 *)(q + 0x20) + 0x4) |= 0x40000000;
            }
        }
        r = *(s32 *)(arg0 + 0xCC);
        if (r != 0) {
            func_80128ED8((void *)r, (void *)(arg0 + 0xDC));
            func_80190BC4(arg0);
            *(u16 *)(r + 0x8) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(r + 0xA) = *(u16 *)(arg0 + 0xA);
            w = *(u16 *)(arg0 + 0xE);
            *(u16 *)(r + 0x18) += 0x15;
            *(u16 *)(r + 0x1A) += 0x15;
            *(u16 *)(r + 0xC) = w;
        }
        if (*(u16 *)(p + 0x5E) == 0x23) {
            *(u16 *)(arg0 + 0x2) += 1;
        }
        if (func_8012BEE8(arg0) == 0) {
            return;
        }
    }
    func_80190C40((void *)arg0);
}


extern u16 D_800B99DA;

extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80190BC4(s32 arg0);
extern void func_80190C40(void *arg0);

void func_801909D8(s32 arg0) {
    s32 p;
    s32 q;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;

    p = *(s32 *)(arg0 + 0xCC);
    if (p != 0) {
        func_80128ED8((void *)p, (void *)(arg0 + 0xDC));
        func_80190BC4(arg0);
        *(u16 *)(p + 0x8) = *(u16 *)(arg0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(arg0 + 0xE);
        *(u16 *)(p + 0x18) -= 0x200;
        *(u16 *)(p + 0x1A) -= 0x200;
        if (*(s16 *)(p + 0x18) >= 0) {
            if (D_800B99DA % 5 == 0) {
                q = func_80132EF4(arg0, 0x22);
                if (q != 0) {
                    t0 = rand();
                    u0 = *(u16 *)(q + 0x6) - 0x10;
                    *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                    t1 = rand();
                    u1 = *(u16 *)(q + 0xE) - 0x10;
                    *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                    *(u16 *)(q + 0xA) -= 0x20;
                    t2 = rand();
                    *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 4) << 16);
                    *(s16 *)(q + 0x34) = rand() % 0x1800 + 0x2000;
                    *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                }
            }
            return;
        }
    }
    func_80190C40((void *)arg0);
}


#include "common.h"

/* func_80190B6C — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_80190B6C(s32 arg0) {
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x35C && *(s32 *)(arg0 + 0x64) == *(s32 *)(p + 0x64) &&
            arg0 != (s32)p) {
            return 1;
        }
        p += 0x10C;
    }
    return 0;
}


#include "common.h"

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80190BC4(s32 arg0) {
    s32 buf[8];
    u16 out[4];
    s32 p;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(p + 0x36) == *(s16 *)(arg0 + 0x10A)) {
        func_8012EC04(p, *(s16 *)(arg0 + 0xFC), buf);
        ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, arg0 + 0x88, out);
        *(u16 *)(arg0 + 0x6) = out[0];
        *(u16 *)(arg0 + 0xA) = out[1];
        *(u16 *)(arg0 + 0xE) = out[2];
    }
}


#include "common.h"

/* func_80190C40 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_80190C40(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}


#include "common.h"

/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_80190C84(s32 a0, u16 *a1, s16 a2) {
    struct S80190C84 sp;
    u16 t;
    sp.f0 = a1[0];
    sp.f2 = a1[1];
    t = a1[2];
    sp.f6 = 0x35C;
    sp.fA = 0;
    sp.f8 = 0;
    sp.fE = a2;
    sp.f10 = 0;
    sp.fC = 0x7FFF;
    sp.f4 = t;
    func_8012C51C(&sp, a0);
}





