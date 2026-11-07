---
ts: 2026-11-06T15:01:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_37wRvh8NgzhRwhblnaJc
---
So the target (with launder) has 237 insns: the difference is at 200-217: target computes vol's magic mult with `lui a0,0x6666; ori a0` and `mult a0,a2` where a0 = av+160? Let's parse.

Target:
```
194 sra a2,v0,0x10        ; sx = (s16)sxy  → a2 (sx)
195 bgez a2
196 move a1,a2            ; av = sx
197 negu a1,a2            ; av = -sx
198 lui a0,0x6666         ; magic for /0x14? 0x66666667
199 ori a0,a0,0x6667
200 addiu a0,a2,160       ; wait, that overwrites a0...
```
Hmm mine:
```
194 sra a3,v0,0x10
195 bgez a3
196 move a1,a3
197 negu a1,a3
198 lui a2,0x6666
199 ori a2,a2,0x6667
200 addiu a0,a3,160      ; a0 = sx+0xA0
201 mult a0,a2
204 mfhi a3
```
Mine: 200-201 are the pan division (sx+0xA0)/0x14 using magic in a2 → mfhi a3. Then 207-211: vol = ((0xA0-av)*0x7F)/0xA0 using mult v1,a2?? hmm a2 magic shared.

Wait mine 207: `mult v1,a2` then `sra a0,a0,0x1f`... confusing.

Anyway, the point: with the launder, sched1 hoisted the PAN multiply first, then vol; without, vol first. And target has one more insn because... In target at 200: `addiu a0,a2,160` then mult v0,a0 — hmm.

This is the classic "both magic multiplies write the same match_scratch" issue.

So the fix: make vol have a real 2nd set so sched1 doesn't move the pan mult before vol's. Wait, actually the launder makes the vol computation come FIRST (before pan) — target order: at 198-201, the magic 0x66666667 (pan divisor /0x14) is loaded, `addiu a0,a2,160` (sx+0xA0), `mult v0,a0`?? Hmm, let me get the target listing to see properly. Not necessary.

Goal: 237 insns, vol in a2, and the pan mult after vol's.

Key: a3->a2 x7 means mine's vol pseudo got a3 while target's got a2. In target, a2 holds sx (194 sra a2) and also the pan result. Hmm target 217: `sll a2,a2,0x8` = pan<<8. So a2 = pan (the reused sx). So sx/pan is in a2, and vol in...? mine 217 `sll a3,a3,0x8` where a3 = pan (since mine's sx got a3). So the swap a3<->a2 is: mine has sx/pan in a3, target in a2. Because vol took a2 in target (higher priority) pushing sx to a3? no...

Actually the "register pairs (mine -> target)" says mine's a3 should be a2: i.e. mine's sx/pan register a3 should be a2. And where's vol in each? Target 207-217: `mult v1,a0`, `mfhi t1`, `sra a0,t1,0x6`, `subu a1,a0,v1` → that's vol computation in a1? Then `sra v0,v0,0x1f; mfhi a2; sra v1,a2,0x3; subu a2,v1,v0` → pan in a2.

Mine: 207-215: `mult v1,a2; sra a0,a0,0x1f; sra v0,a3,0x3; subu a3,v0,a0` → pan in a3; `mfhi t1; sra v0,t1,0x6; subu a1,v0,v1` → vol in a1.

So both have vol in a1! The difference is only sx/pan a3 vs a2. So vol's register isn't the issue; it's sx's register and the instruction schedule/count.

Why does the launder push sx from a3 to a2? Because with the launder, vol has an extra use (the asm) at that point, extending vol's live range, so vol can't take a2...? But vol is in a1 both times. Hmm.

Rather: the asm's tied operand forces vol into a register at the point between; maybe local-alloc's ordering (a2 vs a3) changes because the asm pseudo (a new pseudo? no, tied "0") ...

Anyway: the practical approach is to find a plain-C 2nd set of vol that (a) adds no insn, (b) restores the schedule and the a2 choice.

Hmm, but wait: a "real 2nd set" would create a *new* insn unless it's value-preserving-cast that expands to nothing. In G14, `v0 = (s16)v0` produced a real 2nd set with no insn — because the cast to HImode and back is a SUBREG, so the SET is a (set (reg) (subreg (reg))) which... would need an insn? Actually in RTL a (set (reg:SI x) (subreg:SI (reg:HI y) 0)) is a real move insn → emitted as `move` or coalesced away.

Alternatively the trick from moves.md 187: `-> empty do { } while (0)` — a zero-width barrier that splits the EBB. That keeps 0 insns. Does it affect allocation? It splits cse1's EBB, so sched1 sees different EBBs (scheduling barrier at the loop/branch?) Hmm.

Let's just try a batch of candidates. That's the fastest path.

Candidates for item 1:
- a2: `do { } while (0);  // !FAKE: do-while`
- a3: `vol = (s16)vol;`
- a4: `do { vol = (s16)vol; } while (0);  // !FAKE: do-while`
- a5: `vol = (u16)vol;`
- a6: `vol = vol + 0;`? probably folded; skip.
- a7: `vol = (s32)(u16)vol;`
- a8: reorder: compute sx first then vol (statement order swap) — the comment says 9 spellings tried, all identical, but that was for the launder-in-place. Worth one try.

Also possible: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` → split into two statements: `vol = (0xA0 - av) * 0x7F; vol = vol / 0xA0;` — a real 2nd set of vol, value-preserving, no extra insn (the div by constant is a magic mult; splitting doesn't change insns since it's the same computation, just separate statements → 2 sets of vol). That's a genuine "real 2nd set" in the C0505 catalog (temps/splits). This might work well: it makes vol multi-set so sched1's birth-boost is killed.

Similarly `vol = (0xA0 - av) * 0x7F;` then `vol /= 0xA0;`.

Let me write the variants generator.

Also: does `av` remain pinned? Yes, allowed (pin not a row kind here). Note "no new lever of any kind" — we keep the $5 pin as is.

Let me write mk1.py generating candidates from orig.c by replacing the launder block.

I'll make it generic: a script that takes a base file, an output, and a replacement snippet from argv, replacing the two-line block (comment + asm). But argv with newlines... fine with shell quoting. Better: a spec file. Let me write a python script that takes base, out, and a snippet file.

Simplest: write .run/P40/T11/O04/mk.py:
usage: mk.py <base> <out> <snippet-file> [anchor]
- reads base, finds the line containing `__asm__("" : "=r"(vol) : "0"(vol));` and the preceding comment line, replaces both with snippet content.

Let me generalize: replace from the line matching `/* lever 3:` through the asm line.

I'll write it.
