---
ts: 2026-11-06T16:32:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tnKdvmBRiYLmPwutN4tM
---
Same — pointer self still equated with a0 in the else. So cse merges Pmode/Simode.

New idea: prevent cse equivalence by making the copy happen in a *conditional* context or with a different value. What about `self = arg0; if (flag == 0) ...` — no.

Alternative approach: accept a0 in the else arm and change the *target match* by... no, target is fixed.

We need a0 to be occupied/clobbered at the else. What if `mask` is computed at the top and used in the then arm; then a0 holds mask, so else's self uses a1. But target has `li a0,-129` after bnez. However! Note the target's then-arm `li a0,-129` at 2c34 — could it be that the original source computed mask before the if, and sched1/reorg moved it into the then block? Sinking a constant into the block where it's used is plausible with sched1? sched1 schedules within a block; it can't move an insn across blocks. But the `mask = ~0x80` before the if would be in the entry block; target has it in the then block. Unless global cse or jump optimization moved it... Actually the then block is reached by fallthrough; moving an insn from the entry block into the then block would be code motion across the bnez — not done by sched1.

Hmm, unless the C is:
```
if (flag == 0) { ... } else { ... }
```
and mask is declared in the then block. Then `li a0` is in the then block. And the else block uses a1 in the target because... self is not equivalent to arg0.

So the crux remains: make self non-equivalent to arg0 in a way that survives cse2 + combine.

What about using a `u8 *` pointer with an offset? e.g. `u8 *self = (u8 *)arg0;` and accesses `*(s16 *)(self + 0xAA)`. Still a copy.

What about making self a *global*? no.

What about `self` being a parameter copy via function call? no.

What about exploiting that cse only equates registers when the copy is unconditional in the same block and the source isn't modified? The copy is in the entry block; the else block is a different basic block. cse1 processes per extended basic block; the entry block and then/else blocks may be in the same EBB (entry → then fallthrough → j end; else is a separate EBB since branch target). In cse1, reg_eqv applies within the EBB. The else block starts a new EBB (it's a branch target), so cse's local equivalence doesn't carry? But cse also does "canonicalization" using reg_qty across blocks within the EBB only. Hmm, but global-alloc/copy-prop?

Actually the a0 use in else might come from *combine* or from *flow*'s register copy propagation? Or from local-alloc: the self pseudo is live only in the then arm (if the else uses a separate use of arg0)... no, both arms use self.

Wait — maybe the a0 in the else arm is because local-alloc/global-alloc coalesced self with arg0 for the else block's live range. Since self = arg0 is a copy, the *copy propagation* pass (regmove? or local-alloc's copy coalescing) can replace uses with the source when the source is unchanged. Local-alloc coalesces copy pairs when possible. In the then arm it couldn't because a0 was clobbered by mask. In the else arm, a0 was free, so it coalesced self→a0 (eliminating a1 use).

So the question is what prevents this coalescing: with the zr pin, self wasn't a copy of arg0.

Can we make self a genuine non-copy without extra instructions? `self = arg0 + 0;` → folded to copy at RTL by combine (combine runs before local-alloc: yes, combine is before local-alloc). `self = arg0 ^ 0;` same. `self = arg0 | 0;` same. `self = arg0 * 1;` → mult? combine folds.

What about `self = arg0 + flag - flag`? That's not foldable and emits instructions. Hmm.

`self = (s32)((u32)arg0 & 0xFFFFFFFF);` folds.

What about a value known equal but not syntactically foldable: `self = flag, arg0;`? comma folds.

Hmm. What if we don't create a copy at all, but instead make the *parameter* be used through a form that requires its own register: e.g., `arg0 += 0;`? Same copy.

OK, different tack: maybe we can make the else arm's base a1 not by keeping self separate, but by forcing a0 to be occupied in the else arm with the mask value through a *live* use. For instance, compute `mask` unconditionally before the if, and use mask in the else arm in a way that emits the same instructions as target. Target else arm:
```
lw v0,32(a1)
lw v1,220(a1)
lhu v0,24(v0)
ori v1,v1,0x80
sw v1,220(a1)
sh v0,260(a1)
```
There's no a0 use. If mask is live in a0 across the else, that's fine — a0 keeps -129, unused. But then the `li a0,-129` is in the entry block before bnez, which differs from target. Unless... we put the mask computation in the then block but ALSO force a0 to be clobbered before the branch on the else path? Contradiction: target's else path has no clobber.

Wait, actually, does it matter that a0 is "clobbered"? cse/local-alloc consider liveness. If mask is computed before the if, a0's value is live across both arms (mask used only in then). At the else, a0 holds mask, which is live (needed at the join? no, mask used only in then). So a0's value is not live at else. Hmm, but it's still "set" in the entry block before the branch, so the register a0 at the else has a different value than arg0 — but self's value is in a1 anyway, and local-alloc coalescing of self→arg0 would be invalid because arg0 (a0) was overwritten! That's the key: if a0 is overwritten before the branch, self can't be coalesced to a0 in the else arm. Even if the mask value is dead in the else, the *copy* self=arg0 happened before the overwrite, so self's live range crosses the a0 definition → can't coalesce.

But then the `li a0,-129` would sit in the entry block, before bnez. Target has it after. Unless gcc sinks it. Hmm, could we place the mask assignment inside the then arm but before the branch? No.

Alternatively, force a0 to be defined before the branch by a value that's genuinely used in the then arm only... any such definition would appear before the branch.

What if the a0-defining instruction is the mask, and we place it before the if, but then *also* re-materialize? No.

Hmm hold on — maybe the target's `li a0,-129` in the then block is consistent with the source computing mask in the then block, and the else arm's a1 base comes from self being non-coalescible because self is used *after* a0 is redefined... no, else has no a0 def.

Let me reconsider: maybe the else arm's a1 base is because self is live across the join? At the join (end), self is dead. Hmm.

Let me look at the actual RTL. Use cc1 dumps to see where the a0/a1 decisions come from. But first, maybe simpler: try `self` as `register`-free but with a use in the condition: `if (flag == 0)` where flag loaded from self... no.

Another idea: swap the arms! Put the else content in the if branch and vice versa: `if (flag != 0) { B } else { A }`. Then the code layout changes (B first) which is NOT target (target has A first then B). Unless we invert with goto.

Hmm wait, actually target layout: A (flag==0 arm) first, j end, then B. That's standard if/else.

OK let me look at the RTL dumps for the pinned version vs candidate to understand which pass makes the a0 choice. Use cc1_dumps_tu.sh on the TU? That dumps the whole TU with the current src (pinned). To dump the candidate, I need a TU with the candidate body. delever_search --keep gives cand.o only. But I can create a scratch TU: copy the src file and splice the body? Simpler: use hdump-like approach? For a .c TU, I can copy the whole src file to my item dir and replace the function body with the candidate. The TU is 176KB; copying is fine (scratch). But cc1_dumps_tu.sh expects a .c file and compiles it with includes relative to its dir. The TU includes "../shared/..." — if I put the copy under .run/P40/T11/O05x/<item>/, includes would fail. The header says -Isrc/shared added; the TU's `#include "../shared/..."` resolves relative to the TU's own dir, so a copy must sit one level under src/. I can't write to src/. Hmm, but cc1_dumps_tu.sh cpps from the given file path; the includes are relative to the file's directory. Could I instead make a wrapper .c in src/...? Not allowed to write src/.

Alternative: the .i file — preprocess the original TU from its real location, then splice the candidate body text into the .i, then run cc1 on the .i. That's what I can do: cpp the real TU to a .i in my item dir, then replace the function body (in the .i, the body is expanded with all macros). The body text in the .i may differ (struct accesses expanded). Replacing exactly is doable if I locate the function in the .i.

But is it worth it? The residual is 16 and the only differences are two allocation choices. Let me first try more C variants empirically; cheaper.

Let me think about the else arm again. What if q and g are declared in the *function* scope (top) rather than in the else block? Then their birth/death and qty numbers change. And maybe local-alloc behaves differently. But target allocation q=v0,g=v1 requires q priority > g. q's life is longer than g's, so priority lower unless refs higher. q refs 4 (like p). g refs 2. Then q wins v0! Let's compute: q = `q = self->unk20; q = *(u16*)(q+0x18);` — q is def'd twice, used in address, used in sh → refs 4 → floor_log2(4)*4=8. g refs 2 → 2. So q has higher priority → v0. But in my current candidate, q got v1! Why? Because q and g are in different basic blocks? local-alloc is per basic block; q and g are both in the else block. Hmm, priority computation uses death-birth; maybe q's life is longer, reducing priority: 8/life_q vs 2/life_g. If life_q = 4 insns and life_g = 2, then 8/4=2 vs 2/2=1 → q wins. But mine gave g=v0.

Wait, maybe I mis-assigned: mine else: `lw v1,32(a0)` → q into v1; `lw v0,220(a0)` → g into v0. Hmm so g won. Unless the lw into v1 is q's *address* temp and q is actually v0? Let's trace: `q = self->unk20;` loads into some reg; `q = *(u16*)(q+0x18)` uses it as address and writes into a reg; `self->unk104 = q` sh.

If q's pseudo is v0 (the final value) and the address temp is v1... but with `q = *(u16*)(q+0x18)` it's a single pseudo q (redefined). The lw v1,32(a0) writes q's first value into v1; lhu v1,24(v1) writes q's second value into v1 (same pseudo, same reg v1). Then sh v1,260. So q is entirely v1. Yes q=v1.

So why did g win v0? Let me look at qty computation more carefully: qty_birth/qty_death are insn UIDs, and the priority = (floor_log2(n_refs)*n_refs*size)/(death-birth). Maybe n_refs for q = 3? floor_log2(3)=1, *3=3. life_q maybe 4. 3/4=0.75. g: n_refs 2, 1*2=2, life_g = 2 (load to ori?) hmm 2/2=1 > 0.75 → g wins. Yes plausible.

For p vs f: p refs 3? life longer; f refs 2 life shorter → f should win... but mine has p=v0. Hmm, contradiction again. Unless p refs 4 → 8/life. life_p = 5 (load to sh at delay slot) → 1.6; f: 2/life 2 → 1.0. p wins. For else q: refs 4? life_q = 5 → 1.6; g 2/2 = 1.0 → q should win. But it didn't. Confusing.

Wait, maybe in the else arm, g's load is scheduled before q's? No, target order q load then g load; mine same? Mine else: `lw v1,32(a0)` (q), `lw v0,220(a0)` (g). Yes.

Hmm, maybe local-alloc's qty priority uses the *block-local* birth/death. Let me not over-theorize; test.

Empirical approach: generate variants:
- else with g declared before q
- else with q computed via separate temp
- else field-direct (`self->unkDC |= 0x80;` and `self->unk104 = ...`)

and then the then arm variants:
- f before p declaration
- p via separate address temp
- field-direct store

Let me write a generator script to emit many variants and score them in one go with sc.sh. sc.sh takes multiple files. ~20 candidates per run is fine.

Let me write gen.py in the item dir that takes a variant spec? Simpler: write a Python script that emits N candidate files, then run sc.sh on them.

Design the body as a template with substitution of two arm bodies. Arm bodies to try:

Then arm variants:
T1 (current):
```
        s32 p;
        s32 f;
        mask = ~0x80;
        p = self->unk20;
        f = self->unkDC;
        p = *(u16 *)(p + 0x18);
        self->unkDC = f & mask;
        self->unk100 = p;
```
T2: declarations f,p:
```
        s32 f;
        s32 p;
        ... same
```
T3: field-direct store:
```
        s32 p;
        s32 f;
        mask = ~0x80;
        p = self->unk20;
        f = self->unkDC;
        p = *(u16 *)(p + 0x18);
        f &= mask;
        self->unkDC = f;
        self->unk100 = p;
```
T4: split address temp:
```
        s32 t;
        s32 f;
        mask = ~0x80;
        t = self->unk20;
        f = self->unkDC;
        t = *(u16 *)(t + 0x18);
        self->unkDC = f & mask;
        self->unk100 = t;
```
T5: mask assigned later:
```
        s32 p;
        s32 f;
        p = self->unk20;
        f = self->unkDC;
        mask = ~0x80;
        p = *(u16 *)(p + 0x18);
        ...
```

Else arm variants:
E1 (current):
```
        s32 q;
        s32 g;
        q = self->unk20;
        g = self->unkDC;
        q = *(u16 *)(q + 0x18);
        g |= 0x80;
        self->unkDC = g;
        self->unk104 = q;
```
E2: g declared first
E3: field-direct:
```
        s32 q;
        q = self->unk20;
        q = *(u16 *)(q + 0x18);
        self->unkDC |= 0x80;
        self->unk104 = q;
```
E4: 
```
        s32 q;
        s32 g;
        g = self->unkDC;
        q = self->unk20;
        q = *(u16 *)(q + 0x18);
        g |= 0x80;
        self->unkDC = g;
        self->unk104 = q;
```
E5: `self->unk104 = *(u16 *)(q + 0x18);` directly with q temp.

And self variants: s32 self with casts vs pointer.

Since the else arm's a0 issue is separate, let me focus: the a0-in-else issue is a register choice (coalescing), independent of q/g order. Let me first find which C form avoids the a0 coalescing.

Idea: make self's value used in the else arm in an address computation that differs... hmm.

Wait wait. Look at target entry: `move a1,a0` — and then the then arm uses a1. If self were coalesced to a0 in the else arm, the move would still be needed for the then arm. Fine.

What if we make the else arm use self *before* the then arm? No, block order fixed.

What if `flag` load uses self and the if condition... no.

New idea: make a0 busy at the start of the else block by loading `flag` there? e.g. `if (flag == 0) {...} else { flag = self->unkAA; ... }` — extra load, no.

Another: use `arg0` (the parameter) somewhere after the if so its live range extends and a0 is reserved? e.g. at the end: `self->unk108 = arg0;`? extra store.

Hmm. What about making the parameter used *after* the if, in the join, with no extra instruction? Can't.

OK here's another thought: the coalescing might be done by local-alloc's `combine_regs` on copy pairs, which requires the copy's destination pseudo to be replaced. In gcc 2.7.2 local-alloc, `reg_combined` etc. The copy `self = arg0` where self is used in both arms: local-alloc processes per-block; it can combine self with arg0 in a block if arg0 isn't modified in that block. In the then block, arg0 (a0) is modified by mask → can't combine. In the else block, no a0 def → combine. So self's uses in else become a0.

To prevent combine in the else block, the else block must define a0 (or a0 must be live-in but not a valid copy source). Alternatively, self must be "used" in the else block in a way that requires its own register... 

What if the else block also has `mask = ~0x80;` *used*? If we assign mask in both arms and use it in the else arm's store: e.g. else `self->unkDC = g | ~mask;`? That changes instructions (not/and). Hmm.

Wait — what if mask is computed before the if AND the else arm uses it? Target's else doesn't use a0 though.

Alternatively: the else arm could reference mask in a way that's dead but not eliminated before local-alloc? Dead code elimination (dce) runs before local-alloc? Pass order in gcc 2.7.2 -O2: ... cse1, dce? Let me check toplev.c pass order. Actually the pass order: jump_opt, cse, ... let me check.

Let me look at toplev.c rest_of_compilation.
