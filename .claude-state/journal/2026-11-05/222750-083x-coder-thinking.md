---
ts: 2026-11-06T05:27:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lI4uI0Mkbqz2seAfwG3Z
---
Now I can see the target structure. The key differences:

1. Early exit: target has `bnez v0, 5f3c` (branch into the body when < 0x4001) and falls through to `j 5fe8; move v0,zero`. Mine has `beqz v0, 5f98` (branch to a shared return-0 block). So in the target, the `return 0` after the >0x4000 check is a *separate* `j 5fe8` to the epilogue with `move v0,zero`, whereas mine merges it with the default `return 0` at 5f98 (shared). The asm barrier prevented jump2/cross-jump from merging them.

2. The `hit:` block: target `5fd8 jal func_80178BF8; 5fe0 lui v0, func_80172710; ... 5fe8 epilogue`. Mine: `5fd0 jal; 5fd8 lui v0; 5fe0 epilogue`. Same.

3. Target `case 2` (`beq v1,v0,5f90` with v0=2): `5f90 lhu v1,52(a0); 5f98 beq v1,v0,5fb8` — wait, v0 was set to 2 at 5f5c. Then `5f90 lhu v1,52(a0)`, `5f98 beq v1,v0,5fb8` (v0=2? no, v0 is 2). Hmm, at 5f60 `beq v1,v0` with v0=2 jumps to 5f90. At 5f90, `lhu v1,52(a0)`, `5f98 beq v1,v0,5fb8` — v0 is still 2! So `if (*(u16*)(p+0x34) != 1) return 0;` — hmm, the source case 2 checks `!= 1`. But the asm compares with v0=2? That seems wrong... wait, let me re-read: at 5f5c `li v0,2`; 5f60 `beq v1,v0,5f90` (case 2 → 5f90). At 5f90 `lhu v1,52(a0)` (p+0x34), `5f98 beq v1,v0,5fb8` where v0=2? That would be `if (p->0x34 == 2) goto hit`. But source says case 2: `if (*(u16*)(p+0x34) != 1) return 0;`. Hmm, v0 might have been reloaded. Actually at 5f5c `li v0,2`, and the case-2 target 5f90. Hmm, maybe the compiler reused v0=1? No. Let me not worry.

Wait, actually looking more carefully: at 5f5c `li v0,2`; 5f60 `beq v1,v0,5f90` — so case 2 → 5f90. Then 5f64 `li v0,1`; 5f68 `j 5fe8; move v0,zero` (default). So at 5f90, v0=2 (from 5f5c). `5f98 beq v1,v0,5fb8` → if (p+0x34 == 2) goto hit. But the source says `if (*(u16*)(p+0x34) != 1) return 0;` → `beq v1, 1, hit`. So v0 should be 1! 

Hmm, maybe the target's `li v0,2` at 5f5c is for the case-3 comparison at 5f50? Let me re-trace:
- 5f44 lhu a1,2(a0)  → st = p->0x2
- 5f4c andi v1,a1,0xffff
- 5f50 beq v1,v0,5f84  → v0=3 (li v0,3 at 5f30) → case 3 → 5f84
- 5f54 slti v0,v1,4
- 5f58 beqz v0,5f70  → if st >= 4 goto 5f70
- 5f5c li v0,2
- 5f60 beq v1,v0,5f90 → case 2 → 5f90
- 5f64 li v0,1
- 5f68 j 5fe8; move v0,zero → default return 0
- 5f70 li v0,4
- 5f74 beq v1,v0,5fa8 → case 4 → 5fa8
- 5f78 move v0,zero
- 5f7c j 5fe8
- 5f84 li v0,8
- 5f88 j 5fd8; 5f8c sh v0,2(a0) → case 3 body: p->0x2 = 8; goto after (5fd8 = func_80178BF8 call)
- 5f90 (case 2) lhu v1,52(a0)
- 5f94 nop
- 5f98 beq v1,v0,5fb8 → v0=2 here! So `if (p->0x34 == 2) goto hit`?? But source case 2: `if (*(u16*)(p+0x34) != 1) return 0;`

Hmm, that means v0 is NOT 2 at 5f90. Wait, maybe the `li v0,2` at 5f5c is dead and the real value is 1 from... no, 5f64 `li v0,1` executes before the branch to 5f90? No: 5f60 `beq v1,v0,5f90` branches at 5f60; the delay slot is 5f64 `li v0,1`! MIPS delayed branch: the instruction at 5f64 is the delay slot of the branch at 5f60. So when the branch is taken, v0=1. So at 5f90, v0=1 → `beq v1,1,5fb8` = `if (p->0x34 == 1) goto hit`. Correct!

OK. So the target's branch structure differs from mine in the early-exit and the case-4 block:
- mine: `5f68 li v0,4; 5f6c beq v1,v0,5fa0; 5f70 move v0,zero; 5f74 j 5fe0` and case 2: `5f88 lhu v1,52(a0); 5f90 beq v1,v0,5fb0; 5f94 nop; 5f98 j 5fe0; 5f9c move v0,zero`.
- target: `5f70 li v0,4; 5f74 beq v1,v0,5fa8; 5f78 move v0,zero; 5f7c j 5fe8` and case 2: `5f90 lhu v1,52(a0); 5f98 beq v1,v0,5fb8; 5f9c move v0,zero; 5fa0 j 5fe8`.

The differences are the placement of `move v0,zero` relative to `j` (delay slot) and the jump targets. In the target, `move v0,zero` is in the *branch delay slot* of `beq v1,v0` (5f98/5f9c), then `j 5fe8` (5fa0). In mine, it's `beq ...; nop; j; move v0,zero`.

So the target fills the delay slot with `move v0,zero` (the return value) while mine puts `nop` there and `move v0,zero` in the j delay slot.

This is the `jump2-crossjump-arms` / reorg delay-slot difference. The empty volatile asm is placed right after the early-return `if` in the source, which prevents cross-jumping.

Now, can a real C move reproduce this? The barrier is `__asm__ __volatile__("")` — an empty volatile asm with NO memory clobber and no operands. Its only effect is to be an insn that scheduling/jump passes won't move. It does NOT create a frame (no clobber). Its purpose is to block cross-jumping/merging of the `return 0` blocks.

In pure C, can we prevent cross-jump? Cross-jump merges byte-identical blocks. The target has *different* code, so maybe the source structure differs: e.g., writing the early return as `if (x > 0x4000) { return 0; }` (as now) vs `if (x <= 0x4000) { body } return 0;` changes the CFG and jump threading.

Let me try restructuring item 5:
Variant A: invert the condition and wrap the body:
```
if (func(...) <= 0x4000) {
   ... body ...
   func_80178BF8();
   return (s32)func_80172710;
}
return 0;
```
Hmm, but the target has `return 0` after the check as a separate block. In the target, the `>0x4000` path jumps to the epilogue with v0=0, and the final `return 0` (default) jumps to the same epilogue. Actually the target's early-exit is `bnez v0, 5f3c` (skip) then `j 5fe8; move v0,zero`. And the default is `j 5fe8; move v0,zero` at 5f68. Both are `j 5fe8` + `move v0,zero`. Wait, at 5f34: `j 5fe8` (0x080017fa) and 5f38 `move v0,zero`. At 5f68: `j 5fe8` and 5f6c `move v0,zero`. At 5fa0: `j 5fe8` and 5fa4 `nop` (hmm, delay slot nop) — because the branch at 5f98 has the delay slot `move v0,zero` at 5f9c, so 5fa0's j delay is nop.

Hmm, this is a reorg delay-slot-fill difference. This might be the `dbr-delay-fill` wall or `jump2-crossjump-fallthrough`.

Let me think about what pure-C change could produce the target: the target's `beq v1,v0` at 5f98 with delay `move v0,zero` means the register allocator assigned v0 as the return value and the delay-slot filler (reorg) put the `move v0,zero` there because it's on the fall-through path to `j 5fe8`.

In mine, `move v0,zero` ended up in the j delay slot instead. That's a scheduling difference caused by the asm barrier.

Could restructuring the switch (e.g., if/else instead of switch, or reordering cases) fix it? Let me try a bunch of variants.

OK. Given the scale, let me set up an efficient candidate scoring pipeline. Each sc.sh call spawns Python + compile (~1-3 s). 30 candidates = ~1-2 min. Fine.

Let me now:
1. Item 5: try ~30 real-C variants (restructure early return, switch→if chains, goto shapes, return 0 spellings).
2. Item 1: try ~30 variants.
3. Family: ~30 variants each.

Let me start with item 5, since it's closest (score 10) and has no frame artifact.

For item 5, candidate moves:
A. Invert early return: `if (func(...) <= 0x4000) { ...body...; func_80178BF8(); return (s32)func_80172710; } return 0;`
B. Use `s32 rv = func_8012BD14(...); if (rv <= 0x4000) {...}`
C. Restructure switch into if/else if.
D. Case 3 body: `p->2 = 8; break;` — target `li v0,8; j; sh`. 
E. Change the `goto hit` label placement.
F. Make `return 0` a single exit at the end.
G. Use `st` variable for p->0x2.
H. Reorder cases 2/4.
I. Use a `s32 ret = 0;` variable.
J. etc.

Let me write these variants as files and score them. I'll write a script that takes a list of (name, body) and writes them, then run sc.sh on all.

Actually, the item body is a full definition (with externs). Let me create variants via a Python generator that takes the orig body text and applies textual transformations. Since I need to try many, let me write them explicitly in a Python file.

Let me first check how fast a score is.
