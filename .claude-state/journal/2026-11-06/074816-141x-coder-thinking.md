---
ts: 2026-11-06T14:48:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_92Eih3l2sn0Pd8dZnb32
---
This is hard to read. Let me instead compare the number of branches in the case 5 region of c1's .cse2 vs orig's .cse2. If cse2 folded, c1 would have fewer branches.

Actually, let me just test v7/v8 empirically and see. Let me generate:
- v7: `t = (s16)a1;` before the check.
- v8: save/restore dead-reset.
- v9: `t = (s32)(s16)a1;` before the check.
- v10: `t = t;`? forbidden identity, skip.

Let me test v7/v8/v9.

Actually, let me reconsider v8 more carefully:
```
if (t == 5) {
    s32 save = t;
    t = 0;
    t = save;
    if (t != 3) goto sel_094;
    ...
}
```
The compiler (front-end/cse) might:
- `save = t` -> save == t.
- `t = 0` -> t == 0.
- `t = save` -> t == save == 5? cse knows save's value (from save=t when t==5). So t == 5 again. Fold.

Unless cse doesn't propagate save's value. Let me test.

v7: `t = (s16)a1;` — the compiler knows t == (s16)a1. Since a1 is a parameter, the second `(s16)a1` CSEs to the same value as the first t. Then cse records t == (s16)a1, but the branch recorded t == 5. Hmm, the set of t to (s16)a1 — cse's `record_jump_equiv` puts a REG_EQUAL on the register; a subsequent set invalidates it. But the set is to `(s16)a1` which cse might know equals 5 (if a1's value is known? a1 is a parameter, not constant). So after `t = (s16)a1`, cse doesn't know t==5 (it knows t == (s16)a1, and the branch's t==5 note is gone). Then `t != 3` can't be folded! But the extra computation `sll; sra` — would it be CSE'd with the earlier `(s16)a1`? The earlier `t = (s16)a1` computed `sll $16,$17,16; sra $16,$16,16`. The second `t = (s16)a1` is the same expression; cse would CSE it to the same pseudo, and since t already has that value, it might delete the assignment (self-copy). Hmm, then no set. 

Let me just test v7.

Let me generate v7, v8, v9.
