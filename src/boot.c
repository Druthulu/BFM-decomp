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


extern u8  D_800BA118;
extern u8  D_800AF630[];
extern s32 D_80074778;
extern s32 D_800A2B7C;
extern s32 D_800C7C70;
extern s16 D_800C7C74;
extern s32 D_800A5E60;
extern u8  D_8007BA70[];
extern u8  D_800A4F48[];
extern s32 D_800A651C;
extern u8  D_800A6528[];
extern u8  D_800A6610[];
extern u8  D_800AA60C[];
extern s32 D_800AE7BC;
extern s32 D_800AE7C8;
extern u8  D_800BA0D8[];
extern u8  D_800BA0E4[];

extern void func_80043060(s32);
extern void func_800141F0(void);
extern void func_8005FC68(s32);
extern void func_8005FCB8(void);
extern void func_80018918(void);
extern s32  func_80043300(void);
extern void func_8002C8F4(void);
extern void LoaderInitFileTable(void);
extern void func_80014238(void);
extern void func_80014390(void);
extern void func_800191A8(void);
extern void func_80010A98(void);
extern void func_800189A8(void);
extern void func_80015208(void);
extern void func_80059BFC(s32, s32);
extern void GameModeDispatch(void);
extern void func_80015498(void);
extern void func_8001C00C(void);
extern void func_800D25FC(void);
extern void func_800184F0(void);
extern void func_800596F4(s32);
extern s32  VSync(s32);
extern void func_80059FC0(u8 *);
extern void func_80059D68(u8 *);
extern void CatPrim(s32, s32);
extern s32  func_80059CF4(s32);
extern void func_8003500C(void);
extern void func_8002D034(void);
extern void func_8001AF34(void);
extern void func_8001513C(void);
extern void func_80042610(void (*)(void));

struct MainSlot { s32 unk0; s32 unk4; s32 unk8; };

// @class: other
// @stuck: none -- MATCH (509 ins, -O0 boot object).
/*
 * main (0x80010178) -- the game's outer frame loop, compiled -O0 like the rest of
 * src/boot.c (frame-pointer prologue, every global re-loaded per use).
 *
 * The four gcc-2.7.2 -O0 levers this needed (all NEW, none were in the cookbook):
 *
 *  1. TWO `register` locals, in declaration order, hold the two bases the whole
 *     function addresses through: $s0 = &D_800BA118 (loaded, NEVER used again --
 *     it must still be declared or the lui/addiu pair and the $s0 save/restore
 *     both vanish) and $s1 = D_800AF630. Same lever GameModeDispatch/func_8001099C
 *     already use in this TU; the >0x7FFF member offsets then assemble to the
 *     +0x10000/-0x5Cxx split.
 *
 *  2. `s32 pad[6];` -- 24 bytes of DECLARED-BUT-UNUSED stack. At -O0 gcc reserves a
 *     slot for every local whether or not it is read, and the target's frame is
 *     0x38 (16 outgoing-arg + 24 vars + 16 saved). Without it the frame is 0x20 and
 *     every sp offset in the prologue/epilogue is wrong. The original's six words
 *     were presumably dead locals left in the source.
 *
 *  3. THE SHIFT-FORM MULTIPLY. Inside a MEMORY ADDRESS, `base + i * K` with a
 *     CONSTANT K expands (expand_expr MULT under EXPAND_SUM) to a `(mult reg K)`
 *     rtx that force_operand emits with the INDEX FIRST: `addu d,index,base`.
 *     Writing the same value as `base + ((i * (K>>n)) << n)` materialises the index
 *     into a plain register first, and the address then comes out BASE-first --
 *     `addu $v0,$s1,$a0` / `addu $at,$at,$v0` + `%lo(sym)($at)` -- which is what the
 *     target has. Measured: `p + i*12` -> `addu $4,$3,$2` (wrong), `p + ((i*3)<<2)`
 *     -> `addu $4,$2,$3` (right). Only address context is affected; in VALUE context
 *     (`(s32)(D_800A6610 + i*16384)`) the plain multiply already comes out base-first.
 *
 *  4. The three 12-byte-strided stores go through a struct pointer, not
 *     `*(s32 *)(p + ... + 8)`: only a COMPONENT_REF folds the member offset into the
 *     store (`sw $v1,0x8($v0)`); the pointer-arithmetic spelling materialises it as
 *     a separate `addiu`.
 *
 * Two smaller ones: `(*(u16 *)(p + 0xA3A8))++` emits the extra `addu $v0,$v1,$zero`
 * that `+= 1` does not; and CatPrim's second argument is written
 * `<load> + D_80074778 * 4` (NOT `D_80074778 * 4 + <load>`) -- with a MEM as operand
 * 0 gcc emits the MEM's address first, then operand 1, then the load, and the addu
 * comes out operand-1-first, exactly the target's interleave.
 *
 * The two scratchpad-stack switches around func_80015498/func_8001C00C/func_800D25FC
 * are the §261 idiom: the $sp repointing is inline asm, the calls stay C (so -O0
 * supplies the `jal` + delay-slot nop). $a2 here, not the overlays' $v1.
 */
void main(void) {
    register u8 *q = &D_800BA118;
    register u8 *p = D_800AF630;
    s32 pad[6];

    func_80043060(0);
    D_80074778 = 0x3E0;
    func_800141F0();
    func_8005FC68(0);
    func_8005FCB8();
    func_80018918();
    D_800A2B7C = func_80043300();
    func_8002C8F4();
    LoaderInitFileTable();

    while (1) {
        func_80014238();
        func_80014390();
        func_800191A8();
        func_80010A98();

        while (*(u16 *)(p + 0xA3D4) == 0) {
            D_800C7C70++;
            D_800C7C70 = D_800C7C70 ? D_800C7C70 : 1;
            D_800C7C74 = !D_800C7C74;
            *(u16 *)(p + 0xA3D2) = D_800C7C74;

            D_800A5E60 = (s32)(D_8007BA70 + *(u16 *)(p + 0xA3D2) * 80000);
            ((struct MainSlot *)(p + ((*(u16 *)(p + 0xA3D2) * 3) << 2)))->unk8 =
                (s32)(D_800A4F48 + *(u16 *)(p + 0xA3D2) * 1600);
            ((struct MainSlot *)(p + ((*(u16 *)(p + 0xA3D2) * 3) << 2)))->unk0 = 0x640;
            ((struct MainSlot *)(p + ((*(u16 *)(p + 0xA3D2) * 3) << 2)))->unk4 = 0;

            func_800189A8();
            func_80015208();

            if (*(u8 *)(p + 0xA3E3) == 0) {
                (*(u16 *)(p + 0xA3A8))++;
                *(u16 *)(p + 0xA3AC) += *(u16 *)(p + 0xA3A8);

                *(s32 *)((u8 *)&D_800A651C + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) =
                    (s32)(D_800A6610 + *(u16 *)(p + 0xA3D2) * 16384);
                *(s32 *)(D_800A6528 + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) =
                    *(u16 *)(p + 0xA3D2) * 16384 + (s32)D_800AA60C;
                func_80059BFC(*(s32 *)((u8 *)&D_800A651C + ((*(u16 *)(p + 0xA3D2) * 5) << 2)), 0x1000);
                *(s32 *)((u8 *)&D_800AE7BC + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) =
                    (s32)(D_800BA0D8 + *(u16 *)(p + 0xA3D2) * 16);
                *(s32 *)((u8 *)&D_800AE7C8 + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) =
                    *(u16 *)(p + 0xA3D2) * 16 + (s32)D_800BA0E4;
                func_80059BFC(*(s32 *)((u8 *)&D_800AE7BC + ((*(u16 *)(p + 0xA3D2) * 5) << 2)), 4);
                GameModeDispatch();

                __asm__ __volatile__(
                    "lui   $a2, 0x1f80\n"
                    "ori   $a2, $a2, 0x03fc\n"
                    "addu  $t0, $a2, $zero\n"
                    "sw    $sp, 0($t0)\n"
                    "addiu $t0, $t0, -4\n"
                    "addu  $sp, $t0, $zero\n" : : : "memory");
                func_80015498();
                __asm__ __volatile__(
                    "addiu $sp, $sp, 4\n"
                    "lw    $sp, 0($sp)\n" : : : "memory");

                __asm__ __volatile__(
                    "lui   $a2, 0x1f80\n"
                    "ori   $a2, $a2, 0x03fc\n"
                    "addu  $t0, $a2, $zero\n"
                    "sw    $sp, 0($t0)\n"
                    "addiu $t0, $t0, -4\n"
                    "addu  $sp, $t0, $zero\n" : : : "memory");
                func_8001C00C();
                __asm__ __volatile__(
                    "addiu $sp, $sp, 4\n"
                    "lw    $sp, 0($sp)\n" : : : "memory");
            } else {
                *(s32 *)((u8 *)&D_800AE7BC + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) =
                    (s32)(D_800BA0D8 + *(u16 *)(p + 0xA3D2) * 16);
                *(s32 *)((u8 *)&D_800AE7C8 + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) =
                    *(u16 *)(p + 0xA3D2) * 16 + (s32)D_800BA0E4;
                func_80059BFC(*(s32 *)((u8 *)&D_800AE7BC + ((*(u16 *)(p + 0xA3D2) * 5) << 2)), 4);

                __asm__ __volatile__(
                    "lui   $a2, 0x1f80\n"
                    "ori   $a2, $a2, 0x03fc\n"
                    "addu  $t0, $a2, $zero\n"
                    "sw    $sp, 0($t0)\n"
                    "addiu $t0, $t0, -4\n"
                    "addu  $sp, $t0, $zero\n" : : : "memory");
                func_800D25FC();
                __asm__ __volatile__(
                    "addiu $sp, $sp, 4\n"
                    "lw    $sp, 0($sp)\n" : : : "memory");
            }

            func_800184F0();
            func_800596F4(0);
            VSync(*(s32 *)(p + 0xA3E8));

            *(u16 *)(p + 0x188) = *(u16 *)(p + 0x18A);
            (*(u16 *)(p + 0x18A))++;
            if (*(u16 *)(p + 0x18A) > 1) {
                *(u16 *)(p + 0x18A) = 0;
            }
            func_80059FC0(&p[*(u16 *)(p + 0x188) * 20 + 0x14C]);
            func_80059D68(&p[*(u16 *)(p + 0x18A) * 92 + 0x38]);

            CatPrim(*(s32 *)((u8 *)&D_800A651C + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) + 0x3FF0,
                    *(s32 *)((u8 *)&D_800A651C + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) + D_80074778 * 4);
            func_80059CF4(*(s32 *)((u8 *)&D_800A651C + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) + 0x3FFC);
            func_80059CF4(*(s32 *)((u8 *)&D_800AE7BC + ((*(u16 *)(p + 0xA3D2) * 5) << 2)) + 0xC);
            func_8003500C();
            func_8002D034();
            func_8001AF34();
            func_8001513C();
        }
        func_80042610(0);
    }
}

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

extern u8 D_800AF630[];
extern s32 D_800A5E60;

s32 func_80010A08(s32 arg0) {
    register u8 *p;
    s32 old;
    s32 q;

    p = D_800AF630;
    q = (arg0 + 3) / 4;
    old = D_800A5E60;
    D_800A5E60 += q << 2;
    return old;
}

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

extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80011778(void);
extern u8 D_800AE870;
extern void *loadDestPtrTable;

void func_800112C8(void) {
    if (CdReadRequest(&D_800AE870, loadDestPtrTable, 0, 0) != 0) {
        func_80011778();
    }
}

extern u8 D_800AF630[];
extern void func_800CEDFC(void);

void func_80011320(void) {
    func_800CEDFC();
}

extern s32 D_80074784;

s32 func_80011350(void) {
    return D_80074784;
}

extern u8 D_800AF630[];
extern s32 D_80074784;
extern s32 D_8007478C;
extern u16 D_800B99E8;
extern s32 D_800629D4[];
extern u8 D_800629D6[];
extern u16 D_800629E8[];
extern u8 D_800D3A68[];
extern s32 D_800AE6A8;

extern void func_800295D4(void);
extern void func_80029664(void);
extern void func_80011DCC(void);
extern void func_80011E24(void);
extern void func_8005C4CC(s32);
extern void func_8002D4C8(s32, s32);
extern void func_80011B7C(s32);
extern void func_800118AC(void);
extern void func_80011EB4(void);
extern void func_800CEDFC(void);
extern s32 func_80014CAC(s32, s32);
extern void func_80011DA0(void);
extern void func_800D1724(s32);

/* main:func_80011380 (-O0, boot.c) -- the cookbook §474 "PROVED C-level floor" row, cracked (T5x Fable agent).
 *
 * The target's D_800629D6 index is TWO chained anonymous x2 expansions: lw;copy;sll;copy;sll (expand_mult's
 * copy_to_mode_reg + shift, expmed.c:2227/2244, twice, adjacent). §474 proved no TREE can carry MULT(MULT(i,2),2):
 * fold-const.c:882 split_tree merges it, and every escape (stmt-expr note, register decl (use) brackets) costs a suid.
 * The escape §474 did not consider is that the nested MULT need not exist at TREE level at all. In the EXPAND_SUM
 * (address) route, expr.c:5368 "Apply distributive law if OP0 is x+c" rewrites (x + c) * k with x ALREADY a (mult ..)
 * rtx into (plus (mult (mult X 2) 2) c*k) -- a nested MULT built AFTER fold, which fold never sees; fold has no
 * MULT-over-PLUS distribution, so `(i*2 + 1) * 2` survives as MULT(PLUS(MULT(i,2),1),2). The spurious +2 is cancelled
 * by the `- 2` on the index: both_summands (expr.c:5248) + simplify_binary_operation/plus_constant fold sym-2+2 into
 * the BARE symbol, so the address is (plus (mult (mult X 2) 2) sym) -> force_operand expands the two multiplies
 * back-to-back and expand_binop's copy_to_mode_reg(sym) gives the target's `la $a0; addu $v1,$v1,$a0; lbu $a0,0($v1)`.
 * No note, no variable: stupid.c's born+2 rule 2-colours the chain $v1/$a0 exactly as the target. Verified: match_one
 * MATCH 192/192 and rtu_match MATCH in src/boot.c (--o0). Semantics: (i*2+1)*2-2 == i*4. */
void func_80011380(void) {
    typedef struct {
        u8 pad00[0x16];
        u8 unk16;
    } Unk;
    register u8 *p = D_800AF630;
    Unk *q = (Unk *)&D_800AE6A8;

    switch (*(u16 *)(p + 0xA3B4)) {
    case 0:
        D_800B99E8 = 0;
        func_800295D4();
        if (D_80074784 >= 5) {
            D_80074784 = 0;
        }
        *(u16 *)(p + 0xA3D8) = D_800629D4[D_80074784];
        *(u16 *)(p + 0xA3DA) = (u16)D_800629D4[D_80074784] & 0xF000;
        q->unk16 = D_800629D6[(D_80074784 * 2 + 1) * 2 - 2];
        D_8007478C = D_800629E8[D_80074784];
        if (D_80074784 == 0) {
            func_80029664();
        }
        func_80011DCC();
        func_80011E24();
        func_8005C4CC(1);
        *(p + 0xA434) = 1;
        *(p + 0xA3E0) = 0;
        ++D_80074784;
        func_8002D4C8(0x28, 0);
        func_80011B7C(0);
        func_800118AC();
        break;
    case 1:
        if (*(p + 0xA3E0) != 0) {
            func_80011EB4();
        }
        func_800CEDFC();
        if ((s16)(++D_800B99E8) > D_8007478C ||
            ((s16)func_80014CAC(0, 0x840) != 0 && *(p + 0xA3E0) != 0)) {
            func_80011DA0();
            func_800D1724((s32)D_800D3A68);
            func_800118AC();
        }
        break;
    case 2:
        func_800CEDFC();
        break;
    }
}

extern u8 D_800AF630[];
extern void func_8002D4C8(s32, s32);
extern void func_80011818(s32);

void func_80011680(void) {
    register u8 *p = D_800AF630;

    *(p + 0xA434) = 0;
    func_8002D4C8(0x29, 0);
    func_80011818(5);
}

extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
extern void func_8002D4C8(s32, s32);

void func_800116E0(void) {
    func_8002D4C8(0x21, (u16)func_80028FBC());
    func_8002D4C8(0x22, (u16)func_80029000());
    if (func_80028D9C() == 0) {
        func_8002D4C8(0xC, 0);
    } else {
        func_8002D4C8(0xB, 0);
    }
}

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

extern u8 D_800AF630[];

void func_80011818(param_1)
u16 param_1;
{
    register u8 *p = D_800AF630;

    *(u16 *)(p + 0xA3AE) = param_1;
    *(u16 *)(p + 0xA3B4) = 0;
    *(u16 *)(p + 0xA3BA) = 0;
    *(u16 *)(p + 0xA3B8) = 0;
    *(u16 *)(p + 0xA3BE) = 0;
    *(u16 *)(p + 0xA3B0) = 0;
    *(u16 *)(p + 0xA3B6) = 0;
    *(u16 *)(p + 0xA3BC) = 0;
}

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

extern u8 D_800AF630[];

void func_80011998(void) {
    register u8 *p = D_800AF630;
    (*(u16 *)(p + 0xA3BA))++;
    *(u16 *)(p + 0xA3BC) = 0;
}

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

extern u8 D_800AF630[];

void func_80011B7C(arg0)
    u16 arg0;
{
    register u8 *p = D_800AF630;
    *(u16 *)(p + 0xA3C0) = arg0;
    *(u16 *)(p + 0xA3C6) = 0;
    *(u16 *)(p + 0xA3CC) = 0;
    *(u16 *)(p + 0xA3CA) = 0;
    *(u16 *)(p + 0xA3D0) = 0;
    *(u16 *)(p + 0xA3C2) = 0;
    *(u16 *)(p + 0xA3C8) = 0;
    *(u16 *)(p + 0xA3CE) = 0;
}

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

extern u8 D_800AF630[];

void func_80011CFC(void) {
    register u8 *p = D_800AF630;

    (*(u16 *)(p + 0xA3CC))++;
    *(u16 *)(p + 0xA3CE) = 0;
}

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

extern u8 D_800AF630[];

void func_80011E24(void) {
    extern s32 D_80074788;
    extern s32 D_800629D0;
    extern u16 D_80074794;
    extern u16 D_80074798;
    register u8 *p = D_800AF630;
    long long pad;

    D_80074788 = 0;
    if (D_800629D0 == 0) {
        *(p + 0xA434) = 0;
    }
    D_80074794 = 0;
    D_80074798 = 0;
}

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

extern u16 D_80074794;
extern u16 D_80074798;

void func_800120DC(u16 *arg0, u16 *arg1) {
    *arg0 = D_80074794;
    *arg1 = D_80074798;
}

/* func_8001212C -- boot (-O0). Builds two 0x18-byte SPRT-with-own-tpage prims at
 * the D_800A5E60 prim-buffer cursor and addPrim()s each onto OT word [1] of the
 * frame's ordering table (D_800A6610 + gameFrame*0x4000), then republishes the
 * advanced cursor.
 *
 * -O0 spellings that are load-bearing (all byte-proven here):
 *  - `register u8 *base = D_800AF630;` far-offset base: cookbook ADDENDUM(c) to
 *    §261a -- lands caller-saved ($v0) with no calls, and the >0x7FFF member
 *    access assembles to lui $at,1 / addu $at,$v0,$at / lhu -0x5C2E($at).
 *  - `* 0x4000` (the MULTIPLY, not `<< 14`): the mul-style expansion emits the
 *    `addu $a0,$v1,$zero` copy of the index before the sll -- ADDENDUM(b) to
 *    §261a, read in the mirror direction (there `q << 2` was wanted, here the
 *    multiply is).
 *  - offset 4 is `((u32 *)p)[1]`, every other field is a member lvalue: §127 /
 *    its ADDENDUM -- the constant-offset fold keys on the COMPONENT_REF tree
 *    shape, so the ARRAY_REF form is what materialises `addiu $v1,$a0,0x4` +
 *    a 0-displacement `sw`, which is exactly what the target shows there.
 *  - `p++` and NOT `p = p + 1`: the increment expands add-into-fresh-pseudo +
 *    `addu $a0,$v1,$zero` copy-back before the spill store (§261a's copy row).
 *    `p = p + 1` / `p += 1` / `&p[1]` / the (u8*) cast all fold that copy away
 *    (-1 ins each). This was the whole residual: 175 ins vs 177.
 *  - the 24-bit `addr` bitfield reproduces libgpu's setaddr()/getaddr() RMW:
 *    and 0xFFFFFF (extract) + and 0xFFFFFF (store mask) + and 0xFF000000 + or.
 */

extern u8 D_800AF630[];
extern s32 D_800A5E60;
extern u8 D_800A6610[];

void func_8001212C(void) {
    typedef struct {
        unsigned int addr : 24;
        unsigned int len : 8;
    } PrimTag;
    typedef struct {
        u8 pad0, pad1, pad2, len;
        u32 tpage;
        u8 r0, g0, b0, code;
        s16 x0, y0;
        u8 u0, v0;
        u16 clut;
        s16 w, h;
    } Sprt24;

    register u8 *base = D_800AF630;
    Sprt24 *p;
    u32 *ot;

    p = (Sprt24 *)D_800A5E60;
    ot = (u32 *)(D_800A6610 + *(u16 *)(base + 0xA3D2) * 0x4000);

    p->len = 5;
    ((u32 *)p)[1] = 0xE1000018;
    p->code = 0x66;
    p->clut = 0x77D6;
    p->r0 = 0x80;
    p->g0 = 0x80;
    p->b0 = 0x80;
    p->x0 = 0x30;
    p->y0 = 0x2E;
    p->u0 = 0x40;
    p->v0 = 0xE0;
    p->w = 0x60;
    p->h = 0x18;
    ((PrimTag *)p)->addr = ((PrimTag *)(ot + 1))->addr;
    ((PrimTag *)(ot + 1))->addr = (u32)p;
    p++;

    p->len = 5;
    ((u32 *)p)[1] = 0xE1000018;
    p->code = 0x66;
    p->clut = 0x77D6;
    p->r0 = 0x80;
    p->g0 = 0x80;
    p->b0 = 0x80;
    p->x0 = 0x30;
    p->y0 = 0x46;
    p->u0 = 0xA0;
    p->v0 = 0xE0;
    p->w = 0x60;
    p->h = 0x18;
    ((PrimTag *)p)->addr = ((PrimTag *)(ot + 1))->addr;
    ((PrimTag *)(ot + 1))->addr = (u32)p;
    p++;

    D_800A5E60 = (s32)p;
}
