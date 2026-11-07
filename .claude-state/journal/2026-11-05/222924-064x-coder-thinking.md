---
ts: 2026-11-06T05:29:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Gd9c2dyhwQcM5WUkCJ4B
---
In the orig (pinned), reg73 (iVar1) is absent from the local qty list — because it's a hard register ($3). reg74 (iVar2): 8 refs/10 insns → pri = 3*8*4/10 = 9.6. reg75 (tmp): 22/18 → 4*22*4/18 = 19.5.

With $3 reserved by the pin, the order: tmp → $2, iVar2 → $4 (since $3 is taken by the hard reg; local-alloc's find_free_reg skips hard regs in use). Yes! That's how the target gets iVar2 in a0.

So lever-free we need iVar1 to take $3. iVar1's pri in orig is unknown (hard reg). In the lever-free version, iVar1 (reg73) is 8 refs/18 insns = 5.33.

Hmm, in the orig, reg73 hard reg has 8 refs/18? Let me check the rtl dump.

Actually the key insight: with the pin, iVar2's pri 9.6 doesn't matter because $3 is reserved. Lever-free, iVar2's pri (8-12) beats iVar1's 5.33.

So we need to lower iVar2's priority below 5.33, or raise iVar1's.

iVar2: 8 refs / 10 insns = 9.6 in orig. To get below 5.33 with 8 refs: live > 18. With 6 refs: live > 9. With 4 refs: live > 6.

Hmm, what if iVar2 is used more sparsely (longer live range)? Its live range starts at the sign-extend and ends at the last test. Could we extend it? E.g., if iVar2 were used after the arms (dead but not eliminated)...

Alternatively raise iVar1: 8 refs/18 = 5.33. Need > iVar2. If iVar2 is 9.6, iVar1 needs 14.6 → e.g. 16 refs/18 (4*16*4/18=14.2, close) or 20 refs.

Hmm. What if iVar1's live range is shorter? It spans the whole first if (from 21 to ~61). Could we split iVar1 into two variables (one for the first block, one reloaded)? The source already reloads iVar1 after the first if. The first iVar1 lives from the unk20 load to the last store in the arms.

What if we make the arms use `a0->unk20` directly instead of iVar1? E.g., `((Unkstruct_800B5CB8 *)*(s32 *)(a0 + 0x20))->unk10 = ...` in the arms. Then iVar1's live range shrinks to just the load and the CAST_SIGN. But that changes the asm (extra lw in each arm) — the target has `sh v0,16(v1)` using v1 directly. So no.

OK, what about the reverse: make iVar2's live range longer by moving its computation earlier? It's already at the start.

Hmm, what about making iVar2's n_refs smaller? The refs: the sign-extend chain (3 insns: lh, sll, sra) plus uses. If iVar2 were loaded directly as `lh` into an SI reg without the sll/sra... The `lh` gives a sign-extended value in the register, but gcc's RTL for `CAST_SIGN(s16, iVar1, 0x10)` creates HI reg then sign_extend (sll/sra). Then combine folds it? In the final asm: `lh a0,16(v1)` directly — combine folded the sll/sra into the lh (since lh sign-extends). 

So reg74 (iVar2) refs include the sign-extend. 

What if we declare iVar2 as `s16` (b1)? Then `iVar2 = *(s16*)...` gives an HImode reg, and the sign-extend happens at each use. b1 scored 8 (merged). Hmm.

OK, let me step back and consider the budget. I've spent maybe 20 minutes on item 2 (started ~22:23, now ~22:45?). Let me check the time. If I'm at 20+ min with ~15 tries, I can try more or declare WALL after 30 tries. But there's a cleverer possibility: maybe I can find a spelling where iVar2 is in a0 and iVar1 in v1 by making the *qty sizes* differ. 

Note the priority formula includes qty_size! For HImode qtys, size = 2 (bytes), halving priority. If iVar2 is HImode (s16), its qty size is 2 → pri halves. But then the sign-extend at uses...

b1 (s16 iVar2): let me check its lreg qtys. If b1's iVar2 is HImode and the copy merged... b1's asm was identical to n1's (merged). Hmm, so cse merged even with s16.

Let me think about combining: s16 iVar2 + the (s16) cast copy. 

Actually, wait. What about `tmp = iVar2;` where tmp is declared as `s16` (b3)? Then tmp is HImode, pri halved... but the arms do `tmp += 0x80` in HImode → extra instructions? b3 scored 8 (same as n1), so probably merged.

Hmm.

Let me try another angle: what if we make iVar1's qty size larger or refs higher by *declaring iVar1 as a pointer type* (void*)? Same size.

What if iVar1 is used in the CAST_SIGN as a pointer — same.

Let me look at the actual qty numbers again for a1: reg73 (iVar1) 8 refs/18 insns. To beat reg74 (8/8 = 12), we need iVar1's live ≤ 12 insns with 8 refs (pri 8) — still less than 12. Or 16 refs/18 (14.2).

Hmm, what if we could reduce iVar2's refs to 4 and keep live 8: 2*4*4/8 = 4 < 5.33. ✓. How? iVar2's refs = def + uses. In a1: 8 refs. What are they? Let me look at a1's rtl: 
- insn 24: reg76 = mem (load)
- insn 25: reg77 = reg76 << 16
- insn 26: reg74 = reg77 >> 16 (def)
- jump 29: use reg74
- insn 33: reg75 = reg74 (use)
- jump 36: use reg74
That's 1 def + 3 uses = 4 refs, but the dump says 8. Maybe the count includes subreg uses (reg76 used twice: sll reads it, and...).

Hmm.

Let me try a more experimental approach: generate a bunch of variants and score them, looking for one where iVar1 lands in v1 and iVar2 in a0. Variables to tweak:
- declaration order of iVar1/iVar2/tmp
- iVar2 width
- the copy form
- statement order

Let me write a generator producing ~12 variants and score them.

Variants:
c1: a1 but with iVar2 declared as s16 and copy `tmp = iVar2;` (no cast).
c2: a1 with `tmp = (s16)iVar2;` and tmp declared s16.
c3: a1 with the copy inside the then-arm? no.
c4: `tmp = iVar2;` + `iVar2 = tmp;`? changes semantics slightly (same value).
c5: `tmp = iVar2; if (tmp != iVar2) ...` no.
c6: use `iVar2` cast to `s32` via a union? no.
c7: `tmp = (s32)(s16)iVar2;` (same as a1).
c8: reorder declarations: tmp before iVar2.
c9: `s16 iVar2; ... tmp = (s16)iVar2;`? 
c10: `tmp = iVar2;` with iVar2 used in the arms instead of tmp? Then tmp unused.

Hmm, let me think about what the launder version's RTL looks like in terms of which regs are used in the jumps. Let me look at orig2's cse2 for the first block.
