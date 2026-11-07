---
ts: 2026-11-06T09:13:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aIk9QvAKWo5v9TrmDsa5
---
Confirmed: for a void function, `return expr;` just expands the expression for side effects then null return. So no v0.

So all "value in v0" cases can only be matched with a pin (register-asm), a signature change (forbidden), or... hmm, what if the function returns a *struct*? no.

BUT: here's a thought — what if we make the value live in v0 via a real C construct that uses v0 as an argument to an asm... that's a lever.

What if the last statement is a call to a function whose *argument* is the value, and the argument happens to be passed in... no, args are a0-a3.

What if the value is the return of a call? E.g. `found = func(...)` returns in v0; if found's last assignment is a call result and then found is dead... flow deletes? No — the call's return in v0 is an instruction we can't remove; if found is unused, the call still emits `jal`, and v0 holds the result. Hmm, but the target's `move v0,s2` is a move, not a call.

OK so realistically items 1,2,4,5 are expand-void-return walls unless the value can be routed to v0 by a real return... which needs signature change.

Wait — maybe I'm wrong about "signature change forbidden" for these items. Let me re-read the constraint: "no signature or decl change outside the body (callers stay as they are)". For item 1, line 146's extern void is a decl outside the body → can't change. But maybe the *definition* could be `s32` if we also... no.

Hmm, but consider item 2: the extern for func_801F0C4C at line 426 is `extern void func_801F0C4C();` — a K&R no-prototype declaration! A K&R `extern void f();` still declares void return. Conflict.

What about item 4: TU's extern is `extern void func_80180A54(void *a0, s32 a1, s32 a2);` at 4055.

Item 5: `extern void func_80183E68(...)` at 7168, 7320, 7354.

So all conflict.

Hmm, hold on. What about declaring the *definition* with the same void return but using a *second* function definition with a different name and an asm label? Like `s32 foo(...) __asm__("func_800CD5CC");` — a separate declaration with an asm label that gives the function a second name. Then define `s32 foo(void*) __asm__("func_800CD5CC")`? GCC would emit the symbol func_800CD5CC with s32 return, while the void extern refers to the same symbol name. Would GCC detect conflicting types? The declaration `extern void func_800CD5CC(void*)` and `s32 func_800CD5CC(void*) __asm__("...")` — different identifiers (foo vs func_800CD5CC) mapping to the same asm name. GCC doesn't check asm-name collisions. So:

```c
s32 f800CD5CC(void *arg0) __asm__("func_800CD5CC");
s32 f800CD5CC(void *arg0) { ... return found; }
```

This would emit the symbol `func_800CD5CC` with a s32 return, while line 146's `extern void func_800CD5CC` is a separate identifier? No wait, the extern at 146 IS the identifier func_800CD5CC. Our definition uses identifier f800CD5CC with asm name func_800CD5CC. The two identifiers coexist; the assembler symbol is the same → duplicate symbol? No, only one definition. Callers calling `func_800CD5CC` (the void one) resolve to the same asm symbol. This is the "asm-label alias" idiom the project already uses (`extern u16 aB9A02[1] __asm__("D_800B9A02")` in the worked example — and the note says "Kept the TU-idiom extern asm-label alias ... (symbol name, not a codegen lever; was in orig body)").

But wait, would the definition emit the symbol name func_800CD5CC and would that be a byte-identical object? The object would have func_800CD5CC defined with s32 return semantics (move v0,s2). The rest of the TU's calls to func_800CD5CC compile as void calls (no return use) — same code. The object should be identical except the function body now has the move. That's exactly the target!

Is this allowed? "no signature or decl change outside the body (callers stay as they are)" — callers stay. The body file contains a *new* declaration with an asm label; that's inside the body file. Hmm, but is this a "new lever of any kind"? The brief says lever-free = none of the row kinds remain: no pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind.

An asm-label alias for the symbol name — is that a lever? The worked example explicitly says "the TU-idiom extern asm-label alias ... (symbol name, not a codegen lever; was in orig body)". So symbol-name asm labels are not codegen levers. Here I'd introduce a NEW one (not in orig body) to rename the function for the purpose of changing its return type while keeping callers' void decl. Hmm, that's arguably a trick, not a real-C move, and it IS a decl change (the definition's signature). The constraint "no signature change outside the body" — this signature is in the body file... but the effect is a signature change of the function (return type s32). The brief's "no signature or decl change outside the body (callers stay as they are)" seems aimed at allowing body-only edits; changing the function's return type is a signature change of the function itself, which callers in other TUs rely on. Even if callers stay as they are in this TU, other TUs may call it. The object comparison is only this TU though.

Risky. It's likely considered a "new lever" (asm label to dodge a type conflict). Hmm.

Actually wait. Let me reconsider. Is there a legitimate way? What about the *function's own* return type matching the caller's use: the TU's extern void is used at line 111 with implicit... no.

Let me look at how the project handled this in G24 for func_800CD494 (same wall, same TU): "a dead for-loop use reaches 0 but is a new lever (G24)". So they accepted it as a WALL.

Given the shard is explicitly a "singleton crack shard" for keepalive,pin items, maybe the point is to find real cracks for the ones that can be cracked (item 3?) and record walls for the rest. But the WALL rules (≥20 min, ≥30 tries) would make 5 items take 2.5 hours. Hmm.

Wait, let me reconsider: maybe for some of these the pin is removable and the target doesn't actually need v0. E.g., item 2: maybe without the pin, res gets a different reg but the keepalive keeps it, and with real-C moves (e.g., pointer reuse, decl order) the allocation matches a callee-saved reg? No — target has res in v0 (pinned). Without pin, v0 is caller-saved and a value live across calls can't be in v0. res is assigned 0 at Lcont (after all calls?) — let me check: res=0 after func_801F0E9C() call, then flg=D_801F84AC, if flg res=&D_801F832C, then keepalive. No calls between res's set and the keepalive. So res could live in v0 naturally if... local-alloc gives caller-saved v0 to a pseudo live only in the tail. But v0 is also the return register — with a void function, v0 is free. Hmm! Actually local-alloc assigns v0 to block-local pseudos preferentially (the note in item 4 says expand...). Let me just test item 2's lever-free body — maybe it already scores 0!

That's the key: some of these pins may be removable because the value naturally lands in v0 (local-alloc gives v0 to a pseudo that's born and dies in one block). Let me test each.

Let me extract each def to orig.c and make a lever-free win.c, score them. Start with item 2.

Item 2 def lines 367-423. Let me extract.
