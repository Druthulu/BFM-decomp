---
ts: 2026-10-22T00:42:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_yFwiWPCoIU86svs4gWaI
---
The extra locals didn't change the score (still 7) — so the frame didn't change. Hmm! So adding unused scalar locals doesn't add frame space. That means GCC removes unused locals entirely (and the plain variant's 16-byte local area comes from something else).

Hmm, so what accounts for the plain variant's 24-byte frame? The locals v0, v1, pad — hmm. If GCC removes unused locals, then... hmm, but v0 and v1 ARE used (assigned). So they're allocated? But they're in registers. Hmm, GCC allocates stack space for locals that are "address-taken" or whose address is needed... but v0/v1 are in registers.

Hmm, wait: maybe GCC 2.7.2 allocates the frame space for all locals regardless (var_size = sum of the local sizes, rounded). Then adding 2 more scalars should have increased it. It didn't → so GCC *removed* the unused scalars (pad2, pad3) and kept... hmm, but then why is the plain frame 24 and not 8?

Plain: locals v0, v1, pad (12 bytes) → frame 8 + 12 = 20 → aligned to 24. Yes! That matches: the frame is 24.
Target: frame 32 → the local area = 24 → the locals total 24 bytes (or 20-24 → aligned 32).

So the target has ~8 more bytes of locals than the plain version. The asm's "m"(pad) input makes pad *address-taken* → GCC allocates it in the frame (4 bytes) — that gives 16 → the frame 24. Hmm, not 32.

Hmm, so the target's local area is 24: v0(4) + v1(4) + pad(4) = 12... unless the address-taken pad gets 8 bytes (alignment) or GCC adds a "save area" for the address-taken local.

Hmm! In GCC, an address-taken local is allocated *below* the frame with a specific offset, and the frame size grows. But only 4 bytes.

Hmm, what if the target's frame includes an extra 8 because the "m" input forces GCC to align the *stack* to 8 and add a "parameter save area"? Hmm.

Let me look at the target's asm for func_8017D9D8 (like item 5's): the target had `addiu sp,sp,-32` with ra at 28, s0 at 24 → the local area is 0..23 (24 bytes).

Hmm, and the plain version: ra at 20, s0 at 16 → the local area 0..15 (16 bytes).

Difference: 8 bytes. So the target's local area is 24 vs 16.

If the locals are v0, v1, pad (12 bytes) + address-taken pad → hmm.

Hmm! What if the *asm's* memory operand causes GCC to reserve space for the *address-taken* variable at a *specific* offset AND the register spill area grows? GCC's frame layout: [params][locals][spill area]. An address-taken local must be at a fixed offset. If GCC puts it at sp+0 and the spill area after, the total = 4 (pad) + 8 (spill for s0/ra?) hmm.

Let me try empirically: what if I make `pad` address-taken in real C? E.g.:
```
s32 *pp = &pad;   /* unused → removed */
```
Hmm, GCC removes it (the address is never used).

What if the address is *used* in a way that doesn't add instructions? e.g. `if (&pad == 0)`? That adds a compare (folded to false → but then the address is used → GCC might keep the local).

Hmm! What about `(void)&pad;` — GCC 2.7.2 might warn "statement with no effect" and remove it.

What about `pad = 0; &pad;`? Hmm.

What about making pad a *volatile* local? `volatile s32 pad;` → GCC allocates it in the frame (4 bytes) and the frame grows by 8 (alignment)? Hmm, but volatile is a barrier lever? Hmm, "volatile" on a local — the lever kinds are: pin, launder, barrier, keepalive. A volatile local is arguably a "barrier" (it forces memory ops). Hmm, but if the volatile local is never read/written, it just reserves space. Hmm, `volatile s32 pad;` with no accesses → GCC allocates the slot (since volatile vars are always allocated). That could give the frame.

Hmm! Let me test: variants with `volatile s32 pad;` and `s32 pad[2];` etc.

Hmm, wait. Let me reconsider: maybe the target's 24-byte local area comes from a *different* set of locals: e.g. the original source might have had 6 locals. The decompiler's `pad` was a placeholder for a *dead* local of some size.

The comment in the other function said: "s32 pad[4]; /* load-bearing dead local: reserves 16B var_size matching target's 0x28 frame */" — so the pattern is a dead local ARRAY of 4 s32 = 16 bytes, and the *frame* 0x28 = 40.

So for our item, the pad should be sized to give the target's frame. Let me compute what size gives a 32-byte frame: the local area must be 24 (with the frame = 8 + 24 = 32). The locals: v0(4) + v1(4) + pad(?) = 24 → pad = 16 bytes = s32 pad[4].

But my frmpad4 variant (pad[4]) scored 19 (no change) → GCC removed the unused array. Hmm! But the comment in the other function says a dead pad[4] DOES reserve 16B. Hmm, so an unused array *does* reserve space there. Why not here?

Hmm, maybe because in that other function the array was *address-taken* or something. Or maybe my frmpad4 variant didn't apply (the regex didn't match?). Let me check the generated file f09... hmm, in the framegen, the "arr" variants replaced `s32 pad;` with `s32 pad[3];` (3, not 4). And in variants.py, the frm variants used n in (2,3,4,6) → frmpad4 = pad[4]. It scored 19.

Let me look at the actual generated file to make sure the replacement happened. Let me check v09_frmpad4.c.

Also, maybe the frame *did* change but the score stayed 19 because other differences dominate (the score counts the whole diff). The frame difference would add to the score, not stay the same... unless the frame was already matching? No, plain has 24 vs the target's 32.

Let me look at the file and the residual.
