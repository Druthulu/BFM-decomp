---
ts: 2026-11-06T17:29:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CuXoYeJbCjvLPNVjr37d
---
Now I see the RTL:
- sh16 = pseudo 75 (reg/v:SI 75).
- 148 = sh16 >> 16 (ashiftrt)
- 149 = (u32)sh16 >> 31 (lshiftrt)
- 150 = 148 + 149
- 151 = 150 >> 1
- store 151.

In the target, sh16=75 is in v0. Pseudo 75 has 4 refs (2 defs, 2 uses).

The temps 148, 149, 150, 151 are single-block, short-lived.

Local-alloc priority: 75 (4 refs, life across blocks 396→424, spanning the branch at 421 — it's live across blocks 396/419 to 423) — pseudo 75 is a GLOBAL allocno (live across blocks), not local! The temps 148-151 are local to the block containing 423-427.

Local-alloc assigns the block-local temps FIRST (during local_alloc), then global-alloc assigns 75. Since v0 is taken by a local temp (148?) in that block, 75 gets v1.

Wait, but the target has 75 in v0 and the temps in v1. In the target (pinned), 75 is fixed to v0, so the temps take v1.

Lever-free: to get 75 into v0, no block-local in 75's live range may use v0. The block-local temps 148/149/150/151 are allocated in local-alloc: 148 (>>16) is born at 423 and dies at 426; 149 born 424 dies 426; 150 born 426 dies 427; 151 born 427 dies at the store.

Local-alloc gives the first temp (highest priority) v0 — that's 148 → v0. Then 149 gets v1, etc. In mine: `sra v0,v1,16` (148 in v0), `srl v1,v1,31` (149 in v1 — reusing 75's reg? no, 75 is v1 in mine).

In the target: 148=v1, 149=v0 (srl v0,v0,31). Hmm, target's 149 is v0 — but 75 is also v0 and dies at 424 (REG_DEAD at insn 424). So 149 reuses v0 after 75 dies.

So the target's temps: 148=v1, 149=v0, 150=v1, 151=v1.

Mine: 148=v0, 149=v1, 150=v0, 151=v0.

If we could make 75 (global) get v0, then local-alloc's temps would avoid v0 while 75 is live... but local-alloc doesn't know 75's reg yet (it's global). Local-alloc assigns 148=v0, 149=v1 (since 148 is live at 149's birth? 148 dies at 426, 149 born 424 → overlap → different regs).

Then global-alloc assigns 75: it conflicts with v0 (148 live 423-426) and v1 (149 live 424-426) → 75 must take another reg (a0? t?). Hmm, but mine has 75=v1. That means 149 is NOT v1 in mine... let me re-read mine:
```
170 sll v1,v0,16    ; sh16=75 in v1
171 sra v0,v1,16    ; 148=v0
172 srl v1,v1,31    ; 149=v1 (reusing 75's reg? 75 dies at this insn)
173 addu v0,v0,v1   ; 150=v0
174 sra v0,v0,1     ; 151=v0
175 sh v0,242(s0)
```
So 75=v1, 148=v0, 149=v1, 150=v0, 151=v0.

Local-alloc assigned 148=v0, 149=v1 (148 and 149 overlap at 424-426, so different). Then 150 (born 426, dies 427) can reuse v0 or v1 (both dead after 426? 148 dies at 426, 149 at 426 → 150 could be v0), 151=v0.

Global-alloc then assigns 75: 75's live range includes 423-424 where v0 (148) and v1 (149) are live → 75 conflicts with both → 75 should get a0 or another. But mine has 75=v1! Contradiction... unless local-alloc did NOT assign 148/149 to hard regs because they're... hmm.

Maybe 75 is not global: it's live across the branch at 398/421 (the if/else arms). Blocks: the then-arm (396), the else path (400-419), join (421+). So 75 is live across blocks → global. Yes.

But global-alloc runs after local-alloc and sees the hard regs used by the local temps. If 148=v0 and 149=v1 in the join block, 75 (live at 423-424) conflicts with both → 75 can't be v0/v1. Yet the final asm shows 75=v1.

Unless the local temps were NOT allocated to v0/v1 by local-alloc; maybe local-alloc didn't allocate them (they're "global"? no, block-local). Hmm.

Wait, maybe the block containing 423-427 is a different basic block from where 75 dies. Let me check: 75 is used at 423 (ashiftrt) and 424 (lshiftrt), and defined at 396/419. The join at 421 starts a new block. 75 is live into block 421+ (global). The temps 148-151 are in block 421+ (local).

Local-alloc processes block 421+: it assigns 148, 149, 150, 151. Then global-alloc assigns 75, conflicting with the hard regs live in its range: at 423, 148's reg (v0) is live → 75 ≠ v0. At 424, 149's reg (v1) is live → 75 ≠ v1. So 75 would get a0/t0. But the final is v1!

I'm clearly misreading something. Maybe local-alloc doesn't assign 148/149 before global; maybe the *dump* shows the final assignment and the interaction differs.

Rather than theorize, let me test the hypothesis "the temps take v0/v1 and 75 must avoid them": if I make the expression use FEWER temps (so v0 is free), 75 might get v0.

The temps: 148 (>>16), 149 (>>31), 150 (sum), 151 (>>1). What if the expression is written to reuse: `p[0x79] = (u16)(((sh16 >> 16) + (s32)((u32)sh16 >> 31)) >> 1);` — 4 temps.

Alternative spelling with fewer temps? The target has the same 4 temps.

Hmm.

What if I add a dummy use of v0? no.

Let me look at the target's build (pinned) RTL to see how the temps got v1: with the pin, 75=v0 fixed; local-alloc assigns 148: it can't use v0 (75 is live at 423) → v1. 149: v0 is free at 424? 75 dies at 424 (REG_DEAD on 424) → 149 can use v0. Yes! That's the target's `srl v0,v0,31`.

So the target's pattern is consistent: with 75=v0, 148=v1, 149=v0, 150=v1, 151=v1.

Lever-free: 75 is global (assigned after local). Local-alloc assigns 148=v0 (lowest free) because it doesn't know about 75. Then global-alloc: 75 conflicts with v0 and v1 → gets something else... but the observed result is 75=v1, so local-alloc must have assigned 148=v0 and 149=... let me look at the final: 149=v1, 150=v0, 151=v0. So local temps used v0 and v1; 75 got v1 — meaning global-alloc did NOT see 149 as conflicting? 149's live range is 424-426; 75 is live at 424 (its last use) — they conflict. Unless global-alloc's conflict computation ignores local allocs' hard regs when the local dies at the same insn (the death point).

Whatever. The empirical fact: 75=v1, and the temps v0/v1.

To get 75=v0, we need the local temps to avoid v0 — impossible since local-alloc gives v0 to the first temp.

UNLESS 75 is not global! If 75 were block-local (i.e., its defs and uses in ONE block), local-alloc would allocate it together with the temps by priority, and 75 (4 refs, longer life) might get v0.

Can we make sh16 block-local? The defs are in two branches (different blocks). If we restructure so both assignments happen in the SAME block as the use, e.g., compute sh16 without branches:

```
sh16 = (r[0x49] == 5) ? (angle << 16) : ...;
```
The else path has a call and a goto. Hmm.

Alternative: use a conditional expression where the call is evaluated first:
```
if (r[0x49] != 5 && func_8014CB7C() == 0) goto LAB;
sh16 = (r[0x49] == 5) ? (angle << 16) : (p[0x79] << 16);
```
That changes the CFG and the instructions (the call would be evaluated in a different order). The target's CFG: `if (r[0x49] == 5) {sh16=angle<<16} else {if (call()==0) goto; sh16=p<<16}`. The target's asm has the branches. Restructuring would change the code.

Hmm.

What if sh16 is assigned in each arm but ALSO in the join (a redundant assignment) making it... no.

OK, the alternative: make 75's priority in local-alloc irrelevant — impossible while it's global.

Wait, actually: maybe the issue isn't the temps but global-alloc's choice. Let me look at the greg dump for 75's conflicts and the allocation order.
