---
ts: 2026-11-06T05:37:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5VoL8nyZNQlct20R5zo4
---
o3 = 8. I'm at 34 tries. Time 22:37, item 2 started 22:24 = 13 min.

The wall needs ≥20 min. Let me continue for ~7 more minutes with a few more tries.

Hmm, let me think about whether there's a *fundamentally* different structure. 

Wait — what if the target's iVar1 in v1 comes from it being *loaded into v1 by local-alloc because v1 is the only free reg at that point*? The allocation order: tmp→$2, iVar2→$3, iVar1→$4. If we could make tmp take $3 instead of $2... no, target has tmp in $2.

Hmm, what if the *number of local qtys* is different in the target because of the hard-reg pin? With the pin, iVar1 is excluded from local-alloc, so there are only 2 local qtys (tmp, iVar2) competing for $2 and $4 (since $3 is reserved).

Lever-free, 3 qtys compete for $2,$3,$4. The target order is tmp,$2; iVar1,$3; iVar2,$4 — which is priority order tmp(20) > iVar1(5.33) > iVar2(?). For this to happen, iVar2's priority must be < 5.33.

In the orig (pinned), iVar2's priority is 9.6 — but that doesn't matter since $3 is reserved.

So the question remains: can we lower iVar2's priority below 5.33 while keeping the copy? 

iVar2's priority = floor_log2(nrefs)*nrefs*size/live.

If iVar2 were HImode (size 2): 3*8*2/10 = 4.8 < 5.33 ✓ — but then the copy must survive.

So: iVar2 HImode + a copy that survives. The copy `tmp = iVar2` (HI→SI sign-extend) gets merged by cse (b1). Why? Because cse replaced the second test's operand with tmp, and then local-alloc coalesced.

In a1 (SI iVar2 + `(s16)` cast), cse did NOT replace the test operands. So the `(s16)` cast on the *copy source* is what blocks cse.

What if iVar2 is HImode and the copy is written to force a cross-mode op that isn't a no-op? For an HImode iVar2, `tmp = (s16)iVar2` is a no-op. `tmp = (u16)iVar2` would be a zero-extend (real op) — but semantically wrong for negatives... unless it doesn't matter (as I analyzed, the low 16 bits are what matter, and the comparisons use iVar2 directly).

Wait, let's check: with iVar2 s16 and `tmp = (u16)iVar2` (tmp s32):
- iVar2 = lh (sign-extended s16).
- tmp = (u16)iVar2 = zero-extended low 16 bits.
- then-arm (iVar2 < 0): tmp += 0x80; store (s16)tmp. For iVar2 negative, say -0x40 = 0xFFC0. (u16) = 0xFFC0 = 65472. tmp+0x80 = 65536+... wait 0xFFC0+0x80 = 0x10040. (s16)0x10040 = 0x0040 = 64. And the correct (s16)(iVar2+0x80) = (s16)(-0x40+0x80) = 0x40 = 64. ✓ Same low 16 bits.
- `if (0 < tmp * 0x10000)`: tmp*0x10000 with tmp=0x10040 → (0x10040 << 16) mod 2^32 = 0x00400000... wait 0x10040 * 0x10000 = 0x1_0040_0000; mod 2^32 = 0x00400000 > 0 ✓. The correct: (iVar2+0x80)=0x40, 0x40*0x10000 = 0x400000 > 0 ✓. Same.
- else arm: tmp -= 0x80: 0xFFC0 - 0x80 = 0xFF40; (s16) = -0xC0 = correct (iVar2-0x80 = -0x40-0x80 = -0xC0). ✓
- `if (tmp * 0x10000 < 0)`: 0xFF40 * 0x10000 = 0xFF40_0000 mod 2^32 = 0xFF400000 < 0 ✓. Correct: -0xC0 * 0x10000 = -0xC00000 < 0 ✓. Same.

So `tmp = (u16)iVar2` is semantically equivalent! And it's a zero-extend (real op, not a no-op). But would gcc emit an extra instruction? For an HImode iVar2 already in a register, zero-extend = andi 0xFFFF — an extra instruction! Unless gcc can fold... Hmm, but the target has `move v0,a0` (a plain move), no andi. So this would add an instruction unless gcc knows the value fits.

Hmm. But wait: with `s16 iVar2`, gcc knows iVar2 is sign-extended in the register (from lh). (u16)iVar2 needs zero-extension → andi. So extra instruction.

Unless... `u16 iVar2` (unsigned HImode) — then the load would be lhu (wrong: target has lh).

Hmm.

OK, what if iVar2 is SI but we make its *qty size* smaller? No.

What if we make iVar2's live range longer via a *real but folding* use... I keep coming back.

Let me try: what if the copy is placed AFTER the second test (so iVar2's live range extends to the copy) but the copy is hoisted by reorg into the delay slot anyway? Source:
```c
if (iVar2 != 0) {
    if (iVar2 < 0) {
        tmp = iVar2;
        tmp += 0x80;
        ...
    } else {
        tmp = iVar2;
        tmp -= 0x80;
```
Here the copy is inside each arm (2 copies, one per arm). The target has 1 copy. But maybe combine/reorg would... no, there'd be 2 moves (one per arm, each 1 instruction) vs target 1. Score would differ.

Hmm, but wait: the arms are mutually exclusive; the target has ONE move in the delay slot (executed unconditionally). Two copies in the arms would give 2 moves. Not matching.

OK. What about placing the copy after the *whole* if (before the reload)?
```c
if (iVar2 != 0) { if... } 
tmp = iVar2;   // too late, tmp used in arms
```
No.

Alright, let me try one more creative thing: make iVar1's priority higher by making its live range shorter through **splitting the function's basic block** — e.g., wrap the first if body in a do-while(0), which might split blocks and change the liveness computation? Hmm, a do-while(0) around the arms could create a block boundary that makes iVar1's qty die earlier... Actually if iVar1's uses are in different blocks, local-alloc might create separate qtys per block, each shorter! That could raise iVar1's priority!

Interesting. Let's try: wrap the whole `if (iVar2 != 0) {...}` body in a do { } while (0), or wrap each arm's store.

Actually, more targeted: if iVar1's live range is split into per-block qtys, each qty has a shorter live range → higher priority. E.g., a do-while(0) around the arms might split the then-arm and else-arm into separate blocks (they already are). Hmm.

Let me just try wrapping the if body in a do-while(0).

Also try wrapping the then-arm's statements in a do-while.

Let me try:
p1: do { ... } while (0) around the entire if-body.
p2: do { } while (0) around the then-arm's two statements.

Let me generate p1.

Actually, thinking about it: iVar1's qty in the entry block spans the branch. If the if-body is a nested block, the RTL gets NOTE_INSN_BLOCK_BEG/END, which don't split basic blocks (they're notes). Basic blocks are split by labels/jumps. So no.

Hmm.

OK, let me take a different final shot: maybe the answer is to make iVar1 a *parameter-like* value with a long life that gets a *callee-saved* reg... no, target is v1.

I'll record the WALL now-ish. Let me first spend a couple more minutes with 2-3 tries, then write it up.

Actually, let me reconsider the target ONE more time. Maybe I mis-identified which variable is in which register. Let me re-examine:

```
2a44 lw v1,32(s0)      ← iVar1 = unk20
2a4c lh a0,16(v1)      ← iVar2 = s16 at iVar1+0x10
2a54 beqz a0, 2aa4
2a58 move v0,a0        ← tmp = iVar2
2a5c bgez a0, 2a80     ← if (iVar2 < 0)
2a64 addiu v0,v0,128   ← tmp += 0x80
2a68 sh v0,16(v1)      ← store through iVar1
```
Yes.

Hmm, so iVar1 = v1, iVar2 = a0, tmp = v0.

What if the source is:
```c
iVar1 = ...unk20;
iVar2 = CAST_SIGN(s16, iVar1, 0x10);
if (iVar2 != 0) {
    tmp = iVar2;
```
with iVar2 declared as... hmm.

What if `tmp` is not a variable but a *parameter-like* expression? 

What if the copy `move v0,a0` is actually the *initialization of a loop variable*? No loop.

OK, WALL. Let me use the tag "lreg-qty-order" (precedent in moves.md line 143) or a new one. The brief: "wall (WALL/PARTIAL) = a tag from .run/P40/T11/walls.txt or a new `<pass>-<what>`". walls.txt doesn't have lreg-qty-order, so I'll use "local-alloc-qty-priority" as a new tag. Hmm, actually there IS "lreg-qty-priority" in walls.txt. Let me use that! From walls.txt: "lreg-qty-priority local-alloc qty order mhi > q > mlo ...". That fits: local-alloc qty order puts iVar2 above iVar1.

Let me use "lreg-qty-priority".

Evidence: "local-alloc: iVar2 (8 refs/8-10 insns, pri 9.6-12) outranks iVar1 (8/18, pri 5.3) for $3; the pin reserved $3; best 8 (copy kept, regs swapped)".

Best = 8.

Now, I need to reach 20 min. It's 22:38; started 22:24 → 14 min. Let me do a few more tries while the clock runs. I'll do 5 more distinct tries in ~4 min.

Actually, let me try something I haven't: **making iVar1's qty die earlier by using a separate variable for the second block's iVar1** — i.e., split iVar1 into iVar1 (first) and iVar1b (reload). The first iVar1's live range would still span the arms. But wait — maybe the reload currently EXTENDS the first qty's liveness? No, the reload is a new def.

Hmm, what if we move the reload BEFORE the arms? Can't.

What about making the then-arm use iVar1 and the else-arm use a *reloaded* expression? Extra lw.

Let me try: what if the arms' stores use a *pointer variable p = iVar1* (a copy)? Adds a move.

OK, 5 more tries:
q1: split iVar1 into iVar1 and iVar1b for the second block.
q2: iVar2 declared u16 (unsigned HImode) — lhu, wrong.
q3: `tmp = iVar2;` with tmp declared as `long`? same.
q4: swap the order of the unk20 load and the CAST_SIGN lines.
q5: `iVar2 = CAST_SIGN(s16, iVar1, 0x10);` → `iVar2 = *(s16 *)((u8 *)iVar1 + 0x10);`

Let me run q1, q4, q5.
