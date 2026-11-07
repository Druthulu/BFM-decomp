---
ts: 2026-11-06T12:52:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hmORMyxH5j80xkaMjQwc
---
Now I see the structure: at 5e0 `j 62c` with delay `addiu v0,v0,-2` — that's the arm0 jump to 62c which is the sh. And the else arm falls through from 5e8 to 610, then 614-628, then falls into 62c. So 62c (the sh) is the JOIN block: both arms jump/fall to it. So the sh IS in a separate basic block from the lui/ori? No — the join block starts at 62c and continues through 630 (lui) etc. So sh and lui are in the same BB (the join block).

So sched1 scheduled the join block: source order is sh, then *(u32*)out=0x04000000, sb 0x78, sw 0x4, sh 0xE, lw/lw, ... In target the order is sh, lui, ori, lui 0x400, sw 0(s0), li 120, sb, li 4056, sw -14(a1), sh -4(a1)...

Interesting: target's join block order is exactly source order! sh(0xA) first, then 0x400 store, 0x78 sb, 0x4056 sh, ... wait, the source order is:
1. sh 0xA = y
2. *(u32*)out = 0x04000000      → sw v0,0(s0)
3. out[0xC] = 0x78              → sb v0,-6(a1)
4. *(u32*)(out+4) = 0x64808080  → sw v1,-14(a1)
5. sh 0xE = 0x4056              → sh v0,-4(a1)

Target order: sh(141), lui 0x6480(142), ori(143), lui 0x400(144), sw 0(s0)(145), li 120(146), sb(147), li 4056(148), sw -14(a1)(149), sh -4(a1)(150).

So the constant for #4 (lui/ori) was hoisted above #2 and #3 (to fill the load delay of the lhu? no, there's no delay). It's the only reordering: the lui/ori pair moved up to just after the sh.

And in mine, the lui/ori moved up one more slot, above the sh.

So the residual is: mine hoisted lui/ori one insn too early (above the sh), target kept it after the sh.

Since all priorities are 1, the tie-break is the ready list. Hmm, the target has the lui/ori immediately after the sh — maybe the target's sched is also driven by something else.

Since the difference is exactly one position, maybe a simple real-C change in *statement order* fixes it. What if I move the y store statement after the 0x400 store in source? No — target order is sh first.

What if I move the 0x4 store earlier in source (right after the y store)? Then source: sh y; sw 0x4; sw 0(s0); sb 0x78; sh 0xE. That changes the target order (target has sw 0(s0) before sw -14). But sched might reorder anyway.

Alternatively: think about what determines the order in the ready list. In backward sched, insns are added to the ready list when their dependents have all been scheduled. The initial ready set = insns with no successors (the last insns). Then it picks by priority, ties broken by list order (which is by decreasing uid? or increasing?).

`ready` list: `make_ready_list` walks the insns from the end backward and adds those with no deps. So the last insn is added first. Then scheduling picks `ready[0]` (highest priority; for ties, the first in the array, i.e., the one added earliest = latest in source order).

So at the moment both the sh and the lui/ori are ready, the one later in source (lui/ori? no...) Hmm: in source, the sh comes before the lui/ori. The ready list adds later-source insns first. So the lui/ori (later in source) would be picked before the sh → the lui/ori gets scheduled to a *later* position (backward scheduling: picked first = placed last). That's what target does? Target places lui/ori after the sh (later). Yes! Target: sh at 141, lui/ori at 142-143. So target picks lui/ori first (placing them later).

Mine picks sh first (placing it later, at 143). So mine's ready-list order differs: the sh became ready before the lui/ori.

Why? Because the sh's dependents: nothing. The lui/ori's dependents: the sw at -14(a1) which must be scheduled first. So initially the lui/ori are NOT ready (they depend on the sw being scheduled? no — LOG_LINKS are predecessors; readiness is about successors). Hmm, in backward scheduling, an insn is ready when all its *successors* (users) have been scheduled.

The lui feeds ori feeds sw. The sw (a store) has no successors → ready initially. The sh has no successors → ready initially. So both the sw and sh are ready at the start. Then which is picked first? The one added first to the ready list = the later in source. The sh (source pos 1) vs sw -14(a1) (source pos 4): the sw is later in source → added first → picked first → placed last. Then the ori becomes ready (its only successor sw scheduled) and is added... 

Then eventually when both sh and lui/ori are ready, the order determines. Ugh, too deep.

Empirical route: try real-C variants that change the structure:
(a) Move the y store's value into the store directly per arm (no y temp).
(b) Use a temp for the constant: `u32 k = 0x64808080;` declared in the block (birth after the sh in source).
(c) Reorder the statements: put the 0x4 store before the 0x78 sb.
(d) Put the whole tail in a do-while.
(e) Change y to s16 vs s32 (already s16).

Let me try (b) first — a named constant temp. If the temp is born between the sh and the sw in source, and local-alloc gives it a register, the sched may treat it differently. Actually a constant temp would be cse'd/folded back into the store as an immediate (the target has lui/ori into v1). Hmm.

(f) What about making the 0x64808080 store use a *variable* that is computed from something already live, e.g. `mhi`? No.

(g) What if the y store is moved into the if/else arms? Let's try that — it's a documented move for barrier cracking. But it changes the CFG (two sh). jump2 might cross-jump them (the arms are otherwise different). Actually the two arms end differently (different j targets), so cross-jump wouldn't merge the sh. Then we'd get two sh instructions → 204 ins → wrong.

Hmm, but maybe the *join block* would then start at 62c with the lui/ori and the sh would be at the end of each arm. Target has one sh at the join. So no.

(h) What about making the y store's address depend on y? no.

(i) What if we make the 0x64808080 constant build depend on y? e.g. store `(0x64808080 | (y & 0))`? Identity — forbidden.

(j) Reorder: `*(s16 *)((u8 *)out + 0xA) = y;` then `*(u32 *)out = 0x04000000;` — what if we swap these two in source? Target has sh then sw 0(s0). Source order would be sw then sh; sched might swap back? Unlikely.

Let me try (b), (c), (d), and also (k): declare the y store's value as a variable used twice? no.

(l) Use `u16` for the y store: `*(u16 *)((u8 *)out + 0xA) = y;` — y is s16, the store is sh either way.

(m) Make `y` a u16 and store... same.

Let me also try (n): put the 0x64808080 store's constant in a variable declared at the top of the loop body, e.g. `s32 m24v = 0x64808080;`... no, that's a new variable that could be pinned? Not a pin, just C. Let's see what happens.

Actually, wait. There's a much more promising idea: the residual is a single insn moved up by one. The target keeps lui/ori after the sh. What if the sh were *dependent* on the lhu's value AND the lui/ori dependent on... hmm.

Alternatively — what if I make the two statements adjacent in a way that gcc emits them in one "store group"? No.

Let me look at the existing moves for "ORDER" residuals in this shape: e.g. "sched1-birth-order" (T11 G16b func_801372B0): "sched1 orders two independent insn births opposite to source; reorder moves the other". And "func_80180F68 WALL sched1-birth-order — ... residual is sched putting lui v0,0x20 (unk14) before li a0,2432 (call arg) — target reverses them".

Also, from item 1's success: do-while worked there. Here v1/v2 (do-while) didn't change anything. Let me check if v1 is even different from w0 in output (score 2 same). Probably identical output.

Let me try a broader set: 
- v6: y store uses a direct expression per arm? no.
- v7: swap the 0x400 store and the 0x78 sb in source.
- v8: swap the y store and the 0x400 store.
- v9: constant in a local var `u32 c64 = 0x64808080;` before the y store.
- v10: constant var after the y store.
- v11: `*(u32 *)((u8 *)out + 0x4) = 0x64800000 + 0x8080;` (constant folding → same).
- v12: declare `s16 y2 = y;` and store y2.

Also consider: maybe the target's join block order is exactly "source order with the constant pair hoisted to the top of the block". The pair is hoisted because... it's the only multi-insn constant. If instead the constant were a single `li` (small value) it wouldn't matter.

Hmm, what if I make the 0x64808080 store be a *block move* of 4 bytes from a static u32? No, that'd be a lw.

Let me just try the batch.
