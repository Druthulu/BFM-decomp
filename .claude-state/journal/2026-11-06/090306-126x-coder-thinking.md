---
ts: 2026-11-06T16:03:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UBpBRRXOm6YTd8UHC2rZ
---
Time 09:02:56. ~18 min. I'll do one more minute of tests then write. Let me test r3: the arg assignment moved to after `ot` but the call stays last (so the la's LUID is near the call). Probably same.

Actually, let me finalize. I'll do a final "date" check after writing the notes (which takes a minute), so the total will exceed 20 min by the time the row is written. Let me write the notes and row now — the wall will be recorded after 20 min.

Let me write the notes.md for item 4 first, then the results row, then the moves line.

Notes:
- orig.c from src 2972-3205 (fresh). baseline 0 (346 ins).
- 3 launders: arg (3014), 2-output n/otz (3111, 3182).
- c1 (all 3 removed): 43, 344 ins. c2 (arg removed only): 4 ORDER (la a0 late: target insn 1-2 vs mine 15-16). c3 (2-output removed only): 39 (cross-jump merges the two if(n<4) tails, 344 vs 346).
- 40+ tries: re-set/self-inc/volatile/second-decl/copy+dead-reset for arg; re-derivation/do-while/#line/cast/q2 for the 2-output.
- WALL: two load-bearing zero-byte asm; plain C cannot keep the single-use constant set alive (combine-argcopy-sink) nor split byte-identical if arms (jump2-crossjump-arms). best lever-free 43.

Wall tag: I'll use `jump2-crossjump-arms` (in walls.txt). Evidence: "jump2 cross-jump shares both if(n<4) tails (344 vs 346); 2nd-set asm was the split; arg la = combine-argcopy-sink (la late)" — count ≤140.

Let me count: "jump2 cross-jump shares both if(n<4) tails (344 vs 346); 2nd-set asm was the split; arg la = combine-argcopy-sink (la late)" = about 130 chars. OK.

Tries count: let me count all scored candidate bodies: 
c1,c2,c3 = 3
va1,va2,va3 = 3 → 6
vb1..vb4 = 4 → 10
vc4,vc5,vc6 = 3 → 13
vd1,vd2,vd3 = 3 → 16
ve1,ve2,ve3 = 3 → 19
vf1 = 1 → 20
vg1 = 1 → 21
vh1 = 1 → 22
vi1,vi2,vi3 = 3 → 25
vj3,vj4,vj5,vj6 = 4 → 29
vk2,vk3 = 2 → 31
vm1,vm2 = 2 → 33
vn2 = 1 → 34 (vn1 compile error, not scored)
vo6 = 1 → 35 (first 2 attempts compile errors)
vo7,vo8,vo9 = 3 → 38
vp1,vp2 = 2 → 40
vp3 = 1 → 41
vp4,vp6 = 2 → 43
vr1,vr2 = 2 → 45
Plus orig baseline.

So 45 scored tries. Good.

Let me write notes and the row. Also copy c1 to best.c (for the record) — not win.c (no MATCH).

Also clean up the dump dir from c2. And the keep scratch.

Let me write the notes file.
