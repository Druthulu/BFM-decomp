---
ts: 2026-11-06T06:33:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mD7bwpeBcWEFVtcnfInO
---
Interesting. The target's structure:
- `mulc = D_80126950 * 48;` computed with sll/addu/sll (mulc in a1), then `mulc = mulc / (g.otz * 4)` → div, mflo a1.
- Then `lw a3, D_800A5E60` (pkt), `addiu v0,a3,40`, `sw v0,D_800A5E60`.
- `mulc` stays in a1 (which is `w` later? `w = mulc` at line 70). Hmm, target: at 6dc8 `move a2,a1` (in the beqz delay slot) — that's `w = mulc` (a2 = w). Then w2 = vv-0x100 or vv.

So the target keeps mulc in a1 across the pkt stores, then moves it to a2 (w) at 6dc8.

Without the launder, gcc probably does something else.

The launder `"=m"(D_800A5E60) : "r"(mulc)` forces:
1. mulc in a register at that point.
2. A memory write to D_800A5E60 before the load.

A real-C replacement: maybe `D_800A5E60 = D_800A5E60;`? That's a load + store to the same location — the compiler might keep both (a store of the loaded value). Actually it would emit `lw v0,D_800A5E60; sw v0,D_800A5E60` — 2 insns, not matching (the target has just `lw a3; addiu; sw`).

Hmm. What about `pkt = D_800A5E60; D_800A5E60 = pkt + 0x28;` — that's exactly lines 55-56. So the launder is only there to force ordering/regalloc.

What does the target's code actually need?
- `lw a3,0(D_800A5E60)` — a3 = pkt (note: pkt in a3! and arg3 is also a3? no, arg3 is a3 in the prologue... wait, `lw v0,0(a3)` at the start was arg3. Later a3 is reused for pkt — the args are dead by then).
- `addiu v0,a3,40; sw v0,0(at)`.
- Then `sb v0,3(a3)` etc.

So the load of D_800A5E60 happens AFTER the division. In w0, where does it happen? The diff showed mine[159] `lw v1,0(a3)` vs target `lw a0,0(a3)` — a register difference, and mine[163] `lw a0,20(sp)` vs `lw v1,20(sp)`.

So in w0, the load of D_800A5E60 happens at the same place but with different registers. The diff is mostly registers.

w0 score 68 with 192 ins vs 197 — 5 insns missing. Let me see the beginning of the diff (the first lines). The dt.sh output tail showed only the last 40 lines. Let me get the first part.

Actually the dt.sh prints the diff tail; I asked for 40 lines and got the end. Let me use `--explain`-like output... but --explain works on the tree. Hmm, dt.sh just tails. Let me run with a bigger tail and look at the start: `| head -40` on the dt output gives the FIRST lines of the tail. I did `head -50` on the 40-tail. Let me run with tail 200 and head.

Actually, the output I got started at mine[111]. So there are earlier diffs. Let me get the full diff by using tail 200 | head -60.
