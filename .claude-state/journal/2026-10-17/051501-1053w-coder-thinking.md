---
ts: 2026-10-17T11:15:01.671Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm realizing that with a u16 typed k, the zero-extension in the argument copy breaks the hard register preference, causing the allocation to swap back—so I should try using s16 for k instead to preserve the direct register copy.

But sign-extension for s16 k causes the same preference loss. So the K3 reuse seems to require k as a plain SImode copy to a3, while the m-k mode equivalence issue pushes toward a different mode—these two needs appear to conflict unless I introduce a separate variable shape that supplies the preference without putting it directly on k. I'm now tracing how expand_mult and convert_modes would handle a HImode m being zero-extended for the multiply, and whether CSE could still recover the equivalence there.

For mu16_m, the lhu-loaded m coalesced into a3 and the copy itself vanished from the instruction count, which suggests the zero_extend became a no-op since source and destination ended up in the same register — meaning some pass recognized the extension was already implicit from the load and dropped it entirely.

For a plain `move` to appear in the target RTL, m must actually be SImode rather than HImode, since an HImode value would require an andi-based zero extension pattern that wouldn't simplify to a bare move. So the target case likely has m as a 32-bit value copied directly into k with a plain SI-to-SI move.

But then t3v reading m instead of k after cse2 suggests m's last use occurs later in the loop than k's -- maybe the loop body itself references m again after k's final use, keeping m live through the block while k dies earlier.

I'm also considering whether the outer increment step uses m, like treating it as the updated index value, though that reading is semantically odd.

So the hoisted t3v sits in the preheader, strictly before any use of k or m in the loop -- which means under the plain-copy-plus-cse2 story, t3v can't legitimately end up reading m unless cse2 skips processing that part entirely.

I'm now checking whether cse_main's after_loop pass in 2.7.2's toplev.c handles the preheader differently, since there might be special-case logic in cse_insn tied to the after_loop flag that could explain this. Another possibility is that m stays live at the copy point because of some other instruction further down the stream referencing it.

One scenario is that m's apparent use is actually the hoisted t3v value, and cse2 fails to rewrite it because loop.c inserted the hoisted instruction after flow had already computed k's last-use UID -- meaning REGNO_LAST_UID for k doesn't reflect the loop-inserted insn.

Looking at the u_m test case more closely, it matched everything except the and-based mask, with k=(u16)m and t3v hoisted reading m. If I can get the copy's source to come from a different pseudo that cse treats differently, that might break the equivalence link cse2 is forming.

I'm checking whether this requires the copy to come from an earlier block, like loading m there and copying before the branch, but the load delay slot timing in that block makes it awkward to slot in the move instruction right after the load.

Then I'm considering whether k=i's sign-extension gets merged into m's class through jump equivalence, so that CSE redirects k's source to the shared class head—and whichever variable ends up as that head would live longer, which matters for the register allocation outcome.

Actually, k=c3 doesn't fit either, since c3 is a separate user variable tied to s8, and that path leads to a mismatched move instruction.

So I'm re-examining the jump equivalence itself as the likely source of the discrepancy, tracing through the target's comparison sequence around those sll/sra/bne instructions to see where v0 and s8 get compared and how that lines up with the expected equivalence classes.

Then I consider whether t3v = m*4 could be computed from se_i instead, but that reads v0, not v1, so that doesn't match either. Shifting focus, maybe the ordering of k=m and t3v=m*4 isn't fixed by the RTL order but instead depends on scheduling: since both instructions read m and m dies at one of them, the backward list scheduler could legally place them in either order depending on which one is treated as the leaf with the dependency edge.

In the backward scheduling pass, the instruction with higher priority gets chosen first, which means it ends up placed later in final order. So if `t3v=m*4` ends up with higher priority than `k=m`, it would be scheduled later, giving the order k, t3v that matches what I'm looking for. That priority boost could come from t3v having a dependent use elsewhere in the block, such as if the hoisted address computation in the preheader used t3v directly, giving it a priority of 2 and triggering the "birthing insn" boost logic that elevates priorities for registers live at block end.

Checking which sets qualify as birthing insns (single-set values live at exit): k, pb, m24, and mhi qualify, while j — only set once in that block — ends up with priority 1, meaning it gets scheduled earliest. But that would actually place j first in source order, which is suspicious since j is supposed to be set last for a for-loop init pattern. If j wins priority and ends up live too long, it loses the register anyway — unless preference-based allocation (K3) saves k regardless by giving it a3 by preference. So I don't necessarily need j to win on priority; what matters is whether m stays live past certain points.

Global's conflict detection runs on the post-sched1 instruction stream, and sched1 recomputes death notes for the new ordering. So I need the RTL emitted in an order that's cse-safe — meaning the read of m needs to appear before `k = m` in source order so cse doesn't collapse it — while letting sched1 reorder things so that `k = m` effectively happens differently than written.

I'm checking whether t3v's priority needs to exceed k's for sched1 to place things correctly, and whether the lui/addiu symbol-ref pairs for pb, m24, mhi, q collapse into single RTL insns matching the target assembly ordering.

Looking at the sched dump, insn 340 (the symbol_ref for pb) shows priority 1, but the m24 pair of insns 619/620 (lui then ior) seems inconsistent — I'd expect priority 2 for 619 since it depends on 620, but the dump shows priority 1 for both, so I'm trying to work out how GCC's priority computation actually handles this dependency chain.

So RTL order must be what sched1 preserves, but that creates a contradiction with the cse ordering constraint of t3v needing to be after k reads m. Let me check directly with the base preheader case: j=0, k=m, t3v=m*4 — the flow confirms t3v actually reads k's register, not m directly, so the equivalence works differently than I assumed.

I'm now wondering if there's a code label sitting between the copy and the hoisted reads, something like a label from a do-while(0) construct or similar loop idiom that later gets collapsed away by jump optimization, which could explain how a plain copy coexists with a later read of m.

Thinking about loop rotation specifically — the duplicated pre-test for the loop condition would sit before LOOP_BEG, and since it's a conditional jump rather than a label, the cse basic block would continue through it rather than splitting. I'm checking whether that pre-test gets folded away given j starts at 0.

I'm also considering whether the `k = m` copy might sit before an unfoldable pre-test, or be followed by a label from some goto target, and whether cse.c's handling of register-to-register sets has special rules in `cse_insn` around user variables that might prevent the equivalence from being recorded in the first place.

I'll check when cse actually records a register copy as an equivalence, since using a u16 for k loses K3's hard-register preference and the move to m may remain live afterward.
