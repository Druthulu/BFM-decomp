---
ts: 2026-11-06T18:41:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bGgRZkCDSJEAbS69yIRM
---
No score 0. Best remains 4 (60 of 180). So statement order doesn't fix it.

Time: 11:40:35; item 1 started 11:30 → 10 min. Tries: w1-w6 (6) + p001-p180 (180) = 186 tries. Plenty.

Now, the mechanism: without the asm barrier, sched1 places the a1 symbol_ref late. I need a real-C barrier. Hmm.

Wait — maybe there's another approach: make the a1 materialization *not fold* into the call arg and give it a real use that is scheduled early. What if a1 is used by the *first* call? E.g., reuse a1 for the second arg of the first call:

```
a1 = (s32)&D_801A1590;   // hmm, the first call's arg is D_801A1590
func_8012B1B4(s0, (void *)a1);
```
That would change the first call's arg setup (it currently uses a symbol_ref directly). The target's first call: `lui a1; addiu a1; jal` — the arg is a symbol. If we assign a1 = &D_801A1590 before the call and pass a1, the code would be the same insns (a1 = symbol; call) — but the target's first call arg materialization is at 8008-800c (right before the jal), which matches. Then a1 is *reused* for the second value: `a1 = (s32)&D_801A15AC;` — a1 is a variable assigned twice; the second assignment has a use at the second call.

Would that change the second a1's scheduling? The second assignment is still one use. Hmm, but a1 as a variable live across the call... no, it's dead at the call (used by it).

What if the a1 value is used *before* the call in a way that's free? 

Hmm, what about making the *first* call use the same a1 variable, so the a1 pseudo has 2 refs and can't be folded into the second call arg? Let me think: 
- `a1 = (s32)&D_801A1590; func_8012B1B4(s0, (void *)a1);` → the a1 value dies at the first call.
- `a1 = (s32)&D_801A15AC;` → new value.
Combine sees a1 (pseudo 77) assigned the symbol and used at the call. It could still fold each into the call args.

Not obviously helpful.

Alternative: **use a variable that is live across the first call** so it can't be folded: e.g., assign `a1 = (s32)&D_801A15AC;` BEFORE the first call func_8012B1B4? Then a1 is live across that call (the call clobbers a1's hard reg? a1 is call-clobbered, so the pseudo would need to survive the call → the allocator would keep it in a callee-saved reg or reload). But the target has the a1 load AFTER the first call (801c). So no.

Hmm.

Let me reconsider the target's schedule. In the orig (with asm), the order is 45,47,49,52,55,57,... In w1 (no asm): 45,47,49,52,58,61,64,67,70,72,75,77,86,89,94,96,98,100,104,105 (from the trace; the insn numbers differ). Let me map: in w1, the a1 materialization is insn 94 (the call arg), scheduled at position ~15.

What if I make the call arg materialization insn have a *dependency on an early insn*? E.g., if the a1 value were computed as `(s32)&D_801A15AC` but stored in a variable that's also used by the unk14 store... 

Wait, actually, here's an idea: **make the first store (unk14) use a1's value**? No, the stored value is v0.

**Make a2's value (D_801A15B4) computed from a1?** The target: a2 = &D_801A15B4 (a symbol). No.

Hmm, what if the a1 variable is declared as a pointer to the same type and the value is loaded... no.

OK, different tactic: maybe I can make sched1 not fold the a1 symbol into the call arg by preventing the fold: combine folds `(set (reg 5 a1) (reg 77))` when 77 has one use. If 77 had two uses (both real), the fold wouldn't happen. A second use that costs no insn... 

What if the call is `func_8012D5E4(a0, a1, a2, a3)` and we also use a1 in the *comparison* of the same call: `if (func_8012D5E4(a0, a1, a2, a3) == 1)` — no.

What about `func_8012D5E4(a0, a1, a2, a3)` where the compiler must keep a1 in a register across the call? No, a1 is an argument.

Hmm, hold on. Let me reconsider: maybe the *original* target source (before the pin) had a different shape that naturally produced the early a1. What if the source used `a1` in the address of the unk58 store? No.

What if the source had the a1 assignment *inside* an expression, e.g., `func_8012D5E4(a0, (s32)&D_801A15AC, a2, a3)`? Then the materialization would be at the call arg — late. No.

What if the source computed a1 early and used it for a store: e.g., the target's `sw v0,20(a0)` (unk14) — what if the store were `*(s32*)((char*)a0 + 0x14) = v0;` — no a1.

I'm stuck on the a1 scheduling. Let me look at the problem from the "sched1 barrier" angle: which real-C constructs act as scheduling barriers for sched1?
- A volatile memory access (a volatile store or load).
- A function call.
- An asm.

A volatile store! What if one of the stores is written through a `volatile` pointer? E.g., `((volatile Unkstruct_800B5CB8 *)a0)->unk14 = v0;` — the store becomes volatile, acting as a barrier. But would that change the generated code? A volatile store to the same address is the same instruction. And sched1 treats volatile stores as barriers (they can't be reordered with other memory ops). That could force the order!

But is `volatile` a lever? The brief forbids levers: pin, launder, barrier, keepalive macro or asm. "barrier" — a volatile store as a scheduling barrier would be a barrier lever! Hmm, the kinds list: "no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." A volatile store used to steer the scheduler is a barrier lever — not allowed. So no.

OK, so we need a *natural* C construct. The target's a1 early position must come from something real.

Let me reconsider: maybe the target's a1 position isn't due to the asm at all — maybe the orig's RTL has a different structure that I misread. Let me look at the orig's .rtl (not sched) around the a1 insn and the asm.

Actually, in the orig's RTL, the keepalive asm is at insn 56/57 and the a1 assignment at 55. The asm is `(asm_operands ("") ...)` with a use of 77. Let me check the orig's .rtl to see the exact insn sequence. And the .combine dump might show the fold.

Let me look at the orig's .rtl function.
