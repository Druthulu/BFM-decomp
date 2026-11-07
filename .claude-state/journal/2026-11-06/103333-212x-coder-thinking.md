---
ts: 2026-11-06T17:33:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1waXqevZlhJFLud9bT0q
---
All 7. Time 7.6 min.

Let me think about the preference differently. In the nopin greg dump: "75 preferences: 3". The preference set has ONE reg: 3 (v1). combine_regs adds a hard-reg suggestion when one side of a copy is a hard reg. Is there any copy `(set 75 (reg hard))`? No. But combine_regs is also called for insns where the *output* and a *dying input* are tied: `(set (reg 75) (ashift (reg 77) 16))` — 77 dies → tie 75 to 77's qty (pseudo). Then the qty contains 75 and 77. If 77's qty later gets a hard-reg suggestion (e.g., 77 is tied to a0 via the copy `move a0,v0`?), then 75's qty shows that suggestion.

Hmm, the angle (77) is used as `p[0x79] = angle` (a store) and in the shift. The call result v0 is copied to angle? In the asm: `jal func_80029D3C; move a0,v0; sh v0,242(s0)` — the angle is in v0 then copied to a0. The copy `move a0,v0` suggests a0 (4), not v1.

Where does v1 come from?! Maybe from the SECOND def: 75 = 147 << 16, 147 dies → tie 75-147. 147 = zero_extend(146); 146 = the load. 147's qty might be tied to v0 (from `lhu v0,...`).

Hmm, neither gives v1.

Unless the preference 3 comes from `(set (reg 75) ...)` where the previous value of 75 is in v1... no.

Let me look at the actual RTL after combine (nd.i.combine) for the shift insns — maybe combine rewrote them. Or the cse2 dump. Let me grep the combine dump for the sh16 insns.

Actually, maybe the preference comes from the *store* `(set (mem) (subreg:HI (reg 151)))` — no.

Time: let me try the most direct thing: find which insn gives the v1 suggestion by searching the greg dump for the hard reg 3 in 75's qty. Too deep.

Alternative empirical: make the shift's input NOT die at the shift (keep it live) so no tie:
- `sh16 = angle << 16;` → `sh16 = angle << 16; if (angle) {}` no.
- Use angle after the shift: e.g., `p[0x79] = angle;` moved AFTER the shift? changes order.

In the else arm: `sh16 = p[0x79] << 16;` — the load temp dies. If we write `sh16 = (s32)p[0x79] << 16;` the load is the same.

Hmm, what if the shift source is a *different* variable that stays live? e.g., `s32 av = angle; sh16 = av << 16;` — adds a copy.

I think this is a wall. But it's a header item: maybe I should check whether the residual (7) is the same on ALL includers or only some. If the pin removal happens to match on other includers, the win must be 0 on all — no.

Time: 8 min. Budget 20-30. Let me try a few more variants (the shift expression and the store), then record a WALL.

Actually — wait. Let me reconsider: the target's sh16=v0 and the temps v1. In mine, sh16=v1. What if the *temps* could be forced to v1 first? The temps are local-alloc'd; the first temp (148) gets v0. If we could make 148 take v1... e.g., if 148's life were shorter or its priority lower.

Hmm, what if we split the expression so that fewer temps exist? The target has 4 temps. 

What if the expression uses sh16 directly in the store without temps? `p[0x79] = (u16)(sh16 >> 17) + ...` no.

Let me try writing the expression as:
```
p[0x79] = (u16)(((sh16 >> 16) + (sh16 < 0)) >> 1);
```
`sh16 < 0` → slt (different instruction).

Or `((u32)sh16 >> 31)` → `(sh16 < 0)`? same value but slt/srl differ.

No.

Let me try: `p[0x79] = (u16)((sh16 >> 16) + ((u32)sh16 >> 31)) >> 1;` (the cast outside the shift) — v4 was 18.

OK, let me try 3 more and then decide. Actually, since the score is 7 and only 3 instructions differ, maybe a slightly different source spelling can flip it. Let me brute-force a bunch of spellings of the two shifts and the sum:

b1: `(s32)((u32)sh16 >> 31)` vs `(sh16 >> 31)` (v5=7).
b2: `((s32)sh16 >> 16)`.
b3: `(sh16 / 0x10000)` → div (bad).
b4: use `s16` temp: `s16 h = sh16 >> 16;` then `(u16)((h + (s32)((u32)sh16 >> 31)) >> 1)` — adds width ops.

Let me test b2 and a couple of others quickly.
