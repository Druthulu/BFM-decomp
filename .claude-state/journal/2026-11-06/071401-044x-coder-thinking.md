---
ts: 2026-11-06T14:14:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ruk17MeuGbE5TYmXYdXY
---
The greg dump doesn't show priorities directly. Let me check if global-alloc prints the allocno order with -dg... It prints ";; Register dispositions" and assignments. Not priorities.

OK, let me just empirically test variants. Since the margin is razor-thin (i=12/live39 = 0.923 vs dst 0.917), even adding one ref anywhere in the loop might do it. But how to add a ref with real C without code change?

Idea: The `i++` is an increment. flow.c gives an EXTRA ref for increments (REG_INC). The comment at flow.c:2300 says "When a reg is incremented, spilling it is worse, so we want to make that less likely" — but that's for the post-increment optimization in a specific pass. Both i and dst are incremented, so both get it.

Hmm, what if I change `i++` to `i = i + 1`? That removes the REG_INC extra ref (the increment flag). That would LOWER i's refs. Bad.

What if I change `dst++` to `dst = dst + 2`? That would remove dst's increment extra ref, lowering dst's refs! If dst loses its increment bonus, dst refs drop by loop_depth. Then i wins. And the generated code? `dst++` vs `dst = dst + 2` — both produce `addu $11,$11,2`. The difference: REG_INC note. Would that change codegen? The REG_INC note might affect... Actually in the target, is dst++ generated with a REG_INC note? The target code is `addu $11,$11,2`. Both forms produce the same. But the REG_INC note could affect flow's ref count (which is what we want to change) and possibly other passes (loop.c, auto-inc).

Wait, but hold on: if dst loses refs, then the register allocation flips, and we WANT i to get t2. Let me test: change `dst++;` to `dst = dst + 2;`. But careful: the original is `dst++` (pointer arithmetic, +2 bytes). `dst = dst + 2` is the same. Let me test that variant.

Also `i++` -> keep.

Actually, let me reconsider whether removing dst's increment ref is enough. dst refs 11 -> maybe 8 or 9. Priority drops well below i's 0.846. Then i wins. But wait — would that also affect the scheduling (sched1 uses its own priorities, not n_refs)? sched1 uses INSN_PRIORITY computed from dependency depth, not reg refs. Actually sched1's priority includes `INSN_PRIORITY` (critical path length) and maybe REG_N_REFS? Let me check sched.c priority. But let's just test.

Let me create variant c2: `dst++;` -> `dst = dst + 2;`.

Wait, but there's a subtlety: in C, `dst++` for a `u16 *` adds 2. `dst = dst + 2` also adds 2. Fine.

Let me create the variant and score. Also try `i++` -> `i = i + 1` as c3 (probably worse).

Actually, better: since we need i to WIN, lowering dst is the lever. Let me test several:
- c2: `dst = dst + 2;` (lower dst refs)
- c3: `src = src + 1;`? no, src increments by 2.
- c4: `src += 1`? src is u16*, +=1 adds 2.

Hmm, also we could raise i by making it incremented twice? no.

Let me test c2.

I'll generate variants with a script that does textual replacement on orig.c. Let me write variants directly via Python (script under .run). Actually I can use Edit on a copy? The files are scratch. Let me write a small script that takes replacements. Simpler: use python script `mkvar.py <src> <out> <old> <new>`.

Let me write it.
