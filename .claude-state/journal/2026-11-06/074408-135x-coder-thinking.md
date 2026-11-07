---
ts: 2026-11-06T14:44:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3xlayti0NXy3zk2WAxoE
---
Removing the launder gives score 4 (MIXED): a register swap v0->v1 (x2) and a branch structure difference.

Target:
```
li v1,3
...
beq s0,v1, ...
bne s0,v0, ...
bne s0,v1, ...
```
Mine:
```
li v0,3
...
beq s0,v0, ...
beq s0,v0, ...
j ...
```

So the launder forces `t` (s0?) into a register such that the constant 3 is in v1 (not v0), and the branch structure differs (bne vs beq/j).

Let me look at the surrounding code. The launder is at `if (t == 5) { __asm__("" : "=r"(t) : "0"(t)); if (t != 3) goto sel_094; sel_054: ... }`.

The `t` is `(s16)a1` from case 5. The comparisons `t == 5`, `t == 3`, `t != 3`.

The target has:
```
li v1,3
beq s0,v1,...   (t == 3 -> sel_054)
bne s0,v0,...   (t != 5?)
bne s0,v1,...   (t != 3 -> sel_094)
```

Hmm, let me look at the target asm around there. Let me dump the function. But first, let me understand the C:
```
case 5:
    t = (s16)a1;
    if (t == 0) { sel = &D_8018C4FC; goto set_sel; }
    if (t == 3) { goto sel_054; }
    if (t == 5) {
        __asm__("" : "=r"(t) : "0"(t));   // launder
        if (t != 3) { goto sel_094; }
    sel_054:
        sel = &D_8018C520;
        goto set_sel;
    sel_094:
        ...
    }
    if ((func_800291B4(D_801802E4[t]) & 0xFF) == 0) { goto call_45F; }
    ...
```

Wait, the `if (t == 3) goto sel_054;` is BEFORE the `if (t == 5)`. So t==3 jumps to sel_054 (which is inside the t==5 block!). Interesting control flow.

The launder `t` self-reference forces t into a register (s0) so that the comparisons use s0. Without it, the compiler might keep t in memory or use a different reg.

The diff: mine uses v0 for the constant 3, target uses v1. And the branch structure differs: mine `beq s0,v0` twice then `j`; target `beq s0,v1; bne s0,v0; bne s0,v1`.

This looks like the launder affects the constant register allocation (v0 vs v1) and the branch folding (jump.c's branch optimization).

Let me look at the target asm around insn 90-100. Let me dump the TU (orig) and look.

Actually, let me first try the obvious real-C replacements for the launder:
1. Remove it and adjust the code (c1) → 4.
2. Replace with a real computation that uses t, e.g., `t = t;`? identity (forbidden).
3. `t = t + 0;`? folds.
4. Use the do-while(0) trick.
5. Restructure the if/else.

The launder's purpose: force t to be in a register at that point. The "=r"/"0" constraints mean the asm reads and writes t in the same register, and it's not volatile (so it can be optimized? but the "=r" output forces a register).

Without it, the compiler might rematerialize t or use a different reg.

Let me look at the target asm to understand. Let me dump.

Let me set up the dump for this TU. The TU is src/ov_SC01_004/ov_SC01_004_jr_8017E5B8.c. Let me dump it with cc1_dumps_tu.

Actually, let me first try the simple real-C variants and see if any scores 0:
- c2: replace the launder with `t = (s16)t;`? (redundant cast, might emit nothing or an sll/sra)
- c3: restructure: `if (t == 5) { if (t != 3) goto sel_094; sel_054: ... }` — the launder is gone. That's c1.
- c4: use `if (t == 5 && t != 3) goto sel_094;`? changes structure.
- c5: do-while(0) around the t==5 block.

Hmm. Let me look at the target asm first to understand what the launder achieves. Let me dump.
