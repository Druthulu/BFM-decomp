---
ts: 2026-10-22T00:38:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_83KabG8DEEDNWX1hzIxD
---
Item 5 (func_8017EF0C): the lever is:
```
__asm__ volatile("" : "=r"(v0) : "0"(v0), "m"(pad));
```
This is a "REFUSED launder with 2 inputs" — a volatile asm with an output tied to the input v0 and a memory input "m"(pad). The "m"(pad) input makes it a *memory* reference (pad is a local!) → the asm forces `pad` to be *addressed* (it's in the frame) and forces the asm to be kept (volatile).

So this lever does two things: (a) makes v0 opaque, (b) forces the local `pad` to have an address (i.e. the frame must reserve space for it) — the "pad" local is a *frame pad*!

Interesting: `s32 pad;` is an uninitialized local whose only purpose is to reserve stack space. The asm's "m"(pad) input forces the compiler to allocate stack space for pad → the frame size changes (e.g. 8 → 16 bytes) → the target's frame matches.

So the lever's effect includes the *frame size*. Without it, `pad` is unused → no stack slot → a smaller frame → different prologue!

The residual: mine 49 vs target 50 — 1 instruction. Probably the frame adjustment (`addiu sp,sp,-N` with a different N, or an extra stack save).

So the plain-C way: make `pad` a real local that occupies stack space! E.g. `s32 pad;` → if the compiler doesn't allocate it, we need something that forces the allocation. Options:
- Make pad *addressable* in real C: e.g. `pad = 0;`? A dead store — GCC removes it (no stack slot).
- Use pad in a real way: e.g. `v0 = pad + something`? changes semantics.
- Take the address of pad: `&pad` — GCC would then allocate the slot (the address is taken → the variable is address-taken → it gets a stack slot). But taking the address without using it → GCC's "unused variable" analysis might still remove it. Hmm: `s32 *p = &pad;` unused → GCC removes it (the address is never used). Hmm.

Let me look at the target asm for this function to see what the frame looks like and where the extra instruction is.

Let me check the residual details for c1 of this item.

Let me look at the target asm and my c1's asm.

Actually, let me first check the residual (score 19 = COUNT; mine 49, target 50). Let me see the diff.
