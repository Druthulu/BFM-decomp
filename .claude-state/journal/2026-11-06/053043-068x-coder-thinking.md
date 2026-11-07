---
ts: 2026-11-06T12:30:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mjEFpEWAguXlQR5LDfHH
---
The diff: two stack address pseudos swap registers: `addiu s6,sp,292`/`addiu s5,sp,296` vs target `s5,292`/`s6,296`. So the address &gsz0 (sp+292?) and &gsz1 (sp+296) get swapped regs.

These are the addresses of gsz0 (sp+292) and gsz1 (sp+296). Their allocation is decided by allocno order (a tie).

Real-C knobs: declaration order of gsz0/gsz1 (line 17: `long gotz, gflag, gopz, gsz0, gsz1, gsz2, gsz3;`). Swapping gsz0/gsz1 in the declaration would swap their stack offsets too (292/296) — that would change the whole frame layout (bad, since offsets appear everywhere).

Hmm. But the stack slots are assigned in declaration order, so swapping them changes the offsets. Not good.

Alternative: the addresses are `&gsz0`, `&gsz1` used in gte_stsz3(&gsz0,&gsz1,&gsz2). The pseudo priority = refs/live length. Both are used in the same places.

What changes their allocno order? The allocno number = pseudo number order. Pseudo numbers are assigned in the order the variables are first referenced in the function body... gsz0 is referenced at line 168 (gte_stsz3) first, then gsz1. Their allocnos: for stack slots, the address pseudo is created at each use? Actually &gsz0 is a constant (sp+292) — a "constant address" pseudo, rematerializable.

In global.c, allocnos are numbered by pseudo number. The address pseudos are created in the order the expressions are expanded. So swapping the ARGUMENT order in the gte_stsz3 call (`gte_stsz3(&gsz1, &gsz0, ...)`) — no, that would break semantics.

Hmm. What about the ORDER of the two branches (`if (gsz0 > gsz1) za = gsz0; else za = gsz1;`)? Swapping the if/else would change the comparison and the code. No.

So the barrier at 6 seems stuck too, though it's small.

Hmm wait — maybe the priority difference is tiny (561 vs 560, per the header) and one extra insn flips it. What if I add a real (needed) insn elsewhere... no, we can't add insns.

What if a real-C move changes the live length by 1: e.g. moving a statement into/out of the range of the address pseudo's live range. The address pseudos live from their def (66/67) to their last use (586). That's most of the function — any statement reordering inside that range doesn't change the length.

Unless a use moves to the very end. Hmm.

OK: item 3 is a WALL (needs 30 tries). Let me generate 26 more cheap tries (statement reorders, declaration orders, temp changes) and then record. Actually — given the barrier is at 6 and the keepalives at 53/15/15, the total lever-free is 71.

Let me do a batch of ~26 tries efficiently. But careful: I shouldn't waste too much time. Each score is 1 s; a batch of 26 in one command ~30 s. But generating 26 meaningful variants takes thought. Let me do a mixed batch:

Group A (barrier region, on d201-based? no, lever-free base v0):
Hmm — for the WALL the best is the lever-free body. Let me focus variants on the biggest cluster (a2/a3 swap, from the keepalive at 201) — the header says the keepalive extends my's live range to flip mny/my priority (22115 vs 22072, 43 points).

Real C to flip that: change the refs of `my` or `mny`. Let me look at the region around `my`/`mny`.

Let me grep.
