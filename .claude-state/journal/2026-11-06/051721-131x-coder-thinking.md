---
ts: 2026-11-06T12:17:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5aiDOpOuL0qpZzxoGQGy
---
w5 = 35 (worse, 66 insns). The launders without pins add an instruction.

Hmm. So the pins are needed for `out` to be t0.

Let me think about how to get `out` in t0 without a pin.

The target: `move t0,a2` in the delay slot of beqz. So `out = arg2` is a real copy, and out lives in t0.

Without the pin, out coalesces with a2. To prevent coalescing, I need a conflict between out and arg2, or make out's register choice different.

Real C ideas:
1. Make `arg2` used after `out = arg2`, so out can't coalesce? arg2 isn't used after.
2. Make `out` assigned from something else first. E.g., `out = 0;` before the if — adds code.
3. Use `out` in both branches (already).
4. Make `out` a different type: `u16 *out` instead of `s16*`? The stores are sh; the type might not matter.

Hmm, what if `out` is assigned `arg2` inside each branch (as now) and the compiler still coalesces.

What if the copy is `out = (s16 *)arg2;` — same.

What if I make `out` used before the branch: e.g., `out = arg2;` moved outside the if (before the branch)? Then `out = arg2` would be before the beqz, and out lives across both branches. The compiler might still coalesce with a2 (arg2 is dead after). But maybe not, because out is live across the branch and a2 might be clobbered... no, a2 isn't clobbered.

Actually, in the target, `out = arg2` appears in the delay slot AFTER the beqz, i.e., it's in the "then" path? No — a delay slot executes regardless. The move t0,a2 is shared by both branches (the compiler hoisted the common `out = arg2`). So the source has `out = arg2` in both branches, and the compiler merged them into one move in the delay slot.

Hmm.

What if the source has `out = arg2` ONCE before the if? Then the compiler would emit it before the branch, and maybe coalesce. Let me test: move `out = arg2;` before the `if`, remove it from both branches.

Let me test that (with pins removed).

Also, maybe `w` in $2: the pin `w asm("$2")` forces w to v0. Without it, w might go elsewhere. In w4, the diff showed `lw a0,0(a1)` vs target `lw v0,0(a1)` — w in a0 instead of v0. So the w pin also matters.

Hmm, so both pins are needed. This is looking like a WALL/PARTIAL.

Let me check: can `w` naturally be v0? w = *(u32*)p, used in t4/t5 computations. In the target, w is v0. Without the pin, w is a0.

Hmm.

Given the pins are a kind for this item, and they're needed, this is likely a WALL or PARTIAL:pin.

But wait — PARTIAL would be win.c scoring 0 keeping only the pin kind. That's w3 (score 0, pins kept, keepalive/launders removed, volatile pad). But w3 uses volatile, which is a NEW lever (not in the kinds). Hmm, that would be a PARTIAL:pin + volatile, which isn't "keeping only those levers".

Actually, w3's lever inventory: pins (kind pin, allowed in a PARTIAL:pin), volatile pad (a new lever). So w3 isn't a clean PARTIAL:pin.

I need the frame without volatile. Let me think again.

The frame: `addiu sp,-8` / `addiu sp,8`. Caused by `pad` being addressable. Real C: take the address of pad and use it in a way that requires the address but emits no code.

Ideas:
- `s32 pad; pad = (s32)&pad;` → sw (1 extra).
- `s32 pad; if (&pad == (s32*)arg0) ...` → the comparison is real (beq) — adds code.
- `s32 pad; *(s32*)&pad = 0;` → sw.
- `s32 pad; func(&pad)` → call.

Hmm, none emit zero code.

What if pad is a **struct** whose address is taken? Same.

What if the frame comes from something else: e.g., an `alloca(0)`? A call to alloca.

What about a variable-length array of size 0? no.

Hmm, what if I make the function have a local that's spilled due to register pressure? With the pins removed, there are 65 insns and enough registers. The frame wouldn't appear.

What if I add a local that must be memory-resident for a real reason, like a `jmp_buf`? no.

OK, so the frame needs the keepalive (an asm taking &pad) or volatile.

Hmm, is `volatile` really forbidden? Let me re-read the brief: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."

"no new lever of any kind" — volatile is a lever (it forces memory access/ordering). So adding volatile is forbidden.

So the frame must come from real C. Hmm.

Wait — maybe I can force a stack frame by making a local genuinely used in a way that the target also has? The target has NO stack accesses. So any real use would add instructions.

Unless... the target's frame is from the `pad` slot that the ORIGINAL source had for a different reason. Hmm.

Actually, let me reconsider: maybe the frame can be forced by declaring a local that's large enough to require the stack but unused? Unused locals are eliminated.

What about `register s32 pad;`? no frame.

Hmm, what if I use a local `struct` return value? no.

What if the function has a local `s32 pad[2];` and I take `sizeof`? folded.

Hmm.

Let me look at this from a different angle: maybe the pins can be removed and the frame forced by a different real-C structure that the target's compiler produced. But the target is fixed; we need to match it.

Let me check if maybe the `pad` frame is NOT from pad but from something else. The target's frame is 8 bytes. With the keepalive `"r"(&pad)`, gcc allocates pad to the stack. The frame is 8 bytes (2 words? no, 8 bytes = 2 words, but pad is 4 bytes; alignment to 8).

Hmm, why 8 and not 4? MIPS stack alignment is 8.

Could the frame come from the `w` pin? No.

Let me test: what if I remove the keepalive but keep `pad` used in a real but code-free way? Let me try `pad = pad;` — gcc might keep the store? Let me test a few forms:
- `s32 pad; pad = pad;` 
- `s32 pad; (void)&pad;` (cast to void — folded, but does taking the address force addressability? gcc might optimize it away entirely)
- `s32 pad; if (&pad != 0) {}` — folded.

Let me test `(void)&pad;` — the address is taken but discarded. Does gcc keep the stack slot? Probably optimizes the whole thing away.

Let me test.

Also, maybe I can force the frame by making the function's `pad` a parameter? No, signature change.

Let me test a batch of pad forms.
