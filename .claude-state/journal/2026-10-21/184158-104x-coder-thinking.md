---
ts: 2026-10-22T00:41:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AW7jzJK5syhV09fJOR1s
---
func_8017D9D8 is the same pattern as func_8017EF0C (item 5): the `__asm__ volatile("" : "=r"(v0) : "0"(v0), "m"(pad));` lever.

The "cast" variant (v03_cast0s16 = `v0 = (s16)v0;`) scored 7 (vs 19 for plain). Let me look at the residual for that variant to see what's left.

Note: `v0 = (s16)v0;` is a real set (a truncation) — it's in the C0505 catalog ("s16/u8 widths"). But careful: is it semantically faithful? v0 = CAST_SIGN(s16, a0, 0xFC) → the value is in [-32768, 32767]; (s16)v0 is a no-op numerically. So yes, faithful.

Let me look at the residual of v03_cast0s16 for func_8017D9D8.

Also the "m"(pad) frame effect: the variants frmpad2/3/4/6 (pad as an array) scored 19 (same as plain) → the frame didn't change? Hmm, because the asm (which references pad) was removed → pad is unused → not allocated → the frame stays. Hmm, so the frame effect requires the asm's "m" input. To keep the frame without the asm, I need the pad local to be *address-taken* in real C.

Hmm! How about: `pad` is used in a real way that forces it into memory. E.g. `pad = v0;`? A dead store → GCC removes it (no slot). Hmm. What if pad is *read* from an unknown place? no.

What about taking the address of pad and passing it to a function? e.g. `func_8002D4C8(...)` — no.

Hmm, what if the *frame* is padded by a different mechanism: e.g. an unused local *array* — GCC removes unused locals entirely? Let me check: in the plain variant, the frame was 24 (vs the target's 32). The locals are v0, v1, pad (4 each). Hmm, 24 - 8 (ra+s0) = 16 bytes of local area. So the locals DID take 16 bytes (rounded from 12). So unused locals DO get frame space in this GCC (var_size). And pad as an array of 4 (16 bytes) → the local area would be 4+4+16 = 24 → the frame = 32! But the frmpad4 variant scored 19 — same as plain. Hmm, so the frame didn't change? Maybe because GCC *removed* the unused array (an unused local array might be dropped, unlike a scalar?). Hmm, or maybe the score didn't capture the frame difference... the frame difference is part of the instruction diff (addiu sp,sp,-N), so it would show.

Let me check the residual of a frmpad variant vs plain. Hmm, let me instead check the residual for v03_cast0s16 (score 7) — it will show what remains (frame? register?).

Let me run it.
