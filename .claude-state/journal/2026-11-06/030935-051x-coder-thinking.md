---
ts: 2026-11-06T10:09:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_z6XR5UdMQbasGMuxDnW4
---
k1 (keepalives only, no pins) keeps all 119 ins but registers differ: mine uses a1 for v1, target v1; and the tmp3 keepalive got a2 in the second block (target v1). So dropping the $2 pin broke v1→a1, and dropping the $3 pin made tmp3→a2.

So PARTIAL:keepalive requires fixing register allocation without the pins. The v0 pin forced v0 for the `v0` variable and indirectly freed v1. Hmm.

What if we keep the $2 pin (pin kind) and the keepalives? That keeps both kinds → not PARTIAL. What if we keep the $3 pin but drop the $2 pin? Still pin kind kept + keepalive kept → both kinds. No.

So PARTIAL would need dropping all pins and keeping keepalives (done, score 14) or dropping all keepalives and keeping pins (test that: pins only). Let me test pins-only for item4: keep the $2 and $3 pins, remove both keepalive asm lines. The dead computation would be deleted (no keepalive) → score ~? The $3 pin without keepalive: the store to $3 dead → deleted. So score high (~22). Not 0.

So PARTIAL not reachable. WALL.

But wait — the k1 score 14 is better than lever-free 19! The brief says WALL best = lowest score of a *lever-free* body. k1 is not lever-free (keeps keepalives). So best stays 19. Hmm, but PARTIAL is about keeping some kinds. Since k1 isn't 0, it's not PARTIAL.

Could we improve k1 with real-C moves to reach 0? The mismatch is v1→a1 (register). The target has v1 for the `v1` variable. Without the $2 pin, gcc allocates v1→a1. Real-C moves might shift it. Let me try a few on k1 (keepalives kept):
- v1 as u16? no, that changes ins.
- declaration order: v0, v1, t, rem
- make v0 u16? no.
- add a dummy local? 
- change the first branch to use v1 differently?

Actually, the target's v1 register comes from the original source's allocation where v0 was pinned... no, the target is the real game; it allocated v1 to $3 naturally. Our lever-free k1 gets a1 for v1 because... the `v0` variable (unpinned) took a different reg, and v1 got a1. Hmm.

Let me look at k1's allocation: `sra a1,v0,0xc` — so v1→a1. The `v0` var is in $2 (the comparisons use v0 too). Wait, mine[61]: `sra a1,v0,0xc` means t is in v0, v1 in a1. Target: `sra v0,v0,0xc` (t in v0), `li v1,127`, `subu v1,v1,v0` (v1 in v1). So mine v1=a1, target v1=v1.

Why does mine choose a1? Because $3 (v1) is used by... the tmp3 keepalive in the second block got a2. Hmm. In the first block, a1 is free (a1 param is y? no, this function has no args; a0 is a local, a1 free). So gcc picked a1 for v1. Target picked $3.

Can a real-C move make v1→$3? The choice between a1 and v1: local-alloc picks the first free reg in some order. Both a1 ($5) and v1 ($3) are caller-saved. Hmm.

The $2 pin in orig forced v0=$2, which maybe left $3 free for v1. Without the pin, v0 took $2 anyway (comparisons), and v1 took a1. Hmm.

This is deep. Given the brief, item 4 is a WALL (flow-unused-result for the dead computation; lever-free best 19). The keepalive-only residual (14) is a useful note.

Wait, actually — maybe I should reconsider: is the wall for item 4 really flow-unused-result, or could we keep the dead computation with a *real* use that the target also has? Let me re-examine the target's second branch: it computes v1 = 0x7F - v0, then `slti v0,v1,31; li v1,31`, then calls with a1=0. There's no real use. So flow-unused-result. Yes.

Hmm, but hold on: the orig body's `cmp` keepalive and `tmp3` pin+keepalive are the levers that keep it. Lever-free, flow deletes. So WALL flow-unused-result.

But maybe the tag should be `expand-void-return`? No — item 4 is void but the dead value is a local, not a return. flow-unused-result is right.

Now, let me reconsider the clones' wall tag. The residual is the return value dropped by void return → `expand-void-return`. Prior shard entries used `expand-void-return` for keepalive,pin void functions. Yes.

Actually wait — let me double check the clone's mechanism. The target keeps rv in v0 because the original returned it. Lever-free, the value is dead (flow deletes). Is it flow or expand? The `return rv;` in a void function → expand_null_return drops the value; then flow deletes the dead stores. The primary lever the orig uses is the keepalive (keeps value live) + pin (forces $2). The wall tag `expand-void-return` fits: "void-return expansion drops a value the target keeps live". Good.

Now, the clones' best lever-free = 13 (v05 u16 d). But is v05 truly lever-free? Yes (no asm, no register). It scores 13. However, the "best" for the wall is the lowest score; but should I choose a body that's structurally sensible? The task says best = lowest score of a lever-free body. v05 = 13.

Hmm, but wait: v05 with u16 d produces 23 ins (includes andi/sltiu). The target has 26. Is 13 really the lowest? Let me think if there's a variant that keeps more rv-related computation. The target's 26 ins include the rv values (li v0,-1, sll v0, li v0,31). Lever-free these are dead. No way.

But maybe a variant where `d` is used in a real store (e.g., the value escapes) could retain more with fewer mismatches. But that adds a store the target doesn't have → more mismatches. So 13 likely minimal.

Let me try a couple more width combos to be sure: `d` u16 with `x` s32 (v05) is best. What about `d` as `s16`? v20=15. `d` as `unsigned`? Let me not over-optimize; 13 is fine.

Actually, hold on. Let me reconsider the clone's lever-free best. The 11-ins variants score 15; the 23-ins u16 scores 13. But is 13 a legitimate "best"? The brief's best is used to characterize the wall. Fine.

Hmm, but there's a subtlety: for a WALL, the brief says "best = lowest score of a lever-free body". I'll use 13.

Now, I need to also verify FRESH: diff orig.c against the def in current src at each item's start. I extracted them just now; let me verify the current src still matches orig.c (src moves as batches bank). Let me diff each orig.c against the current src range. Since I extracted at the start of this session, they should match unless src changed during my run (other coders could bank!). The brief warns. Let me re-extract and diff.

Let me do that for all 4 now (before writing results).

Actually, the FRESH instruction says at each item's start. I'll do a final check now for all four and note if any changed.

Let me diff by re-extracting to temp and comparing.

Also, I should double-check the clone variants' generated body matches the current src structure (globals). Yes.

Now let me also do a bit more due diligence on item 4: ≥30 tries done (32 lever-free). Good.

For the clones: 32 lever-free tries each. Good. Plus PARTIAL probes (27 keepalive-kept for SC03; the other two didn't get PARTIAL probes but that's OK — the wall is established).

Hmm, actually the brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item". I have 32 per clone and 32 for item4. Good.

Now let me reconsider whether any clone could be PARTIAL:pin by keeping the pin and dropping the keepalive but adding a real use. b2 (pin only) = 15. No.

OK. Let me now finalize:
- Write win.c for each item: the best lever-free body (v05 for clones, v02 for item4).
- Write notes.md per item.
- Append results.tsv rows.
- Append moves.md lines.
- Write the log.

Wait — for WALL items, is win.c required? The brief says "For each item ... write a lever-free body ... that scores 0" (the goal), and DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0". So for WALL, win.c is optional but useful. I'll write win.c = best lever-free body and note it scores 13/19. Actually, calling it win.c when it's not a win might be misleading. The worked example uses win.c for the match. For walls, prior shards likely stored the best body as win.c or nopin.c. The brief mentions "regenerate orig.c/nopin.c". Hmm. I'll store the best as win.c (the standard file the harness checks) but clearly it's a WALL. Actually, to avoid confusion, let me name the best body `win.c` and note in notes.md that it's the best lever-free body (not a match). The results row's best column records 13/19.

Hmm, but the task says "write a lever-free body of func in G27/<dir>/win.c (bare definition) that scores 0." For walls, I'll put the best lever-free body in win.c and the result WALL with best=13.

Let me now do the FRESH check. Re-extract each def to a temp and diff with orig.c.

The line ranges: item1 3141-3193 (SC06), item2 3252-3289 (SC03), item3 4053-4090 (SC04), item4 3853-3888 (SC05). Let me verify the src hasn't changed by grepping the function definitions and line numbers.

Let me run a check.
