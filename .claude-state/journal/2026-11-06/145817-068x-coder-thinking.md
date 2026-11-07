---
ts: 2026-11-06T21:58:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uUByfw4DPwYRLPxNVXx2
---
Interesting! In w9:
- then arm: `li a0,1; li v1,1; j; move t2,zero` — as predicted, extra `li v1,1`.
- and the join no longer has the move: at insn 30-ish the else arm's copy... let me look: mine[32:33] `move t2,zero` — hmm.

Also the uVar5 (t3 vs t2) registers swapped — because the then arm's iv2c assignment changed things.

So w9 gives 57 ins.

Let me see the full listing of w9 to understand where the else-arm move went. Actually the diff shows at 22-25: `li v1,1` then `j` then `move t2,zero`. Then the else arm and then... where's the `move v1,a0`? Not shown in the diff, meaning it matched the target somewhere? Hmm, mine[32:33] vs target[31:32]: mine `move t2,zero` vs target `move t3,zero`. 

Let me get the full listing.

Actually, wait. This suggests the copy-in-both-arms approach does produce the move in the else arm (matching), but adds the then-arm one.

Idea: make the then arm's `iv2c = iVar2` combine into the `li a0,1` so that only ONE insn results — i.e., the then arm produces `li v1,1` and drops `li a0,1`? But iVar2 (a0) is used later (at the `sll` for r). Hmm, in the target iVar2 is a0 and is used at insn 42.

Unless... in the then arm, iVar2 = 1 and it's used later, so `li a0,1` must stay.

OK so w9 is 57. 

What if we only assign iv2c in the else arm and, in the then arm, rely on iv2c being... no, undefined.

Hmm, what about the reverse: the copy in the then arm only, and the else arm... no.

Let me reconsider. Since the target's move is the reload tie, and reload ties only come from asm/calls... 

Wait, actually maybe there's another source of a copy at reload: **a register class conflict**. If iv2c must be in a class that excludes the source's register... e.g., if iv2c is used as an operand with a constraint.

Hmm, what about **function argument setup**: if iv2c were passed to a call, it'd be moved to a0. There's no call there.

What if the value is used as an *array index*? no.

Let me look at this from yet another angle: maybe the copy can be avoided entirely if the compare's operand naturally lands in v1. What determines the compare's operand register? The compare is `beq X, v0` where v0 = one (pinned). X = the value. In mine, X = iVar2 (a0). Why is iVar2 in a0? Because the else arm computes t+1 into a0 — a0 is a caller-saved temp; the target also has a0 there.

If instead the value in the compare were a *different* pseudo allocated to v1... but the compare's operand must be the same value as iVar2.

Hmm, what if we make the comparison use `uVar5`-style code... no.

Let me reconsider the whole shape: is the move really required? The target has 56 insns; ours 55. Yes.

What if we add an instruction elsewhere and remove... no, the diff positions show everything else matches.

OK, let me try the "second use" diagnostic to confirm combine is the blocker, using a *cheap* second use that the target might tolerate: what if iv2c is used in the `uVar1` computation in place of uVar5? No, different value.

Hmm, actually here's a thought: what if the compare is `if (iv2c != one) uVar5 = 0;` and we ALSO use iv2c in the else arm's... no.

Let me try: declare iv2c at function scope and use it in the `r` line (replacing iVar2), and keep iVar2 alive by ALSO using iVar2 in the r line — as `r = (uint)((iVar2 + 0) << 3)` no.

Alternatively keep iVar2 alive by using it in the uVar1 line: `uVar1 = p4s | (param_3 & 0xffff) | uVar5;` — the target's or chain: `andi v0,a2,0xffff; or v0,a3,v0; or v0,v0,t3`. Adding iVar2 would add an or.

Hmm.

What if iv2c is used in a *dead* statement that flow deletes — but flow runs before combine? Order: cse1, loop, cse2, jump, flow, combine. Flow deletes dead code before combine. So a dead use would be removed by flow before combine — but flow runs BEFORE combine, so if flow deletes it, combine sees no use. 

What if the use is in a place flow keeps but combine's window doesn't reach? E.g., use iv2c far later (beyond 3 insns) — combine's window is limited to 3 consecutive insns, so a use 5 insns later wouldn't merge the copy into THAT use... but the compare is still 2 insns later, and combine would merge the copy into the compare (using the compare's use).

Right — the copy is used by the compare. That's the problem. Any extra use doesn't stop combine from merging the compare's use unless the dest is live after i3.

Hmm, "live after i3" — combine checks REG_DEAD on i3. If iv2c is used later, flow adds a REG_DEAD at the LAST use, not at the compare. So combine sees no REG_DEAD for iv2c at the compare → added_sets_1 = true → it would have to keep the copy → not profitable → reject. 

So a second use later WOULD block the merge. And we need iVar2 to stay live so local-alloc doesn't coalesce.

So: iv2c used at the compare AND later; iVar2 used later too.

Where can we get a free later use of iv2c? The `r = (uint)(iVar2 << 3) | c6b;` line uses iVar2. If we change it to use iv2c, iVar2 dies at the copy. Unless iVar2 is used elsewhere as well.

Wait — is iVar2 used anywhere else? Let me check the body: iVar2 is assigned in the if/else, copied to iv2c, and used in `r = (uint)(iVar2 << 3) | c6b`. That's it.

Hmm, but what if the copy is `iv2c = iVar2` and the r line uses `iv2c`, and iVar2 is kept alive by... the `uVar1` line? Let me look at the target's use: `sll v0,a0,0x3` — a0 = iVar2. So the target uses iVar2 there.

OK so we need iVar2 alive at r AND iv2c used later. There's no such use.

UNLESS: we make the compare use iv2c twice? `if (iv2c != one && iv2c != one)`? folded.

What about `if (iv2c != one) uVar5 = 0;` and then a *second* use in the uVar1 line via a value that's already there... 

Hmm, what about `uVar5`? The compare sets uVar5 = 0 conditionally.

What if we write the compare as:
```
if (iv2c != one) uVar5 = 0;
else uVar5 = uVar5;
```
No.

Hmm, what about using iv2c in the *store* expression? `puVar3[-1] = uVar1` — no.

OK, radical idea: what if we make the *source* iVar2 live after by using it in the tail, and the *copy* be used at the compare and later in `r`. Then both are live: iv2c at the compare and r; iVar2 at the copy and r. E.g.:

```
iv2c = iVar2;
one = 1;
if (iv2c != one) uVar5 = 0;
...
r = (uint)((iVar2 << 3) | (iv2c - iv2c)) | c6b;   // identity launder — no.
```

Hmm.

What if r uses iv2c and iVar2 is used in the uVar1 or chain in a *legitimate* way? uVar1 = p4s | (param_3 & 0xffff) | uVar5 — adding iVar2 changes semantics.

Hmm, is iVar2's value ever legitimately used besides r? In the original source, iVar2 is the "packet count"? Actually iVar2 is used for r only.

So we can't have both live.

Therefore: to block combine, we need the dest live after i3, which requires a later use we can't afford.

Alternative: block combine with a block boundary. jump1 must keep the label. When does jump1 keep a label between the copy and the compare? If the label is targeted by a jump. We could add a branch... but that costs an insn.

Hmm, unless the branch replaces an existing one. Let's look at the structure:

```
            if ((short)iVar4 != 0) {
                six = 6;
                if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
                else { ... }
                iv2c = iVar2;
                one = 1;
                if (iv2c != one) uVar5 = 0;
                uVar1 = ...;
            }
```

What if the compare is moved INTO the else arm and the then arm... no, target has it shared.

What if we use a `goto` to jump into the compare block from the then arm, with the copy placed between the else arm and the compare?

```
            if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; goto CMP; }
            else { ... }
            iv2c = iVar2;
        CMP:
            one = 1;
            if (iv2c != one) uVar5 = 0;
```
Then: the copy is in the else block (fall-through), and the compare is in the CMP block (target of the goto from then). The label CMP is kept (2 predecessors). Combine can't merge across the label!

But semantics: on the then path, iv2c is not assigned. We need iv2c = 1 there. Hmm — but wait: what if we assign iv2c in the then arm as well? That's the 57-insn problem.

Unless... the then arm's iv2c assignment is FREE because it can be merged into the existing `li a0,1`? If the then arm does `iVar2 = 1; iv2c = iVar2;` — combine folds `iv2c = iVar2` to `iv2c = 1` = `li v1,1`, and `li a0,1` stays. 2 insns.

But what if we write the then arm as `iv2c = 1; iVar2 = iv2c;`? Then iVar2 = copy of iv2c → `li v1,1; move a0,v1` — 2 insns.

What if the then arm writes `iVar2 = 1; uVar5 = 0;` and iv2c gets 1 via the *compare*: `if (iv2c != one) uVar5 = 0;` with iv2c uninitialized on that path... In C, that's UB, but we could initialize iv2c = 1 *before* the if:

```
            int iv2c;
            iv2c = 1;
            if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; goto CMP; }
            else { ... }
            iv2c = iVar2;
        CMP:
            one = 1;
            if (iv2c != one) uVar5 = 0;
```
That adds an initialization insn (li v1,1) — extra.

Hmm.

OK, what if the then arm jumps to the compare and the copy is executed only on the else path, but the then path's iv2c is set by... 

Hold on! What if we restructure so the copy is in the *join* but the compare is in a separate block reached by a goto from both? That needs a branch.

Hmm.

Let me reconsider the do-while: it didn't split. Why? Because jump1 merges blocks when the label has a single predecessor and the jump is to the next insn. In C0535's successful case, the do-while DID split — maybe because the copies were stores/loads, not because of jump1 but because of cse1's EBB calculation: cse1 splits EBBs at labels that have more than one predecessor... 

Hmm, actually in the successful cases, the do-while body contained insns that cse1 couldn't merge, so the split had an effect on scheduling. In our case the effect we need is combine blocking, which requires a real label at combine time (after jump1/flow). jump1 deletes the label.

So do-while won't block combine.

Let me now consider whether combine could be blocked by making the copy's source register *modified* between the copy and the compare. Combine's can_combine_p: "Make sure that the value that is to be substituted for the register does not use any registers whose values alter in between" — but only when `!all_adjacent`. Adjacent insns skip this check. Since i2 (li v0) is between, all_adjacent is true (next_active_insn(copy)==i2 and next_active_insn(i2)==compare). So the check is skipped.

Hmm, what if I make the insns NOT adjacent by inserting a NOTE? next_active_insn skips notes. What about a CODE_LABEL? skipped by next_active_insn? Let me check: next_active_insn skips NOTE, CODE_LABEL, BARRIER. Hmm, so even a label doesn't break adjacency by that definition... but `prev_nonnote_insn` (used to find i1/i2) stops at CODE_LABEL? In try_combine:

```
  if (! prev_nonnote_insn (i3) ...)
```
Hmm, combine's main loop uses `prev_nonnote_insn` which skips notes but NOT labels? Actually in 2.7.2 `prev_nonnote_insn` skips NOTE_INSN only... Let me check: rtl.c/emit.c defines prev_nonnote_insn as skipping NOTE, BARRIER, CODE_LABEL? In GCC, `prev_nonnote_insn` skips only NOTEs; `prev_active_insn` skips labels too. Hmm, but there's `if (GET_CODE (insn) == CODE_LABEL) continue;` in combine's loop maybe.

Let me check combine_instructions' loop to see how it walks.
