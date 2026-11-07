---
ts: 2026-11-06T12:31:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cAb52Gt8wgRgVSOH98XV
---
Levers:
- pin: `register s32 ret __asm__("$2")` — pins the return value to $2. This is the "expand-void-return"/"return in $2" family. Here the function is s32 and returns ret; without the pin, the return value would be allocated somewhere else, and the target has `move v0,ret` at the return.

The wall notes (moves.md 302-311) for keepalive,pin said "expand-void-return — void def drops rv; keepalive keeps it live but global-alloc gives $3 not $2; pin $2 needs a real return". Here we have a REAL return (s32), so the pin should be removable more easily: if ret is the return value, global-alloc usually assigns v0.

Wait, but the pin exists because... maybe because ret is used in multiple places (the goto STORE and returns), and global alloc gave it another reg. Let's just remove the pin and see.

- barrier: `__asm__ volatile("")` at line 85 (after the unk20+4 store) and `__asm__ volatile("" ::: "memory")` at 112.
- keepalive: the asm at 129 with "r"(idx) merged into the memory barrier.

Plan c1: remove pin, replace line 112 barrier with nothing (but then the keepalive asm at 129 needs to become a plain `__asm__ volatile("" ::: "memory")`? No — all asm must go).

So c1: remove all asm; the idx ref-count lever needs a real C replacement. The note says idx needs +1 ref so local-alloc gives it $v0 (pri 16000 vs 6666). Lever-free: add a real use of idx, e.g. `tmp2 = D_801ED5EC[idx * 2];` using idx instead of the reload `unk10A` — but the target uses the reload for tmp2 (a second load from unk10A). Hmm, the target loads unk10A again (that's the `((Unkstruct...)->unk10A * 2)` in tmp2).

Lever-free ways to add a ref to idx: e.g. write `idx` in an expression that generates no extra insn. Options:
- `((Unkstruct_800B5CB8 *)param_1)->unk10A = idx;` then use `idx` in tmp1 and tmp2? That would change the code (removing the reload) — target has the reload.
- Declare idx at block scope and add a second statement using idx that folds away... e.g. `u16 idx = D_801ED4B4[i70a]; ... ((...)->unk10A = idx;` then `tmp1 = D_801ED5F0[idx * 2];` — that's what it does.

The +1 ref needs to come from somewhere real. What about making idx `s16`/`u16` conversions? Ref counts count reg uses in RTL. `idx * 2` where idx is u16 → the extension might be folded.

Ideas: change `u16 idx` to `s16 idx`? That could change sign extension insns.

Or: use idx in a second real place that gcc can't eliminate, like `D_801F32D0 = 0;` no.

Alternatively, maybe the priority issue disappears entirely once the pin is gone (different allocation). Let me just test c1 = no pin, no asm at all, see the score and residual.

Let me build c1.
