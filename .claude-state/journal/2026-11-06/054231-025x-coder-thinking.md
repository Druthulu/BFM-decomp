---
ts: 2026-11-06T12:42:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7rXs5V8Mdsqvn6ehQBnE
---
Important correction: PARTIAL:<kept> means every row kind NOT in <kept> is gone from win.c. A win.c that keeps all row kinds is a WALL regardless of score. So for these barrier-only items: either MATCH (all barriers gone, score 0) or WALL (any barrier kept) — PARTIAL doesn't apply because there's only one kind: keeping barrier = keeping all row kinds = WALL.

So for item 1: must remove all 4 barriers AND score 0 for MATCH. Otherwise WALL with best = lowest score of a lever-free body.

OK. Let me keep working on cracking barriers 2, 3, 4.

b2 diff: register swap a0 <-> v1 in the `ua = ub = (sx - ...) << sh; ub += rec->w; ub -= 1;` region. This is a classic local-alloc/global-alloc reg choice. Score 28.

b3 diff: 
- mine at 270: andi v0,a1,0x10; beqz; then at 273 addiu a0,v1,-256
- target at 269: andi v0,a1,0x10; beqz; at 272: j ba90; 273: addiu a0,v1,-256 (delay slot)

So the target has the `j` over the else arm with `addiu a0,v1,-256` in the delay slot, then the else arm (move a0,v1) — wait let's see: target has `beqz v0, ba8c` then `j ba90` then `addiu a0,v1,-256`. So if tc==0, branch to ba8c (else arm at ba8c); if tc!=0, j to ba90 with addiu in the delay slot. So the `j` is needed to skip the else arm.

Mine lacks the `j`: mine has andi/beqz then addiu directly — i.e. mine's layout is: if tc != 0, fall through to addiu a0,v1,-256 (then presumably j to join), else at ba8c: move a0,v1 then falls to join. Actually mine at 270: andi, 271 beqz v0,ba8c, 272? (not shown) ... 273 addiu a0,v1,-256. The `delete mine[273:274] target[275:275]` means target has an extra insn. So mine is missing one insn: the `j` in the tc arm.

So without the barrier, jump2/dbr optimizes: the tc arm `ua = ub - 0x100;` is a single insn (addiu), and the else arm is `move`. Mine arranges: beqz else; addiu in delay slot; then the else block placed after, and after addiu there's a jump to join... Hmm.

Actually mine is one insn shorter: it must be that mine's tc-arm addiu goes in the delay slot and then falls through into... the else arm? No.

Let me think: the barrier in the else arm makes the else arm non-empty at the RTL level? No, `ua = ub;` is a move which may be optimized away as a copy (ua coalesced with ub). Hmm! Actually without the barrier, `ua = ub;` in the else is just a register copy that may be eliminated (coalesced) — but the target keeps `move a0,v1`. With the barrier, the asm forces... hmm, the asm doesn't force the move.

The diff shows mine at 273 addiu a0,v1,-256 and target at 272-273 j + addiu. So target:
```
269 andi v0,a1,0x10
270 beqz v0, ba8c      (else: ba8c)
271 (delay slot? no)
272 j ba90
273 addiu a0,v1,-256   (delay slot of j)
```
Wait the diff shows target 272 j, 273 addiu. And beqz at 270 with delay slot at 271 = ? Probably `nop`? Or the beqz delay slot is filled with something. Hmm, mine[270..272] replaced by target[272..274]: mine 270 andi, 271 beqz, 272 ? ; target 272 j, 273 addiu, 274 ?

Ugh, indices offset by 2 in this region (mine 270 ↔ target 272). The insert at mine[269] means target has 2 extra insns before that point... no, "insert mine[269:269] target[269:271]" = target has 2 insns mine lacks at that spot, and "delete mine[273:274] target[275:275]" = mine has 1 insn target lacks. Net +1 = 408 vs 407. OK.

So target at 269-270 has andi/beqz, mine at 270-271 has the same andi/beqz. So target's andi/beqz come one insn earlier. And target 272 j, 273 addiu; mine 273 addiu... 

I think this is getting deep. Given time budget (20-30 min/item), let me try obvious real-C moves for b3:

The pattern:
```
tc = tpage & 0x10;
ub = sy;
if (tc) { ua = ub - 0x100; } else { ua = ub; }
ub = ua + rec->h - 1;
```
Real-C alternatives that keep the same insns but change block layout:
(a) swap arms: `if (!tc) ua = ub; else ua = ub - 0x100;`
(b) `ua = ub; if (tc) ua -= 0x100;`
(c) `ua = tc ? ub - 0x100 : ub;`
(d) `ua = ub - (tc ? 0x100 : 0);`
(e) remove ub copy: `if (tc) ua = sy - 0x100; else ua = sy;`

Note moves.md line 77: "barrier: swap inner arms if(!overshot){store;ret=1;}else ret=0 (no cross-jump)". So arm swapping is a known move.

For b2 (reg swap a0/v1): the region is `ua = ub = (sx - ((tpage & 0xF) << 6)) << sh; ub += rec->w; ub -= 1; if ((u16)ub >= 0x100) ub = 0xFF;` The barrier before it. Without the barrier the allocation of ua/ub flips. Real-C moves: 
- write `ub = (sx - ...) << sh; ua = ub;` instead of `ua = ub = ...` (but moves.md says chained assignment keeps a move alive).
- fold `ub += rec->w; ub -= 1;` into `ub = ub + rec->w - 1;`
- reorder statements.

Let me try a batch of variants for b2 and b3 in one sc.sh call.

Actually, a smarter approach: since the barrier was added to fix exactly this, the "lever-free" replacement is often a statement split / temp that makes the dependency explicit. Let me try several.

For b2, the reg swap suggests local-alloc gives the wrong pseudo. A `do { } while (0)` (C0535) could split the EBB and change allocation. Let me try:

b2v1: wrap `ub += rec->w; ub -= 1;` in a do-while(0)? Hmm.

Let me just try a set:
- v_a: `ub = (sx - ((tpage & 0xF) << 6)) << sh; ua = ub; ub += rec->w; ub -= 1;`
- v_b: same but `ub = ub + rec->w - 1;`
- v_c: do-while around the ua/ub init.

For b3:
- v_d: `ua = ub; if (tc) ua -= 0x100;`
- v_e: swapped arms
- v_f: `ua = ub - (tc ? 0x100 : 0);`
- v_g: `if (tc) ua = sy - 0x100; else ua = sy;`

Let me generate these from b3.c (which already has barrier 3 removed) and b2.c.

Wait — careful: b2.c has barrier 2 removed but barriers 1,3,4 still present. b3.c has barrier 3 removed. To combine, I need all barriers removed (b1 already removed free). Let me build a base with barriers 1 and (say) 3 removed, then test variants.

Actually best: work on each barrier independently against orig (single-removal variants), find a real-C fix, then combine. Since b1 removal is free, final = orig - b1 - b2fix - b3fix - b4fix.

Let me create variants.

For b2 (barrier 2 removed = b2.c), the code:
```
        prim[7] |= (attr & 0x40) >> 6;
        [barrier removed]
        ua = ub = (sx - ((tpage & 0xF) << 6)) << sh;
        ub += rec->w;
        ub -= 1;
        if ((u16)ub >= 0x100) ub = 0xFF;
        if (id & 0x100) {
            prim[0x14] = prim[0x24] = ua;
            prim[0x0C] = prim[0x1C] = ub;
```
Hmm wait, the diff for b2 shows swaps around `move v1,a0 / addu a0,a0,v0 / addiu a0,a0,-1 / andi v0,a0,0xffff / li a0,255`. So it's the ua/ub block indeed.

Ideas for b2: the problem is ua/ub get a0 vs v1. Try:
1. `ub = (sx - ((tpage & 0xF) << 6)) << sh; ua = ub;` (break the chained assignment)
2. `ub = ...; ua = ub; ub = ub + rec->w - 1;`
3. Add a temp for the base: `s32 t = (sx - ((tpage & 0xF) << 6)) << sh; ua = ub = t;`
4. do-while(0) wrapper.

For b4:
1. inline the mask constant in both stores (drop mFF var) — but mFF is a pin; removing it changes kinds? It's a pin, allowed to stay or... "levers of other kinds the def already had may stay, never added" — removing is fine. But score must be 0. Let's test.
2. `mFF = 0xFFFFFF ^ 0xFFFF;`? no.
3. Move the mFF assignment to after ott but write it as `mFF = ~0xFFFFFF;` (same value). Might change scheduling? Unlikely.
4. Make ott's computation feed mFF? no.
5. Try `ott = (u32 *)(idx * 4 + (s32)ot);` → `ott = ot + idx;` (pointer arithmetic, same sll+addu).

Let me generate a batch and score.

Actually for b4, here's an idea that's real C and creates a block boundary: put the ott computation in an `if` whose condition is already known true but not folded: `if ((u32)idx < 0x1000) { ott = ...; }` — but the preceding statement already is `if ((u32)idx >= 0x1000) return;`, so the compiler knows idx < 0x1000 after. Hmm, would it fold? Possibly yes (range info), leaving the if with a constant-true condition → removed at jump opt, but the BB split happens at RTL generation... Actually if the condition folds to constant before RTL, no split.

Alternative: a do-while(0) around `ott = ...;`. gcc's `do { } while (0)` typically survives to RTL as a loop with one iteration? Let's test — C0535 says it splits cse1 EBB, and it cracked sched1-birth-order items. Worth trying.

Let me generate:
- c4a: inline mask constant in both stores, remove mFF var decl and assignment (keep pin? no, remove pin too). Actually if I remove the var mFF entirely, the pin goes away. That's allowed (pins may stay, not must). But other barriers' codegen might shift... only 1 insn difference region. Let's test.
- c4b: `do { ott = ...; } while (0);` with // !FAKE: do-while
- c4c: compute ott from `ot` via index: `ott = &ot[idx];`

Let me write these.

Actually, to be efficient, let me write a small generator script under the item dir that takes b4.c and produces variants. But careful about time. Let me do it with a python heredoc (allowed? "Scripts, not inline python -c" — heredoc to /usr/bin/python3 is a script via stdin; the rule says scripts, not inline `python -c`. I've already used heredocs. It's fine-ish, but let me write a generator file under the item dir to be safe and reusable.

Let me create gen.py in the item dir.
