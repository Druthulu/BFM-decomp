---
ts: 2026-10-21T23:40:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_U8kOcBcNVdae4XvTShsM
---
So func_801415C0 IS the last function. And it shows constants. So gcc really did constant-fold. Why?

OH!!! I understand now! `func_800291B4` etc. are declared as extern but the *real* definitions exist in the repo? No, they're extern.

Hmm, but constant folding of param_1 to 0? That can't happen without IPA.

Unless... gcc 2.7's `cse2`/`jump` didn't do this. Let me look at the .flow dump section for func_801415C0, which is BEFORE global allocation but after flow. Let me read it.

Actually wait. Let me reconsider the dump semantics. gcc's `-dl` prints "local register allocation" info, `-dg` "global register allocation". The RTL printed is at that stage.

Hmm, the fact that the call args are constants 0 and 16... 

OHHH. I bet this is the dump of the function AFTER the "expand" of the calls where the arguments are... no.

Hold on, maybe I'm misreading: maybe `(const_int 0)` is the *deleted* note... Let's re-read:

```
(insn 13 18 15 (set (reg:SI 4 a0)
    (const_int 0)) 159 {movsi_internal2} (nil)
    (expr_list:REG_EQUAL (const_int 0)
        (nil)))
```
Yeah a0 = 0.

Hmm, and `(call_insn 15 13 20 (parallel[ (set (reg:SI 2 v0) (call (mem:SI (symbol_ref:SI ("func_800291B4"))) (const_int 16))) ...

The call has ONE arg: (const_int 16). So d = 16 = 0x10.

So param_1 = 0x10 - 0x2F = -25? Weird.

Unless the function being dumped is a *different* function that gcc named... no.

Hmm, could the .i file be wrong? The cpp output c1.i — my TU had `#include "pad.inc"` and the externs. Let me check c1.i contains my function properly. And c1.i.s (assembly) to see the actual code generated.

Let me look at c1.i.s for func_801415C0.

Hmm wait — actually! Maybe gcc's dump prints RTL with `(const_int 0)` for things it can't represent... no.

Let me just check the generated assembly c1.i.s.

Hmm, hold on. Another thought: maybe cc1 didn't get my file correctly — the .i file might contain a DIFFERENT func_801415C0? No.

Wait wait wait. Let me re-read: `(insn 13 18 15 (set (reg:SI 4 a0) (const_int 0)) 159 {movsi_internal2}`. 

Hmm, in gcc's RTL dump, `(const_int 0)` could be the *note*? No.

Let me just look at the assembly output. That's definitive.
