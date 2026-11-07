---
ts: 2026-11-06T14:37:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0uqRrGQJL5vgGAFJ0WRs
---
In sched2, the launch order: T-20=45, T-19=47, T-18=49, T-17=52, T-16=58, T-15=61, T-14=64, T-13=67, T-12=70, T-11=72, T-10=75, T-9=77, T-8=94, T-7=96, T-6=98, T-5=86, T-4=89, T-3=100, T-2=104, T-1=105.

So the final order is 45,47,49,52,58,61,64,67,70,72,75,77,94,96,98,86,89,100,104,105.

If T-20 is the first emission, then 45 (a0=s0), 47 (a1) second. That would put a1 early. But the .s shows a1 late. So T-20 must be the LAST emission. Then the order is 105,104,100,89,86,98,96,94,77,75,72,70,67,64,61,58,52,49,47,45 — a1 (47) near the end. That matches the .s!

Wait, but the .s order I read: move $4,$16 (a0), li v0, li s0, sw, la v0, ..., la a1, la a2, li a3, sh, jal. So a1 is near the end (position 31). And 47 near the end. So the emission order is T-1 first (105), T-2 (104), ..., T-20 (45) last. So T-1 is the first slot, and 105 is emitted first. But 105 is the last insn of the block (the branch). That's weird — the branch should be last.

Hmm, unless 105 is not the branch but the first insn of the block in emission order. Let me check what insn 105 is. Let me look at the .rtl dump for insn 105.

Actually, maybe the block's insn order in the RTL is 43 (first) to 105 (last), and the scheduler's T-1 is the LAST time slot, so 105 (the branch) is scheduled last. Then the emission order is T-20 (45) first. That puts a1 (47) second. Contradiction again.

I'm going in circles. Let me directly check: in c1's .s, what is the first insn after the call? `move $4,$16`. That's a0=s0 (insn 45). Then the next is `li $2,-655360` (v0). So the order is 45, then v0. So a0=s0 is FIRST. And a1 (47) is at position 31. So the order is 45, [something], ..., 47. 

The sched dump order (T-20..T-1 or T-1..T-20) — if T-20 first: 45,47,... -> a1 second (wrong). If T-1 first: 105,104,...,47,45 -> a0 last (wrong, a0 is first in .s).

Neither matches! Unless the sched dump's insn numbers don't correspond to the .s order because of the delay-slot filling (reorg) after sched2. Reorg might move insns into delay slots.

OK, I'm spending too long on the mechanism. Let me take the empirical approach: the keepalive pins the la early. Real-C variants so far don't. This looks like a WALL.

But wait — let me reconsider. The score is 4 (ORDER), 51 ins = target 51. Only the la position differs. This is a sched1/sched2 ordering issue driven by the keepalive asm. 

Let me check the moves.md for similar ORDER cracks with keepalive. Earlier I saw:
- "keepalive | func_801810F8 | MATCH: obase set right after pbase and used for the first load too (sched1 then keeps la before the store)"
- "keepalive | func_801856D8 | MATCH: hoist a0pin=sp18 above the outer if (addiu born pre-branch, reorg fills beqz delay); inside the if cse sinks it into the bnez slot"

So there are real-C cracks for keepalive ordering. The technique: make the value USED earlier so sched1 keeps it early.

For our a1: I need a real use of a1 early. What early instruction could use a1? 

Idea: what if I compute `a0 = s0` and `a1 = &D_8019DC34` and then use a1 in the store `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;`? No.

Idea: what if the address computation for `v0` reuses a1? E.g., `v0 = (s32)&D_8019DAFC;` — different address.

Hmm, what if the original source passed a1 to an earlier function? No.

Wait — maybe I can make a1's value used in a comparison or a store that's already there. The `if (func_8012D5E4(a0, a1, a2, a3) == 1)` uses a1 as the 2nd arg. What if I pass a1 through another variable that's used earlier? No.

Idea: compute a1's address via a global array access that cse keeps? E.g., `a1 = (s32)D_8019DC34_ptr;`? no.

Hmm. Let me look at the target's OTHER `la` computations: `la $2,D_8019DAFC` is early-ish (position 25), `la $6,D_8019DC3C` is at position 29, `la $5,D_8019DC34` at 22. So a1's la is the earliest. The keepalive is what forces it.

Given the difficulty, and that this is a known wall class ("sched1-birth-order" / ORDER), let me consider recording a WALL. But the task wants me to try. I've done ~10 tries on this item. A WALL needs ≥20 min and ≥30 scored tries. I have maybe 10. Let me try a few more clever ideas, then decide.

Idea: use a1 in the `a2` assignment so both are computed together? `a2 = (s32)&D_8019DC3C;` — no.

Idea: `a1 = (s32)&D_8019DC34;` and then `a1 = a1 + 0;`? identity.

Idea: what if a1 is computed as part of a larger expression that's used early? Like `v0 = 0xFFF60000; a1 = ...;` reorder.

Idea: Make the `func_8012D5E4` call's argument a1 computed inline but ALSO assign a1 early? 

Hmm, what about using the do-while(0) to split the EBB BEFORE the la, so sched1 can't sink it? Wait, the la sinks DOWNWARD (later). To prevent sinking, I need a barrier AFTER the la. The do-while(0) creates a block boundary AFTER the la if I wrap the la and the following statement... but the boundary is at the end of the do-while. If I wrap `{ a1 = ...; }` then the boundary is after the la. sched1 can't move the la past the boundary if the boundary is a basic-block boundary. But a do-while(0) is not a basic-block boundary (it's a NOTE_INSN_BLOCK). Hmm.

C0535 says the do-while(0) "splits cse1's extended basic block" — cse's EBB, not the scheduler's basic block. So it affects cse, not sched1. For our case, cse might be merging the la with something? Unlikely.

Let me try the C0414 dead-reset: after `a1 = ...`, set a1 to 0? But a1 is used later, so that would break. Unless I re-set a1 later before the call:
```
a1 = (s32)&D_8019DC34;
a1 = 0;   // dead reset? no, a1 is used later... but if I re-set it before the call:
...
a1 = (s32)&D_8019DC34;  // again before the call
```
The first assignment's value is dead (overwritten by the second before any use), so flow deletes... no, the first la would be deleted as a dead store. Then only the second la remains (late). Doesn't help.

Hmm.

What about the "used for the first load too" trick (func_801810F8): make the value used earlier in a real way. For a1, is there an earlier load/store it could serve? The store `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;` — the base is a0, not a1. 

What if I swap the roles: use a1 as the base for the store? `((Unkstruct_800B5CB8 *)a1)...` — wrong (a1 = &D_8019DC34 is a different object).

Hmm.

OK, let me look at this from the target's perspective: the original source probably had the keepalive's job done by something. Given the function is small and the ORDER diff is just the la, maybe there's a simple trick: assign a1 and then USE it in the very next statement as a value, e.g., the store. Let me look at the store: `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;`. What if I write `*(s32 *)(a1 + (a0 - a1) + 20)`? absurd.

Let me try one more: make `a1` a function parameter of a helper? No.

Actually, let me reconsider: maybe I can make a1's la early by using a1 in the `v0` computation in a way that's semantically neutral but not folded. For example:
```
v0 = 0xFFF60000;
a1 = (s32)&D_8019DC34;
v1 = 0x40000000;
v0 = v0 | v1;
```
What if I write `v0 = 0xFFF60000; a1 = (s32)&D_8019DC34;` and then use a1 in an address computation that the target already has: `v0 = (s32)&D_8019DAFC;` — no.

Hmm. What if the `a2` address computation is expressed as `a2 = (s32)&D_8019DC3C;` and I compute `a1 = a2 - 8;`? Since &D_8019DC3C - 8 = &D_8019DC34! So `a1 = (s32)&D_8019DC3C - 8;` — that would make a1 depend on a2, so a2's la would be computed first, then a1 = a2 - 8 (an addiu). But the target has a1 as a `la` (lui+addiu), not a2-8. So the code would differ (a1 would be `addiu a1,a2,-8` instead of `lui+addiu`). Bad.

Hmm.

What if the `v0` address `&D_8019DAFC` and a1 `&D_8019DC34` are related? &D_8019DC34 - &D_8019DAFC = 0x138. So a1 = v0_addr + 0x138. Again, an addiu, not la. Bad.

OK. Let me consider that this might be a WALL. But before giving up, let me check the `.dbr` (delayed branch) dump — maybe the la is being moved by reorg into a delay slot? No, the la is not in a delay slot.

Actually, let me look at the target's .s once more: `move $4,$16; la $5,D_8019DC34; #APP #NO_APP; li $2,-655360; ...`. The #APP/#NO_APP marks the asm. So the la is immediately before the asm. The asm is at position 24 (after the la). 

What if the target's la being early is due to the asm being volatile and acting as a scheduling barrier? In sched1, an asm (volatile) might be treated specially. Without it, the la sinks.

Hmm, let me try replacing the keepalive asm with a real "volatile" memory access that's already there... no.

Let me try a completely different approach: maybe the la can be kept early by making a1's computation an ARGUMENT to an earlier function call. The func_8012B1B4 call: `func_8012B1B4(s0, &D_8019DC18)`. What if I change it to pass a1 too? No, that changes the call.

OK, let me make a decision: I'll try 2-3 more variants (do-while around la+next, and reordering a1 after v0 with a real use), then record a WALL if they fail.

Actually, wait. Let me reconsider the moves.md entry: "keepalive | func_801810F8 | MATCH: obase set right after pbase and used for the first load too (sched1 then keeps la before the store); dead s32 pad[2] dropped". The trick: set the value right after another and USE it for the first load. So the value is used early (in the first load), forcing the la early.

For a1, is there an early use I can create that matches the target? The target's early instructions after the la are `li v0`, `li s0`, `sw v0,20(a0)`, `la v0`, `li v1`, `or`, `li v1`, `or`, `la a2`, `li a3`, `sh s0,2(a0)`, call. 

What if a1 is used in the `sw` store's VALUE? `sw $2,20($4)` stores v0. If I wrote `((...)a0)->unk14 = v0 + (a1 & 0);` folds.

Hmm.

What if a1 is used as the base for the `unk2` store: `((...)a1)->unk2 = s0;`? Wrong object.

I think this is genuinely a WALL: the keepalive forces an empty-asm-adjacent ordering that real C can't reproduce because a1 has no early real use.

But let me try ONE more thing: the C0535 do-while(0) split placed to create a barrier AFTER the la. Specifically, wrap the la AND the next statement:
```
do { a1 = (s32)&D_8019DC34; v0 = 0xFFF60000; } while (0);  // !FAKE: do-while
```
This puts a block boundary after v0, so sched1 might keep the la+v0 together in source order. Let me test.

Also:
```
do { a1 = (s32)&D_8019DC34; } while (0);
v0 = 0xFFF60000;
```
(v1 already did this and got 4).

Let me test the combined do-while (v8).

Also, let me test making the la an explicit "used" value: `a1 = (s32)&D_8019DC34; v0 = 0xFFF60000; ... a2 = (s32)&D_8019DC3C;` — no.

Let me test v8 and then decide.

Actually, let me look at whether the issue is sched1 or sched2 by checking the .sched2 order of the target (orig). If orig's sched2 keeps the la early, the keepalive affects sched2. Let me compare orig's sched2 block 3 order. In orig, block 3 is 43-107. Let me read the tail of the sched2 block.

Hmm, time. Let me just test v8 and one more, then decide.

Let me also try: since the keepalive is `__volatile__`, maybe a real volatile read of a dummy would work? No, that adds a memory access.

Let me test v8.
