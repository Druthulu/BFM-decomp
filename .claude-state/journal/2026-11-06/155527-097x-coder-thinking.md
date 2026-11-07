---
ts: 2026-11-06T22:55:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_N1ljRh9YYKHIylOoLhYJ
---
global_conflicts() first, then expand_preferences(). So the conflicts are valid.

Let me look at the w0 preference chain with actual debugging: maybe I can use gdb? Too heavy.

Alternatively, let me just try to directly test whether removing the a1 preference helps by changing the source so d isn't copied from $a1. 

Idea: make arg1 be used before d = arg1, so the copy source is... no.

Idea: assign d from a global variable? No.

Idea: `d = arg1;` → `d = arg1, 0;`? Comma operator: `d = (arg1, 0)`? No.

Hmm.

Let me look at this from the "what does the original source look like" angle once more. The decomp's body has `d = arg1;` and the target has `move $16,$5` at entry. The original probably had `s32 d = arg1;`. Same RTL.

Hmm, but the original's allocation gave d=$s0. Our lever-free gives d=$s1. If the RTL is the same, the allocation must be the same. So the original's RTL must differ. 

What if the original had the variables declared in a different ORDER, which changes the pseudo numbering? The pseudo numbers affect the tie-breaks (lower allocno wins)! In global.c:607, ties are broken by the allocno number. If the original's pseudo numbering differed, the tie between d and u6 could break differently, and the preference chains differ!

THAT'S IT! The pseudo numbering depends on the declaration order / source structure. If d and s1ang's pseudo numbers are swapped, the "lower allocno wins" tie-break flips.

In w0: d = r74, s1ang = r75, u6 = r77. The .greg order for the 10000 tie: 74 (d) before 77 (u6). d wins $s0? But d conflicts $s0 (local r75) so it doesn't matter.

Hmm, but the local r75 is the blocker, not a tie.

Hmm.

OK, but the declaration order could matter for the preference chains. Let me try reordering the declarations and see.

Actually, I did w22 (w6 decl reorder) = 38, same.

Let me try more declaration orders and initializations. Let me also try declaring the variables in the order the target might have (u5, u6, iVar4, q, t, d, s1ang).

Actually, let me think about the *pseudo numbering* effect on the local-alloc: local-alloc's qty order is by priority, not number. The r75 (s1ang) vs r72 (arg0) order: r72 has higher priority (13333 vs 2857) so it's allocated first. r72 takes $v0 (or $a0). r75 takes $s0. The pseudo number doesn't matter for local-alloc's reg choice (it uses the reg_alloc_order).

Hmm.

OK, let me try the C0505 "pointer reuse" and "loop shape" moves, plus a few type/order variants, and then wall it.

Let me do a final batch of 8 tries:
- w26: w0 with `d = arg1 + 0;`
- w27: w0 with declarations: `s32 s1ang; s32 d;`
- w28: w0 with `u5` declared as s32 and the others...
- w29: w6 with `d` declared before s1ang AND `d = arg1` (same as w6).
- w30: w6 with the pointer load hoisted: `s32 p = *(s32 *)(arg0 + 0x20);` before d.
- w31: w6 with the cast do-while separate and the mask inside a do-while in the arms.
- w32: w0 with the cast via two statements `d = d << 16; d = d >> 16;` — wait, that's an arithmetic shift on a signed value; `d <<= 16; d >>= 16;` changes semantics (d could be negative; >> on signed is implementation-defined but gcc does arithmetic). The target has sll/sra. Let me try.
- w33: w6 with `q`/`t` scoping.

Let me write and score them.

Actually, let me prioritize: the C0535 do-while on the div block is a known crack for the sibling. In our function, w20 (w0 + div do-while) = 38, same as w0. Hmm.

Let me try the div do-while + mask-in-place + cast do-while = w9 (38).

Let me try w0 with the *cast* done as two statements (sll/sra):
```
d = d << 16;
d = d >> 16;
```
This avoids the extendhisi2 temp (in-place), which was the sibling's residual. Let me test w26.

And w27: w6 with the cast as two statements (in-place).

Let me write them.
