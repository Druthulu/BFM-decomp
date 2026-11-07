---
ts: 2026-11-06T11:51:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kRZJMLiEN9pT4YxlSdiw
---
The key line: "Don't enter a bit-field in the hash table because the value in it after the store may not equal what was stored, due to truncation." — for ZERO_EXTRACT/SIGN_EXTRACT destinations, cse invalidates but doesn't record the value. But that's for bit-fields, not QI stores from SI subregs.

Hmm, but here's the thing: storing `(subreg:QI (reg:SI))` to `(mem:QI)` — the value IS truncated (only the low byte). cse records it. The load then gets `(subreg:QI (reg:SI))`. Correct.

So to prevent forwarding, I need the store destination to be a ZERO_EXTRACT/SIGN_EXTRACT — a bit-field! If the original stored through a **bit-field** of width 8, cse would not record the value.

Interesting! What if the original code used a struct with a bit-field? E.g.:
```
struct S { unsigned f : 8; ... };
((struct S *)arg0)->f = temp_v0;
temp_v0 = ((struct S *)arg0)->f;
```
But a bit-field store would generate `sb` too (for an 8-bit field aligned to a byte). And the load would be `lbu`. And cse wouldn't forward!

But the address: `((struct S*)arg0)->f` at offset 6 with an 8-bit field → sb offset 6. And the reload → lbu offset 6. That could work!

But would the rest of the function use bit-fields? The other fields (offset 5, 0x10, 0xC, etc.) would need struct access too, or I can mix. The constraint is "no signature or decl change outside the body" — a local struct typedef inside the body is allowed (it's within the body).

But is using a bit-field a "lever"? It's real C; the original game code might have used bitfields. Hmm, but it might be considered a trick rather than "real C moves". The allowed moves: "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse". Bit-fields aren't listed. But "no new lever of any kind" refers to compiler-steering levers (pins, barriers, launders, keepalive). A bit-field is a data-structure choice, arguably real C. Risky.

Let me first test whether it even works. If it produces score 0, I'll consider whether it's acceptable.

Actually, wait. There might be a simpler way: make the store destination a `ZERO_EXTRACT` by using a bit-field. Let me test.

But before that, let me check: is the load `lbu` from a bit-field? Loading an 8-bit bit-field → lbu + shift/and. If the field is exactly 8 bits at byte offset 6 with no bit offset, the load is lbu and the value is already 0..255, so no extra shift. Let me test.

Let me write w7 with a struct:
```
struct B { u8 a; u8 b; u8 c; u8 d; u8 e; u8 f; u8 g; ... };
```
Actually simpler: define a struct with fields at offsets 5 and 6:
```
struct S { u8 pad0[5]; u8 f5; u8 f6; };
```
But the target's `p[5]` and `p[6]` are u8. The struct approach: `((struct S*)arg0)->f5`, `->f6`. Then cse wouldn't forward the f6 store (if bit-field). But a plain u8 field is not a bit-field; cse forwards.

To make it a bit-field: `unsigned f6 : 8;`. Let me test whether a bit-field store to a byte-aligned 8-bit field gives sb and blocks cse.

Hmm, but then the other accesses (p[5], p[1], p[8], p+0x10 etc.) would still be pointer-based. Mixing is fine.

Let me write w7:
```
struct B { unsigned char f5; unsigned char f6 : 8; };
...
((struct B *)arg0)->f6 = (u8)temp_v0;
temp_v0 = ((struct B *)arg0)->f6;
```
Wait, struct B with f5 at offset 0, f6 at offset 1 — not offset 5/6. I need padding. Let me define:
```
struct B { u8 pad[5]; u8 f5; unsigned f6 : 8; };
```
Then f5 at offset 5, f6 at offset 6.

But `unsigned f6 : 8` — the underlying type unsigned int, 8 bits at offset 6 (byte-aligned). Store → sb. Load → lbu (maybe with andi 0xff if the compiler thinks the upper bits might be set; but lbu zero-extends, so no andi).

Let me test.

Actually, hold on. Let me reconsider the problem from the "what's the original" angle. The header comment says these are shared bodies from the original game. The original 1998 C almost certainly used plain pointer casts like `*(u8 *)((u8 *)arg0 + 6)`, not bit-fields. So the barrier was needed because the decompiler's reconstruction differs from the original in some way.

Hmm, but the task is to find a lever-free body that scores 0. Any real C is fair game. Bit-fields are real C. But is it "a new lever"? The brief's lever list: "pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm". A bit-field is none of those. And the C0505 catalog lists moves "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse" — bit-fields not listed, but the list may not be exhaustive.

Let me test it first; if it works, I'll decide.

Let me also think of another non-lever way: use a **union** with a bit-field? Same.

Let me test w7.
