---
ts: 2026-11-06T17:03:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZdUuchBdm3ryaAx5KvOz
---
Time is 10:02:44 (not 10:09 — I misjudged). Item 4 started ~09:56:30. So ~6 min in. I have time.

Wait, let me recompute the timeline: item 2 at 09:44, item 3 09:44-09:54, item 4 ~09:55. Now 10:02. So ~7 min on item 4.

Let me continue trying to crack item 4. The residual is one instruction. Let me think about the cse cache differently.

The `addiu s1,sp,32` appears because cse decides to compute &m once. In y01 it doesn't. The difference: y01 has the s-launder asm before the copy block. An asm is a cse barrier: cse's `cse_insn` for an asm with a memory clobber? The s-launder is `asm("" : "=r"(s) : "0"(s))` — no memory clobber. Hmm, but asm insns are opaque; cse doesn't look inside. The equivalence table isn't cleared by an asm unless it clobbers memory.

Hmm, wait: maybe the difference is that in y01 the copy block is hand-expanded (t0/t1/t2 with pins), and the pins force specific registers. The pinned t0=$3, t1=$4, t2=$5 are HARD registers. The struct assignment's carriers are v1/a0/a1 (same). 

And the s-launder ties s (the source base) to a register. In the target, the source base is a2. The hand-expanded copy uses a2. The struct assignment also uses a2. Same.

So the difference for the &m cache must be the presence of the asm (s-launder) affecting cse's equivalence tables. Since I must remove all launders, I need another cse barrier — but a real-C one.

Hmm! What about the *pins*? The t0/t1/t2 pins are asms too (register asm). They're "pin" kind, allowed to stay! The pin declarations `register s32 t0 __asm__("$3")` are not asm statements, they're register declarations. But in the hand-expanded copy, t0/t1/t2 are used. In the struct assignment, they're gone.

Wait — the row kinds for item 4 are "keepalive,launder". The pins are other-kind, allowed to STAY. So I could keep the hand-expanded copy with t0/t1/t2 pins! The s-launder is a launder (must go), and the keepalive is a keepalive (must go). The q-launder is a launder (must go).

So: keep the hand-expanded copy (with the t0/t1/t2 pins), remove the s-launder, the keepalive, and the q-launder (dead-reset).

But removing the s-launder gives the D_800AE620 remat (x1 = 19). Hmm. Unless the pins help? In x1 the pins are still there (I only removed the s-launder) → 19. So no.

OK so the struct assignment is needed for the source base, and it costs the &m cache.

Alternative: keep the hand-expanded copy AND make the source base a register without the s-launder. What if `s` is one of the pinned registers? The pins are t0=$3, t1=$4, t2=$5. What if I use t0 as the base pointer? `register Blk20 *s __asm__("$3")` — but that's a NEW pin (adding a lever of another kind — forbidden: "never added").

Hmm, the constraint: "levers of other kinds the def already had (pins under other causes) may stay, never added". So I can't add a pin.

What about using the existing t0 pin as the base? t0 is `register s32 t0 __asm__("$3")` — a s32, could be cast to a pointer? `t0 = (s32)&D_800AE620;` then `((Blk20*)t0)->w[0]`... That uses the existing pin for the base! Is that "adding a lever"? The pin already exists; using it differently is a source change. Hmm, borderline. It might be considered using an existing lever, not adding one. But it changes the pin's role (the copy carriers). Risky but let me think: the target's copy block uses a2 as the base, not $3. So pinning the base to $3 would be wrong.

OK.

Alternative: the struct assignment + accept the &m cache but *force remat* by making the second &m use in a different basic block. E.g., put the func_800484EC call after a label/branch that splits the block. Hmm, the vec assignments are between: `vec[0]=0x4000; vec[2]=0; vec[1]=0;` — these stores are between RotMatrixY and func_800484EC. They're in the same block.

What if the RotMatrixY call is inside a `do{}while(0)` (C0535) to split the cse EBB? C0535 says do-while(0) splits cse1's EBB. If the RotMatrixY call is in a separate EBB, cse might not carry &m across! Let me try:
```
do {
    void *q = &m;
    RotMatrixY(ang & 0xFFF, q);
} while (0);  // !FAKE: do-while
```
Hmm, the do-while adds a block boundary in the CFG? It creates a NOTE_INSN_BLOCK_BEG/END, and cse processes basic blocks (EBBs), so a block boundary might split it. C0535's mechanism: "The block boundary splits cse1's extended basic block, so the copies are not merged/re-ordered there".

Let me try wrapping the RotMatrixY statement in a do-while(0) and the func_800484EC statement too.

This is a real-C construct with the marker. Let me test.
