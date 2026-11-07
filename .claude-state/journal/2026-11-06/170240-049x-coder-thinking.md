---
ts: 2026-11-07T00:02:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RaZDbh4dX6yhMgcKOOhO
---
Interesting. The parameter copies differ:
- Target: `sw s2,24(sp); move s2,a0; sw s4,32(sp); move s4,a1; sw s5,36(sp); move s5,a2; move s3,a3`
- Mine: `move s3,a0; sw s5,36(sp); move s5,a1; sw s4,32(sp); move s4,a2; sw s2,24(sp); move s2,a3`

So the parameter-to-register assignment is permuted: mine param_1=s3, param_2=s5, param_3=s4, param_4=s2; target param_1=s2, param_2=s4, param_3=s5, param_4=s3.

Target: param_1→s2, param_2→s4, param_3→s5, param_4→s3.
The pins were: param_3 pinned $21=s5, param_4 pinned $19=s3. So in the target, param_3=s5 and param_4=s3 match the pins. param_1=s2, param_2=s4 naturally.

Mine (lever-free): param_1=s3, param_2=s5, param_3=s4, param_4=s2.

So the natural allocation gives a permutation. We need to find a C structure that naturally gives target's.

Also the `t` pin ($2=v0): target keeps the loaded halfword in v0 then `move s1,v0; negu s1,s1` for abs. Mine has `lh s1,4(a0)` directly into s1. So the target's t (a v0 pseudo) is needed.

And the launder on iVar4: target has `move v1,v0` copies in each of the max comparisons, mine has `slt v0,s1,v1` directly.

Hmm, this is a complex multi-register allocation. Let me think about the natural C.

Target register roles:
- param_1 = s2 (the self pointer, used as `lw v1,88(s2)`, `addiu a0,s2,4`)
- param_2 = s4
- param_3 = s5
- param_4 = s3
- iVar1 = ? (the loop cursor from func_8012DDE2C / func_8012DDA4)
- iVar5 = s1 (running max)
- iVar4 = v1 (the abs temp)
- t = v0

Mine lever-free:
- param_1 = s3, param_2 = s5, param_3 = s4, param_4 = s2
- iVar5 = s1
- iVar4 = v1
- t absent (lh s1 direct)

So the permutation of the 4 param copies is the main residual (plus the t/launder shape).

Let me look at the whole function body again:

```c
s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 param_1;  /* $s2 */
    s32 param_2;  /* $s4 */
    register s32 param_3 __asm__("$21");  /* $s5 */
    register s32 param_4 __asm__("$19");  /* $s3 */
    s32 iVar1;    /* $s0 */
    s32 iVar5;    /* $s1 (running max, then its square) */
    s32 iVar4;
    register s32 t __asm__("$2");          /* $v0: keep the loaded halfword in $v0 so abs copies $v0->$v1 */
    u32 uVar3;
    param_1 = arg0;
    param_2 = arg1;
    param_3 = arg2;
    param_4 = arg3;
    iVar1 = func_8012DDE2C(param_1);
    ...
}
```

Note the comments say param_1=$s2, param_2=$s4, iVar1=$s0, iVar5=$s1.

So the natural allocation needs: param_1→s2, param_2→s4, param_3→s5, param_4→s3, iVar1→s0, iVar5→s1, iVar4→v1, t→v0.

Mine: param_1→s3, param_2→s5, param_3→s4, param_4→s2.

Interesting: mine's assignment is a rotation. The allocnos are sorted by priority; the register assignment order differs.

Idea: the ORDER of the parameter copy statements. In the target, the copies are emitted in order: param_1 (sw s2,24(sp); move s2,a0), param_2 (sw s4,32; move s4,a1), param_3 (sw s5,36; move s5,a2), param_4 (move s3,a3). Hmm, wait: target order is:
```
sw s2,24(sp)
move s2,a0
sw s4,32(sp)
move s4,a1
sw s5,36(sp)
move s5,a2
move s3,a3
```
Mine:
```
move s3,a0
sw s5,36(sp)
move s5,a1
sw s4,32(sp)
move s4,a2
sw s2,24(sp)
move s2,a3
```
So in mine, param_1→s3 (no save needed? s3 is callee-saved, so it should be saved... hmm, `move s3,a0` then where's sw s3? Maybe saved later or the function doesn't save s3? The prologue in mine might save s3 differently.)

Hmm, actually the target saves s2,s4,s5 (24,32,36) and s3 (28?) — let me look at the full target prologue.

Actually the diff shows the insert of target[1:7] = sw s2,24; move s2,a0; sw s4,32; move s4,a1; sw s5,36; move s5,a2. And target[8] = move s3,a3. The prologue saves probably include sw s3,28(sp) and sw s0,s1 too.

Let me get the full target disassembly for this function to understand the register roles. The target object is in build/ for some includer... The header is included in ov_MAIN_012. Let me find the object.

Hmm, this is getting deep. Let me think about the lever-free C structure.

The parameter copies: 4 locals assigned from args. Their allocation: global-alloc assigns based on priority (refs/live). param_1 is used a lot (self pointer). param_2/3/4 used in the loop.

Mine's assignment: param_1→s3, param_2→s5, param_3→s4, param_4→s2.
Target: param_1→s2, param_2→s4, param_3→s5, param_4→s3.

The mapping is a permutation: mine p1=s3,p2=s5,p3=s4,p4=s2 → target p1=s2,p2=s4,p3=s5,p4=s3.

Hmm, it looks like the allocnos got sorted differently. If the allocation order (by priority) is [p1, p2, p3, p4] and the available regs in order are [s2, s3, s4, s5]? Then p1→s2, p2→s3... no, target p2=s4.

Let me figure out the available regs. s0=iVar1, s1=iVar5. So the params can only use s2-s5 (4 regs) if they need callee-saved. Target: s2,s3,s4,s5 used by p1,p4,p2,p3.

Mine: p1=s3, p2=s5, p3=s4, p4=s2.

Hmm. So the reg assignment order in mine: the first allocated gets s2 (p4), then s3 (p1), then s4 (p3), then s5 (p2).
Target: first s2 (p1), then s3 (p4), then s4 (p2), then s5 (p3).

So the priority order in mine is p4 > p1 > p3 > p2. Target's is p1 > p4 > p2 > p3.

Hmm. That's a reordering. Since the pins forced p3→s5, p4→s3, the natural priority order in the target is p1 > p4 > p2 > p3 (p3 and p4 pinned anyway).

Hmm, so the original source's allocno priorities differed. What determines them? refs/live of each param.

param_1: used in func_8012DDE2C(param_1), `*(u32*)(param_1+0x58)`, `func_80013350(param_1+4, iVar1+4)` → refs ~4, live long (whole function).
param_2: used in the loop store `*(u16*)(iVar1+0x60) = param_2` → refs 1-2, live long.
param_3: similar, refs 1-2.
param_4: used in `if (*(u16*)(iVar1+0x5e) != param_4)` and the store → refs 2-3.

Priorities: p4 (refs 3?) > p1 (refs 4, long live) ...

Hmm. The live lengths all span the whole function (they're live from the prologue to the loop). So pri ∝ refs roughly.

Mine: p4 first (s2) → p4 has the highest pri. Then p1 (s3), p3 (s4), p2 (s5).

Hmm, let me get the allocno table for this function. I need the TU. The includer is src/ov_MAIN_012/ov_MAIN_012.c. Let me use tryinc/cc1_dumps on a spliced TU... but the header is instantiated in the includer. Complex.

Alternative: use the existing build object. Let me find the target object for func_8012DBD0 and disassemble it. That gives the target regs. Already have the diff.

Hmm. Let me think about a simpler lever: the ORDER of the parameter-copy statements in C. The allocno priority doesn't depend on statement order, but the *birth order* (allocno number) does. Ties break by allocno number (lower wins). If the priorities are close, reordering the copies could change the assignment.

Actually, the simplest C-level lever: assign the params in a different order, e.g.:
```
param_4 = arg3;
param_1 = arg0;
param_2 = arg1;
param_3 = arg2;
```
This changes the RTL order and thus the allocno numbers and possibly live lengths (all start at their copy).

Hmm, but the *target's* copy order is p1, p2, p3, p4 (s2,s4,s5,s3). So the C order is p1,p2,p3,p4.

The reg assignment in mine follows priority. Let me get the actual priorities via a dump.

How to dump this function? The TU is src/ov_MAIN_012/ov_MAIN_012.c which includes the header. I can splice my win.c into a copy of that TU? No — the header is included at many sites. Hmm, actually the header is included once per includer; for the TU ov_MAIN_012.c, the function appears once.

Simplest: make a copy of the header with my body (that's what --body does), then... cc1_dumps_tu.sh needs a .c file. I can create a .c that `#include`s the header? The header's include machinery might need the includer's context.

Hmm. Alternatively, maybe tryinc's mechanism creates a scratch TU. Let me look at how recs_for works — it probably builds a TU with the includer recipe.

Let me check delever_search's recs_for and whether --keep leaves the .i file.

Actually, simpler: the includer is src/ov_MAIN_012/ov_MAIN_012.c. I can copy it to my item dir and replace the `#include "../shared/ov/func_8012DBD0.h"` with my body. Then run cc1_dumps_tu.sh on the copy. But ov_MAIN_012.c is a big TU with other functions; that's fine, dumps work per function.

Wait, but the header might be included by ov_MAIN_012.c via a path. Let me check.

Let me first check the include line in ov_MAIN_012.c.

Actually, let me first try the cheap thing: reorder the param copies and see if the regs shift. Let me also try different variable orders.

But 39 is a big score. Let me get the priorities first — it'll guide me. Let me look at how recs_for builds the TU.
