---
ts: 2026-11-06T22:39:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bwa4BKy9dXjryurjKgqv
---
w0's asm order matches the target exactly EXCEPT the registers:
- w0: `move $2,$4` ✓ (target same)
- w0: `sw $17,20($sp); move $17,$5; sw $31,24; sw $16,16` — target: `move $2,$4; sw $16,16; move $16,$5; sw $31,24; sw $17,20`. The stack-save order differs because the callee-saved registers are swapped ($16 vs $17).
- w0: `lh $16,18($2)` (s1ang in $s0), target `lh $17,18($2)` (s1ang in $s1).
- w0: `div ...,$17` (d=$s1), target `div ...,$16` (d=$s0).

So w0 has the EXACT target instruction order and only the $s0/$s1 swap. If I could just swap those two registers...

w6 has d=$s0, s1ang=$s1 (correct!) but the arg0 copy is missing and the scheduling order changed.

So I need the mask-in-place's register effect WITHOUT changing the arg0 copy/scheduling.

In w6, the differences from target:
1. `sw $16,16` before `move $16,$5` vs target `sw $16,16` after `move $16,$5` — minor order (probably fine, it's within the prologue? Actually the target order: move $2,$4; sw $16,16; move $16,$5; sw $31,24; sw $17,20. w6: sw $16,16; move $16,$5; sw $31; sw $17; lw $2,32($4)... — the `move $2,$4` is missing and the lw is early.)
2. Missing `move $2,$4` (arg0 copy).
3. `lw $2,32($4)` uses $4 instead of $2.
4. Scheduling order of the loads differs.
5. The cast uses a temp `$2` instead of in-place `$16`.

Hmm, the cast: w6 `sll $2,$16,16; sra $16,$2,16` vs target `sll $16,$16,16; sra $16,$16,16`. In w6, the do-while on the cast didn't produce in-place? The mask-in-place changed something.

Wait — in w6 the do-while is on the cast: `do { d = (s16)d; } while (0);`. The asm shows `sll $2,$16,16; sra $16,$2,16` — using $2 as a temp. In the target/pinned and w0: `sll $16,$16,16; sra $16,$16,16` (in-place, using the same reg). Hmm, w0's asm shows `sll $2,$17,16; sra $17,$2,16` — also a temp! Wait, w0 line: `sll $2,$17,16` then `sra $17,$2,16`. So w0 also uses $2 as a temp, but the target uses $16 in-place. Yet w0's score was 38 due to the $s0/$s1 swap; the diff didn't show the cast because after register renaming, the target's `sll $16,$16,16` vs w0's `sll $2,$17,16`... the diff would show. Let me look at the earlier diff for w0: it showed line 22 `sra s1,v0,0x10 | sra s0,s0,0x10`. Hmm, so mine was `sra $17,$2,16` (temp $2) and target `sra $16,$16,16`. The diff only showed one line because the diff algorithm aligned.

OK this is getting complicated. The instruction streams differ in more than registers.

Let me reconsider. Maybe the mask-in-place is the right globalisation but I need to preserve the original structure. The key insight: w6 made d=$s0 correctly. The remaining differences are due to the arg0 copy and scheduling.

What if instead of mask-in-place, I globalise s1ang by reassigning it to itself in a way that doesn't change the instruction stream? E.g., `s1ang = s1ang;`? That would be optimized away.

Hmm, what about keeping u6 AND reassigning s1ang:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
...
```
and then adding `s1ang = s1ang & 0xFFF;` where s1ang is used later? That adds the second mask use.

Let me think about why w6 lost the arg0 copy. Actually, maybe it's because the global s1ang (7 refs/22) changed the local-alloc qty ordering such that r72's tie with r80 failed.

Hmm, alternatively: maybe the arg0 copy is related to the *tie* between the parameter pseudo and the pointer load. In w0, r72 (arg0) and r81 (pointer) were tied into one qty that got $v0. In w6, r72 got $a0.

Why would the tie fail in w6? Let me look at the lreg dumps for both to see the parameter handling. Let me grep "Register 72" in both lreg dumps.

Actually, let me look at the .rtl or .lreg around insn 4 for w6 vs w0.
