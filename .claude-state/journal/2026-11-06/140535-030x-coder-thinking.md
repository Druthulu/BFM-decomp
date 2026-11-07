---
ts: 2026-11-06T21:05:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oLA9Rqll9kP3DsSWGsjn
---
Confirmed: after combine, insn 42 is `(set (reg/v:SI 72) (and (reg:SI 84) 4095))` — the andi was folded into ang (pseudo 72), and the `a` copy (insn 35) is gone. The `a` variable (reg/v:SI 4) was eliminated entirely: insn 42 writes 72 directly. Combine merged: `a = 84 & 4095; ang = a` → `ang = 84 & 4095`.

So combine does the merge because `a` is a "user variable" reg/v with hard reg 4, but combine treats it as a normal pseudo (it's a virtual reg). The hard-reg preference is only applied at local-alloc; combine can freely fold it.

With the keepalive asm, `a` has an extra use (asm), so combine can't eliminate it; insn 35 remains `a = ...; ang = a`, then local-alloc honors $4 for a and the copy remains.

So the question: how to keep `a`'s definition and the copy without an asm use?

Idea: Give `a` a second *real* use that combine can't fold. What real use does the target have? None beyond the copy... But maybe we can use `a` in the computation of `d` or the condition in a way that emits no extra insn? For example, `if (d == 0x53)` where d = D_80126C01. No.

What about making `a` used in the `final` block? a is dead there. If we write `ang = a` in final, a would be $4 but clobbered → wrong.

Alternative: prevent combine from folding the copy by making the copy not adjacent/not in the same basic block? Combine works per basic block; a copy across blocks won't be folded. But `a` is a virtual reg that must be live across the block boundary — then it's a global pseudo and local-alloc won't necessarily give it $4.

Hmm, but the copy must be in the block right after the andi (target). Combine folds within the block.

Wait — what if we insert the `d = ...` load *between* the andi and the copy, so combine can't see them as adjacent? In the current w1, order: insn 32 (plus), 39 (d load), 42 (andi+copy). Actually combine already moved the d load before the andi. In orig, order: andi (insn 33), copy a (35), d load (38). The d load is after the copy in orig! Let's check orig's combine dump.

In orig, the sequence: andi→a (33/35), then ang=a (42), then d load (38? numbered). Hmm orig had insn 33 andi, 35 set a, 38 load d, 42 set ang. So combine didn't fold because a had the asm use at... wait the asm use is after the d load. In orig: a computed, then d load, then asm(a), then ang=a. So the asm use is between d load and ang=a.

Combine's folding of `a = and; ang = a` requires the copy to be the only use of a and in the same block. The asm use breaks "single use".

Could a *real* use of `a` between them work? What if we reorder the C so the copy happens after the d load and a is used... no.

Alternatively, use `a` in a real expression whose result is needed: e.g., make `d` depend on `a`? Target lbu v1 = D_80126C01; no dependence.

Hmm. What about a different structure: avoid the temp `a` entirely and get andi into $4 another way. The target's andi a0 could come from the fact that `a` is used as a call argument in the `call` branch? No, that branch calls through a table with no args.

Wait — the `call` path: `return (s16)((s16(*)())(D_80188654[...]))();`. The target at 34e0-3508 does the table lookup and jalr with no args. $4 is not used there.

Another thought: the andi result `a` is $4 because it's the pinned user variable. The pin is what forces $4. If we drop the pin, the andi would still be folded into ang and get s0 — same as w1. So the pin alone without a use is useless.

So we need a genuine second use of `a` OR a structure that keeps the copy.

Real-C lever: "pointer reuse", "statement order", "init at decl", "temps", "decl order/scope", "s16/u8 widths", "loop shape", "&&/|| folds".

What about making `a` the destination of a store? E.g., store `a` somewhere and reload? No, target doesn't.

What about using `ang = a;` where ang is a *different width* so the copy is a zero/sign extend (a real insn that combine might not fold)? The target's move s0,a0 is a plain move. If ang were s16, `ang = a` would be a subreg copy; the later use `ang + ratan2(...)` would need sign extension. Target doesn't have that.

Hmm, what about declaring `a` as `volatile`? That would force memory. No.

Let me look at how the sibling func_80148AFC (matched with pins) handles the same andi: it uses `register s32 tmp __asm__("$5") = (ratan2(...) - 0x400) & 0xFFF;` then `sVar3 = tmp;`. It has a pin on tmp and a copy sVar3 = tmp. Is there a keepalive asm? No! Let me check: in func_80148AFC there's no asm for tmp. And it's matched (71 ins). So there, the copy `sVar3 = tmp` survived without an asm! Why?

Because `tmp` is `register asm("$5")` and initialized at declaration. Then `sVar3 = tmp;`. Hmm, and combine didn't fold? Or maybe the structure differs (there are subsequent uses).

Wait, actually maybe the pin DOES force a hard reg when the variable is initialized at declaration? Let me re-read: `register s32 tmp __asm__("$5") = expr;` — the variable has an initializer. Maybe GCC treats register-asm variables differently when they have an initializer... Hmm.

Actually, in our w1, `a` is declared then assigned (`a = expr;`). In func_80148AFC, `tmp` is declared WITH initializer. Maybe that changes whether combine can fold: with an initializer, the "user variable" gets a hard-reg rtl from the start and combine won't substitute?

But in our orig.c, `a` is declared without initializer and assigned later, and it works because of the asm. Let me test: declare `a` with an initializer at decl: `register s32 a __asm__("$4") = (ratan2(...) - 0x400) & 0xFFF;` and remove the separate assignment. Then `ang = a;`.

But wait, the declaration order matters: p = D_801151D4 must be set before a's initializer uses p. In C89, all declarations must come before statements. So we'd need `s32 p = D_801151D4;` at decl too. Let's restructure:

```
s32 func_80148D44(void) {
    s32 p = D_801151D4;
    register s32 a __asm__("$4") = (ratan2(((Unkstruct_80126948 *)p)->unk44 - ..., ...) - 0x400) & 0xFFF;
    s32 d = (s32)D_80126C01;
    s32 ang;
    s32 res;
    ang = a;
    ...
}
```

Hmm, but `d` load order: target andi then lbu. With `a` initialized at decl, the computation happens at decl point, then d at its decl. Order preserved.

But does `register asm` with initializer force the hard reg? Let me test with the sibling as evidence: func_80148AFC is MATCH and has exactly this pattern (pin $5 with initializer, then sVar3 = tmp). So yes! That's the key real-C move: initialize the pinned variable at declaration. Wait, but is the pin itself needed? For item 1 the pin is allowed (not a row kind). So use the initializer trick.

Actually hold on — maybe combine doesn't fold because `tmp`'s value is used twice? In func_80148AFC, `sVar3 = tmp;` is the only use of tmp I see. Let me confirm: `sVar3 = tmp;` then tmp not used. So it's a single use, yet survived. So the initializer-at-decl is likely the difference.

Hmm, but actually the difference might be that in func_80148AFC, `tmp` is $5 (a1) and the copy sVar3 is to a different pseudo; combine still could fold. Unless combine doesn't fold when the destination is a user variable? Both are user variables (reg/v).

Let me just test it. Write w2.c with the initializer form.

Note: `p` is used in the initializer, so p must be declared/initialized before. In C89 all declarations are at block start; initializers are evaluated in order. So:
```
s32 p = D_801151D4;
register s32 a __asm__("$4") = (ratan2(...p...) - 0x400) & 0xFFF;
s32 d = (s32)D_80126C01;
s32 ang;
s32 res;
ang = a;
```
But target order: lw v0,D_801151D4 (p), then ... ratan2, andi, then lbu d. Good.

Let me write and test.
