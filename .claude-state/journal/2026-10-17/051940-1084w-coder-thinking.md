---
ts: 2026-10-17T11:19:40.146Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm saving my best lever-free candidate as best1.c for now, then turning back to the remaining case—exploring whether restructuring the condition so `m` gets defined in the preheader block could satisfy the same-block requirement for the combine, since the target loads b[0] in the preceding block.

I'm digging into whether cse could fold away the `and` through its own equivalence table, wondering if m's known value as a zero-extended halfword load would let cse simplify `(and (zero_extend X) 0xffff)` directly—but I don't think that fold existed in this old gcc version. The deeper problem is that if cse simplifies it outright, it just becomes a copy and the equivalence check fails, so I need some later pass like combine or reload to do the simplification instead while cse leaves it alone; I'm now looking at insert_regs and the REGNO_QTY_VALID_P logic to see if there's a mode mismatch condition I can exploit to stop cse from registering the equivalence prematurely.

I keep trying simplifications like multiply-by-one or shift-by-zero, but cse likely folds those away too. I'm now wondering if the class gets broken through record_jump_equiv's merge step, where the equivalence from the branch comparison gets combined with the existing class for m.

Another angle: maybe I don't need an exact match at all — a score-1 near-match could still work if I force a conflict between k and m by giving k a second lifetime elsewhere, so expand_preferences refuses to merge them even without an equivalence trick.

Let me try the hard-register conflict angle instead: maybe m conflicts with a3 while it's set for a call, but m's lifetime starts after those calls, so that doesn't work either. I could also consider whether m has a stronger copy-preference toward v1 through some return-value path, but that doesn't fit since m isn't tied to v0 or v1 that way — so maybe the k3 preference itself needs adjusting instead.

I'm now exploring whether k's preferences could propagate into m via expand_preferences when m is the SET_SRC of a copy that dies immediately, since that copy direction always applies both ways. Another angle: maybe t3v's value shouldn't depend on the register m at all, but instead on memory state that cse has already invalidated through an intervening store — though placing that store in the preheader doesn't quite give valid code. Going back to the core setup, I want m in v1, a copy into a3, then a shift computing t3v from v1 — so perhaps if k equals m and t3v is computed as k times 4, I could get the reorganization to rewrite the shift source accordingly.

I'm checking whether m fails to coalesce with a3 simply because k lacks an a3 preference while j outranks k on priority, which requires j's reference count to hit at least 14 while k's stays at 10 or below — and I've already pinned k at 13 in this scenario, so j needs 14. I'm tracing whether j's reference count could be inflated by being reused elsewhere in the function, like a second definition for a call argument, which would add enough weight to push j's priority score above k's — but that particular scoring attempt came out to 10 instead, so something must be suppressing it.

That suppression looks like CSE folding the constant assignment directly into the call argument as an immediate load, which kills that definition of j before it ever reaches flow analysis — so it contributes zero references, mirroring the same constant-folding trick I saw with the shared size variable earlier. To avoid that fold, I'm considering making j's second lifetime depend on a non-constant value, like assigning it from another variable before the call, so CSE can't collapse it away and it actually counts toward j's reference total.

If j were a global pseudo assigned to a2, its computation would land there too, but the target code shows the result going through v0 with shifts for sign-extension, not a2 — so that doesn't match either. Looking earlier in the target, a2 at one point holds the sign-extended value of i itself, used as the third argument in the first branch's function call, so maybe that's where the a2 slot actually comes from.

If j is just an alias for i in that branch — set once, then used in the comparison, the array index, and the call argument — its reference count at that nesting depth would be high enough to dominate register allocation, likely winning the a2 slot outright given the lifetime weighting.

That said, I think the stronger candidate remains the u_m family with the zero-extend score, and I'm now checking whether a natural masking operation like `andi` could actually surface as a plain `move` for a 16-bit cast of a SImode value.

Looking closer at the diff: line 50 shows lhu vs lh (K3 call with k=u16 getting zero-extended), and lines 142-143 show a plain move where k is assigned, with the loop using addu without any andi mask. That's surprising since k's zero-extension seems to just vanish — maybe cse recognizes m's extension in one block but not the other, or some hoisting pass drops the mask. Either way, the result is a bare addu instruction with no masking.

So there are two issues with ku16_m: the register allocation lost the K3 preference (k as a zero-extended u16 gets passed as the 4th arg rather than copied), and K3's load becomes lhu instead of lh because k is unsigned. One fix is to flip k to signed (ks16_m), but that brought back an unwanted sll/sra pair. Another idea is casting k to s16 at the call site so the argument becomes a sign-extension instead — if k was loaded via lhu, that sign-extend might combine differently and avoid the extra shifts.

However, if k itself is declared s16, its load into the HImode register could combine with the sign-extend at the call site, letting the compiler merge them directly into a single lh instruction, which is exactly the pattern I want for a3.

But then I realize the preference tracking breaks down after combine merges the load and sign-extend, since k's pseudo disappears into the combined instruction, losing the copy preference that would have steered allocation to a3. Comparing priorities between j and k by their live ranges and reference counts, k edges out j only slightly, not enough to flip the register assignment.

I'm trying reordering k's definition earlier relative to j to see if adjusting birth order shifts the live-range math in j's favor, but it's a frustratingly close margin either way.

Let me reconsider k's reference count instead: maybe CSE can collapse the repeated zero_extend of k across arm B's two uses into a single shared temp, cutting k's effective refs down and changing the ratio enough to flip the comparison.

I'm puzzled why the final code shows no andi — maybe combine determined k's upper bits were already known zero from how it was assigned, or some HImode promotion rule eliminated the mask. Without certainty on that, I want to check the allocation table for ku16_m directly to see k's actual ref count and whether K3 appears there too.

Now I'm trying a different variant: remove K3 and make k a block-local u16 variable set by copying m, then indexing the array with m instead of k, to see if that reproduces the pattern seen in ku16 on the ak case.

The in-loop copy still fails, so I'll save the score-1 body as the current best and log it. I also spotted that a u16 k copy from s32 m is a free truncating move with no extra `andi`, which only lost due to K3's preference breaking on u16 args—so I'll try it on the non-K3 `allin` body next.
