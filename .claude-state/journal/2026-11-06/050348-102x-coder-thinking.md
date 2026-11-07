---
ts: 2026-11-06T12:03:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Rq11BPOUwFRAePrgoHD1
---
Still 4. The residual is the address materialization into v0 + moves.

Let me think: mine has `addiu v0,sp,16` then `move a2,v0`, `move a1,v0`. Target: `addiu a1,sp,16` then `move a2,a1`, and later `addiu a0,sp,16`.

So target doesn't reuse the address across calls; mine computes it once into v0 and moves. The launder forces va into a register — in mine, va=v0 (then copied to a1/a2?).

Hmm, in p2 the launders are kept. So the launders should force va/vb to regs. Mine: v0 for both, then moves.

The difference is which register the launder outputs get. Target: va=a1, vb=a2. Mine: va=v0 (then moved).

The first call: `func_80149350(node, va, vb)` → a1=va, a2=vb. In mine, va and vb are both v0, so moves.

Real C moves: make va and vb differ. E.g. `vb = va + 0;`? identity. `vb = (u8*)&f.cx;` gave 6.

Hmm. The `f.cx` address: `(u8 *)&f.cx` where f is a local struct at sp+0x10. Target materializes it twice (a1 and a0).

What if we use a pointer variable declared and assigned twice (so each use is a fresh addiu)?
```
u8 *va, *vb;
va = (u8*)&f.cx;  (launder)
f.cy = arg2;
vb = va;  (launder)
```
The launder on vb makes a new pseudo = va. Target: a2 = a1.

In mine: a2 = v0 and a1 = v0. So both are copies of v0.

Maybe the issue is that va's launder output got v0 and then both uses copy from it. In target, va's launder output = a1 directly, and vb's = a2 directly.

What if va is declared/used differently: e.g. `va = &f.cx` where the type is `u8*`; the address is sp+16 (a constant offset). 

Try: declare `va`/`vb` as `s32` and cast at the call? Hmm.

Try: make the first use of va be the call argument directly: the call is at the end. The launder's purpose is to force va into a register early (so the addiu is materialized before f.cy's store).

Target: addiu a1,sp,16 comes BEFORE the f.cy store (f.cy at sp+18?). Mine: addiu v0,sp,16 also before.

The only difference is the register: v0 vs a1, and mine copies to a1/a2.

This is local-alloc: mine gave the laundered pseudo v0 and inserted copies because the call needs a1/a2; target gave them a1/a2 directly.

Real C lever: declaration order? The launder creates a new pseudo; its allocation is by local-alloc qty priority. If I add more uses or change the order...

Idea: swap the order of the two launders' targets: make vb the first (assigned before va):
```
f.cy = arg2;
va = ...; launder;
vb = va; launder;
```
b_cyfirst = 4.

Idea: use two separate address expressions and no copy:
```
va = (u8*)&f.cx; launder;
vb = (u8*)&f.cx; launder;
```
e = 11.

Hmm.

What about the launder's operand form: `__asm__("" : "=r"(va) : "0"(va))` — the "0" constraint ties input to output (same reg). The compiler picks the reg.

Since these are the kept kind (launder), can I change the launder's form? That would still be a launder kind. E.g. `__asm__("" : "+r"(va))` (read-write) — still a launder. The brief says no NEW lever, but modifying an existing lever... risky; it's still the same kind (launder). Hmm, the goal of PARTIAL is to keep only that kind. Changing its exact spelling is arguably still a launder. But it might be seen as gaming. Let me avoid unless needed.

Alternative: change what the launder applies to. Hmm.

Let me think about the target's allocation: a1 and a2 are the call's arg registers. The call is `func_80149350(node, va, vb)` — node in a0, va in a1, vb in a2. If va/vb are born just before the call, local-alloc would prefer... but there are other statements between (the corner stores etc.), and the target keeps a1/a2 live across them.

Mine uses v0 for both and copies at the call. Why? Because the laundered pseudos were assigned v0 (a cheap caller-saved reg) and then copied.

Since the launders are kept in p2, maybe I can change the *number* of launders (e.g. drop one launder — still keeping the launder kind). p1 (barriers kept, launders gone) = 9. What about barriers gone and only ONE launder? Let me try:
- f1: p2 with only the va launder (drop the vb launder).
- f2: p2 with only the vb launder.

Both keep the launder kind → PARTIAL:launder if 0.

Let me test.
