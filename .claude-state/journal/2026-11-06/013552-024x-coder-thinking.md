---
ts: 2026-11-06T08:35:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_trWKixPY9khjB1SjHOzC
---
Now I see exactly. The target (47 ins including nops? target 47 ins; mine 47 too but objdump listing shows 46+... whatever) differences:

Mine vs target:
- line 2: mine `move a3,a0`, target `move a2,a0` — the a0 param copy target $a2.
- mine line 25 `lw a2,0(at)` (4th load, t3) / target line 18 `lw a3,0(at)`.
- mine line 34 `lw v0,0(at)` (5th load, t4) / target line 24 `lw v1,0(at)`.
- mine line 40-42: `lhu v1,6(a3)` / target `lhu v1,6(a2)`; same for 10(a3)/14(a3); and `move a1,a3` / `move a1,a2`.

So the only differences: the register holding the a0 pointer copy (a2 target, a3 mine), and the t3/t4 temps (target a3 and v1; mine a2 and v0). So effectively the assignment of a0-copy and t3 to {a2,a3} is swapped, and t4 got v1 in target vs v0 in mine (v1 free because ... hmm).

Why? Because keepalives make `off` and `t3` live longer, changing pseudo priorities. In target:
- a0 copy ($a2) is live across whole function.
- t3 is loaded into $a3 (the 4th load) — target keeps t3 in $a3? Wait target lw a3,0(at) then sw a3,28(sp): t3 in a3.
- t4 loaded into v1, stored.

In mine (keepalives removed): a0 copy in a3, t3 in a2, t4 in v0.

So target has a0->a2 and t3->a3; mine a0->a3, t3->a2. It's a swap. Global alloc assigns regs by priority. To flip, need the a0-copy pseudo to have higher priority than t3's pseudo (target a2 > a3 assigned in priority order: highest priority gets a2? or lowest?). In target a0-copy (live whole fn) gets a2; t3 gets a3. In mine t3 gets a2 and a0-copy a3. So mine gives t3 higher priority than a0 copy? That's odd since a0-copy is live from start to end (live length huge) — priority = sum of live lengths weighted by refs. Hmm, but a0 copy's live range includes the call (a1 = a3 uses it at the call: `move a1,a3`), so it's live across the call → cannot be caller-saved across call? Wait a2/a3 are caller-saved, and the function makes a call func_8012C51C. The a0 copy is used at the call as a1 arg, so it's live until the call. Since it's used as an argument at the call, fine.

t3 is stored to stack before... no, t3 is stored to sp10[3] at insn 21, then dies. In the target, is t3 live past? No: `sw a3,28(sp)` then a3 is reused? After that, `lw v1,...` etc. a3 not used again. So t3 dies after its store. Then why would global alloc prefer a2 for the a0 copy? Hmm.

Wait, maybe the ordering: local-alloc assigns a2/a3 to the load pseudos (t0..t4) since they're local (short-lived), and global-alloc assigns the a0 copy. Actually in this function, the a0 param copy is a global pseudo? The body has no loops, but the param copy is used across basic blocks? No branches in this function at all (straight-line). Hmm.

Let's think about what the keepalives actually did. With keepalive on `t3`, t3 becomes live from its load to the asm (after h[1] computation), overlapping h[0]/h[1] computation. With keepalive on `off`, off stays live across all the h[] updates until the call.

Removing them, the register allocation changed so t3 got a2 (lower) and a0 copy a3.

To restore target allocation without asm: need real C that keeps `off` live and `t3` live. But real C use must not change the instructions (target has exactly the same 47 insns). So any real use must compile to nothing extra... impossible unless it changes which pseudo lives where without adding instructions. Real C moves allowed: temps, decl order/scope, widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse.

Ideas:
1. Reorder statements so that `t3`'s store happens later, naturally extending its live range: e.g., move the loads' stores around. Target's order: all 5 loads interleaved with 4 stores then 5th load then sw. Actually target order: lw v1 (t0), lw a0 (t1), lw a1 (t2), lw a3 (t3), sw t0, sw t1, sw t2, sw t3, lw v1 (t4), nop, sw t4. So the source order is t0..t4 loads with stores of 0..3 after all four loads. That matches the body: loads t0..t3, stores sp10[0..3], load t4, store sp10[4]. Mine has same order.

But t3's live range ends at its store (insn 21). To extend t3's live range naturally: store t3 later, e.g. after t4's load? But target stores t3 at insn 21 before the 5th load. Can't change order without changing insns... The instruction order is fixed by target. But the pseudo's live range can extend beyond its last use if... no, in straight-line code, last use = death. Unless the same value is used again later — but no later instruction uses a3.

Alternative: keep `off` live longer using a real C use that emits nothing? No.

Hmm, but maybe we don't need both keepalives. The difference is only in a0-copy vs t3/t4 register assignment. Which keepalive caused it? Let's test each keepalive alone:
- w2 = orig minus off keepalive (keep t3 keepalive)
- w3 = orig minus t3 keepalive (keep off)

But wait: keepalive is the kind to remove. For MATCH, keepalive must be gone. If one keepalive remains, that's PARTIAL:keepalive. Let me test which one matters, to understand the mechanism.

Also possible: real C changes that alter priority without adding instructions. E.g., statement order: put `h = (u16*)sp10;` earlier, or compute h[0..2] from a different expression. The key lever is global/local alloc priority.

Let me look at the cc1 dumps to see the pseudo priorities. Use dump.sh from T10 (adapted to G25?) — dump.sh is under .run/P40/T10, shared read-only helper. It takes fn, body, tag and writes to .run/P40/T10/<fn>/dump — outside my shard! Not allowed to write outside G25. I'll write my own dump.sh under G25.

Let me first test the two partial variants to see.
