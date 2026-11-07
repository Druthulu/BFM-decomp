---
ts: 2026-11-06T05:20:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Kt80f8Fdr8GzDhhgQRq9
---
Excellent! This is exactly the pattern. In func_80182ED4:
```
tmp = (s16)t; u = tmp;   /* before the if */
if (t == 0) {...} else { t = u - 1; }
```
The copy `u = tmp` survives because the HImode copy escapes cse2's equivalence class, and crucially `u` is USED later (`t = u - 1`), so it's live across the branch.

In our case, we need TWO copies: raw = t (move v1,v0) and t = raw (move v0,v1). Hmm.

But maybe we can structure it as: `tmp = (s16)t; raw = tmp;` giving ONE copy (move v1,v0) that survives because raw is used after (`t = raw`). Then `t = raw` would be another copy... which cse may merge (raw ≡ tmp? raw is SI = sign_extend(tmp); t = raw is a copy of raw → t ≡ raw → merge). Hmm, but then t gets raw's register v1, not v0. That breaks.

Wait, but what if we write:
```c
tmp = (s16)t;    // t → tmp (maybe folded, no insn? or move)
raw = tmp;       // move v1,v0? 
if (t < 0) { ... return; }
t = raw;         // ?
```
Hmm, the target has `move v1,v0` in the delay slot = the copy that survives. And `move v0,v1` after = the copy back.

Let's think about the register allocation in the target: t is v0 because it's the addiu dest (and the compare). raw is v1 because... the pin. In lever-free with `raw = t; t = raw;`, cse merges.

What if we use the s16 trick for the *second* copy so it doesn't get merged into t's register:
```c
raw = t;           // move v1,v0 (raw gets v1)
...
t = raw;           // cse merges → t and raw same reg → the move is gone AND raw's reg may coalesce
```
So we need the second copy to be a *different* pseudo: `s16 tmp2 = (s16)raw; t = tmp2;`? Then t = tmp2 would merge with... hmm.

Wait. Let's re-read the target instruction sequence: move v1,v0; ...; move v0,v1. What if this is actually: `raw = t;` (move v1,v0) then `t = (s16)raw` where the s16 temp coalesces with t (v0)? I.e., the second copy is `t = (s16)raw` and the sign-extend folds to a move v0,v1. Then t is SI, and (s16)raw is a sign-extend. cse: raw ≡ t (from raw = t); then (s16)raw → (s16)t → since t ∈ [0,239], equals t → set t = t → deleted. Ugh.

But wait — in the func_80182ED4 case, the HImode copy `u = tmp` survived because `tmp = (s16)t` creates a HImode pseudo, and `u = tmp` is a sign-extend that combine folds to a copy, but cse can't equate u with t because the path goes through a HImode pseudo (different mode). So the trick is: insert a HImode pseudo between the two SI variables.

Apply to our second copy: 
```c
raw = t;              // SI copy (move v1,v0)
tmp = (s16)raw;       // HImode copy (may fold into raw's reg)
t = tmp;              // sign-extend back to SI → move v0,v1
```
cse: raw ≡ t; tmp = (s16)raw (HImode); t = tmp → t = (s16)raw = (s16)t = t → deleted? Hmm, cse's reg_eqv: after `raw = t`, raw and t are in the same equivalence class (SI). `tmp = (s16)raw` — cse might not equate tmp with anything (different mode). `t = tmp` — t gets the value of tmp; since tmp is a different pseudo, cse sets t ≡ tmp? But t is already in a class with raw; conflicting? cse would need to handle. The func_80182ED4 case shows the HImode copy survives when the SI var (u) is NOT already equivalent to t. Here raw IS equivalent to t.

So first break the raw ≡ t equivalence using the HImode trick:
```c
tmp = (s16)t;    // HImode copy of t
raw = tmp;       // raw = sign_extend(tmp) → move v1,v0 (survives, cse can't equate raw with t)
t = raw;         // t = raw → SI copy; cse equates t with raw? 
```
Hmm, `t = raw` where raw is a separate SI pseudo → cse equates them and merges (t gets raw's register v1). That would kill the second move and put t in v1. Not target.

Unless we make t's assignment also go through a HImode temp:
```c
tmp = (s16)t;    // copy 1: tmp ← t
raw = tmp;       // copy 2: raw ← tmp
tmp2 = (s16)raw; // copy 3: tmp2 ← raw
t = tmp2;        // copy 4: t ← tmp2
```
That's 4 copies; target has 2.

Hmm. Actually maybe some of these coalesce: tmp and raw might coalesce (raw = sign_extend(tmp) in same reg → no move). tmp2 and t coalesce. Then we'd have: move v1,v0 (tmp=t, where tmp/raw in v1) and move v0,v1 (t=tmp2). That's exactly 2 moves! Because:
- tmp = (s16)t: tmp gets v1, t v0 → move v1,v0.
- raw = tmp: raw coalesces with tmp (same value, same reg) → no insn.
- tmp2 = (s16)raw: tmp2 coalesces with raw (v1) → no insn.
- t = tmp2: t gets... hmm, t is already in v0. t = tmp2 is a copy from v1 to v0 → move v0,v1.

But cse might equate raw with tmp, tmp2 with raw, and then t = tmp2 → t ≡ tmp2... but t is already a pseudo that was copied into tmp. cse's reg_eqv: after `tmp = (s16)t`, does cse equate tmp with t? Different modes → no (that's the trick). After `raw = tmp` (sign_extend), raw is SI, tmp HI → no equation. After `tmp2 = (s16)raw`, tmp2 HI vs raw SI → no. After `t = tmp2`, t SI vs tmp2 HI → no equation. So all four copies survive in RTL, but the allocator coalesces adjacent ones (tmp/raw, tmp2/raw?). Hmm, tmp and tmp2 are different pseudos but both copy raw... they'd be in the same register v1.

Would combine fold these sign-extends into copies? For `raw = (s32)tmp` where tmp is HImode: sign-extend HI→SI. On MIPS, sign-extend from HI in a register = sll/sra (2 insns) unless gcc knows the value is already sign-extended. tmp = (s16)t where t is known 0..239 → combine knows tmp's value is 0..239 → sign-extend is a no-op → plain move. Similarly for tmp2.

But wait, does `t = tmp2` produce a move? If tmp2 is known 0..239 and t SI, the sign-extend folds to a copy → move v0,v1. Yes.

So this might work! But it's 4 source copies producing 2 asm moves — that's fine as long as the asm matches.

Hmm, but the allocator: t is in v0. tmp in v1? Local-alloc priorities... Let's just try.

Actually, maybe simpler with 2 source copies:
```c
tmp = (s16)t;    // HImode copy
t = tmp;         // sign-extend back
```
cse: tmp = (s16)t (no eq), t = tmp (no eq, cross-mode) → both survive in RTL. Combine folds both sign-extends to plain copies. Allocator: tmp and t... `tmp = (s16)t` is a move from v0 to tmp's reg; `t = tmp` a move from tmp's reg to v0. If tmp is in v1, we get exactly move v1,v0 and move v0,v1! And this is exactly the round-trip through a HImode temp.

But in n5/n8 I did `tmp = (s16)raw; t = tmp;` — with raw involved. n8 was `tmp = (s16)t; t = tmp;` — that's exactly the 2-copy version! It scored 12 (46 ins). Hmm.

Let me check n8's RTL to see whether the copies survived in RTL and were coalesced by the allocator (tmp in the same reg as t).

Actually with `tmp = (s16)t; t = tmp;`, the allocator sees tmp and t as two pseudos; t's live range spans both. tmp's live range is short (from the copy to t=tmp). Local-alloc might give tmp the same reg as t (copy preference!) — the copy `tmp = t` prefers tmp = t's register. That's the coalescing. Then `t = tmp` is move v0,v0 → deleted.

To prevent coalescing, we need tmp to have a *conflicting* preference. In func_80182ED4, the copy was `u = tmp` where u was a different variable used later, and it survived because... hmm, u's copy preference would also be tmp's reg.

Wait, in that case: `tmp = (s16)t; u = tmp;` then later `t = u - 1`. The target has `move v1,v0` = u = t. So u got v1, t v0. The allocator gave u a different reg from t even though u = tmp = (s16)t. Why? Because u is live across the branch and... hmm, copy preference ties u to tmp; tmp ties to t. Chains of copies — gcc's local-alloc can coalesce chains but maybe the HImode breaks the preference chain? "The HImode copy escapes cse2's equivalence class" — and the register allocator's copy preferences are set by REG_EQUIV/copy hints? Hmm.

In our n8, the round trip may have given tmp a preference for t's reg on both sides, so it coalesced.

Let me check n8's asm: 46 ins, same as n1 — meaning no moves at all and the same register assignment? The diff would show. Let me score-diff n8.

Actually, let me instead try the 4-copy version (n12) and also a version where tmp is used in a way that forces a different register.

Let me think about what forces tmp into v1: in the target, raw (v1) is created before the branch and lives across it (used after). If our tmp lives across the branch, local-alloc must keep it in a register; and if t is also live across the branch, they need different regs. That's the key: both live across the branch → separate registers.

So: place the first copy BEFORE the branch, and the second copy AFTER. That's exactly func_80182ED4's structure ("hoist it above the branch so the copy and its use land in different blocks").

Our target: `move v1,v0` is in the bgez delay slot (before the branch's taken path, i.e., the copy is after the branch in RTL but reorg moved it). Hmm, in the RTL the copy insn 42 is AFTER the branch (join block). But if we put our first copy before the branch in source, the RTL would have it before the branch, and the target's asm has it in the delay slot — reorg could move a pre-branch insn into the delay slot? No, reorg fills delay slots with the instruction following the branch.

Hmm wait. Let's re-look: target asm:
```
4e4 bgez v0, 4fc
4e8 move v1,v0      ← delay slot
4ec jal ...         ← taken path? 
```
If bgez jumps to 4fc when t>=0, then the fall-through (not taken, t<0) goes to 4ec (jal). The delay slot 4e8 executes always. The move v1,v0 comes from the join block (after the if). Reorg moved it into the delay slot because on the t<0 path raw is dead. So in source, the copy is after the if.

If I put the copy before the if in source, the RTL order would be: addiu, copy, bgez. Reorg would fill the delay slot from the insn *after* the branch... there is none (the branch's taken path). Hmm, the delay slot would then be filled from the taken target's first insn maybe. That changes the layout.

So to match, the first copy must be after the if in source (join block), and reorg pulls it into the delay slot. And for the allocator to keep raw in a different register, raw must live across the branch? No — raw is born after the branch (insn 42), so it doesn't live across.

Hmm, but then how does the pinned version keep v1? Because it's a hard register.

In the func_80182ED4 case, the copy was hoisted above the branch so u lives across the branch → forced separate register.

For us, maybe we can hoist `raw = t` above the branch (source order) and still get the same asm if reorg/sched places it. Let's think: source:
```c
t = raw - 0x10;
raw = t;          // copy before branch
if (t < 0) { call; return; }
t = raw;          // copy after
stores
```
RTL: addiu; copy; bgez. The bgez delay slot: reorg picks the insn after the branch (which is in the taken path or the join). Hmm, layout: bgez jumps to the join label (after the call). The fall-through is the call block. So after the branch in layout: call block. The delay slot would be filled from the call block or be nop. The copy is BEFORE the branch, so it stays before. That gives:
```
addiu v0,v1,-16
move v1,v0
bgez v0, join
...
```
Not target (target has the move in the delay slot, after bgez).

So the copy must be in the join block.

Then how to force raw into a different register from t? If raw is only live in the join block from the copy to `t = raw`, the allocator has no reason to give it a different reg... except the copy itself: if it coalesces raw with t, the move disappears.

In the target, the pin forces it. In plain C, we need a reason.

Hmm — what if raw's live range extends beyond `t = raw`? E.g., use raw after:
```c
raw = t;
t = raw;
... stores use t ...
```
raw dead.

What if raw is used in the stores too? Then it's the same value, cse merges.

What if we make raw live across a *call*? The next call is func_80012ABC, after the stores. If raw were used after that call, it'd need a callee-saved reg — that changes everything (s-registers).

Hmm.

OK here's another thought: what if the second copy `t = raw` is the one that's a HImode round trip, and the first `raw = t` is a real copy with a separate reg because raw is *used* later in a way that extends its life?

I keep going in circles. Let me look at the actual pinned RTL insn 44: `v1 = asm(v1)`. The asm's output is a hard reg v1. This forces v1. In plain C there's no way to force a hard reg without a lever.

Given the constraints (no register vars, no asm), I suspect this item may be a genuine WALL. But let me try a few more structured ideas, and also check the *other* 4 items — maybe they're easier and I should allocate time.

Actually wait. Let me reconsider the problem completely. What if we DON'T need raw and t to be separate at all, but instead the target's `move v1,v0`/`move v0,v1` can be produced by a different structure: e.g., the loaded byte value lives in v1 and is copied to v0 for the addiu:

```
lbu v1,36(s1)
lw a0,76(s0)
addiu v0,v1,-16
```
This is just: raw in v1, t = raw - 16 in v0. That happens naturally if raw and t are separate pseudos with raw in v1, t in v0. In n1, the load pseudo got v0 (merged with t). If we keep `raw` as a separate live variable across the addiu... it already is: raw = lbu; t = raw - 16. raw dies at the addiu. So the load result and t are separate pseudos but local-alloc gave the load result v0 and t v0 too? In n1's asm: `lbu v0,36(s1); addiu v0,v0,-16` — the load result and t coalesced into v0. In target: lbu v1; addiu v0,v1,-16. So the load result is v1 and t is v0.

Why would local-alloc give the load result v1 and t v0? The load result (pseudo A) dies at addiu; t is born at addiu. They can't coalesce if... hmm, they're different pseudos; local-alloc assigns each independently but with a copy preference? A is the operand of t = A - 16; not a copy, so no preference. Both are short-lived. Local-alloc gives v0 to whichever has higher qty priority. In n1, t got v0 and A got v0 too? Actually if A dies at insn 2 and t is born at insn 2, they can share v0. In target, A is in v1 and t in v0.

Hmm, that's a qty/priority difference: with the pin, raw is hard v1 (insn 20: v1 = zero_extend(load)), so the load result goes to v1 via the copy, and t (pinned v0) gets v0.

So in the target, the load's zero-extend is copied into the pinned v1. The load result pseudo is in... insn 17 loads QI 78, insn 18 zero-extends into 79, insn 20 v1 = 79. After optimization, the lbu directly targets v1.

OK. Let me try yet another approach: maybe I can get the desired register split by making the byte load's result *live longer* — e.g., use `raw` after the stores in a dead-but-not-eliminated way? That would add instructions.

Hmm, let me consider: what if `raw` is a `u8` and we store raw *and* t? No.

Let me take stock of time. It's 22:09 start; now maybe 22:35. I've spent ~25 min on item 1 with ~12 tries. Let me try a batch of ~10 more variants (reaching ~20 tries), then if nothing, consider the WALL budget requires ≥30 tries and ≥20 min. I should do at least 30 tries before WALL.

Let me think of 10 more distinct variants:
1. Two HImode hops (n12): tmp=(s16)t; raw=tmp; tmp2=(s16)raw; t=tmp2.
2. `raw = t;` before the branch + `t = raw;` after (statement order).
3. `raw = t;` and stores use raw, plus `t = raw` unused? no.
4. `t = raw` where raw is u8 and t s32: raw = t (QI copy), t = (s32)raw — tried n2.
5. Use `*(u8*)` store from raw and a separate t: hmm.
6. do-while around `raw = t` (splits EBB) — tried n4.
7. do-while around both — n3.
8. Declare t as `volatile`? Not allowed? volatile is a lever (barrier kind). Not allowed.
9. Use a struct field? no.
10. Use `t = raw; raw = t;` reversed order... semantics differ.
11. Make the call path use t? e.g. `if (t < 0) { ...; return; }` — no.

Hmm, what about making raw and t *different types with the store using t*: raw s32, t u16? Then t = raw - 0x10 (HImode), addiu... compare t < 0 in HImode → sll/sra. No.

Let me reconsider: maybe the target's structure can be produced with `raw` being a **pointer-cast byte** trick: e.g. load via a `u8 *pbyte = ...; raw = *pbyte;` no.

Let me look at the *pinned* target's later passes to see if maybe there's a different source structure that yields the same. Hmm.

Alternatively, maybe there's an existing cracked item with the same shape: pin $3 + $2 with launder, where win.c exists. Let me search the shard dirs for items with kinds containing "launder,pin" that MATCHed, and check their structure. moves.md lists many. E.g., line 4: func_8017F584 MATCH — "field post-decrement per arm". Not ours.

Let me grep the G22 list: all 5 items are launder,pin. The shard was presumably built from *uncracked* items. The moves.md lines that are MATCH with launder,pin: line 7 (func_80185944) PARTIAL, line 15 (func_80180E40) MATCH — "pin redundant; u16 var_s4 + (u16)(var_s4 - 0x1000) < 0x11 keeps the andi". Hmm.

Line 44 (func_80186368) MATCH — launder+pin.

Let me look at func_80180E40's win.c — it's a "pin redundant" case. Not our shape.

OK, let me try the batch. I'll write a script to generate variants and score them all with sc.sh (one line each). Let me be efficient.

Variants (all start from n1 = raw/t s32):
v1: raw = t; tmp=(s16)raw; t=tmp;   [tmp between]
v2: tmp=(s16)t; raw=tmp; tmp2=(s16)raw; t=tmp2;  [two hops]
v3: t = raw - 0x10; raw = t; before if; t = raw; after
v4: raw = t; do { } while(0); t = raw;   [empty do-while between]
v5: raw = t; t = (s16)raw;   [second copy via cast]
v6: raw = t; t = (u8)raw;
v7: raw = t; t = raw + 0;  (folds)
v8: t = (s16)raw; raw = t;? 
v9: raw = (s16)t; t = raw;  (first copy via cast)
v10: raw = t; t = *(s16*)&raw;? no.

Also consider: make raw and t `s32` but declare `raw` *inside a do-while scope* to split blocks.

Let me generate v1-v6 and v9 quickly.

Actually, thinking about it more: the fundamental issue is the copy preference coalescing. In func_80182ED4, the surviving copy `u = tmp` worked because u's live range extends across a branch and u is used in the else arm. In our target, `raw` is dead after the copy back. So there's no pressure.

BUT: what if we make the copy `raw = t` happen BEFORE the branch (so raw lives across the branch), and the second copy `t = raw` after? Then:
- raw lives across the branch → it must be in a register at the branch; t also lives across. Two values live across → different registers (or same if coalesced — but coalescing raw with t would make raw=t, and then the copy before is free... hmm, gcc would coalesce them into one register, deleting the first copy, and then t=raw also deleted).

Coalescing happens when the copy's source and dest can share a register without conflict. If raw is live across the branch and t is too, and raw = t (they hold the same value), they COULD share. GCC's local-alloc would prefer to coalesce. Unless there's a conflicting use.

Hmm.

In func_80182ED4, why didn't u coalesce with t? Because u = tmp (HImode) — the copy preference chain through the HImode pseudo. The HImode breaks the preference? Actually local-alloc's copy preference: for `u = tmp`, u prefers tmp's reg. And `tmp = (s16)t` gives tmp a preference for t's reg. Chain: u→tmp→t. GCC's local-alloc doesn't do chains, only direct preferences; so u prefers tmp's reg, and tmp prefers t's reg. If tmp is allocated first to t's reg (v0), then u prefers v0 — conflict? u and t are both live across the branch (t used in the branch test, u used in the else), so u can't take v0 → u goes to v1. Then the move u=tmp survives.

In our case: `tmp = (s16)t; raw = tmp; ... t = raw;` — hmm, we want raw to live across the branch and be used after. Let's construct:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
tmp = (s16)t;        // copy t→tmp
raw2 = tmp;          // hmm, we want raw
if (t < 0) { call; return; }
t = raw;             // copy back
```
But then the first copy is before the branch, and the target has it in the delay slot (after). Hmm, but maybe reorg/sched will place it in the delay slot anyway? If the copy is before the bgez in RTL, it can't be in the delay slot.

Hmm, actually wait. Let me re-examine the target asm: is the `move v1,v0` really in the delay slot, or could it be at the end of the fall-through path? Layout:
```
4e4: bgez v0, 4fc     (branch taken if t>=0)
4e8: move v1,v0       (delay slot)
4ec: jal func_80146CA0  (t<0 path)
4f0: move a0,s0
4f4: j 560
4f8: nop
4fc: move v0,v1       (t>=0 path)
```
Yes, 4e8 is the delay slot. And it's `raw = t` which in source is after the if. Reorg moved it up into the delay slot (a common reorg behavior: it can fill a delay slot from the instruction at the branch's target or from the fall-through; here it moved a join-block insn).

Hmm OK.

What if the source has the copy before the branch? Then RTL: addiu; move; bgez. Reorg: the insn after the branch in layout... Let's just test it. Statement order is a real-C move.

Let me just generate and score a batch of ~8. Time-box: this is the last batch for item 1 before WALL consideration.

Actually, let me reconsider the whole thing once more. Is it possible that the target asm is achievable by keeping `raw` and `t` as separate *parameters*/values where raw is the loaded byte and t is the "adjusted" value, with the copies being part of a *different expression*? 

For example:
```c
raw = *(u8 *)((u8 *)s1 + 0x24);
t = raw - 0x10;
if (t < 0) { ... return; }
raw = t;
*(u8 *)((u8 *)s1 + 0x24) = *(u8 *)((u8 *)s1 + 0x25) = *(u8 *)((u8 *)s1 + 0x26) = raw;
```
This is one copy. The store reads raw (v1). But target's sb reads v0 (t). Hmm, but what if the allocator puts raw in v0 and t in v1? Then `sb v0` would match! And `move ?` — one move (raw = t: move v0,v1). The target's other move (move v1,v0) would be missing.

OK whatever, let me test the batch.

One more idea that's promising: use the `do { } while (0)` to split the EBB *and* keep raw live: 

```c
raw = t;
do { t = raw; } while (0);
```
tried.

Let me also try:
```c
raw = t;
t = (s16)raw;   // second copy through HImode? but no temp
```
Hmm `t = (s16)raw` — t is s32, so it's a sign-extend assignment. cse: raw ≡ t; (s16)t → t → deleted.

What if the ORDER is reversed: first copy back then... no.

Let me look at this from the "dead reset" angle (C0414): `raw = t; raw = 0; ...` no.

Actually — WAIT. What about making `raw` and `t` different *pointer-typed* variables? no.

Let me try the batch now. I'll generate 8 variants.

Actually, one more important thought: maybe I should check whether the *store* is what pins v0. The sb instructions store t. In the pinned version, t is v0 (pinned). In lever-free, the store value pseudo is the QI subreg of t; local-alloc gives it t's reg (v0) via copy preference. Fine.

Let me just do the batch.
