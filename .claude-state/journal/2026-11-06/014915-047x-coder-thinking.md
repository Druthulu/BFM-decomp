---
ts: 2026-11-06T08:49:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BG0e2BzS5eaVNRLqQaTU
---
Interesting! The combine dump shows the structure:
- insn 124: (set reg78 reg77) — this is the if-branch copy (then-block), followed by an unconditional jump to 136 (join). So the then-block is `val = nudge; goto join;`.
- label 128: else-block start.
- insn 265: (use reg78)  ← this is suspicious.
- insn 134: (set reg78 (neg reg77)) — the merged else.

Wait, but insn 265 with `(use reg78)` — where from? It has `(nil)` reg notes. Hmm.

OH. I think I misread the combine dump's ordering: combine's dump might be printed *per function before combining*? The statistics line "65 substitutions (18 requiring new space), 7 successes" then the RTL. This RTL has `(insn_list 100 ...)` notes — those are LOG_LINKS from combine, which appear after combine. And `(use reg78)` could be a combine-created insn? Combine doesn't create USE insns.

Hmm, actually: GCC 2.7.2's combine, when it merges a set into a use and the set's value is needed elsewhere... no.

Wait, maybe `(insn 265 128 130 (use (reg/v:SI 78)))` is actually the **asm** from the *other* function? No, we're inside func_80187988.

Let me search the cse dump for insn 265 and the .combine for where 265 was created. Alternatively, maybe the dumps aren't from my c1 scratch but from a stale p3 dir! The p3 scratch I dumped: I ran cc1_dumps_tu.sh on .run/P36/engine/score/ov_SC02_000__func_80187988/p3/... — but the --keep run earlier (the one that printed p3) was for c1? I ran `--try ... $D/c1.c --body --keep` and it printed p3. Yes. But wait — did it print p3 for the c1 run, or was that an earlier run? The output said "--keep: candidate object .../p3/cand.o". Hmm, "p3" for both items' scratch. The p3 dir is reused; the c1 run overwrote it. OK.

But the scratch .c I grepped has no keepalive at 5878, so it's c1. Then why a `(use reg78)`?

Hmm, let me look at insn 265 more carefully: `(insn 265 128 130 (use (reg/v:SI 78)) -1 (nil))`. Wait, maybe this IS from the asm: the c1 body I generated with `sed '/!FAKE: keepalive/d'` — the asm line is removed. But hold on: is the scratch TU regenerated from the *candidate body* spliced into the TU, or does the tool substitute only the function? The scratch .c at 5875/5877 has `val = nudge;` twice — and at 5876? Let me print the else block of the scratch.
