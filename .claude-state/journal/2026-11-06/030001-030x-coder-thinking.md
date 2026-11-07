---
ts: 2026-11-06T10:00:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Pj1M4hHeX8noH1ubrGEc
---
Item 4 lever-free b1: score 22, mine 108 ins vs target 119. The second branch's dead computation (11 ins) was deleted by flow (insert mine[100:101] target[100:112] = 12 target ins not in mine). Also registers: a1 vs v0/v1 in first branch, and a delay-slot branch target difference.

So target keeps the second branch's t/v0/v1 computation, and mine deleted it. That's the flow-unused-result wall for the second branch. But if we can make it live with zero cost... The target computes it and discards. Hmm. In the target, the second branch's v1 is computed but a1=0 in the call. So the value is dead but gcc kept it. Why? Because in the target source, maybe the second branch actually calls with a value but the call's second arg... no, target delay slot is `move a1,zero`.

Wait, the target's second branch (19f0-1a3c):
```
lui v1,0x1948; ori v1,v1,0xb0fd   (magic for /81)
addiu v0,a0,-369
sll v0,v0,0xc
mult v0,v1
sra v0,v0,0x1f
mfhi a2
sra v1,a2,0x3
subu v1,v1,v0
sll v0,v1,0x1
addu v0,v0,v1
sll v0,v0,0x5
sra v0,v0,0xc
li v1,127
subu v1,v1,v0
slti v0,v1,31
li v1,31
li a0,1031
jal func_8002D4C8
move a1,zero
```
So it computes v1 = 0x7F - ((t*96)>>12), then `slti v0,v1,31; li v1,31` (i.e., v1 = 31 unconditionally? The slti result in v0 is dead). This looks like `if (v1 < 0x1F) v1 = 0x1F;` where the branch was optimized away because... Actually gcc's jump opt can transform `if (a < b) a = b;` (a store to a dead var) into just the comparison? Hmm.

Wait, maybe the target source's second branch is:
```
v1 = 0x7F - v0;
if (v1 < 0x1F) v1 = 0x1F;
```
and then `func_8002D4C8(0x407, 0);`
Since v1 is dead after, gcc's flow deletes the store `v1 = 0x1F` and the branch, but leaves the `slti` and `li`? That doesn't make sense.

Unless the `slti v0,v1,31; li v1,31` are not from an if but from `v1 = (v1 < 0x1F) ? 0x1F : v1;` compiled as `slti v0,v1,31; li v1,31` — no, that's a conditional move, and the else value is v1 itself, so the compiler would emit `slti v0,v1,31; beqz v0,skip; li v1,31; skip:`.

Hmm, but the target has `slti v0,v1,31; li v1,31` unconditionally, then calls with a1=0. So v1=31 unconditionally and v0 = (old v1 < 31) dead. This is weird — unless the target has a *conditional call* structure where v1 is used as an argument on one path. Let me reconsider: maybe the target's second block is not the `rem == D_80185D04` branch but something else.

Let me look at the target's control flow: at 19ec `bne v1,v0,1a40` (if rem != D_80185D04 goto epilogue). Then compute. At 1a2c `slti v0,v1,31`, 1a30 `li v1,31`, 1a34 `li a0,1031`, 1a38 `jal func_8002D4C8`, 1a3c `move a1,zero`. So yes: computes v1 then sets v1=31 unconditionally.

Maybe the source is:
```
t = ((a0 - 0x171) << 12) / 81;
v0 = (t * 96) >> 12;
v1 = 0x7F - v0;
v1 = (v1 < 0x1F) ? 0x1F : v1;   // no
```
No.

Alternatively the source's second branch is a *copy of the first branch minus the second clamp*, i.e.:
```
v1 = 0x7F - v0;
if (v1 < 0x1F) v1 = 0x1F;
if (v1 >= 0x80) v1 = 0x7F;
func_8002D4C8(0x407, 0);
```
and gcc kept `slti v0,v1,31; li v1,31` for the first if (dead store) but removed the second if entirely. That still seems like dead code not removed.

Hmm, wait: maybe gcc's flow does NOT delete stores to pseudos that were *used* in a comparison? No.

Actually! Maybe the `slti v0,v1,31; li v1,31` are the remains of `if (v1 < 0x1F) v1 = 0x1F;` after *jump optimization converted the branch to a conditional move and then flow deleted the branch*, leaving the set. In gcc 2.7.2, `if (cond) x = c;` where x is dead could be converted by `jump` to... Hmm.

Regardless of mechanism, the target has 12 instructions in the second branch that our lever-free body loses. The orig body kept them via the `cmp` keepalive and `tmp3` pin/keepalive. Those were levers. To keep them lever-free, we need a real use of v1 that gcc keeps, costing zero extra instructions.

Idea: the target's call is `func_8002D4C8(0x407, 0)`. What if the real source passes something computed from v1 that evaluates to 0 at compile time? Like `func_8002D4C8(0x407, v1 & 0)`. gcc folds `v1 & 0` to 0 and drops v1. No.

What if `func_8002D4C8(0x407, (u16)(v1 | 0x1000) & 0)`? Folds to 0, drops.

Hmm. The dead computation is kept in the target; how? Maybe via a *store to a global*? No store in target.

Wait, maybe the second branch's v1 computation is not dead in the target because v1 is *returned* or used later? After 1a3c, 1a40 is the epilogue (jr ra). So v1 dead.

Let me reconsider: maybe the second branch is:
```
if (rem == D_80185D04) {
    t = ...;
    v0 = ...;
    v1 = 0x7F - v0;
    v1 = 0x1F;         // unconditional store! 
    func_8002D4C8(0x407, 0);
}
```
Then the `slti v0,v1,31` before `li v1,31` is... a dead computation? No.

Hold on, maybe I mis-attributed. Let's look at target 1a2c-1a34:
```
1a2c: 2862001f  slti v0,v1,31
1a30: 2403001f  li v1,31
1a34: 24040407  li a0,1031
1a38: jal
1a3c: move a1,zero
```
`slti v0,v1,31` then `li v1,31`. If this were `if (v1 < 31) v1 = 31;` with the branch removed because the store is dead... but then why keep slti and li at all? Maybe because the store to v1 is NOT dead: v1 might be the *call-clobbered* return? no.

Alternatively, the source is `v1 = v1 < 0x1F ? 0x1F : v1;` and gcc's `if_then_else` optimization in `combine`/`jump` decided that since the result is only used... ugh.

Let me test: write the second branch with `if (v1 < 0x1F) v1 = 0x1F;` only (no second clamp) and see what gcc produces. In b1 I did exactly that and flow deleted the whole thing (12 ins missing). So gcc 2.7.2 with the current flags deletes it. The target kept it, so the target's source must have something keeping it alive that compiles to zero extra instructions.

What compiles to zero extra instructions but keeps a value live? Nothing in real C... except maybe a `return` (the value in v0)! If the function returned v1, then v1 would be live. But the target doesn't return v1 (it calls then epilogue). Unless the call is a tail... no.

Wait — maybe the target's second branch ends with `return;`? void.

Hmm, what about the function being `void` and the second branch's v1 used as the return value: `return v1;` in a void function → expand_null_return drops it. Unless the target function's actual return type is s32, and the second branch does `return func_8002D4C8(...)`? No, there's a jal then epilogue, not tail.

Hmm, wait: maybe the target source's second branch has an assignment to a *global* that got optimized? No.

Let me reconsider: maybe the target's `slti v0,v1,31; li v1,31` comes from `if (v1 < 0x1F) { v1 = 0x1F; }` and the target was compiled WITHOUT dead-store elimination because v1 is *volatile*? If v1 were volatile, the store would stay and the load... but then there'd be a memory store. No.

Alternatively, the target's original C might be:
```
v1 = 0x7F - v0;
if (v1 < 0x1F) v1 = 0x1F;
...
func_8002D4C8(0x407, v1 & 0x1000 ? 0 : 0);  // no
```

OK, this is a rabbit hole. Let me instead check: maybe the *orig* body's lever-free residue for item 4 is exactly this (the second branch dead computation) and the wall tag is `flow-unused-result`. The orig used keepalive+pin to keep it. Lever-free loses 12 ins. So item 4 is likely WALL flow-unused-result. But the first branch also has register diffs (a1 vs v0/v1). Hmm, the first branch's v1 variable: in b1, gcc allocated v1 to a1. The target has v1. Why? Because the keepalive/pin influenced allocation. Let me see: in b1 mine, `sra a1,v0,0xc; li v0,127; subu a1,v0,a1` — so v1→a1. Target v1. The orig with the pin matched. The pin $2 on v0 forced v0 to be the hard reg, which freed v1? Hmm.

Let me try b2: keep the `$2` pin (PARTIAL:pin) but remove the other levers (cmp keepalive, tmp3 pin/keepalive). Since the second branch's dead computation is the issue, keeping only the $2 pin won't keep it. Actually wait, the `$2` pin is on v0 (the scratch var). The keepalives were on cmp and tmp3 in the second branch. If we keep the $2 pin only, the second branch's dead computation is still deleted. So score would be ~? Let me test: remove keepalives, keep v0 pin. Also keep tmp3 pin? PARTIAL could keep "pin" kind (both pins are pin kind). The kinds are keepalive,pin. PARTIAL:pin means keep only pins (v0 $2 and tmp3 $3), drop keepalives. But the tmp3 pin without keepalive is dead (store to hard reg $3, dead → deleted?). Let's test.

Actually, let me be systematic and time-efficient. For item 4, the orig has:
- pin v0 $2 (used throughout, needed for target's v0 allocation)
- keepalive on cmp in branch 2 (keeps the slti)
- pin tmp3 $3 + keepalive tmp3 (keeps the li v1,31? and forces $3?)

Wait, the second branch target has `li v1,31` — v1, not v0/v3. The tmp3 pin is $3, but the target uses v1 for the 31. Hmm, the orig's `register s32 tmp3 __asm__("$3") = 0x1F;` with keepalive — that forces a `li v1?` no, $3. Hmm, but target has `li v1,31`. Let me re-examine: the orig second branch:
```c
v1 = 0x7F - v0;
{ s32 cmp = (v1 < 0x1F); asm("" :: "r"(cmp)); }   // keepalive
{ register s32 tmp3 __asm__("$3") = 0x1F; asm("" :: "r"(tmp3)); }  // pin $3 + keepalive
func_8002D4C8(0x407, 0);
```
The target has `slti v0,v1,31; li v1,31`. So the `cmp` keepalive keeps the `slti v0,v1,31` (cmp in some reg, target v0). The `tmp3` pin $3 with 0x1F — target shows `li v1,31`?? That doesn't match $3. Unless gcc rematerialized/allocated differently. Hmm, but orig scores 0! So orig produces exactly the target including `li v1,31`. So the tmp3 pin $3 must not appear as `li v1`; maybe the `li v1,31` is from... wait. Let me re-dump the orig candidate's asm? Orig scores 0, so its asm = target. The target second branch: `slti v0,v1,31; li v1,31; li a0,1031; jal; move a1,zero`. So where's $3? Maybe the tmp3 pin is dead and removed (hard-reg store dead), and `li v1,31` comes from... the `if (v1 < 0x1F) v1 = 0x1F;`? But there's no such statement in orig's second branch! Let me re-read orig lines 3182-3189:

```c
{
    s32 cmp = (v1 < 0x1F);
    __asm__ __volatile__("" :: "r"(cmp));  // keepalive
}
{
    register s32 tmp3 __asm__("$3") = 0x1F;  // pin $3
    __asm__ __volatile__("" :: "r"(tmp3));  // keepalive
}
func_8002D4C8(0x407, 0);
```

Target: slti v0,v1,31 (cmp → v0), li v1,31 (tmp3 → ??? should be $3). Wait, maybe the target's `li v1,31` is actually `li $3,31`? The objdump shows `li v1,31` = `2403001f`. $3 is v1! In MIPS register naming: $0=zero, $1=at, $2=v0, $3=v1, $4=a0... Yes! $3 = v1. So the tmp3 pin $3 IS v1. Great. So the orig's levers produce exactly `slti v0,v1,31` (cmp in v0) and `li v1,31` (tmp3=$3=v1).

So the target's second branch keeps:
- the slti from the `cmp` keepalive
- the li v1,31 from the tmp3 pin/keepalive

Lever-free, both disappear → 12 ins missing. To keep them lever-free, we'd need real C that produces a dead `slti v0,v1,31` and `li v1,31` — i.e., a dead comparison and a dead constant load. Not possible without a use.

Therefore item 4 is WALL flow-unused-result (or expand-void-return). Hmm.

But wait — the first branch's register allocation (v1 vs a1) also depends on the $2 pin. Let me test variants to find the best lever-free score and the residual. But the wall is clear: dead computation.

Hold on. Let me reconsider the task's premise. The brief says "write a lever-free body of func ... that scores 0". It expects that for some items it's possible. The prior moves show many walls for keepalive,pin. Maybe the intended outcome for all 4 is WALL, and the task is to prove it with ≥30 tries. That's a lot of work but let's be efficient: generate variations programmatically and score them in batch via sc.sh.

But maybe there's a clever real-C crack. Let me think about the clones again. The target keeps rv in v0. The keepalive forces rv live. The allocation picked v1. Can real-C moves make it v0?

What if we make the function's last statement use rv in a way that gcc must keep but costs no instruction because it's a *dead branch that gcc removes after allocation*? The C0414 "dead-reset cse-breaker" technique: a dead reset that survives to affect allocation but is deleted. Hmm, but "no new lever of any kind" — a dead-reset cse-breaker might count as a lever (launder). The brief's lever-free = none of the row kinds remain: pin, launder, barrier, keepalive. A dead-reset is arguably a launder.

Actually, wait. Let's revisit: the goal for the clones might be achievable by keeping the keepalive (PARTIAL:keepalive) and getting rv into v0 via allocation nudges. Let's investigate why v1.

Let me get a full dump for b3. I'll create the spliced TU under my shard. Steps:
1. Python script: read src TU, find the function definition span, replace with b3 text, write to .run/P40/T11/G27/<item>/tu_b3.c.
2. Run tools/cc1_dumps_tu.sh <that .c> tag with DUMP_ROOT set to my shard.
3. Read the .lreg/.greg dumps for func_80182420.

But the TU has `#include` etc. The tool copies? It takes a .c file directly. The include path uses -I"$(dirname $tc)" and -Isrc/shared -Isrc. Our spliced file in .run/... includes "../shared/..."? Let me check the TU's includes. Let me grep the top of the SC03 TU.

Actually, simpler: the scorer itself creates a spliced scratch copy under .run/P36/engine/score/... and deletes it. I could set an env to keep... no, --keep writes there.

Hmm, is writing to .run/P36/engine/score acceptable? The constraint says write only under .run/P40/T11/G27/. Using --keep leaves tool scratch elsewhere. I'd rather not.

Let me use cc1_dumps_tu.sh with my own spliced TU. Let me check the TU header.
