---
ts: 2026-11-06T10:02:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GHygrhq0CLt8Z9sFAFCc
---
Same shape, also with pin+keepalive. So no help.

OK. Let me think about the lever-free approach concretely using the alloc table arithmetic.

Current nopin alloc table:
```
r78  - 30000 refs 10 live 10  conflicts v0,sp prefers v1,a1  dies in 2 places
r80  - 20000 refs 4 live 4    conflicts sp prefers v0
r79  - 17500 refs 7 live 8    conflicts v0,sp prefers v1,a1
r72  v0 13333 refs 4 live 6   block 0
r77  - 10000 refs 5 live 10   TIE prefers s0
r88  a0 10000 refs 2 live 2
...
r76  - 8333 refs 5 live 12    conflicts v0,s0,sp
r81  v0 6666 ...
r74  - 5185 refs 7 live 27    conflicts v0,v1,a0,a1,s0,sp dies in 3 places crosses 1 call
r92  v1 5000
r75  s0 2857 refs 2 live 7    crosses 1 call
```

Wait, r75 has hard s0 already — from local-alloc. And r74 (d) conflicts with s0 because r75 holds it.

Hmm, but hold on: r74 refs 7 live 27 — is r74 really d? d's live range: from `d=arg1` (insn 6) to the last div. The function is ~75 insns, so live 27 seems too short. Hmm. Maybe r74 is d and live 27 (in insn units, the RTL before scheduling has ~50 insns). Plausible.

And r75 (refs 2 live 7, crosses call) = s1ang. Yes.

So s1ang got s0 via local-alloc; d (r74) then conflicts with s0 and takes s1.

To flip: make d not conflict with s0 — i.e., make s1ang not occupy s0 during d's live range. Since d is live from the start to the end, ANY callee-saved reg holding s1ang conflicts with d. So d can never get s0 if s1ang has s0.

Therefore we need local-alloc to give s1ang s1 instead of s0 (or give it a caller-saved reg, but it crosses the call).

How does local-alloc choose? It iterates over qtys in order and assigns the first free hard reg. s1ang's qty gets s0 because s0 is free in its live range. To make s0 unavailable, another pseudo must hold s0 during s1ang's live range.

Alternatively, make s1ang's live range NOT cross the call — then local-alloc gives it a caller-saved reg (e.g., v1). But the target has it in s1 across the call.

Hmm, wait: maybe s1ang doesn't actually cross the call in the target's RTL. In the target asm, the load is before the call and the use after. But the load could have been *hoisted* by sched1 from after the call to before! Let me check: if the source computes u6 = s1ang & 0xFFF *after* the ratan2 call, the load would be after the call. Then sched1 (or dbr) could hoist the load above the call? No — sched1 doesn't move loads across calls (a call clobbers memory). Hmm, but `s1ang` loads from *(arg0+0x20)+0x12 — memory could be clobbered by the call. So the load can't be hoisted above the call by sched1.

Actually wait, in the target asm the load IS before the jal. And the `jal` has a delay slot `subu a1,v1,a1`. So the load at 38f0 is 1 insn before jal. The source order (as given) has s1ang load before u5=ratan2. So it's genuinely before.

So s1ang crosses the call → must be callee-saved. In target it's s1.

So the original compiler gave s1ang s1 and d s0. How? In the original, maybe d was allocated by local-alloc too (not global), because d's live range... no, d spans blocks.

Hmm, wait. Let me reconsider: maybe in the original, the divisor variable `d` was NOT live across the call! If the source computed `d = (s16)arg1` AFTER the call (i.e., d defined after ratan2), then d's live range doesn't cross the call, and d could get a caller-saved reg. But the target has `move s0,a1` in the prologue (before the call) — so d is defined before the call.

Hmm, unless `move s0,a1` is a copy of the ARGUMENT for later, and d is... 

Actually, in the target prologue: `move s0,a1` then later `sll s0,s0,16; sra s0,s0,16`. So a1 is saved to s0 at the start. That's `d = arg1` at the top. Yes.

So d crosses the call → callee-saved. And s1ang crosses the call → callee-saved. Both. Target: d=s0, s1ang=s1.

For d (global, pri 5185) to get s0, s0 must be free when d is allocated in global-alloc. Global-alloc processes in the order [78,80,79,77,76,74] — d (74) is last. If s1ang were a global allocno instead of local, its priority would determine its position. s1ang pri 2857 < d 5185, so d would be allocated BEFORE s1ang → d gets s0, s1ang gets s1. That's exactly the target!

So the fix: make s1ang a GLOBAL allocno (so it goes through global-alloc) rather than a local one. Then d's higher priority wins s0.

Why is s1ang currently local? Because its live range is within one basic block? But it crosses the call... Hmm. Local-alloc handles pseudos whose live range is entirely within one basic block. If the load and the use are in the SAME basic block (which spans the call), local-alloc can still handle it (a call inside the block doesn't split blocks? Actually calls don't end basic blocks in gcc 2.7.2). So s1ang is born and dies in block 0 → local.

To make s1ang global, its def and use must be in different basic blocks. E.g., if the load is in block 0 and the use is in a later block (after a branch). In the target asm, the use `andi s1,s1,0xfff` is at 3908, after the `jal`. Is there a basic block boundary between? The `jal` is a call, not a branch. So same block.

Hmm. But wait — in the target, after `andi s1,s1,0xfff`, `bne s1,a0`. The andi is before the branch. So s1ang's def and use are both in the entry block.

So in the original compilation s1ang was ALSO local... and yet got s1? That contradicts my reasoning.

Unless the original source had s1ang defined in a different block. Hmm.

Wait, maybe I have the wrong idea. Let me reconsider: maybe in the original, `s1ang` was NOT a variable at all, and the `lh s1,18(v0)` is a load of something else. Let's see: `lh s1,18(v0)` where v0 = *(arg0+0x20) (loaded at 38e0 `lw v0,32(v0)`). Then `andi s1,s1,0xfff`. So s1 = (*(*(arg0+0x20)+0x12)) & 0xFFF. That's u6 = s1ang & 0xFFF.

Alternatively, maybe the original had `u6 = (*(s16 *)(*(s32 *)(arg0+0x20)+0x12)) & 0xFFF;` computed AFTER the call — then the load would be after the call... but it's before. Hmm, sched1 could hoist the load if it knows no aliasing? The call is `ratan2`, and gcc assumes calls clobber memory unless... `-fno-...`. GCC 2.7.2 by default assumes calls clobber memory (CALL_INSN clobbers). So no hoist.

Unless the load was hoisted by the *loop*/dbr? No.

OK here's another thought: maybe in the original, s1ang was defined in an *outer* block. Look at the source:
```
d = arg1;
s1ang = *(...);
u5 = ratan2(...);
```
All in the entry block. Hmm.

Wait, unless the original source had a branch before the s1ang load, making the load in a nested block. But the target asm shows the load unconditionally.

Hmm, let me look at the target's full asm again around the prologue:
```
addiu sp,-32
move v0,a0
sw s0,16(sp)
move s0,a1
sw ra,24(sp)
sw s1,20(sp)
lh v1,14(v0)
lui a0, D_80126B66
lh a0,0(a0)
lh a1,6(v0)
lw v0,32(v0)
subu a0,v1,a0
lui v1, D_80126B5E
lh v1,0(v1)
lh s1,18(v0)
jal ratan2
subu a1,v1,a1
```

Interesting: `move v0,a0` — arg0 copied to v0 (v0 is caller-saved, used for loads). `sw s0,16(sp); move s0,a1` — d=arg1→s0. `sw ra; sw s1` — prologue saves.

Note: s1 is saved in the prologue (`sw s1,20(sp)`) even though s1ang is loaded before the call. That's consistent with s1ang being callee-saved and live across the call.

Hmm OK. Let me look at the sibling function func_8012B8E4's alloc table (it has the same structure). But it also has the pin. Not helpful.

Let me think about local-alloc's choice differently. In gcc 2.7.2 local-alloc, `local_alloc` processes qtys ordered by `qty_n_refs`? Let me read local-alloc.c to understand how it picks s0 vs s1 for a pseudo live across a call.

Actually, maybe there's an important detail: the target's `lh s1,18(v0)` — s1ang's load uses v0 which holds `*(arg0+0x20)`. And d=s0. In the nopin version, d=s1 and s1ang=s0. Both are valid allocations; the difference is which one local-alloc grabbed first.

Let me look at the nopin alloc table more carefully: r75 (s1ang) hard=s0. But why? Let me look at the .lreg dump for block 0 to see the qty ordering. Actually local-alloc processes qtys in order of `qty_n_refs`? Let me check.

Actually — simpler empirical approach: try C variations that change which pseudo local-alloc prefers for s0. 

Key lever candidates:
1. Make d also local-alloc-able? Not possible (multi-block).
2. Make s1ang's qty have a *preference* for a different reg or a conflict with s0.
3. Introduce another variable that takes s0 during s1ang's range.

Wait — actually, maybe the cleanest: the target might have `s1ang` NOT live across the call, with the load hoisted before the call by *sched1* because the call is to `ratan2` which... no.

Hold on, let me reconsider. In gcc 2.7.2, does a call clobber memory? The RTL for a call includes `(clobber (mem:BLK (scratch)))` typically. So loads can't move across. But maybe `ratan2` is declared as a pure function? No.

Hmm, but here's a thought: what if the load `s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)` is actually moved before the call by *cse/dbr*? No.

OK, let me try the empirical route. Let me test a few variants quickly on includer 0 (dt.sh) and see if the register assignment flips:

Variant A: move `s1ang = ...` AFTER the u5 line. (Load would be after the call.)
Variant B: change `s32 s1ang;` to `s16 s1ang;` (changes load width and use).
Variant C: reorder: `u6 = s1ang & 0xFFF;` before the call? no.
Variant D: make u6's computation not use s1ang directly: `u6 = (*(s16 *)(*(s32 *)(arg0+0x20)+0x12)) & 0xFFF;` (no s1ang variable) — then the load is a temp in block 0, used immediately; local-alloc gives it a caller-saved reg (v1?). But target has it in s1 across the call. If the load is after the call, the code would be: call, then lh, andi. Target has lh before call. So no.

Hmm, wait. Actually let me re-examine: is the target's `lh s1,18(v0)` really before the jal in *source* order, or did sched1 hoist it? The jal at 38f4; the load at 38f0. The delay slot is 38f8 `subu a1,v1,a1`. So the load is the insn just before jal. If sched1 hoisted the load from after the call, it would have to cross the call — not allowed for memory.

BUT: gcc's `dbr` (delayed branch) pass or sched1 might move a load into the *delay slot region*? No.

OK. Let me just test empirically. Let me write several variants and use sc.sh (which uses includer 0). Each is fast.

Actually, let me reconsider the whole thing from the angle of: what does the *original* C look like? The decomp project's reconstruction has pin+keepalive because a plain version differed. The plain version's residual is the register swap + prologue order. The "keepalive" was a scheduling barrier for u5. 

Hmm — the keepalive `__asm__ __volatile__("" : : "r"(u5))` after u5's computation: without it, what happens? In the nopin version I removed it. Let me check whether the keepalive affects the register swap or just scheduling. The --explain (which removes both) showed the register swap. Let me test removing ONLY the pin but keeping the keepalive? No — keepalive is a lever too; but to isolate, let me test:
(a) pin only removed (keepalive kept): what's the residual?
(b) keepalive only removed (pin kept): what's the residual?

That tells me what each lever does. But both must go eventually. Still, it isolates.

Let me test (a): keep keepalive, remove pin.

Actually, --explain gives the fully-lever-free residual. Let me instead do targeted tests.

Let me write variant files:
- nopin_keep.c: no pin, keepalive kept.
- pin_nokeep.c: pin kept, no keepalive.

Then sc.sh.

Let me do that.

Actually, the more efficient path: understand the keepalive's role. The comment says "scheduling barrier: anchor u5 before the (s16)d cast". In the target asm, the order after the jal is:
```
addiu v0,v0,-1024   (u5 = ratan2(...) - 0x400)
andi a0,v0,0xfff    (u5 &= 0xFFF)
sll s0,s0,0x10      (d = (s16)d)
andi s1,s1,0xfff    (u6)
bne s1,a0
sra s0,s0,0x10
```
So u5's computation (addiu+andi) happens BEFORE d's sign-extension (sll). The keepalive anchors u5 before d=(s16)d. Without the keepalive, sched1 might reorder sll before the addiu/andi.

In the nopin version, is the sll placed correctly? The --explain diff showed:
mine[20:23]: andi s0,s0,0xfff; bne s0,a0; sra s1,v1,0x10
target[19:23]: sll s0,s0,0x10; andi s1,s1,0xfff; bne s1,a0; sra s0,s0,0x10

The diff is messy due to the register swap. Let me get the full nopin asm to compare.

Let me dump the nopin object. Actually, I have the .s dump in the hdump dir! `it2.s`. Let me read it.
