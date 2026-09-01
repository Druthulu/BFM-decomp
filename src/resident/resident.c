#include "common.h"

/* func_800CEDFC:
 *   v1 = D_800B99F0 (u16, lhu)
 *   if ((u32)v1 < 0x14)  [sltiu, beqz]
 *       D_800D3430[v1]()   ; function-pointer table, sll v1,2 -> word index
 *   return (void)
 *
 * The frame (sw ra; addiu sp,-0x18) is allocated because of the indirect call.
 */
extern u16 D_800B99F0;
extern void (*D_800D3430[])(void);

void func_800CEDFC(void) {
    u16 idx = D_800B99F0;
    if (idx < 0x14) {
        D_800D3430[idx]();
    }
}

extern u16 D_800B99F6;
extern void (*D_800D3480[])(void);

void func_800CEE40(void) {
    if (D_800B99F6 < 2) {
        D_800D3480[D_800B99F6]();
    }
}

extern s16 D_800B9A00;
extern s32 D_80127084;
extern s32 D_80114E78;
extern void func_80029344(void);
extern void func_8001B324(void);
extern void func_8002AEF8(void);
extern void func_80029254(void);
extern void func_800CFBBC(void);
extern void func_80011DCC(void);
extern void func_80010AE0(s32);
extern void func_80011C10(void);
void func_800CEE84(void) {
    func_80029344();
    D_80127084 = 0;
    D_80114E78 = 0;
    if (D_800B9A00 != 0) {
        D_80127084 = 1;
    }
    func_8001B324();
    func_8002AEF8();
    func_80029254();
    func_800CFBBC();
    func_80011DCC();
    func_80010AE0(0x3E0);
    func_80011C10();
}

extern s32 func_800D0488(s32 arg0);
extern void func_80011A3C(void);

void func_800CEF04(void) {
    if (((s32 (*)())func_800D0488)(1)) {
        func_80011A3C();
    }
}

extern void func_8001B324(void);
extern void func_80011A3C(void);

void func_800CEF34(void) {
    func_8001B324();
    func_80011A3C();
}

// func_800CEF5C  -- MATCH (21 ins)
// Body is the straightforward 3-call / 4-store sequence. The ONLY subtlety is the
// stack frame: target is -0x20 with ra@0x18 (gcc: vars=8, args=16, regs=1), i.e. it
// reserves 8 bytes of LOCALS that no instruction ever touches (all three jal delay
// slots are nop, no addiu a0,sp,X). A normal dead local is eliminated by -O2; only a
// `volatile` local survives unused. A `volatile int loc[2]` reserves exactly those
// 8 bytes and emits no access -> the frame and the all-nop delay slots match exactly.
// (Likely the original had a small on-stack scratch buffer; the bytes pin it to 8.)
extern void func_8001B324(void);
extern void func_8001C0C8(void);
extern void func_80011A3C(void);
extern u8  D_800B9A12;
extern s8  D_800B9A10;
extern u8  D_800B9A17;
extern s16 D_800B9A0E;

void func_800CEF5C(void) {
    volatile int loc[2];
    func_8001B324();
    D_800B9A12 = 1;
    D_800B9A10 = 0;
    D_800B9A17 = 0;
    func_8001C0C8();
    D_800B9A0E = 0;
    func_80011A3C();
}

extern void func_80011A3C(void);

void func_800CEFB0(void) {
    func_80011A3C();
}

#include "common.h"

void func_800CEFD0(void) {
    extern void func_8001B85C(void);
    extern s32 func_8001B86C(s32);
    extern void func_80011B7C(s32);
    extern void func_800596F4(s32);
    extern void VSync(s32);
    extern void func_80059CF4(s32);
    extern void func_8001AF34(void);

    extern s32 D_80114E98;
    extern s32 D_80114E9C;
    extern u16 D_800B99F6;
    extern void (*D_800D3488[])(void);
    extern u8 D_800AF630[];
    extern s32 D_800A651C;

    u8 *base = &(*(u8 *)&D_800AF630);

    D_80114E98 = 0;
    D_80114E9C = 0;
    func_8001B85C();

loop:
    if (D_80114E98 == 0) {
        D_800D3488[D_800B99F6]();
    }
    if (D_80114E9C == 0) {
        D_80114E9C = func_8001B86C(0);
    }
    if (D_80114E98 != 0 && D_80114E9C != 0) {
        func_80011B7C(7);
        return;
    }
    func_800596F4(0);
    VSync(*(s32 *)(base + 0xA3E8));
    func_80059CF4(*(s32 *)((u8 *)&D_800A651C + *(u16 *)(base + 0xA3D2) * 20) + 4);
    func_8001AF34();
    goto loop;
}


// func_800CF104 — resident engine main loop (vsync/dispatch).
//   D_80114E98 = 0; D_80114E9C = 0;            (two s32 globals zeroed, source order)
//   func_8001B85C();
// loop:                                         (.L800CF130 — loop TOP, after the inits)
//   if (D_80114E98 == 0) D_800D3488[D_800B99F6]();   (fn-ptr table; D_800B99F6 u16/lhu, sll2)
//   if (D_80114E9C == 0) D_80114E9C = func_8001B86C(1);   (result stored full word, s32)
//   if (D_80114E98 != 0 && D_80114E9C != 0) { func_80011B7C(7); return; }   (beqz;beqz = AND)
//   func_800596F4(0);
//   VSync(*(s32 *)(p + 0xA3E8));               (p = &D_800AF630; 0xA3E8 -> lui1/addu/-0x5C18)
//   func_80059CF4(D_800A651C[*(u16*)(p+0xA3D2) * 5] + 4);  (u16 field; i*5 word index)
//   func_8001AF34();
//   goto loop;
//
// MATCH KEY (the hard part): the loop MUST be written with an explicit `goto loop;`, NOT
// `while(1)` / `for(;;)` / `do-while`. gcc-2.7.2's loop.c only runs loop-invariant code
// motion on natural loops it recognizes from the structured forms; with those, it HOISTS
// the loop-invariant global addresses %hi(D_80114E98)/%hi(D_80114E9C) into callee-saved
// registers (s1/s2, frame -0x20, +6 ins) — which the target does NOT do. The goto form is
// not recognized as a hoistable loop, so each global access stays a fresh `lui %hi; lw %lo`
// (re-materialized, frame -0x18, only s0 used) — matching the target exactly.
// `register u8 *p = D_800AF630` is still required so the two far fields (0xA3E8, 0xA3D2)
// assemble to the register-relative `lui at,1; addu at,s0,at; lw/lhu -off(at)` split.
extern s32 D_80114E98;
extern s32 D_80114E9C;
extern u16 D_800B99F6;
extern void (*D_800D3488[])(void);
extern u8  D_800AF630[];
extern s32 D_800A651C[];
extern void func_8001B85C(void);
extern s32  func_8001B86C(s32);
extern void func_80011B7C(s32);
extern void func_800596F4(s32);
extern void VSync(s32);
extern s32  func_80059CF4(s32);
extern void func_8001AF34(void);

void func_800CF104(void) {
    register u8 *p = D_800AF630;
    D_80114E98 = 0;
    D_80114E9C = 0;
    func_8001B85C();
loop:
    if (D_80114E98 == 0) {
        D_800D3488[D_800B99F6]();
    }
    if (D_80114E9C == 0) {
        D_80114E9C = func_8001B86C(1);
    }
    if (D_80114E98 != 0 && D_80114E9C != 0) {
        func_80011B7C(7);
        return;
    }
    func_800596F4(0);
    VSync(*(s32 *)(p + 0xA3E8));
    func_80059CF4(D_800A651C[*(u16 *)(p + 0xA3D2) * 5] + 4);
    func_8001AF34();
    goto loop;
}

/* func_800CF238 — MATCH (78 ins). Two-state poll loop over D_80114E98 with a
 * terminal inner loop and a service block.
 *
 * KEY TECHNIQUES (feed back to cookbook — "single-base-register loop" idioms):
 *  1. The far-member base &D_800AF630 must be held in the ONE callee-saved reg s0.
 *     `register u8 *p = D_800AF630;` pins it; the three far members are p+offset
 *     (offset >0x7FFF -> as expands `lui at,1; addu at,s0,at; l{hu,w} -0x5cXX(at)`).
 *  2. gcc-2.7.2 -O2 LICM otherwise ALSO hoists each indexed-array base
 *     (&D_800D3488, &D_800A651C) into extra callee regs (s1/s2) -> wrong frame.
 *     To force those bases to RELOAD inside the loop (folded `lui %hi; addu; l* %lo`),
 *     write the access as a byte-pointer + SHIFTED index, NOT array[]:
 *        table: (*(void(**)(void))((char*)D_800D3488 + (idx << 2)))()
 *        array: *(s32*)((char*)D_800A651C + ((idx*5) << 2))
 *     The `<< 2` (shift, not `* 4`) is load-bearing — it makes gcc fold the symbol
 *     into the load and keep only s0 held (frame -0x18, the target).
 *  3. Block ORDER / branch polarity is via explicit labels+gotos:
 *     - inner loop exit (L2F0: func_80011B7C(8); j L35C) is a SEPARATE block reached
 *       by `bnez`, so the CONTINUE path (== 0) is the then-block / fall-through.
 *     - the shared epilogue (L35C) is a single `goto`-target at the end so the exit
 *       does `j .L800CF35C` instead of an inline epilogue.
 */
extern s32 D_80114E98;
extern u16 D_800B99F6;
extern u8 D_800AF630[];
extern s32 D_800A651C[];
extern void (*D_800D3488[])(void);
extern void func_8001B85C(void);
extern void func_80128158(void);
extern void VSync(s32 arg0);
extern void func_8001AF34(void);
extern void func_80011B7C(s32 arg0);
extern void func_800596F4(s32 arg0);
extern s32 func_80059CF4(s32 arg0);

void func_800CF238(void) {
    register u8 *p = D_800AF630;
    D_80114E98 = 0;
    func_8001B85C();
L25C:
    if (D_80114E98 == 0) {
        (*(void (**)(void))((char *)D_800D3488 + (D_800B99F6 << 2)))();
        if (D_80114E98 == 0) {
            goto L300;
        }
    }
L2AC:
    func_80128158();
    if (*(u16 *)(p + 0xA3C2) == 0) {
        VSync(*(s32 *)(p + 0xA3E8));
        func_8001AF34();
        goto L2AC;
    }
    func_80011B7C(8);
    goto L35C;
L300:
    func_800596F4(0);
    VSync(*(s32 *)(p + 0xA3E8));
    func_80059CF4(*(s32 *)((char *)D_800A651C + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) + 4);
    func_8001AF34();
    goto L25C;
L35C:
    return;
}

/* func_800CF370:
 *   jal func_8001A9F8(0)
 *   jal func_80011B7C(0xF)
 *   return (void)
 */
extern void func_8001A9F8(s32);
extern void func_80011B7C(s32);

void func_800CF370(void) {
    func_8001A9F8(0);
    func_80011B7C(0xF);
}

extern void func_80011A3C(void);

void func_800CF398(void) {
    func_80011A3C();
}

/* func_800CF3B8 — MATCH (49 ins). A poll loop: zero two flags, then spin calling a
 * dispatch handler + VSync until D_80114E98 is set, then tear down.
 *
 * KEY TECHNIQUES (same family as func_800CF238 — "single-base-register loop"):
 *  1. The far member D_800B9A18 (= &D_800AF630 + 0xA3E8) is read via the ONE held
 *     callee-saved reg s0: `register u8 *p = D_800AF630;` then `*(s32*)(p + 0xA3E8)`
 *     (offset >0x7FFF -> as expands `lui at,1; addu at,s0,at; lw a0,-0x5C18(at)`).
 *  2. The handler table base &D_800D3488 must RELOAD inside the loop (folded
 *     `lui %hi; addu; lw %lo`), NOT hoist into a second callee reg. Force that by
 *     writing the call as a byte-pointer + SHIFTED index:
 *        (*(void(**)(void))((char*)D_800D3488 + (D_800B99F6 << 2)))()
 *     The `<< 2` (shift, not array[]) makes gcc fold the symbol and keep only s0
 *     held (frame -0x18). Plain `D_800D3488[idx]()` hoists &D_800D3488 into s1 -> -0x20.
 *  3. LOOP MUST BE goto-based, NOT `for(;;){...break;}`. With for/break gcc schedules
 *     `la s0,D_800AF630` into the load-delay slot AFTER func_8001B85C (a 2-insn macro
 *     that doesn't fit -> +2 instructions). The explicit `goto L3E4` form keeps s0
 *     live-in to the first block, so gcc materializes `la s0` in the PROLOGUE
 *     (lui s0 / addiu s0 between `sw s0` and `sw ra`), exactly like the target.
 */
extern s32 D_80114E98;
extern s32 D_80114E9C;
extern u16 D_800B99F6;
extern u8 D_800AF630[];
extern void (*D_800D3488[])(void);
extern void func_8001B85C(void);
extern void func_8001AF34(void);
extern void func_80015310(void);
extern void func_80011B7C(s32 arg0);
extern void VSync(s32 arg0);

void func_800CF3B8(void) {
    register u8 *p = D_800AF630;
    D_80114E98 = 0;
    D_80114E9C = 0;
    func_8001B85C();
L3E4:
    if (D_80114E98 != 0) goto L458;
    (*(void (**)(void))((char *)D_800D3488 + (D_800B99F6 << 2)))();
    if (D_80114E98 != 0) goto L458;
    VSync(*(s32 *)(p + 0xA3E8));
    func_8001AF34();
    goto L3E4;
L458:
    func_80015310();
    func_80011B7C(7);
}

extern s32 D_80114E78;
extern u8 D_800AF218;
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern void func_80011C10(void);

void func_800CF47C(void) {
    if (D_80114E78 != 0) {
        if (func_8001ABBC(0, 0, &D_800AF218, 0, 0) == 0) {
            return;
        }
        D_80114E78 = 0;
    }
    func_80011C10();
}

extern u16 D_800B99FC;
extern void (*D_800D3490[])(void);

void func_800CF4D4(void) {
    D_800D3490[D_800B99FC]();
}

extern u8 D_800B9A11;
extern s32 D_80127084;
extern s16 D_801152BA;
extern void func_80014928(void);
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_8001B384(void);
extern void func_80011CFC(void);
extern void func_80011D54(s32 arg0);

void func_800CF510(void) {
    func_80014928();
    D_800B9A11 = 1;
    func_8001C0C8();
    func_80015310();
    func_8001B384();
    D_801152BA = 0;
    if (D_80127084 != 0) {
        func_80011CFC();
    } else {
        func_80011D54(3);
    }
}

/* func_800CF584: twin of the ALREADY-MATCHED func_800CF5D4 (resident.c:~178), same
 * shape `if (g != 0) { m = <byte>; if (m == 0 || f(m) != 0) func_80011CFC(); }`.
 *
 *   lw   v0, D_80127084 ; beqz v0 -> exit          => if (D_80127084 != 0) {
 *   lbu  a0, D_80078EC1 ;                              m = D_80078EC1;   (value -> a0)
 *   beqz a0 -> .L800CF5BC (the call)               => if (m == 0 ||
 *   jal  func_800D02D0  ; (nop delay slot keeps a0)    func_800D02D0(m) != 0)
 *   beqz v0 -> exit                                       func_80011CFC();
 *   .L800CF5BC: jal func_80011CFC
 *
 * KEY FIX vs prior draft: func_800D02D0 TAKES the byte as its argument (its body does
 * `addiu a0,a0,-1` then a jump-table on it — see func_800D02D0.s). The byte therefore
 * lives in $a0 (not $v0), exactly like func_800CF5D4's ((s32 (*)())func_800D0488)(m). It returns s32
 * (the plain `beqz v0` needs a wider-than-bool return). D_80078EC1 is u8 (lbu, no mask).
 */
extern s32 D_80127084;
extern u8 D_80078EC1;
extern s32 func_800D02D0(s32 arg0);
extern void func_80011CFC(void);

void func_800CF584(void) {
    s32 m;

    if (D_80127084 != 0) {
        m = D_80078EC1;
        if (m == 0 || func_800D02D0(m) != 0) {
            func_80011CFC();
        }
    }
}

/* func_800CF5D4
 * BUG IN PRIOR DRAFT: ((s32 (*)())func_800D0488)() was called with NO argument. The asm keeps
 * the masked value (D_80078EC0 & 0x7F) in $a0 across the `beqz a0` test and the
 * `jal func_800D0488` (nop delay slot leaves a0 untouched), so it IS the argument.
 * func_800D0488 is `s32 ((s32 (*)())func_800D0488)(s32)` (it does `addiu a0,a0,-1` — see the
 * already-matched callers func_800CEF04 / func_800CEF34).
 *
 * asm trace:
 *   lw v0, D_80127084 ; beqz v0 -> exit            => if (D_80127084 != 0) {
 *   lbu v0, D_80078EC0 ; andi a0, v0, 0x7F
 *   beqz a0 -> .L800CF610 (the call)               =>   if (m == 0 ||
 *   jal func_800D0488 ; beqz v0 -> exit            =>       ((s32 (*)())func_800D0488)(m) != 0)
 *   .L800CF610: jal func_80011CFC                  =>     func_80011CFC();   }
 */
extern s32 D_80127084;
extern u8 D_80078EC0;
extern s32 func_800D0488(s32 arg0);
extern void func_80011CFC(void);

void func_800CF5D4(void) {
    s32 m;

    if (D_80127084 != 0) {
        m = D_80078EC0 & 0x7F;
        if (m == 0 || ((s32 (*)())func_800D0488)(m) != 0) {
            func_80011CFC();
        }
    }
}

// MATCHED. Two keys beyond the prior draft:
//  (1) currentLocationId is hoisted into $s0 (callee-saved, survives all jal) -> model via
//      a pointer `cli = &currentLocationId` and deref through it (an extern + direct global
//      access emitted per-site `lui at; lh` and blew the instruction count to 65).
//  (2) Block LAYOUT: the func_80011CFC tail (.L67C) must sit RIGHT AFTER the D_80127084!=0
//      arm (first arm falls THROUGH into it; func_800CFD68-success branches BACK to it). A
//      shared `goto tail_CFC` at the END made gcc place .L68C after the first arm instead,
//      costing one extra `j`. The fix: put the `tail_CFC:` label + func_80011CFC()+return
//      INSIDE the first arm (so it is that arm's fallthrough), and have the success path
//      `goto tail_CFC` backward. func_80011D54 IS a genuinely shared tail (arg 5 vs 6
//      distributed by predecessors) -> keep it as the trailing `tail_D54:` shared label.
//  func_800CFD68(s16): arg sign-extended (sll/sra); returns the nonzero-tested value (s32).
extern s16 currentLocationId;
extern s32 D_80127084;
extern s32 D_80114E94;
extern s32 D_80114E98;
extern s32 func_800CFC5C(s32 arg0);
extern s32 func_800CFBF8(void);
extern s32 func_800CFD68(s32 arg0);
extern void func_80011CFC(void);
extern void func_80011D54(s32 arg0);

void func_800CF628(void) {
    s16 *cli = &currentLocationId;
    s32 arg;

    if (func_800CFC5C(*cli) != 0) {
        if (D_80127084 != 0) {
            D_80114E94 = *cli;
            *cli = func_800CFBF8();
        tail_CFC:
            func_80011CFC();
            return;
        }
        D_80114E94 = *cli;
        if (func_800CFD68(*cli = func_800CFBF8()) != 0) {
            goto tail_CFC;
        }
        *cli = D_80114E94;
        arg = 5;
        goto tail_D54;
    }
    D_80127084 = 0;
    if (func_800CFD68(*cli) != 0) {
        arg = 6;
        goto tail_D54;
    }
    D_80114E98 = 1;
    return;
tail_D54:
    func_80011D54(arg);
}

extern s32 D_80114E94;
extern s16 currentLocationId;
extern void func_800191A8(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);
extern void func_80011CFC(void);

void func_800CF714(void) {
    func_800191A8();
    if (func_800CFE60() != 0) {
        func_800CFDA4();
        currentLocationId = D_80114E94;
        func_80011CFC();
    }
}

extern s32 func_80128218(void);
extern s32 func_800D0214(s32);
extern s32 D_80127084;
extern s32 D_80114E98;

void func_800CF764(void) {
    if (func_800D0214(func_80128218())) {
        D_80127084 = 0;
        D_80114E98 = 1;
    }
}

extern s32 D_80127084;
extern s32 D_80114E98;
extern void func_800191A8(void);
extern s32 func_8001AF04(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);

void func_800CF7A4(void) {
    func_800191A8();
    if (func_8001AF04() == 2) {
        return;
    }
    if (func_800CFE60() == 0) {
        return;
    }
    func_800CFDA4();
    D_80127084 = 0;
    D_80114E98 = 1;
}

void func_800CF804(void) {
    D_80127084 = 1;
}

void func_800CF818(void) {
    D_80114E78 = 1;
}

extern s16 D_800B9A0E;
void func_800CF82C(void) {
    D_800B9A0E = 1;
}

void func_800CF840(void) {
    D_800B9A0E = 2;
}

extern u8 D_800AE6BF;
s32 func_800CF854(void) {
    return D_800AE6BF != 0;
}

extern s16 currentLocationId;
extern u16 D_80126B58;
extern s32 func_800CF8B4(void);

s32 func_800CF864(void) {
    if (currentLocationId == 0x3069) {
        return 1;
    }
    if (D_80126B58 == 0x1A) {
        return 1;
    }
    return func_800CF8B4();
}

extern u16 D_800B99F0;

s32 func_800CF8B4(void) {
    return D_800B99F0 == 9;
}

extern u16 D_800B99F0;

s32 func_800CF8CC(void) {
    return D_800B99F0 == 0xA;
}

// func_800CF8E4 — gate dispatch on two location-class checks then load.
//
// asm trace:
//   jal func_800D1714 / sw s0,0x10(sp)               => id = func_800D1714();
//   addu s0, v0, zero                                => s0 = id
//   jal func_800CFC5C(id)                            => r = func_800CFC5C(id)
//   bnez v0, .end                                    => if (r != 0) return;
//   lh a0, currentLocationId                         => (s16, sign-extended)
//   jal func_800CFC5C(currentLocationId)             => r = func_800CFC5C(currentLocationId)
//   bnez v0, .end                                    => if (r != 0) return;
//   jal func_800CFD68(id)                            => r = func_800CFD68(id)
//   beqz v0, .end                                    => if (r == 0) return;
//   jal func_800CFDE8(id)                            => func_800CFDE8(id)
//
// Notes:
//  - func_800D1714 returns u16 (reads D_80078E50 via lhu) -> `addu s0,v0,zero` (no andi).
//  - func_800CFC5C returns s32 (1..4 or sltiu result) -> tested directly with bnez (no mask).
//  - func_800CFD68 is `void` in resident.c, but the asm TESTS its v0 here (it tail-calls
//    func_800191D4, whose result lands in v0). To emit the `beqz v0` it MUST be declared
//    returning a value (s32) in this self-contained TU.
//  - currentLocationId is s16 (lh).
extern s32 func_800D1714(void);
extern s32 func_800CFC5C(s32 arg0);
extern s32 func_800CFD68(s32 arg0);
extern void func_800CFDE8(s32 arg0);
extern s16 currentLocationId;

void func_800CF8E4(void) {
    s32 id = func_800D1714();

    if (func_800CFC5C(id) != 0) {
        return;
    }
    if (func_800CFC5C(currentLocationId) != 0) {
        return;
    }
    if (func_800CFD68(id) != 0) {
        func_800CFDE8(id);
    }
}

extern u8 D_800AE890;
extern void *D_80072C74;
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80011A3C(void);

void func_800CF94C(void) {
    if (CdReadRequest(&D_800AE890, D_80072C74, 0, 0) != 0) {
        func_80011A3C();
    }
}

// func_800CF990: recovered despite the D_800B9A00 type clash. The already-matched
// func_800CEE84 reads D_800B9A00 with `lh` (s16), but THIS function needs `lhu` (u16).
// Keeping the global s16 (for CEE84) and reading it here via `*(u16*)&D_800B9A00`
// forces the lhu at this site only — byte-correct for both. (The store stays `sh`.)
// KEY FIX vs both prior drafts (which differed ONLY in the func_800167F0 handling and
// BOTH failed): the case-0 third argument. The asm is
//     lh   a2, D_800D3408[D_80114E74]     ; s16 table element
//     sll  a2, a2, 3                       ; * 8  (struct stride, NOT a hand << 3)
//     addu a2, a2, &cdFileLocTable
// i.e. `&cdFileLocTable[idx]` where cdFileLocTable is the PROVEN 8-byte CdFileLoc[]
// struct array (resident.c:351-357, used byte-exact in func_800CFDE8 line 363:
// `func_8001ABBC(2, 0, (u8 *)&cdFileLocTable[idx], 0, 0)`). The prior drafts hand-rolled
// `(u8*)cdFileLocTable + (D_800D3408[D_80114E74] << 3)` — the explicit `<< 3` on the
// freshly-`lh`-loaded s16 schedules the shift/add into different registers than the
// array-index lowering does. Use the proven struct-stride index form + the u8* 3rd param.
//
// Types: D_800B99F6 u16 (lhu, resident.c:21). D_800B9A00 read here with `lhu` then
// incremented/stored/`(s16)`-extended — model as u16 to get the lhu (its matched decl is
// s16 but that only affects the combined TU; the standalone byte form needs u16 -> lhu).
// D_800AF7B8 u16 (lhu). D_800D3408 s16[] (.short, lh). D_80114E74 s16 (lh).
// func_800167F0 returns u16 (proven twins func_800D319C/2EE8) -> the `!= 0` is just
// `andi v0,0xffff; beqz` with NO explicit cast.
//
// case 0 (CF9D8): func_8001C0C8(); func_80015310();
//   if (func_8001ABBC(0,0,(u8*)&cdFileLocTable[D_800D3408[D_80114E74]],0,0) != 0)
//     { func_800167B8(0); func_80011C10(); }
// case 1 (CFA44): func_800CFAD0(); if (func_800167F0(0) != 0) func_80011C10();
// case 2 (CFA70): func_800CFAD0(); v = D_800B9A00 + 1; D_800B9A00 = v;
//   if ((s16)v >= 0x5B && D_800AF7B8 != 0) func_80011B7C(6);
//     (slti (s16)v,0x5B; bnez->end | lhu D_800AF7B8; beqz->end | a0=6; jal 11B7C).

typedef struct {
    s32 word0;
    s32 word4;
} CdFileLoc;

extern u16 D_800B99F6;
extern s16 D_80114E74;
extern s16 D_800D3408[];
extern CdFileLoc cdFileLocTable[];
extern s16 D_800B9A00;
extern u16 D_800AF7B8;

extern void func_8001C0C8(void);
extern void func_80015310(void);
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern void func_800167B8(s32 arg0);
extern void func_80011C10(void);
extern void func_800CFAD0(void);
extern u16 func_800167F0(s32 arg0);
extern void func_80011B7C(s32 arg0);

void func_800CF990(void) {
    switch (D_800B99F6) {
    case 0:
        func_8001C0C8();
        func_80015310();
        if (func_8001ABBC(0, 0, (u8 *)&cdFileLocTable[D_800D3408[D_80114E74]], 0, 0) != 0) {
            func_800167B8(0);
            func_80011C10();
        }
        break;
    case 1:
        func_800CFAD0();
        if (func_800167F0(0) != 0) {
            func_80011C10();
        }
        break;
    case 2: {
        s32 v;
        func_800CFAD0();
        v = *(u16 *)&D_800B9A00 + 1;
        D_800B9A00 = v;
        if ((s16)v >= 0x5B) {
            if (D_800AF7B8 != 0) {
                func_80011B7C(6);
            }
        }
        break;
    }
    }
}

typedef struct { u32 addr : 24; u32 len : 8; } P_TAG_800CFAD0;
typedef struct { u8 b0, b1, b2, b3; } BYTES_800CFAD0;

void func_800CFAD0(void)
{
    extern u32 D_80114E7C;
    extern u32 D_80114E80;
    extern u8  D_80114E84;
    extern u8  D_80114E85;
    extern u8  D_80114E86;
    extern u8  D_80114E87;
    extern s16 D_80114E88;
    extern s16 D_80114E8A;
    extern u8  D_80114E8C;
    extern u8  D_80114E8D;
    extern s16 D_80114E8E;
    extern s16 D_80114E90;
    extern s16 D_80114E92;
    extern u8  D_800AA60C[];
    extern u16 D_800B9A02;

    u32 *ot;

    ((BYTES_800CFAD0 *)&D_80114E7C)->b3 = 5;
    D_80114E80 = 0xE1000085;
    D_80114E87 = 0x64;
    D_80114E84 = D_80114E85 = D_80114E86 = 0x80;
    D_80114E88 = -0x80;
    D_80114E8A = -0x48;
    D_80114E8E = 0x7800;
    D_80114E90 = 0x100;
    D_80114E92 = 0x90;
    D_80114E8C = 0;
    D_80114E8D = 0;

    ot = (u32 *)&D_800AA60C[D_800B9A02 << 14];

    ((P_TAG_800CFAD0 *)&D_80114E7C)->addr = *(u32 *)ot;
    *(u32 *)ot = (*(u32 *)ot & 0xFF000000u) | ((u32)&D_80114E7C & 0x00FFFFFFu);
}


extern s16 D_80114E70;

void func_800CFBBC(void) {
    D_80114E70 = 0;
}

/* func_800CFBCC — trivial two-halfword setter.
 *   addiu v0,zero,0x1 ; sh v0,D_80114E70 ; sh a0,D_80114E74 ; jr ra
 *
 * D_80114E70 is the SAME global already matched as `u16` in src/resident/resident.c
 * (func_800CFBBC sets D_80114E70 = 0). Both stores are `sh` (halfword) so the global /
 * arg signedness does NOT change the emitted store — width is fixed at 16. Kept u16 to
 * mirror the proven type. Stores are in source order (E70 first, E74 second), with the
 * `1` materialised once into v0.
 *
 * Self-contained per drafts3 rules: NO #include; typedef inlined.
 */
extern s16 D_80114E70;
extern s16 D_80114E74;

void func_800CFBCC(u16 arg0) {
    D_80114E70 = 1;
    D_80114E74 = arg0;
}

/* func_800CFBE8
 *   lh   v0, %lo(D_80114E70)($v0)     -> signed-halfword load
 *   jr   ra
 * A bare getter: load D_80114E70 sign-extended (lh) and return it.
 *
 * The matched neighbor func_800CFBBC writes `D_80114E70 = 0` declaring it u16,
 * but THIS reader loads it with `lh` (signed). Per-TU externs are independent,
 * so here it is declared s16 to force the signed `lh` (a u16 read emits lhu).
 * Return type s16 (== the load width/sign); `lh` + plain `jr ra` is exactly
 * `return (s16-global)`.
 */
extern s16 D_80114E70;

s32 func_800CFBE8(void) {
    return D_80114E70;
}

/* func_800CFBF8 — dispatch on func_800CFC5C(currentLocationId).
 *
 * The asm is a LINEAR compare chain (beq 1; bne 2; bne 3; beq 4), NOT a jr
 * through a jump table — so this is an if/else-if chain, not a `switch`
 * (a `switch` over the dense set {1,2,3,4} makes gcc-2.7.2 emit a jtbl;
 * the prior `switch` draft failed for exactly this reason).
 *
 * result==1 -> 0x1010   (asm: beq a0,1 -> the shared 0x1010 block)
 * result==2 -> 0x1052
 * result==3 -> 0x1077
 * result==4 -> 0x1094
 * default   -> 0x1010   (gcc cross-jumps this into the case-1 block: both reach
 *                        L800CFC48 / v0=0x1010, one by branch, one by fall-through)
 *
 * currentLocationId is s16 (matched in resident.c); the `lh` sign-extends it
 * into the s32 argument.  func_800CFC5C returns s32 (compared against 1..4).
 * All returns are plain positive constants -> s32 return type.
 */
extern s16 currentLocationId;
extern s32 func_800CFC5C(s32);

s32 func_800CFBF8(void) {
    s32 r = func_800CFC5C(currentLocationId);

    if (r == 1) {
        return 0x1010;
    }
    if (r == 2) {
        return 0x1052;
    }
    if (r == 3) {
        return 0x1077;
    }
    if (r == 4) {
        return 0x1094;
    }
    return 0x1010;
}

/* func_800CFC5C — MATCH (67 ins)
 * Maps four sparse groups of location IDs to 1..4, else 0. The match form is a run of
 * SEPARATE `if (arg0 == K) return N;` statements — NOT `||` (gcc-2.7.2 -O2 range-merges
 * adjacent constants  a0==K||a0==K+1  ->  (a0-K)<2u  via addiu/sltiu) and NOT `switch`
 * (gcc builds a slti binary-search decision tree). Each standalone `if` emits an
 * independent  addiu v0,zero,K ; beq a0,v0  with the constant in the prior branch's delay
 * slot. The trailing 0x209D folds to  xori v0,a0,0x209D ; sltiu v0,v0,1 ; sll v0,v0,2
 * because the group value 4 == (1<<2) and the default path returns 0. Returns s32.
 */
s32 func_800CFC5C(s32 arg0) {
    if (arg0 == 0x2013) return 1;
    if (arg0 == 0x2015) return 1;
    if (arg0 == 0x2016) return 1;
    if (arg0 == 0x2017) return 1;
    if (arg0 == 0x2018) return 1;
    if (arg0 == 0x2019) return 1;
    if (arg0 == 0x201A) return 1;
    if (arg0 == 0x2055) return 2;
    if (arg0 == 0x2056) return 2;
    if (arg0 == 0x2057) return 2;
    if (arg0 == 0x2058) return 2;
    if (arg0 == 0x2059) return 2;
    if (arg0 == 0x205A) return 2;
    if (arg0 == 0x205B) return 2;
    if (arg0 == 0x207A) return 3;
    if (arg0 == 0x207B) return 3;
    if (arg0 == 0x207C) return 3;
    if (arg0 == 0x207D) return 3;
    if (arg0 == 0x207E) return 3;
    if (arg0 == 0x207F) return 3;
    if (arg0 == 0x2080) return 3;
    if (arg0 == 0x2097) return 4;
    if (arg0 == 0x2098) return 4;
    if (arg0 == 0x2099) return 4;
    if (arg0 == 0x209A) return 4;
    if (arg0 == 0x209B) return 4;
    if (arg0 == 0x209C) return 4;
    if (arg0 == 0x209D) return 4;
    return 0;
}

extern s32 D_800D34AC[];
extern void func_800191D4(s32 arg0);

s32 func_800CFD68(s32 arg0) {
    func_800191D4(D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF);
}

extern s16 currentLocationId;
extern s32 D_800D34AC[];
extern void func_800191BC(s32 arg0);

void func_800CFDA4(void) {
    func_800191BC(D_800D34AC[currentLocationId & 0xFFFF0FFF] & 0xFFF);
}

/* func_800CFDE8
 * The index expression `D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF` is the proven idiom
 * already byte-matched in func_800CFD68 / func_800CFDA4 (D_800D34AC is `s32[]`).
 * The `& 0xFFF` result is compared `>= 0` (asm keeps a redundant `bltz` — gcc-2.7.2
 * -O2 does not prove the masked value non-negative), then an 8-byte record of
 * cdFileLocTable is checked and its address passed.
 *
 * BUG IN PRIOR DRAFT: func_8001ABBC's 3rd parameter was typed `CdFileLoc *`; the
 * proven convention (func_800CF47C, func_800CF3B8) declares it `u8 *`. Match that and
 * pass the record address as a u8*. Everything else (struct stride 8 -> sll 3, word0
 * != 0 check, arg vector 2,0,&rec,0,0 with the 5th on the stack) was already correct.
 *
 * asm trace:
 *   and a0, a0, 0xFFFF0FFF ; sll a0,2 ; lw v0, D_800D34AC[a0]
 *   andi v0, 0xFFF ; bltz v0 -> exit                 => if (idx >= 0 &&
 *   sll v1, v0, 3 ; lw v0, cdFileLocTable[idx].word0
 *   beqz v0 -> exit                                  =>     rec->word0 != 0) {
 *   a0=2 ; sw zero,0x10(sp) ; a1=0 ; a2=&rec ; a3=0
 *   jal func_8001ABBC                                =>   func_8001ABBC(2,0,&rec,0,0); }
 */
extern s32 D_800D34AC[];
extern CdFileLoc cdFileLocTable[];
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);

void func_800CFDE8(s32 arg0) {
    s32 idx = D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF;
    if (idx >= 0 && cdFileLocTable[idx].word0 != 0) {
        func_8001ABBC(2, 0, (u8 *)&cdFileLocTable[idx], 0, 0);
    }
}



s32 func_800CFE60(void) {
    extern s16 currentLocationId;
    extern s32 D_800D34AC[];
    extern s16 D_800D34AE[];
    extern u8 D_800AF630[];
    extern CdFileLoc cdFileLocTable[];
    extern void *D_80072C74;
    extern s32 D_800C7C60;
    extern s32 *D_800C7C64;
    extern s32 D_800A2E20;

    extern s32 func_8002F648(void);
    extern void func_8002F620(void);
    extern s32 func_80029504(void);
    extern s32 func_80029178(s32);
    extern s32 func_8002F658(void);
    extern void func_800D00E4();
    extern s32 CdReadRequest(void *, void *, s32, s32);

    register u8 *base __asm__("$20");
    register s32 mode __asm__("$19");
    s32 file;
    s32 val;
    s32 st;
    s32 cnt;
    s32 res;
    s32 *p;

    base = D_800AF630;

    file = D_800D34AC[currentLocationId & 0xFFFF0FFF] & 0xFFF;
    val = D_800D34AE[(currentLocationId & 0xFFFF0FFF) * 2];

    st = func_8002F648();
    mode = -1;
    if (st != ((*(u32 *)((u8 *)D_800D34AC + ((currentLocationId & 0xFFFF0FFF) << 2)) >> 12) & 0xF)) {
        mode = 0;
        if (st != 0) {
            func_8002F620();
        }
    }

    cnt = func_80029504();

    if (*(s16 *)(base + 0xA3D8) == 0x300B && *(s16 *)(base + 0xA3DE) != 0) {
        val = 8;
        file = 0x8A;
    }
    if (*(s16 *)(base + 0xA3D8) == 0x3001 && cnt < 5) {
        file = 0x37;
    }
    if (*(s16 *)(base + 0xA3D8) == 0x304E && (func_80029178(0x17) & 0xFF) != 0) {
        file = 0x129;
        val = 0x2F;
    }
    if (*(s16 *)(base + 0xA3D8) == 0x1077 && cnt >= 0x2A8) {
        file = 0x151;
        val = 0x34;
    }
    if (*(s16 *)(base + 0xA3D8) == 0x3021 && (func_80029178(0xB9) & 0xFF) != 0) {
        file = 0xC1;
        val = 0x41;
    }

    if (func_8002F658() != val || mode >= 0) {
        s32 *q = &D_800C7C60;
        __asm__("" : "=r"(q) : "0"(q));
        p = q;
        *p = val;
        D_800C7C64 = &D_800A2E20;
    } else {
        p = 0;
    }

    if (file >= 0 && cdFileLocTable[file].word0 != 0) {
        res = CdReadRequest(&cdFileLocTable[file], D_80072C74, mode, p);
    } else {
        res = 1;
    }

    if (mode == 0 && (res & 1)) {
        func_800D00E4((((u32)D_800D34AC[*(s16 *)(base + 0xA3D8) & 0xFFFF0FFF]) >> 12) & 0xF);
    }
    return res;
}


/* func_800D00E4: left as INCLUDE_ASM — genuine structural mismatch. The matched
 * binary references an EXTERNAL jump table `jtbl_80113ED8` (defined in
 * asm/resident/data/tail.data.s) via a HI16/LO16 relocation. A plain C `switch`
 * makes gcc synthesize its OWN anonymous `.rodata` jump table (R_MIPS_HI16 .rodata),
 * which diverges from the named-symbol relocation and the data layout, breaking the
 * full-binary SHA. Recovering it needs the external jtbl wired in, out of scope here.
 */
#if 0
/* func_800D00E4 — dense jump-table switch on (arg0 - 1), 15 cases [0..14].
 *
 *   addiu a0,a0,-1                       ; n = arg0 - 1
 *   sltiu v0,a0,0xF ; beqz v0,.L0204     ; if ((u32)n >= 15) -> epilogue (void)
 *   sll a0,2 ; lw v0,jtbl_80113ED8[n] ; jr v0
 *   each case: la a0,&D_xxx ; j .L01FC
 *   .L01FC: jal func_8002F5C8(a0)
 *   .L0204: epilogue (void return)
 *
 * jtbl_80113ED8 (asm/resident/data/tail.data.s:72558) maps case k -> 0x800D0114+k*0x10,
 * i.e. case 0->D_800CA23C, 1->D_800C8448, ... 14->D_800C9140, in the order below.
 * Every case only selects a pointer and breaks; the single call sits AFTER the switch.
 *
 * VOID function: the out-of-range path needs no `move v0,zero` (B3 only bites
 * value-returning fns). `default: return;` maps straight onto `beqz v0,.L0204`.
 * func_8002F5C8 takes a u8* (each D_xxx is a data/string address taken via la).
 */
extern u8 D_800CA23C;
extern u8 D_800C8448;
extern u8 D_800CA84C;
extern u8 D_800CA3E4;
extern u8 D_800CA344;
extern u8 D_800C83AC;
extern u8 D_800C9A30;
extern u8 D_800C9158;
extern u8 D_800C9310;
extern u8 D_800C83A0;
extern u8 D_800C8058;
extern u8 D_800CADE8;
extern u8 D_800C8500;
extern u8 D_800C8514;
extern u8 D_800C9140;
extern void func_8002F5C8(u8 *arg0);

void func_800D00E4(s32 arg0) {
    u8 *p;
    switch (arg0 - 1) {
    case 0:  p = &D_800CA23C; break;
    case 1:  p = &D_800C8448; break;
    case 2:  p = &D_800CA84C; break;
    case 3:  p = &D_800CA3E4; break;
    case 4:  p = &D_800CA344; break;
    case 5:  p = &D_800C83AC; break;
    case 6:  p = &D_800C9A30; break;
    case 7:  p = &D_800C9158; break;
    case 8:  p = &D_800C9310; break;
    case 9:  p = &D_800C83A0; break;
    case 10: p = &D_800C8058; break;
    case 11: p = &D_800CADE8; break;
    case 12: p = &D_800C8500; break;
    case 13: p = &D_800C8514; break;
    case 14: p = &D_800C9140; break;
    default: return;
    }
    func_8002F5C8(p);
}
#endif
INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D00E4);



s32 func_800D0214(s32 arg0) {
    extern s16 currentLocationId;
    extern s32 D_800C7C60;
    extern s32 *D_800C7C64;
    extern s32 D_800A2E20;
    extern s32 D_800D34AC[];
    extern s16 D_800D34AE[];
    extern CdFileLoc cdFileLocTable[];
    extern s32 CdReadRequest(void *, void *, s32, s32);

    register s32 mask __asm__("$3") = ~0xF000;
    s32 idx = currentLocationId & mask;
    s32 raw = D_800D34AC[idx];
    s32 val = D_800D34AE[idx * 2];
    s32 *p = &D_800C7C60;
    s32 id;

    __asm__("" ::: "memory");
    D_800C7C64 = &D_800A2E20;
    *p = val;

    id = raw & 0xFFF;
    if (id >= 0 && cdFileLocTable[id].word0 != 0) {
        return CdReadRequest(&cdFileLocTable[id], arg0, 0, p);
    }
    return 1;
}


extern s32 (*D_800D375C)(s32);

void func_800D02C0(s32 arg0) {
    D_800D375C = (s32 (*)(s32))arg0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D02D0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0488);

// ANALYSIS: no prior draft existed. Trace:
//   a0 = currentLocationId (s16, lh -> signed); r = func_800D05E8(a0)
//   beqz v0 -> .L800D05C4 ; (delay) a0 = 1     => fall-through is r != 0
//     r != 0:  sw zero,0x10(sp)(5th arg); a1=r; a2=0; a3=0; a0=1
//              result = func_8001ABBC(1, r, 0, 0, 0)
//     r == 0:  result = 1
//   beqz v0 -> .L800D05D8  (result==0 skips the store)
//     D_8012704C = 0
//
// Branch polarity (cookbook T4): the r!=0 arm is the FALL-THROUGH, so write
//   if (r != 0) { result = call; } else { result = 1; }
// The `a0 = 1` (func_8001ABBC's 1st arg) is hoisted into the beqz delay slot by
// gcc -- emitting it as a plain constant arg is correct.
// func_8001ABBC signature copied from the already-matched func_800CF47C / func_800CFDE8
// in resident.c: s32 func_8001ABBC(s32, s32, u8 *, s32, s32). r passed as arg1 (s32).
// currentLocationId is s16 (resident.c). func_800D05E8 result reused both as the
// `beqz` test and as arg1 -> declare it s32-returning, arg s32.
extern s16 currentLocationId;
extern s32 func_800D05E8(s32 arg0);
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern s32 D_8012704C;

void func_800D0588(void) {
    s32 r = func_800D05E8(currentLocationId);
    s32 result;

    if (r != 0) {
        result = func_8001ABBC(1, r, 0, 0, 0);
    } else {
        result = 1;
    }
    if (result != 0) {
        D_8012704C = 0;
    }
}

/* func_800D05E8
 *   addiu sp,-0x18 ; sw ra,0x14 ; jal func_80029504 ; sw s0,0x10 (delay)
 *   lw v1, D_800D375C ; beqz v1 -> .L0618 ; s0 = 0 (delay)
 *   jalr v1 ; a0 = v0 (delay)  ; s0 = v0
 *   .L0618: v0 = s0 ; epilogue ; return s0
 * func_80029504() is called first; D_800D375C is an optional s32(*)(s32) hook fed
 * that result. The return value lives in callee-saved s0 (frame saves ra + s0).
 * Discriminating C shape (vs the count-16 near miss): declare `ret = 0;` BEFORE
 * `r = func_80029504();` and gate with `if (D_800D375C)` (implicit nonzero test) so
 * gcc-2.7.2 -O2 allocates `ret` to s0 and emits the s0 save/restore (matches D0CE0).
 */
extern s32 func_80029504(void);
extern s32 (*D_800D375C)(s32);

s32 func_800D05E8(s32 arg0) {
    s32 ret = 0;
    s32 r = func_80029504();
    if (D_800D375C) {
        ret = D_800D375C(r);
    }
    return ret;
}

extern void func_800D065C(void);
extern s32 D_8011529C;

void func_800D0630(void) {
    func_800D065C();
    D_8011529C = -1;
}

extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_8012704C;
extern s32 D_801201F0;
extern s32 D_80127050;

void func_800D065C(void) {
    D_801151F8 = 0;
    D_80126AE8 = 0;
    D_80127500 = 0;
    D_8012704C = 0;
    D_801201F0 = 0;
    D_80127050 = 0;
}

extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_8012704C;
extern s32 D_801201F0;
extern s32 D_80127050;

void func_800D0694(void) {
    D_801151F8 = 0;
    D_80126AE8 = 0;
    D_80127500 = 0;
    D_8012704C = 0;
    D_801201F0 = 0;
    D_80127050 = 0;
}

extern s32 D_801151F8;
extern s32 D_80127500;

void func_800D06CC(void) {
    D_801151F8 = 3;
    D_80127500 = 3;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D06E8);

extern s32 resLoad_lastId;
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_800D0C48(u16 arg0) {
    func_8002D4C8(1, arg0);
    resLoad_lastId = 0;
}

// func_800D0C74: mirror of the matched func_800D0C48 idiom.
//   andi a1, a0, 0xFFFF      -> caller arg0 is u16, zero-extended into a1
//   jal func_8002D4C8 (delay: addiu a0,zero,1)  -> func_8002D4C8(1, arg0)
//   jal func_8001B34C (delay: nop)              -> no args
//   return (void). The frame (sw ra) exists because of the calls.
// FIX vs prior draft: declare func_8002D4C8 as (s32,s32) and make the CALLER's
// arg0 the u16 (the andi comes from truncating arg0 at the u16 param of THIS fn),
// exactly like the already-matched func_800D0C48.
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8001B34C(void);

void func_800D0C74(u16 arg0) {
    func_8002D4C8(1, arg0);
    func_8001B34C();
}

// ANALYSIS: sibling of the matched func_800D0C48 (resident.c:378). The prior draft
// FAILED because it called func_8002D4C8(1) with ONE arg, but the asm shows
//   andi a1, a0, 0xFFFF      ; a1 = (u16)arg0  -> the 2nd argument
//   jal  func_8002D4C8       ; a0 = 1 (delay slot)
// i.e. func_8002D4C8(1, arg0). func_8002D4C8 is declared as (s32,s32) in resident.c.
// Passing the u16 param produces the andi a1,a0,0xFFFF zero-extension automatically.
// Then resLoad_lastId=0; D_801151F8=3; D_80127500=3 (3 materialized once in v0).

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern s32 resLoad_lastId;
extern s32 D_801151F8;
extern s32 D_80127500;

void func_800D0CA0(u16 arg0) {
    func_8002D4C8(1, arg0);
    resLoad_lastId = 0;
    D_801151F8 = 3;
    D_80127500 = 3;
}

// func_800D0CE0 — optional hook, gate, then clear a block of globals + record id.
//
// asm trace:
//   jal func_80029504 / sw s0,0x10(sp)               => r = func_80029504();
//   lw v1, D_800D375C                                => fp = D_800D375C
//   beqz v1, .L0D10 / addu s0,zero,zero (delay: s0=0)=> s0 = 0; if (fp != 0) {
//   jalr v1 / addu a0,v0,zero (delay: a0=r)          =>   s0 = (*fp)(r);
//   addu s0, v0, zero                                => }
// .L0D10:
//   jal func_8001AAA0(s0)                            => t = func_8001AAA0(s0)
//   bnez v0, .L0D28 / addiu v0,zero,1 (delay: v0=1)  => if (t != 0) goto success(v0=1)
//   j .L0D68 / addu v0,zero,zero (delay: v0=0)       => else return 0;
// .L0D28 (success, v0 preset to 1):
//   sw zero, D_8012704C                              \
//   sw zero, D_801151F8                               |
//   sw zero, D_80126AE8                               |  8 stores in this exact source
//   sw zero, D_80127500                               |  order; D_8012704C is written
//   sw zero, D_8012704C   (DUPLICATE)                 |  TWICE (a redundant store the
//   sw zero, D_801201F0                               |  2.7.2 -O2 keeps — its dead-store
//   sw zero, D_80127050                               |  elimination doesn't disambiguate
//   sw s0,   resLoad_lastId                          /   distinct global memory).
//   -> falls through, returns v0 = 1
//
// BRANCH POLARITY: success is the bnez TARGET with v0=1 in the delay slot and the
// return-0 is the fall-through (v0=0 in the j delay). That is exactly:
//     if (func_8001AAA0(s0) == 0) return 0;  <stores>  return 1;
// (success/main return written LAST so it is the fall-through into the epilogue.)
//
// D_800D375C is an s32(*)(s32) function pointer here (jalr after the lw); its arg is
// func_80029504()'s return.  All cleared globals are s32 (proven in func_800D065C).
extern s32 func_80029504(void);
extern s32 (*D_800D375C)(s32);
extern s32 func_8001AAA0(s32);
extern s32 D_8012704C;
extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_801201F0;
extern s32 D_80127050;
extern s32 resLoad_lastId;

s32 func_800D0CE0(void) {
    s32 s0;
    s32 r;

    r = func_80029504();
    s0 = 0;
    if (D_800D375C != 0) {
        s0 = D_800D375C(r);
    }
    if (func_8001AAA0(s0)) {
        D_8012704C = 0;
        D_801151F8 = 0;
        D_80126AE8 = 0;
        D_80127500 = 0;
        D_8012704C = 0;
        D_801201F0 = 0;
        D_80127050 = 0;
        resLoad_lastId = s0;
        return 1;
    }
    return 0;
}








/* Packed BCD-ish clock word: low byte = minutes (mod 0x3C), high byte = hours
 * (mod 0x18), held in the two consecutive bytes D_80078EB0 / D_80078EB1.
 * Returns the signed 16-bit packed difference "now - (arg0:arg1)".
 *
 * Matching notes (residual levers, see docs/gcc-2.7.2-map/regalloc.md):
 *  - RC-12 ($0-ADD OPAQUE COPY): the target keeps the packed read live in $a3
 *    while a second, opaque copy lives in $a2 (compares read $a2, the &0xFF00
 *    terms read $a3), and likewise $t0 vs $a0 for the hour. A plain C copy is
 *    dissolved by cse/canon; `x = y + zr` with zr pinned to $0 emits the
 *    byte-identical `addu rD,rS,$zero` that neither cse nor combine can remove.
 *    This is also why `andi $v0,$a2,0xFF` survives: combine cannot see through
 *    the opaque copy to fold the low byte back to the D_80078EB0 lbu.
 *  - The 8-byte frame is a phantom: the target reserves `vars= 8` but never
 *    touches the stack. An unused 8-byte local reproduces it (get_frame_size()
 *    is set at expand and never shrinks). Its presence is load-bearing beyond
 *    the two sp insns -- it also lets dbr steal `subu $v0,$t0,$v1` into the
 *    second branch's delay slot and keeps the `sra` out of the jr slot.
 *  - Conditions are spelled `>=` (not `<`): gcc branches on the inverted
 *    compare to the else-label, which is what puts the 0x3C/0x18 arms second.
 */
s32 func_800D0D7C(s32 arg0, s32 arg1) {
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    register s32 zr __asm__("$0");
    u32 now;
    u32 r;
    s32 h;
    u32 dead[2];

    now = D_80078EB0 | (D_80078EB1 << 8);
    r = now + zr;
    h = arg0 + zr;
    if ((r & 0xFF) >= ((u32)arg1 & 0xFF)) {
        r = ((r - arg1) & 0xFF) | (now & 0xFF00);
    } else {
        r = ((0x3C - (arg1 - r)) & 0xFF) | (now & 0xFF00);
        h = arg0 + 1;
    }

    if (((r & 0xFFFF) >> 8) >= ((u32)h & 0xFF)) {
        r = ((((r & 0xFFFF) >> 8) - h) << 8) | (r & 0xFF);
    } else {
        r = ((0x18 - (h - ((r & 0xFFFF) >> 8))) << 8) | (r & 0xFF);
    }
    return (s16)r;
}


s16 func_800D0E30(u8 *p) {
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    register s32 zr __asm__("$0");
    u8 dummy[16];
    u32 hi;
    u32 lo;
    register u32 b __asm__("$5");
    register u32 t2 __asm__("$2");
    register u32 t3 __asm__("$3");
    register u32 h __asm__("$3");

    hi = (u8)(p[1] - D_80078EB1);
    lo = (u8)(p[0] - D_80078EB0);
    p = (u8 *)((hi << 8) | lo);

    b = (u32)p + zr;
    if ((b & 0xFF) >= 0x3C) {
        t3 = (b + 0x3C) & 0xFF;
        t2 = ((u32)p & 0xFF00) - 0x100;
        b = t2 | t3;
    }
    t2 = b & 0xFFFF;
    h = t2 >> 8;
    if (h >= 0x18) {
        t2 = (h + 0x18) << 8;
        t3 = b & 0xFF;
        b = t2 | t3;
    }
    return (s16)b;
}


// func_800D0EC4 — scan func_800291B4(i) over i in [0x2F, 0x3A]; return first i whose
//   (result & 0xFF) == 0, else 0.
//
// asm trace:
//   s0 = 0x2F                                        => i = 0x2F
// .L800D0ED4 (loop top):
//   jal func_800291B4(i)                             => r = func_800291B4(i)
//   andi v0, v0, 0xFF                                => r & 0xFF   (forced andi)
//   beqz v0, .exit / addu v0,s0,zero (delay: v0=i)   => if ((r&0xFF)==0) return i;
//   addiu s0, s0, 1                                  => i++
//   sltiu v0, s0, 0x3B                               => (u32)i < 0x3B   (unsigned, sltiu)
//   bnez v0, .L800D0ED4 / addu v0,zero,zero (v0=0)   => loop while in range; fall off -> 0
//
// CALLEE RETURN TYPE: func_800291B4 loads a byte (lbu). To force the `andi v0,0xFF`
// at THIS call site it MUST be declared returning a type wider than u8 (s32) with an
// explicit `& 0xFF`; declaring it u8 would let gcc drop the andi. (Matches the proven
// pattern: func_800291B4 reads D_800BA1B8[a0] via lbu.)
extern s32 func_800291B4();

s32 func_800D0EC4(void) {
    s32 i;

    for (i = 0x2F; (u32)i < 0x3B; i++) {
        if ((func_800291B4(i) & 0xFF) == 0) {
            return i;
        }
    }
    return 0;
}

extern s16 D_80078EAC;
extern void func_800291A0(s32, s32);
extern void func_800291C8(s32, s32);

void func_800D0F0C(s32 arg0, s32 arg1) {
    func_800291A0(arg0, arg1 & 0xFF);
    func_800291C8((arg0 << 1) - 0x4A, D_80078EAC);
}

// ANALYSIS: a0 masked to u8, passed to func_800D0F8C. Result in callee-saved s0
// (live across 2nd call). If result != 0: call func_800D0FE0(result), return result.
// Else return 0. beqz s0 with v0 preset to 0 in delay slot; nonzero path is fall-through.
extern s32 func_800D0F8C(u8 arg0);
extern void func_800D0FE0(s32 arg0);

s32 func_800D0F4C(u8 arg0) {
    s32 v0 = func_800D0F8C(arg0);
    if (v0 != 0) {
        func_800D0FE0(v0);
        return v0;
    }
    return 0;
}

/* func_800D0F8C - scan indices 0x2F..0x3A; return the first whose
 * (func_800291B4(i) & 0xFF) equals (arg0 & 0xFF); return 0 if none.
 * Loop counter is u32 so gcc emits sltiu (unsigned range test 0x3B).
 */
extern s32 func_800291B4();

s32 func_800D0F8C(u8 arg0) {
    u32 i;
    for (i = 0x2F; i < 0x3B; i++) {
        if ((func_800291B4(i) & 0xFF) == arg0) {
            return i;
        }
    }
    return 0;
}

extern void func_800291A0(s32 arg0, s32 arg1);

void func_800D0FE0(s32 arg0) {
    func_800291A0(arg0, 0);
}

extern s32 func_800291DC(s32);

s16 func_800D1000(s32 arg0) {
    return func_800291DC(arg0 * 2 - 0x4A);
}

// ANALYSIS: byte-for-byte structural twin of the ALREADY-MATCHED func_800D109C
//   (src/resident/resident.c:549). asm:
//     jal func_800291B4 (void)
//     jal func_800D1078        ; andi a0,v0,0xff in the delay slot (arg = result & 0xff)
//     sll v0,16 / sra v0,16    ; sign-extend the s16 result to s32
//   The sll/sra AFTER the call means gcc did NOT prove the value already
//   sign-extended -> the callee must be declared s32-returning here (NOT s16) so
//   the explicit (s16) cast materialises the sll/sra. If func_800D1078 were
//   declared s16-returning, gcc would prove the value extended and DROP the
//   sll/sra. Mirror func_800D109C exactly: callee s32-returning, explicit (s16)
//   cast, function returns s32. (func_800D1078 is elsewhere matched as s16(u8),
//   but at THIS call site we must locally over-declare its return width to s32 to
//   force the visible sign-extension -- same trick as the func_800D2EE8 twin.)
extern s32 func_800291B4();
extern s32 func_800D1078(u8);

s32 func_800D1028(void) {
    return (s16)func_800D1078(func_800291B4() & 0xff);
}

extern s32 D_8010EDE8[];

s32 func_800D1054(s32 arg0) {
    return D_8010EDE8[(arg0 & 0xFF) * 3];
}

// ANALYSIS: andi a0,0xff (u8 idx); index = idx*0xC; return lh at D_8010EDEC + idx*0xC.
// Array of 0xC-byte records, s16 field at offset 0.
extern s16 D_8010EDEC;

s32 func_800D1078(u8 arg0) {
    return *(s16 *)((u8 *)&D_8010EDEC + arg0 * 0xC);
}

// ANALYSIS: t = func_800291B4(); return (s16)func_800D10C8(t & 0xff);
// andi a0,v0,0xff lands in the jal delay slot (arg to func_800D10C8).
// sll/sra 16 => sign-extend the s16 return to s32.
extern s32 func_800291B4();
extern s32 func_800D10C8(s32);

s32 func_800D109C(void) {
    return (s16)func_800D10C8(func_800291B4() & 0xff);
}

// ANALYSIS: direct twin of the ALREADY-MATCHED func_800D1078 (resident.c:539):
//     extern s16 D_8010EDEC;  return *(s16*)((u8*)&D_8010EDEC + arg0*0xC);
// The only differences here:
//   (1) base is D_8010EDEE (the +2 field of the same 0xC-byte record table; D_8010EDEC
//       and D_8010EDEE are adjacent .short at the table head — verified in tail.data.s),
//   (2) the parameter is s32 (not u8): the function opens with `andi a0,a0,0xFF`, so the
//       mask is EXPLICIT in source (a u8 param would need no andi), and
//   (3) the prototype is `extern s32 func_800D10C8(s32)` (resident.c:547) -> s32 return.
//
// Index arithmetic: (arg0 & 0xFF) * 0xC -> gcc emits sll1 + addu (=*3) + sll2 (=*12).
// The load is `lh` (s16, sign-extended); with no trailing sll16/sra16 the sign-extended
// value is returned directly as s32. PRIOR DRAFT used a struct-array + s16 return; this
// uses the proven byte-pointer idiom + the declared s32 return instead.

extern s16 D_8010EDEE;

s32 func_800D10C8(s32 arg0) {
    return *(s16 *)((u8 *)&D_8010EDEE + (arg0 & 0xFF) * 0xC);
}

// func_800D10EC — loop over 0xC entries; per-entry slot test then schedule.
//   s5 = &D_80078E78 hoisted loop-invariant (LICM), read as `lh 0x34(s5)` inside.
//   s4 = 32-bit loop counter; (s16)s4 used in the body and the bottom loop test.
//
// asm trace per iteration:
//   s1 = (s16)i;  s3 = s1 + 0x2F
//   v1 = func_800291B4(s3) & 0xFF
//   if (v1 == 0) continue;
//   s2 = v1 * 0xC                                       (record stride 0xC)
//   s0 = D_8010EDF0[s2]   (lbu, record byte +0)
//   if (s0 == 0) continue;
//   j = (s16)i * 2 + 0x14
//   v0 = (s16)func_800291DC(j)                           (callee s32, re-extended (s16))
//   if (D_80078E78.field_0x34 - v0 < s0) continue;       (lh 0x34(s5); subu; slt signed)
//   func_800291A0(s3, D_8010EDF1[s2]);                   (lbu record byte +1)
//   func_800291C8(j, D_80078EAC);                        (lh s16 global)
//   loop test: (s16)i < 0xC
//
// FIX 1 (LICM hoist): prior used `*(s16*)(D_80078E78 + 0x34)` over a `u8[]`, which gcc did
// NOT hoist (re-emitted lui+lh every iteration -> 62 ins, no s5, frame 0x28). Taking the
// symbol address into a LOCAL POINTER before the loop (`S *p = &D_80078E78;` then
// `p->field_0x34`) makes gcc-2.7.2 keep &D_80078E78 in the saved reg s5 (lui+addiu in
// prologue), giving the target's 65-ins / frame-0x30 shape. (A plain typed-global field
// read `D_80078E78.field_0x34` was NOT enough — gcc still re-luied it; the explicit local
// pointer is what forces the hoist.)
//
// FIX 2 (instruction scheduling): the subtraction `field - (s16)callret` left a 2-insn swap:
// the target interleaves `sll v0,v0,16 ; lh v1,0x34(s5) ; sra v0,v0,16` (field load BETWEEN
// the sign-extension halves), mine did `lh ; sll ; sra`. Computing the sign-extended call
// result into an s32 temp FIRST (`s32 r=(s16)func_800291DC(j);`) and the field into a second
// temp (`s32 f=p->field_0x34;`) before `f - r` makes gcc emit the sext RTL before the field
// load -> the scheduler then fills with `sll;lh;sra` exactly. (Inlining either operand, or a
// `s16` temp, kept the wrong order; the s32-temp-of-(s16)-cast was the unlock.)
//
// func_800291B4 is K&R-called with an arg (asm passes s3) though resident.c:600 prototypes it
// `(void)`; func_800291DC is the proven `s32 func_800291DC(s32)`.
extern s32 func_800291B4();
extern s32 func_800291DC(s32);
extern void func_800291A0(s32, s32);
extern void func_800291C8(s32, s32);

typedef struct {
    u8 pad00[0x34];
    s16 field_0x34;    /* 0x34 */
} Struct80078E78;
extern Struct80078E78 D_80078E78;

extern u8 D_8010EDF0;
extern u8 D_8010EDF1;
extern s16 D_80078EAC;

void func_800D10EC(void) {
    s16 i;
    Struct80078E78 *p = &D_80078E78;

    for (i = 0; i < 0xC; i++) {
        s32 v1;
        s32 idx;
        s32 s0;
        s32 j;

        v1 = func_800291B4(i + 0x2F) & 0xFF;
        if (v1 == 0) {
            continue;
        }
        idx = v1 * 0xC;
        s0 = (&D_8010EDF0)[idx];
        if (s0 == 0) {
            continue;
        }
        j = i * 2 + 0x14;
        {
            s32 r = (s16)func_800291DC(j);   /* sign-extend FIRST (sll/sra scheduled early) */
            s32 f = p->field_0x34;            /* then load the field (lh between sll and sra) */
            if (f - r < s0) {
                continue;
            }
        }
        func_800291A0(i + 0x2F, (&D_8010EDF1)[idx]);
        func_800291C8(j, D_80078EAC);
    }
}


/* ANALYSIS (asm 0x9C):
 *   s1 = arg0 & 0xFF                          // andi
 *   s2 = s1 + 0x2F
 *   s0 = func_800291B4(s2) & 0xFF             // a0=s2 set before jal -> takes an arg here;
 *                                             //   andi v0,0xff -> callee return WIDER than u8 (s32)
 *   if (s0 == 0) return 0;                    // bnez s0,.work / else j ret0 (v0=0)
 *   v0 = (s16)func_800291DC(s1*2 + 0x14);     // sll16/sra16 -> s16; arg = (s1<<1)+0x14
 *   r = (s16)func_800D128C(s0, (s16)((u16)D_80078EAC - v0));
 *   if (r > 0) func_800291A0(s2, 0);          // blez r -> skip; i.e. (r > 0) does the call
 *   return r;
 *
 * D_80078EAC is loaded with `lhu` here (u16) -> declare u16 to avoid an `lh`+andi.
 * func_800291B4 takes an arg in THIS function (a0=s2 set), unlike its void use in
 * func_800D109C -- self-contained draft, so declare it with the arg locally.
 * The first call's arg (s1*2) is materialised in the bnez delay slot; the +0x14 in
 * the func_800291DC delay slot -- the single expression (s1*2 + 0x14) reproduces both.
 */

extern s32 func_800291B4();
extern s32 func_800291DC(s32 arg0);
extern s16 D_80078EAC;
extern s32 func_800D128C(s32 arg0, s32 arg1);
extern void func_800291A0(s32 arg0, s32 arg1);

s32 func_800D11F0(s32 arg0) {
    s32 s1 = arg0 & 0xFF;
    s32 s2 = s1 + 0x2F;
    s32 s0 = func_800291B4(s2) & 0xFF;
    s32 v0;
    s32 r;

    if (s0 == 0) {
        return 0;
    }

    v0 = (s16)func_800291DC(s1 * 2 + 0x14);
    r = (s16)func_800D128C(s0, (s16)((u16)D_80078EAC - v0));
    if (r > 0) {
        func_800291A0(s2, 0);
    }
    return r;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D128C);

s16 func_800D1658(s32 arg0) {
    extern int func_800291B4(int);
    extern void func_800291A0(int, int);
    extern void func_8002D4C8(int, int);
    extern s16 D_8010EDEC;
    register int v __asm__("$2");
    register int t __asm__("$3");
    int id;
    register short ret __asm__("$16");
    int slot;

    slot = (arg0 & 0xFF) + 0x2F;
    id = func_800291B4(slot) & 0xFF;
    if (id == 0) {
        return 0;
    }
    v = *(s16 *)((u8 *)&D_8010EDEC + id * 0xC);
    if (v > 0) {
        goto ok;
    }
    ret = v;
    t = ret & 0xFFFF;
    if (t != 0x8000) {
        goto bad;
    }
    if (id == 0x27) {
        goto bad;
    }
ok:
    func_800291A0(slot, 0);
    func_8002D4C8(0x462, 0);
    ret = 1;
    goto out;
bad:
    ret = 0;
    func_8002D4C8(0x45F, 0);
out:
    return ret;
}


extern u16 D_80078E50;
s32 func_800D1714(void) {
    return D_80078E50;
}

extern s32 D_800AE6B0;
void func_800D1724(s32 arg0) {
    D_800AE6B0 = arg0;
}

extern s32 D_800AE6A8;

void func_800D1734(s32 arg0) {
    D_800AE6A8 = arg0;
}

extern s32 D_800AE6AC;

void func_800D1744(s32 arg0) {
    D_800AE6AC = arg0;
}

/* func_800D1754 — MATCH (25 ins)
 * Key: the address &D_800AE6A8 is held in a callee-saved reg (s0) ACROSS the first
 * func_800D17B8 call, because it is used for both the load (temp = *p) and the store
 * (*p = 0) after the call. Writing the access through an explicit `s32 *p = &D_800AE6A8`
 * forces gcc-2.7.2 -O2 to compute the symbol address once (lui+addiu into s0) and reuse
 * it; the plain-global form re-materialised lui each time (no s0, frame 2 ins short).
 * D_800AE6A8/D_800AE6B0 are s32 (setters func_800D1734/func_800D1724). The 2nd call reuses
 * a0=temp (== D_800AE6B0 just stored). func_800D17B8 returns s32 (no andi after the jals).
 */
extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern s32 func_800D17B8(s32 arg0);

void func_800D1754(void) {
    s32 *p = &D_800AE6A8;
    s32 temp;

    if (func_800D17B8(D_800AE6B0) == 0) {
        temp = *p;
        if (temp != 0) {
            *p = 0;
            D_800AE6B0 = temp;
            func_800D17B8(temp);
        }
    }
}

// ANALYSIS (asm 0xA4):
//   s1 = arg0
//   s0 = arg0 & 0x80FFFFFF
//   beqz s0, .L800D1840   -- the ZERO case branches to the tail (return 0); the
//                            non-zero case falls through into the work body.
//   So the success body must be the fall-through (the if body), with the v0=0 tail
//   reached only by the beqz. Writing  if (s0 != 0) { work; return 1; } return 0;
//   makes the work block the fall-through and gcc emits  beqz s0,.L1840 .
//   func_800D185C(s0)
//   if (arg0 & 0x1000000) { D_800AE6B4 = &D_80159698; D_800AE6BC = 0; }
//   else { v0 = *(s32*)(s0+4); D_800AE6BC=0; D_80114EA8=0; D_800AE6B4 = v0; }
//   func_80011A3C(); return 1;
extern void func_800D185C(void *arg0);
extern void func_80011A3C(void);
extern void *D_800AE6B4;
extern u8 D_800AE6BC;
extern s32 D_80114EA8;
extern u8 D_80159698;

s32 func_800D17B8(s32 arg0) {
    s32 v = arg0 & 0x80FFFFFF;
    if (v != 0) {
        func_800D185C(v);
        if (arg0 & 0x1000000) {
            D_800AE6B4 = &D_80159698;
            D_800AE6BC = 0;
        } else {
            void *t = *(void **)(v + 4);
            D_800AE6BC = 0;
            D_80114EA8 = 0;
            D_800AE6B4 = t;
        }
        func_80011A3C();
        return 1;
    }
    return 0;
}

// arg0 (kept in t0) is a struct pointer. Body:
//  1) 36-byte aggregate copy *D_80078E50 = *arg0  (word loop [0,0x20) + 1-word tail).
//  2) D_800AE6A8.b16 = arg0->b2;
//  3) D_800AE6A8.w8  = (s32)arg0 | (D_800AE6A8.w8 & 0x1000000);   (or arg0 FIRST -> §10)
//  4) D_800AE6A8.b19 = arg0->b3;   (sb in the jr delay slot — last store)
// The target hoists &D_800AE6A8 into one register (t2) used by all 4 accesses, so model
// D_800AE6A8 as a STRUCT and reference named fields (gcc CSEs the base) rather than a u8[]
// with per-store lui/at absolute addressing.

typedef struct {
    s32 w[9];
} Blob36;

typedef struct {
    u8  pad0[2];
    u8  b2;
    u8  b3;
} Src;

typedef struct {
    u8  pad0[8];
    s32 w8;
    u8  pad12[10];
    u8  b16;
    u8  pad17[2];
    u8  b19;
} Dst;

extern u16 D_80078E50;
extern s32 D_800AE6A8;

void func_800D185C(void *arg0) {
    Dst *d = (Dst *)&D_800AE6A8;
    u8 b3;
    *(Blob36 *)&D_80078E50 = *(Blob36 *)arg0;
    d->b16 = ((Src *)arg0)->b2;
    b3 = ((Src *)arg0)->b3;
    d->w8 = (s32)arg0 | (d->w8 & 0x1000000);
    d->b19 = b3;
}

// ANALYSIS: idx = D_800AE6BC (u8, lbu — hoisted to the very top, before the frame).
// Copy the 3-word function-pointer array D_801141BC into a LOCAL stack array (sp+0x10),
// fully unrolled (lw v1/a0/a1 from 0/4/8, sw to 0x10/0x14/0x18 — a 12-byte struct copy),
// then call local[idx](&D_800AE6A8):  sll idx,2; addu sp,idx; lw 0x10(...); jalr.
// Frame -0x28 (ra@0x20, the 0xC-byte local array @0x10).
//
// PRIOR DRAFT was structurally close (same idea). Refinements for the byte form:
//  - The runtime index idx forces gcc to materialise the WHOLE table on the stack and
//    index the LOCAL (it can't prove idx), giving the copy+index seen in the asm. Modeling
//    D_801141BC as a 3-element fn-ptr array and copying it into an identical local array,
//    then indexing the local, is the faithful source.
//  - idx is read FIRST (the lbu floats to the top with no deps).
//  - The call passes &D_800AE6A8 (lui/addiu of the symbol address) as the single arg.
//
// The fn pointers take one pointer arg (the call site passes &D_800AE6A8). Use a struct
// wrapper so the whole-array assignment `local = D_801141BC` is a clean aggregate copy
// (3 words) and `local.fn[idx](...)` is the indexed call.

typedef struct {
    void (*fn[3])(void *);
} FnTbl3;

extern u8 D_800AE6BC;
extern FnTbl3 D_801141BC;
extern s32 D_800AE6A8;

void func_800D18DC(void) {
    u8 idx = D_800AE6BC;
    FnTbl3 local = D_801141BC;
    local.fn[idx](&D_800AE6A8);
}

/* ANALYSIS (asm 0x4C):
 *   s0 = arg0 (saved in func_800D1F58's delay slot)
 *   func_800D1F58();                    // void, no args set -> a0 still holds arg0 (incidental)
 *   func_801285D4();                    // void, nop in delay slot
 *   v0 = (u8)field 0x14  (lbu)
 *   a0 = arg0
 *   field 0x15 = 0       (sb)
 *   v0 = v0 + 1
 *   field 0x14 = (u8)v0  (sb, in jal delay slot)
 *   func_800D1984(arg0);
 *   return 0;            // addu v0,zero,zero -> plain s32 0
 *
 * field0x14 read with lbu (u8), the +1 result stored back with sb (so the store
 * truncates to 8 bits naturally). field0x15 is a u8 store of 0. The store order
 * in asm is: sb 0x15 (=0), then sb 0x14 (=field+1) -- but the 0x14 store sits in
 * the func_800D1984 delay slot. Writing field0x15=0 first then field0x14++ keeps
 * gcc's natural schedule (the 0x14 store hoists into the call delay slot).
 */

typedef struct {
    u8 pad[0x14];
    u8 f14;   /* 0x14 */
    u8 f15;   /* 0x15 */
} S800D1938;

extern void func_800D1F58(void);
extern void func_801285D4(void);
extern void func_800D1984(S800D1938 *arg0);

s32 func_800D1938(S800D1938 *arg0) {
    func_800D1F58();
    func_801285D4();
    arg0->f15 = 0;
    arg0->f14 = arg0->f14 + 1;
    func_800D1984(arg0);
    return 0;
}

s32 aF800D1984(u8 *arg0) __asm__("func_800D1984");

s32 aF800D1984(u8 *arg0) {
    extern s32 func_800D19DC();
    register s32 zr __asm__("$0");
    s32 (*fp)(void);
    u8 *p;

    fp = *(s32 (**)(void)) (arg0 + 0xC);
    if (fp() != 0) {
        p = arg0 + zr;
        p[0x14] = arg0[0x14] + 1;
        return func_800D19DC(p);
    }
    return 0;
}


extern s8 D_800B9A10;

s32 func_800D19DC(void) {
    D_800B9A10 = 1;
    return 1;
}

/* func_800D19F0: MATCH. Copy a 3-entry function-pointer struct (D_801141C8) to the
 * stack, run a location/state gate, then dispatch fns.f[ s0[0x14] ](s0) and RETURN its
 * value. Keys that closed the match:
 *  - STRUCT COPY: `fns = D_801141C8;` (not 3 element assigns) -> base-register load/store
 *    block (lui a1; addiu a1; lw 0/4/8; sw) matching the target prologue.
 *  - RETURN TYPE s32, early exits `return 0` -> the `move v0,zero` that fills each early
 *    return's delay slot (otherwise gcc schedules the 0x3069 constant load there).
 *  - DISPATCH is `return fns.f[...](s0)` with the fn-pointers returning s32 -> the jalr's
 *    v0 IS the return value, so NO extra `move v0,zero` on the dispatch path.
 */
extern u8 D_80126BA6;
extern s16 currentLocationId;
extern s32 D_80114EA8;
extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern void func_8001BE20(void);
extern s32 func_8001BE30(void);
extern void func_800CF8E4(void);

typedef struct {
    s32 (*f[3])(u8 *);
} FnTbl;

extern FnTbl D_801141C8;

s32 func_800D19F0(void) {
    FnTbl fns;
    u8 *s0 = (u8 *)&D_800AE6A8;
    s32 v1;

    fns = D_801141C8;

    if (D_80126BA6 != 0) {
        return 0;
    }
    if (currentLocationId != 0x3069) {
        v1 = D_80114EA8;
        if (v1 != 1) {
            if (v1 >= 2) {
                goto dispatch;
            }
            if (v1 != 0) {
                goto dispatch;
            }
            func_8001BE20();
            D_80114EA8 = D_80114EA8 + 1;
        }
        if (func_8001BE30() == 0) {
            return 0;
        }
        D_80114EA8 = D_80114EA8 + 1;
        if ((D_800AE6B0 & 0x1000000) == 0) {
            func_800CF8E4();
        }
    }
dispatch:
    return fns.f[s0[0x14]](s0);
}

// ANALYSIS (re-derived):
//   s0 = arg0 (struct ptr, callee-saved: live across 4 calls)
//   func_80029124(0x119, 0)
//   func_8002D4C8(4, 0x448)
//   func_8002D4C8(4, 0x449)
//   func_8002D4C8(4, 0x8ED)
//   D_800B9A10 = 0                    sb  (u8)  -- STORE 1
//   v0 = arg0->[0x14]                 lbu (u8)  -- LOAD (hoisted between store 1 & 2)
//   arg0->[0x15] = 0                  sb  (u8)  -- STORE 2
//   arg0->[0x14] = v0 + 1             sb  (u8)  -- STORE 3
//   return 0
//
// STORE ORDER (cookbook T2): the asm keeps stores in source order
//   D_800B9A10(0x14? no -> global), [0x15], [0x14].  The lbu of [0x14] is HOISTED early
//   (gcc loads the increment input ahead of the [0x15] store) but the THREE stores stay
//   in source order: global, +0x15, +0x14.  So write them in that exact order.
//
// Widths: D_800B9A10 sb => declared `s8` in resident.c (func_800D1BAC) -> COPY it ;
//   fields +0x14/+0x15 sb/lbu => u8.
// Return type s32 (plain addu v0,zero,zero).
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern s8 D_800B9A10;

s32 func_800D1B10(u8 *arg0) {
    func_80029124(0x119, 0);
    func_8002D4C8(4, 0x448);
    func_8002D4C8(4, 0x449);
    func_8002D4C8(4, 0x8ED);
    D_800B9A10 = 0;
    arg0[0x15] = 0;
    arg0[0x14] = arg0[0x14] + 1;
    return 0;
}

#include "common.h"

/* func_800D1B80:
 *   s0 = arg0 (struct ptr, callee-saved: live across the indirect call)
 *   v0 = arg0->[0xC]                  lw    -- the fn ptr
 *   if (v0() != 0) {                  jalr v0 ; bnez v0
 *       a0 = s0                       addu $a0,$s0,$zero  (branch delay slot)
 *       arg0[0x14] = arg0[0x14] + 1;  lbu s0 / addiu / sb A0   <-- note the base
 *       return DsMix(arg0);           jal DsMix (sb in the delay slot)
 *   }
 *   return 0;                         j .L800D1BC4 ; addu v0,zero,zero (delay)
 *
 * TWO LEVERS (both byte-required):
 *
 * 1. BLOCK LAYOUT — `if (cond != 0) { body; return DsMix(..); } return 0;`
 *    NOT the early-exit `if (cond == 0) return 0;` spelling.  The two are
 *    semantically identical but NOT byte-identical: the early-exit form sinks the
 *    return-0 block to the end (beqz + a trailing `j` = 23 ins).  The target puts
 *    the return-0 block INLINE before the body (bnez + `j` to the shared epilogue
 *    = 22 ins), which is what the `if (x != 0) {...} return 0;` shape expands to.
 *
 * 2. THE sb BASE IS $a0, NOT $s0 (regalloc map RC-12, the $0-ADD OPAQUE COPY).
 *    The load reads $s0 but the store reads $a0 => the original RTL had a SECOND
 *    pointer pseudo `p`, born before the lbu (so it conflicts with arg0 and cannot
 *    tie to $s0), used for the store and passed to DsMix -- local-alloc's hard-reg
 *    *suggestion* then grants it $a0 and the `a0 = p` arg copy self-deletes, leaving
 *    `addu $a0,$s0,$zero` as the copy itself.  A plain `u8 *p = arg0;` will NOT
 *    survive: cse2 canon (cse.c:826 make_regs_eqv) copy-propagates it away and the
 *    store reverts to $s0 (verified: 4 separate plain-C spellings all did exactly
 *    that).  `p = arg0 + zr` with zr pinned to $0 is a (plus reg (reg 0)) -- not a
 *    reg-reg set, so no canon and no qty merge -- and assembles to the byte-identical
 *    `addu $a0,$s0,$zero`.  $0 is fixed, so there are no regs_explicitly_used /
 *    bad_spill_regs side channels (RC-5) as a real-register pin would have.
 *
 * DsMix is declared K&R-unprototyped ON PURPOSE: the asm proves the call passes
 * arg0 in $a0, but resident.c defines `s32 DsMix(void)` (a custom 2-line wrapper
 * that ignores the arg -- docs/psyq-worklist.md).  An `extern s32 DsMix(u8 *)`
 * prototype would be a conflicting-types error against that definition; the empty-
 * paren declaration is C89-compatible with a (void) definition (cc1 exit 0, silent)
 * and still emits the $a0 argument setup.
 */
s32 func_800D1B80(u8 *arg0) {
    extern s32 DsMix();
    register s32 zr __asm__("$0");
    s32 (*fp)(void);
    u8 *p;

    fp = *(s32 (**)(void)) (arg0 + 0xC);
    if (fp() != 0) {
        p = arg0 + zr;
        p[0x14] = arg0[0x14] + 1;
        return DsMix(p);
    }
    return 0;
}


extern void func_800D1BF8(void);

s32 DsMix(void) {
    func_800D1BF8();
    return 1;
}

// ANALYSIS (re-derived instruction-by-instruction):
//
// PROLOGUE (the key fix vs the prior draft = ORDER):
//   v1 = D_800AE6B0 & 0x80FFFFFF                 lw + and  (struct ptr)
//   fp = *(void(**)(void))(v1 + 0x1C)            lw 0x1C(v1)   -- LOAD the fn ptr FIRST
//   p  = &D_800AE6A8                             la (set up early, used at the tail)
//   D_800B9A0E = 0                               sh  -- store AFTER the fn-ptr load,
//                                                       before the call (stores can't
//                                                       hoist past the jalr)
//   fp()                                         jalr v0
//   The prior draft wrote `D_800B9A0E = 0;` BEFORE the call expression, which let gcc
//   emit the store ahead of the fn-ptr load -> wrong order. Computing the target into a
//   local first pins the load ahead of the store, matching the asm.
//
//   func_800D1D24()
//   if (func_80011DF4() != 0) {                  beqz v0,.L1C64 (else-chain branches in)
//       func_80011DCC();
//       func_80011818(0x11);                     -> j .L1CF0 (tail)
//   } else {
//       // a0val computed by a cascade, then func_80011B7C(a0val)
//       if (func_8002AF08() != 0)         a0val = 0xD;     bnez v0 (a0=0xD in delay)
//       else if (func_800CFBE8() != 0)  { func_800CFBBC(); a0val = 0x13; }
//       else if (func_80029264() != 0)  { func_80029254(); a0val = 0x12; }
//       else switch (func_800D1DB0()) {           beq v1,1 / slti v1,2 / bnez v1
//           case 0:  a0val = 6;  break;
//           case 1:  a0val = 5;  break;
//           default: a0val = 0x10; break;
//       }
//       func_80011B7C(a0val);
//   }
//   // TAIL .L1CF0:
//   if (*(s32*)(p + 8) & 0x1000000) p[0x17] = 1; else p[0x17] = 0;
//
// Widths/types (COPIED from already-matched resident.c):
//   D_800AE6B0 = s32 (func_800D1724 stores arg0)  -> lw + and 0x80FFFFFF -> struct base.
//   D_800AE6A8 = s32 (func_800D1734 stores arg0)  -> &D_800AE6A8 is a struct/array base
//                here, fields at +8 (lw=s32) and +0x17 (sb=u8); take its address as u8*.
//   D_800B9A0E = s16 (func_800D1764/.. stores 1/2).
extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern s16 D_800B9A0E;

extern void func_800D1D24(void);
extern s32  func_80011DF4(void);
extern void func_80011DCC(void);
extern void func_80011818(s32);
extern s32  func_8002AF08(void);
extern s32  func_800CFBE8(void);
extern void func_800CFBBC(void);
extern s32  func_80029264(void);
extern void func_80029254(void);
extern s32  func_800D1DB0(void);
extern void func_80011B7C(s32);

void func_800D1BF8(void) {
    u8 *p = (u8 *)&D_800AE6A8;
    void (*fp)(void);
    s32 a0val;

    fp = *(void (**)(void))((D_800AE6B0 & 0x80FFFFFF) + 0x1C);
    D_800B9A0E = 0;
    fp();
    func_800D1D24();

    if (func_80011DF4() != 0) {
        func_80011DCC();
        func_80011818(0x11);
    } else {
        if (func_8002AF08() != 0) {
            a0val = 0xD;
        } else if (func_800CFBE8() != 0) {
            func_800CFBBC();
            a0val = 0x13;
        } else if (func_80029264() != 0) {
            func_80029254();
            a0val = 0x12;
        } else {
            s32 n = func_800D1DB0();
            if (n != 1) {
                if (n < 2 && n == 0) {
                    a0val = 6;
                } else {
                    a0val = 0x10;
                }
            } else {
                a0val = 5;
            }
        }
        func_80011B7C(a0val);
    }

    if (*(s32 *)(p + 8) & 0x1000000) {
        p[0x17] = 1;
    } else {
        p[0x17] = 0;
    }
}

/* func_800D1D24:
 *   v0 = D_80078E50 (u16)
 *   a0 = D_800B9A0A (u16, old value)
 *   D_800B9A11 = 1
 *   currentLocationId = v0
 *   D_800B9A0C = a0          (old D_800B9A0A)
 *   D_800B9A0A = v0 & 0xF000
 *   func_8001C0C8(); func_80015310(); func_80129258(); func_801378F0();
 */
extern u16 D_80078E50;
extern u16 D_800B9A0A;
extern u8  D_800B9A11;
extern s16 currentLocationId;
extern s16 D_800B9A0C;
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_80129258(void);
extern void func_801378F0(void);

void func_800D1D24(void) {
    u16 v0 = D_80078E50;
    u16 old = D_800B9A0A;
    D_800B9A11 = 1;
    currentLocationId = v0;
    D_800B9A0C = old;
    D_800B9A0A = v0 & 0xF000;
    func_8001C0C8();
    func_80015310();
    func_80129258();
    func_801378F0();
}

extern u16 D_80078E50;

s32 func_800D1D94(void) {
    return (s32)((D_80078E50 & 0xF000) << 16) >> 16;
}

/* func_800D1DB0 — multi-exit, shared `return 2` tail. */
extern s16 currentLocationId;
extern u16 D_80078E50;
extern s32 func_800CFC5C(s32);
extern s32 func_800CFD68(s32);

s32 func_800D1DB0(void) {
    if (currentLocationId == 0x3005) {
        return 2;
    }
    if (func_800CFC5C(currentLocationId) != 0) {
        return 2;
    }
    if (func_800CFD68(D_80078E50) == 0) {
        return 2;
    }
    if (func_800CFC5C(D_80078E50) == 0) {
        return 1;
    }
    return 2;
}

void func_800D1E20(void) {
}

void func_800D1E28(void) {
    extern s16 currentLocationId;
    extern u16 D_80078E50;
    extern int func_800CFC5C(int);
    extern int func_800CFD68(int);
    extern void func_800168B4(int);
    extern void func_800167B8(int);
    int result;
    int r;

    if (currentLocationId == 0x3005) goto two;
    r = func_800CFC5C(currentLocationId);
    result = 2;
    if (r != 0) goto test;
    if (func_800CFD68(D_80078E50) == 0) goto two;
    r = func_800CFC5C(D_80078E50);
    result = 1;
    if (r == 0) goto test;
two:
    result = 2;
test:
    if (result < 0) goto other;
    if (result >= 2) goto other;
    func_800168B4(4);
    return;
other:
    func_800167B8(4);
}


/* func_800D1EBC — MATCH (39 ins)
 * Computes a small state (1 or 2) via a condition chain, then dispatches to one of two
 * helpers and returns (result != 0).
 *
 * State chain — note the LAST two branches are written so the default (state=2) is the
 * shared fall-through block .L800D1F14 (reached by the 0x3005 beq AND the CFD68==0 beqz),
 * and the state=1 case is the branch-taken delay slot. Writing the final test as
 * `func_800CFC5C(...) != 0 -> state=2  else state=1` produces
 *   beqz v0,.L1F18 (delay: addiu v1,1) ; .L1F14: addiu v1,2   (fall-through)
 * which is the target's branch sense. The earlier `!= 0`/`==0` senses likewise map 1:1.
 *
 * Dispatch — the asm is `bltz v1,F3C ; slti v0,v1,2 ; beqz v0,F3C` = a SIGNED two-sided
 * range test with the LOW bound (`< 0`, bltz) emitted FIRST. A `switch(state){case 0:
 * case 1:...}` emits the bounds in the REVERSE order (slti high-bound first). Only the
 * explicit nested if  `if (state<0) B; else if (state<2) A; else B;`  forces gcc-2.7.2 to
 * test the low bound first (bltz) then the high bound (slti<2). state ∈ {1,2} so the bltz
 * is effectively dead, but gcc still emits the canonical low-then-high pair.
 *
 * Callee returns: each jal is followed by `andi v0,0xffff` then a shared `sltu zero,v0`,
 * so func_800168C4/func_800167F0 return u16 and the value flows into `ret != 0` (sltu).
 * currentLocationId is s16 (lh); D_80078E50 is u16 (lhu) — both proven in resident.c.
 */
extern s16 currentLocationId;
extern u16 D_80078E50;
extern s32 func_800CFC5C(s32);
extern s32 func_800CFD68(s32);
extern u16 func_800168C4(s32);
extern u16 func_800167F0(s32);

s32 func_800D1EBC(void) {
    s32 state;
    s16 loc = currentLocationId;
    u16 ret;

    if (loc == 0x3005) {
        state = 2;
    } else if (func_800CFC5C(loc) != 0) {
        state = 2;
    } else if (func_800CFD68(D_80078E50) == 0) {
        state = 2;
    } else if (func_800CFC5C(D_80078E50) != 0) {
        state = 2;
    } else {
        state = 1;
    }

    if (state < 0) {
        ret = func_800167F0(4);
    } else if (state < 2) {
        ret = func_800168C4(4);
    } else {
        ret = func_800167F0(4);
    }
    return ret != 0;
}

extern u16 D_80078EB4;
extern u16 D_80078EB8;
extern s32 D_80078E8C;
extern s32 D_8011DB14;
extern s32 D_8011DB1C;
extern s32 D_80128150;

void func_800D1F58(void) {
    D_8011DB14 = D_80078EB4;
    D_8011DB1C = D_80078EB8;
    D_80128150 = D_80078E8C;
}

/* func_800D1F90 — the inverse of the matched func_800D1F58 (resident.c:673).
 *
 *   D_80078EB4 (u16) = (u16)D_8011DB14 (s32)   -> lw v0; sh v0
 *   D_80078EB8 (u16) = (u16)D_8011DB1C (s32)   -> lw v1; sh v1
 *   D_80078E8C (s32) =       D_80128150 (s32)  -> lw a0; sw a0
 *
 * The three source loads are independent, so gcc's r3000 scheduler hoists all
 * three lw's ahead of the three stores (matches the asm: lw,lw,lw,sh,sh,sw).
 * Types COPIED verbatim from the matched func_800D1F58 so the load widths agree:
 * D_80078EB4/B8 are u16, the rest s32.  sh truncates the s32 source naturally.
 */
extern u16 D_80078EB4;
extern u16 D_80078EB8;
extern s32 D_80078E8C;
extern s32 D_8011DB14;
extern s32 D_8011DB1C;
extern s32 D_80128150;

void func_800D1F90(void) {
    D_80078EB4 = D_8011DB14;
    D_80078EB8 = D_8011DB1C;
    D_80078E8C = D_80128150;
}

/* func_800D1FC8 — resident (0x800D1FC8).
 * Step an object's position toward the global target/camera vector.
 *
 * Levers (docs/matching-cookbook.md / gcc-2.7.2-map):
 *  - regalloc.md S13/RC-10: `sh = arg1;` taken MID-BODY (after the deltas) dissolves the
 *    assign_parms head copy, keeping $a1 live through the delta window -> hard-reg conflict
 *    steers the global pointer to $a2 (not $a1) and dy to $a3. Pin-free.
 *  - local-alloc qty_compare density: hoisting the pair-2/3 global loads into t1/t2 makes the
 *    lw's qty span 2 and the lhu's span 1, so the lhu wins $v1 and the lw takes $a0 (target
 *    order). Pair 1's lw merges with the block-local dx qty, so it must stay un-hoisted.
 */
void func_800D1FC8(void *arg0, int arg1) {
    extern int D_801151D4;
    extern void VectorNormalSS(void *a0, void *a1);

    int *g;
    short v[4];
    int dx, dy, dz;
    int sh, t1, t2;

    g = (int *)D_801151D4;

    dx = *(int *)((char *)g + 0x5C) - *(unsigned short *)((char *)arg0 + 6);
    v[0] = dx;
    t1 = *(int *)((char *)g + 0x60);
    dy = t1 - *(unsigned short *)((char *)arg0 + 10);
    v[1] = dy;
    t2 = *(int *)((char *)g + 0x64);
    dz = t2 - *(unsigned short *)((char *)arg0 + 14);
    v[2] = dz;
    sh = arg1;

    if ((unsigned int)((dx + 0x3FFF) & 0xFFFF) >= 0x7FFF ||
        (unsigned int)((dy + 0x3FFF) & 0xFFFF) >= 0x7FFF ||
        (unsigned int)((dz + 0x3FFF) & 0xFFFF) >= 0x7FFF) {
        v[2] = 0;
        v[0] = 0;
        v[1] = -0xFFF;
    }

    VectorNormalSS(v, v);

    *(unsigned short *)((char *)arg0 + 6) += v[0] >> (sh & 0xFFFF);
    *(unsigned short *)((char *)arg0 + 10) += v[1] >> (sh & 0xFFFF);
    *(unsigned short *)((char *)arg0 + 14) += v[2] >> (sh & 0xFFFF);
}


/* ANALYSIS (asm 0x104):
 * arg0 (s0) = position struct {u16 x@0, y@2, z@4}.
 * arg1 (s1) = SVECTOR* {s16 vx@0, vy@2, vz@4}.
 * arg2 (s2) = shift amount (used as arg2 & 0xFFFF).
 * D_801151D4 is a POINTER global (lw a1,D_801151D4 then lw 0x5C/0x60/0x64(a1)).
 *
 *   dx = D_801151D4->t5C - (u16)arg0->x     (lw - lhu, in s32; sh to local[0])
 *   dy = D_801151D4->t60 - (u16)arg0->y     (sh local[1])
 *   dz = D_801151D4->t64 - (u16)arg0->z     (sh local[2])
 *   all three deltas are live across test1's branch (dy in a3, dz in a0) -> they
 *   are all computed BEFORE the first test, so "compute all deltas, store, then test".
 *
 *   range test on each: (u32)((d + 0x3FFF) & 0xFFFF) < 0x7FFF  (addiu;andi;sltiu).
 *   test1 beqz->override, test2 beqz->override, test3 bnez->keep (3rd inverted) ==
 *   if (t1 && t2 && t3) keep; else override.  Override re-stores local in the asm
 *   order z=0, x=0, y=-0xFFF.
 *
 *   VectorNormalSS(&local, arg1);
 *   shift = arg2 & 0xFFFF;                    (andi a0,s2,0xFFFF -- once, reused x3)
 *   arg0->x += (s16)arg1->vx >> shift;        (lh ; srav ; lhu+add+sh)
 *   arg0->y += (s16)arg1->vy >> shift;
 *   arg0->z += (s16)arg1->vz >> shift;
 */

typedef struct { s16 vx, vy, vz, pad; } SVECTOR;

typedef struct {
    u16 x;   /* 0x0 */
    u16 y;   /* 0x2 */
    u16 z;   /* 0x4 */
} Pos800D20C0;

typedef struct {
    u8  pad[0x5C];
    s32 t5C;  /* 0x5C */
    s32 t60;  /* 0x60 */
    s32 t64;  /* 0x64 */
} Tgt800D20C0;

extern Tgt800D20C0 *D_801151D4;
extern long VectorNormalSS(SVECTOR *a, SVECTOR *b);

void func_800D20C0(Pos800D20C0 *arg0, SVECTOR *arg1, s16 arg2) {
    SVECTOR local;
    Tgt800D20C0 *p = D_801151D4;
    s32 dx, dy, dz;
    s32 shift;

    { s32 tx = p->t5C; dx = tx - arg0->x; }
    local.vx = dx;
    { s32 ty = p->t60; dy = ty - arg0->y; }
    local.vy = dy;
    { s32 tz = p->t64; dz = tz - arg0->z; }
    local.vz = dz;

    if (((u32)((dx + 0x3FFF) & 0xFFFF) < 0x7FFF) &&
        ((u32)((dy + 0x3FFF) & 0xFFFF) < 0x7FFF) &&
        ((u32)((dz + 0x3FFF) & 0xFFFF) < 0x7FFF)) {
        /* keep computed deltas */
    } else {
        local.vz = 0;
        local.vx = 0;
        local.vy = -0xFFF;
    }

    /* MATCH lever (permuter): arg2 declared `s16` (not s32) + per-delta ptr-field
     * temps `{s32 t = p->tNN; d = t - arg0->f;}` reproduce the target's ptr-first
     * load order AND the dy->a3 / dz->a0 register allocation.  Both levers needed. */
    VectorNormalSS(&local, arg1);

    shift = arg2 & 0xFFFF;
    arg0->x += arg1->vx >> shift;
    arg0->y += arg1->vy >> shift;
    arg0->z += arg1->vz >> shift;
}

/* ANALYSIS (asm 0x68):
 *   s0 = func_801465C0(arg0); s1=arg1, s2=arg2 saved in prologue.
 *   bnez s0, .L800D21F8   -- the NON-zero (success) path branches forward, the
 *                            zero path falls through to  j .L800D2210 ; v0=0.
 *   So source form must be  if (s0 != 0) { work; return s0; } return 0;
 *   (the success arm branched-to, the return-0 as fall-through after the bnez).
 *   In the work block: func_8001CC3C(s0, arg1, 0, 0) with  sb s2,0x27(s0)  sitting
 *   in the jal's delay slot in asm -> write the store AFTER the call.
 */
typedef struct {
    u8 pad[0x27];
    u8 f27;   /* 0x27 */
} S800D21C4;

extern void *func_801465C0(s32 arg0);
extern void func_8001CC3C(S800D21C4 *arg0, s32 arg1, s32 arg2, s32 arg3);

S800D21C4 *func_800D21C4(s32 arg0, s32 arg1, s32 arg2) {
    S800D21C4 *s0 = (S800D21C4 *)func_801465C0(arg0);
    if (s0 != 0) {
        func_8001CC3C(s0, arg1, 0, 0);
        s0->f27 = arg2;
        return s0;
    }
    return 0;
}

// func_800D222C — allocate via func_801465C0(arg0); on success initialise via
// func_8001CB6C(p, arg1, 0, 0), store arg2 byte at p[0x27], return p; on NULL return 0.
//
// FIX vs prior draft: BRANCH POLARITY (cookbook §2 T4). The asm is
//     bnez s0,.L800D2260   ; branch TO the call/init path
//     j .L800D2278 ; addu v0,zero,zero   ; the FALL-THROUGH is `return 0`
// so the success path is the branched-to block and `return 0` falls through. The
// matching source therefore writes `if (p != 0) { ...; return p; } return 0;`
// (the prior `if (p == 0) return 0;` produced the inverse beqz).
//
// Arg note: a0 for func_8001CB6C is the alloc result (asm `addu a0,s0,zero` in the
// bnez delay slot) — i.e. p is its first argument.

extern void *func_801465C0(s32);
extern void func_8001CB6C(u8 *, s32, s32, s32);

u8 *func_800D222C(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p = func_801465C0(arg0);
    if (p != 0) {
        func_8001CB6C(p, arg1, 0, 0);
        p[0x27] = arg2;
        return p;
    }
    return 0;
}

// MATCHED form: structure as `if (p) { call; return p; } return 0;` so gcc emits
// `bnez s0,.L22C0` with the `return 0` (v0=0) in the j delay slot of the false path,
// and the call arm inlined after (a1=s1 in the jal delay, v0=s0 the return move).
extern void *func_801465C0(s32 arg0);
extern void func_8001CD9C(void *arg0, s32 arg1);

void *func_800D2294(s32 arg0, s32 arg1) {
    void *p = func_801465C0(arg0);
    if (p) {
        func_8001CD9C(p, arg1);
        return p;
    }
    return 0;
}

typedef struct {
    /* 0x00 */ s32 f0;
    /* 0x04 */ s32 f4;
    /* 0x08 */ s32 f8;
    /* 0x0C */ s32 fC;
    /* 0x10 */ s32 f10;
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
} S800D22E4;

void func_800D22E4(S800D22E4 *p) {
    p->f4 += p->f10;
    p->f8 += p->f14;
    p->fC += p->f18;
}

// ANALYSIS: leaf-ish fn taking a struct* (a0=s3). Loads s32 at +0x2C, masks
// with 0x3FFFFFFF, extracts three signed bitfields via <<16>>19 / <<22>>19
// (signed /8-style scaled extracts), squares two of them, calls
// func_80047D3C(s1f^2 + s2f^2) -> r1, then ratan2(s0f,(s16)r1) -> r2 (stored
// negated at +0x12), then ratan2(s1f,s2f) -> r3 stored at +0x16, +0x1A=0.
// Risk: exact shift/extract idiom + mult/mflo ordering + the negate-in-delay-slot.

extern s32 func_80047D3C(s32 arg0);
extern s32 ratan2(s32 y, s32 x);

void func_800D2318(s32 *p) {
    s32 raw = p[0xB];                 /* *(s32*)((u8*)p + 0x2C) */
    u32 masked = (u32)raw & 0x3FFFFFFF;   /* u32 -> srl on the >> below (matches asm) */
    s32 s1f = (s32)(((masked >> 14) & 0xFFC0) << 16) >> 19;
    s32 s2f = (s32)(raw << 22) >> 19;
    s32 s0f = (s32)(((masked >> 4) & 0xFFC0) << 16) >> 19;
    s32 r1 = func_80047D3C(s1f * s1f + s2f * s2f);

    *(s16 *)((u8 *)p + 0x12) = -ratan2(s0f, (s16)r1);
    *(s16 *)((u8 *)p + 0x16) = ratan2(s1f, s2f);
    *(s16 *)((u8 *)p + 0x1A) = 0;
}

extern s32 func_80047D3C(s32 arg0);
extern s32 ratan2(s32 y, s32 x);

void func_800D23D0(s16 *p) {
    s32 fx = p[0];
    s32 fz = p[2];
    s32 fy = p[1];

    p[0] = -ratan2(fy, func_80047D3C(fx * fx + fz * fz));
    p[1] = ratan2(fx, fz);
    p[2] = 0;
}

void func_800D2460(void) {
}

extern void func_80016714(void *, s32);
extern u8 D_80115110[];
extern s32 D_8012751C;
extern s32 D_8011DB20;

void func_800D2468(void) {
    func_80016714(D_80115110, 0xC4);
    D_8012751C = 0;
    D_8011DB20 = 0;
}








typedef struct { s32 f0; } E4;

void func_800D24A0(s16 arg0) {
    extern void func_80018FC8(void);
    extern void func_800596F4(s32);
    extern void func_8002D4C8(s32, s32);
    extern u16 D_800B9A02;
    extern u8 D_800B9A13;
    extern u8 D_800A6518[];
    extern u8 D_8007BA70[];
    extern u8 D_800856B0[];
    extern u16 D_80115112;
    extern u16 D_8011512A;
    extern u16 D_80115124;
    extern u8 D_80115110[];
    extern u16 D_80115114;
    extern u8 *D_801151C8;
    extern u8 *D_801151CC;
    extern E4 D_80115168[];

    u16 i;
    u32 *src;
    u32 *dst;
    u16 *v;
    char *p;

    func_80018FC8();
    func_800596F4(0);

    src = (u32 *)&D_800A6518[(D_800B9A02 ^ 1) * 20];
    dst = (u32 *)&D_800A6518[D_800B9A02 * 20];
    for (i = 0; i < 5; i++) {
        *dst++ = *src++;
    }

    v = &D_80115112;
    *v = 0;
    D_8011512A = 0;
    D_80115124 = 0;
    (*(u16 *)D_80115110) = arg0;
    D_800B9A13 = arg0 + 1;
    D_80115114 = D_800B9A02;
    D_801151C8 = &D_8007BA70[D_800B9A02 * 80000];
    D_801151CC = &D_800856B0[D_800B9A02 * 80000];

    i = 0;
    p = (char *)v - 2;
    do {
        *(s32 *)(p + (s16)i * 4 + 0x78) = 0;
        D_80115168[(s16)i].f0 = 0;
        i++;
    } while ((s16)i < 8);

    func_8002D4C8(0x14, 0);
}


extern void (*D_8011DB24)(void);

void func_800D25FC(void) {
    D_8011DB24();
}

extern u8 D_800B9A13;
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_800D2624(void) {
    D_800B9A13 = 0;
    func_8002D4C8(0x15, 0);
}

typedef struct {
    u32 *ot;            /* 0x00 */
    u32 pad[4];         /* 0x04..0x13 */
} Env_800D2650;         /* 0x14 stride */

typedef struct {
    u32 addr : 24;      /* 0x00 tag */
    u32 len  : 8;
} PTag_800D2650;

#define OT_800D2650             (D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot)
#define getaddr_800D2650(t)     (((PTag_800D2650 *)(t))->addr)
#define setaddr_800D2650(t, v)  (((PTag_800D2650 *)(t))->addr = (u32)(v))
#define addPrim_800D2650(ot, p) (setaddr_800D2650(p, getaddr_800D2650(ot)), \
                                 setaddr_800D2650(ot, p))

u32 *func_800D2650(u32 *param_1, u8 *param_2, short param_3, short param_4, int a5, u32 a6)
{
    extern Env_800D2650 D_800AE7BC[];
    extern short D_800B9A02;

    register int cw __asm__("$2");
    register u32 s_a6 __asm__("$8") = a6;
    register u32 code __asm__("$14");
    register int clut __asm__("$13");
    register u8 bVar1 __asm__("$3");
    short sVar2;

    if (*param_2 < 0x80) {
        cw = 0x64000000;
        code = s_a6 | cw;
        cw = a5 + 0x100;
        clut = (cw << 6) | 0x16;
        do {
            sVar2 = *(short *)param_2;
            switch (sVar2) {
            case 0x1850:
            case 0x1858:
                *(short *)((u8 *)param_1 + 8) = param_3 + 4;
                *(short *)((u8 *)param_1 + 0xA) = param_4 - 7;
                break;
            case 0x3870:
                param_3 = param_3 + 7;
                param_2 = param_2 + 2;
                continue;
            case 0x3871:
                param_3 = param_3 + 4;
                param_2 = param_2 + 2;
                continue;
            case 0x3872:
                param_3 = param_3 + 2;
                param_2 = param_2 + 2;
                continue;
            default:
                *(short *)((u8 *)param_1 + 8) = param_3;
                *(short *)((u8 *)param_1 + 0xA) = param_4;
                param_3 = param_3 + 7;
                break;
            }
            *param_1 = 0x04000000;
            *(u32 *)((u8 *)param_1 + 4) = code;
            ((u8 *)param_1)[0xC] = *param_2;
            param_2 = param_2 + 1;
            sVar2 = 8;
            bVar1 = *param_2;
            param_2 = param_2 + 1;
            *(short *)((u8 *)param_1 + 0xE) = clut;
            ((u8 *)param_1)[0xD] = bVar1;
            *(short *)((u8 *)param_1 + 0x10) = sVar2;
            *(short *)((u8 *)param_1 + 0x12) = sVar2;
            addPrim_800D2650(&OT_800D2650[2], param_1);
            param_1 = param_1 + 5;
        } while (*param_2 < 0x80);
    }
    return param_1;
}


/* func_800D27DC — MATCH (135 ins).  Emit a run of textured POLY_FT4 sprites into the
 * packet buffer at `out`, addPrim()-ing each one onto the current double-buffer's OT.
 *
 * Source stream `src` is a u16 record per quad:
 *   +0 x  | +2 y  | +4 dx | +6 dy | +8 u | +0xA v
 *   and, when (flags & 2), four more: clut, tpage, du, dv.
 * When (flags & 2) == 0 the texture window is the fixed 8x8 cell clut=0x4056 tpage=0x15,
 * shrunk to 7 in u or v on a repeating (i & 7) cadence.  (flags & 1) dims the flat colour
 * from 0x808080 to 0x585858; prim code is 0x2C (POLY_FT4, len 9).
 *
 * DIRECT REUSE of the four levers proven on func_800D29F8 (the very next function in this
 * same TU, src/resident/resident.c) — this card had no banked twin, but 29F8's header
 * comment IS the crib:
 *
 *  1. `D_800B9A02` VOLATILE, read as `*(volatile u16 *)&D_800B9A02`.  The cast-wrapped `*&`
 *     takes expr.c's INDIRECT_REF path => memory_address() force_regs the constant address
 *     => `la $s1, D_800B9A02` HOISTED INTO THE LOOP PREHEADER (idx 19-20) + `lhu 0($s1)`
 *     twice per iteration.  A bare `D_800B9A02` gives (mem (symbol_ref)) => a maspsx lui/lhu
 *     pair inside the loop and no preheader address.
 *
 *  2. addPrim is the REAL libgpu bitfield macro (both halves `->addr =`), NOT hand-written
 *     masks.  THIS WAS THE WHOLE 42-INSTRUCTION RESIDUAL of the previous attempt:
 *     store_bit_field masks the VALUE (0xFFFFFF) before the DESTINATION (0xFF000000), so the
 *     loop-invariant constants are BORN in the order [&D_800B9A02, 0xFFFFFF, 0xFF000000]
 *     (idx 19-23) and the `or` takes the memory-masked temp as its FIRST operand.  The
 *     hand-rolled `(*out & 0xFF000000) | (ot[2] & 0xFFFFFF)` spelling gets both backwards
 *     (0xFF000000 born first), and every downstream register then walks.
 *
 *  3. OT_800D27DC is a MACRO and `ot` is DOUBLE-EVALUATED exactly as libgpu's addPrim does
 *     => the two independent `lhu 0($s1)` + `lui %hi(D_800AE7BC)` index recomputations.
 *     A named `ot` local would be one pseudo for the whole fn (no live-range splitting in
 *     gcc-2.7.2) and collapse them.
 *
 *  4. `o = add` — an int alias for the u16 param.  A u16 param is a PROMOTED SUBREG, so
 *     combine's commutative canonicalisation ("object first, non-object second") swaps
 *     `(plus src_val add)` => `addu $t3,$s4,$v0`.  Aliasing to a plain int pseudo defeats the
 *     swap => the target's `addu $t3,$v0,$s4` (idx 31).
 *
 * Two more, found here (NOT in 29F8's list — both cost 2 instructions and 30 register walks):
 *
 *  5. `f2 = flags & 2;` MUST BE ITS OWN STATEMENT at the top of the loop body.  Spelled
 *     inline as `if ((flags & 2) == 0)` the andi is NOT hoisted by loop.c, so `flags` stays
 *     live across the loop and costs a `move $t9,$a0` copy AND leaves the `bnez` delay slot
 *     unfilled (137 ins, closeness 109).  As a statement it hoists to idx 18 — FIRST in the
 *     preheader, ahead of the addPrim invariants, which is exactly the target's order.
 *
 *  6. Field stores are RAW CASTS `*(s16 *)(out + K)`, not a `p = (PolyFT4 *)(out + 4)`
 *     struct (which is how 29F8 spells it).  Struct-member stores are MEM_IN_STRUCT_P and
 *     gcc-2.7.2's alias code treats them as non-conflicting with the `*(u32 *)out` full-word
 *     read inside addPrim, letting the scheduler hoist that read arbitrarily early; plain
 *     casts keep everything on one alias footing so the `lw $v1,0($t4)` stays at idx 112
 *     where source order puts it.  Raw casts are also what produce the target's `out + 0x1D`
 *     biased giv ($t0, offsets -0x19..+0x8).
 *
 * Chained vs unchained store pairs (29F8's rule: chaining emits store_expr's SImode->narrow
 * truncation copy, visible only when the source variable stays live afterwards):
 *   x pair, y pair  -> UNCHAINED (no copy in the target; both stay live for x+w / y+h)
 *   u pair, v pair  -> CHAINED   (the target's `addu $v0,$a0,$zero` / `addu $v0,$a1,$zero`)
 *
 * Symbols hand-checked against asm/resident/nonmatchings/resident/func_800D27DC.s: 6 relocs,
 * same offsets/symbols/order — HI16+LO16 D_800B9A02 @0x4C/0x50, HI16+LO16 D_800AE7BC
 * @0x18C/0x194 and @0x1D0/0x1D8; the two R_MIPS_26 are the internal j edges.  No jal.
 *
 * BANKING NOTE: src/resident/resident.c already defines file-scope `PTag_800D29F8` and
 * `Env_800D29F8` (structurally identical to the two typedefs below), but it defines them
 * AFTER this function's INCLUDE_ASM site — so the card's `tu=('Env_800D29F8','[]')` row
 * cannot be spelled verbatim here without moving the typedefs.  The typedefs below are
 * renamed to _800D27DC to stay redefinition-free; layout is byte-identical either way.
 */








typedef struct {
    u32 addr : 24;      /* 0x00 tag */
    u32 len  : 8;
} PTag_800D27DC;

typedef struct {
    u32 *ot;            /* 0x00 */
    u32 pad[4];         /* 0x04..0x13 */
} Env_800D27DC;         /* 0x14 stride */

#define OT_800D27DC             (D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot)
#define getaddr_800D27DC(t)     (((PTag_800D27DC *)(t))->addr)
#define setaddr_800D27DC(t, v)  (((PTag_800D27DC *)(t))->addr = (u32)(v))
#define addPrim_800D27DC(ot, p) (setaddr_800D27DC(p, getaddr_800D27DC(ot)), \
                                 setaddr_800D27DC(ot, p))

u8 *func_800D27DC(u32 flags, u8 *out, u16 *src, s16 count, u16 add)
{
    extern Env_800D27DC D_800AE7BC[];
    extern short D_800B9A02;

    s16 i;
    u32 c;
    int o;
    int x, y, w, h, u, v;
    int tw, th, k;
    int f2;

    o = add;
    c = 0x2C808080;
    if (flags & 1) {
        c = 0x2C585858;
    }
    for (i = 0; i < count; i++) {
        f2 = flags & 2;
        *(u32 *)(out + 0x00) = 0x09000000;      /* setlen(out, 9) */
        *(u32 *)(out + 0x04) = c;               /* r0,g0,b0,code = 0x2C */
        x = *src++ + o;
        *(s16 *)(out + 0x18) = x;               /* x2 */
        *(s16 *)(out + 0x08) = x;               /* x0 */
        y = *src++;
        *(s16 *)(out + 0x12) = y;               /* y1 */
        *(s16 *)(out + 0x0A) = y;               /* y0 */
        w = *src++;
        h = *src++;
        u = *src++;
        *(u8 *)(out + 0x0C) = *(u8 *)(out + 0x1C) = u;      /* u0 = u2 */
        v = *src++;
        *(u8 *)(out + 0x0D) = *(u8 *)(out + 0x15) = v;      /* v0 = v1 */
        if (f2 == 0) {
            th = 8;
            *(u16 *)(out + 0x0E) = 0x4056;      /* clut  */
            *(u16 *)(out + 0x16) = 0x15;        /* tpage */
            tw = 8;
            k = i & 7;
            if (k >= 4) {
                if (k < 6) {
                    tw = 7;
                } else if (k < 8) {
                    th = 7;
                }
            }
        } else {
            *(u16 *)(out + 0x0E) = *src++;      /* clut  */
            *(u16 *)(out + 0x16) = *src++;      /* tpage */
            tw = *src++;
            th = *src++;
        }
        *(s16 *)(out + 0x10) = *(s16 *)(out + 0x20) = x + w;    /* x1 = x3 */
        *(s16 *)(out + 0x1A) = *(s16 *)(out + 0x22) = y + h;    /* y2 = y3 */
        *(u8 *)(out + 0x14) = *(u8 *)(out + 0x24) = u + tw;     /* u1 = u3 */
        *(u8 *)(out + 0x1D) = *(u8 *)(out + 0x25) = v + th;     /* v2 = v3 */
        addPrim_800D27DC(&OT_800D27DC[2], out);
        out += 0x28;
    }
    return out;
}


/* func_800D29F8 — MATCH (172 ins). Emit a run of POLY_G4 quads (a gouraud "ladder"/trail
 * strip) into the packet buffer at `out`, bracketed by two 1-word E1 (GP0 draw-mode) packets,
 * addPrim()-ing every packet onto the current double-buffer's OT tag.
 *
 * Source stream `src` is a 0x10-byte record per rung:
 *   +0 u32 c0 | +4 u32 c1 | +8 u16 x | +0xA u16 y | +0xC u16 w | +0xE u16 h
 * Quad verts (X,Y) (X+W,Y) (X,Y+H) (X+W,Y+H); colours c0 / c0-0x280000 / c1+0x280000 / c1
 * (i.e. a +-0x28 blue ramp top-to-bottom). Prim code 0x38 (POLY_G4), |2 = semi-transparent.
 * Rungs are skipped unless `i>>1 == hs`, `i >= 8`, or `i` is odd.
 *
 * FOUR levers, each byte-verified load-bearing (dropping it re-breaks the match):
 *
 *  1. `D_800B9A02` is VOLATILE, and read as `*(volatile u16 *)&D_800B9A02`. Two effects, both
 *     required, and this is also semantically right: it is the double-buffer index flipped by
 *     the VSync IRQ.
 *       (a) volatile => CSE never caches the MEM => the target's SIX separate reloads (two per
 *           addPrim, because the libgpu macro double-evaluates `ot`). Non-volatile collapses
 *           the fn to 158 ins. NB the §30 "deny /s" bare-store lever does NOT substitute here:
 *           once the address is a register with a known-constant quantity, cse.c's
 *           `cse_rtx_varies_p` reports it as NOT varying, so a /s store leaves it cached — only
 *           an `all=1` store or volatile kills it.
 *       (b) the cast-wrapped `*&` cannot be folded back to the VAR_DECL by the front end, so it
 *           takes expr.c's INDIRECT_REF path => `memory_address()` force_regs the constant
 *           address ("by passing constant addresses thru registers we get a chance to cse
 *           them") => `la $t0, D_800B9A02` + `lhu 0($t0)`, and the loop preheader's
 *           `addu $t5,$t0,$zero` (CSE turns the in-loop address into a copy, loop.c hoists it).
 *           A bare `D_800B9A02` returns DECL_RTL via validize_mem => (mem (symbol_ref)) => the
 *           maspsx `lui/lhu` pair instead, and no preheader copy.
 *
 *  2. addPrim is the REAL libgpu bitfield macro (both halves `->addr =`), not hand-written
 *     masks. store_bit_field masks the VALUE (0xFFFFFF) before the DESTINATION (0xFF000000),
 *     which fixes both the constant creation order (=> the LUID tie-break in sched's
 *     `rank_for_schedule` => `lui $a0,0xff00` lands in the load-delay slot at idx21 reusing the
 *     index's dead reg, not hoisted to idx10 needing its own) and the `or` operand order.
 *     Hand-rolled `(*q & 0xff000000) | (ot[2] & 0xffffff)` gets both backwards (37 mismatches).
 *
 *  3. OT_800D29F8 is a MACRO, and `ot` is double-evaluated exactly as libgpu's addPrim does.
 *     A named `ot` local is ONE pseudo for the whole fn (gcc-2.7.2 has no live-range
 *     splitting) => one long-lived reg; the target's base is a per-expression temp ($v0/$v1/$a0).
 *
 *  4. `o = ofs` — an int alias for the u16 param. A u16 param is a PROMOTED SUBREG, so
 *     combine's commutative canonicalisation ("object first, non-object second") swaps
 *     `(plus src_val ofs)` => `addu $a1,$t7,$a1`. Aliasing to a plain int pseudo defeats the
 *     swap => `addu $a1,$a1,$t7`. (This is why `x`/`w` read `*src++ + v` but `h` reads
 *     `y + *src++` — the target's own operand orders, byte-confirmed either way.)
 *
 * Also load-bearing: the y pair is UNCHAINED (`p->y1=y; p->y0=y;`) while x/w/h are chained
 * (`p->a = p->b = v`) — chaining emits store_expr's SImode->HImode truncation copy, which the
 * target has for x only; and `c`/`c2` are separate locals (one shared local pins both colour
 * groups to the same hard reg).
 */

typedef struct {
    u32 addr : 24;      /* 0x00 tag */
    u32 len  : 8;
} PTag_800D29F8;

typedef struct {
    u32 c0;             /* 0x04 r0,g0,b0,code */
    s16 x0, y0;         /* 0x08 */
    u32 c1;             /* 0x0C */
    s16 x1, y1;         /* 0x10 */
    u32 c2;             /* 0x14 */
    s16 x2, y2;         /* 0x18 */
    u32 c3;             /* 0x1C */
    s16 x3, y3;         /* 0x20 */
} PolyG4_800D29F8;      /* 0x24 = tag + 8 words */

typedef struct {
    u32 *ot;            /* 0x00 */
    u32 pad[4];         /* 0x04..0x13 */
} Env_800D29F8;         /* 0x14 stride */

#define OT_800D29F8             (D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot)
#define getaddr_800D29F8(t)     (((PTag_800D29F8 *)(t))->addr)
#define setaddr_800D29F8(t, v)  (((PTag_800D29F8 *)(t))->addr = (u32)(v))
#define addPrim_800D29F8(ot, p) (setaddr_800D29F8(p, getaddr_800D29F8(ot)), \
                                 setaddr_800D29F8(ot, p))

u32 *func_800D29F8(s16 hs, u32 *out, u16 *src, s16 n, u16 ofs)
{
    extern Env_800D29F8 D_800AE7BC[];
    extern short D_800B9A02;

    u32 *q;
    PolyG4_800D29F8 *p;
    s16 i;
    int code;
    u32 c, c2;
    int x, y, w, h;
    int o;

    o = ofs;
    q = out;
    p = (PolyG4_800D29F8 *)((u8 *)q + 4);
    ((u8 *)q)[3] = 1;                       /* setlen(q, 1) */
    p->c0 = 0xE1000000;                     /* GP0 draw-mode: dither off */
    addPrim_800D29F8(&OT_800D29F8[2], q);
    q += 2;

    for (i = 0; i < n; i++) {
        if ((i >> 1) == hs || i >= 8) {
            code = 0;
        } else if (i & 1) {
            code = 2;                       /* ABE: semi-transparent */
        } else {
            src += 8;                       /* skip this rung's 0x10-byte record */
            continue;
        }
        p = (PolyG4_800D29F8 *)((u8 *)q + 4);
        *q = 0x08000000;                    /* tag: len 8, addr 0 */
        c = ((code | 0x38) << 24) | *(u32 *)src;
        src += 2;
        p->c0 = c;
        p->c1 = c - 0x280000;
        c2 = *(u32 *)src;
        src += 2;
        p->c3 = c2;
        p->c2 = c2 + 0x280000;
        x = *src++ + o;
        p->x0 = p->x2 = x;
        y = *src++;
        p->y1 = y;
        p->y0 = y;
        w = *src++ + x;
        h = y + *src++;
        p->x1 = p->x3 = w;
        p->y2 = p->y3 = h;

        addPrim_800D29F8(&OT_800D29F8[2], q);
        q += 9;
    }

    p = (PolyG4_800D29F8 *)((u8 *)q + 4);
    ((u8 *)q)[3] = 1;
    p->c0 = 0xE1000200;                     /* GP0 draw-mode: dither on */
    addPrim_800D29F8(&OT_800D29F8[2], q);
    return q + 2;
}


/* func_800D2CA8(a0, a1): pack a0 into BCD nibbles (LSD first into the low bits),
 * then shift the whole packed result left by a1.
 *
 * asm register model (the discriminating point — keep TWO copies of the value):
 *   t0 = 0          (result)
 *   a2 = a0         (cur — the value compared and used as the modulo minuend)
 *   if (a2 < 10) goto END                ; slti a2,10 ; bnez -> skip loop
 *   a3 = 0          (shift)
 *   LOOP:
 *     a0 = a0 / 10                        ; signed div: mult magic 0x66666667,
 *                                         ;   mfhi; sra v1,2; sra v0(a0),31; subu
 *     t0 |= (a2 - a0*10) << a3            ; a2 - (a0<<1 + a0<<3) = a2 % 10 (OLD a2)
 *     a2 = a0                             ; cur = quotient
 *     a3 += 4
 *     if (a2 >= 10) goto LOOP             ; slti a2,10 ; beqz -> LOOP
 *   END:
 *   t0 |= a2 << a3
 *   return t0 << a1                       ; sllv (variable shift)
 *
 * The prior single-variable `n%10; n/=10` draft conflated a0 and a2 into one
 * register and mis-allocated. Here `cur`(a2) stays the compare/modulo base while
 * `a0` is the divided value; the modulo is derived as `cur - a0*10` (matches the
 * subu order), and `result |= ...` puts result first (or t0,t0,v0; cookbook A1).
 */
s32 func_800D2CA8(s32 a0, s32 a1) {
    s32 result = 0;
    s32 cur = a0;
    s32 shift = 0;

    while (cur >= 10) {
        a0 = a0 / 10;
        result |= (cur - (a0 * 2 + a0 * 8)) << shift;
        cur = a0;
        shift += 4;
    }
    result |= cur << shift;
    return result << a1;
}

void func_800D2D10(val, n, dst, flag)
unsigned int val;
short n;
unsigned short *dst;
short flag;
{
    extern unsigned short *D_800D38D8[];
    register unsigned int d __asm__("$8");
    short i;
    int idx;

    for (i = 0; i < n; i++) {
        d = val >> 28;
        idx = d;
        if (flag != 0) {
            if (d != 0) {
                flag = 0;
            } else if (flag < 0) {
                idx = (i != n - 1) ? 10 : 0;
            } else {
                idx = 10;
            }
        }
        val <<= 4;
        *dst = *D_800D38D8[idx];
        dst++;
    }
}


/* func_800D2DAC(arg0):
 *   func_8016EDEC(func_800D3238, 0x1000000);   ; a0=&func_800D3238, a1=0x1000000
 *   func_800167B8(0);                          ; a0=0 (delay slot)
 *   arg0[0x15]++;                              ; lbu/addiu/sb at +0x15 (u8)
 *   return 0;                                  ; addu v0,zero,zero
 *
 * Mirrors the already-matched func_800D2F48 (call; func_800167B8(0); arg0[0x15]++;
 * return 0). The first arg to func_8016EDEC is a FUNCTION ADDRESS (func_800D3238),
 * so it materialises as lui/addiu %hi/%lo — declare the param as a generic pointer
 * so passing the function name decays to &func_800D3238 with no cast.
 */
extern void func_800D3238(void *arg0);
extern void func_8016EDEC(void *arg0, s32 arg1);
extern void func_800167B8(s32 arg0);

s32 func_800D2DAC(u8 *arg0) {
    func_8016EDEC(func_800D3238, 0x1000000);
    func_800167B8(0);
    arg0[0x15]++;
    return 0;
}

// func_800D2DFC: byte-identical twin of the ALREADY-MATCHED func_800D319C /
// func_800D2EE8 in src/resident/resident.c, differing ONLY in the argument
// (a0 = 0 here vs a0 = 4 there):
//     jal func_800167F0          ; delay slot: addu a0,zero,zero  -> a0 = 0
//     andi v0,v0,0xffff          ; zero-extend the u16 return
//     sltu v0,zero,v0            ; v0 = (0 < v0) = (v0 != 0)
//     return                     ; plain s32 return
//
// FIX vs BOTH prior failed drafts: they declared func_800167F0 as a WIDER type
// (s32/int) and wrote an explicit (u16) cast to "force" the andi. That is wrong
// for THIS binary — the proven matched twins (func_800D319C / func_800D2EE8) declare
// func_800167F0 returning **u16** with NO cast and `!= 0`; gcc still emits the
// andi 0xffff as the natural zero-extend of the u16 return before the sltu. Copy
// that exact form; only the arg changes from 4 to 0.
extern u16 func_800167F0(s32 arg0);

s32 func_800D2DFC(void) {
    return func_800167F0(0) != 0;
}

// func_800D2E20 — body-twin of the MATCHED func_800D3104 (read u8 field_0x15, store
// 0xA at field_0x19, write field_0x15 back, return 0), with a LEADING call
// func_8016EDEC(func_800D3348, 0x1000000). The incoming a0 is the field base; it is
// saved into the callee-saved s0 across that call (asm: `addu s0,a0,zero`), so it must
// stay live across the call and be dereferenced AFTER.
//
// Proven idioms reused:
//   - func_8016EDEC declared (void *arg0, s32 arg1), passing the function name
//     func_800D3348 directly (decays to its address; matches func_800D2DAC / func_800D33B8).
//   - struct-pointer field access with u8 fields (lbu/sb) like func_800D3104.
//   - store order: field_0x19 = 0xA  THEN  field_0x15 = v+1  (asm sb 0x19 before sb 0x15);
//     gcc hoists the lbu 0x15.

extern void func_800D3348(u8 *arg0);
extern void func_8016EDEC(void *arg0, s32 arg1);

typedef struct {
    u8 pad15[0x15];
    u8 field_0x15;  /* 0x15 */
    u8 pad16[0x3];
    u8 field_0x19;  /* 0x19 */
} Struct800D2E20;

s32 func_800D2E20(Struct800D2E20 *a0) {
    func_8016EDEC(func_800D3348, 0x1000000);
    a0->field_0x19 = 0xA;
    a0->field_0x15 = a0->field_0x15 + 1;
    return 0;
}

/* func_800D2E6C(arg0) — byte-identical to the MATCHED func_800D3120 (resident.c:1179).
 * Countdown trigger on a u8 field at +0x19 of arg0 (kept in s0).
 *   v1 = arg0->field_0x19          ; lbu (u8)
 *   v0 = v1 + 0xFF                  ; addiu v0,v1,0xFF  (IMMEDIATE 0x00FF, +255)
 *   bnez v1, .L800D2ED0            ; if (v1 != 0) skip
 *     sb v0,0x19(s0)               ; (delay) store wrapped value UNCONDITIONALLY
 *   ; v1 == 0 -> work; arg0->field_0x15++; return 0
 *
 * The decrement is written `v + 0xFF` (not `v--`) so the QImode constant is the positive
 * +0xFF gcc emits, and the branch tests the OLD value v.
 */
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8001BFD0(void);
extern void func_800D0C48(u16 arg0);
extern void func_800167B8(s32 arg0);

typedef struct {
    u8 pad00[0x15];    /* 0x00..0x14 */
    u8 field_0x15;     /* 0x15 */
    u8 pad16[0x3];     /* 0x16..0x18 */
    u8 field_0x19;     /* 0x19 */
} Struct800D2E6C;

s32 func_800D2E6C(Struct800D2E6C *arg0) {
    u8 v = arg0->field_0x19;
    arg0->field_0x19 = v + 0xFF;
    if (v == 0) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800167B8(4);
        arg0->field_0x15++;
    }
    return 0;
}

// ANALYSIS: identical asm shape to the ALREADY-MATCHED func_800D319C in
// src/resident/resident.c:
//     jal func_800167F0 (a0=4); andi v0,v0,0xffff; sltu v0,zero,v0; return.
// The proven matched form declares func_800167F0 as returning u16 (so the
// andi 0xffff is the natural zero-extend of the return) and writes `!= 0`
// (sltu zero,v0 = "0 < v0" = v0 != 0). The prior draft declared it s32 and
// added an explicit (u16) cast; copy the proven u16-return form instead.
extern u16 func_800167F0(s32 arg0);

s32 func_800D2EE8(void) {
    return func_800167F0(4) != 0;
}

extern void (*D_800D39C4[])(void);

void func_800D2F0C(u8 *arg0) {
    D_800D39C4[arg0[0x15]]();
}

extern void func_800D33B8(void);
extern void func_800167B8(s32 arg0);

s32 func_800D2F48(u8 *arg0) {
    func_800D33B8();
    func_800167B8(0);
    arg0[0x15]++;
    return 0;
}

// ANALYSIS: byte-identical asm SHAPE to the ALREADY-MATCHED twins func_800D319C and
// func_800D2EE8 in src/resident/resident.c:
//     jal func_800167F0 (a0=0); andi v0,v0,0xffff; sltu v0,zero,v0; jr ra
// The ONLY difference vs the twins is a0 = 0 here (they pass 4).
//
// PRIOR-DRAFT BUG: it declared func_800167F0 as `s32` and wrote `(u16)func_800167F0(0) != 0`.
// The proven matched form declares the callee as RETURNING u16 — then the `andi v0,0xffff`
// is the NATURAL zero-extend of the u16 return value (no explicit (u16) cast), and
// `!= 0` lowers to `sltu v0,zero,v0` (0 < v0). With an s32 return + explicit cast, gcc
// schedules the andi differently / can drop it. Copy the twins verbatim.
extern u16 func_800167F0(s32 arg0);

s32 func_800D2F8C(void) {
    return func_800167F0(0) != 0;
}

extern void (*D_800D39F0[])(void);

void func_800D2FB0(u8 *arg0) {
    D_800D39F0[arg0[0x15]]();
}

// ANALYSIS: jal func_800D33E0() (void — the delay-slot `addu s0,a0,zero` SAVES the
// incoming a0 across the call, it is NOT an argument to the call; ref source declares
// func_800D33E0(void)). a0 = struct/byte-base pointer kept in s0.
// Then: read u8 field 0x15; store s32 0xA at 0x28; field_0x15 = v+1; return 0.
// Mirrors the matched func_800D3104 shape (read field, store const, write field back, ret 0),
// only differing by the leading call + a sw(0x28)=0xA instead of sb(0x19)=0xA.
//
// PRIOR-DRAFT BUG: it passed arg0 to func_800D33E0 (`func_800D33E0(arg0)`), but the asm
// shows a0 merely COPIED to the callee-saved s0 in the jal delay slot — the call takes no
// args. Declaring it (void) and keeping arg0 live in a local emits the exact `addu s0,a0,$0`.
extern void func_800D33E0(void);

typedef struct {
    u8 pad00[0x15];
    u8 field_0x15;   /* 0x15 */
    u8 pad16[0x12];
    s32 field_0x28;  /* 0x28 */
} Struct800D2FEC;

s32 func_800D2FEC(Struct800D2FEC *a0) {
    func_800D33E0();
    a0->field_0x28 = 0xA;
    a0->field_0x15 = a0->field_0x15 + 1;
    return 0;
}

// ANALYSIS: twin of the ALREADY-MATCHED func_800D2FEC (resident.c:~862): same struct
// (u8 field at 0x15, s32 field at 0x28), same "do work then field_0x15++; return 0" tail.
//   s0 = a0 (struct ptr).
//   v0 = field_0x28 - 1;  field_0x28 = v0;          (the `sw v0,0x28(s0)` is in the bne
//                                                     delay slot -> the store ALWAYS runs)
//   if (v0 == -1) {                                  (bne v0,-1 -> skip when != -1; the -1
//                                                     constant is materialized in v1 first)
//       func_8002D4C8(0x1C, 0);
//       func_8001BFD0();
//       func_8002D4C8(0x1D, 0);
//       func_800D0C48(1);                            (one arg = 1: `addiu a0,zero,1`)
//       func_800D1E28();
//       field_0x15 = field_0x15 + 1;                 (lbu/addiu/sb at 0x15, u8)
//   }
//   return 0;                                        (addu v0,zero,zero at the shared tail)
//
// All callees are void/no-mask at their call sites (no `andi v0,0xffff` after any jal), so
// no callee-return-width subtlety here. func_8002D4C8 is (s32,s32) (matches resident.c).
// The work is in the if-body and `return 0` is the shared fall-through epilogue (.L800D3090),
// which is exactly the branch polarity gcc picks for `if (v == -1) {...} return 0;`.

extern void func_8002D4C8(s32, s32);
extern void func_8001BFD0(void);
extern void func_800D0C48(u16 arg0);
extern void func_800D1E28(void);

typedef struct {
    u8  pad00[0x15];
    u8  field_0x15;   /* 0x15 */
    u8  pad16[0x12];
    s32 field_0x28;   /* 0x28 */
} Obj800D302C;

s32 func_800D302C(Obj800D302C *arg0) {
    s32 v;

    v = arg0->field_0x28 - 1;
    arg0->field_0x28 = v;
    if (v == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        arg0->field_0x15 = arg0->field_0x15 + 1;
    }
    return 0;
}

extern s32 func_800D1EBC(void);

void func_800D30A8(void) {
    func_800D1EBC();
}

extern void (*D_800D3A8C[])(void);

void func_800D30C8(void *arg0) {
    D_800D3A8C[*(u8 *)((u8 *)arg0 + 0x15)]();
}

/* func_800D3104: a0 is a struct pointer.
 *   lbu v0, 0x15(a0)        -> read u8 at +0x15
 *   addiu v1, zero, 0xA     -> 10
 *   sb v1, 0x19(a0)         -> store 10 at +0x19
 *   addiu v0, v0, 1         -> +1
 *   sb v0, 0x15(a0)         -> store back at +0x15
 *   return 0
 */
typedef struct {
    u8 pad15[0x15];
    u8 field_0x15;
    u8 pad16[0x3];
    u8 field_0x19;
} Struct800D3104;

s32 func_800D3104(Struct800D3104 *a0) {
    u8 v = a0->field_0x15;
    a0->field_0x19 = 0xA;
    a0->field_0x15 = v + 1;
    return 0;
}

// func_800D3120 (byte-identical to the also-unmatched func_800D2E6C):
// countdown trigger on a u8 field at +0x19 of arg0 (kept in s0).
//   v1 = arg0->field_0x19          ; lbu (u8)
//   v0 = v1 + 0xFF                  ; addiu v0,v1,0xFF  <-- IMMEDIATE 0x00FF, +255
//   bnez v1, .L800D3184            ; if (v1 != 0) skip the work
//     sb v0,0x19(s0)               ; (delay slot) store the wrapped value UNCONDITIONALLY
//   ; v1 == 0 -> do the work:
//     func_8002D4C8(0x1C, 0); func_8001BFD0(); func_8002D4C8(0x1D, 0);
//     func_800D0C48(1); func_800167B8(4);
//     arg0->field_0x15++           ; lbu/addiu 1/sb  (u8)
//  .L800D3184: return 0
//
// FIX vs BOTH prior drafts: they wrote `p->field_0x19-- == 0`. A u8 post-decrement
// promotes to int, so `-1` is emitted as `addiu v0,v1,0xFFFF` (immediate 0xFFFF) —
// but the asm shows `addiu v0,v1,0xFF` (immediate 0x00FF = +255). gcc renders the
// constant as a positive +0xFF, which only happens when the source ADDS 0xFF, not
// subtracts 1. So write `v + 0xFF` (the byte-wrapping decrement) explicitly and test
// the OLD value `v` for the branch. Stored via sb so the byte result == v-1 mod 256.
// func_800D0C48 is u16-arg per resident.c:440; the others match resident.c sigs.
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8001BFD0(void);
extern void func_800D0C48(u16 arg0);
extern void func_800167B8(s32 arg0);

typedef struct {
    u8 pad00[0x15];    /* 0x00..0x14 */
    u8 field_0x15;     /* 0x15 */
    u8 pad16[0x3];     /* 0x16..0x18 */
    u8 field_0x19;     /* 0x19 */
} Struct800D3120;

s32 func_800D3120(Struct800D3120 *arg0) {
    u8 v = arg0->field_0x19;
    arg0->field_0x19 = v + 0xFF;
    if (v == 0) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800167B8(4);
        arg0->field_0x15++;
    }
    return 0;
}

extern u16 func_800167F0(s32 arg0);

s32 func_800D319C(void) {
    return func_800167F0(4) != 0;
}

extern void (*D_800D3920[])(void);

void func_800D31C0(u8 *arg0) {
    D_800D3920[arg0[0x15]]();
}

extern void (*D_800D3928[])(void);

void func_800D31FC(u8 *arg0) {
    D_800D3928[arg0[0x15]]();
}

// ANALYSIS: idx = *(u8*)(arg+0x214); fp = D_800D3A98[idx]; fp(arg).
// Function-pointer table dispatch; a0 (arg) preserved into the jalr.
extern void (*D_800D3A98[])();

void func_800D3238(void *arg0) {
    D_800D3A98[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern s32 func_8013767C(s32);

void func_800D3274(u8 *arg0) {
    s32 w = *(s32 *)(arg0 + 0x198);
    if (w != 0) {
        *(s32 *)(arg0 + 0x198) = func_8013767C(w);
        *(u8 *)(arg0 + 0x214) = *(u8 *)(arg0 + 0x214) + 1;
    } else {
        *(u8 *)(arg0 + 0x214) = *(u8 *)(arg0 + 0x214) + 2;
    }
}

extern s32 func_801399F0(s32);
extern void func_80139914(s32);

void func_800D32D4(void *arg0) {
    if (func_801399F0(*(s32 *)((u8 *)arg0 + 0x198)) != 0) {
        func_80139914(*(s32 *)((u8 *)arg0 + 0x198));
        *(u8 *)((u8 *)arg0 + 0x214) += 1;
    }
}

extern void func_8016F0E4(void);

void func_800D3328(void) {
    func_8016F0E4();
}

extern void (*D_800D3AA4[])(void);

void func_800D3348(u8 *arg0) {
    D_800D3AA4[*(u8 *)(arg0 + 0x214)]();
}

void func_800D3384(u8 *arg0) {
    *(u8 *)(arg0 + 0x214) += 1;
}

extern void func_8016F0E4(void);

void func_800D3398(void) {
    func_8016F0E4();
}

/* func_800D33B8 — exact mirror of the already-MATCHED func_800D33E0
 * (src/resident/resident.c:827), differing only in the global it passes
 * (&D_800D3AAC here vs &D_800D3AB0 there). func_8016EE40 takes (u8*, s32).
 * asm: lui/addiu a0=&D_800D3AAC ; jal func_8016EE40 ; lui a1=0x1000000 (delay). */
extern u8 D_800D3AAC;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_800D33B8(void) {
    func_8016EE40(&D_800D3AAC, 0x1000000);
}

extern u8 D_800D3AB0;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_800D33E0(void) {
    func_8016EE40(&D_800D3AB0, 0x1000000);
}

