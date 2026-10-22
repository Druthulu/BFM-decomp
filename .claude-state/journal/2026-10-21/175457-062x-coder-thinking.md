---
ts: 2026-10-21T23:54:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_qusLQtlOCevICcaeb3jw
---
KEY INSIGHT from find_best_addr: it looks up the address in the cse hash table and, if a cheaper equivalent exists (e.g. a REG), it REPLACES the address with that REG.

"CONSTANT_ADDRESS_P (addr) → return" — so a constant address (like (plus (symbol_ref) (const 0))) is NOT replaced. Hmm! So a MEM with a constant address is left alone. Hmm, but the doc row 6 said "an address in the table is replaced by the cheapest equivalent" — the address here is a symbol_ref (not CONSTANT_ADDRESS_P? hmm, (symbol_ref) alone is not a CONSTANT_ADDRESS_P; a CONSTANT_ADDRESS_P is (plus (symbol_ref) (const))).

So: for a MEM whose address is exactly `(symbol_ref D_800B99DC)` (no offset), find_best_addr would look it up in the cse table; if a REG with the same value is in the table (e.g. a pseudo holding the address), it would replace the MEM's address with that REG! And ADDRESS_COST(REG)=1 < SYMBOL_REF=2.

So: if the C has BOTH `p = &D_800B99DC;` (creating a pseudo/reg holding the address) AND a MEM `*(u16 *)&D_800B99DC` (a direct dereference of the global), then cse would replace the MEM's address with the reg holding the address.

And then the address pseudo (a REG) would be... hmm, that gives the MEM a reg base but doesn't create a copy.

Hmm. But the doc says the RESULT of that is "the pseudo then survives calls and crosses them in an $s-reg" — i.e., the address pseudo ends up in an $s reg. And the "la" (lui/addiu) pair would be materialized into it.

Hmm, so where does the extra `move s0,v0` come from then?!

AH, maybe: the address pseudo is in v0 (a caller-saved reg) for the MEM access, and then... no, the target has the load using s0.

Hmm hmm. OK, let me try to think about what gcc 2.7.2 does for `p = &D_800B99DC;` where p is a pseudo:
- expand: `(set (reg P) (plus (symbol_ref D_800B99DC) (const 0)))`? or `(set (reg P) (mem (symbol_ref)))`? Hmm, for `&global`, expand creates `(set P (symbol_ref D_800B99DC))`? I believe expand creates the address as a MEM-like: for `&x`, the value is the address → `(set P (plus (symbol_ref x) (const 0)))`? Hmm, actually gcc represents it as `(set P (symbol_ref x))`? I think for a global, `&x` expands to `(set P (symbol_ref x))`.

Then cse: P = (symbol_ref) → P's reg_equiv = (symbol_ref) → P is a "CONST" pseudo.
Then local-alloc: P is allocated s0 (it crosses calls) → but P's value is a constant → local-alloc might handle it as a "CONST" pseudo: in gcc 2.7.2's local-alloc, `reg_equiv` with a constant → the pseudo is put in a reg and reload materializes the constant into it: `lui s0; addiu s0,s0,0`.

Now, the TARGET has `lui v0; addiu v0,v0,0; move s0,v0`. So the target's s0 is NOT a CONST pseudo — it's a copy of a reg.

Hmm, so in the target, the value was in a reg v0 and copied.

I keep coming back to: the original compiler didn't coalesce. gcc-2.7.2 does.

Hmm, unless... the ORIGINAL game binary was compiled by a DIFFERENT compiler (the "psx" toolchain in the repo? tools/reference/psx_tomba? there's a "psx_tomba" reference dir!). Hmm.

OK. Time check: 17:46 was the start of item 2; now it's probably ~18:20. I'm way over budget on this item (8018483C). Let me time-box: 2 more experiments, then record a WALL.

EXPERIMENT 1 (v4): pointer reuse: pb = &D_801E87B2; q = pb; pb = &D_800B99DC; p = pb; r = &D_8018F078;
EXPERIMENT 2 (v8): the "declaration order / decl count" dial: maybe adding a decoy local changes the allocation. Hmm, no asm allowed. But adding an extra local variable (e.g. an unused one) could change the block's qty count → the 3-qty sort bug path → different allocation! Interesting: the preheader block might have exactly 3 qtys (q, p, r + s4 + i...). Adding a 4th local could change the order. But the copy isn't about order.

Hmm.

EXPERIMENT 3: what if the *p&1 load is written to force a MEM with a symbol address: e.g. `D_801E86BC = (*(u16 *)&D_800B99DC & 1) + 3;` — then cse's find_best_addr would replace the MEM's address with the REG holding the address (p's reg or a new pseudo). And the copy? Hmm.

Hmm, hold on, hold on! Let me re-read the doc row 6 once more:

"| 6 | **Give the address a pointer local used ≥2× in one EBB, or remove it** (`p = &D_x; … p->f … p->g`) | cse (`find_best_addr`) → global | `cse.c:2622-2700`: an address in the table is replaced by the cheapest equivalent — `ADDRESS_COST(REG)=1` (`mips.h:2895`) vs `SYMBOL_REF` = 2 unless `SYMBOL_REF_FLAG` (`mips.c:1600-1620`) → every `(mem (symbol))` in the EBB becomes `(mem (reg))`; the pseudo then survives calls (`invalidate_for_call` kills hard regs only, `cse.c:1725`) and crosses them in an $s-reg | One `la $sN,SYM` + `lw 0($sN)` per use vs a macro `lw $r,SYM` per use: the count differs by 1 per shared address and the $s-bank grows (§153's symptom; `cse_expr.md` §2/§3). **Kill it with the §373 dead-reset or the §153 launder; create it with a pointer local / a second `&SYM` argument in the same EBB.**"

"create it with a pointer local / a second `&SYM` argument in the same EBB" — so this row is about the ADDRESS PSEUDO (a reg holding the address) appearing in the output. In the TARGET, we have `lui v0; addiu v0,v0,0; move s0,v0` — the address is in a reg (v0 → s0).

Hmm! So the target's shape = the address pseudo materialized in v0 and copied to s0? OR: the address pseudo IS v0 (the short-lived one) and s0 is a copy.

The doc says "the pseudo then survives calls and crosses them in an $s-reg" → the pseudo crosses calls in an $s-reg → the pseudo is s0. And the "la $sN,SYM" is the lui/addiu pair. So the target's `lui v0; addiu v0,v0,0; move s0,v0` = a "la" pair into v0 + a copy to s0. The doc's example "One `la $sN,SYM` + `lw 0($sN)` per use" suggests the la pair goes directly into the $s reg.

So the target has an EXTRA copy compared to the doc's description. Which is what the launder produced.

Hmm, so how did the launder produce `lui v0; addiu v0,v0,0; move s0,v0`?
- The asm forces the address into a reg (v0).
- Then p = pb (the asm output) → p is in s0 → `move s0,v0`.

And in the lever-free version, p = &D_800B99DC → p is a CONST pseudo → `lui s0; addiu s0,s0,0`.

So: we need p's value to be a REG (not a constant) → p = <something in a reg>.

**A REG!** What if the address is in a reg because it's the result of an ARITHMETIC expression? E.g. `p = (u16 *)((u8 *)&D_800B99DC + 0)` — folds. What about `p = (u16 *)((u32)&D_800B99DC + 0)`? On a 32-bit target, (u32)ptr is a no-op cast → folds to the same.

Hmm, what about a pointer difference: `p = (u16 *)((u8 *)&D_800B99DC - 0 + 0)`? folds.

What if the address is computed from a DIFFERENT symbol plus an offset? e.g. `p = (u16 *)((u8 *)&D_800B99D8 + 4)` — that would be a different reloc (D_800B99D8) → the masked diff compares reloc operands → mismatch. ✗

Hmm. What if the expression is `&D_800B99DC` but through a pointer-to-pointer cast? no.

**What if p's value is a reg because it's the result of a load?** Then the reloc would be a load. ✗

So: the ONLY way to have p's value be a reg is a copy from another pseudo that holds the address — and cse collapses that.

**UNLESS the other pseudo's value is a REG (not a constant)!** I.e., a chain: X = &D_800B99DC (X is CONST), Y = X (collapsed), ... collapses all the way.

Hmm, so the chain always collapses to the constant.

**BUT WAIT**: what if the copy's source is set to the address in a context where cse does NOT record the equivalence? cse's `record_cse` for a SET with a constant source: it records the reg_equiv (update_reg_equiv) only if the value is a "simple" rtx. It does.

Hmm, what if the SET is in a different basic block from the use? cse's forward scan is per-block, but the reg_equiv is global-ish (reg_equiv is per-register, invalidated per block?). Hmm! cse's `delete_reg_equiv` is called at block boundaries? In cse.c's `cse_basic_block`, at the end of a block, the equivs are flushed. And `update_stmt` (called from the RTL flow) invalidates.

So if the address assignment is in block A and the copy in block B, cse's per-block scan wouldn't forward the value! But the reg_equiv (set by local-alloc/global-alloc) hmm.

In gcc's flow, cse runs per basic block. The forward scan within a block records equivalences. Across blocks, the reg_equiv persists (it's a per-register array updated by `update_reg_equiv` in cse? no, reg_equiv is updated by local-alloc/global-alloc).

Hmm, actually `reg_equiv` is set in global.c's `global_alloc` (via `reg_equiv` chains) and in `allocate_reg`. And cse's `update_stmt` deletes reg_equivs when a pseudo is set.

Hmm! So the ORDER of passes: cse runs before local-alloc/global-alloc? The pass order in gcc 2.7.2: ... cse, ..., local_alloc, global_alloc, reload, ... So cse runs BEFORE the allocation. At cse time, reg_equiv is mostly empty (set by expand?). Hmm, but the cse forward scan within a block records the equivalence in the cse hash table (cse->equivs), which is per-block.

So: if `p = &D_800B99DC;` is in block A and `p2 = p;` is in block B, cse's block B scan wouldn't know p's value → the copy stays a copy → p2's value is a REG (p) → and then local-alloc allocates p (v0) and p2 (s0) → `lui v0; addiu v0,v0,0; move s0,v0`!!!

Hmm! But wait, p's value at block B: p = &D_800B99DC was set in block A; at block B, p's value is unknown to cse (the block's scan starts fresh) → so `p2 = p` is a real copy ✓. And p (the pseudo) is allocated a reg: p is live from block A to block B → it's an $s reg (crosses calls?) hmm, then p would be in an $s reg and the copy would be `move s1,s0` — the target has `move s0,v0` (v0 = caller-saved).

Hmm. Unless p is NOT live across a call: if the copy `p2 = p` happens in the SAME "region" without a call in between... but p is set in the preheader and p2 is used in the loop.

Hmm, hmm. But hold on: in the target, the copy is `move s0,v0` — the source v0 is caller-saved, so the source's live range does NOT cross a call. If p were set in the preheader and copied in the preheader, p's range is short → v0 ✓, and p2 = s0 (crossing calls) ✓.

So: the copy must be in the SAME basic block as the assignment, but the cse forward scan must not forward it. The forward scan doesn't forward when the source's value is not "known" in this scan — i.e. when the source was set BEFORE the block started? But then the source is live across blocks.

Hmm, wait, actually: cse's forward scan within a block starts by recording the equivalences from the block's live-in state? Hmm, in gcc's cse, at the start of a basic block, the table is empty (cse_basic_block starts fresh) — but there's `cse->equivs` handling with `init_cse`...

Hmm, but actually the important thing: cse's `record_cse` records a SET's destination value in the table, and a USE of that dest gets the value. If the dest was set in a previous block, cse's table (fresh per block) doesn't have it → no forwarding. But `canon_reg` and the reg_equiv chains might still allow the copy to be simplified by combine.

So: to get the copy, the source's set must be in a DIFFERENT basic block from the copy, and the source must be short-lived (not crossing a call) — impossible if the source is set in a previous block and the copy is in a later block (the source IS live across the block boundary, but maybe not across a CALL!).

In our function, the preheader is one block (0..30) and the loop body is another. If the assignment `p = &D_800B99DC;` is in the preheader and the copy in the LOOP body — then p is live across the loop (and across calls) → p would be an $s reg → the copy `move sX,sY` with both $s. ✗ (target: move s0,v0).

Hmm, but what if the assignment is in the loop body and the copy is ALSO in the loop body but in a different block? Hmm.

OK, alternative: what if the source is set in the same block but the copy is in a block where cse's scan is fresh — i.e. the copy is the FIRST statement of a new block, and the source's set is at the END of the previous block?

In our function: the preheader ends with the `D_801E86C0 = D_800B99D8;` statement, and the loop body starts. If `p = &D_800B99DC;` is the LAST statement of the preheader and the copy `p2 = p` is the FIRST statement of the loop body → different blocks! Then:
- p is live across the block boundary but NOT across a call (the call is inside the loop body, after the copy) → p gets a caller-saved reg (v0) ✓✓✓
- p2 (the copy) crosses calls → s0 ✓✓✓
- The materialization of p = &D_800B99DC happens in the preheader: `lui v0; addiu v0,v0,0` ✓ (v0 is p's reg)
- The copy at the loop top: `move s0,v0` ✓✓✓

THAT'S EXACTLY THE TARGET SHAPE!!! And the order: `lui v0; addiu v0,v0,0` at 17-18 and `move s0,v0` at 19 — hmm, but the copy would be at the loop top (insn 31+), not at 19. Hmm! The target has the move at 19, right after the materialization, BEFORE the other stuff.

Hmm. Unless the copy is in the same block but cse's scan...

Hmm, but actually gcc's scheduler can move the `move s0,v0` earlier — it's a register move with no dependencies; sched2 could hoist it into the preheader. Actually, the move must stay after the materialization (a data dependency), but it could be scheduled earlier than the other preheader statements. The target's insn 19 is right after 18 — so the move is immediately after the materialization. That's consistent with a copy placed at the loop top but SCHEDULED up into the preheader! (sched2 can move a move up as long as the deps allow.)

Hmm, interesting! But would it move it across the `lui s2` (r's materialization) and the `lhu v0,0(s0)`? The move s0,v0 has a dependency on v0 (the materialization) and defines s0. The `lhu v0,0(s0)` USES s0 → so the move must precede the load. It could be scheduled to just after the materialization. Plausible!

So the recipe:
```
    /* in the preheader, at the END: */
    p = &D_800B99DC;      /* the source: a pseudo in v0 */
    /* in the loop body, at the TOP: */
    p2 = p;               /* the copy → s0 */
```
Hmm, but wait: p would be live from the preheader's end into the loop body's top — but the loop's top block is the loop body, and p's live range crosses the block boundary but no call → p gets a caller-saved reg (v0) ✓.

But hold on: the LOOP is entered at the top (the loop body is the "latch" successor). The preheader is the block before the loop. Hmm, and the loop body's first block... the copy `p2 = p` at the top of the loop body. And p2 (s0) is used throughout the loop ✓.

Hmm, but the preheader's `D_801E86BC = (*p & 1) + 3;` uses p — which would be v0, not s0! The target has `lhu v0,0(s0)` — the load uses s0! ✗

Hmm!! So the preheader's load must use s0 (the copy's destination). That means the copy happened BEFORE the load in the preheader. So the copy is in the preheader, before the load.

So the copy is in the same block as the materialization... and cse's forward scan would forward it. ✗✗

UNLESS the source's set is in a DIFFERENT block that ends right before, and the copy+load are in the next block. E.g.:

block A: `p = &D_800B99DC;` (and other stuff)
block B (the preheader proper): `p2 = p; D_801E86BC = (*p2 & 1) + 3; ...`

For that, there must be a branch between the assignment and the copy. In our function, the `if (--D_801E86BC != 0) return;` is before. Hmm, the assignment is after that.

Hmm, what if the assignment is placed BEFORE the `if`? Then:
```
    p = &D_800B99DC;
    s4 = a0;
    if (--D_801E86BC != 0) return;
    ...
    p2 = p;   /* in the post-if block */
```
Hmm, but the target's preheader (after the early return) has the materialization at 17-19 — the early return is at 12-13. So the materialization is AFTER the early return. Hmm, but scheduling could move it? The materialization `lui v0` has no dependency on the branch, so sched2 could hoist it above the branch! Hmm, but it's after the `bnez` in the target (insn 17 vs the branch at 12) — the branch is at 12-13, so the materialization is after. If it were before the branch, the target would show it before. So it's after.

Hmm, so the materialization is in the post-if block and the copy is in the same block (insn 19, right after 18).

OK so both are in the same block. So cse's forward scan applies... and forwards. ✗

UNLESS: cse's forward scan does NOT forward because the source's value is a REG (not a constant)! I.e., the source pseudo's value is a REG. And the source pseudo's value is a REG because the source was itself copied from a constant in a different block...

AAAH. OK: consider a chain across blocks:
- block A: `x = &D_800B99DC;` → x's value = a constant (cse records it in block A's table)
- block B: `p = x;` → cse's block B table is fresh → x's value is not known → the copy p = x is a REAL COPY ✓ → p's value is a REG (x) → p is not a CONST pseudo → local-alloc: x → v0 (short-lived? x is live from block A to block B — no calls in between → v0 ✓), p → s0 (crosses calls) ✓ → `lui v0; addiu v0,v0,0` (in block A) + `move s0,v0` (in block B) ✓✓✓

And the preheader's load `*p` uses p (s0) ✓✓✓ — IF the load is in block B (after the copy).

So the structure needed:
- block A ends with `x = &D_800B99DC;` (or the assignment is in a block that ends before)
- block B starts with `p = x;` then `D_801E86BC = (*p & 1) + 3;` etc.

And the materialization would be in block A (before the branch) — but the target has it after the early-return branch. Hmm. Unless the block boundary is elsewhere.

Hmm! What about the LOOP? The preheader block ends and the loop body begins. If `x = &D_800B99DC;` is the LAST statement of the preheader and `p = x;` is the FIRST statement of the loop body, then:
- x is live across the block boundary, no call in between → x gets v0 ✓
- the materialization `lui v0; addiu v0,v0,0` is at the end of the preheader (insn 17-18 — hmm, the target has it at 17-18 and the copy at 19, both before the load at 22).

Hmm, the copy at 19 would be in the loop body block, but the target shows it at 19, before the preheader's other stuff (20-30). Scheduling could hoist the move up? The move defines s0, which is used by the load at 22. If the copy is in the loop body (after the preheader), the load at 22 (in the preheader) couldn't use s0! ✗

So the load `*p` at 22 uses s0 → the copy must precede it → the copy is in the preheader.

So we need a block boundary INSIDE the preheader, between the materialization and the copy. What could create a block boundary there? A conditional! The preheader has `if (--D_801E86BC != 0) return;` — that's BEFORE.

Hmm, what if the C has an additional `if` that creates a boundary? That would change the control flow. ✗

Hmm, what about the LOOP's preheader: gcc's loop.c creates the preheader as a separate block! And the loop body is a separate block. So the boundary is between the preheader and the loop body. The target's insns 0..30 = the preheader, 31..96 = the loop body.

So: if `x = &D_800B99DC;` is in the preheader and `p = x;` is at the TOP of the loop body, the copy is in the loop body. But then the preheader's load `*p` (insn 22) would use... hmm, p is assigned in the loop body, so the preheader's load would use an unassigned p. ✗ (semantically broken, and the target's load uses s0 which is the copy's dest).

Hmm, so the load must be in the loop body?! But the target has the load at insn 22, in the preheader (the loop body starts at 31). Hmm, is that right? Let me double check the loop boundaries. The loop back-edge: insn 95 `bnez v0,3180` → 3180. The function starts at 31a8? The `bnez v0,32a8` at 12 → 32a8 = the function's start + 0x100 = the else part. And the target's insn 31 is at 0x31ec (since insn 0 is at 0x31a8: 0x31a8 + 4*31 = 0x31a8+0x7c = 0x3224? hmm, let me compute: the diff said target[50] = `j 31ec` and the function's base... insn 51 (target) = 0x31ec → so insn 0 = 0x31ec - 51*4 = 0x31ec - 0xCC = 0x3120. So insn 0 = 0x3120, insn 12 = 0x3150 (bnez 32a8 = the function's end+?), insn 31 = 0x319C, insn 51 = 0x31EC, insn 95 = 0x329C, and the back-edge target 3180 = 0x3180 → insn (0x3180-0x3120)/4 = 24 → the back-edge goes to insn 24?! Hmm: 0x3180 = 0x3120 + 0x60 = insn 24. Hmm, but the diff said `bnez v0,3180` at insn 95 → the loop head is insn 24? Hmm, insn 24 in the target is `li s3,1023`? no wait, that was the other function. For func_8018483C: insn 22 `lhu v0,0(s0)`, 23 `lui v1`, 24 `lhu v1,0(v1)`, 25 `andi v0,v0,1`...

Hmm, that doesn't look like a loop head. Let me recompute: 0x3120 + 24*4 = 0x3120+0x60 = 0x3180. Hmm, so the back-edge target 0x3180 = insn 24 = `lhu v1,0(v1)`. That can't be a loop head.

Hmm, maybe the function base is different. The `bnez v0,32a8` at insn 12 → 0x32a8 = the function's END (the function's last insn is 113 at 0x32a4?). Hmm, insn 12's branch target 0x32a8 = the function's exit point (past the end) → so the function's base = 0x32a8 - 12*4 = 0x32a8-0x30 = 0x3278?? That contradicts.

Hmm, the branch offsets in the target dump are the ORIGINAL game's addresses (the game binary's layout), while the diff tool's "mine" uses the recompiled layout. The target's insn addresses: 0x32a8 for the branch at insn 12. And the back-edge 0x3180 at insn 95. So the function's base = 0x32a8 - 12*4 = 0x3278. Then insn 95 = 0x3278 + 95*4 = 0x3278+0x17C = 0x33F4 ≠ 0x3180. Inconsistent.

Hmm, so the target's insn addresses aren't a simple linear function of the index — meaning the dump's addresses might be the ORIGINAL binary's and the function might not start where I think. Whatever. Let me not go down this path.

The key structural question: is the load at insn 22 inside the loop or the preheader? The back-edge at insn 95 goes to 0x3180. The function's start (insn 0): the `bnez v0,32a8` at insn 12 → 0x32a8 is the "else"/exit. Hmm.

Let me instead reason: the loop body contains the call to func_80049CAC (insn 36) and the loop back-edge (insn 95). The preheader has the D_801E86BC store (insn 28) and the D_801E86C0 store (insn 30). The load at 22 is right before those → likely the preheader.

And the loop head = the block that the back-edge targets. If the back-edge (insn 95) targets 0x3180 and the function's base is 0x3120 (from the diff's `j 31ec` at insn 50/51: mine[50] `j 31e8` vs target[51] `j 31ec` — so target insn 51 = 0x31ec → base = 0x31ec - 51*4 = 0x31ec - 0xCC = 0x3120 ✓). So the back-edge target 0x3180 = (0x3180-0x3120)/4 = 24 → insn 24. Hmm, insn 24 = `lhu v1,0(v1)`.

Hmm, that means the loop includes insns 24..95?! And the preheader would be 0..23. Hmm! But then the load at 22 is in the preheader and the D_801E86BC store at 28 is INSIDE the loop?!

Hmm, wait: the back-edge at insn 95 (`bnez v0,3180`) — hmm, but insn 95 is `bnez v0,3180`? Let me re-read the target listing:

```
 88 addiu	s1,s1,1
 89 addu	v0,v0,v1
 90 addiu	v1,v1,1
 91 sh	v0,0(s0)
 92 slti	v0,s1,4
 93 lui	at,0x0   ; HI16 D_801E86C0
 94 sw	v1,0(at)   ; LO16 D_801E86C0
 95 bnez	v0,3180 <func_8018483C+0x80>
 96 addiu	a0,s3,-2
```
`bnez v0,3180 <func_8018483C+0x80>` → the offset 0x80 = 128 = insn 32! So the loop head is insn 32 (0x3120+0x80 = 0x31A0... hmm, the annotation says +0x80 relative to the function's start). So the loop head = insn 32 (0x31A0).

So the loop body = insns 32..96, and the preheader = 0..31. The load at 22 is in the preheader ✓, and the `j 31ec` at 51 is the loop's exit (0x31ec = 0x3120+0xCC = insn 51).

Hmm, so insn 31 (`addiu a0,s3,-2`) is the last preheader insn and insn 32 (`lhu v0,0(s0)`) is the loop head.

Hmm! And the preheader's insn 31 is `addiu a0,s3,-2` — that's the first call's argument setup (for func_80049CAC at insn 36). Hmm, so insn 31 is part of the loop body's setup (scheduled into the preheader? no...). Hmm, insn 31 `addiu a0,s3,-2` and insn 36 `jal func_80049CAC` with the delay slot at 37 (`sh v0,0(s3)`). So the argument setup for the call is at 31 (in the preheader) — gcc scheduled it there. OK.

So: the loop head is insn 32, and the preheader is 0..31.

NOW: the copy `move s0,v0` at insn 19 is in the preheader, and the load at 22 is in the preheader. So both the materialization and the copy are in the preheader block. And the loop body (32+) uses s0.

So for my "block boundary" theory, the boundary would have to be inside the preheader. Hmm.

BUT: gcc's loop.c creates the loop preheader as a NEW block (the "preheader" is created by splitting). The statements before the loop are in the preheader block, and the loop body is a separate block. cse's forward scan is per block: the preheader block and the loop body block are separate.

So if the assignment `x = &D_800B99DC;` is in the preheader and the copy `p = x;` is in the LOOP BODY, then the copy is a real copy ✓. But then the preheader's load `*p` (insn 22) would use p BEFORE the copy → p is unassigned in the preheader. ✗ semantically.

Hmm! Unless the preheader's load uses a DIFFERENT variable that also holds the address... but the target's load uses s0 (the same reg as the loop's p). Hmm, unless the load's reg s0 is the X variable and the loop's p is the copy... but then the loop's p would be in a different reg (s1?), and the target's loop uses s0 for `lhu v0,0(s0)` (insn 32) — the same s0.

So both the preheader load and the loop's uses are s0. So there's ONE variable p used in both.

Hmm, so the copy `move s0,v0` must be in the preheader before the load. And the materialization `lui v0; addiu v0,v0,0` is also in the preheader. Same block. So cse's forward scan...

Hmm, WAIT. Is the preheader a single basic block? The preheader contains the early-return branch (insn 12) and then falls into the loop. So the preheader is: block1 (insns 0..13, ending with the conditional branch) and block2 (insns 14..31, the "then" path of the early return, which continues into the loop). YES! TWO BLOCKS!

Block 1: insns 0-13 (the early-return check).
Block 2 (the loop preheader): insns 14-31.
Block 3 (the loop body): insns 32-96.

So if the assignment `x = &D_800B99DC;` is in block 1 (before the early-return branch) and the copy `p = x;` is in block 2 (after the branch), then cse's forward scan for block 2 starts fresh → the copy is a REAL copy ✓✓✓!

But: the target has the materialization at insns 17-18, which is in block 2 (after the branch at 12). Hmm! If the assignment were in block 1, the materialization would be in block 1 (insns ~9-11). ✗

Hmm! Unless the scheduler moved it. Hmm, the materialization `lui v0` has no dependencies → it could be scheduled into block 1. But the target shows it at 17-18 (block 2). Hmm, gcc's scheduler generally doesn't move instructions across basic blocks. So ✗.

Hmm. OK so what if the copy is in block 3 (the loop body) and the materialization in block 2? Then the copy `move s0,v0` would be in block 3 → scheduled at insn 32+. But the target has it at 19. ✗

ARGH.

OK. Let me now consider that the copy might not be a "copy" in the RTL but the result of `reload` materializing a CONST pseudo into a hard reg via a scratch. Let me check reload.c for the case where a pseudo's reg_equiv is a symbol_ref and the pseudo is allocated a hard reg...

In gcc 2.7.2's reload.c, `reload()`:
```c
      /* If this is a constant, ... */
      ...
	  if (reg_equiv != 0 && GET_CODE (reg_equiv) == SYMBOL_REF ...)
```
Hmm, there's a known behavior: reload's `reload_in_const_mode`? no.

Actually, in reload.c there's:
```c
	  /* If the register is dead after this instruction, ... */
```
and
```c
      /* If we are outputting the reload into a hard register, ... */
```

Hmm, and there's this in reload.c:
```c
	  /* If this is a symbol ref, we may need to do a "la" ... */
```

Let me actually look at reload.c for the SYMBOL_REF handling. Let me grep "SYMBOL_REF" in reload.c.

Hmm, I'm at ~40 min on this item (budget 20-30). Let me cap it: I'll do ONE more experiment (v4: pointer reuse with pb) and if it fails, I'll record a WALL with the mechanism evidence, and move on to the remaining 3 items. The wall evidence is valuable.

Actually, let me do 2 experiments in one bash call (chained with &&): v4 and v8 (v8: p's assignment in block 1 (before the early return) and the copy after — no wait, that's semantically fine! `p = &D_800B99DC;` before the `if (--D_801E86BC != 0) return;` and the copy... hmm, but the copy must be in block 2, and p is used in block 2's load.

v8:
```
    p = &D_800B99DC;      /* block 1 */
    s4 = a0;
    if (--D_801E86BC != 0) { return; }
    ... block 2 ...
    p2 = p;   /* hmm, need p2 to be the loop's variable */
```
Hmm, but the target's load at 22 uses s0 and the loop's uses also s0. If p2 = p is the copy (p2 → s0) and p → v0, then the load must use p2 (s0) ✓ and the loop uses p2 ✓. So:

```
    u16 *p;      /* the source, in v0 */
    u16 *p2;     /* hmm, extra local */
```
Hmm, but then the preheader's load `*p2 & 1` → s0 ✓ and the loop uses p2 → s0 ✓.

But the materialization would be in block 1 (before the branch) → the target has it in block 2 (insn 17). ✗ Hmm, but sched2 might move it? A `lui v0` with no deps could be hoisted into block 1 by the scheduler? gcc's sched2 doesn't move instructions across basic blocks (it works within blocks). But the PREHEADER/loop restructuring (reorg/jump) can move code around...

Hmm, honestly: the materialization's position (insn 17-18) is right after the branch (insn 12) — in block 2. If the assignment were in block 1, the materialization would be in block 1 (insns 9-11 area). The target's block 1 is insns 0-13: `lui v0; lw v0,0(v0); addiu sp,sp,-72; sw s4,64(sp); sw ra,68(sp); ...; addiu v0,v0,-1; lui at; sw v0,0(at); bnez v0,32a8; move s4,a0`.

So block 1 = insns 0..13. If the p assignment were there, we'd see `lui v0; addiu v0,v0,0` in block 1. It's not. ✗

CONCLUSION: the copy's source and the copy are both in block 2, and cse's forward scan forwards it.

So the ONLY remaining possibility: cse's forward scan does NOT forward because the source's value is a REG at that point. Which requires the source to be set from a REG. Which requires... the source to be set from a pseudo whose value is a REG. Circular — UNLESS the source's value is a REG because of a LOAD or because cse's table has it as such.

Hmm! What if the source's value is the result of an ARITHMETIC expression, e.g. `x = y + 0` where y is a pseudo holding the address? Then x's value = (plus (reg y) (const 0)) → hmm, simplify_rtx folds (plus (reg y)(const 0)) → (reg y) → so x = y → a copy → the chain continues to the constant. ✗

What if `x = y + 1` and then the address is used with an offset? Then the address would be wrong.

What if the expression is `x = (u16 *)((u8 *)y + 0)`? folds.

Hmm, what if the value is a MEM? e.g. `x = *(u16 **)&someGlobalThatHoldsTheAddress`? That changes the reloc.

WAIT!!! What about this: the source's value could be a REG if it's the result of a *comparison* or an *arithmetic op* that's not folded. What if we compute the address as `x = (u16 *)((u32)&D_800B99DC)`? On a 32-bit target, (u32) of a pointer is a no-op → folded. Hmm, but is it? In gcc, casting a pointer to an unsigned int of the same size: `convert_to_mode` → the RTL becomes (mem (symbol_ref) SImode)?? and then fold-const's fold_convert turns it back into the address? Let me check fold-const.c's fold_convert for pointer→int:

```c
    case INTEGER_MODE:
      if (POINTER_SIZE == GET_MODE_SIZE (mode)
	  && (GET_MODE (x) == mode ...))
	{
	  ...
	  if (GET_CODE (x) == MEM && GET_MODE (x) == VOIDmode) ...
	  ...
	  /* Only do this if the address is a constant... */
```
Let me actually read fold-const.c's fold_convert to see whether (s32)&global becomes a constant address or a MEM load.

If it becomes a MEM load, then `x = (s32)&D_800B99DC` would emit an actual LOAD from the address — 1 insn (lui/lw) — hmm, the target has no load. ✗

If it folds to a CONST (the address 0x800B99DC), then the materialization would be `li`/`lui` with an absolute constant, NOT a D_800B99DC reloc. ✗ (the masked diff compares reloc operands).

OK. So the value must be the symbol_ref itself (for the reloc).

=> The value IS a constant (symbol_ref) => cse forwards => no copy. => **UNLESS the copy is not a copy in the RTL but a reload artifact.**

Let me look at reload.c's handling of a CONST pseudo with a symbol_ref reg_equiv. In gcc 2.7.2's reload.c, `reload()`:

```c
	  /* If this is a constant, ... */
	  ...
	  if (reg_equiv != 0 && ... GET_CODE (reg_equiv) == SYMBOL_REF ...)
```
Hmm, I recall reload has:
```c
      /* If we are reloading a register that is a constant, ... */
```
and
```c
	  /* If the register is a pseudo with a constant reg_equiv, ... */
```

Let me grep reload.c for "SYMBOL_REF".

Given my time budget, let me do that ONE grep, and if it doesn't immediately reveal a lever, I'll record the WALL.

Actually, hmm, hold on. Let me reconsider the problem from the "how does the ORIGINAL compiler do it" angle one final time, because there's a MUCH simpler explanation I might be missing:

The original game code was probably:
```
u16 *p = &D_800B99DC;
```
compiled by gcc 2.7.2 (the game's own compiler — the game is from the PSX era, gcc 2.7.2 was THE compiler for the PSX toolchain!).

And the project's compiler is "gcc-2.7.2-psx" — a port of gcc 2.7.2 to the PSX. If the original game used gcc 2.7.2 for Windows/PSX (the "egcs"/"2.7.2" for i386-windows?), the codegen could differ in the local-alloc's copy coalescing.

Hmm! In gcc 2.7.2, local-alloc's copy coalescing: for a pseudo with reg_equiv = a constant, the pseudo can be given a hard reg and the constant materialized directly. Our compiler does that. The original compiler (a different target: Windows/PSX) might have had a different ADDRESS_COST or a different local-alloc.

Hmm, but the target's relocs are MIPS (HI16/LO16) → the original was compiled for MIPS (the PSX). So the original compiler IS a MIPS gcc, probably gcc 2.7.2 for mips/psx or the "SGI" gcc 2.7.2.

So the difference between the original and ours is a compiler-version difference in the copy coalescing. The original had a "la" + "move" pattern.

Hmm, so the "la" (lui/addiu) into v0 then a move — this is what gcc 2.7.2 does when the address is materialized as a "CONST" pseudo in a pseudo register and then copied to the final reg.

In gcc 2.7.2, local-alloc's `allocate_reg` for a pseudo with a constant reg_equiv: it may allocate a HARD reg for it if the pseudo's live range is short ("CONST" pseudos get hard regs when their live range is a single insn or so — "local-alloc's `allocate` for CONST pseudos": in gcc 2.7.2's local-alloc.c there's `hard_reg` allocation for constants via `global_alloc`?).

Hmm! In gcc 2.7.2's local-alloc, there IS a mechanism: a pseudo with a constant value and a short live range can be allocated a HARD register directly ("allocate a hard reg for a constant"). Then reload materializes the constant into that hard reg (lui/addiu) and the copy to the destination... hmm.

You know what? The empirical difference might come from the ORDER/structure of the C: e.g., if p's value were computed in a way that p is a "CONST pseudo with a hard reg" (v0) and then copied to s0.

In gcc 2.7.2's local-alloc.c, there's this: constants are handled by `global.c`'s `allocate_constants`? Hmm.

OK, let me try a DIFFERENT C shape that might trigger a "CONST pseudo in a hard reg" + copy: what if the address is used in TWO places, one in a short-lived context?

Recall: q and r (also symbol addresses) are materialized DIRECTLY into their $s regs (s3, s2) — no copy. p gets a copy. The difference must be that p's value is needed in TWO DIFFERENT contexts.

What if p's value is used in the preheader (the load) and in the loop, and the load's MEM address gets replaced by find_best_addr with a REG...

AAAH WAIT!!! **find_best_addr**! Look: the preheader's load `*p` — after cse forwards p's value, the MEM's address is (symbol_ref D_800B99DC) — hmm, but p's value is (plus (symbol_ref)(const 0))? Hmm: for `p = &D_800B99DC`, the value is (symbol_ref D_800B99DC) (no PLUS). So the MEM's address = (symbol_ref) → find_best_addr: CONSTANT_ADDRESS_P((symbol_ref))? CONSTANT_ADDRESS_P is defined as (GET_CODE(x) == PLUS && CONSTANT_P(XEXP(x,0)) && CONSTANT_P(XEXP(x,1))) — hmm, or for a SYMBOL_REF alone? In gcc, `#define CONSTANT_ADDRESS_P(X) (GET_CODE (X) == PLUS && CONSTANT_P (XEXP (X, 0)) && CONSTANT_P (XEXP (X, 1)))`. So a bare (symbol_ref) is NOT a CONSTANT_ADDRESS_P → find_best_addr proceeds!

And then: "if the address is in the hash table, find a cheaper equivalent" — ADDRESS_COST(REG)=1 vs SYMBOL_REF=2. So if the cse table has a REG entry with the same value (the pseudo holding the address, i.e. p's reg), the MEM's address is replaced by that REG → `(mem (reg p))` → the load becomes `lhu v0,0(s0)` ✓ (the target!).

And the REG (p's reg) — the pseudo p holding the address — is the one that crosses calls in an $s reg. Hmm.

So this doesn't create the copy either. But it tells me the target's `lhu v0,0(s0)` is consistent with the MEM's address being replaced by p's reg.

OK, I need to stop. Let me do the final experiments and then decide. Given the time, let me try:

v4: pb = &D_801E87B2; q = pb; pb = &D_800B99DC; p = pb; r = &D_8018F078;
(the "pointer reuse" move — 2 sets of pb, the second copied to p)

If cse forwards, this fails. But it's the most C0505-catalog-ish move.

Let me test it. If it fails, WALL.

Actually, let me ALSO prepare a fallback: if this item is a WALL, I have 3 more items to do (8017DA30, 80184828, 8017D81C) and ~2 hours. Let me look at those items' shapes quickly while I'm at it. Actually no, let me focus.

Let me write v4 and score.
