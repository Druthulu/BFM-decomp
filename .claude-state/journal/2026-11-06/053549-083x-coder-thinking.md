---
ts: 2026-11-06T12:35:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8hSZdDJI1Yf01uIkfwaD
---
In mine:
- The j==0 arm: 119 `addiu a0,t4,2` (var_v0_3 in a0!), 120-121 load b4b, 122 j, 123 li v0,4095 — the store `sh v0,0(at)` for the if-arm is MISSING (only the else arm has it at 129). So the if-arm's `D_801152AA = 0xFFF;` store is gone — merged with the else arm's store?? That can't be semantically right... unless gcc put the store in the join using a conditional move? No.

Hmm, look: mine 122 j b74, 123 li v0,4095 (delay slot). Then at the join... where does `sh v0,0(at)` happen for the 0xFFF case? Not visible at 124-130 (the else arm has its own at 129). Hmm, maybe the if-arm jumps to a label where the store is at 129? No, 129 is in the else path.

Hold on: 122 `j b74` jumps to +0x200 = index 128! So the if-arm jumps to 128 (`lui at,0x0`) and then executes 129 `sh v0,0(at)` with v0 = 4095 (set in the delay slot at 123). And the else arm falls through 124-129 with v0 = -4095.

So gcc merged the two stores: the if-arm jumps to the else arm's store! That's cross-jumping (jump2). Target keeps them separate (the barrier prevents it).

So the barrier prevents jump2 cross-jumping the arms. Real-C: hard. But maybe I can prevent the merge by making the arms differ: e.g. store `var_v0_3` in each arm too (store-per-arm) — then the arms aren't byte-identical.

Hmm, target: if-arm: `lui v1; lw v1; lui at; sh v0,0(at); j b84; addiu v0,t4,2` (delay slot). else: `lui v1; lw v1; li v0,-4095; lui at; sh v0,0(at); addiu v0,t4,-2`; then the join `sh v0,2(v1)` at 132.

Interesting: in the target the store of `b4b[1] = var_v0_3` (132) is in the else arm's tail (the join falls through from the else). And the if arm jumps to 132? `j b84` = +0x210 = index 132. Yes! Both paths converge at 132.

In mine: the if arm jumps to 128, both store at 129, then `sh a0,2(v1)` at 130 with a0 = var_v0_3 (computed in the arm since a0 is used in both).

So mine merged the constant store (jump2) and used a0 for var_v0_3.

To prevent the jump2 merge, make the two arms' tails differ: e.g. put `b4b[1] = var_v0_3;` inside each arm (store per arm!). Then the arms have different code... but the values differ anyway. Hmm, actually the arms' stores `D_801152AA = 0xFFF` vs `-0xFFF` differ only in the immediate — jump2 merges because the code is otherwise identical (li v0, imm; lui at; sh v0,0(at)).

If I add `b4b[1] = var_v0_3;` to each arm, the arms would each end with a different addiu (pos+2 vs pos-2) followed by the same sh — jump2 might still merge the tail.

Alternatively, write the if/else so the two arms differ structurally, e.g.:
```
if (arg1 & 1) {
    b4b = D_8017E918;
    D_801152AA = 0xFFF;
    b4b[1] = pos + 2;
} else {
    b4b = D_8017E918;
    D_801152AA = -0xFFF;
    b4b[1] = pos - 2;
}
```
That's store-per-arm — a known cracking move ("barrier->store per if-arm"). Let me try it.

Also note: the target has the store `sh v0,2(v1)` once (at 132, in the else tail). So the target does NOT duplicate the b4b store. Hmm, but jump2 might re-merge it.

Let me try several barrier variants:
1. store-per-arm for b4b[1].
2. keep b4b[1] shared but write the constant differently in the arms (e.g. `D_801152AA = 0xFFF;` vs `D_801152AA = -0xFFF;` → maybe `= 0 - 0xFFF`?).
3. reorder: put `b4b = D_8017E918;` outside the if (it's identical in both arms!) — target has `lui v1; lw v1` in BOTH arms, so it stays in the arms. Interesting: hoisting it out would change the code. But wait, in the C it's duplicated in both arms; if I hoist it before the if, the code would have one load. Target has two. So keep.

Let me also handle the launder (2) and keepalive (3).

Launder: `__asm__("" : "=r"(a1v) : "0"(arg1));` = a1v = arg1 with a1v pinned to $5. Removing it → `a1v = arg1;` = 2 (REG-caller). Real-C alternative: use `arg1` directly instead of a1v? Then a1v would disappear — but a1v is pinned to $5 and used in `if (!(a1v & 1))`. If I replace all a1v uses with arg1, the pin would be unused. Hmm.

Let me look at the diff for l0 (2, REG-caller) and k0 (3, REG-caller).

Given time (~07:25, item 4 at ~10 min), let me be efficient: test the barrier store-per-arm and the keepalive/launder variants in one batch.

For the keepalive `"r"(pos)`: extends pos's live range to line 83. Real-C: pos is used at line 31 (`pos = arg2`) and lines 75/80 (`var_v0_3 = pos + 2`). The asm at 83 is after the if/else. Real-C: use pos later, e.g. write `b4b[1] = var_v0_3;` using pos... Actually maybe restructure: `b4b[1] = (arg1 & 1) ? pos + 2 : pos - 2;`? That changes the code.

Alternative: move the `b4b[1] = var_v0_3;` statement to use pos directly: `b4b[1] = (arg1 & 1) ? pos + 2 : pos - 2;` — the arms would change.

Let me first check the diffs for l0 and k0 to see what's actually wrong (2 and 3 are small).
