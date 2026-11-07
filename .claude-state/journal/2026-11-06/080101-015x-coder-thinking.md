---
ts: 2026-11-06T15:01:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FuhC9pEnT2srj7liICtn
---
Plain drop: score 30, 236 ins (one insn short: the target has the extra insn from... hmm 236 vs 237 — the launder being removed loses one insn? But the launder is zero-width. Wait, the launder asm creates an RTL insn that can affect scheduling, not insn count. Actually the target has 237 and mine 236 — so the launder, being an asm with tied operand, caused... hmm, maybe it prevented a merge so one extra insn existed. Actually target has one extra: e.g. `lui a0,0x6666`... mine at 200 has `addiu a0,a3,160` while target has `--`. So the schedule differs.

Key evidence: register pairs a3->a2 x7: mine uses a3 where target uses a2. Interesting — the launder made vol live in a2? Hmm, mine 236 vs target 237.

Let me think about the mechanism. The launder `__asm__("" : "=r"(vol) : "0"(vol))` — tied operand forces vol into a register at that point, and importantly it's an opaque insn. Its removal changed allocation (a3 vs a2) and count.

So we need a real 2nd set. Try `vol = (s16)vol;` — but that emits sll/sra pair? For s32 → (s16) → back to s32 in gcc 2.7.2, the conversion might be a subreg which expand handles as no-op if the value is known to be in SImode... Hmm, in G14 notes: "v0 = (s16)v0 (a real 2nd set)". Let's check how it was spelled there. Let me look at the actual win.c from a G14 match, e.g. func_8017D9D8 or func_8017EF0C. Are those available? They'd be in .run/P40/T11/... shards from earlier batches. Let me grep moves/other shard dirs for "v0 = (s16)v0".

Actually the moves.md entries reference them. Let me find a win.c with a do-while 2nd set to copy the idiom. Search in .run/P40/T11/*/*/win.c for "(s16)".

But careful about ls/find outside project — searching inside .run/P40/T11 is fine but "never ls/find outside the project" — inside is OK. But large listings? Use grep -l with a narrow scope.

Let me try candidates directly; faster. Candidate a2: replace with `vol = (s16)vol;`.

Also candidate: `do { } while (0);` alone (C0535 EBB split) — but that doesn't create a 2nd set; the moves line 187 shows it worked for one item.

Also `vol = vol;`? deleted by tree folder probably.

Let's try a few in sequence: I'll write a script that generates variants? The brief allows bin/sc.sh <itemdir> <files…> (one line per candidate) — scores several candidates in one line each. 

Let me create candidates a2..a6 with different spellings and run sc.sh.

Candidates:
- a2: `vol = (s16)vol;`
- a3: `do { vol = (s16)vol; } while (0);  // !FAKE: do-while`
- a4: `vol = (u16)vol;` (would add andi 0xffff — probably 238 ins)
- a5: `vol |= 0;`? no.
- a6: `do { } while (0);` (empty do-while, C0535)

Also consider that the issue is a3->a2 allocation plus one missing insn. Since target uses a2 and mine a3, and target has an extra insn. Hmm, maybe the launder's presence made vol's live range start later... 

Another idea from cookbook C0414: dead-reset as cse-breaker. Not applicable to sched.

Let me look at the diff more closely to understand which insn is missing. Let me see full diff of a1.

Actually, let me be efficient: create variants and use sc.sh.

First let me check sc.sh usage.
