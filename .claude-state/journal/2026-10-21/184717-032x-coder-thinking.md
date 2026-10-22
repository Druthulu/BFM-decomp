---
ts: 2026-10-22T00:47:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_XZTx2jMFn25DgoeWxbeV
---
Neither gives me a disassembly listing directly. But `tools/cc1_dumps_tu.sh` dumps gcc RTL for a TU — that's for my candidate, not the target.

Hmm, but wait: for understanding, the *target* IS the current src def (it scores 0). So the target's asm = the asm produced by the current src (with the launder). So I can dump MY compiled object's asm with cc1_dumps? That gives RTL, not final asm.

Alternative: since the residual diff shows both sides, I can iterate to make the diff smaller and read the target side from the diff blocks. The diff prints target mnemonics in the "replace" blocks. Right now the big block covers indices 56-85, showing both sides.

Actually, looking again at the diff output, the alignment is by difflib opcodes, so the pairing is approximate but the target lines are in order. Let me carefully extract the target sequence for the region:

From the diff:
```
replace mine[56:64] target[56:62]
  56  sra a3,v0,0x10        | sra a2,v0,0x10
  57  bgez a3,930           | bgez a2,930
  58  move a1,a3            | move a1,a2
  59  negu a1,a3            | negu a1,a2
  60  lui a2,0x6666         | lui a0,0x6666
  61  ori a2,a2,0x6667      | ori a0,a0,0x6667
  62  addiu a0,a3,160       | --
  63  mult a0,a2            | --
delete mine[66:67] target[64:64]
  66  mfhi a3               | --
replace mine[69:73] target[66:71]
  69  mult v1,a2            | mult v1,a0
  70  sra a0,a0,0x1f        | mfhi t1
  71  sra v0,a3,0x3         | addiu v0,a2,160
  72  subu a3,v0,a0         | nop
  73  --                    | mult v0,a0
replace mine[74:77] target[72:78]
  74  mfhi t1               | sra a0,t1,0x6
  75  sra v0,t1,0x6         | subu a1,a0,v1
  76  subu a1,v0,v1         | sra v0,v0,0x1f
  77  --                    | mfhi a2
  78  --                    | sra v1,a2,0x3
  79  --                    | subu a2,v1,v0
```
Note: difflib's replace blocks align by index within the block, so with unequal lengths the pairing shifts. mine[56:64] is 8 insns, target[56:62] is 6. The listing shows 8 lines with the last two having "--" on the target side, i.e. it prints max(len) lines. But the pairing after a shift is off: for the block mine[69:73] (4 insns) vs target[66:71] (5 insns), it prints 5 lines: mine[69]=mult v1,a2 | target[66]=mult v1,a0; mine[70]=sra a0,a0,0x1f | target[67]=mfhi t1; mine[71]=sra v0,a3,0x3 | target[68]=addiu v0,a2,160; mine[72]=subu a3,v0,a0 | target[69]=nop; mine[73]=-- | target[70]=mult v0,a0.

So the TARGET sequence for indices 56..85 is:
```
56 sra a2,v0,0x10
57 bgez a2,930
58 move a1,a2
59 negu a1,a2
60 lui a0,0x6666
61 ori a0,a0,0x6667
62 ? (missing, target[62]) — hmm
```
Wait, target[56:62] = indices 56,57,58,59,60,61 (6 insns) and the block listed 8 lines with the last two "--" for target. So target[62],[63] are... the "delete mine[66:67] target[64:64]" block means target has nothing at 64 (equal region between). Hmm, the diff structure: replace mine[56:64] target[56:62] → mine 56..63 (8), target 56..61 (6). Then between target[62] and target[64] there's an "equal" region covering mine[64:66] and target[62:64]. So target[62],[63] equal mine[64],[65]. Then "delete mine[66:67] target[64:64]" → mine[66] deleted, target[64] nothing (equal region mine[67:69] ↔ target[64:66]).

So target[62],[63] = mine[64],[65] (equal insns). Those weren't printed. Probably `mult v1,a0` and `mfhi t1`? Let's reconstruct the target list:
- 56: sra a2,v0,0x10
- 57: bgez a2,...
- 58: move a1,a2
- 59: negu a1,a2
- 60: lui a0,0x6666
- 61: ori a0,a0,0x6667
- 62: = mine[64] (equal)
- 63: = mine[65] (equal)
- 64: = mine[67] (equal)
- 65: = mine[68] (equal)
- 66: mult v1,a0
- 67: mfhi t1
- 68: addiu v0,a2,160
- 69: nop
- 70: mult v0,a0
- 71: sra a0,t1,0x6
- 72: subu a1,a0,v1
- 73: sra v0,v0,0x1f
- 74: mfhi a2
- 75: sra v1,a2,0x3
- 76: subu a2,v1,v0
- 77: bne a2,v0,98c
- 78: sll a2,a2,0x8
- 79: li a2,15
- 80: sll a2,a2,0x8
- 81: (target[81] = ?) 
- 84: or a1,a1,a2 (mine[84] ↔ target[85])

Hmm wait, the last replace: mine[84:85] target[85:86]: mine[84] = or a1,a1,a3 | target[85] = or a1,a1,a2. Hmm, so target[85] = or a1,a1,a2 and mine[84] = or a1,a1,a3.

And what were mine[64],[65],[67],[68]? They're "equal" to target[62],[63],[64],[65] — the instructions in the common part. Since mine's version of this region is:
```
60 lui a2,0x6666
61 ori a2,a2,0x6667
62 addiu a0,a3,160
63 mult a0,a2
64 mfhi a3          (equal)
65 mult v1,a2       (equal)
66 mfhi ... hmm
```
Hmm, mine[66] was deleted (mfhi a3). Let me re-read mine's listing:
```
56 sra a3,v0,0x10
57 bgez a3
58 move a1,a3
59 negu a1,a3
60 lui a2,0x6666
61 ori a2,a2,0x6667
62 addiu a0,a3,160
63 mult a0,a2
64 ? (equal, not shown)
65 ? (equal, not shown)
66 mfhi a3   (deleted)
67 ? equal target[64]
68 ? equal target[65]
69 mult v1,a2
70 sra a0,a0,0x1f
71 sra v0,a3,0x3
72 subu a3,v0,a0
73 (--)
74 mfhi t1
75 sra v0,t1,0x6
76 subu a1,v0,v1
77 (--)
78 bne a3,v0,988
79 sll a3,a3,0x8
80 li a3,15
81 sll a3,a3,0x8
84 or a1,a1,a3
```
So mine[64],[65] equal target[62],[63]: mine has after `mult a0,a2`: [64],[65] = ?,? then [66] mfhi a3 (deleted), [67],[68] = ?,? then [69] mult v1,a2.

For the /160 division of n=(160-ax): the standard GCC expansion (no add indicator):
```
mult n, M
mfhi r      ; hi
sra t, r, 6  ; >> 6
mflo ...
```
Hmm. Actually GCC's magic division for /160 without the "add" flag:
```
;; r = n
;; mult r, M
;; mfhi r2
;; sra r2, r2, 6      (shift)
;; sra r, r, 31      (sign)
;; subu r2, r2, r    (correction)
;; mflo r3
;; srl r3, r3, 30    (or similar)
;; addu r2, r2, r3
```
Hmm. And for the *other* division (the /20 one, x = (x+160)/20), the magic is the same M with shift 5.

Also the 0x7F multiply: n = (160-ax)*127 → the *127 mult: `mult v1, ???`. Since 127 is a constant, gcc would emit `mult v1,a?` where a? = 127 (li) or use `multu v1,127`. Hmm, but target[66] = "mult v1,a0" with a0 = M. So v1 * M.

OK so it seems v1 is the numerator of the /20 division? x = (x+0xA0)/0x14 — the numerator is x+160.

I'm clearly misreading which values are which. Let me get the full target listing a different way.

IDEA: use `delever_search --try` with a body that is a trivial stub? No.

BETTER IDEA: The target function's asm is exactly what the current src compiles to. I can compile the current src myself using the TU's recipe... but the recipe pipeline is in a recipes file. Hmm, delever_search uses `oracle.recipes_by_src(oracle.load_recipes())`.

Is there a tool to compile a TU and dump asm? tools/cc1_dumps_tu.sh does cc1 dumps (RTL). Not final asm.

Hmm, what about the `.run/` corpus: maybe the target asm is stored somewhere as .s files! E.g. build/asm/... or a "splat" .s per function. asm_verbatim mentions "a splat `.s`". Let me look for .s files with func_8017FE9C.

Let me search for the function in .s files under the repo (excluding .run/tool-results).

Actually! There's an easier route: `md.insns_from_object` — the masked_diff CLI compares two objects and prints counts only. But `tools/masked_diff.py` is a module; I can't easily call it with custom args... but I CAN run `/usr/bin/python3 tools/masked_diff.py <a.o> <b.o> fn` — it prints mismatch counts. Not a listing.

Hmm, but what if I create a dummy .s? No.

OK alternative plan: reconstruct the target from the diff by making candidates closer. The diff shows the target lines for changed blocks; equal blocks aren't shown but are identical to mine. If I get my candidate to be structurally identical to the target except for register allocation, the diff would be small.

Actually, here's a cleaner idea: **the current src def with the launder scores 0**. I want to know what changes when the launder is removed. The launder's effect: it creates a 2nd set of vol. The residual is in the vol computation's scheduling.

Let me think about what the launder does in terms of gcc internals:
- `__asm__("" : "=r"(vol) : "0"(vol));` — expand creates a new pseudo V = asm output, with V tied to vol (input). The asm is a real insn (0 bytes) with pri 1.
- The asm output V is then used in `((vol | flg) | x)`.

Without the launder, vol is a single pseudo used once at the `or`. With the launder, there are two pseudos: vol (set by the division) and V (set by the asm). The division chain ends in vol; V is a copy of vol (the asm ties them).

How does that change the SCHEDULING of the division chain? The asm acts as a "priority 1" insn; sched1 might schedule the asm early (it's ready as soon as vol is ready) but with priority 1 it goes last-ish. Hmm, but the asm doesn't appear in the final asm (0 bytes).

Hmm, but the presence of the asm changes the LUID/priority structure of the whole division chain: the division chain's output is now `vol` (dead after the asm copies it to V), and the consumer (the `or`) is V. The chain's priority may drop, changing the order of the two mults.

Specifically: in the target, the mult of the constant 127 (or whatever) is FIRST, and the variable numerator's mult is second. In mine, the variable's mult is first.

That's the classic "birth boost": the single-set constant is boosted.

What creates the birth boost? The set of the constant 127 (or the magic M). Hmm.

Actually, let me look at this from the "real 2nd set" angle used in other shards: "launder->real 2nd set `pv = *p; pv &= 0xFF000000; *p = pv | ...`; pv multi-set, no birth boost".

For our case: the launder makes `vol` multi-set (vol set by the division, then V set by the asm). The effect is on the *birth boost* of the vol computation: with a single set, the division chain is "born" at its first insn and gets a birth boost, which boosts the whole chain's priority; with 2 sets, the chain's output is dead after the copy...

Hmm, honestly, let me try the C equivalents:
(a) `vol = vol | 0;` — a real 2nd set? `vol | 0` would be folded by gcc (x|0 = x) → probably no 2nd set. Hmm.
(b) `vol &= 0xFFFFFFFF;` — also folded.
(c) Use a different variable: `s32 v2 = vol;` then use v2 → that's a copy, which cse/flow would fold (copy propagation) → same as no launder.
(d) `vol = vol + 0;` — folded.

Hmm. What actually creates a "real 2nd set" in these cases is a compound assignment with a mask (like `pv &= 0xFF000000`) because the value CHANGES (the mask is a real operation), so cse can't forward the old value.

For vol: `vol &= 0xFFFF`? That changes the value (truncates to 16 bits) — but vol's use is `((vol | flg) | x) & 0xFFFF`, so masking to 0xFFFF is semantically fine (the final & 0xFFFF). And `vol &= 0xFFFF` is a real 2nd set with a real operation (andi). But it ADDS an instruction (andi) which the target doesn't have... unless the final `& 0xFFFF` merges with it!

Look at the source: `func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);` — the final & 0xFFFF. If instead we write `vol &= 0xFFFF;` before, then `((vol | flg) | x) & 0xFFFF` still has the andi. Two andis. Unless we write:

```
vol &= 0xFFFF;         /* real 2nd set */
func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF);
```
Hmm, that's an extra andi vs the target (which has 1 andi presumably). But maybe the target's andi is `andi` on the final value, and the extra one would show as an extra insn.

Alternatively: `flg = 0x3000; vol |= flg;` — a compound assign on vol: `vol = vol | flg` → real 2nd set of vol, and it replaces `vol | flg` in the expression! Then the expression becomes `((vol) | x) & 0xFFFF`. That's exactly the same computation, with vol now multi-set (set by division, then set by the |). No extra instruction!

That's the G11 pattern: `pv &= 0xFF000000` (compound assign) = a REAL 2nd SET.

So candidate:
```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
...
{
    s32 flg = 0x3000;
    vol = vol | flg;      /* real 2nd set */
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
Hmm, but `vol | flg` where flg = 0x3000 — gcc will fold: vol | 0x3000.

But careful: the ORDER of statements matters. The launder is placed right after vol's computation, BEFORE `x = (x+0xA0)/0x14;`. So the 2nd set should be right there:

```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;      /* real 2nd set, in place of the launder */
x = (x + 0xA0) / 0x14;
if (x == 0x10) x = 0xF;
x = x << 8;
func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
```
This is semantically identical (| is associative/commutative) and creates a real 2nd set of vol at the same point.

But hmm: does `vol = vol | 0x3000` create a "real 2nd set"? Yes: vol is set twice (once by the division, once by the or). cse can't forward the division's value to the later use because vol's value changed.

But does that reproduce the launder's *scheduling* effect? The launder's effect was probably exactly this: a 2nd set of vol → the division chain's result has 2 sets → the birth boost of the chain is killed/changed.

Also the `& 0xFFFF`: the target's last part: `or a1,a1,a2` then presumably `andi a1,a1,0xFFFF`. In mine, `or a1,a1,a3`.

Also the register difference a3 vs a2 for ax.

Let's test this candidate. Also alternative: put the 2nd set as `vol = vol | flg` with flg declared before (to keep the same statement structure).

Let me write cand02.c with the compound-assign 2nd set.

Note: the `flg` block: `{ s32 flg = 0x3000; func_8002D4C8(0x93E, ((vol | flg) | x) & 0xFFFF); }`. I'll restructure minimally: keep flg but apply it to vol:

```
{
    s32 flg = 0x3000;
    vol = vol | flg;
    func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
}
```
But then the 2nd set of vol happens AFTER the x computation, not at the launder's position. Does the position matter? The launder's position (right after vol's definition) probably matters for scheduling (the 2nd set is early). Let me try the in-place version at the launder's position first:

```
vol = ((0xA0 - ax) * 0x7F) / 0xA0;
vol = vol | 0x3000;
x = (x + 0xA0) / 0x14;
if (x == 0x10) x = 0xF;
x = x << 8;
func_8002D4C8(0x93E, (vol | x) & 0xFFFF);
```
Wait — careful, the `& 0xFFFF` was applied to the whole thing: ((vol|flg)|x) & 0xFFFF. Now (vol|x) & 0xFFFF where vol already has 0x3000 ORed. Same value. Good.

But: the `x = 0xF` / `x = x << 8` and `x` is s32 (from `s32 x = (s16)L.sxy[0];`). The final & 0xFFFF truncates. Fine.

Let me write cand02 and score. Also prepare cand03 (the flg-in-block version) as backup.

Let me write cand02 now.
