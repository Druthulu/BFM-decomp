---
ts: 2026-11-06T12:16:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_12x2UPbPrG3XYv1uRRWc
---
Target: `addiu sp,sp,-8` at the start and `addiu sp,sp,8` at the end. The `pad` slot is never accessed.

Mine (w1) is identical except the frame.

So I need to force an 8-byte stack frame without adding memory accesses.

Idea: `s32 pad;` and use `&pad` in a way that's optimized but forces addressability. E.g., `pad = (s32)&pad;`? That would store (sw).

Idea: declare `pad` and make it `volatile` — the compiler might allocate it. Let me test if it emits the frame without accesses. Actually, an unused volatile local: gcc might not allocate it at all (it's never referenced). If referenced, it would emit lw/sw.

Idea: make the function's local `pad` a `register` variable? No frame.

Idea: use a local array `s32 pad[2];` unused → removed.

Idea: `s32 pad; ... func(&pad)` — a call would add code.

Hmm. What if the function has a **variable-sized** local? no.

What if I add a `s16 *out` pointer that's spilled? In the target, `out` is in $8 (pinned, saved? $8 is a0... wait, $8 = t0). The pin is `out asm("$8")` = t0. Target uses t0 as out. No spill.

Hmm.

What if the frame is caused by the `arg2`/`out` needing a save? No.

The frame is 8 bytes = one word (aligned to 8). It's for `pad`.

Real C to force a stack slot without instructions: 
- `s32 pad; pad = 0;` → sw (1 extra insn).
- Take the address and pass to an asm — that's the keepalive (forbidden).
- `volatile s32 pad;` and never use → probably no allocation.

Hmm, what about making `pad` a `register` that's addressable? No.

What about a local variable whose address is used in a comparison that's optimized away? E.g., `if (&pad == 0) ...` — folded.

What if `pad` is used in a real but cheap way, e.g., `pad = arg2 == arg2;` → li/sw (2 insns). No.

Hmm, what if the frame comes from a **jump table**? No.

What if the original function had a local that was genuinely spilled but the spill was optimized away? 

Let me reconsider: maybe the frame can be created by an unrelated real need. For instance, if the function had a call with 4+ args (stack args). No.

Or if a local needed 8-byte alignment for a `double`/`long long`? An unused `double` → removed.

Hmm, what about `s32 pad[2];` with `pad[0] = 0;`? Adds sw.

Let me test a few:
- volatile s32 pad (unused)
- s32 pad; pad = (s32)&pad; (adds sw)
- s32 pad; if (&pad) {} (folded)
- use `&pad` in a self-assignment: `pad = pad;` (folded, maybe forces addressability? no)
- declare `s32 pad; pad = arg1;` then use pad? adds code.

Let me test volatile first.

Actually — maybe a cleaner idea: make `pad` an **array** and use `sizeof`? no.

Let me test `volatile s32 pad;` unused.

Also, another thought: the frame might be reproducible by making the function `inline`-less with a local `struct` that's returned? no.

Let me test a batch.

But also: the pins still need to go (kinds include pin). Let me check what removing the pins does. Let me create w2 = orig minus keepalive, launders, AND pins.

Actually, let me first see if the pins matter at all. Let me test w2 (no pins, keepalive/launders removed).

Let me generate w2 and w3 (volatile pad).
