---
ts: 2026-11-07T00:20:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vXnGC3i8wL7MyL9NpWbA
---
Oops — I forgot the `cd /home/musashi/bfm-decomp;` prefix? No, I did include it. Good.

Now the moves line for item 4, then the log.

Actually, let me reconsider before finalizing all these walls. All 4 items are WALLs. That's a poor outcome for a "crack shard". Let me take a fresh look at whether I'm missing something.

Hmm. Let me reconsider item 1 (best 14, only the reg swap between base and mode). That's the closest. If I could flip base/mode...

The priorities: base 1518 (refs 8, live 158), mode 1204 (refs 5, live 83).

To flip: mode refs 7 (2*7/83 = 1686 > 1518) or mode live ≤65, or base refs ≤7.

Adding 2 refs to mode = 2 extra instructions. Unless...

WAIT. What about `allocno_size`? pri *= allocno_size. If MODE had size 2... it's SImode. But what if I declare mode as a `long long`? No.

Hmm, what if `mode` is used in a 64-bit context? No.

Hmm, what about `allocno_n_refs` — the ref count. What if `mode` appears twice in ONE insn? E.g., `mode = mode + mode`? That's 2 refs in one insn. The allocno_n_refs counts per-insn occurrences? Let me check: global.c's `mark_reg_store`/`mark_reg_live_nc` increment `allocno_n_refs` by... Let me check `global_conflicts`.

In global.c, `record_one_conflict` and `mark_reg_store`:
```
static void
mark_reg_store (reg, setter)
{
  if (regno >= FIRST_PSEUDO_REGISTER)
    regs_set[(regno - FIRST_PSEUDO_REGISTER) * 2] = setter;
  ...
}
```
Hmm, and n_refs comes from `reg_n_refs` (flow). `reg_n_refs` is incremented in flow.c per reference occurrence.

`mode + mode` would be 2 refs in one insn. If the insn is `addu mode, mode, mode`... that's a real instruction (changes mode). Hmm, but `mode = mode + mode` is wrong semantically.

What about `mode == 0 && mode >= 0`? 2 refs in one expression, but combine folds.

Hmm, what about a comparison that uses mode twice in one insn? Like `if (mode == 0 && mode == 0)` folds.

Hmm.

What about `switch (mode)`? The target doesn't have it.

OK. What about reducing base's refs to 7? I tried respelling a base use with the symbol, which changed the code (cse doesn't merge across blocks).

Hmm, what if I respell a base use in the SAME block as base's set? base is set in block 0. Are there base uses in block 0? Looking at the C: base is used in the ifs, which are in later blocks. So no.

Hmm.

What if I move `base = D_800AF630;` into the block where a use is? That changes the code.

Hmm.

OK, one more idea for item 1: what if I make `mode` a `u32` and compare `mode >= 0`? That's always true for u32 → the compiler would optimize the condition away. No.

What if mode is `s32` but I use it as `(s32)mode >= 0`? same.

Alright. I'm fairly confident these are walls.

Hmm, wait. Let me reconsider item 1's approach entirely. Maybe the correct C for the target doesn't have `base` as a single variable used 7 times. What if the original source used a struct pointer `Unkstruct_80010178 *base` and accessed fields via a *different* pointer variable per use? No.

Hmm, what if the target's `base` is actually `D_800AF630` accessed via a macro that expands to `(Unkstruct_80010178 *)D_800AF630` each time, and the compiler CSEs the address into one register? That would give base refs 7 (each use is a fresh symbol_ref, cse merges them into one reg). Then the allocno would be the *merged* pseudo with 7 refs? Hmm, if each use is a fresh pseudo, cse replaces them with the canonical → the canonical has many refs.

Actually, that's exactly what would happen: `((Unkstruct *)D_800AF630)->unkA3D8` written out 7 times. cse would merge the address computations. The canonical pseudo would have 7 refs (one per use) + the sets. Hmm, same count.

But the *set* count: each occurrence has its own set (7 sets), but cse deletes 6. The surviving canonical has 1 set + 7 uses = 8 refs. Same.

Hmm.

OK. What if the original had `base` as a *parameter*? No.

Let me now also reconsider: maybe the score 14 residual for item 1 isn't purely the swap. It's `s3->s4 x10, s4->s3 x5`. That's 15 register mentions. A swap.

Hmm, one thing I could try: make `base` a `u8 *` but accessed via a `struct` pointer so it conflicts differently... no.

I'll accept the walls. But let me reconsider the whole task: the brief says "For each item ... write a lever-free body of func ... that scores 0" — the goal is to crack. If I wall all four, that's a valid (if disappointing) outcome, provided I have the evidence.

Hmm, but let me sanity-check one thing: maybe I'm missing an obvious lever. Let me re-read the brief: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

OK.

Hmm, let me reconsider item 2: nolau (pins kept) scored 2! That's very close. If I could get the launder gone with the pins kept → PARTIAL:pin. The residual was a branch target + nop vs slt at insns 29-30.

Let me revisit that! nolau score 2, only 1 diff. If a small C change fixes it, that's a PARTIAL:pin crack!

The diff:
```
replace mine[29:31] target[29:31]
  29  bgez v1,5afc <+0x84>  | bgez v1,5af8 <+0x80>
  30  slt v0,s1,v1         | nop
```
So mine has `slt v0,s1,v1` in the delay slot, target has `nop` and the branch target differs by 4 (0x84 vs 0x80).

This is the first max comparison: `if (iVar5 < iVar4) iVar5 = iVar4;` after the launder. In the target, the `slt` is NOT in the delay slot; in mine it is.

Hmm. With the launder, the first max's slt placement differs. The launder adds an insn, pushing the slt out of the delay slot.

So the launder's role: it inserts an insn between the abs and the max, so the slt can't fill the delay slot.

Lever-free: can I add a real statement between the abs and the max that produces the same code? The target has `nop` in the delay slot, meaning there's an insn slot. Hmm.

Let me look at the target around there:
```
5aec: bgez v1,5af8
5af0: nop
5af4: negu v1,v1
5af8: slt v0,s1,v1
5afc: beqz v0,5b08
5b00: nop
5b04: move s1,v1
```
And mine (nolau):
```
5aec?: bgez v1,5afc
      slt v0,s1,v1
      negu v1,v1 ...
```
Hmm, let me get the exact diff. The diff says mine[29:31] = `bgez v1, 5afc` + `slt v0,s1,v1`; target = `bgez v1, 5af8` + `nop`.

So in mine, the `slt` (the max comparison) is in the delay slot of the bgez (the iVar4 abs test), and the branch jumps to 5afc (past the negu). In the target, the bgez jumps to 5af8 and the delay slot is nop, then slt at 5af8.

So in the target, the slt is AFTER the branch target; in mine, it's in the delay slot (executed unconditionally, which is fine because the negu is skipped when positive).

Hmm, actually in mine: `bgez v1, 5afc; slt v0,s1,v1` — if v1>=0, jump to 5afc (skip negu), and the slt executes in the delay slot regardless. Then at 5afc: beqz v0,... So the slt is done before the beqz. That's correct.

In the target: `bgez v1, 5af8; nop; negu v1,v1; [5af8] slt v0,s1,v1`. So the slt is after the negu.

The difference is reorg's delay-slot fill: it filled the bgez delay slot with the slt in mine, but not in the target. The launder's extra insn changes the scheduling.

So lever-free we need the slt not to be in the delay slot. Hmm.

What C change could do that? The order of statements: `if (iVar4 < 0) iVar4 = -iVar4; if (iVar5 < iVar4) iVar5 = iVar4;`. If I reorder or restructure...

Hmm, this is a 1-insn scheduling difference. It's the kind of thing a small C change could fix.

Since nolau is score 2 (pins kept), if I fix this, I get PARTIAL:pin (score 0 with only the pin). That would be a crack!

Let me spend a few minutes on this. The nolau body keeps the pins (param_3, param_4, t) and removes the launder.

Let me try variants of the first max block in nolau:
1. `if (iVar5 < iVar4) { iVar5 = iVar4; }` (current)
2. Reorder: `if (iVar4 > iVar5) { iVar5 = iVar4; }` — same RTL probably.
3. Use a temp: `s32 m = iVar4; if (iVar5 < m) iVar5 = m;`
4. Add a statement between.
5. Different abs formulation.

Actually, the issue is the slt placement. Let me think: reorg fills delay slots from the branch target/fall-through. The bgez's delay slot is filled with the next insn if safe.

In the target, the delay slot is `nop` and the slt is at the target. In mine, the slt is in the delay slot.

Hmm, why would reorg not fill it in the target? Because in the target's RTL, the insn after the bgez is the negu (in the fall-through) and the slt is at the join. Hmm, both have the same structure.

The difference must be the *order* of the RTL insns. With the launder, there's an extra insn (the asm) between the negu and the slt. So the RTL is: bgez, negu, [asm], slt. The delay slot filler picks... hmm.

In mine (nolau): bgez, negu, slt. Reorg puts slt in the delay slot.

To prevent that lever-free, I need an insn between the negu and the slt that can't be moved. But any such insn would appear in the code (the target has only a nop).

Hmm, wait — the target has `nop` in the delay slot. A nop is a real insn in the output. So the target's code has: bgez; nop; negu; slt. Mine has: bgez; slt; negu? Hmm no, mine's diff shows mine[29]=bgez, mine[30]=slt. And the target[29]=bgez, target[30]=nop.

So both have the same number of insns (117). Mine: bgez, slt, negu, ... Target: bgez, nop, negu, slt. Both 4 insns? Let me see: mine has bgez+slt (2), then where's the negu? The diff only shows 29-31. Let me get the full context.

Hmm, actually the diff says "replace mine[29:31] target[29:31]" — mine[29:30] = bgez+slt, target[29:30] = bgez+nop. Then they re-align, meaning mine[31] = target[31]. So mine: [29] bgez, [30] slt, [31] ... and target: [29] bgez, [30] nop, [31] ...

Hmm, that means mine's [31] equals target's [31]. If mine's [30] is slt and target's [30] is nop, then mine's [31] = target's [31] = negu? So mine: bgez, slt, negu... but then the slt is in the delay slot and the negu after — that's wrong semantically (the slt would use the un-negated v1).

Hmm, wait. Let me re-read: the bgez at [29] branches to 5afc (mine) / 5af8 (target). In mine, the delay slot [30] = slt. Then [31] = negu? That would mean if v1<0, negu executes after the slt — but the slt in the delay slot executed before. Hmm, that's still semantically OK if the slt is not in the branch's delay... 

Ugh, I'm confusing myself. Let me just get the full diff with more context.

Let me run dt.sh with more lines.
