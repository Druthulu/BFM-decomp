---
ts: 2026-11-06T23:59:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V5gCa5EejlJlHmayCuRv
---
Interesting! q05: the reg swap is GONE (mode/base in the right regs!), but now the symbol-spelled site uses `lui v1,0x1; lh v1,-23592(v1)` instead of `lui at; addu at,s4,at; lh v1,-23592(at)`. So cse did NOT merge the fresh symbol reference with base's value — it kept a separate address computation (using v1, shorter). And that also removed the copy (160 insns).

Wait, q05 is 160 insns — the copy disappeared. Hmm, but the reg swap is fixed. Interesting: dropping base's ref to 7 flipped mode above base! Great — the mechanism works.

But now two problems:
1. The symbol-spelled site emits a different address form (lui v1; lh) instead of base-relative (lui at; addu at,s4; lh).
2. The copy disappeared (160 insns).

Hmm, wait. q05 replaced the 5th if's base use. Let me re-look: q05 replaced `((Unkstruct_80010178 *)base)->unkA3D8` in the 5th if (0x3021). The diff at insn 88-90 shows the 5th if's load is now `lui v1,0x1; lh v1,-23592(v1)`.

So cse didn't merge. Why? Because at that point base is in s4 and the address D_800AF630... cse should know base == D_800AF630. Hmm, unless base's value isn't in cse's table anymore (too many blocks later?).

Actually cse processes per extended basic block. The 5th if is far from base's set, in a different basic block. cse's table doesn't carry across branch boundaries in general. base was set in block 0; the 5th if is in block ~5. cse1 doesn't know base's value there. But the ORIGINAL code uses base there as a register (base is live). So `((Unkstruct*)D_800AF630)->...` computes a fresh address (2 insns) instead of using base's register.

So this trick changes the code at that site. Bad.

Hmm. But it did flip the regs. I need a way to drop a base ref WITHOUT changing the code.

Alternative: drop base's *set* ref? No.

Hmm. What if instead I ADD a ref to mode? That would change code too... unless the added ref is in a place that gets folded.

Wait — what if I make mode's live range shorter by... hmm.

Actually, hold on! q05's result is interesting: 160 insns means the copy also disappeared. Why? Because the store `*q = val; p = q;` — with the 5th-if change... hmm, the copy disappearing is probably because the register pressure changed. Not important.

Let me think differently. I need base refs 7 with identical code. The only way: one base use must be spelled differently but compile identically.

What if I use a *cast* that doesn't change the RTL: e.g. `((Unkstruct_80010178 *)(u8 *)base)->unkA3D8`? Same RTL, same ref. No.

Hmm, what about the SET: `base = D_800AF630;` — if base is initialized at declaration `u8 *base = D_800AF630;` same.

What if base is not a variable but... hmm.

OK, alternative: increase mode's refs by 2 with no code change. Is there any C construct that adds a register reference but gets folded before global-alloc while still counting? No — n_refs is computed from the RTL after combine (global.c uses reg_n_refs from flow, updated by combine? Actually `reg_n_refs` is set by flow and combine updates it? global.c uses `allocno_n_refs` computed in global_conflicts from reg_n_refs).

Hmm, wait: maybe combine/sched can *delete* insns but the refs count is from the .lreg (after local-alloc) or .greg? The .lreg dump showed r73 refs 5. local-alloc runs before global-alloc. The .lreg dump is after local-alloc.

So the refs count includes insns present at local-alloc time.

Hmm.

Let me reconsider: maybe there's a *different* variable structure that changes the allocno priorities while keeping the same code. For example, what if `mode` and something else are combined?

Actually — wait! What about making mode's live_length SHORTER by making the last use come earlier in the RTL? The last use is `if (mode == 0 && (res & 1))`. What if I restructure to `if (!mode && (res & 1))` — same.

What if the `mode == 0` test is replaced by a test on a *copy* of mode made earlier? no.

Hmm, what if the CdReadRequest arg use (`mode` passed as 3rd arg) is the last... no, `mode == 0` is after.

Hmm OK. Let me think about `live_length` computation in flow.c. It's the number of instructions in the live range, incremented per insn. For a straight-line range, it's roughly the span.

mode span: from `li s3,-1` (~insn 34) to `bnez s3` (~insn 133). Span ~99. live 83.

To get live ≤65 we'd need the span to shrink by 18. Not possible.

To get refs 7 we'd need 2 more refs.

Hmm, hold on, what about the OTHER allocnos? Maybe I can make another allocno take s3 before base, pushing base to s4, and mode would then... no, mode must get s3.

Wait, what if mode could get s3 by being allocated earlier than base via a priority tie or something? pri mode 1204, base 1518. No.

What if base's pri drops because its live_length grows? base live 158, function 161 insns. If I could make base's live 200+... no.

Hmm, what if base's refs drop to 7 via the *set* being shared? E.g., `u8 *base; ... base = D_800AF630;` — what if base is initialized from another variable that already holds it? No.

OK, what about the reverse trick: add a ref to base to raise its priority? No, that makes it worse.

Hmm, let me reconsider the problem. In the TARGET (pinned), base=s4 and mode=s3. With the pin, mode is a hard reg so base's priority doesn't matter for mode. So the target code was produced with the pin. But this is a "crack shard": we're asked to find a lever-free body. If the target's original source had base=s4/mode=s3 naturally, then the original's priorities had mode > base. Our reconstruction has base > mode. That means our reconstruction's RTL differs from the original's in refs/live for one of them.

Which one? Possibly the original's `mode` had 7 refs or a shorter live. Since the emitted code is identical, the RTL *insns* are the same. But the RTL *pseudos* could differ! For example, if the original used a single pseudo for mode but our C creates... no, same.

Hmm, wait. What if the original source's `mode` is not set by `mode = -1;` before the if, but the code shows it. Hmm.

OR: the original's base had 7 refs because one of the 5 unkA3D8 reads used a *different variable* that the original kept in the same register (e.g., the original read `unkA3D8` into a local `x` once and reused it? No — the target re-reads `lh` before each if, so no).

Hmm, look at the target: before each if, `lui at,0x1; addu at,s4,at; lh v1,-23592(at)`. So each if re-reads unkA3D8 via base. 5 reads + 1 unkA3DE + 1 final = 7.

So base refs = 8 in the target too.

And mode: 5 refs.

So the target's own priorities would be base 1518 > mode 1204 — but the target used a pin, so mode never competed.

Therefore, the target source may have had mode pinned via a different mechanism, OR the original was compiled differently (different compiler version/flags), OR... 

Hmm, this is exactly the `global-pri-bank-order` WALL: "global-alloc priority order assigns the hard regs in a different order than the target".

But hold on — q05 showed that dropping ONE base ref flips the order AND changes the code at that site. What if I drop a base ref at a site where the re-spelling still compiles to base-relative addressing? The reason q05 changed code: cse couldn't prove the symbol equals base in that block. But maybe if the re-spelled site is in the SAME basic block as base's set (block 0), cse would merge.

base is set in block 0 (`base = D_800AF630;`). The first if (0x300B) is also in block 0? Let's see the control flow: block 0 = from function start to the first branch (the `st != ...` if at line 971). The 0x300B if is after `cnt = func_80029504()` (a call). Hmm, calls don't end basic blocks? In gcc, a call insn doesn't end a basic block (it's not a jump). So block 0 continues until the first conditional branch at 10e8 (`beq v0,v1`). That's the `if (st != ...)` at line 971.

So block 0: base set, file/val, st call, mode, the if-branch. Then the if-body (mode=0, func_8002F620) is block 1. Then block 2 (join) has cnt call and the 5 ifs... each if has a conditional branch → each ends a block.

So the first if (0x300B) is in block 2 (after the join). base's value: is cse's table valid at block 2? cse_basic_block processes an extended basic block path. From block 0 through the branch to block 2 (the join). The join block 2 is reached from both the then-block and the fall-through — so cse would start a new cse_basic_block at block 2 (the table is cleared because the path isn't unique). So base's value is NOT in cse's table at block 2 → re-spelling D_800AF630 there gives a fresh address (2 insns). That's what q05 showed.

So no re-spelling in blocks 2+ will merge.

Hmm, so dropping a base ref changes code. Unless... the re-spelling is in block 0 itself. Is base used in block 0? No — base is only set there.

Hmm! What if base's *set* is re-spelled? No.

OK, so what about raising mode's refs by 2 without changing code? Any added ref must be folded away. Folded refs don't count.

Hmm, what about this: make mode's live range shorter by moving its first set to a later block? The first set is `mode = -1` in block 0. If I move it to block 2 (the join), the code would change (li s3,-1 would move).

Hmm.

Wait, actually! What about making `mode`'s live SHORTER by moving the LAST use earlier? The last use `mode == 0` is in the last block. What if the C reorders `if (mode == 0 && (res & 1))` before `if (file >= 0 && ...)`? That changes code order.

Hmm.

OK, what about a completely different approach: what if I make base's live_length LONGER by making its set earlier? It's already at the top. Or by adding a use at the very end that gets folded... 

Hmm, actually — what about making base's live length longer by *using base in the mode test*? No.

Let me reconsider: maybe I can make base NOT an allocno by making it a *hard register* naturally? No, that's a pin.

Hmm, hold on. What about `allocno_size`? pri = ... * allocno_size. If base had size 2 (DImode), its pri would DOUBLE. That's the wrong direction.

If mode had size 2... it's s32.

OK. What if base is accessed as a *struct pointer* so that... no.

Let me reconsider the refs: `allocno_n_refs` is the total number of references. Hmm, does it count the set? Yes.

Alright, let me look at this from a different angle: maybe there's a way to make `mode` get s3 by making `file` or `val` take different regs, shifting everything. But target has file=s1, val=s2.

Hmm, what if the order were file, val, mode, base → s1, s2, s3, s4. That's what we want! We need mode (r73, pri 1204) to beat base (r72, pri 1518). 

What if I could make r74 (val/file) and r75 change? No.

OK — radical idea: what if `mode` is not a global allocno but a *local* one, because I restructure so that its live range is within one block? Then local-alloc would assign it. But mode spans blocks.

Hmm.

Let me now reconsider: is it possible that the *copy* construction affects the priorities? In p14, base/mode priorities are the same as G_nopin. Let me verify with a dump of p14 — maybe the store-first order changes base's live length! In p14, `*q = val; p = q; D_800C7C64 = ...`. The base's last use is still the final if. Hmm.

Actually wait, let me just dump p14's allocno table and check the numbers. Maybe they differ from G_nopin's.

Let me do that — it's cheap and decisive.
