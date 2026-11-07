---
ts: 2026-11-06T15:27:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y9UPZIMCPIcmvkupXwYQ
---
Mine: `move s1,v0; andi v1,s1,0x6000` — the copy exists, and the first test uses s1 instead of v0. Target: `move s1,v0; andi v0,v0,0x6000`.

So the difference: the first test's `raw` pseudo. In target, raw is the call result in $v0, used by the andi. In mine, cse replaced raw's use with flags? No — mine's andi reads s1 which holds the copy. So cse merged the two regs into one (both uses on s1), but the copy `move s1,v0` remains (that's the `flags = raw` copy).

Wait, if they were merged into one pseudo, the move wouldn't exist. So there are two pseudos: raw ($v0, dies) and flags ($s1), but the andi got attached to flags? Hmm, `andi v1,s1,0x6000` — the first test uses flags instead of raw. That's cse substituting flags for raw at the use (canon_reg picks one).

Interesting: cse records flags ≡ raw, and canon_reg replaces raw with flags (the *newer* reg? canon_reg uses reg_eqv to the first reg in the class; probably the one with lower regno = raw... but here it picked flags). Hmm, actually maybe the andi was on raw and cse rewrote it to flags.

Target: the andi is on raw (v0). So I need cse to *not* unify them at all, or to prefer raw.

In the original with the asm, flags is defined by the asm → flags is not equivalent to raw, and the first andi stays on raw.

So I need a real 2nd set of flags that cse can't see through, *before* the first use of flags but... the first andi is on raw. The problem is cse's equivalence table maps raw→flags. If I add a 2nd set of flags right after the copy, e.g. `flags = flags;` (deleted) — no. What about making flags' definition opaque via a real 2nd set that emits nothing? 

Hmm: what if flags is defined twice with a value-preserving op that cse folds but at the RTL level leaves a second set? E.g. `flags = raw; flags = flags & 0xFFFFE000 | (flags & 0x1FFF);`? Folds.

Alternative: make the copy `flags = raw` NOT a plain copy in cse's eyes by giving flags a different value that's masked later. Since the only uses are `& 0x8000` and `& 0x6000`, we could set `flags = raw & 0xE000` and let combine fold the masks. Let's test: `flags = raw & 0xE000;` then `m = flags & 0x8000;` → combine might fold to `raw & 0x8000`... but then the first andi on raw is unaffected, and cse may still unify at the use.

Actually, better: what about making flags' value come from a *different expression* that cse treats as a distinct value but which the target's andi then... no, target's second andi is `andi v0,s1,0x8000` (on s1) and `andi v1,s1,0x6000`. So flags must be in $s1 and hold the full value.

What about writing the second `if` condition differently, e.g. `m = raw & 0x8000` too? Then everything on raw → one pseudo global. No.

Hmm, what if we keep `raw` and `flags` but make the *first test* use the call expression in a way cse can't touch: e.g., test the call result through a separate local:

```
raw = call();
if ((raw & 0x6000) != 0x2000) ...
flags = raw;
```
No — the copy after the if; target's move is before the andi.

Wait, actually maybe the target's order is: move s1,v0 (copy) at 1f04, andi v0,v0 at 1f08. The andi uses $v0 (raw). If we put `flags = raw;` after the andi in source... the target's move is in the delay slot of the jal? No: 1f00 is the delay slot `sw s1,68(sp)` of the jal at 1efc, then 1f04 `move s1,v0`. So move right after the call, then andi on v0.

So source order: raw = call(); flags = raw; if ((raw & 0x6000)...).

To make cse not rewrite the andi's operand: the equivalence is created by the copy. cse's canon_reg rewrites registers to their canonical equivalent. If flags ≡ raw, both are canonical to one. In the target with the asm, flags is not equivalent.

Real-C options to create an opaque definition without asm: 
- A call? no.
- A volatile access? barrier kind, not allowed.
- A memory round trip through a non-volatile variable: `s32 tmp = raw; flags = tmp;` — same.

What about the dead-reset placed BETWEEN the copy and the first use? `raw = call(); flags = raw; raw = 0;` would break the equivalence but then the first test on raw would use 0. Unless the first test uses a different variable that holds the value:

```
raw = call();
flags = raw;
if ((raw & 0x6000) != 0x2000) ...   // uses raw before reset
```
The reset must be after the andi but before... cse processes the whole block: `raw=call; flags=raw; andi v1,raw,0x6000; ...; raw=0`. cse's table at the andi has raw≡flags, so it may rewrite the andi to flags. Order of canon_reg: it rewrites uses as it goes. So placing the reset after doesn't prevent the earlier use rewrite.

Hmm, but the earlier use is `raw` itself — canon_reg would rewrite raw's use to the canonical reg. Which is canonical? In cse.c, `reg_eqv` / `insert_regs`: when a copy `(set flags raw)` is seen, it records flags as equivalent to raw with `REG_EQUIV`? The canon_reg function replaces a register with the first reg in its equivalence class that is "cheaper" — typically it prefers the one with the lower register number? Let's check gcc 2.7.2 cse.c canon_reg.

Actually in the target (with asm) there's no equivalence so no rewrite. In mine, the andi got rewritten to s1 (flags). So canon_reg preferred flags over raw. Weird but whatever.

Maybe I can flip it: make the copy direction `flags = raw` such that canon picks raw. It picked flags... Perhaps because canon_reg replaces with the *last* reg (the newest)? Let's look at cse.c.

Alternatively, avoid the copy entirely and create the $s1 pseudo differently: e.g., store `flags` in a variable that is assigned *before* the call? No.

Another approach: `flags = raw;` where raw is not a register variable but the call expression:
```
flags = ((s32 (*)(s32))func_8012CBA4)(a0);
raw = flags;    // hmm
```
Same thing reversed: raw = flags copy, and the first test uses raw. canon would pick one.

What if the first test uses an expression that cse can't map to the same reg? E.g. `if ((raw & 0x6000) != 0x2000)` where raw was assigned from the call and flags is a *separate call result*? No.

Let's look at cse.c canon_reg to understand which reg wins.
