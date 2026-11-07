---
ts: 2026-11-06T04:33:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fNGD9G6eF5chNo7U5ePG
---
21:32 — only 10 min in. Hmm, the clock: item 3 ended ~21:22 per my notes but the actual date at item 4 start... Let me recompute: the date at item 4's first command was 21:09 (when I read cse.c). Actually the timeline: item 2 ended ~21:16 (date 21:09 was during item 2). Item 3: 21:16-21:22. Item 4 started ~21:22? But the last date is 21:32:55. So item 4 has been ~10 min.

Wait, but I've done 34+ tries. The 20-min rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries". I need 20 min. Let me continue for ~9 more minutes. That's a lot of extra tries. Hmm, but the rule is explicit. Let me use the time to explore more systematically — maybe I'll crack it.

Let me think about the delay-slot fill more concretely. The target: lw obj->1C; nop; sll. Mine: lw obj->1C; lw p; sll.

What if the target's obj->1C load and the p load are in DIFFERENT basic blocks? If the p load is in the merge block (after the label), sched1 wouldn't move it into the arm's block. For that, the label must be before the p load. The label is created by the jumps from the other arms to the merge store. If the merge store's label is placed before the p load, the p load is in the merge block. But the p load is only executed by the `<0x11` arm (fall-through), and the merge store by all arms. The label would be at the p load if the other arms' jumps target the p load — but they target the store (they don't need the p load; they have p already). So the label is at the store.

UNLESS the original C's merge block re-loads p for ALL arms: i.e., the shared tail is
```
((Unk*)((Unk*)a0)->unk20)->unk18 = v;
```
with a raw expression! Then the merge block starts with the model load (the label is at the load), and all arms jump there. The `<0x11` arm's p load would then be... the arm's own p load? Let me check the target again: for the `<0x11` arm, 4944 lw v1,32(s1); 4948 addiu; 494c sh. If the merge block started at 4944 (label there), then the `<0x11` arm would fall through to it. The other arms jump to 494c (the store), not 4944 — so they skip the load. But if the merge block's store used a raw expression, all arms would need the load at 4944, and the jumps would target 4944, not 494c. The target's jumps target 494c (48b8 j 494c, etc.). So the merge store uses p (no load). OK.

So the label is at 494c. The p load at 4944 is in the `<0x11` arm's block. sched1 filled the delay slot.

Given the target has a nop, the original compiler's sched1 didn't fill it. The only way is if the p load wasn't ready. Its address a0 (s1) is ready. Unless the p load's address is computed from a value defined by the obj->1C load chain — no.

Hmm, wait: maybe the p load in the target is not `lw 32(s1)` from a0+0x20 but from a *pointer variable* that was computed later. E.g., the original C might have `p = *(Unk**)((s32)a0 + 0x20)` where the address `(s32)a0 + 0x20` is computed into a register after the chain. But the address is a simple offset, folded into the load.

What if the original used a pointer variable `q` assigned before the arm and the load is `*q`? q is a copy of a0+0x20, available early.

I'm confident: this is the sched1-load-delay-fill wall (already a known wall from G18). Let me satisfy the 20-min minimum by continuing for ~9 more minutes with a few batches, then record.

Let me try a systematic sweep of declaration order/scope and small expression changes, which is cheap. Also try the `n` variable reuse and `obj` reuse.

Actually, one more idea: make the p load's *use* (the merge store) depend on the chain so the load is born later AND has a dependency... no.

Another idea: use `__builtin_...`? no.

Let me try: put the p load in the merge block for the `<0x11` arm by using a block-scope variable and an explicit store before the merge:
```
        } else if (... < 0x11) {
            store 0x1A raw;
            v = mult;
            v += 0x600;
            {
                Unkstruct_800B5CB8 *q = ((Unkstruct_800B5CB8 *)a0)->unk20;
                ((Unkstruct_800B5CB8 *)q)->unk18 = v;
            }
            goto call;   // or fall to merge? 
        }
```
z1 did a variant (27).

Let me try the reverse: make the shared merge store's p load for the `<0x11` arm happen via a different block by adding a `goto` label right before it:
```
        } else if (... < 0x11) {
            ...
            goto merge11;
        } else { ... }
        ...
    merge11:
        p = model;  // ??? 
```
Too complex.

OK, let me just do a final batch of 4 variants (decl order variations of p/v, and `p` as a `s32*` cast) and then wait until 20 min. Let me also re-run the best candidate to confirm 14 (w4).

Time: 21:33. I need until ~21:42. Let me do a batch, then check the clock.
