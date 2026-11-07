---
ts: 2026-11-06T10:47:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_c2bko0ud2kfVXHWR2EPD
---
Now the only diff: the load is at position 30 in mine vs 28 in target. Mine: lui, addiu, lw, sw, ori, sw? Target: lw, lui, addiu, sw, ori, sw.

So the load needs to be first (before the address computation). sched1 kept the source order (a computed first, then the load). So put the load first in the source: `do { t = ...; a = ...; } while(0)` was v_addr (regs swapped). Hmm, so source order t-first gives regs swapped; a-first gives the load late.

What about splitting: `do { t = unkC4; } while(0); a = (s32)&D_801907C4;` then `unk58 = a; unkC4 = t|2;`? Then the load is in block1, a in block2, store in block2. That's similar to v_dw with the address hoisted out — the store might sink again. Hmm, but the address is now a separate statement.

Wait, in v_addr the do-while wraps both. The schedule put the address first because it's first in source. What if I put the load first in source AND keep the register allocation right? The regs swapped because a got v0. Maybe the decl order matters: in v_addr3, a is declared... let me look: v_addr has `s32 t;` then `s32 a;`. v_addr3 is derived from v_addr with the source order swapped, decl order still t then a. It gave a→? and t→? — no pairs reported, so t is v0 and a v1! Wait, the diff shows `lw v0,196` in mine (t in v0) and the store `sw v1,88`? The diff only shows the load position, so the rest matches target: lui v1, addiu v1, sw v1, ori v0, sw v0. So in v_addr3, t=v0 and a=v1 — correct regs!

So v_addr3 has correct regs and only the load position wrong (source order: a first, t second; sched1 kept it).

Now: I need the load to be scheduled first even though `a` is computed first in source. In the target, the load is first. sched1 ordered by source. If I put the load first in source (v_addr), the regs swapped.

Hmm. What determines the reg swap in v_addr? There, t is first in source and a second, and a got v0. So allocation isn't source-order.

Wait, maybe in v_addr the issue is different: both in the same block, t and a. Let me recheck v_addr's diff: mine had `lw v1,196` (t→v1), `lui v0/addiu v0` (a→v0). So a got v0.

In v_addr3 (a first, t second): t→v0, a→v1. So the SECOND statement's pseudo got v0? That's odd but consistent: in v_addr, t first, a second → a (second) got v0. In v_addr3, a first, t second → t (second) got v0.

So local-alloc's allocation order gives v0 to the last-defined pseudo? Probably because allocno priority (live length): the second one's live range starts later and ends at the same point → shorter? Hmm, priority = refs * live length; shorter live length → lower priority → allocated later → gets the lower reg? No.

Whatever — empirically, the second-defined gets v0.

Target: t (load, first) gets v0 and a (second) gets v1. So in the target, the FIRST-defined got v0.

Hmm, but the target's block structure differs (t is in a different block from a? no—if the barrier splits, t is in block B with a...).

Hmm hold on: with the barrier, the block is one basic block containing both t and a. And t (first) got v0.

So target: first → v0. My v_addr: first (t) → v1. Contradiction. Unless the barrier splits the *basic block* for local-alloc too, making t and a in different blocks: t in block B, a in block C? But the barrier is before the load, so both are after it. No.

Wait, maybe the barrier does split the basic block in gcc 2.7.2 because an asm volatile is a `CALL_INSN`? No, it's an INSN with ASM_OPERANDS and volatile. In gcc, `basic_block` splits at jumps/labels; asm volatile with memory clobber might be treated as a `BLOCK_END`? There's `flow.c` / `find_basic_blocks` which splits at `code == JUMP_INSN`, `CALL_INSN`? Actually in gcc 2.7.2, `find_basic_blocks` splits at labels, jumps, and also after a call? Let me check: a call ends a basic block in gcc! Yes — in gcc's CFG, a CALL_INSN ends a basic block (since the call can have side effects and is a "block boundary" for optimization purposes). Hmm, actually in modern gcc calls don't end BBs. In gcc 2.7.2's find_basic_blocks, I recall it splits on `GET_CODE(insn) == CALL_INSN`? Let me grep.

This matters: if calls end basic blocks, then the else-block starts after the last call (func_8012A828). Then the block contains the stores and the load etc.

Let me look at find_basic_blocks in flow.c.
