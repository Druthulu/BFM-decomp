---
ts: 2026-11-06T14:32:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2vqBbc0jafrn9KQ80BiW
---
Target asm:
```
	move	$4,$16        # a0 = s0
	la	$5,D_8019DC34 # a1 = &D_8019DC34
 #APP
 #NO_APP              <- the keepalive asm
	li	$2,-655360    # v0 = 0xFFF60000
	li	$16,4         # s0 = 4
	sw	$2,20($4)     # a0->unk14 = v0
	la	$2,D_8019DAFC
	li	$3,0x40000000
	or	$2,$2,$3
	...
```

Interesting: `la $5,D_8019DC34` — the assembler uses `la` (which expands to lui+addiu, but in the object it's lui+addiu). The keepalive is AFTER the la.

Without the keepalive (c1), the la sinks to just before the call (after the or's and la $6). The target has it right after a0=s0.

So the target's a1 computation is early because of the keepalive. To reproduce with real C, I need a1's address computation to stay early.

Hmm. Note: `a1` is a local variable `s32 a1;`. In the target, a1 = &D_8019DC34 (la $5). The call func_8012D5E4(a0, a1, a2, a3) uses a1 as the 2nd arg.

Real C idea: use a1 earlier in a way that forces the computation but doesn't emit extra code. E.g., `a0 = s0; a1 = (s32)&D_8019DC34;` — already there.

What if I move the a1 assignment BEFORE `a0 = s0;`? The target has a0=s0 then la a1. If I move a1 before a0, sched1 might still reorder.

What if I move the a1 assignment even earlier, e.g., before the `func_8012B1B4` call? Then the la would be before the call, which differs.

Hmm.

The keepalive is an empty asm that references a1. Real-C replacements:
- Use a1 in a real computation at that point. The only nearby computations are v0, s0, the stores. 

What if I compute the address into a1 via a different expression that's used early? E.g., `a1 = (s32)&D_8019DC34;` and then use a1 in a real store value? No.

Hmm, let me look at what C0535/C0414 or other techniques say. The keepalive here forces the address computation early. A "dead-reset cse-breaker" won't help. A do-while(0) split might: wrap `a1 = (s32)&D_8019DC34;` in a do-while(0) to split the EBB so cse/sched1 doesn't sink it? Let me think: the EBB split means sched1 (which operates within a block) can't move the la across the boundary. If I put `do { a1 = (s32)&D_8019DC34; } while (0);` and then the rest, the do-while creates a block boundary after the la, so sched1 can't sink the la into the later block. But wait, the la is already in the same basic block as the later code (no branches between). The do-while(0) might create a NOTE_INSN_BLOCK_BEG/END, which splits the EBB for cse but does it split for sched1? sched1 operates per basic block (not EBB). A NOTE_INSN_BLOCK doesn't create a basic block boundary. Hmm.

Actually, C0535 says the do-while(0) "splits cse1's extended basic block" and "sched1 sees them in source birth order". So it affects sched1's ordering via LUID/priority, not block boundaries.

Hmm. Let me look at how the la gets sunk: sched1 reorders based on priority. The keepalive asm (priority 1, but it's a use of a1) creates a dependency that pins the la at that position. Without it, sched1 sinks the la to the call (where it's needed).

To pin the la early with real C: create a real use of a1 at that point. What if I assign a1 to another variable that's used early? E.g., `a1 = (s32)&D_8019DC34; v1 = a1;` then use v1 later? But v1 is used for 0x40000000.

Hmm, what if the source computes the address and passes it through a temp that's used in the OR chain? Like `v0 = ((s32)&D_8019DAFC) | ...`? no.

Wait — the target's `la $5,D_8019DC34` is a `la` pseudo (lui+addiu). The target computes it early. What if the original source had the address used in an earlier statement, e.g., `a1 = (s32)&D_8019DC34;` placed right after `a0 = s0;` AND the compiler naturally keeps it because the source order has other independent statements after it? sched1's priority determines the order. The keepalive adds a use that raises a1's refs.

Hmm, this is the same class as the previous item: the keepalive adds refs to a1, affecting sched1's ordering. But here it's ORDER (sched1), not REG.

Let me look at the sched1 dump to understand. Actually, let me think about what real C adds a use of a1 early without code.

Idea: use a1 as the base of an early store? The target's early stores are `sw $2,20($4)` (a0->unk14) and `sh $16,2($4)` (a0->unk2). If I write `((Unkstruct_800B5CB8 *)a1)...` no, wrong base.

Idea: `a1 = (s32)&D_8019DC34;` and then `a2 = (s32)&D_8019DC3C;` — a2 is computed later in the target (`la $6,D_8019DC3C` after the or's). So a2 is NOT early.

Hmm.

Let me look at the exact difference again:
- Target: `move $4,$16; la $5,D_8019DC34; #APP#NO_APP; li $2,-655360; li $16,4; sw ...`
- Mine: `move $4,$16; ... li $2,-655360; li $16,4; sw $2,20($4); la $2,D_8019DAFC; li $3,0x40000000; or; li $3,0x20000000; or; la $6,D_8019DC3C; li $7,0x20; sh $16,2($4); jal func_8012D5E4; sw $2,88($4); ... la $5,D_8019DC34`? 

Wait, the diff said mine has the a1 la at insns 31-32, target at 22-23. Let me get mine's full asm. Let me look at the diff positions: target[22:24] = `lui a1,0x0; addiu a1,a1,0`. Mine[31:33] = same. So mine computes a1 at insn 31 (later). Let me count the target: insn 22 is `la $5,D_8019DC34` (which is lui+addiu = 2 insns). So target has a1 at 22-23, right after `move $4,$16` (insn 21).

Mine has a1 at 31-32. What's at 24-30 in mine? Probably `li $2,-655360; li $16,4; sw $2,20($4); la $2,D_8019DAFC; li $3,0x40000000; or $2,$2,$3; li $3,0x20000000`. Then a1 at 31-32? Hmm, the diff says "insert mine[22:22] target[22:24]" meaning target has 2 extra insns at 22 that mine doesn't have there, and "delete mine[31:33]" meaning mine has 2 insns at 31-33 that target doesn't. So it's purely a move of the a1 la from position 31 to 22.

So mine sinks the a1 la to position 31. The target has it at 22.

To fix with real C: I need the la to be at position 22 (early). 

What if I reorder the source statements so that `a1 = (s32)&D_8019DC34;` is followed by statements that force it early? The source currently:
```
a0 = s0;
a1 = (s32)&D_8019DC34;
[keepalive]
v0 = 0xFFF60000;
s0 = 4;
((...*)a0)->unk14 = v0;
v0 = (s32)&D_8019DAFC;
v1 = 0x40000000;
v0 = v0 | v1;
...
```
Without the keepalive, sched1 moves the la down. The target keeps it right after a0=s0.

Real-C idea: move the `a1 = ...` assignment to be AFTER `v0 = 0xFFF60000; s0 = 4;`? Then sched1 would place it even later — worse.

Idea: Move the a1 assignment to the TOP (before a0=s0)? Then sched1 might keep it at the top. But the target has a0=s0 first. Hmm, sched1 might reorder.

Idea: use the do-while(0) trick to split the EBB after the la, preventing sched1 from sinking it. C0535 says the do-while(0) split makes sched1 keep birth order. Let me test:
```
a0 = s0;
do { a1 = (s32)&D_8019DC34; } while (0);  // !FAKE: do-while
v0 = 0xFFF60000;
...
```
Hmm, but the do-while(0) creates a block boundary AFTER the la, and sched1's scheduling is per basic block. If the boundary is a NOTE_INSN_BLOCK, it doesn't split basic blocks for sched1. But C0535 says it affects sched1's birth order. Let me just test.

Actually, the C0535 mechanism: "The block boundary splits cse1's extended basic block, so the copies are not merged/re-ordered there and sched1 sees them in source birth order." So it prevents cse from merging, and sched1 then sees them in source order. Hmm, sched1 reorders within a block based on dependencies and priorities, not "source birth order" per se, but the LUIDs matter.

Let me just test a few variants:
- v1: `do { a1 = (s32)&D_8019DC34; } while (0);`
- v2: move the a1 assignment before `a0 = s0;`
- v3: assign a1 earlier and use a1 in a real early expression.

Let me also check: is `a1` used anywhere else? Only in the call. 

Let me test v1 and v2.

Also, maybe the simplest: since the pin `register s32 a0 __asm__("$4")` is present (it stays), maybe I can use a1 differently.

Let me test v1/v2 quickly.
