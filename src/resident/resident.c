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
    int loc[2];
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
    u8 *p = D_800AF630;
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
    u8 *p = D_800AF630;
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
    u8 *p = D_800AF630;
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

    u8 *base;
    register s32 mode __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus10)
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
        __asm__("" : "=r"(q) : "0"(q));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus10)
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
