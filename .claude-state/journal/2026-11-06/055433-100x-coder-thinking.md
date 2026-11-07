---
ts: 2026-11-06T12:54:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tDaWPnlMhKxjcRvSSsQZ
---
This is getting deep. Let me think about what the removed asm did more concretely by looking at the ORIGINAL (with asm) lreg/greg dumps vs c1's.

Actually, a faster approach: the differences are (1) the src register a1 vs a2, (2) c36/dcount swapped v0/v1, (3) prologue order.

Since `ba` is pinned to $5 = a1 and `dst` to $4 = a0, and in the target `src` = a2: the pin on ba ($5) reserves a1. Without the launder/keepalive, src takes a1 (after ba dies).

In the target, src = a2. Why? Because `src` is `base`'s copy: `u16 *src = base;` where base is a variable (t2). The copy `src = base` → gcc copies t2 → a2.

Hmm, why would src go to a1 in mine? Maybe because in mine the copy happens later/earlier or the register preferences differ.

Note the launder `__asm__("" : "=r"(decoy) : "r"(ba))` + keepalive(decoy): this creates a pseudo `decoy` that is live and forces `ba`'s value into a register at that point. Since ba is pinned $5 (a1), the asm's input is a1, and the output decoy gets some reg. The keepalive then uses decoy → decoy is live across the copy loop? That could affect register allocation of src!

Actually, the launder's purpose per the comment: it's a launder (out-only asm with an input) — it makes `ba` opaque so that the subsequent `dst = ba` doesn't just alias? Hmm.

Since all my variants stay at 18, let me look at what the exact diffs need:
1. src: a1 → a2 (4 insns)
2. c36/dcount: v1/v0 → v0/v1 (2 insns)
3. prologue order (2 insns)

Let me try:
- `u16 *src = base;` where base is declared as `u16 *base` and assigned earlier. Maybe making src's copy use a different expression: `src = (u16 *)base;` no change.
- What if `src` is declared as `u16 *src = (u16 *)base;`?

Alternatively, maybe the target's `src` is not a copy of base but of `param_1`... no, `src = base` in the C.

Hmm, let me look at the target's full asm to see where base/t2 is set.

Let me look at the region around 0xf44 (the main loop) and the start.

Actually, let me reconsider: the launder/keepalive might have been keeping `base` (t2) alive and `src` in a2 via a copy chain. 

Alternative plan: maybe I should think about which registers are free at the copy loop. At the loop:
- dst = a0 ($4 pin)
- ba = a1 ($5 pin), dead after `dst = ba`
- src = ?
- The loop body: lhu v0,0(a2); sh v0,0(a0)...

If src took a1, that's because a1 is free (ba dead). In the target, src is a2, meaning a2 was preferred/allocated earlier. src's copy `move a2,t2` in the target vs `move a1,t2` in mine — a local-alloc choice for the copy's destination qty.

In local-alloc, the qty for `src` (used across the loop, not dying) is allocated globally (global-alloc) since it spans blocks? src is used in the copy loop (one block) — the loop is a single basic block! So local-alloc assigns it.

local-alloc: for each block, quantities get registers if the block's live range doesn't cross calls. The copy loop block: src, dst, tv, iVar2. dst pinned a0, tv → v0. src → a1 or a2?

The `qty` order: local-alloc sorts by `qty_n_refs` etc. and assigns the first free reg from `reg_alloc_order`... src has many refs (each `*src` use).

Hmm, why a1 vs a2? Maybe the *pins*: ba=$5 (a1) is live at the block start (dst = ba is the first insn), so a1 is occupied → src should get a2! But in mine src got a1, meaning `ba` was dead before src's allocation... 

The order in the block: `dst = ba;` (dst=a0, ba=a1) then the loop. So a1 is live at the start. Unless the C has `dst = ba;` and then ba dies. local-alloc allocates qty's per block with conflicts; src conflicts with ba at the start (both live at the block head? src is live from the block start too).

Hmm, unless in mine the copy `src = base` is INSIDE the block and `dst = ba` after, so src is born after ba dies? Let me look at the C:

```
{
    u16 *src = base;
    ...
    ba = (u16 *)(tmp + (u8 *)dp);
    {
        register u16 *dst __asm__("$4");
        dst = ba;
        do { ... } while (iVar2 < 0xc);
    }
}
```
`src = base` is at the top (decl-with-init), and `dst = ba` is after. So in the block, src is live from the start and ba too → conflict → src can't take a1... but mine took a1.

Wait, maybe the launder asm was what kept ba alive until the copy loop, forcing src out of a1! Without the launder, `dst = ba` becomes `move a0,a1`... 

Hmm, in mine: `addu a0,v1,a0` (ba computed into a0!), `lhu v0,0(a1)`. So mine computes ba directly into a0 ($4 = dst's pin!) — because dst=ba is coalesced: `dst = ba` and ba pinned a1... 

Wait: mine `addu a0,v1,a0; lhu v0,0(a1)`: a0 = v1 + a0 (ba), and src in a1. Target: `addu a1,v1,a0; move a0,a1; lhu v0,0(a2)`.

So in the target, ba is computed into a1 ($5 pin) and then copied to a0 (dst). In mine, ba is computed directly into a0 and src is in a1.

So mine's `ba` pseudo got coalesced into dst (a0) — i.e., local-alloc tied ba and dst. In the target, ba stays in $5 and dst copies.

The launder asm `"=r"(decoy) : "r"(ba)` forced ba to be a *real* value (not coalesced with dst) because it's read by the asm. And the pin `ba __asm__("$5")` should have forced ba into a1... but in mine ba's pin... 

Hold on! In mine, `register u16 *ba __asm__("$5")` is still there (pins stay). So ba IS $5 = a1. But the asm shows ba computed into a0. Hmm, maybe the pin was dropped because ba's value is only used by `dst = ba` and gcc... no, a pinned register variable is a hard reg.

Unless gcc's `ba = (u16 *)(tmp + (u8 *)dp);` with ba pinned → `addu a1,v1,a0`. In mine it's `addu a0,v1,a0`. So the pin isn't taking effect?! Let me check c1.c has the pin. Yes: `register u16 *ba __asm__("$5");`.

Hmm wait, maybe with `-O2` and `register ... __asm__`, gcc 2.7.2 does honor it. Let me look at the mine asm again around the tail: from the diff, mine[130] = `addu a0,v1,a0`, mine[131] = `lhu v0,0(a1)`.

Hmm, that means ba went to a0. But a0 is dst's pin ($4)... conflict! Both pinned to... no, dst is a *different* variable pinned to $4=a0. If ba is pinned to a1, the code must be `addu a1,...`.

Unless... the `register u16 *ba __asm__("$5")` pin means the *variable* ba lives in a1, and gcc would emit `addu a1,v1,a0`. Mine emitted a0.

Let me check whether c1.c still has the ba pin after my edits. The grep earlier showed line 100 `register u16 *ba __asm__("$5");` — yes.

Hmm! Unless gcc's handling: with a `register` variable pinned via asm, and then `ba = X`, gcc might copy-prop... Hmm.

Wait, maybe I misread the diff alignment. mine[130:133] vs target[130:134]:
```
130  addu	a0,v1,a0     | addu	a1,v1,a0
131  lhu	v0,0(a1)     | move	a0,a1
132  addiu	a1,a1,2      | lhu	v0,0(a2)
133  --                 | addiu	a2,a2,2
```
So mine: `addu a0,v1,a0; lhu v0,0(a1); addiu a1,a1,2`. If ba is in a1 in the target, in mine the roles are: a0 = ba/dst, a1 = src.

Hmm, so mine's ba went to a0 and src to a1. That's exactly swapped relative to the pins. Something's off — maybe gcc renumbered and the target's a1 IS ba (pin $5) and mine's a0 is... 

OH WAIT. Maybe in mine the pin for ba was DROPPED because the variable `ba` is dead after `dst = ba` and gcc's copy propagation replaced `ba` with its value expression... A `register ... __asm__` variable still gets the hard reg. Hmm.

Let me just dump c1's asm from the object to check the whole tail. The dump dir has h1.s (the cc1 output). Let me look at the generated assembly for the copy loop.
