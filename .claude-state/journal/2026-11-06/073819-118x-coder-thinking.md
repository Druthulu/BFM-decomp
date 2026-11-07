---
ts: 2026-11-06T14:38:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_E03zp1TOjFHruhXSqRN1
---
Still 4. The la always sinks to position 31.

Let me look at the target's sched2 order vs c1's to understand which pass. Actually, let me check the target's .sched2 block 3 order. In orig (_d4), block 3 is 43-107. Let me read the tail of the sched2 block 3 and find where insn 47 (a1 la) is launched.

Actually, let me compare the sched2 dumps: in c1, the launch order (T-1..T-20) is 105,104,100,89,86,98,96,94,77,75,72,70,67,64,61,58,52,49,47,45. In orig (target), the block has 2 extra insns (the asm at ~49-50). Let me read orig's sched2 block 3.

Hmm, but the .s order suggests the launch order T-1..T-20 corresponds to emission order? In c1, the .s order is: a0(45), v0, s0, sw, la v0, or, or, la a1(47), la a2, li a3, sh, call... So a0 is first and a1 is 8th. The sched2 launch order T-20..T-1 would be 45,47,49,52,58,61,64,67,70,72,75,77,94,96,98,86,89,100,104,105 — a1 second. Doesn't match.

The T-1..T-20 order is 105,104,100,89,86,98,96,94,77,75,72,70,67,64,61,58,52,49,47,45 — a1 19th (near end). The .s has a1 8th. Doesn't match either.

So the sched2 dump's order isn't the final .s order (reorg/dbr may reorder, or the dump's T numbering is confusing). Let me stop trying to map it.

Given the difficulty, let me consider the time: ~08:20, I've spent ~20 min on this item. The budget is 20-30 min. I have ~10 tries (need 30 for a WALL). Hmm.

Let me think about whether there's a known real-C trick for "keepalive forces an la early". The moves.md entry func_801810F8: "obase set right after pbase and used for the first load too (sched1 then keeps la before the store)". So the trick is to make the value used in the first load/store.

For a1, the target uses a1 only at the call. But maybe I can make a1 used in the FIRST store (`sw $2,20($4)`) — no, that store's base is a0.

Wait, what if the target's `la $5,D_8019DC34` is actually used by the store `sh $16,2($4)`? No, that uses a0.

Hmm.

What if I reorder the source so that a1's la is naturally before v0? The scheduler sinks it because it has no early use. 

Let me try a DIFFERENT real-C structure: what if I compute a1 and a2 together early, e.g., `a1 = (s32)&D_8019DC34; a2 = (s32)&D_8019DC3C;`? Then both la's are early. The target has a2 late (`la $6,D_8019DC3C` at position 29). So that would move a2 early too — wrong.

What if a1 is assigned and then a2 is assigned from a1? `a2 = a1 + 8;`? Then a2 would be `addiu a2,a1,8` instead of `la`. Wrong.

Hmm.

Let me look at the target's exact ordering once more:
```
	move	$4,$16          # a0 = s0
	la	$5,D_8019DC34   # a1
 #APP
 #NO_APP                 # keepalive
	li	$2,-655360      # v0 = 0xFFF60000
	li	$16,4           # s0 = 4
	sw	$2,20($4)       # a0->unk14 = v0
	la	$2,D_8019DAFC   # v0 = &D_8019DAFC
	li	$3,0x40000000
	or	$2,$2,$3
	li	$3,0x20000000
	or	$2,$2,$3
	la	$6,D_8019DC3C   # a2
	li	$7,0x20         # a3
	sh	$16,2($4)       # a0->unk2 = s0
	jal	func_8012D5E4
	sw	$2,88($4)       # a0->unk58 = v0
```

The keepalive sits between the a1 la and the v0 li. The scheduler placed the asm right there. Real C cannot place an empty barrier there without an asm.

Unless... the ORIGINAL source had a real operation there that produces no code. Hmm.

Wait — what if the source had `a1` used as an argument to a macro or inline function that got optimized away? No.

I'm fairly convinced this is a WALL. But let me check: the function might have been previously attempted in another shard. Let me grep moves.md/walls.txt for func_80183130 — earlier grep found nothing. Let me also check other shards' results for it.

Actually, let me reconsider: the pin `register s32 a0 __asm__("$4")` is present. Maybe I can use the PIN to my advantage? No, I can't add levers.

Wait — actually, maybe I can KEEP the pin and the pin affects the schedule. The pin is `a0` in $4. Hmm.

Let me look at whether there's a real-C way to get the la early: what if I make `a1` the destination of a `register`-less copy that's used early? 

Hmm, let me try: `a1 = (s32)&D_8019DC34; a0 = s0;` and then `((...)a0)->unk14 = v0 + (a1 - a1);`? folds.

OK. Let me try the C0414 "dead-reset" applied differently: what if I add a dead store that uses a1 early, which flow deletes? E.g., `a1 = (s32)&D_8019DC34; v1 = a1;` where v1 is then overwritten (dead). `v1 = a1` is a copy with a dead dest (v1 is overwritten by 0x40000000). Flow deletes the copy (dead store) BEFORE counting, so no ref. But wait — does flow delete it? The insn `(set v1 a1)` with v1 dead -> insn_dead_p -> deleted. So the use of a1 isn't counted. But the INSN existed during sched1? No — flow deletes it before sched1. So sched1 never sees it. No effect.

Hmm.

What if `v1 = a1;` and v1 IS used (not dead)? Then it's a real copy (extra instruction). Unless combine folds it. `v1 = a1; v1 = 0x40000000;` — v1 is overwritten, so the copy is dead. Flow deletes.

What if `v1 = a1` and then `v0 = v0 | v1`? That would use v1, but the target's `or $2,$2,$3` uses 0x40000000, not a1. So wrong.

OK, I'll record this as a WALL. But first, let me make sure I've done enough tries and note the evidence. Actually, wait — the task says a WALL needs ≥20 min AND ≥30 scored tries. I have ~10 tries and ~20 min. Let me do a few more tries to get closer, but honestly, if I'm confident it's a wall, I should record it accurately. The instruction: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So if I can't reach 30 tries, it's "not an attempt" — but I can't do 30 meaningful tries if the mechanism is clear. Hmm.

Let me reconsider. Maybe there IS a crack I'm missing. Let me look at the moves.md "keepalive" cracks again, especially those with ORDER/sched:
- func_801810F8: obase set right after pbase and used for the first load too.
- func_801856D8: hoist a0pin=sp18 above the outer if.
- func_80187988: hoist rand() to a temp c and put val=nudge before the test.

The common thread: use the value earlier in a real computation.

For a1: what if I make the a1 la serve as the base for an early store? The early store is `sw $2,20($4)` (a0->unk14). What if I change the order so that a store to a1 comes first? No, the semantics.

Hmm, wait. What if a1 is used in the `func_8012D5E4` call's a2/a3 computation? Like `a2 = (s32)&D_8019DC3C; a3 = 0x20;` — no a1.

What if the target's early la is forced by the fact that a1 is live across the call? No, the call is the use.

Let me look at the sched1 priority: the la's priority is 1. The scheduler schedules insns with priority 1 in some order. The asm (priority 1) after the la forces the la before it. If the asm is scheduled early (say position 3), the la must be at position 2. Without the asm, the la can be anywhere.

So the question: why does the scheduler place the empty asm early? Because it has no dependencies and is at the front of the ready list? The ready list order is by LUID (or reverse). The asm's LUID is right after the la. Hmm.

Real C can't create an empty barrier. So this is a WALL.

Actually, hold on. Let me reconsider the problem statement: "levers of other kinds the def already had (pins under other causes) may stay, never added". The pin `register s32 a0 __asm__("$4")` stays. What if I can express the keepalive's effect using the EXISTING pin? No.

Wait, maybe the crack is to make the a1 computation a PINNED register? No, adding a pin is forbidden.

Hmm. Let me look at the walls.txt for a matching tag. "sched1-birth-order" is in walls.txt. This case is more like "the asm's placement forces the la early" — a keepalive-order wall. Let me check if there's a tag like "keepalive-order" or "asm-barrier". The walls.txt has "sched1-birth-order", "sched1-load-order", etc. I could use `sched1-birth-order` or create a new tag like `asm-barrier-order`.

Actually, the diff is ORDER of the la. The mechanism: the keepalive's empty asm is scheduled at a fixed early position (priority 1, no deps), forcing the la before it; without the asm, sched1 sinks the la to the call. This is a wall of the class "asm-barrier-order" or "sched1-order".

Let me do a few more tries to be thorough, then record the WALL with best=4.

Actually, let me reconsider: maybe I can make a1 be computed via the `a0` pin? Like `a1 = (s32)&D_8019DC34;` — the pin is on a0, not a1.

Hmm, what if I change the call to use `&D_8019DC34` directly (inline) and keep a1 for something else? No.

Let me try: what if the a1 assignment is placed right after the call to func_8012B1B4 but BEFORE `a0 = s0`? (v2 tested a1 before a0). Let me try a1 after a0 but with a real use: `a1 = (s32)&D_8019DC34; a2 = (s32)&D_8019DC3C;` both early — no.

Let me try one thing: make a1's value used in the `if (... == 1)` comparison? No.

OK, let me also try the possibility that the la can be hoisted by making a1 a `s32` that's compared/used in the store address offset. 

Actually — new idea: what if I write the store as `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;` and the SECOND store `((Unkstruct_800B5CB8 *)a0)->unk2 = s0;` and use a1 in between? Like `a1` is passed to the call. The call args are a0,a1,a2,a3. What if I compute the args in a different order? The target computes a1 early, a2 late, a3 last. Hmm.

Let me try: compute `a1` and immediately use it in a dummy comparison that folds? no.

I'll do a few more tries with different formulations, then record the WALL.

Let me try:
- v10: `a1 = (s32)&D_8019DC34;` moved to just before the call `if (func_8012D5E4(a0, (s32)&D_8019DC34, a2, a3)...)` — no, that removes a1.
- v11: `a1 = (s32)&D_8019DC34;` and use a1 as the `a3` value? no.

Let me instead test whether making a1 used in the `sh` store's address helps: `*(s16 *)(a0 + 2) = s0;` is the same as a0->unk2. No a1.

OK. I'll record the WALL. But the requirement is ≥30 tries. Let me do a quick batch of 10 more trivial variants (reorderings) to reach a reasonable count, but honestly they'll all be 4. Hmm, that's not productive.

Wait, let me reconsider the item's `kinds` field: it's `keepalive`. The score with the keepalive removed is 4 (ORDER). Maybe a PARTIAL? No, PARTIAL means keeping only some levers (pin) and scoring 0. Here, removing the keepalive gives 4, not 0. So it's a WALL (best = 4).

But wait — the `result` WALL means "best = lowest score of a lever-free body". Our best lever-free score is 4 (c1). So WALL with best=4.

Hmm, but let me double-check: maybe I can keep the pin and remove the keepalive and get a different score? The pin is already there in c1. So c1 is the lever-free body (keepalive gone, pin kept). Score 4.

Actually, hold on — the pin is a "lever of another kind" and may stay. So the lever-free (of keepalive) body is c1 = 4. WALL.

But let me reconsider whether the item is actually crackable with the pin REMOVED or changed... no, we must keep the pin (can't add/remove? Actually we could remove the pin too, but that's not required; the kinds only require keepalive gone).

Let me try removing the pin as well (to see if the ORDER improves)? That's allowed (removing a lever of another kind isn't "adding"). Let me test: c1 without the `register s32 a0 __asm__("$4");` line (make it a plain `s32 a0;`). Maybe the pin is causing the issue? Unlikely, but let me test.

Let me test c1 without the pin.

Actually, the pin is on a0 ($4). Without it, a0 might get a different register, changing lots. But let me test.

Let me also test: what if I add a real use of a1 by making the `v0` OR chain use a1's low bit? `v0 = (s32)&D_8019DAFC | 0x40000000 | 0x20000000;` — the target ORs 0x40000000 and 0x20000000. If I add `| (a1 & 0x0)`? folds.

OK, let me just test c1 without the pin and then record the WALL.

Actually, wait. Let me reconsider the moves.md entry "func_80184D28 | MATCH — keepalive replaced by return v0". And "func_801810F8 | MATCH: obase set right after pbase and used for the first load too". These are real-C uses. For our a1, the only real use is the call. Unless... 

OH. What if I make the a1 address used in the STORE `sw $2,20($4)` by changing the store's value to depend on a1? No.

What if I make a1 used in the `a2` computation: `a2 = (s32)&D_8019DC3C;` could be written as `a2 = a1 + 8;`? Then a2 depends on a1, forcing a1 early! But the code would be `addiu a2,a1,8` instead of `la a2,D_8019DC3C`. The target has `la $6,D_8019DC3C` (lui+addiu). So `a2 = a1 + 8` would emit `addiu a2,a1,8` — 1 instruction instead of 2. Different code. Unless the assembler... no.

Hmm, what if `a2 = (s32)&D_8019DC3C;` and `a1 = (s32)&D_8019DC34;` and the compiler CSEs? No.

OK, let me test the pin removal and then record the WALL.

Actually, let me reconsider one more: the target's la is `la $5,D_8019DC34`. What if I write `a1 = (s32)&D_8019DC34;` and then `a1 = a1;` — identity (deleted). Or `a1 += 0`? folds.

What if I use a1 in a REAL way that the target already has: the call `func_8012D5E4(a0, a1, a2, a3)`. The args are set up early. What if I write the call as `func_8012D5E4(a0, a1, a2, a3)` but ALSO use a1 in the condition `if (... == 1) D_80126B96 = s0;`? No.

Let me try the pin removal quickly, then record WALL.
