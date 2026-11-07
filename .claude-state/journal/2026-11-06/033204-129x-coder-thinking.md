---
ts: 2026-11-06T10:32:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tjvpbyDtk13wZuK2cfLK
---
Confirmed: no `move a0,s0` at all. So with the pins but no barrier, GCC emits a call with a0 unset — a real codegen bug (or the arg is passed in a0 from the last call?). The last a0 set: `addiu a0,a0,0` for func_800233CC. After that call, a0 is clobbered. So the call passes garbage. That's a miscompile triggered by the missing barrier? No — the barrier can't cause a missing arg move.

Wait, this means GCC thinks the argument is already in a0. Since s0 is pinned $16, the arg is `s0` = $16. Unless the argument expression is not s0 but arg0, and arg0 was coalesced to a0! In barriers_off_pins_on, the call is `((void (*)(s32))func_80146C3C)(s0);` — s0 is the variable (pinned). Hmm.

Unless the compiler's s0 variable is actually in a0?! But the prologue `move s0,a0` sets $16... and `sw s0,16(sp)` saves $16. So s0=$16.

Hmm, but the call arg is s0. GCC should move $16 to a0. It doesn't. That's a bug — unless the call is being optimized as a tail call or the arg is dead. Weird.

Wait — maybe the source `((void (*)(s32))func_80146C3C)(s0)` with the pin: GCC's expand_call for a cast function... The barrier `:::"a0"` was there to work around exactly this. So without the barrier, GCC has a bug (or the body is semantically different). Whatever — the point is score 1, not 0.

OK, item 1 WALL 6 stands.

Now let me record item 4 (func_80023BF0) and then finalize the log.

Item 4: WALL, best 97 (m2.c = pkt moved after otab), tries 33, wall `global-hardreg-reserve` (or maybe a new tag). Let me use `global-hardreg-reserve` since the $3 pin reserves v1 for base across the function.

Hmm, but is that accurate? Let me check the residual: nopin pairs were t0->t1, a0->t0, t1->t2, etc. — a caller-saved shift, not a callee-saved reserve. The pin is on $3 (v1), a caller-saved reg. `global-hardreg-reserve` says "the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it". base=$3 (v1) reserves v1; lever-free the temps take it. That matches: the caller-saved temps shift because base no longer holds v1.

Yes, `global-hardreg-reserve` fits.

Also the 13 fences are a live-length slider (C0050) — needed but not sufficient without the pin.

Let me write notes and record.

win.c = m2.c (97). But wait — m2 moves pkt to after otab, which is a real-C move; does it keep the body semantically identical? Yes (pkt assignment order doesn't matter). Fine.

Let me record.
