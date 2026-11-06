---
ts: 2026-10-22T20:32:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_c14ziG6xXNibvfXQ9MmO
---
w5 has s1 (extra callee-saved) — the address in s1. Why? Because with 3 sets of src, gcc's cse creates a separate pseudo (r80-ish) from the movstr dest and the assignments... hmm.

In w1, the calls use src and there's no s1. So w1 is special: the calls use the hard reg directly, and the movstr dest pseudo is *dead* (not used by the calls). That's why no s1.

So w1 is the right structure! The only issue: the hard reg $5 is assumed live across the calls, so only one addiu.

Target: 3 addiu. If the address value were dead after each call, reload would rematerialize. Since src is a hard reg, gcc never reloads it.

What if the call argument is `(void *)(src + 0)`? cse folds +0.

What if the calls use a *fresh copy* of src into a normal variable *inside each call's argument*, e.g. `(void *)(mp = src)` with mp an int*? Assignment expression → mp is a pseudo set at each call, 3 sets → global → s1 (like w8/w5).

What if we use `o2` (int) as the address and set it before each call from `src`? `o2 = (int)src;` — src is a hard reg, so this is a copy to a pseudo; 3 sets → global → s1.

Hmm. The target's 3 addiu are constant rematerializations at each call: reload knows the value is fp+16 and remats. That only happens when the pseudo holding it has no register.

The key question: in w1, the calls use `src` (hard $5). In the target, the calls use the constant fp+16 with no register.

Can I make the C call `(void *)m` (constant) while ensuring the movstr dest pseudo is NOT the same value as seen by cse? The movstr dest pseudo r80 = fp+16, and cse uses it for the call args. What if the movstr dest address is set from the pinned src (a hard reg)? Then r80 = (reg a1) — a copy; cse would know r80 == a1's value; the call args (constant fp+16) wouldn't be equated to r80 unless cse knows a1 == fp+16 (it does, since src was set to fp+16 and cse folds constants... but src is a hard reg, so cse may not track its value).

Hmm! In w1, src = &D_800AE620 (a constant), then the movstr source is `(mem:BLK (reg src))`. cse folded the symbol in? The output shows `lui a1; addiu a1; lw v0,0(a1)` — so a1 holds the symbol address and the loads use offsets: that's the movstr source pseudo (r81 = symbol) expanded, allocated to a1. And src (hard $5) may have been coalesced/ignored.

For the dest: if I write the copy with the dest as the pinned src... but src holds the source.

New idea: use the pinned src for the *destination* during the copy and a *different* pointer for the source:
```
src = (int *)m;                          // src (hard $5) = m
*(Mat32 *)src = D_800AE620;              // movstr dest via hard reg; source symbol pseudo
src = (int *)m;                          // (redundant)
RotMatrixX(..., (void *)m);              // constant → addiu per call
```
Here the movstr dest is the hard reg (a1), so no dest pseudo; the calls use the constant m. cse would equate the call constant fp+16 with... the hard reg's value? cse may fold the constant into `set a1, fp+16` per call (as in score-0) → 3 addiu! And the dest stores would be `sw v0,0(a1)` (not sp-relative) — target has sp-relative. That's a difference of 8 stores (a1 vs sp) → score ~16. Hmm, but maybe gcc's movstr with a hard-reg dest still uses sp offsets? Unlikely.

Unless... after the movstr, gcc's reload sees a1 = fp+16 and the stores use a1. Target uses sp.

OK, so what about the source via the hard reg and the dest as the symbol-free constant:
```
src = (int *)&D_800AE620;
*(Mat32 *)m = *(Mat32 *)src;   // w1
```
Then calls `(void *)m` → w4 = 19 (dest pseudo).

I keep going in circles. Let me accept: w1 = 2 is the best lever-free body; the residual is reload keeping the pinned $5 value across the calls instead of rematerializing the constant per call. Wall tag: `reload-hardreg-call-live` or reuse an existing tag. Existing tags: sched1-argcopy-hoist, cse-const-addr, ... This is a reload/hard-reg issue. The `pin` in the def is a pre-existing lever (allowed to stay), but the *residual* is caused by the pin's hard reg being kept live across calls. Since the pin is allowed to stay (kinds=launder only), a body scoring 2 with the pin kept is a legitimate lever-free (w.r.t. launder) body. 

Hmm wait — but is the pin actually *needed* in w1? Let me test w1 without the $5 pin: `int *src;` (no asm). Then `src = &D_800AE620; *(Mat32*)m = *(Mat32*)src; src = (int*)m; calls src;` — without the pin, cse folds src's constant into the movstr source (fine) and the calls use `(void*)src` → cse folds to the constant per call → addiu ×3! And the copy source: `*(Mat32 *)m = *(Mat32 *)src` with src folded to the symbol → movstr with a symbol source pseudo → a1 base. That could be exactly 0!

Wait, but then the calls' constant fp+16 might again be equated with the movstr dest pseudo (r80)... In w1, the movstr dest pseudo exists (r80) but wasn't reused for the calls because the calls used the hard reg. Without the pin, the calls use src = constant fp+16 → cse would equate it with r80 → 19 again? Or cse folds the constant into the call args (since it's a constant, and r80's equivalence...). In c_struct the calls used `(void *)m` (constant) and cse reused r80 → 19. So without the pin, w1 becomes w4-like → 19.

Hmm. Unless the src set after the copy (a second set of src) changes things.

Let me just test the no-pin variant: 
```
int *src;
src = (int *)&D_800AE620;
*(Mat32 *)m = *(Mat32 *)src;
src = (int *)m;
RotMatrixX(..., (void *)src);
```
This is w1 without the $5 pin. cse: src's first value is a constant → folded into the movstr source; the second set is fp+16 → folded into the call args → 3 addiu? and the movstr dest pseudo might be reused... Let me test. If it gives 0, great: no levers at all (except the $16 pin which may stay).

Test also the variant where the copy uses the symbol directly:
```
*(Mat32 *)m = D_800AE620;
src = (int *)m;
calls (void *)src;
```
(no $5 pin) — src's value is a constant, folded into the calls → 3 addiu? and the movstr dest pseudo r80... cse would equate src's constant with r80 → move a1,s1? or fold the constant. In c_struct, the calls' constant got replaced by r80. Here src is a pseudo assigned a constant; cse might replace its uses with the constant (fold into a1) — score-0 did that. Worth testing!

Let me test both no-pin variants.
