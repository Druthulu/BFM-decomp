---
ts: 2026-11-06T14:39:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iOiaWUrE9vofQ0QDeHLB
---
In orig's .rtl:
- insn 45: a0 = s0
- insn 47: a1 = &D_8019DC34 (the la)
- insn 49: ? (ref_count 16)
- insn 52: a0 = ... (reg/v a0)
- insn 55: reg 77
- insn 57: asm_operands (the keepalive!)

So the keepalive asm is insn 57. In the sched dump, insn 57 has ref_count 11. Interesting.

The sched order for orig: T-1=107, T-2=106, T-3=102, T-4=100, T-5=98, T-6=96, T-7=91, T-8=88, T-9=79, T-10=77, T-11=74, T-12=72, T-13=69, T-14=66, T-15=60, T-16=60?, T-17=57, T-18=55, T-19=52, T-20=49, T-21=47, T-22=45.

Wait, that's the orig dump from earlier: "T-18: 52 (1) 55 (7f000001), now 55 52; T-19: 52; T-20: 49; T-21: 45 47, now 47 45; T-22: 45". So the launch order (T-22..T-1) = 45, 47, 49, 52, 55, 57, 60, 63, 66, 69, 72, 74, 77, 79, 88, 91, 96, 98, 100, 102, 106, 107.

So in orig, the order is 45, 47, 49, 52, 55, 57 (asm), 60, ... So a1 (47) is second, asm (57) is sixth.

In c1 (no asm), the order was 45, 47, 49, 52, 58, 61, 64, 67, 70, 72, 75, 77, 86, 89, 94, 96, 98, 100, 104, 105. So a1 (47) is also second!

Wait, both have a1 second. But the final .s differs. So the difference must be in sched2 or reorg, not sched1.

Let me compare the sched2 dumps. In c1, the sched2 block 3 order (T-20..T-1) = 45,47,49,52,58,61,64,67,70,72,75,77,94,96,98,86,89,100,104,105. a1 (47) second.

Let me check orig's sched2 block 3 order. If orig's sched2 keeps a1 early and c1's doesn't... but c1's sched2 also has 47 second. Hmm.

Wait, maybe the .s order I'm reading is wrong. Let me carefully re-read c1.s. The block after the call:
```
	la	$5,D_8019DC18
	jal	func_8012B1B4
	move	$4,$16        <- delay slot of jal? 
	move	$4,$16        <- a0 = s0
	li	$2,-655360
	li	$16,4
	sw	$2,20($4)
	la	$2,D_8019DAFC
	li	$3,0x40000000
	or	$2,$2,$3
	li	$3,0x20000000
	or	$2,$2,$3
	la	$5,D_8019DC34   <- a1
```
Hmm, there are TWO `move $4,$16`: one in the jal delay slot and one after. So a0 = s0 is the second move. Then v0, s0, sw, la v0, or, or, la a1.

So a1 is at position ~8 after the call. The sched order says 45 (a0=s0), 47 (a1), 49, 52... So a1 should be right after a0. But it's not.

This means the sched2 dump's T-20..T-1 order is NOT the emission order. Let me figure out the correct interpretation.

The scheduler emits insns in the order they're "launched". If T-1 is the FIRST launch, then the order is 105,104,100,89,86,98,96,94,77,75,72,70,67,64,61,58,52,49,47,45. Then a1 (47) is 19th (near the end). And a0 (45) is last. But the .s has a0 first. So neither.

Unless the block's first insn in the RTL is 43 (something before a0). Hmm, the .s block after the call starts with `move $4,$16` (a0). But maybe insn 43 is the `la $5,D_8019DC18`/call stuff and the block actually starts earlier.

I'm clearly misunderstanding the dump. Let me just focus on the empirical result: the la sinks in c1 and stays early in orig. The keepalive asm forces it.

Let me check the sched2 dump of orig vs c1 more carefully by looking at the "ready list" around the la. Actually, let me try a totally different diagnostic: compile c1 with sched1 disabled and see if the la is early (then it's sched1) or late (then it's something else). But I can't change compiler flags easily... Actually, delever_search uses fixed flags.

Hmm. Let me look at the .dbr dump (delayed branch) — reorg might move the la. But the la isn't near a branch.

OK, let me take a decision. This item is a WALL of class "sched1-birth-order" or similar. But I haven't reached 30 tries. Let me do a few more targeted tries using the "real use" idea in a way that might actually work.

New idea: What if I use `a1` as the argument to the FIRST store's base in a way that's equivalent? No.

New idea: what if I compute `a1` from the pin `a0`? `a1 = (s32)&D_8019DC34;` — no.

New idea: maybe the la is early in the target because the ORIGINAL source used a1 in the `func_8012B1B4` call's arguments in some way? No, that call is before.

Wait — what if the original source had `a1` assigned BEFORE the func_8012B1B4 call and the call is `func_8012B1B4(s0, (void *)&D_8019DC18)`? Then a1 would be computed before the call. The target has it after. So no.

Hmm, let me look at the target .s again: after `jal func_8012B1B4` (with delay `move $4,$16`), the next insn is `move $4,$16` (a0=s0), then `la $5,D_8019DC34`. So a1 is right after a0. 

What if I make the source assign a1 in the same statement as a0? Like `a0 = s0, a1 = (s32)&D_8019DC34;`? Same RTL.

What if `a1 = (s32)&D_8019DC34;` is moved to the very start of the if-block (before the call)? Let me test: the la would be scheduled before the call? The call is a block boundary. Hmm, but sched1 might sink it into the post-call block. Let me test (v10).

Actually, v5 tested moving a1 before the call AND a0 after. It scored 4. Let me check v5's diff position — maybe the la moved but not correctly.

Let me test a cleaner v10: move ONLY `a1 = ...` to before the func_8012B1B4 call (keep a0 after).

Let me also try v11: put `a1 = (s32)&D_8019DC34;` immediately after the `if (unk94 == 15) {` line, before the call.

Let me test.

Actually, I realize I should check the moves.md for the EXACT function's original form. The keepalive comment says "NEEDED DIFFERS (P36 rung B t8_tus2)". So this was analyzed in P36. Maybe there's a note in P36 about this function. But I can't read logs/... Actually, .run/P36/ might have scratch. Let me grep .run/P36 for func_80183130? That's not a log dir (it's .run). Hmm, the brief says read only what it points at. Let me not go exploring .run/P36.

Let me try v10/v11 and a couple more, then decide.

Actually — wait. Let me reconsider the ORDER diff. It says "insert mine[22:22] target[22:24]" and "delete mine[31:33] target[33:33]". So in MINE, the la is at insns 31-32; in TARGET, at 22-23. Both have 51 insns. The la is a 2-insn sequence (lui+addiu).

What if I could make the la a SINGLE instruction? No, la is always 2.

Hmm, what if the la is computed via `lui`+`addiu` but the target's early position is due to a different reason.

Let me look at the sched2 dump for orig block 3 and c1 block 3, and specifically where insn 47 (a1) appears in the "ready list" launch order. In both, it seems to be launched at T-19 (second). So sched1/sched2 both put a1 second. But the final .s has it 8th. So REORG (the delayed-branch pass) must be moving it! Reorg fills delay slots and can reorder. Let me check the .dbr dump.

Actually, reorg doesn't reorder arbitrary insns; it fills delay slots. The la isn't a delay-slot fill.

Hmm, wait. Maybe the final .s order IS 45,47,... and I'm misreading which insn is a1. Let me re-examine: maybe `la $5,D_8019DC18` (the func_8012B1B4 arg) is insn 45/47? No, that's before the call.

Let me just dump c1's .s with line numbers around the function and carefully map. Actually, let me use objdump on the candidate object to see the actual instruction addresses. Or use the --keep object.

Hmm, this is taking very long. Let me step back and consider: the score is 4 and the ONLY difference is the la's position. This is a classic sched-order wall. Given the time, let me record it as a WALL with the evidence, noting the mechanism (keepalive's empty asm occupies a fixed early slot forcing the a1 la there; without it sched sinks the la to the call).

But the requirement of ≥30 tries for a WALL... Let me do a batch of more tries to accumulate. Actually, maybe I should reconsider whether the "la sinking" is really unfixable. Let me look at the sched1 priority: the la has priority 1. The asm also priority 1. The scheduler's order among priority-1 insns is by the ready-list order (which is LUID-based). The asm's LUID is after the la's. In the backward scan, the ready list is built in reverse. Hmm.

Let me try a DIFFERENT real-C use of a1 that's genuinely early and produces the same code: what if the `v0 = 0xFFF60000;` statement is rewritten as `v0 = 0xFFF60000; a1 = (s32)&D_8019DC34;` — reorder so a1 is after v0. Tested v6, still 4.

What if the a1 assignment is combined with the a0 assignment via a struct? No.

Let me try the "used for the first load" idea literally: make a1 used by the first store. The first store is `sw $2,20($4)` = a0->unk14 = v0. What if I write `((Unkstruct_800B5CB8 *)a0)->unk14 = v0;` as `*(s32 *)(a1 + ((s32)a0 - (s32)a1) + 20) = v0;`? That's absurd and would generate extra code.

OK. Let me accept the WALL. But first, let me try 5-6 more quick variants to be thorough (reordering the OR chain, moving a2, etc.), and count the tries.

Actually, let me reconsider the mechanism from the sched1 dump ONE more time. In orig, the asm is insn 57 with ref_count 11. Wait, ref_count 11 for an empty asm? That's the "ref_count" used by the scheduler = the number of references to the insn's result? Or the priority contribution. Hmm.

The asm at insn 57: its input is a1 (reg 5). The asm's scheduling priority... In sched1, an insn's priority = length of the longest dependency chain from it to the end of the block. The asm has priority 1. But it's scheduled at T-17 (6th from first). Why? Because the scheduler's ready list order.

Let me look at the ready list around T-17 in orig: "T-18: 52 (1) 55 (7f000001), now 55 52; T-19: 52; T-20: 49; T-21: 45 47, now 47 45; T-22: 45". Hmm, this is the order from T-22 to T-1: 45, 47, 49, 52, 55, 57... wait, where's 57? Let me look: "T-17: 57 (1), now 57". So T-17 launches 57. And T-18 launches 55. So the order is ... 55 (T-18), 57 (T-17), ... So 57 (asm) is after 55.

OK whatever. The scheduler places the asm at a fixed position based on its dependencies. The asm depends on a1 (insn 47). Without the asm, the la has no early consumer.

I'm confident: real C can't replicate an empty asm's placement. WALL.

But let me do due diligence: maybe the a1 la can be kept early by making a1 used in an EARLIER instruction that the target also has. The target's insn 49 (ref_count 16) is likely the `sw $2,20($4)` store or the `move $4,$16`. If a1 were used there... no.

Hmm, actually — what about making a1 the destination of a store that's already there? No.

Let me try ONE creative thing: use a1 in the `v0 = (s32)&D_8019DAFC;` computation by writing the address as an expression involving a1 that the compiler folds back to the same la. E.g., `v0 = (s32)&D_8019DC34 - 0x138;`. That would be `lui v0; addiu v0,v0,-0x138` — same as la D_8019DAFC! And it uses a1? No, it uses a constant.

But if I write `v0 = a1 - 0x138;` where a1 = &D_8019DC34, then v0 = &D_8019DAFC. This makes v0 depend on a1, forcing a1 to be computed first! And the code: `addiu v0,a1,-0x138` (1 instruction) instead of `la v0,D_8019DAFC` (2 instructions: lui+addiu). So the instruction count changes (51 -> 50). Bad.

Unless... the target has `la $2,D_8019DAFC` = lui+addiu. If I use `v0 = a1 - 0x138`, it'd be `addiu $2,$5,-312` (1 insn). Different. Bad.

Hmm.

What if the target's v0 and a1 addresses were related such that the compiler would emit la? No.

OK, let me record the WALL. But let me first reach a reasonable number of tries and note the evidence. Let me do a batch of 10 more variants (reorderings that are semantically identical) just to satisfy the "attempt" criterion? That feels wasteful and dishonest. The instruction says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". I've spent ~25 min and done ~14 tries. If I record a WALL with fewer than 30 tries, it's "not an attempt" — meaning the expert might reject it. 

Let me think about whether there's a genuinely different lever I haven't tried. 

The ORDER diff is the la. What if the la is being moved by cse? cse might be merging the la with something. Let me check: cse2 (before flow) — does it CSE the `&D_8019DC34`? It's a unique address. Hmm.

What if I use the do-while(0) to split the cse EBB BEFORE the la so cse can't sink it? But cse doesn't sink.

Let me look at the .cse2 dump for c1 to see the insn order of the la. If cse2 moved it, that's the lever.

Actually, let me compare the .cse2 dumps of orig and c1: the la's position. Let me grep.

Hmm, I keep going deeper. Let me just look at whether the la position differs in .cse2 (pre-flow, pre-sched). If it does, cse is the culprit and a do-while(0) could fix it. If not, it's sched1/sched2.

Let me check c1's .cse2 and orig's .cse2 for the la (reg 5 set).
