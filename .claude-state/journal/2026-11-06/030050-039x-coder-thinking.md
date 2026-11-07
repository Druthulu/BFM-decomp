---
ts: 2026-11-06T10:00:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_uCvqfrKV8mIoNCipbkDg
---
I can create a spliced TU (like --try does) and dump cc1 passes. But simpler: the candidate body is spliced into a scratch copy of the TU. I can build that scratch TU myself under my item dir, then run cc1_dumps_tu.sh on it with DUMP_ROOT under my item dir.

But actually, for a 7-score function, maybe easier to just brute-force real-C variants. Let me think about the -dl (local-alloc) dump to see the qty priorities. That would tell me exactly why t gets v1.

Let me create the spliced TU. I can write a small script using delever_search.body_span to splice. Actually --try does it; I can replicate: take src file, replace function span with body text, write to my item dir, then run cc1_dumps_tu.sh with DUMP_ROOT=.run/P40/T11/G28/<item>/dumps and delete after.

Let me write a helper splice.py. Actually I can use python inline? "Scripts, not inline python -c". Let me write a script.

Hmm, this is getting heavy for a 7-score item. Let me first try a handful of cheap C variants and see if any flips t/tb. Time budget 20-30 min for this item.

Cheap variants:
A) Declare `tb` before `t` (decl order) — qty numbering tie-break only.
B) Make tb `u16 tb;` — different size.
C) Make t `s32 t` and tb `s32 tb` but use tb only once by storing directly: `((Unkstruct*)s0)->unkE = ((Unkstruct*)s0)->unk54;` — removes tb variable → one fewer qty; then t gets v0? and the direct load gets... hmm.
D) Direct store without temps for all three: `s0->unk6 = s0->unk4C; s0->unkE = s0->unk54; s0->unkA = s0->unk50 - 8;` — no temps, allocator uses scratch regs; target has distinct v0/v1. Might match! Target: lw v0,76; sh v0,6 (temp v0); lw v1,84; sh v1,14; lw v0,80; addiu v0; sh. With no temps, each statement's scratch would be a fresh pseudo → local-alloc assigns in birth order by priority; each lives 2 insns, nrefs 2 (1 def+1 use) → pri 2/2=1 for all three, tie → qty number order → first gets v0, second v1, third v0 (since v0 freed). That matches target! t(unk4C)→v0, tb(unk54)→v1, u(unk50)→v0. 

But the source already uses temps t/tb. Why? Because the original author needed temps for something? Let me check: the target code for unk50: lw v0,80; addiu v0,v0,-8; sh v0,10. With direct `s0->unkA = s0->unk50 - 8`, GCC emits exactly that (lw v0; addiu v0; sh). Yes.

And unk4C: `s0->unk6 = s0->unk4C` → lw v0; sh v0. Yes.
And unk54: `s0->unkE = s0->unk54` → lw v1; sh v1. Yes.

So variant D (no temps) might match! But wait, will the three scratch pseudos be separate qtys? Each statement creates a temp for the load result. They might be combined into one qty by local-alloc's combine_regs if... they're in different statements but the same block; local-alloc combines quantities when a reg is copied. Here no copies. They'd be separate.

Let me try D. But the struct types: `((Unkstruct_800CD314 *)s0)->unk6` etc. unk6 is presumably s16 or u16; the store `sh`. Let me just write:

```
((Unkstruct_800CD314 *)s0)->unk6 = ((Unkstruct_800CD314 *)s0)->unk4C;
((Unkstruct_800CD314 *)s0)->unkE = ((Unkstruct_800CD314 *)s0)->unk54;
((Unkstruct_800CD314 *)s0)->unkA = ((Unkstruct_800CD314 *)s0)->unk50 - 8;
```
Keep `t`/`tb` declarations unused? Unused vars are fine but might affect nothing. Better remove them (but removing declarations is a body change, allowed). Actually unused variables don't emit code.

Let me create v3.c from nopin.c replacing the block. The current block lines:
```
            t = ((Unkstruct_800CD314 *)s0)->unk4C;
            ((Unkstruct_800CD314 *)s0)->unk6 = t;
            tb = ((Unkstruct_800CD314 *)s0)->unk54;
            ((Unkstruct_800CD314 *)s0)->unkE = tb;
            ((Unkstruct_800CD314 *)s0)->unk30 = 0;
            t = ((Unkstruct_800CD314 *)s0)->unk50;
            ((Unkstruct_800CD314 *)s0)->unkA = t - 8;
```
Replace with direct stores, keeping unk30=0 in place.

Let me write v3.c with sed carefully, or use python script. Let me use sed with line ranges? The file is 47 lines. I'll use a small python script to do replacements? The rule says scripts not inline python. Let me just use sed with a unique pattern.

Actually easier: use `sed` to replace each assignment. Let me construct v3 from nopin.c:
- `t = ...unk4C;` → delete
- `->unk6 = t;` → `->unk6 = ((Unkstruct_800CD314 *)s0)->unk4C;`
- `tb = ...unk54;` → delete
- `->unkE = tb;` → `->unkE = ((Unkstruct_800CD314 *)s0)->unk54;`
- `t = ...unk50;` → delete
- `->unkA = t - 8;` → `->unkA = ((Unkstruct_800CD314 *)s0)->unk50 - 8;`

Let me do it.
