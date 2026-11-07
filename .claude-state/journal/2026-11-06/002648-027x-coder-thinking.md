---
ts: 2026-11-06T07:26:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nYNvvmJ7Qe2Uak3aCOz8
---
Interesting! Mine has `li v0,0x8000` then `li a0,75`, while target has `li a0,75` then `li v0,0x8000`. That's the insert/delete at 32/33: target births li a0,75 before li v0,0x8000. And target's copies use a1-a3 because... hmm mine uses a0,a1,a2. Target uses a1,a2,a3. 

The difference: target's `id` (li a0,75) is in a0, but it's defined at insn 32. Why would that shift copy regs? Unless the pseudo `id` is born earlier in target (its live range starts at function entry?) — no.

Wait. Look at the target: `li a0,75` at 32, then `li v0,0x8000`, `move a1,s1`, `move a2,zero`, `move a3,zero`. So a0 holds id. In mine: `li v0,0x8000`, `li a0,75`, `move a1,s1`... same assignments for args. So the only register difference in the call setup is order.

The copy-register difference: target uses a1,a2,a3 (avoids a0) for copies; mine uses a0,a1,a2. So in target a0 is reserved/occupied during the copies. What pseudo occupies a0 there? The `id` pseudo if its live range began before the copies. Perhaps in the target, the pseudo that becomes `id` is actually live from earlier because it's the same pseudo as `v1` used in the copies? No, v1 is the load temp.

Hmm, think about local-alloc: caller-saved regs are allocated by local-alloc (per basic block) and the quantities are sorted. Which register a temp gets depends on the set and order. There are 4 loads in a group; local-alloc assigns regs in qty order. In target, the loads got v1, a1, a2, a3 — skipping a0. Why skip a0? Because a0 was already allocated to another quantity whose live range overlaps this basic block. Which quantity? The `id` maybe: its def `li a0,75` is in the NEXT basic block (after the branch). Actually the branch `bne` and the `sw v0,28(s0)` in the delay slot; the `li a0,75` is in the target block. Local-alloc works per basic block, but global-alloc assigns regs across blocks. a0 is caller-saved, so local-alloc assigns caller-saved regs only within a block. Hmm, but global-alloc may allocate a0 to `id` (which lives only in the if-block) — that's a different block, so no conflict.

Alternatively: the target's a0 usage in copies is avoided because a0 is assigned to `keep_a0` pseudo — the pin! The pin `register s32 keep_a0 __asm__("$4")` creates a pseudo that's live at the keepalive point (after copies) and possibly from `keep_a0 = arg0` (before copies). Its live range spans the copies, occupying a0. In the target, the natural C must have something live in a0 across the copies. The keepalive is exactly that. So the target genuinely has a value in a0 live across the copies! But the disassembly doesn't show any use of a0 in that range... A live range can exist with no visible instruction: the value is set before (move a0?) and used after (the keepalive). But the target has no asm. The target's a0 gets overwritten by li a0,75 at 32 — after copies. So a0's value is live from somewhere to insn 32 but unused in between. What sets it? `move s0,a0` doesn't set a0.

Unless the pseudo assigned to a0 is defined at... nothing. That can't be.

Wait — maybe the reason is different: local-alloc's register preference. When allocating the 4 loads, it uses the caller-saved regs. The order it considers registers may start at a1 because a0 is the "return value" register reserved? No, local-alloc uses a0 freely.

Actually here's a thought: local-alloc assigns hard regs to quantities within a basic block. The copies are one basic block. The set of quantities includes the 4 loaded values. But it also includes `v0` (the pointer) which is live. And possibly arg0? Let me count: 4 loads = 4 quantities, plus v0 pointer. If v0 takes v0, the 4 values take a0..a3. Mine does exactly that: v1, a0, a1, a2? That's 4 regs: v1 (loaded 52(v0)), a0,a1,a2. Wait, only 4 loads and they use v1,a0,a1,a2 — 4 regs. Target uses v1,a1,a2,a3. Why would target start at a1?

Maybe because the register allocator's ordering of hard regs depends on which regs are "free" — a0 might be occupied by the live pseudo `s0`? No, s0 is $16.

OK here's another possibility: target has the `id` pseudo allocated to a0 and local-alloc/global considers it across the whole function since it's a single pseudo used in the if-block. Global alloc assigns a0 to id; then local-alloc, when allocating the copies in the earlier block, must avoid a0 because... local-alloc only avoids hard regs that are live across the block. Is id live across the copy block? id is defined in the if-block, used immediately. Not live across.

Hmm, unless the original source defines `id` earlier (e.g., `s32 id = 0x4B;` at top) and the assignment is in the if? No, the target li a0,75 at 32.

Let me think about the "keepalive" from another angle. Maybe the natural C had `func_80146A6C(id, s1, ...)` with id defined as a variable, and the keepalive was emulating the fact that arg0 is used later: e.g. original may have `s0` not exist and all accesses use arg0 directly? If the body used `arg0` for the struct accesses instead of `s0`, then a0 would be live across the copies and reused. But target clearly does `move s0,a0` early and all accesses use s0. Hmm, but maybe the original C was:

```
void func_800CB458(s32 arg0) {
    s32 s0 = arg0;
    ...
}
```
and the compiler chose to copy to s0 because arg0 is a parameter needing a callee-saved reg (used across calls). That's what happens. So a0 free.

Let me look at the actual difference in allocation: is it possible that target's copies use a1,a2,a3 because the FIRST load is v1 and local-alloc assigns in reverse order? Let's understand local-alloc ordering: quantities in a block sorted by priority (refs, live length), ties by birth. The four loads are identical (1 ref each? they're each used once in a store). Ties broken by birth order (local-alloc.c:1486-1507: "A block with exactly THREE quantities is allocated in BIRTH order"). With four quantities, sorted by qty_compare.

The difference could stem from a 5th quantity in the block. In target, there might be an extra quantity (the keepalive's a0 pseudo) that consumes a0, shifting the 4 loads to a1-a3. The keepalive pseudo IS the extra quantity: `keep_a0 = arg0` before the copies creates a def of a0 (well, a copy from arg0), and the asm use after. In the compiler, the keepalive asm has a def/use of the register variable keep_a0, whose pseudo is live across the copy block and allocated to hard reg $4 (register asm var). That reserves a0 in that block, so the copies use a1-a3. That's exactly the lever's effect.

To remove the lever with real C, we need a genuine value in a0 live across the copies. What could it be? In the target, is there an instruction that sets a0 before the copies? No. So no.

Hmm wait, actually maybe the target's a0 IS the id value and the `li a0,75` is just where it's set — but the pseudo could be "live" from block start if it's referenced in a PHI-like manner? GCC 2.7 has no SSA.

Alternatively: maybe the effect isn't a0 being live but register allocation order in local-alloc being perturbed by the extra quantity (the pin pseudo) in the same block. The pin pseudo `keep_a0` is defined in the entry block (keep_a0 = arg0) and used in the copies block (asm). Being a hard-reg var, it's not allocated by local-alloc. But its presence as a live hard reg at block start means local-alloc marks a0 as used in that block and won't allocate it. That's the mechanism. So the copies use a1-a3.

Now, the target naturally has a0 occupied during the copies. Since target has no asm, there must be a real C value live in a0. Could it be `arg0` itself, used after the copies? If the original C used `arg0` (not s0) for the decrement at the end? No, uses s0.

Wait, maybe `s0` isn't a separate variable; maybe `s0 = arg0` and the compiler keeps arg0 in $4 because s0 gets... no, move s0,a0.

Let me reconsider: maybe the target's a0 usage is the return value of func_800CAF84? No.

Actually — maybe the original had a local variable that is a copy of arg0 used in the if-block, and the compiler moved it to s0. Hmm.

Let me check whether target's a0 is truly live across the copies by checking register allocation: In the target's if-block, `li a0,75` — a0 is written there. If a0 were live from a prior def, it'd be killed here. Nothing sets a0 before. So a0 is dead across the copies.

So the target's a1-a3 assignment must be explained by local-alloc's allocation order, not by a0 liveness. Maybe the difference is caused by a different set/order of quantities in the block: e.g., in the target the block has 5 quantities and the 5th (dead?) takes a0... but instructions identical.

Hold on: local-alloc allocates regs to quantities; the register order used is from `reg_alloc_order`? In GCC 2.7, `local-alloc.c` uses `reg_alloc_order` from `regclass`? Actually it uses `regs` list built from `reg_alloc_order`? Hmm. Let me think about `local-alloc.c` `block_alloc`: it computes `qty` for each quantity, sorts by `qty_compare`, then loops over `reg_alloc_order`? Let me read the reference source. tools/reference/gcc-2.7.2/local-alloc.c exists? The brief lists jump.c, combine.c, reorg.c, cse.c, sched.c. Let me check local-alloc.c.

Actually maybe the mechanism: local-alloc assigns the FIRST quantity the first free caller-saved reg. The free set at block start excludes regs live across block boundaries (allocated by global-alloc). If a0 is live across the block, it's excluded. Which global pseudo could be in a0? `id`? id is defined and used within the if-block only, so it's local to that block (local-alloc assigns it). Hmm.

Unless `id` was assigned by global-alloc to a0 because it's used across... no.

Let me test: what if I add a real C use that keeps arg0 live? For example, use arg0 instead of s0 in the final if-block: `((Unkstruct*)arg0)->unk1C` instead of s0. That would keep arg0 live across calls (needs callee-saved, so s0). Hmm.

Better test: what if the original C did NOT have `s0 = arg0` but used `arg0` directly, and the compiler created the copy to s0? It would do that automatically if arg0 used after calls. So write body without s0, using arg0 everywhere. Then arg0 (a0) is live across the copies (it's used in the if-block after func_800CAF84 call), so global-alloc assigns it to s0 ($16) — the move s0,a0 — and a0 is free. Same result.

Hmm. Let me just try variants empirically. The key residual: register shift a0->a1 etc (4 pairs) and the li order. Let me first fix the li order: target has li a0,75 before li v0,0x8000. In source, `id = 0x4B; func_80146A6C(id, s1, 0, 0, 0, 0x8000, 0);`. The li v0,0x8000 is the 6th arg (0x8000) passed on stack? Actually func_80146A6C has 7 args; args 5,6,7 go on stack: sw zero,16(sp); sw v0,20(sp); sw zero,24(sp). `li v0,0x8000` sets the value for the 6th arg stored to 20(sp). Target births li a0,75 (id) before li v0,0x8000. Mine does v0 first. This is scheduling order (sched1 birth order). Source order: id=0x4B then the call. Both id and 0x8000 constant are needed. The target schedules li a0,75 first. In mine, li v0,0x8000 first. Hmm — maybe because in target, a0's value (id) has an earlier birth LUID? Both source lines: `id = 0x4B;` (line before call) and the constant 0x8000 is part of the call expression (line after). So source order matches target; mine reversed. This could be sched1-birth-order wall, but might resolve once register allocation matches.

Actually the count score 14 = 4+4+4 pairs + insert+delete? The li order contributes insert/delete (1 each?).

Let me try: what if keep the pin but give keep_a0 a real C use? E.g.:
```
keep_a0 = arg0;
...
v0 = keep_a0; // no
```
Any real use of keep_a0 (a register var) counts as reading $4. But that's essentially a launder/keepalive via C, and "identity-statement launders do NOT count as a crack". Using `keep_a0` in a real computation that affects output would change semantics/bytes.

Hmm. The pin itself is a lever of kind "pin" that "may stay" (under other causes). Wait, is the pin allowed to stay even though it's not in kinds? Yes: "levers of other kinds the def already had (pins under other causes) may stay, never added". So I can KEEP the pin AND the `keep_a0 = arg0` assignment, just remove the keepalive asm. But then keep_a0 is set and never used -> flow deletes it -> pin has no effect. Unless... a `register` variable assigned but unused: does flow delete? It's a dead store to a hard reg; flow removes dead stores. Then a0 free.

But maybe I can keep the pin effective by using `keep_a0` in a way that's real C. Hmm.

Alternative: maybe the natural C is that arg0 is passed to func_800CAF84? No.

Let me look at the actual original source history — maybe there's a notes file or the git log for this function. The source line has comment "!FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t8_tus2)" and keepalive same tag "t8_tus2". Let me look at the function's history: maybe .run/P36/agents/ has a pack for t8_tus2. But we're told not to read outside? We may read .run/P40/T11 and tools. Reading .run/P36 might be fine (not forbidden). But budget.

Let me think about what real C gives a0 liveness. The target's a0 dead zone: maybe a0 is allocated to a quantity whose live range spans the copies but has no instruction — impossible.

Let's test the hypothesis that it's local-alloc's quantity ordering, not a0 liveness. Add a 5th quantity to the copy block, e.g. split a load/store into two statements with a temp:
```
s32 t0 = *(s32*)(v0+0x34);
*(s32*)(s0+0x38) = t0;
```
That's already what it does effectively (the lw/sw are one set each). The quantities are the 4 loaded values. The regs: v1,a1,a2,a3. In target the FIRST value (52(v0)) went to v1, then a1,a2,a3. In mine first to v1 then a0,a1,a2. So local-alloc picked v1 first in both (v1 is the first free? or highest priority). Then the remaining three: target a1,a2,a3, mine a0,a1,a2. So a0 is excluded in target. That strongly suggests a0 is live/occupied in the target during that block.

Which value is in a0? Could be the function's own argument still live: if the original C didn't copy arg0 to s0 but the compiler still needed arg0 in a0? But move s0,a0 sets s0; if arg0 is used later, the compiler would keep arg0 in a0 OR copy to s0. It chose s0 (callee-saved) because used across calls. So a0 dead.

Wait, maybe a0 holds a value used AFTER the copies but before the call, and the use is the `func_800CAF84()` call? void no args. Hmm.

Let me look at the target bytes again around copies: after `sw a3,84(s0)` comes `jal func_800CAE0C` (func_800CAF84 relocated). No a0 use.

So a0 is dead from insn 2 to insn 32. Therefore local-alloc excluding a0 must be because a0 is allocated to a pseudo live across the block by global-alloc — and that pseudo has no instructions in between because it's... hmm, a global pseudo's live range is a set of blocks; it can span the block without being used there if it's live across. Which pseudo? `s1`! s1 = struct->unk34 is loaded at insn 5 and used in the if-block at `move a1,s1`. s1 is live across the copies! But s1 is $17 (callee-saved). And s0 is $16. Those are callee-saved.

Is there any OTHER value live across the copies? `v0` (the pointer) is used for all copies, live in the block. `s1` is $17. Hmm.

Maybe the copies' loaded values are used in stores; each value's live range is short. 

What if in the target, the loads/stores are not 4 separate quantities but 2 struct copies of 16 bytes each? The source says `*(Struct16 *)(s0+0x38) = *(Struct16 *)(v0+0x34);` — Struct16 is 16 bytes, copied as 4 words. Expand_block_move generates 4 loads/4 stores with 4 temps. Fine.

Maybe the a0 reservation comes from `arg0` being used for the stack? No.

Let me just try empirical variants. Variant A: keep pin+assignment, no asm (w1) → 14. Variant B: keep pin+assignment, and replace the asm keepalive with a real C statement that uses keep_a0 in a dead-but-not-deletable way? Not allowed (launder).

Variant C: Remove pin and keepalive entirely, use arg0/s0 naturally; maybe allocation differs. Let me try removing the pin line and assignment too (fully lever-free). This is the true target: "write a lever-free body". The pin may stay but doesn't have to. Let me try.

Actually wait. The constraint says win.c must have kinds gone; other levers may stay. But the ideal is fully lever-free. Let me try removing pin and keepalive both.
