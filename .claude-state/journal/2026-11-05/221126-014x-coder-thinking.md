---
ts: 2026-11-06T05:11:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oVMRqxMP4NSfevmR5KJr
---
Log went to .run/3.40/logs/. Phase dir is 3.40.

Target:
```
0..:
7 lbu v1,36(s1)
8 lw a0,76(s0)
9 addiu v0,v1,-16
...
11 move v1,v0
12 jal func_800CAE0C
13 move a0,s0
14 j ...
16 move v0,v1
```

Wait this is the `if (t < 0)` block: target computes t = raw-0x10 into v0; raw copy into v1; then calls func_80146CA0 (which is func_800CAE0C in the object? Hmm, jal 0 <func_800CAE0C> — probably the actual name from the TU). Then `move v0,v1` — hmm.

Actually, the target:
- insn 7: lbu v1,36(s1)  — raw load into v1
- insn 8: lw a0,76(s0)   — p load into a0
- insn 9: addiu v0,v1,-16 — t = raw - 0x10 into v0
- ... presumably slt/bgez?
- 11: move v1,v0 — raw = t (v1 = v0)
- 12: jal
- 13: move a0,s0
- 14: j
- 16: move v0,v1 — t = raw (v0 = v1)

Hmm, so the target literally has raw in v1 and t in v0. The pins reproduce that. The launder forces the `move v1,v0` (raw = t) to survive? And `t = raw` yields `move v0,v1`.

Wait let's see: mine currently:
```
7 lbu v0,36(s1)
8 lw v1,76(s0)
9 addiu v0,v0,-16
```
So mine puts raw in v0 and t in v0 (merged), p in v1. Target raw in v1, t in v0, p in a0.

So the difference is register allocation: target has three values live: raw(v1), t(v0), p(a0). Mine merges raw and t into v0, so p gets v1.

Without pins, raw and t are just copies of each other (raw = t; t = raw), so cse/combine merge them into one pseudo. The pin makes them distinct hard regs. Launder keeps raw from being merged.

To be lever-free, we need plain C where raw and t are separate live values that get v1 and v0 respectively, and p gets a0.

Idea: keep `raw` alive after the copy? e.g. `raw = t;` and use raw later. Or restructure so that the value is genuinely two variables.

Let's think about the target semantics:
- raw = *(u8*)(s1+0x24)  [lbu v1,36(s1)]
- t = raw - 0x10         [addiu v0,v1,-16]
- if (t < 0) { call; return; }
- raw = t;               [move v1,v0]
- t = raw;               [move v0,v1]
- store t to three bytes.

The `raw = t; t = raw;` is a no-op semantically. The target has both moves because of the pin/launder dance. Hmm wait, actually with the pin, `raw` and `t` are distinct registers, so both moves are real.

But the target also loads p at insn 8 (lw a0,76(s0)) — p is used only later (at the second call, `*(s16*)(CAST_SIGN(...p...)+0x12)`). Hmm, p is loaded early because... global-alloc? No, p is a local. Actually `p` is loaded at insn 8 right after the lbu. That's scheduling: the load was hoisted.

So lever-free target: we need the same instruction sequence. The key question: can plain C produce `move v1,v0` and `move v0,v1`? That requires two distinct pseudos with a copy chain.

Since raw and t are both live: raw is used only in `t = raw - 0x10`; t used in compare and then stores. If I write:

```c
raw = *(u8*)((u8*)s1 + 0x24);
t = raw - 0x10;
if (t < 0) { ...; return; }
raw = t;
t = raw;
```

Without pins, cse makes raw and t equivalent after `raw = t` (and `t = raw` merges). Actually initially raw and t are not equivalent (t = raw-16). After `raw = t`, raw and t are equal; cse would set them equivalent and then `t = raw` is a no-op copy removed. Then stores use whichever. So the moves disappear.

To keep both moves in plain C, we need to prevent cse from making them equivalent — i.e., make raw and t genuinely different values at that point, but produce the same instructions. The target's moves are: move v1,v0 (raw = t) and move v0,v1 (t = raw). Semantically they are just copies. In plain C, how could we get two copies that aren't folded? 

Hmm. If raw and t are different types! E.g. `u8 raw; s32 t;`. Then `t = raw - 0x10` and `raw = t` (a u8 store) and `t = raw` (a zero-extend load). Hmm, but the target stores t (32-bit) to bytes via `= t` chain; the sb takes low byte.

Wait, actually let's reconsider. The target's `move v1,v0` at 11 and `move v0,v1` at 16 — maybe these are not copies of raw/t but of the *result of the call*. Let me get the full target asm to be sure. Let me dump the target object.

Actually let me look at the diff more carefully: it says "insert mine[11:11] target[11:15]" — target 11-14: move v1,v0; jal; move a0,s0; j. Then "replace mine[12:16] target[16:17]": mine has jal; nop; j; nop; target has move v0,v1.

So target sequence around:
- 9 addiu v0,v1,-16
- 10 (something: maybe bgez v0 -> ...)
- 11 move v1,v0
- 12 jal func_800CAE0C
- 13 move a0,s0
- 14 j ...
- 15 nop
- 16 move v0,v1
- 17... rest

Hmm wait, jal at 12 with `move a0,s0` in delay slot, then j at 14 — that's the `if (t<0)` arm: call func_80146CA0(arg0) then return. And `move v1,v0` at 11 before the branch? That's odd — it's in the branch delay slot? Let's see: probably insn 10 is `bltz v0, ...`? No, if it were bltz, the delay slot is 11 = move v1,v0. Then jal at 12... Hmm, a branch to the call. Actually `if (t < 0) { call; return; }` compiles as `bltz v0, L; ...` where L is the call block.

Wait but move v1,v0 in the delay slot of bltz means raw = t executed always (speculatively). That matches `raw = t;` before the if... no, in source `raw = t` is after the if. Hmm, reorg could move it into the delay slot.

Hmm, actually the order: `t = raw - 0x10; if (t < 0) {...}` then `raw = t`. The branch bltz's delay slot could be filled with `move v1,v0` (raw = t) since it's the fall-through instruction... but source order has the if block first, then raw=t. Reorg fills delay slots from the fall-through path. So insn 10 = bltz v0, L; 11 = move v1,v0 (from after the if, moved into the delay slot); then 12-15 = the taken path (jal; move a0,s0; j; nop), and 16 = move v0,v1 (t = raw) continuing the fall-through.

Wait, but if bltz jumps to the call path, the call path is placed at 12-15 after the delay slot. So the layout is: bltz v0, 12? Then fall-through would be 11... hmm no.

Whatever — the key is the target has both copies. Let's dump the actual target and mine asm to see.

Let me find how delever_search --try --keep gives the object. Or use tools to disassemble. Simpler: use --explain? Let me check what tools exist: tools/cc1_dumps_tu.sh, tools/alloc_table.py. Also maybe there's a dump of the target in build/. 

Let me just run --try with --keep and disassemble with objdump. Actually sc.sh/dt.sh don't pass --keep. I can call delever_search directly.

Let me look at what's in .run/3.40/logs/T11_G22_c1.log — only 18 lines, that's the whole thing.

Approach: I'll write candidate bodies and score. Let's think about what plain C can produce both moves.

Key insight: In the orig, `raw` is pinned $3 and `t` pinned $2. Both pins are row kinds and must go. The launder forces raw to be "reborn" so cse doesn't equate raw with t after `raw = t`. Then `t = raw` copies back.

Lever-free alternatives: make raw and t have different machine modes so cse can't merge: e.g., declare `raw` as `u8` and `t` as `s32`? Let's think:

```c
u8 raw;
s32 t;
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) ...
raw = t;
t = raw;
```

- `raw = *(u8*)(s1+0x24)`: lbu.
- `t = raw - 0x10`: raw (u8) is promoted to s32; addiu.
- `raw = t`: store low byte of t into raw's pseudo (a QImode subreg set). That's `move v1,v0` if raw is in v1.
- `t = raw`: zero-extend raw to s32 → andi 0xff possibly, or if raw's value is known in range... Hmm, `raw` is u8 so t = (s32)raw requires andi 0xff unless gcc knows. Actually if raw = t where t was raw-0x10 ≥ 0 and ≤ 0xEF... gcc's range analysis might know. Risky.

Alternatively `s16 raw`? Hmm.

What about making the two variables genuinely different: maybe the original source was:

```c
u8 *s1;  // some struct
s32 raw, t;
...
raw = s1->unk24;
t = raw - 0x10;
if (t < 0) { ... }
s1->unk24 = t; s1->unk25 = t; s1->unk26 = t;
```

and the target really just has the moves because of pin+launder. But the task says produce lever-free body scoring 0 — i.e., the target asm must be reachable without levers. Maybe through some other real-C move. The moves.md catalog has many cases where the pins were replaced by real C moves (e.g., HImode copies, do-while, dead resets).

Here the moves needed: 
1. `move v1,v0` and `move v0,v1` — two copies between raw(v1) and t(v0). 

Hmm, wait. Maybe a different reading: The register pair mapping says "v0->v1 x2, v1->a0 x2". So mine has v0 where target has v1 (2 insns) and v1 where target has a0 (2 insns). The moves themselves: target 11 `move v1,v0` and 16 `move v0,v1`.

If I make raw and t the same pseudo (merged), there are no moves at all, and mine is 46 vs 47 (one insn short).

So we need two extra insns: the two moves. Plus reg assignment: raw in v1, t in v0, p in a0.

Idea: use a `u8` copy for one of them. E.g.:

```c
s32 raw, t;
raw = *(u8*)((u8*)s1 + 0x24);
t = raw - 0x10;
if (t < 0) {...}
raw = t;
t = raw;
```
With raw and t both s32, cse merges.

What if:
```c
s32 raw;
u8 t8;
...
```
Hmm.

Alternative: introduce a third variable? But must not add instructions beyond target.

Let's think about what the RTL looks like in target. raw in v1, t in v0. The moves: move v1,v0 (raw = t), move v0,v1 (t = raw). These are genuine copy insns in target. So the source must have had two variables that gcc keeps separate.

Consider declaring raw as `s32` but with a cast at the assignment from t: `raw = (s32)t;` — same type, merged.

Consider `raw` as `u8`:
- raw = lbu → raw is QImode.
- t = raw - 0x10: t = (s32)(u8)raw - 16. Hmm, `raw` promoted.
- raw = t: t's value (≥0) truncated to u8: a QImode copy.
- t = raw: (s32)raw zero-extend.

If gcc tracks that raw ∈ [0,255] after `raw = t` where t ≥ 0 (guarded by if(t<0) return), then t = raw needs no andi. And raw = t is a truncate... which for a value known < 256 is a plain copy. Hmm, gcc might still emit move (subreg).

But then the first `t = raw - 0x10` from u8 raw: gcc needs the zero-extended raw, which lbu gives.

Would that produce both moves? raw in v1 as QImode, t in v0. `raw = t` → move v1,v0 (QImode move? On MIPS, QImode move would be `move` since regs are 32-bit). `t = raw` → move v0,v1 (zero-extend of a value in reg; if known non-negative, plain move).

Register assignment: raw is used in: t = raw-0x10 (read), raw = t (write), t = raw (read). t used in compare and stores. Hmm.

Actually hold on. Let's reconsider whether the `move v0,v1` at 16 is `t = raw` or something else. Let me get the full target disassembly. I'll use the keep option.

Let me run: /usr/bin/python3 tools/delever_search.py --try <tu> func_800CB2C8 n1.c --body --keep  and see output path, then objdump.

Actually, better: maybe there's a disassembly helper. Let me check tools/ for a disasm script.
