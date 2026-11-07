---
ts: 2026-11-06T12:16:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4yk7ZkQjHud9Zv98j3aQ
---
The only difference: the target has `addiu sp,sp,-8` at the start and `addiu sp,sp,8` at the end — a stack frame of 8 bytes! Mine has no stack frame (63 insns vs 65).

The `s32 pad;` variable and the keepalive `__asm__("" :: "r"(&pad))` forced a stack slot for `pad` (hence the 8-byte frame). Removing the keepalive, `pad` is unused, so no stack slot.

So the keepalive's effect: allocate `pad` on the stack (addiu sp,-8 ... addiu sp,8).

To reproduce the stack frame without the keepalive, I need `pad` to be actually used/stored on the stack. But adding a real use would change the code.

Hmm. The target's frame is just `addiu sp,-8` at the start and `addiu sp,8` at the end, with no store/load of pad. So `pad` is allocated to the stack but never accessed? That's what the keepalive `"r"(&pad)` does: it takes the address of pad, forcing it to be addressable (stack), but the asm doesn't use the address (empty template).

Without the keepalive, pad is unused → no frame.

Real C ways to force a stack frame without using pad:
- Take the address of pad and pass it somewhere that doesn't emit code? No.
- Declare a variable and use it in a way that requires the stack.

Hmm, what if I make `pad` actually used, e.g., `pad = arg0;` — that would store to the stack (sw) and add instructions. The target has no sw for pad.

What if the function needs a stack frame for another reason? E.g., a call with stack args. No calls here.

Hmm. The `addiu sp,-8`/`addiu sp,8` is purely from `pad` being addressable.

Real C: `&pad` used in a real operation. For example, `pad = (s32)&pad;`? That stores to pad (sw). Not matching.

What if pad is a `struct` or array whose address is taken but not used? The compiler would remove it.

Hmm. What about `alloca`? No.

Let me think: gcc allocates a stack frame if the function has any addressable locals or spills. With `pad` unused, nothing.

Could I make the function have a stack frame via a different mechanism that doesn't add instructions? For example, a large local array that's unused → optimized away. A local whose address is taken and passed to a call → call.

Hmm.

What if I make `pad` a `volatile` variable? A volatile local would be stack-allocated (addressable), and if never accessed, maybe no instructions but a frame? Let me test: `volatile s32 pad;` — would gcc allocate it? If it's never used, it might still allocate the stack slot (volatile objects are addressable). Let me test.

But volatile is a lever (barrier-ish)? The kinds are keepalive,launder,pin. A volatile local isn't a "barrier" in the pin/asm sense... but "no new lever of any kind" — volatile is a compiler-steering lever. Risky.

Hmm. Let me first test if `volatile s32 pad;` gives the frame.

Actually, wait: maybe the original source had a real use of pad that the target shows? The target has no store to the stack. So pad is allocated but unused. That means the original had something like `s32 pad; ... (&pad)` — but the original 1998 code wouldn't have an unused address-taken variable.

Hmm, actually the decompiler added `pad` and the keepalive to force the frame. The original C might have had a stack-allocated temporary that got optimized out but still reserved the frame? Unlikely.

Wait — maybe the frame comes from a different cause: the function might have a `jump` table or a register spill. Let me look at the target asm around the start.

Let me view the target.
