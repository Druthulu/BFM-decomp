---
ts: 2026-11-06T07:29:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pyRxXJLTR8AzAvnWOVnw
---
"A=DIFFERS B: removed 0 needed 2" means the lever-free removal attempt failed to compile/match? Actually "removed 0 needed 2" = after removing levers, score didn't reach 0; needed 2 more? Not helpful.

Let me look at the trace jsonl entries' text to see the closest candidate source (the "R16 const-holder id=0x4B x1" at score 14 etc.). Maybe one candidate changed something relevant. But all 14.

Let me consider that this item is a WALL. But we should try ≥30 scored tries before WALL, and ≥20 min. We have 4 items and 30 min budget each. Let me be efficient.

But first, maybe there's a known natural-C resolution. The pattern: a0 reserved during a block. What natural C reserves a0? The function's incoming argument, if the function does something with arg0 AFTER the struct copies but BEFORE the call. Nothing.

Hmm, wait! Maybe the source is not `s0 = arg0` but rather the original signature is `void func_800CB458(void *arg0)` or the body accesses `arg0` directly. Let's test variants systematically. I'll write a generator that produces variants and scores them.

Variants to try:
A. Use arg0 directly everywhere (no s0).
B. Declare `s32 s0;` and assign `s0 = arg0;` as separate statement.
C. Two 16-byte copies via a local `Struct16 t;` variable.
D. Split the copies into s32 fields with named temps.
E. Reorder the two copies.
F. Put the two copies in a `do { } while(0)`.
G. Declare `id` at top with `s32 id;` vs `s32 id = 0x4B;` in the if.
H. Use `u32` for loads.
I. Compute v0 = *(s32*)(s1+0x20) inline in the copies.
J. Different decl order (v0, s1, id).

Actually, think about what could reserve a0: a value that is live only in the first block and allocated a0. What value in the target's first block? The four copy temps + v0 pointer + s1 + s0. s0/s1 callee. v0 in $2. The 4 temps take v1,a1,a2,a3. That's 4. Where's a0? Used by... maybe a 5th temp from the SECOND copy group that spans? No, the two groups are sequential; each has 4 temps.

Wait — maybe the 4 temps are shared between the two groups? In target group1 loads v1,a1,a2,a3; stores them; group2 loads v1,a1,a2,a3 again. Same regs reused. So 4 quantities each group. 

Could a0 be reserved by the `func_800CAF84` call's return/arg? No.

Let me look at `regs_live_at`: local-alloc marks liveness of pseudos in the block including those live across. Which pseudo could be live across the whole first block and in a0? The `id`? If id's def were hoisted above the copies (e.g. source `id = 0x4B;` before the copies), then id would be live from there to the if-block, crossing the func_800CAF84 call → callee-saved, not a0.

What about a pseudo that is live from entry to the copy block and dies at the copies? arg0! If arg0's last use is inside the copy block (e.g., `s0 = arg0` is at the END of the block, after the copies?), then arg0 (a0) would be live through the copies and allocated... but a0 is caller-saved and arg0 doesn't cross a call before the copies (no call before), so global-alloc could assign arg0 to a0 and it's live in the block, reserving a0! And then `move s0,a0` at the end? But target's move s0,a0 is at insn 2, at the top.

Unless... the target's move s0,a0 at insn 2 is a coalesced copy and arg0 is a *different* pseudo still live? No.

Hmm, actually wait: could a0 be reserved by the value `id` because the compiler allocated `id` to a0 in the if-block, and local-alloc's block for the copies actually INCLUDES the if-block? No, the `bne` ends the block.

Let me check the basic block structure: entry block = insns 0..28 (through the copies and jal? no, jal doesn't end a block in GCC's CFG? Calls don't split basic blocks). Actually calls don't split basic blocks in GCC. So the first basic block runs from entry through the `jal func_800CAF84` (the call), the `lw v0,28(s0)`, `li v1,-1`, `addiu`, `bne` — the branch ends the block. So the copies and the call are in ONE basic block! Then local-alloc allocates regs for the whole block including across the call. And `id`? The `li a0,75` is in the next block (target of the bne), so id is local to the if-block.

But the call is in the first block. local-alloc assigns caller-saved regs; quantities crossing the call must be in callee-saved (reg_n_calls_crossed>0 → used=call_used_reg_set excludes caller-saved). Fine.

Still, where does a0 get reserved in the first block? `regs_live_at` includes pseudos live at each insn. Within the first block, a pseudo live at the copies but not used... 

AH WAIT. I bet it's the `v0` pointer! No.

Let me just try the empirical variants; much faster than theorizing. Let me write a script to generate variant bodies from a template and score with sc.sh.

Actually, let me first try one high-probability idea: `s32 s0 = arg0;` where the parameter is used as the struct pointer directly in the two copies, i.e.:

```
*(Struct16 *)(arg0 + 0x38) = ...
```
but arg0 is s32. Hmm, `s0` IS arg0. Same value.

Another idea: the compiler's copy `s0 = arg0` happens because arg0 crosses the call. What if the original C had NO s0 and used arg0, and the compiler generated the copy. Then a0 is dead after the copy. Same.

OK let me look at it from the "id" angle more carefully. In the target, `li a0,75` is the first insn of the if-block. In mine, `li v0,0x8000` then `li a0,75`. The 0x8000 is the 6th argument (stack). Both are constants materialized in the if-block. Why order differs? sched1 orders by birth priority; the li for id has birth at the id assignment (earlier source line) vs the 0x8000 constant. In mine, sched1 put li v0,0x8000 first; in target li a0,75 first. If a0 were live in the first block (target), then... hmm, sched1 wouldn't care.

Maybe in target, the `id` pseudo is live in the first block because of an early def, which would also explain BOTH: a0 reserved in the copy block AND li a0,75 hoisted to the top of the if-block? If id were assigned `id = 0x4B;` at the top of the function (before the copies), then:
- id live from top, crosses the func_800CAF84 call → must be callee-saved, so it'd be in s2/s3, not a0. Unless there's no crossing? The call is after the copies. id would be live across the call → callee-saved. So no.

Unless the if-block's `id` assignment is after the call; fine.

Hmm, what if `id` is not a variable but the literal 0x4B passed directly: `func_80146A6C(0x4B, s1, 0,0,0,0x8000,0);`? Then the compiler materializes li a0,75 at the call setup, after li v0,0x8000? Mine does that order too? Mine has li v0,0x8000 then li a0,75. Target has li a0,75 then li v0,0x8000. Hmm.

Let me try variants and see. Time to script it. I'll create a template file and use sed/python to generate.

Actually, let me reconsider the whole approach: maybe the crack is not about a0 but about making the copy temps use a1-a3 through a "5th quantity" that takes a0. What if we introduce a real temp that holds something live across the copies, e.g.:

```
s32 s0 = arg0;
s32 s1 = ((Unkstruct*)s0)->unk34;
s32 v0 = *(s32*)(s1+0x20);
s32 t = *(s32*)(v0+0x34);   // first load hoisted into a named temp
...
```
Hmm, that's exactly one of the copy temps but named, making it live longer, possibly allocated to a0 by global-alloc? Named temp `t` used once in the store. Same.

What if we name the SOURCE base pointer as `u8 *src = (u8*)(v0+0x34);` then copies. Adds a quantity.

Honestly, the a0 reservation pattern appears in other functions: "global-hardreg-reserve — the pin's hard-reg pseudo reserves a reg for the whole fn; lever-free the temps take it (T11 G08b func_801536DC)". That wall tag says exactly: a pin reserves a hard reg; lever-free the temps take it. So this is a known WALL class: global-hardreg-reserve. The natural C cannot reproduce it. For item1, the pin is $4 (caller-saved). The keepalive was the lever making it effective. If the pin can stay (other kind), maybe we keep the pin but it needs a use. Hmm.

But wait: the pin is listed in the row as part of "kinds"? The row kinds = keepalive only. So the pin is a different cause. "levers of other kinds the def already had (pins under other causes) may stay". So we may keep the pin and its assignment. But the keepalive must go. If the keepalive goes, the pin assignment is dead and removed. Unless the pin assignment itself is enough to reserve a0? Let's test: keep the pin and `keep_a0 = arg0;` but remove the asm. We did w1: score 14. So no.

What if we keep the pin and use `keep_a0` in a REAL expression whose result matters but doesn't change the bytes? For example, `s1 = ((Unkstruct*)s0)->unk34;` becomes... no.

Hmm. But the brief's constraint: "identity-statement launders ... do NOT count as a crack". And "no new lever of any kind". So we can't fake it.

Thus item1 likely WALL: global-hardreg-reserve or similar. But wait, the wall tag "global-hardreg-reserve" says lever-free the temps take the reg — exactly our case. Let me confirm by checking if the pin's hard-reg pseudo reserves a0 "for the whole fn" — in our case $4 is caller-saved, not reserved whole fn. Hmm.

Let me test whether a *different* real-C spelling makes a0 live. Try: use arg0 as the pointer in the if-block decrement (`arg0` instead of `s0`). Then arg0 crosses the call → callee-saved copy; but maybe the copy is deferred: the compiler may use a0 for arg0 up to the call and copy to s0 just before? GCC 2.7 doesn't split live ranges... Actually it does via global-alloc's allocation; the value lives across the call so it gets a callee-saved reg and a move at entry.

Let me just test a batch of variants. I'll write them as separate files and run sc.sh.

Template variants:
1. v_arga: use arg0 directly, no s0 var.
2. v_decl: `s32 s0;` then `s0 = arg0;`.
3. v_tmp: name the 4 loads explicitly with temps.
4. v_struct: local Struct16 temp.
5. v_dowhile: wrap copies in do-while.
6. v_swap: swap the two copy statements.
7. v_idtop: `id = 0x4B;` before copies? (changes semantics? no, but it's a real move; would keep id live across call → callee-saved, wrong).
8. v_u32: cast loads to u32.

Let me generate them with python from orig minus levers, then score. Since scoring is ~1-2s each, fine.

Let me write a quick generator. Actually simpler: write each file with Write or sed. Let me do it with a python script that reads a base body and applies textual edits.

Base body (no levers):
```
void func_800CB458(s32 arg0) {
    extern void func_800CAF84(void);
    extern s32 func_80146A6C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    s32 s0 = arg0;
    s32 s1;
    s32 v0;
    s32 id;

    s1 = ((Unkstruct_800CB458 *)s0)->unk34;
    v0 = *(s32 *)(s1 + 0x20);

    *(Struct16 *)(s0 + 0x38) = *(Struct16 *)(v0 + 0x34);
    *(Struct16 *)(s0 + 0x48) = *(Struct16 *)(v0 + 0x44);

    func_800CAF84();

    if ((((Unkstruct_800CB458 *)s0)->unk1C -= 1) == -1) {
        id = 0x4B;
        func_80146A6C(id, s1, 0, 0, 0, 0x8000, 0);
        ((Unkstruct_800CB458 *)s0)->unk1C = 0x18;
    }
}
```

Let me write the variants manually into files. Start with a few.

Variant "inline v0": replace `v0 = *(s32 *)(s1 + 0x20);` and use `(*(s32*)(s1+0x20))` inline? That would re-load. No.

Variant "split each struct copy into 4 scalar assignments with explicit temps": the struct copy already does that in RTL. Writing it out as scalars might change the temp liveness (each temp dies at its store). Actually the struct copy generates exactly that. But writing scalars could change the order of loads/stores: currently target does 4 loads then 4 stores (block move). If written as 4 separate `*(s32*)(s0+0x38) = *(s32*)(v0+0x34);` statements, each is load-then-store, and sched1 might interleave; target has 4 loads then 4 stores, which is what expand_block_move does. So keeping Struct16 is right.

Hmm, what about the `Struct16` type? Let me check its definition and whether the target's 4+4 could come from two Struct16 copies. Yes.

Let me look at what `s0 + 0x38` vs `v0 + 0x34` means: both 16-byte structs, so 4 words each. Fine.

Let me just run a batch.
