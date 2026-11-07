---
ts: 2026-11-06T10:21:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_K4qvGjXOY3U3tQcoIizg
---
With the keepalive, the only residual is the div sign-ext temp: mine `sll v1,s0,0x10; sra s0,v1,0x10` vs target `sll s0,s0,0x10; sra s0,s0,0x10`.

So the sign-extension of the divisor uses a temp v1 instead of in-place. This is because div is a pseudo and gcc's sign-extension pattern creates a temp. With the pin (hard reg s0), the sll could be in-place.

How to get the in-place sign-extension with real C? 

The sign-extension `div = (s16)div` compiles to `sll temp,div,16; sra div,temp,16`. The temp is a new pseudo. If the temp could be allocated to the same register as div (s0), then `sll s0,s0,16; sra s0,s0,16`. 

Why is the temp in v1? Because local-alloc gave the temp v1 (caller-saved) — the temp is short-lived (dies at the sra). local-alloc assigns it the first free reg, v1 (v0 is busy with the call result).

To make the temp get s0, we'd need... hmm. The temp and div are connected by a copy-like relation (sll temp,div then sra div,temp). local-alloc's combine_regs might tie them if the sll's dest and source could be the same. For a sign-extension, the MIPS `extendhisi2` pattern might be `(set (match_operand 0) (sign_extend (match_operand 1)))` with a temp. 

Alternatively, use a different C spelling for the sign extension that produces in-place code. E.g., `div = div << 16; div = div >> 16;` (explicit shifts). The `div <<= 16` → `sll div,div,16` (in-place!). Then `div >>= 16` → `sra div,div,16` (in-place). But div is a pseudo; the sll would be `sll div,div,16` in-place (same pseudo, no temp!). Let me test:

```
div = (s16)div;   →   div <<= 16; div >>= 16;
```
Wait, `div << 16` in C on a signed int is UB for overflow, but gcc handles it. `div = div << 16; div = div >> 16;` — the shift right of a signed value is arithmetic (sra). This should produce in-place shifts if div is a pseudo? Actually, the pseudo is the same register, so `sll div,div,16` is valid in-place. gcc's shift patterns allow in-place.

But careful: the target has `sll s0,s0,0x10; sra s0,s0,0x10`. If I write `div = div << 16; div = div >> 16;`, gcc might generate exactly that. Let me test.

But hold on — would that change the semantics? `(s16)div` sign-extends the low 16 bits. `div << 16 >> 16` does the same (arithmetic shift). Yes, equivalent.

Is this a "launder"? No, it's a real sign-extension spelling. But the brief says "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". Hmm! `div = div << 16; div = div >> 16;` is a sign-extension idiom, not an identity (it changes the value). `(w>>16<<16)|x` is an identity *when x is the original w*. Here `div << 16 >> 16` is NOT identity (it sign-extends, changing bits 16-31). So it's a legitimate width cast. The C0505 catalog includes "s16/u8 widths". OK.

Let me test: f3 = f2 with `div = (s16)div;` → `div = div << 16; div = div >> 16;`.

Actually, maybe simpler: `div = (s32)(s16)div;` — same as (s16)div. Let me try the explicit shifts.

Let me also consider: `div = div << 16 >> 16;` (one statement).

Let me test both.
