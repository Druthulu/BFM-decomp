---
ts: 2026-11-06T15:00:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1tC9dbqEobIUfllit3P6
---
Good, control is 0.

Now the win.c: remove the launder asm on vol. Try plain drop first — expect the sched1 swap.

Let me create win.c from orig.c with the launder line removed, then score.

Approach: write a small script? Simpler: copy orig.c to win.c with sed? I need surgical edits. Let me use cp then Edit tool. Actually cp is a bash command; fine.

But careful: Edit requires reading the file. I'll write win.c via Write tool from the orig content? That's a whole-file write, which is allowed for new files. But the file is 102 lines, I have it in context. Hmm, but rewriting whole file is discouraged for edits... it's a scratch candidate file, fine.

Actually better plan: use `sed` to produce win.c variants from orig.c. Each candidate is a mechanical transform. But surgical text edits are easier with Edit on win.c after cp.

Let me do: cp orig.c win.c, then Edit to remove the launder line.

Wait, the launder line is:
```
            /* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)
```

Plan A: just delete it → score?

Then Plan B: replace with a real 2nd set: `vol = (s16)vol;` (no-op value-wise? vol = ((0xA0-av)*0x7F)/0xA0, range 0..0x7F, so s16 cast is value-preserving). Also `vol = vol | 0;`? Tree folds. `do { vol = (s16)vol; } while (0); // !FAKE: do-while`.

Also candidates from cookbook C0414: dead-reset `vol = 0;`? no, that changes value. C0535: do-while splits cse1 EBB.

Another: `vol = (vol & 0xFF);` adds andi → 238 ins, wrong unless target... target has no andi (237 ins). Hmm wait target 237 with the launder producing zero insns. So any added real insn breaks count. Unless a real 2nd set that emits no insn: `vol = (s16)vol` on an s32 var → conversion HImode then SImode; expand may emit nothing if it can just use a subreg, but it creates a SET in RTL? The evidence from G14 says `v0 = (s16)v0` gives a real 2nd set with no insn. Actually in func_8017D73C the target had a `sll/sra` pair... hmm. Let's just try.

Also worth trying: `vol = vol + 0;`? fold removes.

Let me also consider: is `vol` s32? Yes declared `s32 vol;`.

Let me try A first.
