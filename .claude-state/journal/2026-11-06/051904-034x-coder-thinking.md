---
ts: 2026-11-06T12:19:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iZgaeDrYxVjMSHdC8EzQ
---
Interesting: keeping temps live to the end gives 22 (469 ins — an extra insn, probably a `move`). g5 (v0.vz/v1.vz early) = 9. g3, g7 = 7.

So the plateau is 7 with the exact same residual. That residual is the vh→v0 vs a0 allocation.

Let me examine: is there a way to raise vh's priority? In the target, vh's srl is at 373, very early, and its store at 383.

Idea: make vh's value used by TWO statements: `v1.vy = vh;` and something else that doesn't add an instruction. Hmm: `q[0x1D] = q[0x0D] + (rec >> 24)` earlier uses a separate srl. What if instead: compute `vh = rec >> 24;` once, use it in BOTH places — that gives one srl instead of two (v4 = 100). But what if the earlier use is written differently so gcc emits a separate srl anyway? E.g. earlier: `q[0x1D] = q[0x0D] + (s32)((rec >> 24) & 0xFF);` — that's an andi + srl, extra insn. No.

What about giving vh a second use that is FREE (no extra insn): e.g. `v1.vy = vh;` and `v0.vy = vh;`? No, semantics wrong.

Hmm, what about the store width/order? No.

Let me reconsider: maybe the residual isn't about vh's priority at all, but the ORDER: target's 373 is `srl a0,s1,0x18` — the srl appears BEFORE `sh v0,72(sp)` at 374 and before `lhu a1,0(s3)` at 376. If vh's srl could be scheduled earlier (slot 373), then the allocator might give it a0 anyway.

Why is vh's srl at 378 in mine? Because sched1 sinks it. Its priority is low because vh has only 1 use (at 382) — sched1's priority for an insn is based on the length of the dependence chain to the end of the block (largest path length). With the asm, vh's chain extends to the asm, which... hmm, both cases vh's use is at the store.

Let me think about what makes the target's srl early: In target's source (with the asm), the srl's priority = longest path to the end. The asm is a use of vh, and the asm is at the end of the block. So path length from srl to end is same.

Hmm, but wait: gcc's sched1 priority uses `INSN_PRIORITY` = length of the longest path to the end of the block computed at the start of sched1. With the asm, vh's srl path: srl → asm → end. The asm has a large "latency"? Asm insns get a latency from the insn template; maybe asm has a long latency (asm insns in gcc 2.7.2 default to... hmm).

This is deep. The practical approach: this is a huge function whose last 7 come from an allocation fact. I've spent ~30 min. Let me consider whether an alternative cluster A fix might also fix B (different ref weights). Actually! Important: the do-while around the store adds LOOP notes; flow then adds loop-depth refs to registers used in the loop. But also — wait, could the do-while be the cause of the 7? No: v0.c (no do-while) had 11, with cluster A's 4 + cluster B's 7.

Let me try one thing: does adding a do-while around the fill group AND the store do-while help? v5 was 21 (do-while around fill) — worse.

Another idea for cluster B: use `v0.vy = vv2` where vv2 is u16 and v1.vx... no.

Let me try: vh as `u32` instead of `s32`? No andi since shift by 24 of a s32 → sra? Actually rec is u32; `rec >> 24` is u32 → srl. vh is s32 = assignment, fine.

Try: `v1.vy = rec >> 24;` inline (no temp) — that was f3/f4 = 7.

Try making vv2's load later/earlier: target has the vv2 load at 376, mine at 375 (one slot early). And vv2 gets a0 in mine (target a1).

What if I make vv2's load happen AFTER vw's srl in C (it already is: vw = rec>>16 comes before vv2 in the original order? no, original: v0.vx; vv2 = ...; v0.vy = vv2; ...). Hmm mine scheduled the vv2 load at 375 (after vw's srl at 374). Target: vh srl 373, vw srl 375, vv2 load 376.

Honestly the simplest difference: in mine, the first srl scheduled is vw (374) then load (375); in target, srl vh (373), srl vw (375), load (376). So target's srl order is vh then vw; mine's is vw then vh.

If sched1's ready-list priority decided: both srl's are ready at the same time; priority ordering picks one first. In target the vh srl is picked first; in mine the vw srl. vh's chain: srl→sh (store) ; vw's chain: srl→andi→sh. So vw's chain is LONGER (2 insns) → higher priority → scheduled first. In target, vw is first? No: target 373 is srl a0,s1,0x18 = vh, and 375 srl v0,s1,0x10 = vw. So vh (shorter chain) scheduled first in target. With the asm: both chains also go to the asm... vw's chain: srl→andi→sh(v1.vx)→asm; vh's: srl→sh(v1.vy)→asm. Still vw longer. Hmm, so priority should still favor vw.

Unless the asm's operands create an anti-dependency/ordering: in gcc 2.7.2 sched1, an asm with operands is scheduled as a unit; the three values must be simultaneously live. Hmm.

Different thought: maybe with the asm, the *allocator* (running after sched1? no, global-alloc runs after sched1? Let me recall gcc 2.7.2 toplev order: 
1. jump_optimize (jump)
2. cse
3. ... 
Actually toplev.c: rest_of_compilation: `insn_addresses`... order is: jump_optimize, cse (cse1), loop, cse (cse2), flow, combine, sched (sched1), local_alloc, global_alloc, reload, ... 

Yes! sched1 runs BEFORE local_alloc and global_alloc. So sched1's output determines pseudo births.

OK so the difference must be in sched1's ordering. The asm is a barrier for... hmm, in gcc 2.7.2, `asm_noperands` insns: sched.c has a check `if (GET_CODE (insn) == INSN && GET_CODE (PATTERN (insn)) == ASM_OPERANDS)` — I recall `sched_analyze_insn` handling asm by making it depend on everything? There's `sched_analyze_asm` which treats asm as a full barrier for memory if it has a memory clobber, but for plain asm it adds dependencies on the registers used (the operands) — and importantly, "asm statements are assumed to clobber nothing but are barriers"? 

Let me look at tools/reference/gcc-2.7.2/sched.c for asm handling. That's the documented reference. Let me grep.

Actually — maybe faster: the difference in mine is that the two srl's are adjacent-ish and sched1 picks by priority. Let me test the hypothesis that vh's chain length matters by giving vh a longer chain: e.g. compute vh via two steps `vh = rec >> 8; vh = vh >> 16;`? That's 2 insns, changes count.

Alternatively, delay the vh srl by making it depend on the vv2 load? e.g. `v1.vy = vh + 0`? no.

Hmm, what about the reverse: make the vw srl LOWER priority so vh goes first. vw's chain: srl → andi → sh. If I write `v1.vx = vw & 0xFF;` as `v1.vx = (u8)vw;` — same andi. Hmm.

What if vw is computed and stored as `v1.vx = vw & 0xFF` but vw is u16? Then no andi: `vw = rec >> 16` truncates to u16 → andi 0xffff... different.

Let me try a different tack — measure how much the residual depends on the do-while. Let me check: is there an alternative cluster A fix that ALSO changes B favorably? For example, instead of a do-while around the store, wrap the q[7] RMW in a do-while (v1 = 35, bad).

What about `if (1) { ... }`? no, that's a fake.

OK, let me look at this from the WALL side: I've done ~22 scored tries on this item. The budget says WALL needs ≥20 min and ≥30 tries. Let me do 8-10 more targeted tries, then write WALL with best=7.

Targeted tries (h-series): manipulate the vh srl's scheduling priority:
h1: `vh = rec >> 24; v1.vy = vh;` placed early in the group (before v0.vx), rest original order.
h2: vh as a u32 temp (`u32 vh`)? declaration change: vh is s32; `s32 vh`. Try `u16 vh`? adds andi. Skip.
h3: use `v1.vy = vh;` immediately after `vh = rec >> 24;` (adjacent), and move that pair early.
h4: compute vw late: `vw = rec >> 16;` just before `v1.vx = vw & 0xFF;` (i.e. original) but move vh early. (that's h1/f1-ish)
h5: no vw temp; use `v1.vx = (rec >> 16) & 0xFF;` and keep vh temp. (f7 = 7)
h6: vh computed from a different spelling: `vh = (s32)rec >> 24;`? same.
h7: vh used twice: `v1.vy = vh;` and `v0.vy = vh & 0xFFFF`? no.

Alternative: make vv2's allocno lower priority: load vv2 inline at the last store `v0.vy = ((Unkstruct_8001EFE0_2 *)p)->unkA;` (g3 = 7, same).

So the plateau is robust: 7 with the vh→v0/vv2→a0 swap.

One more idea: use the `p` pointer's field widths to change the load order: target loads v0.vx at 371 (lhu v0,-2(s3)) and vv2 at 376 (lhu a1,0(s3)). Mine loads v0.vx at 371 (same) and vv2 at 375 into a0. 

Hmm, what if vv2's value comes from a *different expression* that cse keeps separate... no.

What if I make vv2 a u8? No.

Let me try 8 more variants quickly (h1..h8) focusing on: vh pair adjacency/placement, vw pair adjacency, and swapping which temp holds a0 by giving vv2 more refs (e.g. use vv2 in the q[0x1D] statement? no).

Actually here's a thought: give vh a second use in a place that costs no instruction: the gte_ldv3? No.

What about `v1.vy = vh;` AND `v1.vz = sz;`... no.

OK — alternative structural idea that could genuinely match: in the target, is `vh` maybe not a temp but the expression `(rec >> 24)` used in v1.vy, with the store at 383 being sh a0,82? The allocator gives a0 because ... hmm.

Let me try ONE more idea: the order of declaration of vv2/vh/vw. In global-alloc, ties break on allocno number = pseudo order, which follows the declaration order in the function (pseudo numbers are assigned when the pseudo is created — for locals with -O2 and no -fno-... the pseudo is created at the first mention, actually the RTL pseudo is created when the variable is first referenced in the body, not at the declaration). Hmm, but the variable's DECL order can matter via `assign_parms`/`expand_decl` for stack slots only.

Hmm, but moves.md mentions "sched1-birth-order" as a wall tag, and "global-alloc-priority".

Let me test: reorder the declarations of vv2/vh/vw (e.g. vh declared before vv2) — cheap try.

Let me generate h1-h8:
h1: reorder declarations: move `s32 vh;` before `u16 vv2;`.
h2: reorder: `s32 vw;` first.
h3: vh pair adjacent placed first in the group:
    vh = rec >> 24; v1.vy = vh; v0.vx = ...; vv2 = ...; v0.vy = vv2; v0.vz = sz; vw = rec >> 16; v1.vx = vw & 0xFF; v1.vz = sz;
h4: vw pair adjacent placed first, vh at end.
h5: v0.vx loaded last.
h6: v0.vy stored first (right after its load).
h7: v1.vy = vh and v0.vy = vv2 adjacent at end, temps computed at top.
h8: vh = rec >> 24 computed after the two sz stores.

Let me just do these.
