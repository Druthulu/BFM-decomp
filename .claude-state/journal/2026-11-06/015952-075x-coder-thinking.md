---
ts: 2026-11-06T08:59:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dypZjDyXJJTQN8sWatfp
---
Confirmed the structure. Note `lhu v0,8(s2)` is loaded at insn ~82 (before the call) for `v[2].vy = v[3].vy = *(u16*)((s32)a+0x8)`, and again at 84 (`lw v0,8(s2)`) for the product. The product reloads a[2] as a word.

So the original C had `(a[2]-z)*buf[5]` after the call. What if the original was:

```c
func_8017E410(mode1, buf);
v[0].vy = v[1].vy = z;  // moved after the call?
```
No, the target's v stores are before the call.

Hmm, what if the original C was:
```c
v[0].vy = v[1].vy = z;
v[2].vy = v[3].vy = (a[2] - z) * buf[5];   // ??? 
```
No, the store is `lhu 8(s2)` (a halfword from a+8), and the product is a separate word load.

OK. Let me consider that this is a genuine wall. But the brief wants 30 tries for a WALL. Let me at least try a set of plausible real-C uses that could keep the product with zero extra insns:

1. Use the product in a *dead branch* that gcc keeps as a branch but the target doesn't have → no.
2. Use the product as an argument to a *macro* that discards it: e.g. `gte_stszotz((s32*)((a[2]-z)*buf[5]))`? That changes the store address → wrong.
3. Use the product in the `p->tag` computation as a no-op term? changes bytes.
4. Use it as a *return value*: `return (a[2]-z)*buf[5];` — changes the return (target returns 0).
5. `if (otz > 0 && cull == 0)` — replace `otz > 0` with `(a[2]-z)*buf[5] > 0`? changes bytes.

Hmm.

What about the possibility that the original C computed the product and *stored it into `v[]`* but the store was to a slot that the target writes earlier... e.g.:

```c
v[0].vy = v[1].vy = z;
```
What if the original was:
```c
v[0].vy = v[1].vy = z;
v[2].vy = v[3].vy = *(u16 *)((s32)a + 0x8);
```
and then:
```c
func_8017E410(mode1, buf);
p->x0 = ...; 
```
No.

Let me look at the *second* block: it has the same v[] setup but no product and no `if (a[7]...)` handling. The first block's product could be part of the "mode1" computation? No, mode1 is computed before.

Maybe the original source had:
```c
z2 = (a[2] - z) * buf[5];
```
and `z2` was used in a `gte_stszotz`-like macro? Hmm.

Actually — wait. What if the product feeds the **GTE `gte_ldv0(&v[3])`**? No.

What if the product is used as the *pointer* for gte_stsxy3? No.

Let me try a different tack: maybe the product can be kept by making it feed a **memory store that flow keeps because the destination is a global** — but the target has no store, so no.

Alternatively, maybe the *product* itself isn't the issue: maybe the target's `mflo t1` is used as a **delay-slot filler**? No, it's not in a delay slot.

Let me look at what comes right before: `jal func_8017C294` (the call to func_8017E410, aliased) with `sh v0,34(sp)` in the delay slot. Then the 5 insns. In the *asm* version, the asm is a use, so the 5 insns are emitted and flow keeps them.

Since GCC's flow deletes dead sets, the only way is a use. So the original source had a use. What use? It must be something that doesn't generate additional instructions in the final code. The only such use is an asm — which the original programmer couldn't have written (it's a decomp).

UNLESS: the original use was in an expression that was *itself* optimized away but whose RTL use survived — e.g., a `(use)` insn from combine's REG_DEAD handling! Remember in item 2, combine created a `(use reg)` insn. If a real C use of the product exists in a way that combine turns into a USE insn... hmm.

Actually, here's a thought: what if the product is used in a *conditional expression that becomes a no-op after folding*, e.g.:

```c
if ((a[2]-z)*buf[5] == (a[2]-z)*buf[5]) { }
```
No, CSE.

What if the product is used in a **variable-length array / alloca**? no.

What if the product is used in a **goto target computation**? no.

What if the product is used as a *loop bound* `for (i = 0; i < (a[2]-z)*buf[5]; i++)`? That would add a loop.

Hmm, what if the original code was:
```c
do {
    ...
} while (0);
```
no.

OK, let me look at this from the "what did the original source look like" angle by examining the *neighbouring* decompiled code style. The function is a sprite-drawing routine. The product `(a[2] - z) * buf[5]` might be a **depth value for the OT** — but the OT insertion uses otz.

Hmm, wait. What if the original source had:
```c
gte_stszotz(&otz);
```
but the *product* is what `buf[5]` was for... 

Let me look at func_8017E410's signature: `func_8017E410(s32 param_1, u32 *param_2)` — fills buf. buf[5] is the 6th word.

What if the original code was:
```c
s32 tmp = (a[2] - z) * buf[5];
...
```
and tmp was used in the *second* loop too? The second loop doesn't have it.

I think this is a wall. But the brief says a WALL needs ≥30 scored tries. Let me be efficient: generate a batch of candidate bodies (say 25) with different real-C uses, score them in one sc.sh call, and record. If none is 0, WALL.

But hold on — before mass-generating, let me reconsider one specific idea: **the multiply result could be used in a `?:` whose other branch is the same expression, folded to one**. No.

Another: the product could be used in a **cast to a pointer and back** (launder — banned as identity).

Another: `if ((a[2]-z)*buf[5]) goto skip;` where skip is the next statement → jump.c removes the branch and label, but the *condition* computation might remain? A conditional branch on a value: if gcc's jump optimizer removes a branch to the immediately following label, it deletes the branch insn but the condition computation (mult) becomes dead and flow removes it. Unless the order of passes: jump1 runs before flow? If the branch is removed after flow... Pass order: jump_optimize runs before cse/flow? Let me check toplev.c order. In 2.7.2: 
rest_of_compilation: ... jump_optimize (1st) ... cse ... loop ... cse ... combine ... jump_optimize (2nd) ... flow ... sched ...

Hmm, if the branch is removed by jump2 (after combine) and flow runs after jump2? Actually flow_analysis runs before jump2? The order in 2.7.2: after combine: `jump_optimize (insns, 0, 1)` then `flow_analysis` then `local_alloc` ... Hmm.

Actually, a conditional branch with a condition that's always true (e.g. comparing a value to itself) would be folded by cse/jump early.

What about `if ((a[2]-z)*buf[5] != 0x12345678) { }` — a branch with an empty then-block: gcc would still emit the branch (or remove the empty if at tree level — an empty then-block is removed at tree level).

`if (cond) { ; } else { ; }` → removed at tree level.

What about `while ((a[2]-z)*buf[5]) { break; }`? That's a loop: computes the condition, branches. Adds a branch. Unless the loop optimizer... no.

What about `switch ((a[2]-z)*buf[5]) { case 0: break; default: break; }`? gcc might emit a compare+branch or a jump table; adds.

Hmm, what about using the product as the **index of a `goto` computed**? no computed goto in C89.

OK, what about this: the product feeds a *conditional move*-like expression that gcc turns into a `slt`+`move`? adds.

Let me also reconsider: maybe the original source had the product **as a function argument to func_8017E410** — e.g. `func_8017E410(mode1, buf)` where the second argument is `buf`, and the product was passed as a *third* argument to a function that ignores it? That would add a call arg (a1/a2 moves) — no.

What if the product was passed as the *first* argument, mode1? No.

Hmm, what if the original code was:
```c
func_8017E410(mode1, buf);
if (buf[5] && (a[2]-z)) { ... }
```
adds branch.

I'm fairly convinced it's a wall. But wait — one more idea: **`z` is used after**. What if the product's result is assigned to `z` in a way that's later overwritten before use? `z = (a[2]-z)*buf[5];` then `z -= 0x80;` uses z... no, z -= 0x80 comes before.

After the if block: `z -= 0x80;` in the loop, and `z = top` in the else. If we set z = product at the end of the if block, the loop's `z -= 0x80` would use it → changes behavior and bytes.

What about assigning to `otz`? otz is set by gte_stszotz later; the assignment before would be a dead store, and since otz's address is taken (gte_stszotz(&otz)), flow might keep the store... but the store isn't in the target.

Wait, actually, hmm: what if the product is assigned to otz and gte_stszotz's `&otz` store is *the only other write*, and the target's mfc2+sw is at sp+72 — if we assign otz before, the target would have an extra sw to sp+72. Not present.

OK. Let me also consider: maybe the target's product is NOT dead in the *original* binary but the decompiler's `t1` is actually used by the GTE command in a way objdump doesn't show (e.g., the GTE instruction takes a GPR operand!). Let me check: `gte_rtpt()` is `cop2 0x0180001` — the `0x0180001` might encode a register field (bits 25-21?). MIPS cop2 commands can take rt/rd fields = GPRs. `gte_rtpt` in PSX is `cop2 0x0180001` (fixed). Some GTE ops (e.g., `gte_stsxy`, `gte_ldv0`) use `swc2/lwc2` with a GPR base. The RTPT command doesn't read a GPR.

But hmm, `mflo t1` — maybe a later `swc2` uses t1 as a source? Let me grep the target listing for "t1" again — only mflo. And "swc2" lines: let me check the region after. If `swc2 $14,0(t1)` existed, t1 would be used. Let me grep the target listing for swc2.

Actually my grep for "t1" over the whole function listing found only line 88. So t1 is dead.

Let me also consider the possibility that the value is used via a **hilo** dependency: `mult` clobbers HI/LO; if a later instruction reads HI/LO (mflo/mfhi), the mult is needed. Does a later `mflo` exist? In the else branch of the outer if (`if (hi != 0)`) there are mults (rand()%3). Those come much later and are separate mults. So no.

OK. Given the wall list has `flow-unused-result` explicitly with "flow deletes results the target computes but never uses", this item is that wall. But the brief wants 30 tries. Hmm, let me re-read the brief: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

I've spent ~10 min on item 3. I need to either crack it or reach 30 scored tries and 20 min.

Actually, wait. Let me reconsider the problem once more. The target's 5 insns:
```
lw v0,8(s2)      ; a[2]
lw v1,68(sp)     ; buf[5]
subu v0,v0,s3    ; -z
mult v0,v1
mflo t1
```
Then `addiu v0,sp,16`.

What if the original C was:
```c
s32 *dst = &v[0].vx;  // or similar
```
no.

What if the product's result was used to compute an address for the GTE load: `gte_ldv3c(&v[0])` — if the source passed `&v[(a[2]-z)*buf[5]]`? That would index with the product → the address computation would include a shift and add. Not in target.

What if the source was `gte_ldv3c((SVEC8*)((a[2]-z)*buf[5] + (s32)&v[0]))`? no.

Hmm, what if the product was used in the `gte_stsxy3` destination? no.

OK — but hold on, maybe I should reconsider the *decompiler's* asm: `__asm__ __volatile__ ("" :: "r"((a[2] - z) * buf[5]));`. Maybe the decompiler chose this expression because the original binary has those insns, but the original C might have had a *different* computation that happens to produce the same insns. E.g., the original could have been:

```c
v[2].vy = v[3].vy = (a[2] - z) * buf[5] >> 16;
```
No, the v[2].vy store is `lhu 8(s2)` (the a[2] halfword).

What about `z = z + (a[2]-z)*buf[5];`? Then z would be modified — the target's s3 (z) is used later (z -= 0x80 at the end of the if-block, and v stores). Actually wait: is s3 modified by the product? The product writes t1, not s3. So no.

What if the original computed `(a[2]-z)*buf[5]` into a variable that was then *stored into the stack at an offset that the target writes elsewhere*? The frame slots: v[] at sp+16..sp+44, buf at sp+48..sp+60, otz at sp+72. The target's stores to sp+68? `lw v1,68(sp)` reads sp+68 = buf[5]. Any store to sp+68 in the target? Let me check the target listing for "68(sp)".
