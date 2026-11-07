---
ts: 2026-11-06T11:55:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MIz798Oos7udKIhh2IfI
---
Interesting — w6's cse dump has many small blocks (the do-while created loop notes/branches!). "Processing block from 2 to 63" etc. The do-while created actual control flow? A do-while(0) shouldn't create a branch... unless gcc keeps the loop structure.

Hmm, "Processing block from 2 to 63, 11 sets" then "from 64 to 14, 2 sets" — the block boundaries are at insn 63, 14, etc. These are loop-related.

Wait, w6 wrapped both the store and load in one do-while. The cse processed block 2→63 (11 sets). Then 64→14... The function has the if branch at the end, so blocks exist anyway.

Let me look at whether the store and load are in the same block. The store/load are around insn 30-34. Block "2 to 63" covers them. So same block → forwarding.

Hmm, so the do-while didn't split between the store and load.

Wait, the block boundaries here (63, 14, 16, 22, 25, 28, 31, 34, 37, 40, 66, 69, 70, 73) — these are unusual. It seems the do-while created a LOOP with many blocks? That's a lot of blocks for a simple function. Maybe the do-while(0) became a real loop that gcc's loop optimizer split.

Hmm, but the final asm was only 37 insns. Let me check w6's asm — score 1, so it's the same as w1 essentially.

OK, the EBB split isn't happening between the store and load.

Let me try a different construct: **`if (0) { } else { store; }`** no.

Let me look at how cse determines block boundaries: `cse_basic_block` is called for each EBB; the EBB ends at a CODE_LABEL that is a branch target (LABEL_NUSES > 0) or a NOTE_INSN_LOOP_BEG. A do-while creates a LOOP_BEG note. If the LOOP_BEG note is placed at the top of the loop body (before the store), then the store and load are both inside the loop body → same block.

For C0535's use, the do-while was around two copies and the SPLIT was between the copies and the following insns (the loop end / following code). So the loop boundary separates the body from what follows.

In our case, to separate the store from the load, I'd put the store in a do-while and the load AFTER the do-while. That's w2 (do-while around the store only). Let me check w2's cse blocks. If the LOOP_END note / following boundary is between the store and the load, then cse wouldn't forward. But w2 scored 1 (forwarded). So the boundary didn't separate them.

Maybe because do-while(0) is optimized away entirely (the loop note deleted). In C0535's case it worked because of a specific interaction.

Let me check w2's cse dump to see if the block boundary is between the store and load.

Time: 04:56. Let me not spend too long. Let me run one dump for w2 and check.

Actually, let me try a **real loop that runs once** and that loop.c might keep:
```
do { *(u8*)(arg0+6) = (u8)temp_v0; } while (temp_a0 == 0x100);
```
No, changes semantics (temp_a0 is 0..255, so the condition is always false → runs once!). temp_a0 is a u8, so `temp_a0 == 0x100` is always false. The compiler knows temp_a0's range (0..255) and may fold the condition. But gcc 2.7.2 might not know the range → it would emit a real loop! That would add a branch (bne) — changing the code. No good.

Hmm.

Let me try the label approach with a label that IS a branch target and a branch that doesn't add instructions... impossible.

OK, I think this is a WALL: `cse-store-forward`. The evidence is clear: cse1 records the sb's QI subreg value and forwards it into the reload; only a memory clobber (barrier/volatile) invalidates the entry.

But wait — the target's reload is `lbu v0,6(s0)` — maybe the original compiler didn't forward because the ORIGINAL source had the store and load in **different extended basic blocks** due to the surrounding `if`? No, the if is later.

Let me reconsider the original source once more. What if the original is:
```
temp_a0 = *(u8 *)(arg0 + 5);
temp_v0 = *(u8 *)(arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)(arg0 + 6) = temp_v0;
...
temp_v0 = *(u8 *)(arg0 + 6);
```
Hmm same.

Actually, maybe the original had the reload BEFORE the store in source order, and the STORE was after — but then sched1 would keep the load before the store (a load followed by a store to the same address: the load's value is needed, and the store depends on it? no). Let me test: what if source order is:
```
temp_v0 = *(u8*)(arg0+6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
temp_v0 = *(u8*)(arg0+6);      // reload FIRST
*(u8*)(arg0+6) = (u8)(temp_v0); // store after
```
Then temp_v0 after the reload is the old byte value, and the store stores the old value — semantics differ! Target stores the subtraction result. So no.

Hmm, unless the reload writes a DIFFERENT variable:
```
temp_v0 = *(u8*)(arg0+6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
temp_a1 = *(u8*)(arg0+6);       // reload into temp_a1
*(u8*)(arg0+6) = (u8)temp_v0;   // store
```
Then the asm would be: lbu (reload), sb (store). But target is sb then lbu. And temp_a1 is used for the sh stores, not temp_v0. Target uses v0 for the sh stores after the lbu. So the reload is into the same reg v0.

So no.

OK, let me also consider: maybe the original used a **`u8` variable for the subtraction result** and the store/reload logic differs. Let me test a few type variants in a batch.

Let me generate a batch of ~15 variants (legit) and score. Then decide WALL.

Variants:
1. temp_v0 as u8 (with the reload into a separate s32)
2. temp_v1 as s32 instead of s16
3. reload into a separate u8 var, stored into s16s
4. store via struct field u8 (done w9)
5. load via struct field (done w10)
6. both struct fields
7. do-while around temp_v1+store
8. do-while around the whole prefix
9. separate variable for the store value (u8 sv) (done w5)
10. pointer reuse: reuse arg0 pointer variable
11. declare temp_a0 after temp_v0
12. reorder the sh stores
13. `temp_v0 = *(u8*)(arg0+6);` as `temp_v0 = ((u8*)arg0)[6];`
14. use `u8 *p = (u8*)arg0;` for everything
15. compound assignment for the store with temp_v0 kept

Let me batch these. But honestly none will block cse.

Actually, let me reconsider #15: 
```
temp_v0 = *(u8 *)((u8 *)arg0 + 6) - temp_a0;
temp_v1 = -(temp_v0 & 0xFF);
*(u8 *)((u8 *)arg0 + 6) = *(u8 *)((u8 *)arg0 + 6) - temp_a0;  // recompute, cse makes it v0
temp_v0 = *(u8 *)((u8 *)arg0 + 6);
```
The store src is the subtraction expression. cse1: is `(minus (mem) (reg))` in the table? The initial load at insn ~16 computes `temp_v0 = mem - temp_a0`; cse inserts `reg temp_v0 = (minus (mem) (reg))`? No, cse inserts the DEST reg with the src expression. So the expression `(minus (mem) (reg))` IS in the table (as the value of temp_v0). Then the store's src `(minus (mem) (reg))` is looked up → found → src_elt != 0 → store recorded → forwarding!

Unless cse can't equate because the store's mem address computation differs... same.

Hmm.

OK, let me look at this from a completely different angle: maybe the target's lbu is NOT from the same source. Maybe the original function read the byte into a variable that is NOT temp_v0, and the compiler allocated it to v0 because temp_v0 was dead. Look at the target:
- After the lbu, v0 is used for the 4 sh stores (D_801269xx). 
- temp_v1 (v1) is used for 2 sh stores.
So the reloaded value goes to the 4 sh stores. If the reload were into a separate variable, the compiler could still put it in v0. And cse forwarding would still happen (the load is from the same address).

Right, no difference.

I'm now fairly confident this is the `cse-store-forward` WALL. Let me do the remaining tries to hit 30 and 20 min, then record.

Let me batch-generate 18 more variants quickly and score them all. Then record WALL.

Let me write gen.py for item 2 with variants.

Actually, simpler: use sed to create variants from w1. Let me create ~18 files with small variations. I'll write a Python generator for clarity.

Time is 04:57. Need until ~05:07 for 20 min. Let me generate and score now, then do a couple more checks, and record around 05:07.

Let me write the generator.
