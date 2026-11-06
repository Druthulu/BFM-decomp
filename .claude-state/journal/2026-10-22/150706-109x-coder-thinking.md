---
ts: 2026-10-22T21:07:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0bTsGPr17POowja1O8GG
---
i4/i5 add insns (5), i6 adds an insn (3).

I've spent 25 min on item 3. Best = 2 (e1/f1/h1/h2/h3/f2/f3). Let me record best 2 with the sched1 tag and note e1 as the best body.

Wait — before that, let me check whether the remaining 2-diff could be fixed by the *store* order. In f1, by is at 72 and bx at 73, ax at 74. The target: by 72, ax 73, bx 74.

What if I move the `bx = bx - 0x57;` statement to *after* `ax` but keep ax's uid before... that's the source (by, ax, bx) = gen_o3 → ax first.

What if I write the bx re-set as the *last* statement of the block (after the prim stores)? Semantically bx's new value is needed by prim.y1 = bx. If I write `prim.y1 = bx - 0x57;` and then `bx = bx - 0x57;` after? The store would need the new value; cse merges.

What if the prim stores use a temp for bx: `s16 nbx = bx - 0x57; prim.y1 = nbx; ...; bx = nbx;`? Extra move.

Hmm, what about making `ax` depend on `bx`'s *old* value in a no-op way that sched1 sees as a dependency: `ax = ay + 0x7B;` → `ax = ay + 0x7B;` with a dummy `(bx & 0)`. Folded.

What about `ax = ay + 0x7B + (by - by);`? folded (by-by=0).

Since CSE/combine remove identity arithmetic, no.

OK: best 2. Let me also check: maybe the target's order by, ax, bx arises from sched2 rather than sched1? Doesn't matter.

Record: item 3 WALL, best 2, tries 60+~20 = 80, tag sched1-birth-order (or a new tag). Evidence: "sched1 puts ax's addiu before by's when the source is by,ax,bx; with by,bx,ax it keeps by,bx,ax (ax one late); best 2 ORDER (by/ax swap only)".

Hmm, the tag name: the mechanism is sched1's ordering of two independent addiu's; the target keeps by,ax,bx. `sched1-birth-order` is fine as a new tag.

Let me update the results row (it currently says best 4) to best 2 and tries 80, and rewrite the notes. Then finalize.

Also, I should double check e1 is truly lever-free: it has no launders; it keeps the pins $23, $20, $7 (pre-existing). Let me verify no `__asm__` except the pins and no `register` beyond the pins. e1 = gen_o3 + the prim changes. gen_o3's diff from orig showed only the launders removed and the `ax = (u16)ax;` added. Let me grep e1 for asm/launder.
