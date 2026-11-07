---
ts: 2026-11-06T22:41:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PbCsw1Fz5yfJwInzRVoR
---
In w6:
- `mine: lw v0,32(a0)` vs target `lw v0,32(v0)` — mine uses a0 (no arg0 copy). The target has `move v0,a0` first.
- iVar4 in a1 vs target v1 (register pair a1->v1 x20).
- u5 in v1 vs target a0 (v1->a0 x5).
- d=s0 ✓, s1ang=s1 ✓.

So w6 fixed d/s1ang but shifted u5 and iVar4. Interesting: in w6, u5 (r79?) got $v1 and iVar4 (r77) got $a1, whereas the target has u5=$a0, iVar4=$v1.

In w0, u5=$v1, iVar4=$a1 too! Wait, w0's diff earlier showed `subu a1,v1,s0` — iVar4=$a1, u5=$v1. And the target: `subu v1,a0,s1` — iVar4=$v1, u5=$a0. So w0 also had u5=$v1, iVar4=$a1 — the SAME as w6. So the u5/iVar4 difference is present in both w0 and w6; the register swap was the only *extra* difference in w0. Wait, but w0's score was 38 with `sra s1,v0,0x10 | sra s0,s0,0x10`... 

Hmm, in w0 the diff showed only a few lines (the register pairs). Let me re-run w0's full diff to compare. The earlier dt.sh tail-40 for w0 showed lines 22-68 with differences in d/s1ang AND iVar4/u5? Let me look: w0 line 25: `subu a1,v1,s0 | subu v1,a0,s1` — yes, mine iVar4=a1, u5=v1; target iVar4=v1, u5=a0. So w0 also has that difference! I misread earlier. So w0's differences are:
- d/s1ang swap (s1 vs s0)
- u5/iVar4: mine v1/a1, target a0/v1

So w0 and w6 differ only in the d/s1ang swap and the arg0 copy. Both have the u5/iVar4 shift.

Hmm wait, but the score of w0 was 38 and w6 was 38. And w6 has 74 ins (missing move). So the remaining issues are:
1. u5 should be $a0, iVar4 should be $v1 (mine: u5=$v1, iVar4=$a1).
2. The arg0 copy (missing in w6, present in w0).
3. In w6, the load scheduling order.

Let me focus: the target wants u5 in $a0 and iVar4 in $v1. In our lever-free bodies, u5 gets $v1 and iVar4 gets $a1.

u5 = (ratan2(...) - 0x400) & 0xFFF. In the target, u5 is $a0 (a caller-saved reg, and $a0 was arg0 which is dead). iVar4 = $v1.

Why does u5 get $v1 in ours? The alloc table: r80 (4 refs/4 insns, prefers v0) = u5? It got... in w0's greg dump "80 in 2" (v0)? Hmm. Let me map the pseudos:
- r78: 10 refs/10 insns, prefers a1 → iVar4 (10 refs: computed once, then compared and modified in both arms).
- r79: 7 refs/8 insns, prefers a1 → ?
- r80: 4 refs/4 insns, prefers v0 → ?
- r76: 5 refs/14 insns → ?
- r77: 5 refs/10 insns → u6.

In the final w0 asm: iVar4 = $a1 (r78 → a1 via preference). u5 = $v1 (r80? it prefers v0 but conflicts v0, so v1). u6 = $s0 (r77).

Hmm, what's r79 (7 refs/8, prefers a1)? Maybe u5? Let me check: u5 = (call - 0x400) & 0xFFF. refs: the call result, the -0x400, the &0xFFF, then uses in compare, iVar4, arms... Actually u5 is used in: compare (u6==u5), iVar4 = u5-u6, iVar4 = u5 - t (twice). That's ~5 uses. u5 might be r79 (7 refs).

Hmm, the mapping is unclear. Let me look at the target's pinned alloc table: r78 30000 (10 refs), r80 20000 (4 refs), r79 17500 (7 refs), r77 10000 (5 refs), r76 7142 (5 refs). And the target asm: iVar4=$v1, u5=$a0, u6=$s1, d=$s0.

In the pin table, r77 = u6? (5 refs/10, prefers s1). r75 = s1ang raw (2/7). So u6 = r77.

In w0: u6 = r77 = $s0. iVar4 = ? In w0's asm, iVar4 = $a1. Which allocno got $a1? r78 prefers a1 (r78 10 refs/10). So iVar4 = r78 = $a1. In the target, iVar4 = $v1. So the target's r78 got $v1.

In the target (pin), the .greg order: 78 80 79 77 76. r78 (10 refs) first → gets... in the target asm, what's $v1? iVar4. So r78 = $v1 in the target. In w0, r78 = $a1.

Why the difference? r78 "prefers a1" in both tables. In the pin table, r78 "conflicts v0,s0,sp" and prefers a1. In w0, r78 "conflicts v0,sp" prefers a1. Hmm, in w0, $a1 is available (preference) → $a1. In the pin table, r78 conflicts v0,s0,sp; prefers a1 → but the target has it in $v1!

Wait, the preference is just a preference; global-alloc's `find_reg` tries the preferred reg first? Let me check: in global.c, the preference is used only if the register is not conflicting AND... Actually global-alloc assigns hard regs using `find_reg` with `reg_preferred`? Hmm.

Actually, wait: in the target, the pinned $s0 (d) changes the conflicts. r78 conflicts s0 in the pin table. But that shouldn't push it from a1 to v1.

Hmm, let me look at the target asm again: `subu $3,$4,$17` (iVar4 = $3 = $v1). And `$4` = u5 = $a0. So iVar4=$v1, u5=$a0.

In w0: `subu $5,$3,$16`? No, w0's asm: `subu $5,$3,$16` — hmm wait, w0's asm has `subu $5,$3,$16` where $3 = u5 (v1), $16 = u6 (s0), $5 = iVar4 (a1). Yes.

So the target's u5=$a0 and iVar4=$v1; w0's u5=$v1 and iVar4=$a1.

This is a register allocation ordering difference: in the target, u5 (r79 or r80) gets $a0 and iVar4 (r78) gets $v1; in w0, iVar4 gets $a1 and u5 gets $v1.

The preference: r78 prefers $a1 (iVar4). In w0 it gets $a1. In the target it gets $v1 — so $a1 must be taken or conflicting in the target. Who takes $a1 in the target? Let me look at the target asm: $5 = $a1 is used for `lh $5,6($2)` (arg0+6) and `subu $5,$3,$5` (the ratan2 second arg). So $a1 is used by the call argument. Hmm, but that's before iVar4's birth.

Hmm, maybe the pin changes the allocation order such that r78 gets $v1. In the pin table, the .greg order is 78 80 79 77 76 — r78 first. If r78 gets $v1, then r80 (u5?) gets... Let me check the pin table's hard regs: r78 `-`, r80 `-`, r79 `-`, r77 `-`, r76 `-`. Hmm, the alloc table doesn't show their assigned regs. Only local-alloc'd ones show hard regs. The global allocnos show `-` and the .greg order. So I can't tell from the table.

Let me instead look at the greg dump for the pin version to see the assignments. Actually, the "Register dispositions" line in the greg dump shows "72 in 2 74 in 17 75 in 16..." — that's the mapping. Let me check the pin's greg dump.

Hmm, this is getting very deep. Let me step back and think about the score-38 pattern: in all our lever-free bodies, iVar4=$a1, u5=$v1, whereas the target has iVar4=$v1, u5=$a0. This is a *separate* difference from the d/s1ang swap. To reach score 0, we need ALL of them right.

Wait, but the W50x notes said w1 (keepalive removed, pin kept) scored 2 — "Only diff: sll s0,s0,0x10 (d=(s16)d) born 2 slots early." So with the pin kept, everything else matched (u5=$a0, iVar4=$v1). So the pin's presence made u5=$a0 and iVar4=$v1. Without the pin, they shift.

So the pin affects the whole allocation order. Removing the pin requires reproducing its effect on u5/iVar4 too. That's a big deal.

Hmm, but w6 got d=$s0 and s1ang=$s1 (matching the pin's effect on those), yet u5/iVar4 still wrong. So the mask-in-place fixed d/s1ang but not u5/iVar4.

What determines u5=$a0 vs $v1? Let me look at the alloc table: in w0, r80 (4 refs/4, prefers v0, conflicts sp) — if r80 is u5, it prefers v0 but v0 is taken by r100 (v0, 40000). So r80 gets v1. In the target (pin), u5 = $a0. Which pseudo is u5 in the pin table? Maybe r79 (7 refs/8, prefers a1)? Hmm.

Let me identify the pseudos precisely by looking at the lreg dump's insns and the final regs. Let me map in w0:
- u5 = (call - 0x400) & 0xFFF: the call result r99/r100? Let me trace: insn 51 sets r99 = v0 + (-1024), insn 52 sets r76 = r99 & 4095. So u5 = r76! (5 refs/14 insns). Yes: r76 "used 5 times across 14 insns". So u5 = r76.
- u6 = r77 (5 refs/10).
- iVar4: insn 69 uses r77; the subu iVar4 = u5 - u6 → some pseudo. Let me find. In w0's lreg, after insn 69, `iVar4 = u5 - u6`. Which reg? Let me grep.

So u5 = r76, and in w0 r76 = $v1 (from the asm `subu $5,$3,$16`: $3=v1 is u5). In the target, u5 = $a0. r76's pri 7142 in both tables. In the pin table, r76 conflicts v0,s0,s1,sp; in w0, conflicts v0,s0,sp. Hmm.

iVar4 = ? Let me find which pseudo. Probably r78 (10 refs/10, prefers a1) — in the target it's $v1.

OK let me look at the greg dumps' dispositions for w0 and pin to map.

w0 greg: "72 in 2 74 in 17 75 in 16 76 in 3 77 in 16 78 in 5 79 in 5 80 in 2 81 in 2 85 in 3 88 in 4 92 in 3 95 in 5 99 in 2 100 in 2 101 in 2 102 in 2 104 in 2 106 in 2"
- 72 in 2 (v0) — arg0 copy
- 74 in 17 (s1) — d
- 75 in 16 (s0) — s1ang raw
- 76 in 3 (v1) — u5
- 77 in 16 (s0) — u6
- 78 in 5 (a1) — iVar4
- 79 in 5 (a1) — ? (7 refs/8)
- 80 in 2 (v0) — ?
- 81 in 2 (v0) — pointer
- 85 in 3 (v1)
- 88 in 4 (a0)
...

Target (pin) greg dispositions: let me read.
