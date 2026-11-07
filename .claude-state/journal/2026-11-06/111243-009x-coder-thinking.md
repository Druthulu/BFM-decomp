---
ts: 2026-11-06T18:12:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aDFI3GqdrQSwAU2nLDNJ
---
Now let me plan each item.

Item 3 (func_80184B70, pin $3): The pin `register s32 v1 __asm__("$3")` gives v1 = $3. Target uses v1 register ($3) for the unkCC pointer. Lever-free: need the load `v1 = ((Unkstruct*)a0)->unkCC` to land in $3 (v1). In the target, note the structure:

```
v0 = D_80078EB1 (u8 load, lbu)
slt a1,v0,a1   ; a1 = (v0 < a1)
bnez a1, L30
slt v0,v0,a2   ; v0 = (v0 < a2)
beqz v0, L30
li v0,1
lw v1,204(a0)
j L38
nop
L30:
lw v1,204(a0)
li v0,2
L38:
sw v0,176(v1)
```

Source in orig.c:
```
v0 = D_80078EB1;
if (!(v0 < a1)) {
    if (v0 < a2) {
        v0 = 1;
        v1 = ((Unkstruct*)a0)->unkCC;
    } else {
        v1 = ((Unkstruct*)a0)->unkCC;
        v0 = 2;
    }
} else {
    v1 = ((Unkstruct*)a0)->unkCC;
    v0 = 2;
}
*(s32*)(v1+0xB0) = v0;
```

Note the else and the else-if are identical blocks → cross-jump merges them (L30 block: lw v1; li v0,2). That's why the source has both.

Lever-free: replace `register s32 v1 __asm__("$3")` with plain `s32 v1;`. Would it still score 0? Let's try. Since v1 is assigned in all branches and used once at the end, local-alloc might give it something else (maybe a0? or v0?). Let's just test.

Actually, first step per FRESH: diff orig.c against current src def. Let me check the src files.

Let me get the current src defs for each and diff. The src body is likely the same. Let's extract. Actually delever_search compares the body given with the function in build/. The current src should equal orig.c (which was copied from src). Let me verify.

Let me do item 3 first (simplest). Test plain `s32 v1;`.

Item 2: pin a7 to $7. Lever-free: plain `unsigned short *a7;`. Target uses a7 (=$7) as the return pointer/advancing pointer, and v1 as current pointer. The loop: v1 advances, a7 advances. At the end returns a7. Actually a7 and v1 are kept equal: a7 = v1 initially? orig: a7=&D_8011FD10; v1=a7; loop: v0=v1; if (*v0 != 0) { a7 += 0x68; v1 += 0x68; a6++; a5 += 0x68 } else { ... stores ...; return a7; }

In target: a3 = &D_8011FD10; v1 = a3 (move v1,a3); loop body: lhu v0,0(v1); ... on nonzero: a3 += 0x68; v1 += 0x68; a2++; a1 += 0x68. On zero: stores; then j to return with `move v0,a3` in delay slot. Return v0=a7=a3.

So a7 is $7, v1 is $3. Without pin, local-alloc/global alloc might give both... a7 and v1 have identical values and live ranges? a7 and v1 are both live across the loop, both advance together; they are equal at all times except... a7 = &base; v1 = a7; then both advance. Actually they're equal always. So cse would merge them (cse copy merge) — that's why the pin exists: the target keeps two separate registers (a3 and v1) despite being equal. Hmm. The wall tag cse-copy-canonical exists: "cse canonicalises a reg copy onto the older pseudo; target keeps the pinned reg (W48)".

So item 2 is likely a WALL (cse-copy-merge / cse-copy-canonical). But the task says try lever-free bodies, 20-30 min, 30 scored tries. Maybe there is a real-C way to prevent cse merge: make a7 and v1 differ in mode/type? E.g., v1 as `unsigned short *` and a7 as a different type? But a7 is returned. Or spell the pointer advances differently (a7 as char*?). Hmm.

Idea from moves: func_8017E1D4 etc: "$0 zr pin: s16 flag2/3/4 copies (sign-extend escapes cse...)". The trick: make the copy escape cse by using a different mode. Here `v1 = a7` is a pointer copy; cse merges equivalent registers. If instead v1 is an int (s32) and a7 a pointer, cse may still merge via subregs? Different modes: cse has make_regs_eqv for same mode; a copy between different modes might not be equivalent. Hmm, but the code needs *v0 load of unsigned short at v1 and stores. Could declare v1 as `unsigned short *` and a7 as `char *`? Then the return cast. But target's a3 and v1 both advance by 0x68.

Alternatively, maybe reorder: `v1 = &D_8011FD10; a7 = v1;`? Then cse canonicalizes the other direction. Hmm.

Actually the target has `move v1,a3` at e7c — a copy that stays. cse does merge regs when one is copied. In cse.c, make_regs_eqv is called when... let me recall: cse eliminates the copy if it can. `cse_insn` handles SET of a register with another register: if src is a reg and dest reg, it records equivalence and deletes? Actually cse "cse_reg_info" and "make_regs_eqv" when an insn is a copy? Let's check gcc 2.7.2 cse.c. There's code: if (dest is reg && src is reg) then record_reg_equiv and delete the insn if... Actually there's `cse_insn` case SET with `if (GET_CODE (src) == REG ...)` it calls `make_regs_eqv (dest, src)`? And later `delete_reg_equiv`... Hmm, in cse, a copy `a = b` where both regs: it registers equivalence and removes the insn (the "copy propagation"). It only keeps it if one of the regs is used across a "barrier" (setjmp) or is a hard reg that... Actually cse keeps copies involving hard registers? No: `cse_insn`: "If SRC is a REG and DEST is a REG, and DEST is not a hard register, we can..." Let me read the actual source in tools/reference/gcc-2.7.2/cse.c when needed.

Since a7 is pinned to hard reg $7, cse keeps the move because dest a7 is a hard register? Hmm, cse can't delete the copy if the destination is a hard register that's live and used? Actually cse can delete a copy into a hard reg if it can replace uses of the hard reg with the source... but hard regs have fixed uses.

Wait: target `move v1,a3` where v1 = a3. Which is pinned? a7 = $7 = a3. So the move writes v1 ($3) from a3 ($7). cse would like to say v1 ≡ a3 and delete the move (replace uses of v1 with a3). But then the return would be a3? Hmm, if deleted, both become a3 and only one register is used — that would reduce insn count. Target keeps the move, so cse did not delete it, likely because... the pinned reg is the SOURCE, and cse deletes copies into non-hard regs normally. Hmm, actually maybe because a3 is a hard register, cse can't prove...? Let's look at cse.c.

Anyway, the practical approach: test candidates. Let me first check each src def matches orig.c and run experiments.

Item 1 (func_80183E80, keepalive): The keepalive `__asm__ __volatile__("" :: "r"(a1))` keeps a1 live. Target has a1 = &D_801A15AC loaded before, and the keepalive forces a1's liveness across the lui v0 etc. Also there's `move a0,s0` twice (8014 and 8018) — because a0 is pinned to $4 and assigned `a0 = s0` then used as call arg; the first move at 8014 is the pin assignment (a0 = s0, pinned so it must be in $4 → move $4,s0), and second at 8018 is the call setup (also $4). Interesting: `a0 = s0;` then `((Unkstruct*)a0)->unk14 = v0;` — uses a0 for stores. Because a0 is pinned to $4, the stores use $4. And func_8012D5E4(a0, a1, a2, a3) call requires $4 = a0. The duplicate move arises because the call arg setup re-copies.

Actually the pin here ($4 for a0) is the *other* lever, allowed to stay. So we keep the pin and only remove the keepalive. The keepalive is what forces a1 to be live until the call. Without it, a1 (set at line 20) would be... a1 is used as second arg to func_8012D5E4 at line 34, so it's live anyway. Hmm, but the ordering: a1 = &D_801A15AC at line 20; then various; call at line 34 uses a1. So a1 is live across. Why the keepalive? The comment says NEEDED DIFFERS. The keepalive asm is `"" ::"r"(a1)` — it forces a1 into a register at that point, acting as a scheduling barrier / preventing the lui/addiu from being sunk/hoisted, and ensuring a1 keeps its value in $5 across the v0/v1/s0 work.

The moves.md for func_800CB458: "MATCH: pass arg0 to func_800CAF84 (cast call) — keeps $4 live across the Struct16 copies... the pin+keepalive had faked that liveness". And func_801810F8: MATCH: obase set right after pbase and used for the first load too.

For our item: removing keepalive, a1 = &D_801A15AC remains a real use at the call. The question is whether gcc keeps the lui/addiu early or sinks it to the call. Target: lui a1 at 801c, addiu at 8020, right after the second move a0,s0 at 8018, before lui v0 0xfff6. Without the asm barrier, sched1 may sink the a1 load to just before the call, or hoist other stuff. The keepalive also has `__volatile__` so it's a scheduling barrier for sched1? Volatile asm is a barrier for scheduling.

Lever-free alternatives: make a1 used earlier (a real use before the v0 chain) — but there is none in target. Or use do{}while(0) to split EBB (C0535) to influence sched1 order. Or reorder statements.

Hmm. Wait: what does target show? a1 set at 801c/8020 (after the second move a0,s0 at 8018, before lui v0,0xfff6 at 8024). Then the stores etc. Then call at 8058 uses a1. So a1's constant load is early. sched1 typically hoists loads early (it schedules for latency). Without a barrier, maybe it still does that. Let's test: remove line 21 and see score.

Let me start. First verify src matches orig.c, and set up a working directory for candidates. Actually each item dir is under W48x; win.c goes there.

Let me diff orig against src def. For TU files, I can grep the function body from src. Let me write a small script? Simpler: use sed to print the function from src and compare visually. Since orig.c is small, I can read src ranges.

Let me find the function in each src file.
