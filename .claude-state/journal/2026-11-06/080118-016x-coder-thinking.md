---
ts: 2026-11-06T15:01:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_87GfZbUg9tdRBS6zTGyP
---
Note sc.sh does `cd /home/musashi/bfm-decomp` inside a subshell — that's the helper, fine.

Let me generate variants with a python script that does textual substitution on orig.c, writing a2..a8. That's cleaner than many Edit calls.

I'll write .run/P40/T11/O04/gen.py that takes a base file and a substitution spec... Simpler: a script per item? Let me make a generic generator: gen.py <base> <out> <mode> where modes map to replacement strings for the launder line.

Actually simplest and most flexible: a small script `mk.py` that reads a template file containing `@@` placeholder... Hmm.

Let me just write a python script that applies a list of (old, new) pairs given in a small spec file. Overkill.

Alternative: use Edit on separate copies. For 6 candidates that's 6 cp + 6 edits = 12 calls. Too many.

Better: one python script per item that emits all variants from orig.c using explicit code. It's a scratch script under .run, allowed. Let me write mk1.py for item 1 emitting a2..a9 with different launder replacements.

The common anchor: line `            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder ...` plus the preceding comment line. I'll replace the two-line block with a given snippet.

Variants:
1. `vol = (s16)vol;`
2. `do { vol = (s16)vol; } while (0);  // !FAKE: do-while`
3. `do { } while (0);  // !FAKE: do-while`
4. `vol = vol & 0xFF;` (andi)
5. `vol = (u8)vol;` (andi 0xff)
6. `sx = sx;` hmm no.
7. `vol = (s32)(u16)vol;`
8. `{ s32 v2 = vol; vol = v2; }` (copy → cse merges)

Also possibility: reorder statements — the comment says source order doesn't move it (9 spellings swept).

Hmm. What about a different real 2nd set: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` computed into a temp then assigned: `s32 t2 = ...; vol = t2;` — that's a copy which cse merges.

Another thought: The 236 vs 237 difference. Target has one more insn. Which one? From the diff at 194-200: mine has `sra a3,v0,0x10; bgez a3; move a1,a3; negu a1,a3; lui a2,0x6666; ori a2..; addiu a0,a3,160` and target `sra a2,v0,0x10; bgez a2; move a1,a2; negu a1,a2; lui a0,0x6666; ori a0,..; --`. So target's addiu a0,a3,160 exists elsewhere.

Register pair count a3->a2 x7: so mine's a3 should be a2 throughout the tail. That's an allocation difference: mine gives vol to a3, target a2. In target, a2 is used... Since the pin $5 av stays (a1), and vol gets a2 in target.

What makes local-alloc/global-alloc assign a2 vs a3? qty priority. With the launder, vol's ref count... the asm is a use+def of vol, adding a ref (2 refs more: "=r" def, "0" input use). So the launder increases vol's priority so it gets $a2 (lower-numbered / higher priority?) instead of $a3.

So to keep vol in a2 we need to add refs to vol — but the insn count must stay 237, meaning no new emitted insn... unless the target's 237 comes from elsewhere.

Wait, target is the current src = with launder = 237 insns. Mine without = 236. So removing the launder ALSO lost an insn. Which insn? Since asm "" is zero insns, the lost insn is a real insn that was present before. Possibly the `negu a1,a3` vs `negu a1,a2`... Let me diff full listings to see which insn disappears.

Let me look at the whole diff (a1 vs target) — that's ~30 score so many diffs, but the count difference means one insn missing somewhere. Let me run dt with more tail and look at the "missing"/"extra" markers.

Actually better: use --explain? It reads residual (no writes). Same as dt.

Let me just get the full diff into a file and read it. dt.sh prints score + diff tail. Use tail 200.

I'll run and capture. Output may be long → use run.sh? The rule: >40 lines runs through tools/run.sh. Let me use run.sh with a name.

Actually simpler: `bash .run/P40/T11/bin/dt.sh ... a1 300 > .run/P40/T11/O04/item1/a1.diff` then read the file. But writing output redirect is fine. Hmm, but dt.sh's tail is applied to the whole output; redirect works.

Let me do that and read.
