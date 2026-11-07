---
ts: 2026-11-06T20:52:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_N1ahAj8ek23BTOU2VhLy
---
vAQ's code is EXACTLY the target in the ent region: `ed4c move a0,s0`, `ed50 sh v0,6(s0)`, `ed58 lw v1,196(a0)`, `ed5c sh v0,10(a0)`, etc.

So the copy IS right! The only difference is the frame size (48 vs 40) — an extra 8 bytes of stack.

Why did the frame grow? The expression `(v[0] ^ v[0]) & 1` must have created a stack temp (gcc allocates a temp slot for a non-folded expression, then combine folds it, but the frame was already sized? No — the frame size is computed later by reload/global-alloc based on actual stack usage).

Hmm, maybe the `v[0] ^ v[0]` expression caused gcc to allocate a temporary stack slot during expansion (a `save_expr`?) that wasn't reused.

If I can get the same copy effect without the stack temp, I'd match.

The copy: `ent = a0 + <expr that gcc folds to 0 but not before expand>`. The key is that the ADD survives expansion (a real PLUS rtx), then combine/cse folds the zero later? Wait, if the add is folded by combine, we'd be back to a copy. But the code shows `move a0,s0` = `addu a0,s0,$0` — a real add with $0. So the expression `(v[0]^v[0])&1` was folded to 0 at some point, and the add `a0 + 0` became `addu a0,s0,$0`... which is what gcc emits for `(set reg (plus reg (const 0)))`? Actually, gcc's addsi3 with a constant 0 would normally be simplified to a move by combine. But here the result is `addu a0,s0,$0` — the MIPS `movsi` pattern is `addu rd,rs,$0`! So a plain copy also emits `addu rd,rs,$0`.

Wait — so the instruction is the same for a copy. The difference is that the copy SURVIVED (wasn't propagated).

Why did it survive in vAQ? Because the ADD `a0 + expr` was a real PLUS at the time of cse/combine, and the expression `(v[0]^v[0])&1` was folded to 0 by... the add became `a0 + 0`, which combine then simplified to a move but the *pseudo* ent remained a distinct pseudo (the add's dest). Since it was an add (not a copy), cse/combine didn't propagate it.

Then why did the frame grow by 8? Probably the `v[0] ^ v[0]` expression created a temporary during expansion (a stack slot for the subexpression?).

Let me find an expression that (a) is a real PLUS at expand time, (b) folds to 0 later, and (c) doesn't allocate a stack temp.

Ideas:
- `(s32)((u32)a0 + (u32)(v[0] - v[0]))` — v[0]-v[0] uses a load; the compiler may create a temp.
- `(s32)a0 + (s32)(v[0] & 0)` — `& 0` is folded immediately (tree-level) → no add.
- `(s32)a0 + (s32)(v[0] * 0)` — folded.
- `(s32)a0 + (s32)(v[0] - v[0])` — not folded at tree level (x - x is not folded by the C front end? gcc might fold it in fold()). Hmm.
- `(s32)a0 + (s32)(v[0] ^ v[0])` — same.

The stack temp: maybe it's because `v` is an array and `v[0] ^ v[0]` is computed... hmm.

Alternatively, use a *global* or a parameter: `(s32)a0 + (s32)(arg - arg)` where arg is another parameter — no parameters. Use a local scalar: `v2 - v2`? v2 is uninitialized.

What about `(s32)a0 + (s32)(bx - bx)` where bx is a variable? There's no bx here. But there are locals: v0, v1 (s32), v[4], out[4]. Using `v0 - v0`: v0 is a local (s32) holding the first call's result. At the point of the copy, v0 is still live? Let me check: v0 = func_8012C1B8(); unk20 = v0; if (v0 == 0) ...; so v0 is dead after the if? It's used at the top only. Using `v0 - v0` at the copy point would make v0 live again → it would need to be kept in a register across the calls (it's dead now, so it might not be available).

Hmm.

What about `(s32)a0 + (s32)(v[1] - v[1])`? v[1] is loaded at that point.

The stack temp might come from the *expression evaluation* creating a temp for the subexpression `(v[0]^v[0])&1`. Let me test simpler forms and check the frame:
- vAT: `(s32)a0 + (s32)(v[0] - v[0])`
- vAU: `(s32)a0 + (s32)(v[0] ^ v[0])`
- vAV: `(s32)a0 + (s32)(v[0] & 0)` (folds)
- vAW: `(s32)a0 + (s32)(v[0] == v[0] ? 0 : 1)` — hmm.

Let me test vAT and vAU and see the frame.

Actually, wait: the frame grew by 8 bytes. The function's declared locals total 40 bytes (frame 0x28=40). An extra 8 bytes suggests a compiler temp for a *non-folded* expression that required a stack slot (maybe a `SAVE_EXPR` or a temp for `v[0] ^ v[0]` evaluated twice?). 

Hmm, `v[0] ^ v[0]`: the compiler loads v[0] twice? That's 2 loads + xor + andi + addu = 5 insns, but the insn count is the same (69), so it must have folded.

Let me look at the vAQ disassembly at the copy point: `ed48 lhu v0,16(sp)` (v[0]) and `ed4c move a0,s0`. So the v[0] load is the normal one; no extra insns. The expression was folded entirely. But the frame still grew — maybe because during expansion gcc allocated a stack temp for the `&` expression (e.g., `expand_binop` needed a temp) and never freed it.

Hmm, if the expression was folded at tree level (before RTL), no temp would be allocated. But the frame grew, so something happened.

Maybe the frame growth comes from `v[0]` being used in a *non-lvalue* context requiring an address? The array v is on the stack; `v[0] ^ v[0]` loads from sp+16. That shouldn't add a temp.

Let me just test variants and check the frame. Let me test:
- vAT: `(s32)a0 + (s32)(v[0] - v[0])`
- vAU: `(s32)a0 + (s32)(v[0] ^ v[0])`
- vAV: `(s32)a0 + (s32)(v[0] * 0)` 
- vAW: `(s32)a0 + (s32)(v[0] & 0)`

Score each and look at the frame (the score's first diff line shows the frame).

This is promising! If one keeps the copy and the frame at 40, it's a MATCH.
