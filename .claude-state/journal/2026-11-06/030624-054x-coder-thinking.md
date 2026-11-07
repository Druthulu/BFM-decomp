---
ts: 2026-11-06T10:06:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h4clKVOBugu7CrQZQn6E
---
Mine (wk): rv=v1. Target: rv=v0, and the scheduling of `sll v0,a0,0x1` in delay slots differs slightly (target has sll in the bnez delay slot at 4408, mine has nop; target has beqz at 4418 then sll v0 in delay, mine beqz at 4418 with li v1,31 then sll).

Actually mine at 4418: `beqz v0,4424; li v1,31` — the delay slot holds `li v1,31`, whereas target has `sll v0,a0,0x1`. Hmm wait:

Target:
```
4404: slti v0,a0,16
4408: bnez v0,4424
440c: sll v0,a0,0x1     ; delay slot
4410: subu a0,a1,v1
4414: slti v0,a0,16
4418: bnez v0,4424
441c: sll v0,a0,0x1     ; delay
4420: li v0,31
4424: jr ra
```
Mine:
```
4404: slti v0,a0,16
4408: bnez v0,4420
440c: nop
4410: subu a0,a1,v1
4414: slti v0,a0,16
4418: beqz v0,4424
441c: li v1,31
4420: sll v1,a0,0x1
4424: jr ra
```

So the difference is not just the register: the scheduling of the sll/li in delay slots differs because the register (v1 vs v0) and the branch structure differ. In target, `bnez v0,4424` branches to the end (jr ra) with `sll v0,a0,0x1` in the delay slot. In mine, `beqz v0,4424` with `li v1,31` in the delay.

Interesting: the source has `if (d < 16) { rv = d * 2; goto done; }` → branch if d<16 to done, with rv=d*2 in the delay. In mine, the compiler inverted the branch (beqz) and put `li v1,31` in the delay. Why? Because with rv in v1, `li v1,31` can be in the delay slot? Hmm, reorg fills delay slots. 

Anyway, getting this to 0 with keepalive-only may be possible by steering rv to v0.

Let me try a bunch of real-C variants for item 1 with keepalive kept, to find one where rv lands in v0:

a) Declaration order: put `s32 rv;` before `s32 x = ...`.
b) Initialize `s32 rv;` at the top without init.
c) Use a `goto`-less structure.
d) Make rv the first thing assigned? 
e) Use `d` variable reuse (d = x - a0; if (d<16) { rv = d*2; ...}).
f) Split rv into a return-like variable...

Hmm, actually maybe I should test the pin-free *original* (with keepalive) but with different declaration orders. The pin forces $2; without it, we need global-alloc to pick v0.

What if we make rv's priority higher than x's? Then rv gets v0 (if v0 is free). x would take v1. That matches target! So: raise rv's refs or lower x's.

rv refs: 4 sets + 1 use (keepalive) = 5 refs (some in branches at depth 1). x refs: lw + uses.

Hmm, in the target x is v1 — same as mine. So x already gets v1 in both. The question is why rv doesn't get v0 in mine.

Maybe v0 is taken by a local temp pseudo that's live across rv's birth? The slt temps are block-local. In the block where rv is born (the `if (a0>=x)` block), the slt temp `v0` (from `slt v0,a0,v1`) dies at the branch. rv's birth (`li v0,-1`) is in the delay slot of the `j`. Hmm, after the slt temp dies. So v0 should be free.

Unless global-alloc's conflict: rv conflicts with v0 because of the `slt v0,v1,a1` at 43f0 which is live when rv is... no.

Let me check the conflict: rv is live at the end (from the first set). In the block starting at 43e8, `slt v0,a0,v1` defines v0 and it's live until 43ec. rv is not yet live there (its first set is at 4400, after). So no conflict.

Hmm, but global-alloc might not know rv's live range starts at 4400 vs 43e8... it does (flow).

Maybe the issue is that rv conflicts with v0 in a *different* path. E.g., in the path where rv = d*2 at 4420, v0 holds the slt result just before. `slti v0,a0,16` at 4414, then rv = d*2 at 4420. The slt temp dies at 4418. rv is set at 4420. So no overlap.

Hmm, but at 4418 `beqz v0` uses v0 (the slt temp) — and if rv were v0, it'd be fine (rv's value not yet set).

So why v1? Maybe because v0 is preferred/conflicting due to the function's return convention? No, void.

Or because local-alloc assigned rv? No, rv is global (live across blocks).

Wait — maybe the issue is `reg_live_length` and the preference mechanism: rv has a copy preference with the slt temp? Hmm.

Let me try the empirical route: generate variants. Let me write a generator script for item 1 with several real-C moves, keeping the keepalive.

Variants:
1. decl order: rv first.
2. `s32 rv = 0;` at decl (adds a set).
3. Reorder the two `if` checks.
4. Use a single `d` for both differences.
5. Combine the two rv=-1 branches with `||`.
6. `rv = -1;` → `rv = ~0;`
7. Restructure with `else`.

But careful: each variant must keep the same semantics and ideally the same code except the register.

Actually, maybe simpler: the target's source probably had `s32 rv;` and the pin was added because global-alloc gave v1. The decomp author used the pin to force v0. So a real-C crack may not exist (the pin is "NEEDED DIFFERS").

Hmm, "NEEDED DIFFERS (P36 rung B tus7)" suggests the pin was needed.

OK. Let me step back and consider the overall economics. I have 4 items. Items 1-3 are expand-void-return: the keepalive is essential (no real-C replacement), so full MATCH impossible. The best PARTIAL is keeping the keepalive; and if the pin is also needed for score 0, keep both.

For items 1-3, I can report PARTIAL:keepalive,pin with win.c = orig (score 0). That's honest and cheap. But the brief's spirit is to try to reduce levers. For item 3, we saw wk (keepalive-only, pins removed) = 27 — so the pins matter.

Hmm wait, for item 3, wk kept the keepalive but removed all three pins and scored 27 (41 ins). So pins needed.

For item 2: wk = 22 (31 vs 32).

So items 1-3: PARTIAL:keepalive,pin, best lever-free 15/23/28.

Hmm, but hold on. Let me reconsider whether the keepalive is truly needed for item 2 and 3 — maybe there's a real-C use. In item 2, `ret` is 0/1. The function `func_80180AC4` is called by others; its return value ignored. What if we make the last statement `if (ret) { }`? dead.

No.

OK, so items 1-3 → PARTIAL:keepalive,pin.

Wait, but is PARTIAL even the right call vs WALL? Let me re-read: "result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)". 

For PARTIAL, "win.c scores 0 keeping only those levers" — i.e., win.c is a body that scores 0 and uses only the listed levers. The orig body does that. So PARTIAL:keepalive,pin is correct.

But hmm — "keeping only those levers" implies we tried to remove levers and found the minimal set. For items 1-3, the minimal set is both (keepalive needed; pin needed for exact reg). We verified: keepalive-only = 6/22/27, no-keepalive = 15/23/28. So both needed.

Now item 4: let me focus on cracking it. Score 7, identical instruction count, f↔giv swap. Let me try variants.

Let me set up a generator. Actually, let me first try a few hand variants quickly.

Variant A: `do { ... } while (0)` around the loop body.
Variant B: `f = 0;` inside a do-while? 
Variant C: `if (cond) f = 1;` → `f = cond ? 1 : f;`
Variant D: `f |= (cond);`
Variant E: `for (i1 = 0; i1 < 5; i1++) { ... }` → `i1 = 0; do { ... i1++; } while (i1 < 5);`
Variant F: reorder: put the `f = 1` store before the compare? no.
Variant G: use `(u16)` casts differently.
Variant H: declare `f` as `s16`.
Variant I: use `f = 1, 1`? no.

Let me write the generator script producing candidates from orig.c via string replacement, then sc.sh them all.

Actually, the loop body in orig.c:
```
    case 1:
        f = 0;
        /* comment */
        for (i1 = 0; i1 < 5; i1++) {
            __asm__ __volatile__("" :: "r"(i1));  // keepalive
            if (*(u16 *)(D_801AECD8[i1] + 2) == 5) {
                f = 1;
            }
        }
```

Let me create variants by replacing this block.

Let me write a Python script gen4.py under the item dir.
