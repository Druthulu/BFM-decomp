---
ts: 2026-11-06T21:43:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_EtUriwPqEFX8JUojTotI
---
Now clear:
- Pseudo "tag" = lw a0,0(a3) at 174 (target) / lw v1,0(a3) (mine). Wait 174 loads from 0(a3). a3 here is a pointer... hmm at 174 a3 is pkt pointer. `lw a0,0(a3)` loads the current *(u32*)pkt. So that's the packet word, not tag. Then 178 `lw v1,20(sp)` = g.otz load? then sll by 2 = oidx. 181 lhu v0,-23598(at) = the D_800A6614? no, -23598(at) with at=t1+0x10000; t1 = base. base+0xA3D2 holds a u16 — that's the "tag" value. Then sll v0,v0,0xe = tag<<14.

So:
- "packet word" pseudo: target a0, mine v1 (loaded at 174, used at 190 and 193: and a0,a0,a2; or a0,a0,v0; sw a0,0(a3)). This pseudo lives 174→193.
- "oidx" pseudo: target v1, mine a0: lw at 178, sll at 182, addu at 184, then used again? At 203-204 target: addu v1,v1,v0; addu v1,v1,a0 — v1 here is oidx (still live!), a0 = D_800A6614 base. So oidx lives 178→204. Longer than the packet word (174→193)? Actually oidx birth 178, death 204; packet birth 174 death 193.

So oidx has longer life but gets... target oidx=v1($3), packet=a0($4). Mine packet=v1($3), oidx=a0($4).

Priority = n_refs*log2*size/lifetime. oidx: how many refs? In RTL, `oidx` used twice (in two index expressions). The packet word is used twice (and, or). Both n_refs 2? lifetimes: packet 19 insns, oidx 26. So packet should win $3 in both cases! Yet target gives $3 to oidx. So maybe n_refs differ: oidx has more refs than the packet word.

Wait — the packet word is loaded as `*(u32 *)pkt` and stored back: `*(u32 *)pkt = (*(u32 *)pkt & ...) | ...`. That's one load and one store, but the store is the same memory. In RTL, the value pseudo is set once, used twice (and, or) → n_refs = 2.

oidx: used in the first expression `&D_800A6614[oidx + tag<<14]` and second same. But the first expression's address is folded into `at` (base+index) — oidx used once at 184. Second at 203/204: addu v1,v1,v0 then addu v1,v1,a0 — wait that's `oidx + (tag<<14)` then `+ D_800A6614`. So oidx used again. So 2 refs each.

Hmm, but why target gives oidx $3? Maybe because of copy preferences / qty suggestions: local-alloc has a "suggested register" phase (qty_sugg_compare) before the general sort. The packet word might have a suggested hard reg $3 from a copy (e.g., it was coalesced with something) or oidx got $3 via suggestion.

Actually the target's $3 for oidx could come from the *pin* in the original source! The original had `register s32 oidx __asm__("$3")` — a pin gives a suggested register (hard reg). But target is the *compiled original* (the game's bytes), which is the reference; the source we write must reproduce it without pins. In the target, oidx indeed is in $3 — likely because the original source used $3 naturally (or the compiler chose it).

Hmm wait. The reference is the game binary, not built from our source. So the reference register assignment is whatever the original compiler did. Our source must coax the same.

So local-alloc in the reference chose oidx $3 and packet $4. In our compile it's the opposite. What differs? The reference's source may have had different expression structure leading to different n_refs or suggested regs.

Let me think about qty suggestions: local-alloc first pass: for each qty with copy suggestions, try to allocate the suggested reg. Copy suggestions come from `reg_copy_sugg` — registers tied by copies (e.g., a move from one pseudo to another, or a return value). The packet word pseudo is the result of `lw` from pkt; no copy. oidx is `g.otz << 2` — no copy.

Then the main sort: priority = floor_log2(n_refs)*n_refs*size/(death-birth). If both n_refs=2, floor_log2(2)=1, size=1: packet pri = 2/19, oidx = 2/26. Packet higher → gets first free reg. Free regs among $3,$4? $2 might be free too. Which is first? find_free_reg iterates hard regs in order: for each `regno` 0..FIRST_PSEUDO, if in class. $2 (v0) might already be taken by something else (pkt? a3? etc). Hmm.

Actually maybe $2 is occupied by another qty (e.g., the pkt pointer? no, pkt is a3). Let me see: registers in use in this region: a3 (pkt), a2 (0xff00 mask), a1 (0xffff), t1 (base), at (scratch). So $2 v0 free, $3 v1 free, $4 a0 free. The first allocated qty takes $2? But neither got $2; v0 is used as the loaded value temp. Hmm, the value loaded (v0 at 188) is another qty that might take $2.

Wait, order of allocation is by priority; the highest priority qty gets the first free reg in its class. $2 is likely allocated to the highest-priority qty. Then $3, $4.

In mine, packet (pri 2/19) got $3, oidx (2/26) got $4. So something else got $2. In target, oidx got $3 and packet $4; so oidx outranks packet.

Unless n_refs differ: if oidx n_refs=3 vs packet 2: floor_log2(3)=1, pri=3/26=0.115 vs 2/19=0.105 → oidx wins! So oidx might have 3 refs in the reference. Why would it? Because the source might reference oidx three times, e.g. the two index expressions plus... Hmm. Or the packet word has n_refs counted differently (the store to *pkt doesn't count as ref of the loaded value? it does).

Alternatively the target's packet pseudo might have a longer life: if the load of *(u32*)pkt is scheduled differently... but the life is measured on RTL before scheduling (local-alloc runs before sched1? Actually local-alloc runs after sched1? Pass order: expand, jump, cse, ... sched1, local-alloc? In gcc 2.7.2: sched1 runs before local-alloc? Let me recall toplev: `if (optimize > 0) { ... combine_instructions; ... }`; local_alloc then sched1? Actually order in toplev.c: `if (optimize > 0) { ... }`; `rest_of_compilation`: `... if (optimize > 0) { ... }`; schedule_insns is called in two places: sched1 after combine and before local-alloc? Let me check: In gcc 2.7.2 rest_of_compilation:
```
  if (optimize > 0) {
    ...
    if (flag_schedule_insns) schedule_insns (insns);
    ...
    local_alloc ();
    ...
  }
```
I think sched1 is before local-alloc. So the RTL at local-alloc has sched1-reordered insns. The life spans are post-sched1.

In the target disassembly, the oidx chain: lw v1,20(sp) at 178 (after the packet word load at 174). So oidx born after packet. death: oidx at 204, packet at 193. So packet life 174-193 (19), oidx 178-204 (26). For oidx to win, n_refs must be higher.

Hmm, but n_refs is computed in flow (before sched1), counting register references in the whole function. Let me think about the source-level refs:
- packet word: `*(u32 *)pkt` appears twice (load, and in the OR assignment). If the compiler loads it once (cse/combine) then the pseudo has 2 refs. 
- oidx: `oidx` appears twice in the two address expressions. 2 refs.

Both 2. But wait, the second expression `otp = (u32 *)&D_800A6614[oidx + (*(u16 *)(base + 0xA3D2) << 14)];` — `oidx` is an SImode variable used as index. The index expression `oidx + (tag<<14)` — in the address, the compiler might use oidx twice? No.

Hmm, maybe the tag pseudo also has refs: tag = `*(u16*)(base+0xA3D2)` appears twice but it's reloaded each time (no cse because base+... may alias?). In disassembly, tag is loaded twice (181, 200) — so two separate pseudos, each 1 ref.

Let me instead get the actual n_refs via cc1 dumps. We have tools/cc1_dumps_tu.sh + alloc_table.py. Let me check how to use them.

Actually, maybe easier: use local-alloc dump (-dl) via cc1 to see qty priorities for both the current body and understand what would flip. But the reference we can't dump. However we can reason: we need oidx to outrank the packet word.

Options to raise oidx priority:
1. Increase oidx's n_refs by using it one more time in the source (a real C use that doesn't change generated code? risky) — e.g., compute `otp = &D_800A6614[oidx + ...]` twice? The second address recomputes; adding a third use might add refs without changing code if cse merges. But refs count pre-cse? flow runs after cse (n_refs from flow, which is after cse/combine? order: cse, ... flow, combine, sched1). So cse already merged; adding a redundant use would be cse'd away before flow? Actually cse runs before flow, so extra identical expressions get merged → no extra refs.

2. Reduce packet word's n_refs from 2 to 1: e.g., restructure so the loaded word is used once. But both and+or need it.

3. Change lifetimes: make packet's birth later / death earlier. The packet word is loaded at 174 but its first use is at 190 (and). If we could delay the load... but the load is scheduled by sched1. In source it's `*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (...)`. The load must happen before the store. sched1 placed it at 174 (early, after the sh's). Hmm.

Actually wait — lifetimes for local-alloc are computed from the RTL insn order *after* sched1, so the load position matters.

4. Change size/mode: if oidx were HImode? No, it's an index.

5. Use a copy suggestion: assign oidx via a variable that has a copy preference to $3? Copy suggestions come from `reg_copy_sugg` where two pseudos are tied by a move. Hard to steer.

Hmm, but the notes say "Widths (oidx s16/u16/u32), an explicit tag temp, oidx inlined / moved / cast, and the tail statement orders all stay at 13-16." So these were tried.

Let me reconsider. Maybe the target's oidx priority is higher because in the reference source, oidx had 3 refs: e.g., the source might have been:
```
oidx = g.otz << 2;
*(u32 *)pkt = ... D_800A6614[oidx + ...] ...;
otp = (u32 *)&D_800A6614[oidx + ...];
*otp = ...
```
2 refs. Unless the original had `oidx` used in a bounds or the address split differently.

Alternatively, the target's packet pseudo might be *not* a pseudo with n_refs 2, but the value stored directly from memory? No.

Wait — maybe the packet-word pseudo in the target has n_refs=2 but lifetime longer than I think because death is at the store 193 and birth at 174 → 19. In mine same. So priority equal → tie broken by qty number (`return *q1 - *q2`): the lower qty number wins. qty numbers are assigned in order of birth (alloc_qty called at birth during local-alloc's scan). The packet word is born at 174, oidx at 178, so packet has lower qty number → packet wins tie → gets $3. That matches mine!

For target, oidx wins → must have strictly higher priority. So its n_refs must be higher (3) or life shorter.

Could the reference's oidx have n_refs=3 because `oidx` appears in the RTL as a 3-operand? Hmm.

Let's test the hypothesis by adding a real third use of oidx that survives cse. E.g., compute the second address as `&D_800A6614[oidx + (tag<<14)]` but with tag recomputed... no.

What if we split oidx: `oidx = g.otz << 2;` and use `oidx` three times by writing the two address expressions plus e.g. `pkt[0x??] = oidx;`? That changes code.

Alternative: reduce packet word n_refs to 1 by changing `*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (...)` into a form where the load result is used once? Not possible; both operands needed.

Hmm, but what about the `and a0,a0,a2` at 190: a2 = 0xFF00... Actually at 190 target: `and a0,a0,a2` where a2=0xff00 (lui a2,0xff00). Wait 0xFF000000 mask: `lui a2,0xff00` = 0xff000000. So packet_word & 0xff000000. Then or with (loaded & 0xFFFFFF). So 2 uses of packet_word.

Unless the reference source used the same variable for both the loaded word and something else... 

Let me approach differently: maybe the packet word in target isn't a local-alloc qty that competes; maybe it's allocated by global-alloc? No, it's block-local.

Wait, actually reconsider: is it possible the target's *oidx* is actually a different pseudo — e.g., the reference source computed `oidx = g.otz << 2` but also `g.otz` is used? Hmm.

Let me look at what registers are: target: packet_word in a0 ($4), oidx in v1 ($3). Also a2 = 0xff000000 mask, a1 = 0xffffff, a3 = pkt, t1 = base, v0 = temps.

So local-alloc allocated $2 to a temp (v0), $3 to oidx, $4 to packet word. That means oidx had the highest priority among the three? Or $2 to the highest. The temps at v0: the tag load `lhu v0` and the loaded D_800A6614 value `lw v0` and addu at — many short-lived temps with high priority (short life, 1 ref → floor_log2(1)=0 → pri 0!). Hmm floor_log2(1)=0 gives pri 0. For n_refs=1, pri=0. So multi-ref pseudos win.

Let's compute: qtys with n_refs=2:
- packet word: pri = (1*2*1)/(193-174)=2/19≈0.105
- oidx: 2/(204-178)=2/26≈0.077
- a2 mask (0xff000000): set at 176, used at 190, 208? and v0... `and v0,v0,a2` at 208 and `and a0,a0,a2` at 190. Born 176, death 208 → 2/32=0.0625.
- a1 mask 0xffffff: born 170, used 191, 206 → 2/36=0.055.
So packet wins $2? But $2 is v0 used by temps... hmm but target has packet in $4, not $2. So maybe $2 was taken by something with higher priority: e.g., a qty with n_refs=3.

Hmm, local-alloc allocates in sorted order; each takes the lowest-numbered free reg in its class at its live range. Since all these are in the same block, they conflict? No—different live ranges may allow sharing: packet word live 174-193, oidx 178-204 → overlap, conflict. a2 mask 176-208 overlaps both. So they can't share.

$2 v0: used by temps at 181,183,188,200,202... those temps are short-lived. The temp `lhu v0,-23598(at)` result at 181 used at 183 → very short, n_refs=1, pri 0. So it wouldn't outrank. But allocation order: higher priority first; packet (0.105) first → should get $2 (lowest free). Unless $2 is in a different class? No, all general.

Unless local-alloc's find_free_reg excludes $2 for some reason (e.g., $2 is fixed/call-used? v0 is call-clobbered but fine). Hmm, in local-alloc, find_free_reg for a qty with no calls crossed considers all regs in class, but there's `qty_n_calls_crossed` and `regs` mask from preferred class. Actually `reg_preferred_class` for a pseudo may be ALL_REGS, and find_free_reg uses `reg_class_contents[class]` intersected with `regs` (allowed set passed). In `local_alloc`, the call is:

```c
qty_phys_reg[q] = find_free_reg (qty_min_class[q], qty_mode[q], q, 0, 0, qty_birth[q], qty_death[q]);
```

Hmm. Also note `$2` might be reserved because it's `HARD_REGNO_CALLER_SAVE_MODE`? no.

Maybe the temps take $2 because they are *born* early and allocated in the first phase via copy suggestions? No.

Let me stop speculating and get the actual cc1 -dl dump for our v0.c body. tools/cc1_dumps_tu.sh can produce dumps. Let me check its usage.

Actually the key question: what makes the target assign oidx $3? Could be that in the reference source, oidx had n_refs=3. Let me test empirically: create a body where oidx is used 3 times in a way that generates identical code (e.g., use oidx in the `pkt[0xC]` or elsewhere? no).

Alternative approach: make the packet-word pseudo have n_refs=1 by *not* reusing it: e.g., change `*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (X & 0xFFFFFF);` to load into a variable `u32 pw = *(u32*)pkt;` then `*(u32*)pkt = (pw & ...) | ...`. Still 2 refs of pw.

Hmm. What if we do the masking differently so that the memory value is used once: `*(u32*)pkt |= X & 0xFFFFFF` — but that would produce `or` with the full word, not and-mask. Target has the and 0xff000000.

OK here's another thought: qty priority uses qty_size = register size in words. For SImode size=1, HImode size=1? Actually `size` passed to alloc_qty is `reg_size[regno]`, which is the number of hard regs (1 for SI and HI on mips32? HI is 1). So no.

qty_n_refs comes from reg_n_refs. But note: for a pseudo that is set once and used twice, n_refs counts *sets* too? reg_n_refs is incremented in flow for each REG occurrence including the set. So packet: 1 set + 2 uses = 3 refs. oidx: 1 set + 2 uses = 3 refs. Both 3! Then pri: floor_log2(3)=1, 1*3/19 = 0.158 vs 3/26=0.115. Packet still wins.

Hmm wait — floor_log2(3) = 1 (floor log2 3 = 1). Yes.

Unless oidx has more uses. Let me count in the target disasm: oidx appears at 182 (sll), 184 (addu), 203 (addu), 204 (addu). At 203-204: `addu v1,v1,v0` then `addu v1,v1,a0` — v1 (oidx) used twice in a row! That's `oidx + tag<<14 + D_800A6614`? Wait the first expression uses `at` for the sum. Let's map:

First: `&D_800A6614[oidx + (tag<<14)]`:
- 178 lw v1,20(sp) [otz]
- 181 lhu v0,-23598(at) [tag]
- 182 sll v1,v1,2 [oidx]
- 183 sll v0,v0,0xe [tag<<14]
- 184 addu v0,v1,v0 [oidx + tag<<14]
- 185-187 lui at,0; addu at,at,v0 [D_800A6614 + idx]
- 188 lw v0,0(at)
So oidx used once at 184.

Second: `otp = (u32 *)&D_800A6614[oidx + (tag<<14)]`:
- 194-196 lui a0,0; addiu a0,a0,0 [D_800A6614 base]
- 198-200 lhu v0,-23598(at) [tag again]
- 202 sll v0,v0,0xe
- 203 addu v1,v1,v0 [oidx + tag<<14] — oidx used here
- 204 addu v1,v1,a0 [ + D_800A6614]
- 205 lw v0,0(v1)
So oidx used twice: 184 and 203. Total 2 uses + 1 set = 3 refs.

Packet word: 174 lw a0; 190 and; 193 or → 2 uses + 1 set = 3 refs. Life 174-193.

So both n_refs=3, packet higher priority. Yet target chose oidx. So the reference must have a different structure — OR the target's register allocation came from a *different* mechanism: copy suggestions! 

Look: in target, at 203-204, `addu v1,v1,v0; addu v1,v1,a0` — oidx is accumulated in place. In mine, `addu a0,a0,v0; addu a0,a0,v1` where a0=oidx, v1=D_800A6614 base. Hmm.

Copy suggestion: `qty_phys_copy_sugg` is set when two pseudos are related by a copy (move). In the target, maybe oidx is copy-related to something in $3 (e.g., a call result in $2/$3? no).

Alternatively, maybe the target's allocation isn't local-alloc for oidx: maybe oidx is a *global* pseudo (live across a basic block boundary?) The tail is in one block, but oidx's uses are in the same block. global-alloc runs before local-alloc; if oidx were allocated by global-alloc it'd have a hard reg fixed already. Hmm, but all these are within one basic block after the div. Unless the basic block extends from before.

Hmm wait — actually the div is in the middle; oidx's uses span... no.

Let me consider that the reference source had the tail differently such that oidx had a *shorter* life or more refs. For instance, if the reference computed `otp` first (the second expression) and then the packet store, ordering could differ. But the instruction order matches except the swap.

Honestly, the most productive path: brute-force a few structural variants with the scorer. The notes already tried many. Let me try new ideas:

Idea A: Make the packet-word load happen *later* (shorten life): reorder source statements so the `*(u32*)pkt = ...` statement comes after computing otp? But that changes the order of stores (target has packet store at 193 before otp store at 209). Reordering would change output? They're independent stores to different addresses (pkt vs otp). If we move `otp = ...` computation before the packet store, sched1 may keep order... The target order is packet store then otp. Hmm.

Idea B: Increase oidx refs: use `oidx` a third time in a way cse won't merge and codegen ignores? E.g., `if (0) pkt[0x26] = oidx;` would add code (dead code eliminated by flow? flow runs before? flow is before combine; dead code with constant 0 branch removed at jump/optimize). Actually `if (0)` is folded at tree level, no code. Won't add refs.

What about a `do { ... } while (0)` wrapper? no refs.

Idea C: Make the tag load not reuse `at`: currently the tag load uses `lui at; addu at,t1,at; lhu v0,-23598(at)` twice, and `at` is the assembler temp. Fine.

Idea D: Reduce packet word priority by extending its life? No, higher life = lower priority. Wait: priority = refs/life. To make packet lower priority we can *extend its life*. Its death is the store at 193. If we could make the packet-word pseudo live longer (e.g., use it after the otp store), its priority drops below oidx's. E.g., reuse the loaded word for something after: `*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);` uses pkt, not the word. Hmm.

What if we write the final `| ((u32)pkt & 0xFFFFFF)` using the *loaded word* variable? No, that's pkt's address.

Alternatively shorten oidx's life: its last use is at 203/204. If the second address expression is restructured so oidx is used earlier... but the order is fixed.

Idea E: Split oidx into two pseudos: use `g.otz << 2` directly in the first expression and a variable in the second. Then the first use doesn't involve oidx; oidx has 1 set + 1 use = 2 refs, life 178?→203. That lowers priority. Opposite.

Idea F: Make oidx a `u32` vs `s32` — no difference. Notes tried.

Idea G: Since priority tie-ish, maybe change qty birth order: if oidx were *born earlier* than packet word, then... no, priority is by refs/life, tie by qty number (birth order). If oidx born earlier (lower qty number) and priorities equal, oidx wins. Priorities: packet 3/19 > oidx 3/26, not equal. Unless we extend packet's life to ≥26: birth earlier (before 174) or death later (after 200). If packet life ≥ 26, its pri ≤ 3/26, tie → lower qty number wins. Packet born at 174 < oidx 178 → packet still wins tie. So we'd need packet pri < oidx pri, i.e., life > 26.

Hmm, so making packet's load earlier by 7+ insns? The load is at 174, quite late. If the load moved to ~168 it'd be born earlier and life longer. But sched1 controls that.

Actually! Consider: the loaded packet word could be loaded *earlier* if the expression is computed earlier in source, e.g., before the `sh` stores. In target it's at 174, after the sh's at 160-177. Actually the source order: the packet store expression comes after all the sh stores. If we moved it earlier in source (before the sxy stores), the load might be scheduled earlier. But that would change instruction order vs target. Unless sched1 re-sorts it back. Risky but testable.

Idea H: Change the number of refs by using the packet word in the second store too. E.g., the final store `*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);` — what if the reference source was `*otp = (*otp & 0xFF000000) | (pw & 0xFFFFFF)` where pw is the *first loaded word*? No, target shows `and a1,a3,a1` at 206 = pkt & 0xffffff, then or. So it's pkt.

Hmm, at 206: `and a1,a3,a1` — a3 = pkt, a1 = 0xffffff. So yes pkt.

Idea I: Maybe the reference's oidx has n_refs=4. Where? If the original source used oidx in a place that got cse'd into the same register... 

Wait, maybe the reference source is:
```
oidx = g.otz << 2;
*(u32 *)pkt = ... D_800A6614[oidx + (tag << 14)] ...
otp = (u32 *)&D_800A6614[oidx + (tag << 14)];
```
Same. Unless the original had `oidx` also as the offset for something else, like a bounds check `if (oidx < 0)`? No.

Let me look at the actual original source? This is a decomp project; src is our reconstruction. Maybe there's an asm listing / splat with the original? The "target" is the game binary. There may be a reference disassembly with symbols but not original C.

OK let me try a different lever: local-alloc's `find_free_reg` uses `qty_n_calls_crossed`. Both 0.

Hmm, what about `qty_changes_size`? no.

Let me get the -dl dump for v0.c to see actual qty priorities and the qty numbers. That will tell whether packet is 3/19 etc. Then I can find a lever that flips. Let me check tools/cc1_dumps_tu.sh usage.
