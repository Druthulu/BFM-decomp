---
ts: 2026-11-06T06:12:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KPb52i748fwvfWv3kMFT
---
Now which pseudos are pp, pf, zpush? The globals with high live length: r72 (20 refs, live 132), r73 (14/129), r79 (22/121), r90 (5/126), r89 (3/62), r88 (3/63).

The .greg order line: 75 80 87 86 85 84 126 79 72 74 73 83 123 90 89 88. Hmm, that's the allocno order (by priority descending presumably). Wait but the priorities listed: r75 23414, r80 17391, r87 17142, r86 15000, r85 13333, r84 12000, r126 11428, r79 7272, r72 6060, r74 4153, r73 3255, r83 2372, r123 2295, r90 793, r89 483, r88 476. Yes descending.

So callee-saved candidates in priority order: r79 (22 refs/121), r72 (20/132), r73 (14/129), r83 (7/59), r123 (7/61), r90 (5/126), r89 (3/62), r88 (3/63).

Which is pp? pp has 3 refs. r89 (3 refs, live 62) or r88 (3 refs, live 63). pp is the first of the two addresses: addiu s7,sp,40 (pp) then s6 (pf). Hmm, in mine pf=s6 and zpush=s7, pp=fp. Hmm, but pf should have 5 refs. r90 has 5 refs/126 — that could be pf? pf: def + loop1 use + 3 loop2 uses = 5 refs, live from 20 to ~140 = 126. Yes r90 = pf, pri 793. And r89/r88 = pp and zpush? pp: 2 refs (def + 1 use)? But table shows r89 3 refs/62, r88 3/63.

Hmm: pp def+use = 2 refs. Unless the address &p pseudo and pp... Let me identify by prefs/notes. Let me grep the .greg dump for the order line and preferences to map regnos to the RTL.

Actually easier: grep the .rtl or .greg dump for "r89"/"r88" names. The dumps print pseudo regs as (reg:SI 89) maybe with names? Let me grep the .flow or .greg for lines mentioning 89.

Hmm, but wait: pp and zpush both have 3 refs. pp: 2 refs → n_refs = 2? The table's "refs" column might already include the loop weighting (flow's reg_n_refs). pp: set at depth 0 (+1), use at depth 1 (+2) = 3. zpush: set +1, two uses at depth1 (+2 each) = 5. So zpush = 5 refs = r90? And pf = def(1) + loop1(2) + 3*loop2(2) = 9 refs. Hmm, r90 is 5 refs, r79 is 22 refs, r72 20.

Hmm. Let me reconsider: maybe reg_n_refs counts each reference once + loop_depth once, so:
- pp: def (1) + use (1+1=2) = 3 ✓ (r89 or r88)
- pf: def (1) + loop1 use (2) + 3 loop2 uses (2 each=6) = 9 → r74 (9 refs, live 65)! Yes r74: 9/65, pri 4153.
- zpush: def (1) + 2 uses (2 each) = 5 → r90 (5/126) or r126 (4/7).
- pa, pb: def + increment per loop + use → r72 (20/132)? pa: set(1) + use in loop1 (arg? no, pa used as address in v0p = (s32)pa) ... 
- i (r79? 22 refs).

Hmm so r74 = pf with pri 4153, r90 = zpush 793, and pp = r89 or r88 (483/476).

So the order: pf (4153) > ... > zpush (793) > pp (483). Confirms zpush beats pp.

Now target needs pp to beat zpush. pp pri 483, zpush 793. pp: 3 refs, live 62. If pp had 4 refs: floor_log2(4)=2 → 8/62*10000 = 1290 > 793. ✓. So ONE more ref on pp flips it (any depth: at depth 0 it adds 1 ref → 4; at depth 1 adds 2 → 5).

But an extra ref must not add an instruction.

Idea: a use of pp that folds into an address. pp points at `p` (a scalar s32 on stack). Hmm, `*pp` = p. Is there any place where p is read? No — p is only written by the calls (out-param).

Idea: make `pp` used in the else branch as a base for something? no.

Idea: Instead reduce pp's live length. pp live=62; zpush live=126. pp pri = 3*1/62 = 483. With live 45: 666 < 793. With live 30: 1000 > 793. So shortening pp's live range to ≤ 37 would also flip it. pp's live range: from def (position 16) to last use in loop 1. Hmm 62 insns. Because the loop body is ~30 insns and pp is live across it.

Hmm — what if pp's def is *inside* the loop? Then pp would be local (block-scoped) → local-alloc, and the addiu would repeat. Target has one addiu. No.

Alternatively: **increase zpush's live length** to lower its priority: zpush live 126, pri 793. If live were 160: 625 < 483? no, 5*2/160*10000=625 > 483. Need live > 126*793/483 = 207. Not feasible.

So: add one ref to pp for free. What free construct? 

What about `p` being read: e.g., after the loop... no, p is written by calls.

Wait — maybe there's a natural one: the RotTransPers4 call takes `pp` as arg. What if instead of passing `pp`, we pass `&p` and use `pp` elsewhere? no.

Hmm, what about this: make the loop-2 `&p` arg use `pp` for the FIRST call only, and `&p` for the others. Then pp gets +3 refs (depth 1 → +2 each = 6 refs, total 9) and a2 = move a2,s7 for that one call. Target has addiu a2,sp,40 for all three. Mismatch — but wait, maybe not: if pp is in s7, `move a2,s7` ≠ `addiu a2,sp,40`. Mismatch.

Alternatively make loop 2's `&p` a *new* pointer `pq = &p;` declared... that'd add insns.

Hmm, what about the `do { } while (0)` trick adding a *loop* around something so pp's use is at depth 2? E.g., if pp's single use were inside an extra nested loop (depth 2), the ref weight would be +2 instead of +1 → pp refs = 1+3 = 4. floor_log2(4)=2 → 8/62 = 1290 > 793! And a `do { } while (0)` inside the loop around the call... but that changes the loop structure/CFG, likely changing scheduling and possibly creating a new basic block. C0535 says do-while(0) splits cse1 EBB but loop notes may not be created (it's optimized away). Hmm, loop_depth comes from loop notes at flow time — a do{}while(0) around a statement doesn't create a real loop in RTL at -O2 (it's folded). But the EBB split happens at cse1 which is after flow. So no.

What about the `do { r = p + i; } while (0)` trick: it added a ref because `r` was a *new* variable whose computation folded. The ref was on p (the pointer being added). For pp, we need an expression using pp that folds into an existing instruction.

Look at loop 1: `q = (G4 *)func_80010A08(0x24);` — the arg is a constant. `c = ((Unk*)arg0)->unkEC;` — uses arg0. 

Hmm, what about `AddPrim(D_800A651C[...].a + otz * 4, q)`. no.

What about using pp as the base for `&q->xy0`? Those are q-relative.

Idea: in the else arm: `v0p = arg0 + 0x84;` etc. Could we write `v2p = (s32)pb;` etc. — uses pb. no.

OK, different approach: maybe don't fight; instead restructure the whole thing so pp/pf aren't needed: what if we pass `&p`/`&flag` directly at the RotTransPers4 call (no pp/pf vars)? Then in target, the stack args 9/10 would be `addiu v0,sp,40; sw v0,32(sp)`. But target has `sw s7,32(sp)` where s7 was computed once — because the address is loop-invariant, cse/loop hoists it into a reg. So even without pp, gcc would hoist the address into a register! That's exactly why the address ends up in a callee-saved reg. So writing `&p` directly might produce the same code but with the *address pseudo* hoisted — whose allocno is the same &p constant pseudo, with different refs.

Hmm interesting: `&p` appears once (loop1, arg 9). If written directly, cse/loop hoists it. Same thing.

Hmm, but in the target, pp and pf are the hoisted addresses.

OK so how to add a ref... 

**What about making `pp` also used in the second loop but in a way that's optimized away at the RTL level after cse, yet counted by flow?** flow runs after cse? Order: flow (counts refs) runs before global-alloc, and cse has already run? Pass order in gcc 2.7.2: cse (after loop) then flow then global_alloc. Actually flow_analysis runs right before global_alloc, after cse and combine? The pass list: ... loop, cse, ... flow, combine, sched, local-alloc, global-alloc, reload... So dead code that cse removes is gone before flow counts refs. So a dead use won't count.

Unless it survives cse but folds in combine — combine runs after flow! Combine is after flow_analysis? Let me check toplev.c pass order: `{cse, 0}, {loop, 0}, {cse, 0}, {flow, 0}, {combine, 0}, {sched, 0}, {local_alloc, 0}, {global_alloc, 0}, ...`. Yes! flow counts refs, then combine runs and can fold the extra use away. That's exactly the `do { r = p + i; } while (0)` trick: the add survives cse, gets counted by flow, then combine folds it into the store address.

So I need a use of pp that cse keeps but combine folds into an existing instruction. E.g.: `s32 *tmp = pp;` — cse would propagate the copy? cse does copy propagation within an EBB; across a loop boundary probably not. Then combine would... hmm, `tmp = pp` is a plain move, and if tmp is used as `*tmp`... 

Better: an add: `(s32)pp + K` used as a pointer. Where could that fold? The stack stores at 32(sp)/36(sp): args are `pp`. If we wrote the arg as `pp + 0`... folds in combine but is it a ref? `pp + 0` → plus with 0, likely folded by combine into pp. But cse might simplify at rtl generation? `pp + 0` is simplified during RTL expansion (fold). So no ref.

What about `pp - 0`? same.

What about a cast: `(s32 *)((s32)pp)`? no-op, folded at tree level.

Hmm, what about using pp in a *comparison* that folds? no.

What about making the else-arm use pp: e.g. `v0p = (s32)pp - 0x2C + 0x84`? no.

Let's think about which existing instruction could absorb an extra use of pp. In loop 1, the last use of pp is the stack store `sw s7,32(sp)`. If we wrote the arg as `pp` there — already.

Hmm! What about `pf`: it's passed as arg 10 (`sw s6,36(sp)`). And in loop 2 as a3.

What if we changed loop 1's RotTransPers4 args to `pp, pf` → already.

What if the *stack* arg setup could use `(s32)pp + 0`? folded.

What about using pp inside the loop as a *dummy* in a dead computation that combine eliminates but cse doesn't: e.g.
```
s32 junk = (s32)pp + 8;   /* dead */
```
flow counts a ref to pp, then combine/dead-code deletes it. But is dead code deleted before flow? flow_analysis itself doesn't delete; dead code elimination (delete_dead_insns) happens... In gcc 2.7.2, dead insns are deleted in jump_optimize? Actually `delete_dead_from_cse`? There is `delete_dead_insns` called in toplev before flow? Hmm, the C0414 note says "dead-reset cse-breaker; deleted by delete_dead_from_cse" — so dead code survives to cse and is deleted there.

Hmm, the risk: a dead `junk = pp + 8` would be deleted by cse (dead store elimination) BEFORE flow → no ref.

Unless the dead value is used in a way that survives cse but dies later... 

OK here's another idea that definitely adds a ref and folds: **reuse pp for the address of something already computed**. E.g., in the loop, the `if (i != 11)` else arm sets v0p..v3p from constants. No.

Alternatively — **make `p` a struct member or array so pp is used**? no.

Let me step back and consider a different structural lever: what if `pp` and `pf` are not separate variables but we exploit that `p` and `flag` are stack slots: `pp = &p; pf = &flag;`. In target, addiu s7,sp,40 and addiu s6,sp,44. 

What if instead we declare a small array `s32 out[2];` and use `&out[0]`, `&out[1]`? Then pp and pf would be out+0/out+4, with cse forming one base... probably changes code.

Alternatively, accept PARTIAL? The brief allows PARTIAL:<kinds still kept> — but the goal is MATCH. Since only 5 items and each needs a row, a WALL is acceptable if ≥20 min and ≥30 tries. But let's try harder.

Let me look at how similar items were cracked: moves.md has "lreg-v0-local-first", "greg-pri-refs", "keepalive ... ref weight". For G16x: "do-while(0) ref weight".

Actually — line 25: "keepalive | func_8017BF14 | WALL lreg-tie-dying-pin — ... mny keepalive cracked by do-while ref weight". So `do { } while (0)` around a use increases loop weighting? do-while(0) is a loop construct: in the tree, `do { ... } while (0)` might not create loop notes but the *statement* is a loop at RTL level? If loop_depth counted it, refs inside get +1. But the value of that here: if the RotTransPers4 call were inside `do { ... } while (0)`, pp's use would be at depth 2 → refs 1+3 = 4 → priority 1290 > 793. And a do{}while(0) around the call adds no instructions (loop optimized to nothing) — but it does add basic-block boundaries (cse1 EBB split), which affects scheduling. Hmm, and loop_depth in flow is from loop notes: `basic_block_loop_depth` computed from LOOP_BEGIN/END notes. A do-while(0) that is optimized away leaves no loop notes. But maybe it does leave them (gcc might keep the loop structure). The C0535 note says do{}while(0) "splits cse1 EBB", implying it becomes a real loop in the CFG (a loop with a single iteration, condition false). Hmm, `do { } while (0)` is usually folded by the front end... but apparently gcc 2.7.2 keeps it as a loop? That's the whole point of the trick.

If it creates a loop note, then wrapping the RotTransPers4 call in `do { ... } while (0)` would put pp's use at depth 2, boosting refs. But it would also put the whole call inside a loop → other allocnos' refs also boost (pa, pb, q, otz...), and loop.c might not hoist things. Risky but worth a try.

Let me instead try the simplest first: wrap just the `otz = RotTransPers4(...)` statement in do-while(0) and score.

Actually wait — that also serves the launder problem (splitting the EBB so combine doesn't fold the otz copy). Two birds. Let's try:

```
do {
    otz = RotTransPers4(v0p, v1p, v2p, v3p, &q->xy0, &q->xy1, &q->xy2, &q->xy3, pp, pf);
} while (0);
```
Hmm, but a do-while around a call statement — the call is the only statement. 

Let me try variants:
w1: do-while(0) around the RotTransPers4 statement (with `// !FAKE: do-while` comment).

Also try w2: `do { } while (0)` empty after the call.

Let me write and score both.

Actually also consider: the missing `move s1,v0 / move a0,s1`. The asm re-tie made otz a real 2nd set. Plain C `otz = RotTransPers4(...)` then `otz = func_801823D4(otz, -0x1A)` — combine merges into a0=v0. Wait, actually the target has `move s1,v0` (otz gets s1) then `move a0,s1`. That means otz is a *global* allocno in s1 (live across... no, it dies at the arg copy). Hmm, why would otz be in s1 rather than v0? Because with the asm re-tie, otz has a set and the asm makes it non-copyable... Actually the asm `"=r"(otz) : "0"(otz)` forces otz into a register with a real set, and then combine can't fold the copy into the call.

Without the asm: combine turns `(set otz (reg v0))` + `(set a0 otz)` into `(set a0 v0)` — dropping the move. Also `otz` gets v0.

Target: `move s1,v0` then `move a0,s1` then after the second call `move s1,v0`. So otz lives in s1 (global allocno, because it spans basic blocks? no—it's within one block... but it's assigned s1 because it's live across the call to func_801823D4? No: otz = RotTransPers4(...); a0 = otz; jal func_801823D4. otz dies at the arg copy before the call. Hmm, then local-alloc would give it v0.

Unless... the asm re-tie makes otz's live range span the asm insn which is a use+def, so otz = call; asm(otz); a0 = otz. Still local.

But target shows s1. So otz is a global allocno. Why? Because `otz` is used in loop 2 as well, in a different block? No, each block has its own... it's the same variable `otz` in both loops! So the pseudo is global (used in multiple basic blocks) → global-alloc → s1. Yes! otz is one variable used in loop1 and loop2, both loops, so it's global and gets s1 (callee-saved? it's live across calls in the loop... yes, otz is live from the RotTransPers4 call to the AddPrim call across func_801823D4, so it must be callee-saved: s1).

So otz = s1 globally. The copy `move s1,v0` is the global pseudo's assignment from v0, and `move a0,s1` is the arg copy. In plain C, combine folds these because the pseudo's... hmm, combine sees `(set (reg s1) (reg v0))` — no, at combine time otz is still a pseudo (global-alloc runs after combine). So combine sees `(set otz (reg v0))` then `(set a0 otz)` and folds to `(set a0 (reg v0))`, eliminating otz's set. But otz is used later (AddPrim index), so otz keeps... hmm, if combine folds the first use, otz's set becomes `(set otz (reg v0))` still needed for the later AddPrim use, but then combine could propagate v0? No, v0 is clobbered by the next call.

Hmm, the diff says mine has `move a0,v0` where target has `move s1,v0; move a0,s1`. So mine indeed folded.

The asm re-tie prevented it. A plain-C way: make otz's first assignment *not* a simple copy — e.g. `otz = RotTransPers4(...) + 0`? folds. `otz = (s32)RotTransPers4(...)`? cast no-op.

Or use do-while(0) to split the block: combine operates within a basic block; if there's a block boundary between the set and the use, combine can't fold. do{}while(0) creates a block boundary (a label/jump). From G14: "the launder tied-output on sc -> empty do { } while (0) (plain C keeps the CFG shape the asm forced)". So an empty do-while(0) between the call and the next use should prevent the fold — but does it add instructions? A `do {} while (0)` compiles to nothing (no branch) if the body is empty and the condition is constant... then no block boundary either. Hmm, but in G14 it worked. The trick works because gcc's front end emits a loop structure (NOTE_INSN_LOOP_BEG) even for do{}while(0)? Let's just test empirically.

Let me try w1: do-while(0) around the RotTransPers4 call statement; w2: empty do-while(0) between call and func_801823D4; w3: `do { otz = RotTransPers4(...); } while (0);`.

Let me create three candidates and score them in one sc.sh call.

For w1/w3 the syntax:
```
        do {
            otz = RotTransPers4(...);
        } while (0);   // !FAKE: do-while
```
But comments in the body file are fine.

Let me generate them with a script to avoid writing 3 full files by hand. I'll write a small gen script that takes the w0 text and applies a substitution.

Simplest: write w1.c fully via a python script that reads w0.c and replaces the line.

Let me do that.
