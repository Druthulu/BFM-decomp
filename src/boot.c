#include "common.h"


/* start (0x80010000) -- crt0 entry, HANDWRITTEN assembly (splat marks it
 * "Handwritten function"; the body's `addi` is flagged "handwritten instruction"
 * -- gcc-2.7.2 never emits the trapping add -- and the 8-byte alignment is done
 * with an sll/srl roundabout). Semantics: zero the bss (D_80074750..D_800C7F08),
 * build the initial stack pointer from heap-top D_800629BC - 8 forced into
 * kseg0 via or 0x80000000, 8-align the bss end D_800C7F08, subtract the game
 * footprint D_800629C0, publish the bounds to D_800629A0/D_8006299C, park $ra,
 * load $gp, call main(). Return from main traps (break 1).
 * Reproduced verbatim per cookbook §261 lane 2 (file-scope __asm__); immediates
 * decimal because maspsx rejects hex literals inside __asm__ strings, the trap
 * is spelled `break 1` because maspsx cannot parse the two-operand form, and
 * sltu is written with bare commas because maspsx mis-parses ", " operands.
 * This artifact REPLACES the single INCLUDE_ASM("asm/nonmatchings/boot", start)
 * stub in src/boot.c -- nothing else in the TU changes. */
__asm__(".text\n"
        ".align 2\n"
        ".globl start\n"
        ".ent\tstart\n"
        "start:\n"
        ".set\tnoreorder\n"
        "lui $v0, %hi(D_80074750)\n"
        "addiu $v0, $v0, %lo(D_80074750)\n"
        "lui $v1, %hi(D_800C7F08)\n"
        "addiu $v1, $v1, %lo(D_800C7F08)\n"
        ".L80010010:\n"
        "sw $zero, 0($v0)\n"
        "addiu $v0, $v0, 4\n"
        "sltu $at,$v0,$v1\n"
        "bnez $at, .L80010010\n"
        "nop\n"
        "lui $v0, %hi(D_800629BC)\n"
        "lw $v0, %lo(D_800629BC)($v0)\n"
        "nop\n"
        "addi $v0, $v0, -8\n"
        "lui $t0, 32768\n"
        "or $sp, $v0, $t0\n"
        "lui $a0, %hi(D_800C7F08)\n"
        "addiu $a0, $a0, %lo(D_800C7F08)\n"
        "sll $a0, $a0, 3\n"
        "srl $a0, $a0, 3\n"
        "lui $v1, %hi(D_800629C0)\n"
        "lw $v1, %lo(D_800629C0)($v1)\n"
        "nop\n"
        "subu $a1, $v0, $v1\n"
        "subu $a1, $a1, $a0\n"
        "lui $at, %hi(D_800629A0)\n"
        "sw $a1, %lo(D_800629A0)($at)\n"
        "or $a0, $a0, $t0\n"
        "lui $at, %hi(D_8006299C)\n"
        "sw $a0, %lo(D_8006299C)($at)\n"
        "lui $at, %hi(D_80074750)\n"
        "sw $ra, %lo(D_80074750)($at)\n"
        "lui $gp, %hi(_gp)\n"
        "addiu $gp, $gp, %lo(_gp)\n"
        "addu $fp, $sp, $zero\n"
        "lui $ra, %hi(D_80074750)\n"
        "lw $ra, %lo(D_80074750)($ra)\n"
        "nop\n"
        "jal main\n"
        "nop\n"
        "break 1\n"
        ".set\treorder\n"
        ".end\tstart\n");

void start(void);

/* __main (0x800100A0) -- crt0 constructor-runner, HANDWRITTEN assembly.
 * Replaces the boot __main stub line in src/boot.c IN PLACE (order preserved:
 * lands right after the `start` artifact, before __do_global_dtors). Same
 * lane-2 file-scope __asm__ form already byte-gated in this TU for `start`,
 * and used by banked StopRCnt/gfx2D_BG0_OBJ_658/FGO_06_OBJ_64/func_800D0440
 * elsewhere in the tree. Per cookbook §265: ship NO C externs/prototype with
 * the file-scope form -- the asm resolves symbols at link time; a guessed
 * decl for a crt-reserved name is pure conflict risk.
 *
 * WHY ASM, NOT C: this TU builds -O0 per-file (the boot.c precedent), but
 * __main's target bytes are -O2/handwritten-shaped code (loop state held in
 * $s0/$s1 across the call, delay slots filled, zero local spill/reload) --
 * no C body in this TU can produce them (a C draft compiles to 47 spilled
 * -O0 insns).
 *
 * RECOVERED SEMANTICS (for the eventual real decomp):
 *   static int done;              // D_80062998
 *   void __main(void) {
 *       if (!done) {
 *           done = 1;
 *           int *p = (int *)&start;   // init-array base
 *           int n = 3;                // count ships as literal zeros in the
 *                                     // target (splat renders `lui $s1,(0x0>>16)`
 *                                     // / `addiu $s1,$s1,0x0` -- its display of a
 *                                     // bare 32-bit literal, cf. `(0x80000000 >> 16)`
 *                                     // for raw 0080033C); emitted as plain zero
 *                                     // immediates, byte-identical, no relocation
 *           do { ((void (*)(void))*p)(); p++; n--; } while (n != 0);
 *       }
 *   }
 * Maspsx rules honored per the start artifact: decimal immediates only,
 * .set noreorder with explicit delay-slot nops, .ent/.end wrappers. */
__asm__(".text\n"
        ".align 2\n"
        ".globl __main\n"
        ".ent\t__main\n"
        "__main:\n"
        ".set\tnoreorder\n"
        "lui $t0, %hi(D_80062998)\n"
        "lw $t0, %lo(D_80062998)($t0)\n"
        "addiu $sp, $sp, -16\n"
        "sw $s0, 4($sp)\n"
        "sw $s1, 8($sp)\n"
        "sw $ra, 12($sp)\n"
        "bnez $t0, .L800100F8\n"
        "ori $t0, $zero, 1\n"
        "lui $at, %hi(D_80062998)\n"
        "sw $t0, %lo(D_80062998)($at)\n"
        "lui $s0, %hi(start)\n"
        "addiu $s0, $s0, %lo(start)\n"
        "lui $s1, 0\n"
        "addiu $s1, $s1, 0\n"
        "beqz $s1, .L800100F8\n"
        "nop\n"
        ".L800100E0:\n"
        "lw $t0, 0($s0)\n"
        "addiu $s0, $s0, 4\n"
        "jalr $t0\n"
        "addiu $s1, $s1, -1\n"
        "bnez $s1, .L800100E0\n"
        "nop\n"
        ".L800100F8:\n"
        "lw $ra, 12($sp)\n"
        "lw $s1, 8($sp)\n"
        "lw $s0, 4($sp)\n"
        "addiu $sp, $sp, 16\n"
        "jr $ra\n"
        "nop\n"
        ".set\treorder\n"
        ".end\t__main\n");

__asm__(".text\n"
        ".align 2\n"
        ".globl __do_global_dtors\n"
        ".ent\t__do_global_dtors\n"
        "__do_global_dtors:\n"
        ".set\tnoreorder\n"
        "lui $t0, %hi(D_80062998)\n"
        "lw $t0, %lo(D_80062998)($t0)\n"
        "addiu $sp, $sp, -16\n"
        "sw $s0, 4($sp)\n"
        "sw $s1, 8($sp)\n"
        "sw $ra, 12($sp)\n"
        "beqz $t0, .L80010160\n"
        "nop\n"
        "lui $s0, %hi(start)\n"
        "addiu $s0, $s0, %lo(start)\n"
        "lui $s1, 0\n"
        "addiu $s1, $s1, 0\n"
        "beqz $s1, .L80010160\n"
        "nop\n"
        ".L80010148:\n"
        "lw $t0, 0($s0)\n"
        "addiu $s0, $s0, 4\n"
        "jalr $t0\n"
        "addiu $s1, $s1, -1\n"
        "bnez $s1, .L80010148\n"
        "nop\n"
        ".L80010160:\n"
        "lw $ra, 12($sp)\n"
        "lw $s1, 8($sp)\n"
        "lw $s0, 4($sp)\n"
        "addiu $sp, $sp, 16\n"
        "jr $ra\n"
        "nop\n"
        ".set\treorder\n"
        ".end\t__do_global_dtors\n");

INCLUDE_ASM("asm/nonmatchings/boot", main);

void func_8001096C(void) {
    extern void func_8002CDD8(void);
    func_8002CDD8();
}


extern s32 VSync(s32);
extern u8 D_800AF630[];
extern s32 D_800AE810[];

void func_8001099C(void) {
    register u8 *p = D_800AF630;
    D_800AE810[*(u16 *)(p + 0xA3D2)] = VSync(1);
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80010A08);

extern void DrawSyncCallback(void (*func)(void));
extern void func_80042610(void (*func)(void));
extern void func_8001099C(void);
extern void func_8001096C(void);

void func_80010A98(void) {
    DrawSyncCallback(func_8001099C);
    func_80042610(func_8001096C);
}

void func_80010AE0(s32 arg0) {
    extern s32 D_80074778;
    D_80074778 = arg0;
}

s32 func_80010B10(void) {
    extern s32 D_80074778;
    return D_80074778;
}

/* (*gameModeHandlerTable[gameMode])() — 18 handlers @0x800629F4 (entry [7] =
 * DebugMenuHandler). gameMode is a u16 at D_800AF630 + 0xA3AE (= 0x800B99DE) in the
 * main state block. NOTE: `register` is REQUIRED to match — at -O0 (this module) it
 * keeps the struct base in a callee-saved reg with no stack spill, and the 0xA3AE
 * (>0x7FFF) member offset then assembles to the +0x10000/-0x5C52 split. */
extern void (*gameModeHandlerTable[])(void);
extern u8 D_800AF630[];
void GameModeDispatch(void) {
    register u8 *p = D_800AF630;
    gameModeHandlerTable[*(u16 *)(p + 0xA3AE)]();
}

extern u8 D_800AF630[];
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_80029690(void);
extern void func_80018FC8(void);
extern void func_8001903C(void);
extern void func_80029274(void);
extern void func_8002941C(void);
extern void func_80010AE0(s32);
extern void func_80011B7C(s32);
extern void func_80011778(void);
extern s16 D_801150D4;
extern s32 D_80074784;

void func_80010BB4(void) {
    register u8 *p = D_800AF630;

    *(p + 0xA3E0) = 0;
    *(p + 0xA3E1) = 1;
    *(p + 0xA434) = 0;
    func_8001C044();
    func_80015310();
    func_80029690();
    D_801150D4 = 0;
    D_80074784 = 0;
    func_80018FC8();
    func_8001903C();
    func_80029274();
    func_8002941C();
    func_80010AE0(0x3E0);
    func_80011B7C(0);
    func_80011778();
}

extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern u8 D_800AE838;
extern void *loadDestPtrTable;

void func_80010C7C(void) {
    int iVar1;

    iVar1 = CdReadRequest(&D_800AE838, loadDestPtrTable, 0, 0);
    if (iVar1 != 0) {
        func_80010AE0(0x3E0);
        func_80011778();
    }
}

extern u8 D_800AF630[];
extern void func_800CEDFC(void);
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_80011818(s32);

void func_80010CEC(void) {
    register u8 *p = D_800AF630;

    func_800CEDFC();
    if (*(u16 *)(p + 0xA3B6) != 0) {
        func_8001C044();
        func_80015310();
        func_80011818(3);
    }
}

void func_80010D60(void) {
    func_80010AE0(0x3E0);
    func_80011818(5);
}

extern u8 D_800AF630[];
extern void func_80011778(void);

void func_80010DA0(void) {
    register u8 *p = D_800AF630;
    func_80011778();
}

extern void func_80011818(s32);

void func_80010DE0(void) {
    func_80011818(5);
}

extern void func_80011818(s32);

void func_80010E14(void) {
    func_80011818(0xD);
}

extern void func_80011818(s32);

void func_80010E48(void) {
    func_80011818(0xC);
}

extern u8 D_800AF630[];
extern void func_8002D4C8(s32, s32);

void func_80010E7C(void) {
    register u8 *p = D_800AF630;

    func_8002D4C8(2, 0);
    *(u16 *)(p + 0xA3D4) = 1;
}

extern s32 D_800C7C60;
extern void *D_800C7C64;
extern u8 D_800A2E20[];
extern u8 D_800AE848[];
extern void *loadDestPtrTable;
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_8002D4C8(s32, s32);
extern void func_80010AE0(int);
extern void func_80014338(void);
extern void func_800116E0(void);
extern void func_80011778(void);
extern s16 D_800B99DA;

void func_80010ED4(void) {
    D_800C7C60 = 0x57;
    D_800C7C64 = D_800A2E20;
    if (CdReadRequest(D_800AE848, loadDestPtrTable, 0, &D_800C7C60) != 0) {
        func_8002D4C8(2, 0);
        func_80010AE0(0x3E0);
        func_80014338();
        func_800116E0();
        D_800B99DA = 0;
        func_80011778();
    }
}


extern void func_800CEEC8(void);
extern void func_80011B7C(s32);
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_80011818(s32);
extern void func_80029514(s32);
extern u8 D_800AF630[];
extern u8 D_80078E78[];
extern s32 D_800629C8;

void func_80010F80(void) {
    register u8 *p = D_800AF630;
    u8 *sp10 = D_80078E78;
    func_800CEEC8();
    if (*(u16 *)(p + 0xA3B6) != 0) {
        func_80011B7C(0);
        func_8001C044();
        func_80015310();
        if (*(s16 *)(p + 0xA3B8) == 4) {
            *(u8 *)(p + 0xA434) = 1;
            func_80011818(0xF);
        } else if (*(s16 *)(p + 0xA3B8) < 2) {
            *(s16 *)(p + 0xA3D8) = 0x3005;
            *(s16 *)(p + 0xA3DA) = 0x3000;
            func_80029514(D_800629C8);
            if (*(s16 *)(p + 0xA3B8) == 1) {
                func_80011818(0xA);
                func_80011B7C(0xB);
            } else {
                func_80011818(0xA);
            }
        }
    }
    (void)sp10;
}

extern void func_8001A9F8(int);
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80010AE0(int);
extern void func_80011778(void);
extern void func_80015310(void);
extern u8 D_800AE880;
extern void *loadDestPtrTable;

void func_800110CC(void) {
    int iVar1;
    func_8001A9F8(0);
    if (CdReadRequest(&D_800AE880, loadDestPtrTable, 0, 0) != 0) {
        func_80010AE0(0x3E0);
        func_80011778();
        func_80015310();
    }
    (void)iVar1;
}

extern void func_8001A9F8(int);
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80010AE0(int);
extern void func_80011778(void);
extern void func_80015310(void);
extern u8 D_800AE888;
extern void *loadDestPtrTable;
/* gameMode 7 handler (gameModeHandlerTable[7]) — the TCRF L3 debug menu. Streams the
 * room-select overlay (cdFileLocTable[11] -> 0x800CEDF8) via CdReadRequest, then inits it
 * (func_80011778 / func_80015310). Retail: only room-select works. Phase 3 T8. */
void DebugMenuHandler(void) {
    int iVar1; /* -O0 reserves this local's 8-byte slot (frame 0x20); the original
                * checks CdReadRequest's result directly (no store) — assigning iVar1
                * here would emit a store the target lacks, so it stays declaration-only. */
    func_8001A9F8(0);
    if (CdReadRequest(&D_800AE888, loadDestPtrTable, 0, 0) != 0) {
        func_80010AE0(0x3E0);
        func_80011778();
        func_80015310();
    }
    (void)iVar1;
}

extern u8 D_800AF630[];
extern void func_800CEE74(void);
extern void func_80011818(s32);

void func_800111BC(void) {
    register u8 *p = D_800AF630;

    func_800CEE74();
    if (*(u16 *)(p + 0xA3B6) != 0) {
        func_80011818(0xA);
    }
}

extern void func_80011778(void);
extern void func_80011B7C(s32);

void func_80011220(void) {
    func_80011778();
    func_80011B7C(0);
}

extern u8 D_800AF630[];
extern void func_800CEDFC(void);

void func_8001125C(void) {
    register u8 *p = D_800AF630;

    *(p + 0xA434) = 0;
    func_800CEDFC();
}

void func_800112A8(void) {
}

INCLUDE_ASM("asm/nonmatchings/boot", func_800112C8);

extern u8 D_800AF630[];
extern void func_800CEDFC(void);

void func_80011320(void) {
    func_800CEDFC();
}

extern s32 D_80074784;

s32 func_80011350(void) {
    return D_80074784;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80011380);

extern u8 D_800AF630[];
extern void func_8002D4C8(s32, s32);
extern void func_80011818(s32);

void func_80011680(void) {
    register u8 *p = D_800AF630;

    *(p + 0xA434) = 0;
    func_8002D4C8(0x29, 0);
    func_80011818(5);
}

INCLUDE_ASM("asm/nonmatchings/boot", func_800116E0);

extern u8 D_800AF630[];

void func_80011778(void) {
    register u8 *p = D_800AF630;

    (*(u16 *)(p + 0xA3AE))++;
    *(u16 *)(p + 0xA3B4) = 0;
    *(u16 *)(p + 0xA3BA) = 0;
    *(u16 *)(p + 0xA3B8) = 0;
    *(u16 *)(p + 0xA3BE) = 0;
    *(u16 *)(p + 0xA3B0) = 0;
    *(u16 *)(p + 0xA3B6) = 0;
    *(u16 *)(p + 0xA3BC) = 0;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80011818);

extern u8 D_800AF630[];

void func_800118AC(void) {
    register u8 *p = D_800AF630;

    (*(u16 *)(p + 0xA3B4))++;
    *(u16 *)(p + 0xA3BA) = 0;
    *(u16 *)(p + 0xA3BE) = 0;
    *(u16 *)(p + 0xA3B6) = 0;
    *(u16 *)(p + 0xA3BC) = 0;
}

extern u8 D_800AF630[];

void func_80011928(u16 arg0) {
    register u8 *p = D_800AF630;

    *(u16 *)(p + 0xA3B4) = arg0;
    *(u16 *)(p + 0xA3BA) = 0;
    *(u16 *)(p + 0xA3BE) = 0;
    *(u16 *)(p + 0xA3B6) = 0;
    *(u16 *)(p + 0xA3BC) = 0;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80011998);

extern u8 D_800AF630[];

void func_800119F0(u16 arg0) {
    register u8 *p = D_800AF630;
    *(u16 *)(p + 0xA3BA) = arg0;
    *(u16 *)(p + 0xA3BC) = 0;
}

extern u8 D_800AF630[];

void func_80011A3C(void) {
    register u8 *p = D_800AF630;
    register u16 x;

    x = *(u16 *)(p + 0xA3C0);
    x = x + 1;
    *(u16 *)(p + 0xA3C0) = x;
    *(u16 *)(p + 0xA3C6) = 0;
    *(u16 *)(p + 0xA3CC) = 0;
    *(u16 *)(p + 0xA3CA) = 0;
    *(u16 *)(p + 0xA3D0) = 0;
    *(u16 *)(p + 0xA3C2) = 0;
    *(u16 *)(p + 0xA3C8) = 0;
    *(u16 *)(p + 0xA3CE) = 0;
}

extern u8 D_800AF630[];

void func_80011ADC(void) {
    register u8 *p = D_800AF630;

    --*(u16 *)(p + 0xA3C0);
    *(u16 *)(p + 0xA3C6) = 0;
    *(u16 *)(p + 0xA3CC) = 0;
    *(u16 *)(p + 0xA3CA) = 0;
    *(u16 *)(p + 0xA3D0) = 0;
    *(u16 *)(p + 0xA3C2) = 0;
    *(u16 *)(p + 0xA3C8) = 0;
    *(u16 *)(p + 0xA3CE) = 0;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80011B7C);

extern u8 D_800AF630[];

void func_80011C10(void) {
    register u8 *p = D_800AF630;
    register u16 gameMode;

    gameMode = *(u16 *)(p + 0xA3C6);
    gameMode += 1;
    *(u16 *)(p + 0xA3C6) = gameMode;
    *(u16 *)(p + 0xA3CC) = 0;
    *(u16 *)(p + 0xA3D0) = 0;
    *(u16 *)(p + 0xA3C8) = 0;
    *(u16 *)(p + 0xA3CE) = 0;
}

extern u8 D_800AF630[];

void func_80011C8C(u16 arg0) {
    register u8 *p = D_800AF630;

    *(u16 *)(p + 0xA3C6) = arg0;
    *(u16 *)(p + 0xA3CC) = 0;
    *(s16 *)(p + 0xA3D0) = 0;
    *(u16 *)(p + 0xA3C8) = 0;
    *(u16 *)(p + 0xA3CE) = 0;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80011CFC);

extern u8 D_800AF630[];

void func_80011D54(u16 arg0) {
    register u8 *p = D_800AF630;

    *(u16 *)(p + 0xA3CC) = arg0;
    *(u16 *)(p + 0xA3CE) = 0;
}

extern s32 D_80074780;

void func_80011DA0(void) {
    D_80074780 = 1;
}

extern s32 D_80074780;

void func_80011DCC(void) {
    D_80074780 = 0;
}

extern s32 D_80074780;

s32 func_80011DF4(void) {
    return D_80074780;
}

INCLUDE_ASM("asm/nonmatchings/boot", func_80011E24);

void func_80011E84(s32 a0) {
    extern s32 D_80074790;
    D_80074790 = a0;
}

void func_80011EB4(void) {
    extern s32 D_800629D0;
    extern s32 D_80074788;
    extern s32 D_80074790;
    extern u16 D_80074794;
    extern u16 D_80074798;
    extern s32 func_80014B10(s32 a0);
    extern s32 func_800149E0(s32 a0);
    u16 local;

    switch (D_800629D0) {
    case 0:
        local = func_80014B10(0);
        *(u16 *)(0x80700000 + D_80074788 * 2) = local;
        D_80074788++;
        local = func_800149E0(0);
        *(u16 *)(0x80700000 + D_80074788 * 2) = local;
        D_80074788++;
        break;
    case 1:
        if (D_80074790 != 0) {
            D_80074794 = *(u16 *)(D_80074790 + D_80074788++ * 2);
            D_80074798 = *(u16 *)(D_80074790 + D_80074788++ * 2);
        } else {
            D_80074794 = 0;
            D_80074798 = 0;
        }
        break;
    case 2:
        D_80074794 = *(u16 *)(0x80700000 + D_80074788++ * 2);
        D_80074798 = *(u16 *)(0x80700000 + D_80074788++ * 2);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/boot", func_800120DC);

INCLUDE_ASM("asm/nonmatchings/boot", func_8001212C);
