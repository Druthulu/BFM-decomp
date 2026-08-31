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

__asm__(".text\n.align 2\n.globl main\n.ent\tmain\nmain:\n.set\tnoreorder\n"
"addiu $sp,$sp,-56\nsw $ra,52($sp)\nsw $fp,48($sp)\nsw $s1,44($sp)\nsw $s0,40($sp)\naddu $fp,$sp,$zero\n"
"jal __main\nnop\nlui $s0,%hi(D_800BA118)\naddiu $s0,$s0,%lo(D_800BA118)\nlui $s1,%hi(D_800AF630)\naddiu $s1,$s1,%lo(D_800AF630)\n"
"addu $a0,$zero,$zero\njal func_80043060\nnop\naddiu $v0,$zero,992\nlui $at,%hi(D_80074778)\nsw $v0,%lo(D_80074778)($at)\n"
"jal func_800141F0\nnop\naddu $a0,$zero,$zero\njal func_8005FC68\nnop\njal func_8005FCB8\nnop\njal func_80018918\nnop\njal func_80043300\nnop\n"
"lui $at,%hi(D_800A2B7C)\nsw $v0,%lo(D_800A2B7C)($at)\njal func_8002C8F4\nnop\njal LoaderInitFileTable\nnop\n"
".L80010204:\nj .L80010214\nnop\nj .L8001094C\nnop\n.L80010214:\njal func_80014238\nnop\njal func_80014390\nnop\njal func_800191A8\nnop\njal func_80010A98\nnop\n"
".L80010234:\nlui $at,1\naddu $at,$s1,$at\nlhu $v0,-23596($at)\nnop\nbeqz $v0,.L80010254\nnop\nj .L80010938\nnop\n"
".L80010254:\nlui $v1,%hi(D_800C7C70)\nlw $v1,%lo(D_800C7C70)($v1)\nnop\naddiu $v0,$v1,1\naddu $v1,$v0,$zero\nlui $at,%hi(D_800C7C70)\nsw $v1,%lo(D_800C7C70)($at)\n"
"lui $v0,%hi(D_800C7C70)\nlw $v0,%lo(D_800C7C70)($v0)\nlui $v1,%hi(D_800C7C70)\nlw $v1,%lo(D_800C7C70)($v1)\nnop\nbnez $v1,.L80010290\nnop\naddiu $v0,$zero,1\n"
".L80010290:\nlui $at,%hi(D_800C7C70)\nsw $v0,%lo(D_800C7C70)($at)\nlui $v0,%hi(D_800C7C74)\nlh $v0,%lo(D_800C7C74)($v0)\nnop\nxori $v1,$v0,0\nsltiu $v0,$v1,1\n"
"lui $at,%hi(D_800C7C74)\nsh $v0,%lo(D_800C7C74)($at)\nlui $v0,%hi(D_800C7C74)\nlhu $v0,%lo(D_800C7C74)($v0)\nlui $at,1\naddu $at,$s1,$at\nsh $v0,-23598($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $a0,$v1,3\nsubu $a0,$a0,$v0\nsll $v1,$a0,4\naddu $v1,$v1,$v0\nsll $v0,$v1,7\n"
"lui $v1,%hi(D_8007BA70)\naddiu $v1,$v1,%lo(D_8007BA70)\naddu $v0,$v1,$v0\nlui $at,%hi(D_800A5E60)\nsw $v0,%lo(D_800A5E60)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,1\naddu $v1,$v1,$v0\nsll $a0,$v1,2\naddu $v0,$s1,$a0\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a1,$v1,$zero\nsll $a0,$a1,1\naddu $a0,$a0,$v1\nsll $a1,$a0,3\naddu $a1,$a1,$v1\nsll $v1,$a1,6\n"
"lui $a0,%hi(D_800A4F48)\naddiu $a0,$a0,%lo(D_800A4F48)\naddu $v1,$a0,$v1\nsw $v1,8($v0)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,1\naddu $v1,$v1,$v0\nsll $v0,$v1,2\naddu $v1,$s1,$v0\naddiu $v0,$zero,1600\nsw $v0,0($v1)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,1\naddu $v1,$v1,$v0\nsll $v0,$v1,2\naddu $v1,$s1,$v0\nsw $zero,4($v1)\n"
"jal func_800189A8\nnop\njal func_80015208\nnop\nlui $at,1\naddu $at,$s1,$at\nlbu $v0,-23581($at)\nnop\nbnez $v0,.L80010644\nnop\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23640($at)\nnop\naddiu $v1,$v0,1\naddu $v0,$v1,$zero\nlui $at,1\naddu $at,$s1,$at\nsh $v0,-23640($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23636($at)\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23640($at)\nnop\naddu $v0,$v0,$v1\nlui $at,1\naddu $at,$s1,$at\nsh $v0,-23636($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a0,$v1,$zero\nsll $v1,$a0,14\n"
"lui $a0,%hi(D_800A6610)\naddiu $a0,$a0,%lo(D_800A6610)\naddu $v1,$a0,$v1\nlui $at,%hi(D_800A651C)\naddu $at,$at,$v0\nsw $v1,%lo(D_800A651C)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a0,$v1,$zero\nsll $v1,$a0,14\n"
"lui $a0,%hi(D_800AA60C)\naddiu $a0,$a0,%lo(D_800AA60C)\naddu $v1,$v1,$a0\nlui $at,%hi(D_800A6528)\naddu $at,$at,$v0\nsw $v1,%lo(D_800A6528)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,%hi(D_800A651C)\naddu $at,$at,$v0\nlw $a0,%lo(D_800A651C)($at)\naddiu $a1,$zero,4096\njal func_80059BFC\nnop\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a0,$v1,$zero\nsll $v1,$a0,4\n"
"lui $a0,%hi(D_800BA0D8)\naddiu $a0,$a0,%lo(D_800BA0D8)\naddu $v1,$a0,$v1\nlui $at,%hi(D_800AE7BC)\naddu $at,$at,$v0\nsw $v1,%lo(D_800AE7BC)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a0,$v1,$zero\nsll $v1,$a0,4\n"
"lui $a0,%hi(D_800BA0E4)\naddiu $a0,$a0,%lo(D_800BA0E4)\naddu $v1,$v1,$a0\nlui $at,%hi(D_800AE7C8)\naddu $at,$at,$v0\nsw $v1,%lo(D_800AE7C8)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,%hi(D_800AE7BC)\naddu $at,$at,$v0\nlw $a0,%lo(D_800AE7BC)($at)\naddiu $a1,$zero,4\njal func_80059BFC\nnop\n"
"jal GameModeDispatch\nnop\nlui $a2,8064\nori $a2,$a2,1020\naddu $t0,$a2,$zero\nsw $sp,0($t0)\naddiu $t0,$t0,-4\naddu $sp,$t0,$zero\njal func_80015498\nnop\naddiu $sp,$sp,4\nlw $sp,0($sp)\n"
"lui $a2,8064\nori $a2,$a2,1020\naddu $t0,$a2,$zero\nsw $sp,0($t0)\naddiu $t0,$t0,-4\naddu $sp,$t0,$zero\njal func_8001C00C\nnop\naddiu $sp,$sp,4\nlw $sp,0($sp)\nj .L80010744\nnop\n"
".L80010644:\nlui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a0,$v1,$zero\nsll $v1,$a0,4\n"
"lui $a0,%hi(D_800BA0D8)\naddiu $a0,$a0,%lo(D_800BA0D8)\naddu $v1,$a0,$v1\nlui $at,%hi(D_800AE7BC)\naddu $at,$at,$v0\nsw $v1,%lo(D_800AE7BC)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a0,$v1,$zero\nsll $v1,$a0,4\n"
"lui $a0,%hi(D_800BA0E4)\naddiu $a0,$a0,%lo(D_800BA0E4)\naddu $v1,$v1,$a0\nlui $at,%hi(D_800AE7C8)\naddu $at,$at,$v0\nsw $v1,%lo(D_800AE7C8)($at)\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,%hi(D_800AE7BC)\naddu $at,$at,$v0\nlw $a0,%lo(D_800AE7BC)($at)\naddiu $a1,$zero,4\njal func_80059BFC\nnop\n"
"lui $a2,8064\nori $a2,$a2,1020\naddu $t0,$a2,$zero\nsw $sp,0($t0)\naddiu $t0,$t0,-4\naddu $sp,$t0,$zero\njal func_800D25FC\nnop\naddiu $sp,$sp,4\nlw $sp,0($sp)\n"
".L80010744:\njal func_800184F0\nnop\naddu $a0,$zero,$zero\njal func_800596F4\nnop\nlui $at,1\naddu $at,$s1,$at\nlw $a0,-23576($at)\njal VSync\nnop\n"
"lhu $v0,394($s1)\nnop\nsh $v0,392($s1)\nlhu $v0,394($s1)\nnop\naddiu $v1,$v0,1\naddu $v0,$v1,$zero\nsh $v0,394($s1)\nlhu $v0,394($s1)\nnop\nsltiu $v1,$v0,2\nbnez $v1,.L800107A4\nnop\nsh $zero,394($s1)\n"
".L800107A4:\nlhu $v0,392($s1)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\naddiu $v1,$v0,332\naddu $v0,$s1,$v1\naddu $a0,$v0,$zero\njal func_80059FC0\nnop\n"
"lhu $v0,394($s1)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,1\naddu $v1,$v1,$v0\nsll $a0,$v1,3\nsubu $a0,$a0,$v0\nsll $v0,$a0,2\naddiu $v1,$v0,56\naddu $v0,$s1,$v1\naddu $a0,$v0,$zero\njal func_80059D68\nnop\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,%hi(D_800A651C)\naddu $at,$at,$v0\nlw $v1,%lo(D_800A651C)($at)\nnop\naddiu $v0,$v1,16368\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v1,-23598($at)\nnop\naddu $a1,$v1,$zero\nsll $a0,$a1,2\naddu $a0,$a0,$v1\nsll $v1,$a0,2\nlui $a0,%hi(D_80074778)\nlw $a0,%lo(D_80074778)($a0)\nnop\naddu $a1,$a0,$zero\nsll $a0,$a1,2\nlui $at,%hi(D_800A651C)\naddu $at,$at,$v1\nlw $a1,%lo(D_800A651C)($at)\nnop\naddu $v1,$a0,$a1\naddu $a0,$v0,$zero\naddu $a1,$v1,$zero\njal CatPrim\nnop\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,%hi(D_800A651C)\naddu $at,$at,$v0\nlw $v1,%lo(D_800A651C)($at)\nnop\naddiu $v0,$v1,16380\naddu $a0,$v0,$zero\njal func_80059CF4\nnop\n"
"lui $at,1\naddu $at,$s1,$at\nlhu $v0,-23598($at)\nnop\naddu $a0,$v0,$zero\nsll $v1,$a0,2\naddu $v1,$v1,$v0\nsll $v0,$v1,2\nlui $at,%hi(D_800AE7BC)\naddu $at,$at,$v0\nlw $v1,%lo(D_800AE7BC)($at)\nnop\naddiu $v0,$v1,12\naddu $a0,$v0,$zero\njal func_80059CF4\nnop\n"
"jal func_8003500C\nnop\njal func_8002D034\nnop\njal func_8001AF34\nnop\njal func_8001513C\nnop\nj .L80010234\nnop\n"
".L80010938:\naddu $a0,$zero,$zero\njal func_80042610\nnop\nj .L80010204\nnop\n"
".L8001094C:\naddu $sp,$fp,$zero\nlw $ra,52($sp)\nlw $fp,48($sp)\nlw $s1,44($sp)\nlw $s0,40($sp)\naddiu $sp,$sp,56\njr $ra\nnop\n"
".set\treorder\n.end\tmain\n");

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
