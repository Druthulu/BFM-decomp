---
ts: 2026-11-06T21:44:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_00k8eoquirZufoF9JQFt
---
The .lreg is huge (whole TU). grep for our function's RTL tail is hard. 

Time check: I've used maybe 15 min on item 1. Let me be pragmatic: try a batch of candidate moves quickly via sc.sh (one line per candidate). Ideas to test:

1. Make packet word a `u32` temp `pw = *(u32*)pkt;` then store expression uses pw. Might alter n_refs? Same.

2. Instead of loading `*(u32 *)pkt` twice in the expression, write:
```
pkt_word = *(u32 *)pkt;
*(u32 *)pkt = (pkt_word & 0xFF000000) | (...);
```
Same.

3. Reorder: compute `oidx` earlier, right after `w = mulc;`? oidx = g.otz << 2 could be computed before the sh stores. In target oidx is computed at 178 (late). If we move `oidx = g.otz << 2;` earlier in source, sched1 might keep it early → longer life → lower priority. Bad.

4. Move `oidx` computation *later*: currently it's before the first big store. In target it's at 178. Fine.

5. Use `u16` for the tag or `s16`—tried.

6. Add a *third* real use of oidx that the compiler can't eliminate but doesn't change the final code. E.g., store `pkt[0x26] = oidx;`? adds an sb. No.

Hmm, what about using oidx as the index in a *third* identical address expression that cse merges into the existing one, thereby adding a ref before cse? flow runs after cse, so merged → no.

Wait, is flow after cse? Pass order in gcc 2.7.2 rest_of_compilation:
```
  if (optimize > 0) {
    ...
    if (flag_expensive_optimizations) ...
    ...
    cse_insns? 
```
Let me check the actual order. In gcc 2.7.2 toplev/rest_of_compilation:
```
  /* Initialize the RTL before any passes. */
  ...
  if (optimize > 0 && flag_keep_static_consts ...)
  ...
  if (optimize > 0)
    {
      ...
      /* Jump optimization */
      jump_optimize (insns, 1, 1, 1);
      ...
      /* Perform common subexpression elimination. */
      cse_main (insns, max_reg_num (), 0, rtl_dump_file);
      ...
      /* Perform various loop optimizations, including strength reduction. */
      loop_optimize (...);
      ...
      /* Perform data flow analysis. */
      flow_analysis (...);
      ...
      /* Combine instructions */
      combine_instructions (...);
      ...
    }
  ...
  if (optimize > 0)
    {
      ...
      if (flag_schedule_insns) schedule_insns (insns, ...);  /* sched1 */
      ...
      local_alloc ();
```
So flow is BEFORE combine and sched1, after cse. n_refs from flow reflects post-cse, pre-combine/pre-sched1 RTL.

The life (death-birth) for local-alloc comes from local-alloc's own scan of the sched1-ordered RTL. So sched1 changes lives but not n_refs.

So to raise oidx priority: raise its n_refs (pre-combine, post-cse) or shorten its life (post-sched1).

n_refs of oidx: it's a pseudo created by the compiler for the C variable `oidx`. Each C use is one ref (plus the set). Two uses → 3 refs.

If the original source had *three* uses of `oidx`... maybe the original code was:
```
oidx = g.otz << 2;
*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000)
            | (*(u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)] & 0xFFFFFF);
otp = (u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)];
```
The second expression repeats the whole thing. But cse would make the second `&D_800A6614[oidx + (tag<<14)]` identical to the first → cse replaces it with the first's address value! But the target recomputes it (194-205). Why? Because the first address value (`at` scratch) isn't kept. Hmm, cse might have merged them into a register if profitable. In target it didn't, because the address is used once each time? Actually cse would need to hold the address in a register across the store (which may alias). The store to *pkt could alias D_800A6614, so cse can't reuse the loaded value; but the *address* computation is pure. cse could still reuse the computed address (at) but it's a scratch not a pseudo.

Hmm.

Let me try yet another angle: make the packet-word pseudo live longer so its priority drops below oidx. Extend its death beyond oidx's death (203): use the loaded packet word *after* the otp store. For example:
```
u32 pw = *(u32 *)pkt;
*(u32 *)pkt = (pw & 0xFF000000) | (...);
...
*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
```
pw dies at 193. To extend, add a use of pw after 209 that produces no extra instruction? E.g., `if (pw == 0xFFFFFFFF) ...` adds a branch. No.

Hmm, what about making the *tag* and *packet word* the same variable? no.

Alternatively, lower oidx's life by having the second use occur earlier... but target order fixed.

Wait, maybe there's a much simpler explanation: in the target, `oidx` is in $3 because it was *pinned* in the original source too (the original devs also used register asm? unlikely — but the target is from 1998 compiled source; the source could have had `register int oidx asm("$3")`? Actually many PSX games didn't. But the previous decomp had a $3 pin because it was needed to match).

Hold on — the target is the original binary; if the original source had a register pin, then lever-free reproduction is impossible → WALL. But the task is to try.

Let me look at whether $3 assignment could come from a *copy preference*: local-alloc's qty_sugg_compare phase. A qty gets copy suggestions when it's tied to another pseudo by a move that can be coalesced. Look at target at 203-204: `addu v1,v1,v0; addu v1,v1,a0`. The first `addu v1,v1,v0` is oidx = oidx + (tag<<14). Since oidx is used as both source and dest, local-alloc may keep it in place.

Actually here's a thought: qty suggestions come from `reg_copy_sugg` set in `block_alloc` via `combine_regs` when it sees a move `set (reg A) (reg B)`. The `sll v1,v1,2` is a shift, not a copy.

Hmm.

Let me look at what register the *first* expression's index sum uses: `at` (assembler temp). In mine, also at. Good.

New idea: maybe the difference is the *order of qty allocation* due to a qty with n_refs=1 but a copy suggestion taking $2 or $3 first. The suggested phase runs before the general sort: qtys with copy suggestions get their suggested reg. If some qty has a copy suggestion for $3, it takes $3, pushing oidx to $4 and packet to... no wait, target has oidx in $3. So maybe in the reference, oidx had a copy suggestion to $3!

How to give oidx a copy suggestion? A copy suggestion arises when a pseudo is copied to/from a hard reg or another pseudo, e.g. `register s32 oidx asm("$3")` gives a hard-reg preference (that's the pin). But the reference is compiled from original source without our pins... unless the original had `register` pins (some PSX libs did).

Alternatively: if the tail block starts by a move from a call result (v0) into oidx? oidx = g.otz << 2 — g.otz is loaded from stack.

OK. I think the most promising empirical move: give oidx an extra reference by making it used in a *non-cse-mergeable* way that still produces the same instructions. What about using `oidx` in a `do { } while(0)`? no.

What if we compute the second address as `&D_800A6614[oidx] + (tag<<14)`? That's `(D_800A6614 + oidx) + (tag<<14)` — different instruction order: addu base+oidx then +tag. Target has oidx+tag then +base. Would differ.

What if `otp = (u32 *)(&D_800A6614[oidx] + (*(u16 *)(base+0xA3D2) << 14));` — changes order.

Hmm, actually maybe we can get oidx an extra ref *for free*: the first expression `D_800A6614[oidx + (tag<<14)]` uses oidx once. If we instead write `D_800A6614[oidx] + ...` no.

Let me look at this from the "what did the reference compiler see" angle by examining the target's instruction at 182: `sll v1,v1,0x2`. The `lw v1,20(sp)` at 178 loads g.otz. So oidx = otz<<2.

What if the reference source had `oidx = g.otz * 4;`? Same.

What if `oidx` was `s16`? Then sll still.

Let me just try a batch of ~10 quick variants and see if any lands 0. Variants:
a) u32 pw temp for packet word.
b) compute oidx with `* 4`.
c) use `s32 tag = *(u16*)(base+0xA3D2);` and reuse `tag` var twice (explicit tag temp) — notes tried, 13-16.
d) Move the packet store before the `pkt[0xC]` line? Changes order.
e) Declare oidx as `u32`.
f) Use `oidx` three times: add a third use in the second expression by writing `D_800A6614[oidx + (tag<<14) + 0]`? constant fold.
g) Compute `oidx` as `g.otz << 2` and then reuse in a `*(volatile ...)`? no.

Actually, here's a clean idea for a third ref without changing output: write the first expression's index as `oidx + (tag << 14)` and the second as `oidx + (tag << 14)`; but compute `tag << 14` into a variable `toff`. Then oidx refs unchanged.

What about making the packet word *not* a qty in this block: if we compute `*(u32*)pkt` via a different statement order such that it's combined differently.

Hmm, let me try a completely different tactic: change the *width* of the loaded packet word's use. E.g., load as `u32` but store via a different mask sequence... no.

Let me look at the residual more: only the two registers swap; everything else matches. That means a single qty-priority inversion. We need one pseudo to move.

What if we *shorten oidx's life* by reordering the tail: do the otp computation+store BEFORE the packet store? Then oidx's last use would be at the otp computation (before the packet store), and the packet word would be born later. But store order changes → the target has packet store at 193 then otp store at 209. If we reorder source, the target order breaks (score high). Not good.

What if we shorten oidx's life by *splitting* it: use a separate variable for the second index that is `oidx` recomputed as `g.otz << 2` again? Then each has 1 use; but target has oidx kept in v1 across both. No.

Hmm, hold on. Let me re-read the target: at 203 `addu v1,v1,v0` — this reuses v1 (oidx). If oidx were recomputed, it'd be lw/sll again. So reference kept oidx live.

Let me try to get local-alloc's actual qty data from the .lreg dump? gcc -dl dumps the RTL *after* local-alloc, but there's a `-dL` (dump local alloc? maybe). We already have .lreg = -dl. Hmm, what is -dL? The tool passes -dL too. Files listed: .lreg (dl), ... no dL file? The list showed .i.rtl, .sched, .sched2, .greg, .lreg, .flow, .cse, .combine, .loop, .dbr, .jump2, .s. -dL maybe dumps loop? Let me check gcc 2.7.2 flags: -dl = local-alloc dump; -dL = loop dump? Actually:
-dl = dump after local-alloc
-dL = dump after loop optimization? no that's -dL? Let me check toplev.c.

I could add debug print to local-alloc source? No, we can't rebuild the toolchain.

Alternatively use the .sched dump (RTL after sched1, before local-alloc) and .flow n_refs to compute priorities by hand for the tail qtys. That's doable: find the tail in .sched (search for the D_800A6614 store pattern), get register numbers, then look up n_refs in .flow.

Let me grep .sched for "D_800A6614" near our function. The dump is 2MB; grep with line numbers and context.

Actually, better: the .lreg dump shows the *result*; the .sched shows before. Let me find our function in .sched. Function boundaries: search for "func_80183534" maybe comments. Let me grep.
