---
ts: 2026-11-06T17:31:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jBRBlsEw5JGxfZN22SPb
---
All 7. Time 10:31, 5.8 min.

Let me look at the target's exact 3-instruction difference again:
```
163 sll v1,a0,0x10  | sll v0,a0,0x10
170 sll v1,v0,0x10  | sll v0,v0,0x10
171 sra v0,v1,0x10  | sra v1,v0,0x10
172 srl v1,v1,0x1f  | srl v0,v0,0x1f
173 addu v0,v0,v1   | addu v1,v1,v0
174 sra v0,v0,1     | sra v1,v1,1
175 sh v0,242(s0)   | sh v1,242(s0)
```
So in the target, sh16=v0 and the temp chain uses v1. In mine, sh16=v1 and the temps use v0.

The target's sh16=v0 might be achievable if the *first* def's source is v0... In the target, the first def's source is a0 (`sll v0,a0,16`), so the dest≠source. That means the preference was NOT followed in the target either (it was pinned).

For a lever-free body, we need the allocator to pick v0 for sh16. The preference (whatever it is) points to v1.

What if we *change the preference* by making the shift sources die differently? E.g., `sh16 = angle << 16;` where angle is used later (not dead) → the preference may not be set. The angle is used at `p[0x79] = angle;` before. If angle were used AFTER the shift too, the tie wouldn't happen.

Try: use `angle` after the shift, e.g., `p[0x79] = angle;` moved after? The target's store order: `sh v0,242(s0)` (p[0x79]=angle) happens BEFORE the branch (bc08). So the store is before.

Hmm, in the source, `p[0x79] = angle;` is before the if. So angle's last use is the store (before the shift). The shift uses `angle` again — so angle is live across the store. 

What if we reorder: `if (r[0x49] == 5) { sh16 = angle << 16; } ... p[0x79] = angle;`? The store order changes → bytes change.

Let me try a different tack: make the *load* in the else arm die before the shift: `sh16 = p[0x79] << 16;` — the load temp (147) is dead at the shift → tie → preference v0 (147's reg). In mine, 147 is in v0 and the preference... the dump said 3.

Honestly, let me try modifying the declaration of sh16 to `s32 sh16 = 0;` (init) — adds an instruction but changes the pseudo's birth/priority. No.

Time check: 6 min in, 14 to go for a 20-min wall. Let me try a couple of broader structural variants and then decide. Since this is a header item, a MATCH needs 141 includers — expensive but the body is shared (the same body for all). If I find a body scoring 0 on includer 0, I can verify the rest.

Let me try:
y1: split sh16's computation: `sh16 = angle; sh16 = sh16 << 16;` (two statements) in both arms.
y2: `s32 t16 = angle << 16; sh16 = t16;`
y3: declare sh16 inside the if's block.
y4: use a union? no.

Let me test y1-y3.
