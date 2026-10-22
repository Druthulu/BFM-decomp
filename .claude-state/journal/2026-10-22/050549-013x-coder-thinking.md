---
ts: 2026-10-22T11:05:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AoeOYob9s3gvJSnjayOB
---
Excellent! Now I can see the target clearly.

Target key sequence:
```
1ff4: lhu v0,112(s0)
1ff8: nop
1ffc: andi v0,v0,0x3
2000: move v1,v0        <- the "copy" of mode into v1
2004: sh v0,254(s0)     <- the store of mode
2008: li v0,1
200c: beq v1,v0,...
```

So the target: mode computed into v0; `move v1,v0`; then `sh v0,254(s0)`; then comparisons use v1.

Note: v1 is used later as the base of `lw v0,4(v1)` at 2084 and 207c. So v1 holds `unk20` pointer in the case0/case1 arms! Interesting: at 2058 `lw v1,32(s0)` — so v1 is REUSED for unk20 in each arm. So v1's live range as "mode" ends before that.

Wait — v1 is used for the comparison chain at 200c-2030, and then in the case0 arm `lw v1,32(s0)` reassigns v1. Since the arms are separate blocks, v1 can be reused.

Now: the C source has `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` in both case0 and case1 arms, and the target does `lw v1,32(s0)` in each arm — v1! So the asm launder `__asm__("" : "=r"(e) : "0"(e));` in case1... hmm wait, but in case0 there's no launder, and the target does `lw v1,32(s0)` there too.

Hmm, actually the notes say "the unk20 load sinks out of the case1 arm into the shared block (the target keeps one load per arm)" when only the e re-tie was removed.

OK so in the target, `e` (unk20) is in v1 in both arms. And `v1` (mode) is in v1 in the chain. So the register allocator reuses v1 for both.

Now let's think about the source structure:
- `mode` = andi → target v0
- `v1 = mode` → needs `move v1,v0`
- `unkFE = mode` → `sh v0,254(s0)`

To make GCC keep the move: we need v1 to not be merged with mode by cse.

Options:
1. Make `mode` not a separate variable. E.g.:
```c
s32 v1 = CAST_SIGN(u16, (u8 *)s0, 0x70) & 3;
...
((Unkstruct_800B5CB8 *)s0)->unkFE = v1;   // sh v1,254(s0) -- wrong, target is sh v0
```
No good, target has the store from v0.

Hmm. But wait — actually, does it? `sh v0,254(s0)` and `move v1,v0`. So mode is in v0, and the copy is in v1. If we wrote `v1 = ...; unkFE = v1;` we'd get `sh v1,254(s0)` and no move. The target wants sh from v0 and move to v1. So GCC chose to keep the ORIGINAL in v0 and copy to v1.

So GCC has a canonical form: the value is computed once into v0, and v1 is a copy. Why did GCC choose to make v1 the copy rather than coalesce? Because of the asm: `__asm__("" : "=r"(v1) : "0"(v1));` forces v1 to be a distinct register from the input (the "0" constraint ties input to output, so v1 = same reg as input... hmm actually "0"(v1) with output "=r"(v1) means output must equal input register, and the asm has no clobber, so GCC must materialize a copy beforehand).

Right: the asm's output is tied to the input, so GCC emits `move v1,v0` to satisfy the constraint that v1 (the pseudo) is in a register and the asm reads/writes it — actually with "=r"(v1) and "0"(v1), GCC will assign v1 to some register and emit a move if the value is in a different one. Since the asm is volatile-ish? `__asm__("" : ...)` without volatile and with output = the compiler can... hmm, the output "=r" means v1 is written by the asm (undefined value), so v1 after the asm is undefined! But the code then uses v1 in the comparisons. That would be wrong C semantics but GCC with "=r" and "0" — the input is v1's value, output overwrites v1. Hmm, but then the comparison `v1 == 1` uses undefined value. GCC's optimizer... with non-volatile asm it might just treat it as a copy? No, "=r" is an output so it writes.

Hmm, but actually GCC treats "=r"(v1) with "0"(v1) as: the asm writes to v1, and v1's input value is the same reg. So after the asm, v1 has an unknown value. Then `if (v1 == 1)` would be unpredictable. That doesn't match the target where v1 is compared meaningfully.

Unless GCC optimizes: since asm output = same reg as input, and non-volatile... GCC's RTL would be `set v1, v0` before the asm, then the asm clobbers v1 with same reg. Actually the "0" constraint on the output means the output register equals the input register. GCC emits the asm with a single register operand, and the value in it is the input value. So v1 holds mode after the asm. GCC's semantics: v1's value after the asm is "whatever the asm wrote", but since output=input register, the asm didn't change the register (it's an empty asm). GCC can't know that, but the empty string asm... GCC treats asm with empty template as having no effect on registers other than the outputs. The output v1 gets a fresh undefined value.

Hmm but then the code `if (v1==1)` uses undefined v1, and GCC would fold the whole thing to arbitrary. But the target does compare v1. So actually GCC must be keeping v1 = v0.

Ah — I recall GCC's behavior: when the output is tied to the input ("0"), GCC's `asm` handling sets up so that the register contains the input value, and the output pseudo is a NEW pseudo assigned to that register, and the old value of the pseudo is dead. GCC actually generates a copy: it creates `set v1_new, v1_old` and then the asm writes v1_new. So the register holds the input value at the time of the asm. But subsequent reads of v1_new are the asm output (undefined).

Yet the target compares v1 to 1 and branches meaningfully. Hmm... So maybe GCC 2.7.2 (this is an old MIPS gcc) treats "=r"(x) with "0"(x) specially...

Actually wait. Look at the target: `move v1,v0` then `sh v0,254(s0)` then `li v0,1; beq v1,v0`. If v1 were undefined after the asm, GCC would have folded the comparison to a constant. So GCC treats the asm output as preserving the input when tied. Indeed, GCC has a rule: for a tied output operand (matching constraint "0"), the value is the same as the input, and GCC models the output as a copy of the input. Yes — GCC's `asm` handling: when the output matches an input constraint number, the output's value equals the input's value at the asm (since the same register holds it). GCC does model this correctly: the output pseudo is defined by the asm but since it's the same reg as the input, the value is unchanged... hmm, actually no, GCC documents that the output is written by the asm so the value is whatever the asm wrote. But GCC's RTL for a tied operand: `asm_operands` creates `set out, in` copies. The output pseudo gets a reg.

Whatever. Empirically: the target has `move v1,v0` and v1 is then compared. So GCC kept v1 = mode.

So this is essentially: GCC does NOT eliminate the copy because the asm's output forces v1 into a register distinct from... hmm, or because the asm creates a new pseudo.

OK, let's stop theorizing and start experimenting. The key challenge: reproduce `move v1,v0` + `sh v0,254(s0)` in plain C.

Ideas to keep a copy in plain C:
(a) Use v1 in two places where one requires it to be distinct.
(b) Make the copy a "real 2nd set" as in successful cracks: e.g.
```c
s32 v1;
v1 = mode;
v1 = v1;   // no
```
(c) Take the address / cast to force a distinct reg? e.g. `v1 = *(s32*)&mode`? That would be an extra load.
(d) Use a union/bitfield?

Hmm. Another classic GCC trick: **the copy survives if the source value is needed later in a different register**... no.

Actually here's a thought: cse's make_regs_eqv merges when the copy is `v1 = mode` and mode is a reg. But if the source is a CONSTANT or an expression that has been "expanded", GCC may keep the copy.

Alternative approach: **make the comparison chain use a different variable than the store**, i.e., invert the roles:
```c
s32 v1 = mode;   // v1 = the copy
```
vs. what if mode itself is defined as a copy of something else:
```c
s32 tmp = CAST_SIGN(u16,(u8*)s0,0x70);   // lhu
s32 mode = tmp & 3;                        // andi v0
s32 v1 = tmp & 3;                          // andi again — no
```

Hmm what about:
```c
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
v1 = mode;
```
being reordered to
```c
v1 = mode;
((Unkstruct_800B5CB8 *)s0)->unkFE = mode;
```
Then GCC has: mode in v0 (live across the copy), v1 = mode. Same.

What if we make `mode` a *const* or make the store use a separate temp:
```c
s32 mode = ... & 3;
s32 st = mode;      // extra
((Unkstruct*)s0)->unkFE = st;
v1 = mode;
```
Adds a move.

Think about it from the target's perspective: the target has TWO registers holding the same value simultaneously (v0 for the store, v1 for the chain), and the store happens AFTER the move (sched1 reordered). And crucially, the comparison chain uses v1 while the store uses v0.

In plain C: `unkFE = mode; if (mode == 1) ...` would give `andi v0; sh v0; beq v0,...` — one register.

To have two registers, we need the compiler to believe the value in v1 may differ from the value in v0 — i.e., they must not be provably equal. But they're computed from the same expression.

**Key idea**: if the store is between the definition of mode and the copy, and the store could modify the memory... but the store writes to s0->unkFE, and mode is loaded from s0+0x70 — different address, but the compiler can't know (unless it does alias analysis!). Hmm, but unkFE = 0xFE and the load is at 0x70 — different offsets of the same struct but GCC doesn't know struct aliasing rules... actually it does for the same object type: `((Unkstruct_800B5CB8*)s0)->unkFE = mode;` — writing to s0->unkFE could alias s0->unk70 if the struct has those as separate members of the same struct type. GCC's alias analysis on struct members: writes to member unkFE do not alias member unk70 (different offsets of the same object, TBAA says no alias). Hmm, GCC does know distinct struct members don't alias.

BUT: what if the load of mode happens BEFORE the store in program order? Then the store can't affect the load anyway.

**Realization**: The copy `v1 = mode` in the target is a copy whose source dies. GCC eliminates such copies (copy coalescing / cse make_regs_eqv) when the source's register is available. The source mode dies right at the copy.

**Trick that often works**: make the source live longer by using it in the store AFTER the copy... i.e. swap the order so that:
```c
v1 = mode;              // copy
unkFE = mode;           // use of mode (source still live)
```
Then mode is live from andi to the store, and v1 is live from the copy to the chain. The overlap forces different registers! And the allocator would assign... hmm, GCC still coalesces.

But wait — cse make_regs_eqv happens in CSE, which works on the RTL after expansion, before register allocation. It merges `v1 = mode` into `v1 = mode_reg` substitution: i.e. it replaces v1 with mode's reg everywhere. The condition is roughly: the copy is "trivial" (rhs is a reg) and v1 isn't live-in, and the substitution doesn't conflict.

In GCC 2.7's cse.c, `make_regs_eqv` is called from `equiv_find`/`record_eqv` when a copy is found: it substitutes the "eq" reg for the copy. There's a check `if (!REG_P (reg) ...)`. And there's the important guard in cse.c: the copy is only merged if the destination reg's live range doesn't conflict.

Given the target KEEPS the copy, something in the original code prevents the merge — the asm.

For plain C to keep it, we need the copy's destination to be genuinely required in a distinct register. One reliable way: **use the copy in a context where the original must be preserved** — but there's only one use.

Another: **make v1's definition depend on a value that could have been clobbered** — e.g., make the load of mode happen, store it, then reload? No.

**Alternative reliable way**: make `mode` a *global* or *volatile*? A volatile load would change the instruction (lw instead of lhu+andi).

**Another way**: make the two "equal" values come from different but equivalent-looking computations that GCC can't prove equal:
```c
s32 mode = CAST_SIGN(u16, (u8*)s0, 0x70) & 3;
s32 v1 = CAST_SIGN(u16, (u8*)s0, 0x70) & 3;
```
GCC would CSE the two loads (same address, no intervening store... the store unkFE = mode is between them, but TBAA says different members don't alias → GCC would CSE the loads!). Then we'd get one andi and one copy — which cse might then merge. Hmm, but actually if the load is CSE'd, then v1 = mode is still a copy → merged.

Hmm, but with the store in between, GCC's CSE might not merge the loads if it can't prove no aliasing (it should prove it via TBAA on struct members).

OK, what about this: make v1's set be a **phi** or come from a different block so it isn't a copy? E.g.

```c
s32 v1;
if (something) v1 = mode; else v1 = mode;
```
That's a phi → would need a move in each branch. Different instruction count.

Hmm.

Let me step back. Maybe the *other* lever (the `e` launder) is easier, and the v1 one is genuinely a wall. The notes said the best lever-free score was 13 with both removed. Let me re-read:

"Tried (5 bodies):
 - both re-ties removed: 13 (88 ins) — the target has `andi v0,v0,0x3; move v1,v0; sh v0,254(s0)` (the re-tie MATERIALISES a real move v1=mode); plain C merges the copy (cse make_regs_eqv), so the move disappears.
 - moving the store `unkFE = mode` after `v1 = mode;` so the copy is not dead: 13 (cse still merges).
 - only the e re-tie removed: 6 (89 ins) — the unk20 load sinks out of the case1 arm into the shared block (the target keeps one load per arm).
 - only the v1 re-tie removed: 3108 ins — cse turns the equality chain into a CASE TABLE.
 - do-while(0) wrappers: no change."

Interesting! "only the e re-tie removed: 6" → 6 is better than 13! And it keeps 89 ins (same count). So removing just the `e` launder gives 6.

So strategy: keep the v1 launder?? No — we need lever-free (NO launder at all). Hmm. But wait: we need to remove BOTH launders and keep score 0.

Hmm, so:
- v1 launder present, e launder removed: score 6, 89 ins.
- both removed: 13, 88 ins.
- e launder present, v1 removed: 3108.

So the residual with only-e-removed is 6 mismatches. If we can fix those 6 with the v1 copy problem... Let's think: with the v1 asm present we have `move v1,v0` but the e load sinks out of the case1 arm.

The e issue: `e = s0->unk20;` in case0 and case1, then in `shared:` block `t = e; t |= 0x8040; e = t; func_8012C658(callarg0, argmode, s0);`. Target:
```
2054: li a0,409
2058: lw v1,32(s0)     <- case0 arm
205c: j 2084
2060: li a1,2
2064: lw a0,32(s0)     <- case1 arm
...
2078: li a0,409
207c: lw v1,32(s0)     <- case1 arm
2080: li a1,3
2084: lw v0,4(v1)      <- shared
2088: move a2,s0
208c: ori v0,v0,0x8040
2090: jal func_8012C658
2094: sw v0,4(v1)
```
So target has the `lw v1,32(s0)` in BOTH arms (duplicated load), not sunk to shared. With plain C, GCC sinks the load to the shared block (one load) — because both arms assign the same value `s0->unk20` and it's a common subexpression. The asm launder in case1 prevents that (the asm's output makes e's value "defined by asm" in that arm, so the two can't be CSE'd/sunk).

Hmm, so in case0 there's no asm but GCC still sinks. Since case0's `e = s0->unk20` and case1's `e = s0->unk20` are identical, GCC's CSE across blocks (dominating) can hoist/sink.

To defeat the sinking in plain C: make the two arms' loads non-identical in a way GCC can't prove equal, e.g., load from different offsets? No — must produce same code.

Options:
- Make case1's load a *second* load of the same address: `e = s0->unk20;` twice in case1? Then there'd be an extra load instruction (count changes). Unless GCC CSEs them.
- Make the two arms' expressions textually different but semantically same: e.g., case0: `e = ((Unkstruct*)s0)->unk20;` case1: `e = *(s32*)((u8*)s0 + 0x20);`. GCC's alias/equivalence analysis: it might still see both as loads from s0+0x20 and CSE them. Hmm, but the TYPE differs (s32 vs whatever) — GCC's CSE works on the alias set + offset, so it'd still fold.
- Insert a store between the load in one arm and the shared block that might modify s0->unk20 → forces a re-load in the shared block. But the target has exactly 2 loads (one per arm) and the shared block uses v1 from the arm.

Wait — look at the target: the shared block at 2084 uses `v1` which was set in the ARM (2058 or 207c). So the load IS in the arm and the value flows to shared. The register allocator has one v1 across the join.

In plain C: `case0: e = s0->unk20; ... goto shared;` and `case1: e = s0->unk20; ... goto shared;` — GCC sinks the load into shared (dominance: both arms assign e = same load; GCC's CSE can sink a load to the common block because it's "safe" if the block dominates... actually sinking a load into the join block is what GCC does when the load is available in both preds — it's a "sinking" optimization, and since the address doesn't change, the value is the same).

To prevent sinking: the value must differ between the arms, OR there must be something between.

Hmm, in the target the asm in case1 forces a distinct pseudo. Without asm, both arms have the same load → sunk.

**Trick**: make the load in one arm depend on something arm-specific. E.g., in case1, load from a different but equal address? Like `e = ((Unkstruct*)s0)->unk20;` in case0 and `e = *(s32 *)&((Unkstruct*)s0)->unk20;` in case1 — same address, GCC CSEs.

**Trick 2**: make case1's e come from the store `unkFE`? No.

**Trick 3**: In the original target, note case1's `li a1,3` is in the delay slot of the `j`... no wait, case1 has no j — it falls through to 2084! Look:
```
2078: li a0,409
207c: lw v1,32(s0)
2080: li a1,3
2084: lw v0,4(v1)     <- shared, case1 falls through
```
And case0:
```
2054: li a0,409
2058: lw v1,32(s0)
205c: j 2084
2060: li a1,2    <- delay slot
```
So case0 jumps to shared, case1 falls through. Both have their own load.

Interesting. So how did the original get a load in each arm? The asm in case1. And case0's load is natural. So case0 alone would have the load sunk to shared? Then both arms' loads would be in shared. With the asm in case1, GCC must keep case1's load in case1 (asm output), and case0's load also stays (different pseudo/path).

So the crux: in case0, GCC needs a load of unk20 in the arm, not sunk to shared.

Hmm. What if case0's `e` is loaded via a different pointer spelling that GCC can't equate with case1's? E.g. case0 uses `s0` directly and case1 uses a copy of s0? Like in case1: `void *s1 = s0; e = ((Unkstruct*)s1)->unk20;`. Then the load is from s1+0x20 where s1 = s0 (a copy). GCC would copy-propagate s1→s0 and then CSE the loads. Unless s1 is a copy that survives.

Hmm, this is getting complicated. Let's think about what mechanism keeps the load in the arm.

**Alternative**: the store `unkFE = mode` in the prologue! `((Unkstruct_800B5CB8 *)s0)->unkFE = mode;` happens at 2004, BEFORE the branch. Then case0's load of unk20 at 2058 comes after a store to s0->unkFE. If GCC couldn't prove that store doesn't alias the load of unk20, it couldn't sink the load to shared... but that doesn't matter for the sink, both arms load the same address.

Hmm, actually why would GCC sink the load into the shared block at all? Because in the shared block, `e` is used. GCC's "sinking" of a load from predecessors into the join block is done by... hmm, actually GCC doesn't usually sink loads. Let me reconsider: maybe GCC doesn't sink; rather, case0's `e = s0->unk20` — since case1 also does the same and they merge at shared, GCC's PRE (partial redundancy elimination) or "jump threading"...

Actually the standard GCC pass that does this is "sinking" (sink.c) — no. More likely: the load is in the shared block from the start because... no, in C the load is written in each arm.

Hmm, actually GCC's "cse across blocks" / "jump threading" (thread_prologue_and_epilogue) can move code from a block into its unique predecessor. That's `jump.c`'s `thread_prologue_and_epilogue`! It threads a block's prologue into its predecessor when the block has a single predecessor and the values are compatible. That's exactly it: shared has 2 predecessors (case0, case1), so the load can't be threaded into both... but if both arms assign e the same way, the load appears in the shared block.

Hmm wait, that doesn't work either: shared has 2 preds.

Actually let's think about it as: GCC's SSA-ish "phi" handling. `e` is a phi at shared: phi(e0, e1) where e0 = load in case0, e1 = load in case1. Since the two loads are identical (same address, same value), the phi is trivial → GCC replaces phi with one of them and DELETES the other load, then the surviving load can be sunk/hoisted to the shared block. Yes! That's "phiopt"/"jump" simplification: identical phi args → the phi is replaced by the common value and the redundant load removed; then the load is in the predecessor... but the target wants it in the predecessor.

Hmm, if the phi has identical args from both preds, GCC's `simplify_phi` in phiopt replaces the phi with the value (the load reg). But then the load is in each pred — both loads remain? No, only one load reg is used; the other load is dead → removed. Then the shared block would use the reg from ONE pred, which is invalid.

Right, that's why GCC would then move the load into shared: after the phi is replaced by a value defined in a specific pred, GCC must either keep the phi or sink the load. Actually GCC's approach: the phi is in the shared block; since both preds define e identically, GCC's `simplify_phi` can't just pick one (dominance). Instead, at the RTL level the two loads are CSE'd: the second load is redundant (same address) and gets a phi reg at the join. Then in RTL, the phi reg gets the value; but GCC 2.7 doesn't have SSA — it uses "REG_DEAD"/local reg sets with the "cross-jumping" and "local reg" machinery.

The final RTL: in the shared block, e is a reg defined by a phi-like copy at the join (in the jump insn's operands? MIPS has no phi). For MIPS, at the join GCC must have a single register. The two arms both do `lw v1,32(s0)`. GCC would do "cross-jumping": the two arms' load sequences are identical → cross-jump merges them. But the arms aren't identical (different li a1,2 vs li a1,3).

Hmm, GCC's mechanism: `reload`/`reload_cse`? Or in the RTL, the shared block's use of `e` is a pseudo reg; at the join, the reg is assigned via the predecessor's definitions. GCC's "local register allocation" per basic block plus "global-alloc" for cross-block values.

OK. Empirically: without the asm, GCC produced a single load in shared (that's what the notes say: "the unk20 load sinks out of the case1 arm into the shared block"). Hmm, "sinks out of the case1 arm INTO the shared block" — so one load in shared. And the target has 2 loads (one per arm). So the diff is 1 instruction count difference (2 loads vs 1 load) plus register differences. Score 6.

So to get a load in EACH arm, we need the two arms' e values to be non-identical from GCC's perspective.

**Idea**: make case1's e load happen through a different pointer value. In the target, the case1 arm's load `lw v1,32(s0)` uses s0. Same as case0.

**Idea**: use a `volatile`? Changes code.

**Idea**: In case1, insert an opaque operation between the load and the shared block... e.g., a store to s0->something? That would add instructions.

Hmm, what if we make the *shared* block's use of `e` different such that the phi can't be simplified? E.g. in the shared block:
```c
s32 t = CAST_WIDTH(s32, e, 4);
```
`CAST_WIDTH(s32, e, 4)` = `*(s32*)((u8*)e + 4)` presumably — a load from e+4. The target: `lw v0,4(v1)` then `ori v0,v0,0x8040` then `sw v0,4(v1)`.

So `e` is used as a base pointer for load+store.

**Idea**: Make the two arms compute `e` from different expressions that GCC can't prove equal but produce the same code. E.g.:
- case0: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;`
- case1: `e = *(s32 *)((u8 *)s0 + 0x20);`

Both are loads from s0+0x20. GCC's CSE uses alias sets and offsets → equivalent → merged. Likely.

Unless the pointer arithmetic differs in a way GCC can't fold: e.g. case1: `e = ((Unkstruct_800B5CB8 *)((u8*)s0 + 4))->unk1C;` — the address would be s0+4+0x1C = s0+0x20, but GCC folds the offset at RTL → same address. Hmm.

What if the address is computed via a runtime value that equals 0x20? Like a global const? `e = *(s32 *)((u8*)s0 + g_offset)` where g_offset is a const int 0x20 — GCC folds.

OK — different approach: **make the two arms' e values differ in a way that's resolved at runtime but produces the same target code**. Impossible.

**Approach: duplicate the load in one arm via a construct GCC won't CSE but which produces identical instructions.** E.g., in case1:
```c
e = ((Unkstruct_800B5CB8 *)s0)->unk20;
e = e;  // no
```

What about using a `volatile` local pointer? no.

Hmm, what about the "asm" restriction — we can't use asm. But what about other non-asm opaque constructs? Like `__builtin_choose_expr`, `__builtin_constant_p`? Those are compile-time.

What about a function call that GCC won't inline and that returns the pointer? E.g., `e = get_unk20(s0);` where get_unk20 is an external function? That changes the code (call). No.

What about a **setjmp/longjmp**? No.

What about making the load go through a `volatile` pointer cast but with the volatile read replaced? `*(volatile s32*)&x` generates a lw with a volatile semantics — GCC would keep it, but it also prevents optimization. Actually, would a volatile load produce the same instructions? `lw v1,32(s0)` — yes, same instruction! And volatile prevents CSE/sinking of that load. But it would also prevent other optimizations around it.

Hmm! Interesting. But is a volatile load a "lever"? The kinds are: pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm. A volatile load is arguably a "barrier" (it acts as a memory barrier preventing reordering). Hmm. The task says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

A volatile access IS a new lever of kind "barrier". So no.

OK so for item 1, the difficulty is real. The notes already established a wall with tag cse-copy-merge.

But my task: "Retry: each item was walled before after too few tries; read <dir>/notes.md first, then try new moves." I need ≥20 min and ≥30 scored tries for a WALL to count. That's a lot of work per item. 5 items × 30 tries... That's heavy but let's see. Each dt.sh run takes ~1 second. 30 tries = 30 seconds of compute, but I need to think of 30 distinct candidate bodies. That's the real cost.

Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". OK.

Given the time budget (20-30 min wall per item), and 5 items, this is a long task. Let me be efficient: focus on finding a MATCH for at least one item, and for the rest do genuine exploration to reach a documented wall.

Let me reconsider — maybe there are more promising items. Let me look at the other items:

**Item 2: func_8017E780** — best lever-free score 2 (ONE instruction!). That's very close. The residual: the `lw a0,32(s0)` (unk20 load, the call's a0 setup) is inside sched1's call+argsetup group in the candidate but outside in the target. Target has it at index 96, candidate at 97.

This one is very promising: score 2 = 1 instruction difference? Actually "score 2 (one instruction)" per the notes. So it's just a reordering of ONE instruction. If we can move the load out of the group...

In C: `t = ((Unkstruct_80126B58 *)p)->unk20;` then `func_8001D0E8(t, 0x140, 0xF0);`. The load feeds the call's a0. sched1 groups the call with its argument setup. To keep the load OUT of the group, we need the load to not be part of the arg setup...

Hmm: sched1's SCHED_GROUP_P groups instructions feeding a call. The load feeds a0 for the call. To break it: make the load's value flow through something else, or make the load's result used by something else too.

Actually if the load result is used elsewhere (another use), sched1 might place the load earlier because it's needed earlier. Hmm, but "earlier" = outside the group? Let's think: sched1 tries to fill delay slots. The target has the load at index 96, the candidate at 97, i.e. the load is one slot EARLIER in the target.

Actually let's look at the target disassembly around there. Let me get it.

Also, note the constraint: the candidate must produce the same instruction sequence. Let's examine.

**Item 3: func_80180054** — best 48.
**Item 4: func_801832A8** — best 14, count exact (237=237)! Just the constant birth position.
**Item 5: func_80185380** — best 28 / 4 with only v6 re-tie removed (count exact 111).

Item 5: "only the v6 re-tie removed (p10's kept): 4 (111 ins — count exact). The residual is the p10 re-tie's nop landing one slot off". Since we can't keep the p10 re-tie (it's a launder), we need to remove both. Both removed → 39.

Item 4: count exact at 14 — very close! The residual is the shared 0x66666667 magic constant materialised at the wrong place + a v0/v1 transposition.

Let me start with the most promising: item 2 (score 2, count exact).

Let me look at item 2 in detail.

Actually, let me be systematic and start with item 2 since it's closest.

Let me read orig.c for item 2 and the target disassembly.
