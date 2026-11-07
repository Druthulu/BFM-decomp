---
ts: 2026-11-06T06:27:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fOpJniIj46MxbqZ15UcU
---
Interesting — here the do-while(0) replaced the asm because the asm's effect was CFG shape. In our case the asm's effect is a *use* between set and copy.

Let me test the equivalent placement: in our case the asm is between `otz = RotTransPers4(...)` and `otz = func_801823D4(otz, -0x1A)`. The G14 pattern put `do { } while (0)` at the same position — that's my w1, which scored 8 (no effect).

Hmm, but wait: in G14, the do-while kept the CFG shape because there was an if/else around it. In our case, no.

OK so let me now check: maybe the *combination* — w2 (do-while around the call) gives the pp fix; and maybe there's ANOTHER placement of the empty do-while that fixes the move. Let me think about what "CFG shape" the asm forced here: the asm insn was between the call and the arg copy. In w1, the empty do-while was in the same place but had no effect. Why did it have an effect in G14? Because there the asm was inside an else block at the end of a chain.

Alright, let me try placing the empty do-while *inside* the statement sequence differently: e.g. `otz = RotTransPers4(...); do { } while (0);` — w1 (8).

Hmm.

Let me try one more idea: since combine folds `(set r80 v0)` + `(set a0 r80)`, what if we make the *second* call take `otz` via a **different pseudo** that is assigned from otz inside a do-while:

```
do {
    t = otz;
} while (0);
otz = func_801823D4(t, -0x1A);
```
RTL: (set r80 v0), loop{(set t r80)}, (set a0 t). cse2 may propagate t... but cse2's copy propagation is within EBBs; the do-while's loop body might be a separate block. Then combine: (set t r80) and (set a0 t) are in different blocks → no fold. And (set r80 v0) can't fold into the loop block.

Result: `move s1,v0` (r80=v0), `move ?,s1` (t=r80), `move a0,?` (a0=t). That's 3 moves vs target's 2. Unless t coalesces with r80 (same reg) → then `move s1,v0` + `move a0,s1` = exactly 2! Coalescing happens in local/global alloc when t and r80 don't conflict — t is a copy of r80, they could share s1.

Hmm! That could work: t = otz inside a do-while, then use t. If cse doesn't propagate and the allocator coalesces t with otz, we get the target's 2 moves. Let me try it. It's a long shot but cheap.

Let me also try the variant where t is declared `s32 t;` outside the loop.

Let me test:
b5: 
```
        otz = RotTransPers4(...);       (inside the w2 do-while)
        do { } while (0);  -> no
```
Hmm, careful with the w2 structure. Let me construct b5 from w2:

w2 has:
```
        do {
            otz = RotTransPers4(...);
        } while (0);  // !FAKE: do-while
        otz = func_801823D4(otz, -0x1A);
```
b5:
```
        do {
            otz = RotTransPers4(...);
        } while (0);  // !FAKE: do-while
        do {
            t = otz;
        } while (0);  // !FAKE: do-while
        otz = func_801823D4(t, -0x1A);
```
with `s32 t;` declared.

Let me try b5 and also b6 where the copy is `s32 t = otz;` at decl.

Let me generate and score.
