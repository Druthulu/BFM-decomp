---
ts: 2026-11-06T11:42:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_gW6LBuBoDw6EIrD02Cvm
---
That's 2*3*4*2*3 = 144 candidates. Too many (144 * 4 s ≈ 10 min). Let me trim: the tagpos "early"/"late" may produce wrong code? "early" puts the load before x+=w_ (source base already has it before the adds: base source is tag2 load then x+=w_). My group2 "base" doesn't emit the load at all! Bug: in group2, tagpos == "base" emits no tag2 load — the load must exist. Let me fix: "base" = load first (like source), "early" = load before... hmm I need distinct positions:

Positions relative to the body:
- "first": tag2 load at the top of group2 (source order).
- "afterx": after the x stores block (after *(s16*)(p+0x18) = vx) — i.e. after x += w_ and its stores.
- "late": after all stores, before pmask.
- "verylate": after pmask, before the tag store.

Let me restructure group2 with tagpos in {first, afterx, late}.

Also 144 is too many. Let me cut: g1s 2 × add 3 × tagpos 3 × tagstore 2 × masks 3 = 108. Still a lot. Reduce masks to ("", "2") and tagstore to plain only for the first sweep: 2*3*3*1*2 = 36. Good.

Let me rewrite the generator.
