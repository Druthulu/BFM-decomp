---
ts: 2026-11-06T11:35:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rGsEW2qqwFbg4r2CxaD5
---
Target details:
- tmp computed into v0 then andi a1,v0,0xfff → a1. So `tmp = (...) & 0xFFF` in a1 (the pin was $5 = a1! MIPS reg $5 = a1). Yes: $5 = a1. So pin $5 gives tmp in a1.
- Then `move s1,a1` at 3270 (delay slot of beq v1,v0 for case 0x53). So s1 = tmp (sVar3).
- Then in the 0x53 arm: lhu v1,174(s0); li v0,128; andi a0,v1,0xff; bne a0,v0 → if lo != 0x80 goto 32f0; srl v0,v1,0x8; beq v0,a0 → if hi == lo(0x80) return 0; move v0,zero (delay slot). Then 32f0: lhu a1,174(s0) reload; li v0,128; andi a0,a1,0xff; addiu a0,a0,-128; srl a1,a1,0x8; jal ratan2; subu a1,v0,a1; addu v1,s1,v0; li v0,1; andi v1,v1,0xfff; sh v1,18(s2).

So the target has TWO loads of 174(s0): one for the compare, one for the call args. Because of the barrier. Without the barrier, cse reuses v1/a1: mine has one load.

So this is a cse issue: cse forwards the load. Wait but the store to *(u16*)(iVar5+0x12) happens after. And the call ratan2 — the loads are arguments computed before the call. CSE sees `*(u16*)(p+0xAE)` loaded at `bb = ...`, then the same expression at the call args; there's no store or call in between (the call's own args are evaluated before the call). So cse folds.

How to break cse with real C? A "dead reset" like C0414: reassign bb=0 after the compare? But bb is used... Hmm. Actually the value loaded is used in the compare; then the call reloads. If I can make the first load's value not be reused (e.g., the value in bb is dead after the compare), cse would still have the memory value in its table and forward to the second load.

CSE tracks memory: `(mem:HI (plus (reg) 0xAE))` in the hash table. The second load is the same expression → replaced by the register. To prevent, we need something to invalidate the memory table between: a store. The target's barrier does exactly that. Real C: a store to memory between... but any real store would appear in the output (and target has none between). Unless it's a dead store that flow deletes. C0414 "dead-reset cse-breaker" — that was about registers, not memory.

Hmm, the target does have a store after: `*(u16*)(iVar5+0x12) = ...`. But the load is before it.

Wait, ordering: mine at insn 45 lhu a0,174(s0), 46 li v1,128, 47 andi a1,a0,0xffff (bb & 0xFFFF? because bb is u32 = *(u16*) so andi a1,a0,0xffff — widening), 48 andi v0,a1,0xff, 49 bne..., 50 nop, 51 srl v0,a1,0x8, 52 beq..., 53 nop, 54 andi a0,a0,0xff ... hmm then 55+ probably addiu, srl, call, etc.

So mine has an extra `andi a1,a0,0xffff` because I declared bb as u32. Target has bb presumably s32 or the value used as HImode. Actually target: andi a0,v1,0xff directly, srl v0,v1,0x8. No 0xffff mask. So bb should be s32 (or the load is HImode and `bb & 0xFF` where bb is s32 sign-extends? lhu → zero-extend; if bb is s32 then bb & 0xFF = andi; bb >> 8 = srl? For signed s32, >>8 is sra normally. Target uses srl v0,v1,0x8 — logical. So bb is unsigned. But u32 & 0xFF gives andi on the u32... it's already 0..0xFFFF so no extra mask. Hmm mine has `andi a1,a0,0xffff` extra. Why? Because bb = *(u16*) → loaded as HImode and then converted to u32: `andi a1,a0,0xffff`. If bb is u16 (unsigned short), then `bb & 0xFF` → andi on u16 directly, `bb >> 8` → srl. So use `u16 bb` maybe? But then `bb >> 8` on u16 promotes to int, shift logical fine.

Actually target: the load result v1 used directly for andi and srl. So declare `u16 bb;` or keep the expression inline.

But the bigger issue: the reload. The target loads 174 twice. So we need cse to not forward. Options in real C:
1. Use a struct member load: "in-struct MEM" — the G21x move: struct-member u16 load makes cse invalidate. Hmm, that was for a nonscalar store invalidating.
2. Make the second access go through a different expression that cse can't match, e.g., `*(u16 *)(p + 0xAE)` vs `*(u16 *)((s32)a0 + 0xAE)` — same after folding.

Alternative: the first read could be from a different base pointer that's not provably equal, e.g. `*(u16*)((u8*)p + 0xAE)` vs `*(u16*)(p + 0xAE)` — same.

Hmm. What about a union/struct: `((struct X*)p)->unkAE` — MEM_IN_STRUCT. And the call args read `*(u16*)(p+0xAE)` (MEM not in struct). CSE treats in-struct and not-in-struct as different hash? In gcc cse, the memory expression hash includes the MEM_IN_STRUCT_P flag? Actually cse uses `rtx_equal_p` on the memory addresses and the mode. The MEM_IN_STRUCT flag is part of the MEM rtx. In gcc 2.7.2 cse.c, `rtx_equal_p` compares MEM attributes? Let's check: cse's `hash_rtx` — for MEM, it hashes the address only? Let me recall. In cse.c, `hash_rtx` does:
```
case MEM:
  /* We don't want to look at the memory expression's alias set... */
```
Hmm. Actually the G21x move said: "struct-member u16 load `sq->v` makes cse invalidate the *q cache at the nonscalar ptr[3] store". So MEM_IN_STRUCT affects alias invalidation: a store to a nonscalar pointer invalidates in-struct memories but not non-in-struct ones... Actually in cse.c `invalidate_memory`, the logic: if the store is to a non-struct memory, it invalidates everything? Let me look at cse.c.

But here the issue is the opposite: we want the load invalidated. There's no store between though.

Wait — is there? In the target, the store `sh v1,18(s2)` is after. Nothing between the two loads. So cse must be blocked some other way in the original: by the explicit memory barrier. Real C has no way to force a reload without a store/call... 

BUT: there's a call! `ratan2` is called at 3304. The call args are computed before. The loads at 32f0,32f4 are before the call. Hmm.

Wait, maybe the second load is not a "reload" in the C sense; maybe the original C genuinely reads `*(u16*)(p+0xAE)` twice, and without the barrier cse merges. The barrier makes cse clear its memory table.

Alternative real-C approach: make the first load and second load have different modes or addresses that cse can't equate, while generating identical code. E.g., first load via `*(u16*)(p + 0xAE)`, second via `*(u16*)(p + 0xAE + 0)`? No, folded.

What about the first load being done as `*(s16*)` vs `*(u16*)`? Different modes → different memory expression? In cse, the load is a HImode mem; signedness doesn't change the mode (HImode for both), but the extension is done separately (lhu vs lh). Actually `lhu` vs `lh` differ. Target uses lhu for both.

Hmm. Another idea: use a volatile pointer? `*(volatile u16*)(p+0xAE)` would prevent cse but generate the same lhu (volatile doesn't change code). But volatile is arguably a lever? The brief says lever-free = none of the row kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind. Is volatile a lever? It's a C qualifier that suppresses optimization — likely considered a lever-ish trick? Hmm, "no new lever of any kind" - the kinds listed are the shard's kinds (barrier, launder). Volatile could be considered a new lever of kind "barrier". Risky. But the check is likely automated: the delever tool detects pins/asm/launders. The constraint says MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had may stay, never added. So adding volatile = adding a new lever of a different kind, prohibited.

Let me think about real C. The two loads: the target's second load feeds the call. What if we write the C so the second read is of a *different object* that aliases: e.g., a local `u16 *q = (u16 *)(p + 0xAE);` and read `q[0]` — cse treats `*(u16*)(p+0xAE)` and `*(u16*)q` the same after substitution (q is a copy).

What if we use `p` as `u8*` for one read: `*(u16*)((u8*)p + 0xAE)` — folded to same address.

Hmm, what about the first read being through the `a0` pointer with a different offset arithmetic that doesn't fold at -O1? e.g. `*(u16*)((char*)p + 0xAE)` vs `*(u16*)(p + 0xAE)`: same.

Consider: cse's memory table is invalidated by a CALL. The call `ratan2` at 3304 is after the loads, so no help. But what if we reorder: compute the ratan2 call args first? No.

Wait, actually let's reconsider: is the second load actually a reload of the same address, or is the original C reading a different location? Target: `lhu a1,174(s0)` then `andi a0,a1,0xff; addiu a0,a0,-128; srl a1,a1,0x8; jal ratan2`. So ratan2(a0 = (v&0xFF)-0x80, a1 = v>>8). And the source has `ratan2((*(u16 *)(p + 0xAE) & 0xFF) - 0x80, 0x80 - (*(u16 *)(p + 0xAE) >> 8))`. Wait target second arg a1 = v>>8, not 0x80 - v>>8. Hmm: `subu a1,v0,a1` after the call — that's the result. Wait 3308: `subu a1,v0,a1` — hmm, that's after jal. Actually 3304 jal ratan2, 3308 subu a1,v0,a1 (delay slot!) — computes a1 = ret - (v>>8)? That doesn't match `0x80 - (v>>8)` as an argument.

Hold on. Let me re-read: the source says `ratan2((v & 0xFF) - 0x80, 0x80 - (v >> 8))`. That would compute `li t,0x80; subu a1,t,(v>>8)` BEFORE the call. But target shows `srl a1,a1,0x8; jal ratan2; subu a1,v0,a1`. The subu is in the delay slot and subtracts... v0 is the return of ratan2! That can't be an argument.

Unless... the call is not ratan2 but something else, or the args are: a0 = (v&0xFF)-0x80, a1 = v>>8, and then after return, a1 = ret - a1?? Then `addu v1,s1,v0` uses v0 (ret) and s1. Then andi v1,0xfff; sh. So the `subu a1,v0,a1` result is dead? That's the `flow-unused-result` style thing — computed but unused. Hmm, weird.

Wait — maybe I misread the C. `*(u16 *)(iVar5 + 0x12) = (sVar3 + sVar4) & 0xFFF;` where sVar4 = ratan2(...). So sVar4 = v0 return. addu v1,s1,v0. Then the `subu a1,v0,a1` in the delay slot is dead (a1 was v>>8, v0 ret). That looks like the compiler emitting a dead computation. Odd but it's what the original produced. That's a hallmark of the barrier/launder forcing something.

Actually wait: maybe the C is `0x80 - (*(u16 *)(p + 0xAE) >> 8)` and the compiler computed `a1 = v>>8` before, then `0x80 - a1` ... but target has subu a1,v0,a1 where v0 = ret, not 0x80. Hmm, unless the register v0 held 0x80 at the call? No, v0 is the return value after jal.

Hmm, hold on: `jal ratan2` writes v0. In the delay slot `subu a1,v0,a1` executes BEFORE the call takes effect, so v0 is still... what was v0 before? `li v0,128` at 32f4! So v0 = 0x80 in the delay slot. So `subu a1,v0,a1` = 0x80 - (v>>8) computed in the delay slot, and that's the second argument a1 to ratan2 (delay slot executes before the call's body but after the args are set). Yes! Of course. The delay slot computes the second arg. 

So target: a0 = (v&0xFF)-0x80 computed at 32fc, a1 = 0x80-(v>>8) in the delay slot. Fine, matches the source.

OK so the key difference is the double load. Mine has one load reused for both, plus the extra andi 0xffff.

Given the barrier is the mechanism for the double load, and real C can't force a reload without a store or call... unless: use the value from the first load only in the comparison, then call something? No.

Wait — actually cse's memory table: does a store to `*(u16*)(iVar5+0x12)` invalidate `*(u16*)(p+0xAE)`? iVar5 is loaded from p+0x20, unknown alias → yes it would invalidate all. But the store is after the call in source order. If we moved the store earlier... no.

Alternative: The first read `bb` is used in the compare; the second read is in the call args. If we make the first read happen *before* something that clobbers memory... 

Hmm, what about making the first load not a load at all in cse's eyes by loading it as two u8s? `u8 lo = ((u8*)p)[0xAE]; u8 hi = ((u8*)p)[0xAF];` → lbu a0,174; lbu v0,175. Target uses lhu. No.

What about using a union/bitfield? `((struct {u16 v;} *)(p+0xAE))->v`? MEM_IN_STRUCT. In gcc 2.7.2 cse, does MEM_IN_STRUCT_P affect hashing? Let me check cse.c's hash_rtx.

Let me grep the gcc source.
