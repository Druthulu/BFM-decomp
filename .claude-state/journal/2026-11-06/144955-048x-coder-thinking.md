---
ts: 2026-11-06T21:49:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kPwNGhHXbVRp1Y7gzWxt
---
Still 13 for b3. Hmm.

Let me think about the target's $3 occupant differently. Maybe in the target, the packet chain got $4 because the *oidx qty* was allocated BEFORE it with a suggested hard reg $3. How would oidx get a suggestion to $3? From a copy with a hard reg: `reg_qty[sreg]` suggestion when sreg is a pseudo and ureg is hard. If oidx's source r181 (otz load) were copied from a hard reg... no.

OR: the reference had a *different qty* taking $3: e.g., the mask 0xff000000 (r184) or 0xffffff (r193). In target a2/a1. Hmm.

Wait, maybe I have the target's registers backwards: in target, `lw a0,0(a3)` at 174 — could this be r182 coalesced into the same reg as the final store value, which is $4 because... 

Let me look at the .lreg dump for our function to see the actual allocation and, importantly, check if the qty that got $3 in mine is the packet chain or something else. Then compare with the target's expected.

Actually, maybe a better lever: the .lreg dump will show if r84/r181 got a hard reg or a suggestion. Let me grep the .lreg for "reg:SI 84" or hard regs.

Hmm, time. Let me try yet another class of move: change the *mask constants* order or spelling to alter qty priorities. E.g., the mask 0xFF000000 and 0xFFFFFF: if written differently (`& ~0xFFFFFF` / `& 0xFFFFFF`), the RTL may differ in insn count. Target has lui a2,0xff00 (0xff000000) and lui a1,0xff + ori 0xffff (0xffffff). Same.

Alternative: what if the reference source's packet store used `pkt` as a `u32*` variable: `u32 *pp = (u32*)pkt; *pp = (*pp & 0xFF000000) | ...`? a3 test showed 13.

Let me try targeting the *other* side: make the oidx qty's priority higher than 24000. It has refs 7, live 16 → 8750. To exceed 24000: refs 7 needs live ≤ 2 (impossible) or refs ≥ 12 with live 16: floor_log2(12)=3, 3*12/16=2.25 → 22500, still < 24000. refs 16: 4*16/16=4 → 40000. So if oidx's qty had ~16 refs, it would win. That means the reference source used oidx many times! 

Hmm, 16 refs for oidx? That seems like a lot. But consider: if the original source didn't use a variable `oidx` but instead an expression repeated, the compiler might create multiple temps... no.

Alternatively, the oidx qty's live range in the reference could be much shorter. If oidx's live were ~4: refs 7 → 2*7/4=3.5 → 35000 > 24000. So if the reference computed oidx late (birth just before first use), its live would be short. But the disassembly shows the otz load at 178 and uses at 184 and 203 — live ~26 instructions in the final code! Hmm, but the *live range at local-alloc time* is measured on the sched1 RTL, where oidx's birth is at insn 343 and last use at 375; the positions differ from final insn order because sched1's order ≈ final order. So live ~16 positions.

Wait — in the target's final code, oidx is born at 178 and dies at 204: 26 instructions. In ours, born 178, dies 204 too (same schedule!). So the live range is the same. So the target's oidx qty had the same live 16-26 and refs. So the difference must be elsewhere: a different $3 taker.

What if in the reference, $3 was occupied by a *callee-saved* thing? No, $3 is caller-saved.

Let me look at the target vs mine at 160-177: identical except 174. So the qtys there are the same. The allocation of the packet chain in target = a0. For that, at allocation time, $2 and $3 were busy. $2 = r191 (loaded value). $3 = ??? In the target, oidx is in $3. Could it be that in the reference, oidx was allocated BEFORE the packet chain because of a *copy suggestion* to a hard reg $3?

How to get a copy suggestion to $3 for oidx: if some pseudo in the block is copied to/from a hard reg $3. Hmm.

Actually — here's a thought. In the reference, maybe `oidx` was not tied to the otz load. If `oidx = g.otz << 2;` and the compiler did the shift in a different place... no.

Alternatively, maybe the reference's otz load result r181 got a *suggestion* to $3 because g.otz was loaded from `20(sp)` — no.

OK let me look at the actual .lreg to see the final assignment and whether local-alloc gave r181 a suggestion. Also I realize: the .lreg dump shows the insns with hard registers; the qty grouping isn't shown. 

Let me try an entirely different lever: alter the *scheduling* of the otz load so it's born earlier (giving it a longer life but maybe different allocation order)? No.

Hmm, wait. Let me reconsider the local-alloc allocation ORDER: it's by priority; but the priority uses `qty_death - qty_birth` where birth/death are `2*insn_number` style indices? In reg_is_born, birth = 2*this_insn_number - ... So lives are doubled; ratio unaffected.

Let me compute priorities more carefully with ties: the packet qty = r182+r183+r194: refs = 2+2+2 = 6, birth = r182's birth, death = r194's death. live = (17-12)*2 = 10. pri = floor_log2(6)*6/10 = 2*6/10 = 1.2 → 12000. Hmm I previously said 24000 with live 5; using doubled units: live = 2*(17-12)=10, so 12/10=1.2 → 12000.

r191 qty = r191+r192: refs 4, birth pos13, death pos16 → live 6 → 2*4/6 = 1.33 → 13333.

oidx qty = r181+r84+r198: refs 2+3+2 = 7, birth pos5, death pos21 → live 32 → 2*7/32 = 0.4375 → 4375.

Packet 12000 > oidx 4375. Still packet wins.

For target, $3 taker must have pri > 12000 overlapping packet's range (pos12-17). Candidates: r191 qty 13333 (pos13-16) → takes $2 (v0). Then packet (12000) → $3. Unless another qty with pri between, overlapping, takes $3 first. What about the qty for r189 (index sum, r84's... no tie) — r189 = plus(r84, r187), r187 dies → r189 ties into r187's qty? ureg=r187 (used, dies), sreg=r189. r187's qty = r186+r187 (r186 died into r187). refs 2+2+2=6, birth pos8, death pos13 → live 10 → 2*6/10=1.2 → 12000. Same as packet! Tie → qty number decides: r186's qty born pos8 < r182's pos12 → r186/r187/r189 qty allocated first → takes $3, then packet takes $4!

In OUR compile, why did packet get $3 then? Because the r186 qty's live range (pos8-13) overlaps packet's (pos12-17)? Yes at pos12-13. So they conflict; r186 qty gets $3 first, packet should get $4. But ours has packet in $3 and r186/r187/r189 in v0 ($2)? Wait in the disassembly, the tag shift `sll v0,v0,0xe` at 183 = r187, and the index sum `addu v0,v1,v0` at 184 = r189. So r186/r187/r189 are in v0 ($2)! That means the r186 qty got $2 (not $3). Then packet got $3.

Why would r186 qty get $2? Because it has a *copy suggestion* or because at its live range $2 is free and it's allocated first among the top priorities. Priorities: r186 qty 12000, r191 qty 13333, packet 12000. r191 (13333) allocated first → $2 (if free). But r191's live is pos13-16; r186's live pos8-13 — they overlap at pos13? r191 born pos13 (insn 362), r186 dies pos13 (insn 362). Depending on boundaries, they may not conflict. So r186 qty could also take $2 after r191 dies. Local-alloc's find_free_reg checks conflicts by marked life arrays; if r191's life ends at pos13 and r186's ends at pos13, they might conflict or not.

In ours: r186 qty got $2, r191 also $2 (v0 used at 188 `lw v0,0(at)` — that's r191; and at 183 `sll v0,v0,0xe` r187). Both in v0 → they don't conflict.

So allocation: r191 qty (pri 13333) → $2. r186 qty (12000, lower qty num) → $3? But it got $2! Hmm, unless $3 was already taken by something else at pos8-13. What overlaps pos8-13 and got $3? In our code, v1 ($3) at that range: the otz load is at 178 (r181, pos5-7) then v1 used for... at 182 sll v1,v1,2 (r84!) — wait! r84 is in v1 = $3. So the oidx qty (r181+r84) got $3!

But r84 is in the SAME qty as r181 (tied). And oidx's last use is pos21, but the qty's register is fixed for its whole life. So the oidx qty occupies $3 from pos5 to pos21. That conflicts with the packet chain (pos12-17) and the r186 qty (pos8-13).

So the allocation order must be: oidx qty got $3 BEFORE packet/r186. But oidx pri 4375 < 12000. Contradiction... unless the qty priorities are different from my estimate.

Hmm, wait: maybe the tie r181+r84 gives qty_death = r84's last use but qty_birth = r181's birth, and n_refs = 2+3 = 5 (not including r198 since r198 ties at insn 375, but the tie happens during the scan in order; at the time of allocation, the qty is complete). Let me recompute: r198 tie: r84 dies at insn 375, so r198 (set at 375) ties into r84's qty. refs 5+2=7. birth pos5, death = r198's death (insn 379) pos22. live 34 → 2*7/34 = 0.41 → 4117.

So oidx qty pri 4117 — allocated late, after packet. Yet it has $3 in the final code. How?

Unless local-alloc's find_free_reg for the packet chain (allocated earlier) couldn't take $3 because... the packet chain qty's live range includes pos12-17, and at that time $3 was reserved by an *already-allocated* qty. Which? The r186 qty? If r186 qty (pri 12000, born pos8) allocated first and took $3, then packet (12000, later qty num) takes $4. But in ours r186 qty is in v0. Hmm, but r186 qty is a *tie* of r186+r187+r189 with r187's... let me recompute: r187 = ashift(r186,14), r186 dies → tie r187 into r186's qty. refs 4, birth pos8, death pos11 (r187's death at insn 354 pos10? REG_DEAD r186 at 354; r187 dies at 358 pos11). Then r189 = plus(r84, r187) at pos11, r187 dies → tie r189 into r187's qty. refs 6, death = r189's death at insn 362 pos13. live 2*(13-8)=10. pri 12000.

r189's death at pos13 — the same insn where r191 is born (pos13, insn 362). So r186 qty live pos8-13, r191 qty live pos13-16. Overlap at pos13? mark_life boundaries: birth/death at 2*insn_number. Death of r189 at insn 362 = 2*13? and birth of r191 at insn 362 = 2*13. They may or may not conflict (local-alloc's conflict test uses `qty_birth <= death && qty_death >= birth` with strict?). Typically a register dying at insn N can be reused by one born at insn N (they don't conflict if the death is at the input). But r189 is *used* at 362 (input) and r191 is *set* at 362 (output); the death is marked at the input, birth at output — so they don't conflict.

In ours: r186 qty in v0 and r191 qty in v0 — consistent with no conflict.

So allocation order among pri-12000: r186 qty (born pos8) before packet (pos12). Both take $3? They conflict (pos12-13 overlap). So r186 → $3, packet → $4. But ours shows packet $3, r186 $2! So r186 took $2 (free) — meaning when r186 was allocated, $2 was free. Priorities >12000: r191 (13333) allocated first → $2. If r191's life doesn't conflict with r186's (boundary at pos13), then $2 is still considered free for r186 (find_free_reg checks only already-assigned qtys' marked lives; if r191 is marked live at pos13 and r186 is also live at pos13, they conflict → r186 takes $3).

The result (both in v0) says they don't conflict → r186 got $2. Then packet (12000, next) → $2 free? packet's live pos12-17 overlaps r191's pos13-16 → $2 conflicts → takes $3. Yes! That matches ours: packet $3, r186/r187/r189 $2, r191 $2.

In target: packet $4, so $3 was taken by someone else at packet's turn. Who? The only pri-12000 qty before packet is r186 (takes $2). Then packet → $3. Unless there's another qty with pri between 12000 and... Let me look for qtys with pri >12000 that overlap packet: r191 (13333) → $2. Any qty with pri 14000+? 

Hmm, what about the qty for r189 being separate in the reference? If the reference's r187 didn't tie (e.g., because of a mode difference), then r189 could be its own qty with refs 2, live 2 → 10000. Doesn't help.

What if in the reference, r191 (the loaded D_800A6614 value) qty had a *copy suggestion* to $3? no.

Hmm, let me reconsider: maybe in the reference the packet chain's priority is LOWER than 12000, e.g., live longer. If the reference's r182 load was scheduled earlier (born pos10), live 14 → 12/14*10000 = 8571 → below r186 (12000) and oidx? oidx 4117. Then allocation: r191 (13333) $2; r186 (12000) $3 (conflicts with r191? no → but r186's turn: $2 maybe taken by r191 only if conflict; r186 would take $2 as in ours). Hmm.

Alternatively the reference's r194 (ior result) might not tie into r183's qty if combine merged the and/or into one insn. If the OR's source r183 dies → tie. Always.

I'm spending too long. Let me try a few "priority arithmetic" moves:
- Make the packet chain's live longer by loading the word earlier *in the source* so that sched1 keeps it early but the final code still matches? b1 gave 19 (198 ins) — one extra insn, probably the load moved and something else. Let me look at b1's diff quickly? Actually b1 = 19, close. Maybe tweak b1: the extra insn might be a nop or the load duplicated. Hmm.

- Make oidx's qty shorter-lived: if the second index use happened right after the first (before the packet store), oidx's life would be short and its priority high. But target keeps it across. 

Wait — what if the reference's oidx had a *hard reg copy suggestion* because the original C was `oidx = g.otz << 2` where g.otz... no.

Let me look at the actual original decomp attempt's prev_win: the pin was `register s32 oidx __asm__("$3")`. The pin creates a hard-reg preference via the *declaration*, so local-alloc's qty for oidx gets a suggested reg $3. That's exactly the mechanism. In the reference binary, oidx is in $3 — consistent with the original compiler choosing $3 naturally OR the original source pinning it.

Given the difficulty and that the prior author tried ~24 bodies, this may genuinely be a WALL. But the brief says each item was banked PARTIAL after <30 tries; the shard is a "crack" shard. I should make a serious attempt but not burn all 4 items on one.

Let me try 6 more targeted variants quickly, then decide:
c1: reorder the packet store expression so the load is the second operand: `(X & 0xFFFFFF) | (*(u32*)pkt & 0xFF000000)` — commutative OR might change tie order. Actually the RTL `ior r183, r192` order might flip → coalescing/tie changes → priorities change.
c2: swap and-mask into a variable `mask` reused: `u32 m = 0xFF000000;` etc.
c3: use `pkt` typed as `u32*` from the start (u32 *pkt) and adjust other uses — big change.
c4: oidx used as the second operand in the plus: `D_800A6614[(tag<<14) + oidx]` — changes operand order; the tie r189's input order may change.
c5: `*(u32*)pkt = (*(u32*)pkt & 0xFF000000) | (*(u32*)&D_800A6614[(*(u16*)(base+0xA3D2) << 14) + oidx] & 0xFFFFFF);` and same for otp.
c6: make the tag shift a separate variable (tag<<14) declared s32 → changes tie structure.

Let me test c1, c4, c6, plus d1: use `volatile`? no.

Also d2: change the *declaration order* of oidx before w2 etc. (C0505 decl order) — might change qty numbers? Qty numbers assigned at birth, not declaration. But the C variable's pseudo number allocation order can affect `reg_qty`? no.

Let me run c1/c4/c6.
