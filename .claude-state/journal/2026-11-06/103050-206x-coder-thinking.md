---
ts: 2026-11-06T17:30:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MSkTkf9JroKncgAVq6Uy
---
Mine:
```
lh $4,242($16)      ; cmp79
beq $4,$2,$L1705
jal func_80029D3C
move $4,$2          ; ??? weird: move $4,$2 in the delay slot
sh $2,242($16)      ; p[0x79] = angle (angle = $2 = v0)
lbu $3,73($18)      ; r[0x49]
li $2,5
beq $3,$2,$L1703
sll $3,$4,16        ; sh16 = angle << 16  (angle in $4=a0, result $3=v1)
jal func_8014CB7C
beq $2,$0,$L1705
lhu $2,242($16)
sll $3,$2,16        ; sh16 = p[0x79] << 16 (v1)
$L1703:
sra $2,$3,16
srl $3,$3,31
addu $2,$2,$3
sra $2,$2,1
sh $2,242($16)
```
Target:
```
move a0,v0         ; angle saved
sh v0,242(s0)      ; p[0x79]=angle
lbu v1,73(s2)
li v0,5
beq v1,v0,bc38
sll v0,a0,16       ; sh16 = angle<<16 -> v0
jal ...
...
lhu v0,242(s0)
sll v0,v0,16
bc38: sra v1,v0,16
srl v0,v0,31
addu v1,v1,v0
sra v1,v1,1
sh v1,242(s0)
```
The difference: the target's sll destination is v0 (with the source a0); mine's is v1 (source a0) — wait, mine's sll is `sll $3,$4,16` = sll v1,a0,16 and the target's is `sll v0,a0,16`.

So the sll output register: v1 (mine) vs v0 (target). The preference: 75 prefers reg 3 (v1) — because the *first* sll's source is a0? Hmm, preference 3 = v1. Where does v1 come from? Maybe from the `p[0x79]` load: the second sll's source is $2 (v0) → preference v0. Hmm.

Actually the qty 75 has 2 defs (two slls) with different sources: the first source is a0 (from angle), the second is v0 (from lhu). The preferences would be {a0, v0} = {4, 2}. But the dump says "75 preferences: 3" (v1) — odd.

Hmm, "preferences: 3" in global-alloc means qty_phys_sugg bit 3 = v1. Where from? Maybe from the store: `sh 75?` no.

Wait, maybe 75 isn't sh16. Let me verify: in the flow dump, the shift `(set (reg/v:SI 75) (ashift (reg/v:SI 77) 16))` — yes, 75 is sh16.

Preferences 3 (v1): hmm, maybe from combine_regs where the sll's output is copied to something in v1? Or the `p[0x79]` store... 

Let me look at the global-alloc preferences mechanism: `qty_phys_sugg` gets a hard reg when a copy insn ties a pseudo to a hard reg. For 75, maybe there's a copy `(set (reg 75) (reg ...))` somewhere? The two slls set 75 directly.

Hmm, the "preferences: 3" might be from a REG_NO_CONFLICT or a copy preference added by local-alloc's combine_regs: when a pseudo is set from a hard reg or vice versa. `(set (reg 75) (ashift (reg 77) 16))` where 77 is a pseudo → tie 75 to 77's qty (a preference for 77's eventual reg? no).

Whatever the mechanism, the result is v1.

Empirical approach: change the second source (p[0x79] load) to influence the preference. The second sll's source is `p[0x79]` loaded into a temp (147). If that temp is in v1, the preference would be v1.

In mine: `lhu $2,242($16)` → the loaded value is in v0, then `sll $3,$2,16` (source v0, dest v1). Hmm, so the source is v0 but the dest is v1.

In the target: `lhu v0,242(s0); sll v0,v0,16` — same reg.

So in the target, the second sll's dest = source (v0). In mine, dest v1 ≠ source v0. So the preference was NOT followed for the second sll, but the first sll (a0→v1) also doesn't follow.

Hmm, so where does preference v1 come from? Maybe from the *first* sll: `sll v1,a0,16` — the dest is v1 and the source a0. Not a copy.

Let me look at the global-alloc's `75 preferences: 3` — maybe reg 3 is a0? No, MIPS: 2=v0, 3=v1, 4=a0. Reg 3 = v1.

The preference could come from the *store* `sh 75, 242(s0)`: no.

Let me look at the greg RTL for the sh16 insns to see the preference source... The greg dump prints "75 preferences: 3".

Hmm, maybe it's from local-alloc's combine_regs on the two `(set 75 ...)` insns where the *previous* value of 75 (v1?) ... 

Let me try an experiment: change the second assignment's source to make the preference v0: e.g., `sh16 = (s32)p[0x79] << 16;` — same.

What if we swap the arms: `if (r[0x49] != 5) {...} else { sh16 = angle << 16; }` — changes layout.

What if we use a conditional expression for the assignment, so both sources feed one sll? Not possible with the call/goto.

Let me look at the target's preference: the target (pinned) had sh16 forced to v0. So we don't know its natural preference.

Given the time (10:30, 5 min in), let me try a few things:
1. Change the first sll's source: `sh16 = angle << 16;` where angle is s32. The angle pseudo is in a0 (a copy from v0). 
2. Make sh16 assigned via a temporary: `s32 t = angle << 16; sh16 = t;` → adds a copy (bytes change).
3. Use `(sh16 = angle << 16)` in a different order.

Actually — maybe the cleanest lever-free move: the preference for v1 might come from the *second* def: the loaded p[0x79] value (pseudo 147) is in v0... 

Let me check the global-alloc dump for 75's preferences and the flow dump's REG_DEAD. Actually, let me try modifying the code so the two sll sources are the same register as the dest naturally.

Experiment: replace `sh16 = p[0x79] << 16;` with `sh16 = *(u16 *)(p + 0x79) << 16;` — same load.

Hmm.

Another idea: the *angle* variable. In the target, angle is copied to a0 and the sll uses a0 with dest v0. In mine, angle is in a0 too (`sll $3,$4,16`). So the first sll: target dest v0, mine dest v1. The preference says v1. If the preference came from the first sll's source (a0), it'd be a0.

Let me look for the copy that creates the preference: in the flow dump, is there a `(set (reg 75) (reg X))`? Let me grep the flow dump for "reg/v:SI 75".
