---
ts: 2026-11-06T10:12:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yMcKjaNwCUeMnndPbCtC
---
v2 (`f |= cond`) replaces the branch with `xori/sltiu/or` — different code, not matching. So no.

OK so the branch form is required. The priority issue stands.

Let me think about `reg_live_length` again. f: refs4 live16. Hmm, why is f's live 16? Because it's live across the loop from `f=0` to the read. If I make f's live shorter by setting `f = 0` right before the loop... it already is right before (insn 301 then loop).

What if `f` is initialized with a value that comes from a later insn? No.

What if we split: use a loop-local variable `g` inside the loop, then `f = g;` after? Then g is the one with refs in the loop, and f... hmm, f would be set once after the loop and read right after — short live, but then f is v-something. But the target's v1 gets `move v1,zero` BEFORE the loop and `li v1,1` inside — so the value lives across the loop. A split wouldn't match.

Hmm.

OK, at this point I've spent a lot on item 4. Let me check the time: started ~02:54, now maybe 03:15. Let me check.

Actually, let me reconsider the problem from a different angle: the target's f is in v1. The pin forces v1. Without the pin, global-alloc gives v1 to the giv (higher priority). 

What if we reduce the giv's priority by making its live range longer? The giv r234: refs7 live9. If its live were > 28, pri < 5000. Hmm, the giv lives only inside the loop (~9 insns).

What if we use the array pointer *outside* the loop too? E.g., compute `p = D_801AECD8` before the loop and use `p[i1]` — the base r234 already lives from before the loop (insn 617) to the loop end. Live=9? Hmm.

What if we add `D_801AECD8[0]` usage before/after the loop? Adds code.

Alternatively, lower i1's priority? i1 is 12727 in mine; it takes a0 after the giv takes v1. If i1 were higher than the giv, i1 would take v1! Then f... hmm, target has i1 in a0, so no.

Wait, actually, let's reconsider the target order: f=v1, i1=a0, giv=a1. The allocation order must be f first (v1), then i1 (a0), then giv (a1). OR: i1 first but conflicts with v1, takes a0; then f (v1); then giv (a1). In the pinned version, i1(22500) is first and conflicts v0,v1 → a0; then giv(14000) conflicts v0,v1 → a1; f pinned v1.

So the target order is consistent with: i1 > giv, both conflict v1, f gets v1.

For the lever-free body, if i1 > giv and both conflict v1, then i1→a0, giv→a1, and f (last) → v1. That's exactly the target! So we don't need f to beat them; we need them to CONFLICT with v1.

The conflict with v1 comes from... in the pinned version, f is in v1 and live across the loop, so i1 and giv (live across the loop) conflict with v1.

Without the pin, no one is in v1. But could we make a *local* temp in v1 live across the loop? Local-alloc assigns block-local pseudos to hard regs by scanning within a block. If a temp in the loop block gets v1 and is live at a point where i1/giv are live, then i1/giv conflict with v1.

In the loop block, the temps are: r174 (lw result, block-local, v0), r176 (lhu result, block-local, v0). Why v0? Because local-alloc assigns in order and v0 is first.

If v0 were taken, the temp would go to v1. What takes v0? Hmm.

Alternatively, make a temp that lives across the loop in v1 via local-alloc... hard.

Hmm, wait. Actually maybe the conflict in the pinned version comes from f's *pin*: a pinned hard-reg variable creates a conflict for any pseudo live at the same time. f is live across the loop (from before to after). So any pseudo live across the loop conflicts with v1.

Without f in v1, nothing else is live across the loop in v1.

BUT: what if we put ANOTHER variable in v1 that is live across the loop, without a pin? We'd need global-alloc to assign it to v1, which requires it to be allocated before the giv... circular.

Hmm.

OK, let me try a different tactic: use a real-C construct that creates a v1-hard-reg value across the loop. For example, a local temp assigned by local-alloc... 

Actually — what about the loop counter i1's increment temp? Or the limit 5 (r177)? The limit is in a2.

Hmm, what about making the loop condition use a comparison whose temp local-alloc puts in v1? `slt v0,a0,5` uses v0.

What if the loop body has a value that local-alloc puts in v1 and is live across the giv's range? Local-alloc assigns per-block; a value computed at the block start and used at the end...

Honestly, this is the "greg-pri-refs" wall class (moves line 73, 114, 16, 51, 60). Let me check what those walls concluded: e.g. line 16: "PARTIAL:keepalive greg-ref-count — ... keepalive: pb 4 refs/live 72 pri 1081 < j,k ~1900; keepalive adds refs so pb takes a2 first; lever-free best 11". Line 73: "WALL greg-pri-refs — pf20 8 refs/live 66 beats pf34 10/96 for s3; pf34 needs 12 refs or live <83; do-while(0) ref boost breaks loop opts (71)".

So these are walls where the keepalive adds refs. Here the keepalive's role is different (it creates the v1 conflict).

Hmm, wait. Let me reconsider: maybe the keepalive's refs on i1 don't matter; maybe what matters is that the keepalive is an asm insn that local-alloc/global-alloc treats as using i1 across the whole loop body, making i1 live at the point where v1 is... no, without the pin there's no v1.

Let me test: take the pinned version but replace the pin with a plain `s32 f;` and keep the keepalive (i.e., drop only the pin). What's the score? Earlier for item 4, wk? No, I didn't test that for item 4. Let me test: f plain + keepalive kept.

If the keepalive alone (no pin) gives f=v1, then the pin is redundant and the keepalive is the only needed lever → PARTIAL:keepalive. Let me test.

Actually wait, in the pinned version the order is 77(22500) 234(14000) and f pinned. If f is unpinned, where does f go? f would be in the global list with its priority (maybe 5000) and would be allocated after 234 → a1? But the conflicts of 77/234 with v1 are due to f being in v1... which was due to the pin. Without the pin, no v1 conflict, so 234 takes v1 again. Hmm, but 234's priority in the keepalive version is 14000 and 77's is 22500. 77 first: conflicts v0,v1 → a0? Wait, without f in v1, why would 77 conflict with v1? The conflict listing came from the pinned dump. Without the pin, the conflicts change.

Let me just test it.
