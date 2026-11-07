---
ts: 2026-11-06T04:06:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_o0RcrtYn0TI2BkYKt1Oj
---
c2: one load, plus a nop. Score 13.

So do-while doesn't help here.

Let me reconsider the possibility that the ORIGINAL source had the `+=` as a **read-modify-write with the load of 0xE first**, and the two 0x2E loads separated by a **store** in the RTL. What if the original wrote:

```
*(u16 *)((s32)s0 + 0xE) = *(u16 *)((s32)s0 + 0xE) + (*(s16 *)((s32)s0 + 0x2E) << 6);
```

RTL order: load 0xE, load 0x2E, shift, add, store 0xE. No store between the two 0x2E loads.

But the target order is: lh 0x2E (diff), lhu 0xE, subu, lh 0x2E (x2), sll, sll, addu, sh. The scheduler reordered to put lhu 0xE between. Fine.

Hmm, what if the ORIGINAL had a store between the two loads that got eliminated by the **compiler itself** (e.g., a store that combine merged)? No.

Let me reconsider the first load. Maybe the first `lh v0,46(s0)` is NOT `*(s16*)(s0+0x2E)` in the diff block but the `diff` block's load is actually from a different expression that the decompiler approximated. E.g., `diff = 8 - ((Unk*)s0)->unk2E` where unk2E is `u16` (lhu)? But target is lh. What if the original used `s16` field.

OK, radical idea: maybe the original source had a **function call or asm** between them in the ROM? No, the ROM is compiled code; if there were a call, it'd be in the target.

Let me look at this from the "what does the ROM target require" angle: We need the second load. Plain C options that produce a second load:
(a) volatile
(b) a memory-clobbering operation between (store or call) — none available without adding insns
(c) cse's table entry removed by a **set of the value register** — requires an extra assignment (extra insn)
(d) the first load not recorded because `do_not_record` — volatile/asm
(e) different address expression that cse can't equate — try hard to find one that folds to the same instruction

Option (e) is most promising. What expressions produce `lh 46(s0)` but have different RTL address trees that cse's exp_equiv_p would consider different? 

cse's HASH and exp_equiv_p operate on canonicalized RTL after `canon_reg` and `fold_rtx`. The address for `*(s16*)((s32)s0 + 0x2E)` is `(plus (reg s0) (const_int 46))`. Any constant-offset access folds to that. But what if the offset is a *symbolic* constant? E.g., `*(s16*)((s32)s0 + (s32)&D_80126954 - (s32)&D_80126954 + 0x2E)` — folds.

What if the offset is computed at runtime from a variable that cse can't prove constant? Then it'd emit extra instructions.

What about accessing through a **SUBREG** or different mode then converting? E.g., load a 32-bit `lw` at 0x2C and extract bits 16-31: `(s16)(*(u32*)(s0+0x2C) >> 16)` → lw + sll/sra, extra insns. No.

What about a `s16` access via a struct with a **bitfield**? Extra insns.

Hmm, option (c): add an assignment to the value register that is not dead. What if we write the diff expression to REUSE the load result register for `t`? e.g.:
```
s32 x = *(s16*)(s0+0x2E);
s32 diff = 8 - x;
t = diff << 9;
x = t;            // x reassigned, live if used later
...
```
then use x somewhere that produces no extra insns? If x is used in a place where t is used, e.g., the final stores use x instead of t:
```
((Unk*)s2)->unk1A = x;
((Unk*)s2)->unk18 = x;
```
with x = t (a move t→x, extra insn). Unless the assignment `x = t` is coalesced away! If x and t are coalesced (same register), then `x = t` is a no-op and removed — but then the invalidation? cse would see the SET of x (same pseudo? no, x and t are different pseudos; coalescing happens later in global_alloc, after cse). So at cse time, `x = t` is a real set of x, invalidating x's load entry. Then the second load is not forwarded. Later, global_alloc may coalesce x and t if their live ranges don't conflict — but they DO conflict? x's first value (the load) and t... Let's think:

```
x = load;         // x = l1
diff = 8 - x;
t = diff << 9;
x = t;            // x = t (x's l1 dead)
...
x2 = load;        // second load into a new pseudo (or same x?)
```
Wait, if we then reuse x again for the second load, cse... Let's design:

```
s32 x = *(s16 *)((s32)s0 + 0x2E);   // pseudo x = load1
s32 diff = 8 - x;
t = diff << 9;
x = t;                              // x = t
{
    s32 x2 = *(s16 *)((s32)s0 + 0x2E);  // second load
    *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
}
```
At cse: load1 recorded MEM→x. Then `x = t`: cse invalidates the MEM→x entry (because x is set to a non-equivalent value). Then the second load is a fresh load. 

Then `x = t` remains as an instruction unless coalesced/eliminated. But x is never used after `x = t` → dead code elimination (flow) removes it! Then the invalidation never happened (the insn is removed before cse? order: jump, cse1, then flow? The pass order in toplev: ... jump, cse (cse1), then loop, cse2, ... and dead code elimination in flow is run twice: once after jump/cse1? Let me check toplev.c pass order: flow analysis (flow.c) runs `life_analysis` + `delete_dead_code` maybe. Actually dead code elimination happens in `flow_analysis` which is called in rest_of_compilation. Order roughly: jump_optimize, cse, ... Let me check toplev.c.

Alternatively, make x live after: use x in the final store instead of t (x == t at that point). Then `x = t` is a copy; global_alloc may coalesce them, and the copy disappears. But if x is used at the final stores, its live range extends; the copy x=t is a register-to-register move that may be coalesced. Hmm, but cse also does copy propagation: it might replace uses of x with t, eliminating the copy (and then the invalidation is moot? but cse processes in order: the load2 lookup happens after x=t was processed and x invalidated; if cse later replaces x with t in uses, that's fine).

But wait: if cse replaces `x = t` with `x = t` copy, then at the second load, x is set (invalidated). Good. Then later `x` used → replaced by t. The `x = t` insn might be deleted by cse as a redundant copy? cse doesn't delete copies; jump.c's `delete_noop_moves` maybe.

This is getting speculative. Let me just test a few concrete variants:

c5:
```
    s32 x;
    s32 diff = 8;
    x = *(s16 *)((s32)s0 + 0x2E);
    diff -= x;
    t = diff << 9;
    x = t;
    {
        s32 x2 = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
    }
    ((Unkstruct_800B5CB8 *)s2)->unk1A = x;
    ((Unkstruct_800B5CB8 *)s2)->unk18 = x;
```
Here x is live (used at the end), so `x = t` won't be DCE'd. If global_alloc coalesces x with t, the copy disappears and x is just t. This is a real "reuse the temp" move.

Risk: the final stores use x instead of t; if coalesced, identical. Let's test.

c6: same but `x = t;` and second load into x again:
```
    x = *(s16*)(...); diff -= x; t = diff<<9; x = t; x = *(s16*)(...); += (x<<6); ... store x
```
Second load into x again.

Let me try c5 and c6.

Actually, there's a simpler variant: instead of `x = t`, use a different live reassignment that cse sees. Let me test c5 first.
