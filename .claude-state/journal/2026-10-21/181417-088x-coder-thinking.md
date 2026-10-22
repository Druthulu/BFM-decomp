---
ts: 2026-10-22T00:14:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_o0bdUeVGn1wi9c5BVVzu
---
The ledger row for the item 6 header says: "header": true, "includers": 136, verdict RESIDUE (the pin is NEEDED per the oracle), and the sites list the pin at line 30 with verdict "NEEDED", why "", oracle "DIFFERS".

Interesting: the ledger says the pin's oracle verdict is "DIFFERS" (i.e. removing the pin changes the bytes ✓ consistent with my finding) — hmm, but wait: it says the pin is NEEDED and the oracle DIFFERS. Hmm, but my lever-free body (with the call-site cast) scored 0! So the oracle's "NEEDED" was for the naive removal (just deleting the pin line), not for the cast ✓.

Also "includers": 136 ✓ and the verdict RESIDUE means the body still has a lever (the pin) — the bank hasn't accepted my cast version (it's not in the tree).

The "replay_disagreed": false and the site's oracle "DIFFERS" — hmm.

Note: this ledger row's "sites" shows the pin at line 30 as NEEDED. The bank rule: the ledger's per-site oracle checks whether removing the lever changes the bytes. My cast version removes the pin's EFFECT without removing the "site"? Hmm, the site detection is a text scan for `register ... __asm__` — my version has no such text ✓ → the site is gone → the body would be lever-free ✓.

OK. The includer count is 136 ✓ (from the ledger, an authoritative source).

Now, about the multi-includer verification: the ledger's "includers": 136 and the header is banked per-recipe... The verdict RESIDUE is about the lever, not the byte-identity.

I'll document: score 0 at the header's first includer; 136 includers per the ledger; the body is context-free C (no macros/conditionals; checked the sampled includers for colliding #defines).

Now let me write everything up. Time: ~3h55m.

Deliverables:
A. results.tsv: 7 new rows (items 3,4,5,6,7,8,9).
B. moves.md: 7 new lines.
C. notes.md in each of the 7 item dirs.
D. phase-ends/current/logs/T11.cG08r.md.
E. Cleanup: remove the cc1 dumps dir (.run/P32/t4e/dumps_item5) and the scratch dumps5 dir? The brief says the dumps go under my item dir and are deleted after reading. I put them in .run/P32/t4e (the script's default). Let me try `rm -rf .run/P32/t4e/dumps_item5` — if denied, note it.
   Also the shard dir size: let me check (the many c_*.c files from the prior run + mine). The brief: "your shard dir stays < 200 MB". Let me check the size.

Let me do the results.tsv rows first. The format: `dir file func kinds result best tries wall evidence` (tabs).

Rows:
1. func_8014C308__func_8014C308	src/shared/ov/func_8014C308.h	func_8014C308	pin	WALL	17	13	const-fold-return	evidence
2. func_8014FD54__func_8014FD54	src/shared/ov/func_8014FD54.h	func_8014FD54	pin	WALL	8	9	sched1-hardreg-sink	evidence
3. func_801536DC__func_801536DC	src/shared/ov/func_801536DC.h	func_801536DC	pin	WALL	9	5	lreg-allocno-tie	evidence
4. func_801580B4__func_801580B4	src/shared/ov/func_801580B4.h	func_801580B4	pin	MATCH	0	2	-	evidence
5. func_801581AC__func_801581AC	src/shared/ov/func_801581AC.h	func_801581AC	pin	MATCH	0	1	-	evidence
6. func_8017849C__func_8017849C	src/shared/ov/func_8017849C.h	func_8017849C	pin	WALL	36	4	greg-pri-refs	evidence
7. func_8018655C__func_8018655C__5fb02634	src/shared/ov/func_8018655C__5fb02634.h	func_8018655C	pin	WALL	58	3	greg-pri-refs	evidence

Evidence (≤ 140 chars, "gcc pass + mechanism"):
1. "gcc2.7.2 combine/cse: the const 1 is folded into the return copies, the v0 pseudo dies, $2 stays free for the compare temp (li v0,9 vs li v1,9); 41 vs 39 ins"
   Hmm, keep it ≤140 chars. Let me count: roughly 150. Trim:
   "combine folds the const 1 into the return copies (pseudo dies), $2 stays free for the compare temp: li v0,9 vs li v1,9; 41 vs 39 ins" — ~128 ✓
2. Item 4: "with the pin, result is a hard-reg set sched1 sinks past the mask test; lever-free keeps it in $3 and copies at the return (move v0,v1); 40 vs 40 ins" ~145. Trim: "the pinned $2 set is sched1-sunk past the mask test; lever-free keeps result in $3 and copies at the return (move v0,v1); 40 ins both" ~135 ✓
3. Item 5: "alloc_table: the RESULT_DECL (pri 10000, prefers v0) ties with the load temps (pri 10000) and loses the allocno tie-break; temps take $2/$3" ~135 ✓
4. Item 6: "gcc2.7.2 -O2: call-site cast ((s32(*)(void*))func_80161418)((void*)a0) != 0 keeps the call result in $2; pin gone, 62 ins identical" ~140. Trim: "call-site cast ((s32(*)(void*))func_80161418)((void*)a0) != 0: the call result stays in $2, pin gone; 62 ins byte-identical" ~128 ✓
5. Item 7: same with func_801581AC ✓
6. Item 8: "lever-free: callee-saved bank assigns p/q/i to $16/$18/$19 (target $17/$16/$18) and the load temps take $2/$3 (target $4/$3); 95 vs 91 ins" ~140. Trim: "callee-saved order flips (p,q,i -> $16,$18,$19 vs target $17,$16,$18) and the load temps take $2/$3 vs $4/$3; 95 vs 91 ins" ~135 ✓
   Hmm, the wall tag: "greg-pri-refs"? The mechanism is the global-alloc priority. Let me use the tag "greg-alloc-order" (a new `<pass>-<what>` tag ✓).
   For item 9: the mechanism: the callee-saved bank swaps t/r between $16/$18 (the t pin forced t to $18). Tag: "greg-alloc-order" too (same mechanism) — hmm, the brief says a new tag should be "defined in the coder's results evidence" ✓ (I'll define it in the evidence/log).
   Item 9 evidence: "lever-free: the callee-saved bank gives the call result t $16 (more refs) and r $18; the target has t $18 (pin) and r $16; 167 ins both" ~140. Trim: "lever-free: the call result t takes $16 (more refs) and r $18; target has t $18 (pin), r $16; 167 ins both" ~118 ✓

Tries counts: let me count the scoring runs per item:
- Item 3: nopin (prior, counted), A, B, C, D, E, F, G, H, I, J, K, L = 13 (I scored: A,B,C,D,E,F,G,H,I,J,K,L = 12 + nopin = 13) ✓
- Item 4: nopin, M2, M4, Q1, Q2, P1, P2 = 7
- Item 5: nopin, R1, V1, V2 = 4
- Item 6: nopin, S1 = 2
- Item 7: S1 = 1 (plus orig = a control) → 2
- Item 8: nopin, P1, P2 = 3
- Item 9: nopin, Q1, Q2 = 3

Let me set tries accordingly (item 7: 1 candidate scored → but I'll count the orig control → 2).

Also the "wall" column for MATCH rows = "-" ✓.

Now the moves.md lines (format: `kind | func | MATCH: the move / WALL: tag — mechanism (G08)`):
1. `pin | func_8014C308 | WALL const-fold-return — combine folds the const 1 into the return copies (the pseudo dies), so $2 stays free for the compare temp: li v0,9 vs li v1,9; 41 vs 39 ins (G08)`
2. `pin | func_8014FD54 | WALL sched1-hardreg-sink — the pinned $2 set is sched1-sunk past the mask test (the ROM's mask==0 path returns the stale $2); lever-free keeps result in $3 and copies at the return (G08)`
3. `pin | func_801536DC | WALL greg-alloc-order — alloc_table: the RESULT_DECL (pri 10000, prefers v0) ties with the load temps (pri 10000) and loses the allocno tie-break, so the temps take $2/$3 (G08)`
4. `pin | func_801580B4 | MATCH — call-site return-type cast ((s32 (*)(void *))func_80161418)((void *)a0) != 0: the call result stays in $2, the pin is gone (G08)`
5. `pin | func_801581AC | MATCH — same call-site cast on func_80161418; the call result stays in $2, the pin is gone (G08)`
6. `pin | func_8017849C | WALL greg-alloc-order — lever-free the callee-saved bank flips (p,q,i -> $16,$18,$19 vs target $17,$16,$18) and the load temps take $2/$3 vs $4/$3 (G08)`
7. `pin | func_8018655C | WALL greg-alloc-order — lever-free the call result t takes $16 (more refs) and r $18; the target has t $18 (pin) and r $16 (G08)`

Now, appending to results.tsv and moves.md: I must APPEND. The Write tool overwrites whole files ✗ — I need appends. Hmm! The Write tool can only write whole files. For results.tsv, I can read the current content (2 rows) and rewrite the whole file with the old + new rows ✓ (that's effectively an append, and the file is small). Same for moves.md (150 lines, 25KB — rewriting it wholesale would require reading all 25KB ✗ and would violate the "don't read whole files" rule and risk damaging it).

Hmm! For moves.md I need to APPEND a line. Options:
- Use the Edit tool: read the tail of moves.md and use Edit to add after the last line ✓ (Edit requires a unique old_string — the last line is unique ✓).
- Read the last ~3 lines with Read (offset 148) and Edit.

Let me do that: Read moves.md lines 146-150, then Edit to append.

For results.tsv: read it (552 chars, small ✓) and Write the full new content.

Let me now do these. First, read the tail of moves.md and results.tsv.

Also notes.md per item dir (7 files) — brief: "Notes in <dir>/notes.md". Let me write a concise notes.md per item.

And the log file phase-ends/current/logs/T11.cG08r.md — hmm, "phase-ends/current/logs/" — the brief says LOG: phase-ends/current/logs/T11.cG08r.md. Note the house rule says never read phase-ends/*/logs/ — but writing is required here ✓.

Also the log must record the timeline per item with start/end times, minutes, and tries. I have rough times: item 3 started ~17:34, item 3 ended ~18:20 (46 min!). Hmm, let me reconstruct from the `date` outputs: the first date was 17:34:33. I don't have per-item timestamps except that one. I should be honest: I can note the times I measured. Hmm, the brief says "per item, in the log timeline, record start/end time (date), minutes, and tries". I can reconstruct approximate times from the session: I only have one date output (17:34:33) and the final one. Hmm.

I can run `date` now and estimate the earlier times from the tool-call sequence... that's guesswork. Better: be honest — record the measured start (17:34) and the observed elapsed times per item as measured by the number of scoring runs? No.

Hmm, I should have dated each item. Let me be honest in the log: give the shard start (17:34:33, measured), the end time (measured now), and per-item the elapsed window derived from the log order, marked as approximate. Actually — I can measure the elapsed per item approximately: the total is ~4h10m for 7 items ≈ 35 min each. Let me give per-item approximate windows based on my ordering, and mark them "(approx; only the shard start/end were clocked)".

Hmm, that's not great but honest. Let me record what I can: I'll note the wall budget breach for item 3 (>30 min → "past 30 min stop and record a wall" — I did stop it at ~45 min and record a wall ✓).

Let me get the current time and then write everything.
