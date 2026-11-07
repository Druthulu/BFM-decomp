---
ts: 2026-11-06T17:34:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gStQbaauXkNSeTulMqLq
---
Time 8.8 min. All 7.

Let me look at the preference source definitively: dump the sched1 RTL (nd.i.sched) and look at the insns 396-427 with REG notes; and check the local-alloc dump's block for 75's neighbors.

Actually, here's a cleaner experiment: if the preference is v1, then making v1 *unavailable* at 75's allocation would force another reg. What if we add another live value in v1 at that point? That would change code.

Alternatively, understand: preference 3 (v1). In the target (pinned), the temps: 148=v1. So the target's 148 (the >>16 temp) is in v1 — the same register as the preference! That's because 75 is fixed in v0, so 148 (which must differ from 75's v0 at 423) gets v1.

In nopin, 75 prefers v1 and gets it; then 148 must avoid v1 (75 live at 423) → gets v0.

So the preference for v1 is the root. If the preference were absent, global-alloc would give 75 the lowest free reg not conflicting with the local temps. The local temps in that block: 148 (v0), 149 (v1), 150, 151. 75 is live at 423 (148's def) and 424 (149's def) → conflicts with both v0 and v1 → 75 would get a0 or t-regs. That's not the target either (target: 75=v0).

Wait, in the target, 75=v0 and 148=v1: 75 is live at 423 where 148 is defined. They're different regs, fine. 149=v0: 75 dies at 424 (the REG_DEAD is on insn 424), so 149 can reuse v0.

So the target's assignment is self-consistent with 75=v0. For lever-free to get 75=v0, the local-alloc temps must not take v0 *before* 75's allocation. But local-alloc doesn't know 75's reg — it assigns 148 first (v0).

Unless 75 is block-local (assigned by local-alloc together with the temps by priority). If 75 were local to the join block (defined and used there), local-alloc would allocate 75 and the temps together: 75 (4 refs) vs 148 (2 refs) → 75 wins v0!

Can we make 75 block-local? Its defs are in the then/else blocks. If we compute sh16 in the join block instead:
```
s32 a;
if (r[0x49] == 5) { a = angle << 16; } else { ... a = p[0x79] << 16; }
sh16 = a;  // in the join block
```
Then sh16 is defined in the join block and used there → local! But that adds a copy (move) in the join block — an extra instruction vs the target.

Hmm, but the target's sh16 is defined in the arms (sll in the delay slot / in the else path). So the target's sh16 is global.

Unless... the target's sh16 is actually local because the arms' blocks are the same extended block? The defs are in two different blocks (the if arms) — global.

OK so lever-free, 75 is global and the preference v1 decides. The wall tag: `global-copy-pref`? The preference is from local-alloc's combine (a dying input tie). Tag `lreg-qty-priority` or `global-copy-pref`.

Hmm, let me try ONE more thing: the preference is a *copy* preference (may_save_copy) or a normal suggestion? If it's a normal suggestion, the first loop (just_try_suggested) gives it v1. If I can make the tie not happen by having the source live...

Let me look at the combine_regs calls for shift insns in local-alloc's block_alloc (lines ~1290-1360).
