---
ts: 2026-10-21T23:46:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_8t2GsxV7gFryn5KWFHeT
---
All 17, same shape. Hmm, the width changes didn't even change the count (still 41 ins) — suspicious: maybe the widths didn't change codegen (v0=1 with s16 → `li v0,1` same; the return sign-extends but 1 is positive).

Interesting: all variants produce exactly the same 41-ins shape. So the difference is robustly "const temp in $2".

Let me think about the ROM structure again:
```
20 bnez v0,+0x90      ; if (mask & arg3) != 0 -> return 0
21 li v1,9
22 beq a2,v1,+0x94    ; arg2 == 9 -> return (v0 = 0!)
23 li v0,1
24 li v1,17
25 beq a2,v1,+0x94
26 li v1,41
27 beq a2,v1,+0x94
28 li v1,10
29 beq a2,v1,+0x94
30 nop
31 lw v0,376(a0)
32 nop
33 xor v0,v0,a1
34 j +0x94
35 sltu v0,zero,v0
36 move v0,zero
```
Hmm wait — ins 23 `li v0,1` comes AFTER ins 22's branch. But ins 22 branches to +0x94 which is the return. If v0=0 at that branch, the function returns 0 for arg2==9. Then ins 23's `li v0,1` is dead for that path but live for the later branches (25,27,29) which return v0=1.

But hold on: branches 25,27,29 come AFTER ins 23 → v0=1 ✓. And branch 22 → v0=0 ✗ (returns 0). So the ROM has an oddity: arg2==9 → 0.

Hmm, but this is the pinned C compiled → identical bytes. So gcc compiled `v0 = 1; v1 = 9; if (arg2 == v1) return v0;` into: branch on arg2==9 → return (v0 not yet set = 0!). That means gcc sank the `v0 = 1` assignment past the first compare — a scheduling artifact — and the ROM inherits it. Fine. Actually that means the ROM is "buggy" relative to the C semantics, but our job is bytes.

Now, in MY compile (41 ins): mine[20] bnez, mine[21] move v0,zero, mine[22] li v0,9, mine[23] beq a2,v0,6aa4, mine[24] li v0,17, ... mine[29] bne a2,v0,6aac, mine[31] j, mine[32] li v0,1.

So mine has: `move v0,zero` at 21 — where does that come from? It's the delay slot of the `bnez` at 20? No — the delay slot of ins 20 would be ins 21. Yes! `bnez v0,+0x90` with delay slot `move v0,zero` — that's the return-0 setup (the branch is taken when the mask test != 0 → return 0, and the delay slot sets v0=0). ✓.

In the target, ins 20 `bnez v0,6ab8` + ins 21 `li v1,9` (delay slot) — so the target's delay slot is the first `li v1,9`! Because in the target, the branch at 20 is not the "return 0" one — it goes to +0x90 = ins 36 `move v0,zero`... wait, the delay slot of the branch at 20 must be ins 21 = `li v1,9`. And the branch target +0x90 = ins 36 `move v0,zero` → so the branch path sets v0=0 at ins 36. OK.

In mine, the branch at 20 goes to +0x?? and its delay slot is `move v0,zero`. So mine has the "move v0,zero" in the delay slot (i.e., the return-0 block is reached with v0=0 already set) while the target has it at the block +0x90.

So mine's layout: the branch at 20 jumps forward to a return-0 block, with the delay slot doing `move v0,zero`. Target: branch at 20 jumps to +0x90 (near the end), delay slot = `li v1,9`.

This difference comes from the block ordering: in the target, the "return 0" block (ins 36) is placed at the END (after the fall-through chain), while in mine it's placed... hmm, in mine the return-0 block would be at 6ac4 (later too).

Let me get my mine's full listing. I can get it by scoring the nopin again and reading the whole diff (with more tail lines). The diff prints both sides only for changed regions. Since mine[0..19] == target[0..19], I know the head.

Mine (from diff):
```
20 bnez v0,6ac4
21 move v0,zero
22 li v0,9
23 beq a2,v0,6aa4
24 li v0,17
25 beq a2,v0,6aa4
26 li v0,41
27 beq a2,v0,6aa4
28 li v0,10
29 bne a2,v0,6aac
30 ??? (equal to target[30] = nop)
31 j 6ac4
32 li v0,1
33 ???
34 ???
35 ???
36 j 6ac4
37..40 (equal to target[35..38])
```
Hmm mine[30] == target[30] = nop; mine[33:36] == target[31:34] = nop, lw v0,376(a0), nop; mine[37:41] == target[35:38] = sltu, move v0,zero, ?, ?.

Wait that gives mine 41 ins: 0..40.

So in mine, the "li v0,1" is at 32 (as the delay slot of `j 6ac4` at 31) — i.e., mine's "return 1" is a `j` + `li v0,1` pair, whereas the target's is a single `li v0,1` at ins 23 in the middle.

And mine's last compare uses `bne a2,v0,6aac` (jump if NOT equal) while the target uses `beq a2,v1,6abc` (jump if equal). So the target branches "if equal → return 1", mine branches "if not equal → continue". That's the classic if/else inversion: in the target the "return 1" case is the branch-taken path; in mine it's the fallthrough. Hmm, this suggests the source shape differs: in the target, the last compare `if (arg2 == v1) return v0;` compiles to `beq` (branch to return) — i.e. the "return" is the THEN branch. In mine, gcc inverted it: `bne` to continue, fallthrough to return.

Why? Because in mine, the "return v0" path is the fallthrough of the last compare, while in the target it's a branch. This is a code-layout thing: gcc put the return block before the continuation.

Interesting: this is the "flow" of blocks. Hmm.

So the difference in mine is not just registers: also block layout (41 vs 39 ins).

Let me think about the source shape that would produce the target:

Target's chain:
```
21 li v1,9
22 beq a2,v1,RET      ; equal -> RET (which returns v0)
23 li v0,1
24 li v1,17
25 beq a2,v1,RET
...
29 beq a2,v1,RET
30 nop
31 lw v0,376(a0)
...
```
So the target's four compares all branch to a common RET block, and the "li v0,1" sits between the first compare and the second. Then after the last compare falls through to the `lw v0,376(a0)` (the final return expression).

In the C source:
```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
v1 = 0x11;
if (arg2 == v1) return v0;
v1 = 0x29;
if (arg2 == v1) return v0;
v1 = 0xA;
if (arg2 == v1) return v0;
return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
```
So the first `if` is at the top; the last `if` is followed by the final return. gcc compiled the pinned version to branch-to-RET for all four, with `li v0,1` sunk to after the first compare.

In mine (no pin), the last compare became `bne` (branch if not equal → continue) with the fallthrough being "return v0". So gcc inverted the last if. Why would the pin change that? Because with the pin, the "return v0" block is a distinct block (v0 in $2) vs mine where v0 (the "1") is in $3 and the return-value register $2 is used by the const temp → the return block's structure differs.

Hmm, this is a deep rabbit hole. The essence: the "1"-value pseudo must be allocated $2 (the return register), and then everything follows.

So: how to make gcc allocate $2 to the "1" pseudo without a pin?

Ideas:
1. Make the "1" pseudo the ONLY pseudo that wants a caller-saved reg... no, the const temp also wants one.
2. Reduce the const temp's priority: e.g. give the const temp a shorter live range. But its live range spans the chain (it's set 4 times).

Hmm — what if the const temp is NOT reused across the four compares but each compare uses a fresh temp (variant A) — I tried; same result (gcc reused them into one pseudo).

3. What if the "1" is stored in a variable that is used in a way that gives it higher qty: e.g. `v0 = 1;` then `if (arg2 == v1) return v0;` — v0 has 5 uses (returns). qty=6. The const temp: 4 sets + 4 uses = 8.

To beat it, v0 needs qty > 8, or the const temp needs < 6.

4. Give the const temp fewer refs by making the compares not use a variable: `if (arg2 == 9)` (variant A) — tried, no change. gcc still used one pseudo (it coalesced).

Hmm, actually maybe in variant A, gcc created 4 pseudos but local-alloc gave them all $2 (v0) since they're not live simultaneously → the "1" got $3. The "pairs v0->v1 x3" indicates mine's $2 == target's $3 (the const temp) in 3 places.

So the const temp keeps winning $2 regardless.

5. Reverse: make the "1"-value pseudo need a *different* class of register... e.g. what if the "1" is not a variable but an expression `arg2 == 9 ? 1 : ...`? Hmm.

6. What about making the const temp a *pointer* or making it "volatile"? volatile is a barrier lever (not allowed... well, "barrier" is a lever kind; adding a barrier would be adding a lever → not allowed).

7. What about the ORDER of the compares? E.g. write the chain as a switch:
```c
switch (arg2) {
case 9: case 0x11: case 0x29: case 0xA: return v0;
}
```
gcc would generate a jump table or a comparison chain — different bytes.

8. What if the const temp is `s32` but assigned from a constant expression, e.g. `v1 = 9;` → li. Same.

9. Idea: make the const temp's pseudo be the SAME as the "1" pseudo? No.

10. Idea: use a *local array* or struct? no.

11. What about making v0's value not 1 but something that needs $2 for a different reason? e.g. `v0 = 1;` → the pseudo is a constant 1. GCC's local-alloc might treat a pseudo whose value is a constant specially (e.g. "li v0,1" generated late in RTL expansion). Hmm! Indeed: `li v0,1` might not be a pseudo at all but a literal set. In the target, `li v0,1` at ins 23 suggests the pseudo v0 (holding 1) is allocated $2 and its set is materialized there.

12. Try: make the "1" value come from a computation, e.g. `v0 = (s32)(u8)1;`? Meh.

13. Try: swap the roles — make the const temp the one that's "1"? No.

14. Think about local-alloc in gcc 2.7.2 (final.c): within a basic block, local_alloc assigns hard registers to pseudos. The order: it iterates over the block's live pseudos sorted by `qty` (number of refs) DESCENDING? In final.c's local_alloc: for each block, it computes `reg` allocation via `allocate_reg`? The pseudo's "qty" is the count of references. Ties broken by pseudo number (declaration order!). Hmm — decl order swap (variant D) didn't change anything, suggesting decl order isn't the tiebreak here (or the qty difference dominates).

So I need to change the qty ratio. Options:
- Make the const temp have ≤ 5 refs: e.g. split the chain into two temps? Doesn't reduce refs (each compare still needs set+use).
- Reduce by 1: e.g. the first compare `if (arg2 == v1) return v0;` → the const temp's first use could be avoided: `v1 = 9; if (arg2 == v1) return v0;` → 2 refs for the first compare. If I write `if (arg2 == 9) return v0;` (no temp) → 0 refs for that compare, but gcc reuses a pseudo anyway (variant A showed no change).

Hmm, variant A gave exactly the same score and same shape, suggesting gcc's output for variant A is identical to nopin. So gcc coalesced the 4 constants into one pseudo (via combine/cse). OK.

- Increase v0's refs: the "1" pseudo is used 5 times (4 returns + ...?). Actually the returns: `if (arg2 == v1) return v0;` ×4 + the final `return *(...) != arg1;` (not v0). So v0 has 1 set + 4 uses = 5 refs. The const temp: 4 sets + 4 uses = 8 refs.

To flip: give v0 more uses. Idea: restructure so that v0 is used more, e.g. `v0 = 1; if (arg2 == v1) return v0; ...` — what if I add a redundant use like `v0 = v0 + 0;`? That's a no-op that may create a copy (an extra ref) but might also be optimized away.

Alternatively: reduce the const temp's refs from 8 to 6 by making two of the compares use constants directly and hoping gcc keeps them separate... it doesn't.

Hmm, what if the const temp is used with `==` on a *u16* comparison so the compare is done in HImode? Then the const temp would be u16 (2 refs of 16-bit)? Changes bytes.

Different approach: maybe the whole structure should change — e.g. make the ROM's shape emerge differently. Consider writing the chain as:

```c
v0 = 1;
if (arg2 == 9) return v0;
v1 = 0x11;
...
```
Already the case.

What about making v0 hold the value 1 but assigned in a way that creates a copy: `v0 = 1; v0 = v0;`? gcc would fold.

Hmm, what about the local-alloc "qty" being influenced by loop-depth weighting? The moves.md mentions "loop-weighted ref" (REG_N_REFS += loop_depth). A do-while(0) around `v0 = 1;` would boost v0's refs. That's the "fake do-while" trick, allowed with the marker. But is it a "new lever"? moves.md G06 line 146 used exactly this as a MATCH move: "do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2". And the T10 worked example used `do { r = p + i; } while (0);` with the note "flow REG_N_REFS += loop_depth". The brief says: "`do{}while(0)` only with `// !FAKE: do-while`" — implying it's allowed as a spelling (with the marker). And "no new lever of any kind" refers to lever kinds (pin/launder/barrier/keepalive). A do-while(0) is a "real C move" (loop shape) per the C0505 catalog. I'll treat it as allowed, marked with the comment.

But before that, let me try to find a pure-C crack.

Idea: what if the "1" is not stored in a variable at all, but the four returns are `return 1;`? Then gcc emits `li v0,1` at each return (4 sets) → the ROM has only one `li v0,1` → mismatch (as observed in nopin: mine had "j + li v0,1"). Hmm, in mine (nopin) there's exactly one `li v0,1` (at ins 32) plus a `j`. So the "1" is one pseudo with one set, and the return block is reached via a jump.

Interesting: in mine, the return-1 path is `j 6ac4` + delay `li v0,1` — the set of v0 is sunk into the jump's delay slot. In the target, the set is at ins 23 (before the last three compares) and the branches go directly to the RET block.

The difference: in the target, the RET block is shared and the "li v0,1" is hoisted out of it (into the chain). In mine, the "li v0,1" stayed in the block (as a delay slot).

That's a sched1 (scheduling) difference, likely triggered by the register allocation.

Let me try a couple of quick experiments in parallel to see if anything shifts the shape:
- E: v0 declared `s32` but assigned `v0 = 1 + 0;`?
- F: the whole final return expression as a temp?
- G: put the four compares in a different order (e.g. 17, 41, 10, 9)? — changes semantics/bytes.
- H: use `v0` as the loop-ish trick.

Actually, let me try the do-while boost on v0:
```c
do { v0 = 1; } while (0);   // !FAKE: do-while
```
Hmm, would gcc keep that? It becomes a single set (the loop is unrolled since it's do-while(0) with constant condition... gcc might keep it as a loop with a branch!). The T10 example used `do { r = p + i; } while (0);` and it produced a loop-shaped live range, meaning gcc kept a loop (not unrolled) because the body had a side effect ordering? Hmm, gcc 2.7.2 might not unroll `do{}while(0)` — it treats it as a real loop with a backward branch? That would add instructions (a branch) → byte mismatch. But the T10 example says it worked (score 0). In their case the body was `r = p + i;` and it matched the ROM bytes.

Hmm, in the T10 example the do-while produced no extra instructions? That means gcc 2.7.2 does optimize `do{...}while(0)` into just the body but keeps the loop notes? Hmm, moves.md line 146: "do-while(0) around the tail gives the byte temp a loop-shaped live range, so local-alloc ranks it above the ret0 copy and it wins $2" — so the do-while affects local-alloc's ranking (loop_depth weighting in REG_N_REFS) but doesn't add instructions. Plausible: gcc computes REG_N_REFS with loop weighting at RTL expansion, then the loop is later removed by the CFG cleanup (jump threading) but the allocno's ref count was already computed.

OK. Given the C0505 catalog explicitly lists "loop shape" as a real C move, and the constraint explicitly mentions `do{}while(0)` with the `// !FAKE: do-while` marker, using it is sanctioned. But the "no new lever of any kind" clause makes me cautious. The do-while trick is not a "lever" in the lever taxonomy (pin/launder/barrier/keepalive); it's a code-shape move. Also moves.md shows several MATCHes using it (lines 67, 81, 146). I'll use it as a fallback and note it.

Let me first try a few more pure-C variants for item 3:

V1: do-while boost on v0: `do { v0 = 1; } while (0);  // !FAKE: do-while`
V2: v0 with an extra use: e.g.
```c
v0 = 1;
if (arg2 == v1) return v0;
```
→
```c
v0 = 1;
if (arg2 == v1) { v0 = v0; return v0; }
```
Hmm, "v0 = v0" is a self-copy → gcc folds but might count refs? Actually the ref count is computed on RTL before folding? Possibly.

V3: swap the order of the four compares in the source (e.g. 0x11, 0x29, 0xA, 9)? That changes semantics but the ROM's bytes are fixed; the ROM's order is 9,17,41,10 — so no.

V4: change the const temp to `s32 v1` but assign via `v1 = 9;` vs `v1 = arg2 & 9`? no.

V5: Use `u16` compare for arg2: no.

V6: Make the const temp's uses fewer by restructuring the chain to a nested if:
```c
v1 = 9;
if (arg2 == v1) return v0;
v1 = 0x11;
if (arg2 == v1) return v0;
```
→ nested:
```c
if (arg2 == 9) return v0;
if (arg2 == 0x11) return v0;
```
(variant A, tried).

V7: Hoist the "1" assignment out of the if-block? It's already the first statement in the innermost block.

V8: Move `v0 = 1;` to the top of the function (before the first if)? Then v0's live range spans the whole function → much higher priority! And the bytes? The ROM has `li v0,1` at ins 23, deep inside. If v0=1 is hoisted to the function entry, gcc would emit `li v0,1` early (ins ~0) → mismatch. But gcc might sink it back (it's a "sunk" value). Worth a try: gcc's "store motion"/scheduling might place it where needed. Actually since v0 is only used in the deep block, gcc's RTL expansion would place the set right before the uses (it doesn't hoist stores across branches) — the set would be placed in the block where it's assigned, i.e., the entry block → `li v0,1` at ins 0. Then the ROM's ins 23 wouldn't match. But maybe gcc's "sink" pass moves it. Hmm, unlikely but cheap to test.

Actually wait. In the ROM, `li v0,1` is at ins 23, i.e., inside the innermost block (after the first compare). That IS the source position (v0 = 1 is the first statement of the innermost block) — but gcc sunk it past the first compare?! Hmm, in the target, ins 21-22 are `li v1,9; beq a2,v1,+0x94` and ins 23 `li v0,1`. If v0=1 were set at the start of the block, the order would be `li v0,1; li v1,9; beq...`. The ROM has it AFTER. So gcc sank the v0=1 set past the first compare (sched1 sinking, since the branch at 22 doesn't need v0 — because the branch target block is the shared RET which... hmm, but RET needs v0!).

Unless the RET block at +0x94 is NOT the shared return but something else. Argh.

Let me settle the tail question: I want to know what ins 37 and 38 are. Let me look at my probe's compiled output more carefully: "mine 2 ins" for `return 0;`. A function `s32 f(){return 0;}` compiles to `move v0,zero; jr $ra; nop` = 3 insns. The tool said 2. So the tool dropped one — probably the LAST (the function's epilogue is in a different fragment?). Hmm, or the tool's extraction stops at the next label.

Wait — maybe the ov TU's object contains MANY functions and the tool extracts by label. If the extraction is correct, my probe would be 3 ins.

Unless... the tool's `_INS_RE` doesn't match `jr $ra`?! Let me check _INS_RE in masked_diff.py. If the regex requires a specific mnemonic pattern (e.g. lowercase letters, digits, and specific chars), "jr\t$ra" would match. Hmm, but maybe the regex excludes instructions with '$'?

Let me checkthe regex.
