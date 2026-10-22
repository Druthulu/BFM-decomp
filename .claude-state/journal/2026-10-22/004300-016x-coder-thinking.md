---
ts: 2026-10-22T06:43:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_HXhuVo5x0WlhI1a7nKHD
---
Confirmed: the only difference is `li a0,16` at position 5 (mine) vs 7 (target).

Interesting: target has, at 5,6: sw s0,24(sp); move s0,a2; then li a0,16 at 7; sw ra; sw s3; jal.

Mine: li a0,16 at 5; sw s0; move s0,a2; sw ra; sw s3; jal.

So the difference: mine hoisted li a0,16 one slot earlier relative to sw s0/move s0,a2 — 2 slots.

Now the key question: why does the asm version produce the target?

Hypothesis: the asm `__asm__("" : "=r"(rgb) : "0"(rgb))` in the tree — with rgb being a register variable in $16 — is an asm insn with an output that is a hard reg pseudo. GCC's RTL for a register variable assigned $16: the variable lives in a pseudo bound to $16? Actually `register s32 rgb __asm__("$16")` binds the variable to a hard register, so uses of rgb are direct $16 references, not pseudos. Then the asm with "=r"(rgb) outputs into $16 directly (a hard reg). So the asm is: output = $16 (hard reg), input = $16. Zero instructions.

Now: in GCC, an asm with a hard-reg output creates a REG_DEAD/REG_LIVE... it's a "REG_DEAD" note for $16, and then subsequent uses of $16 require a reload → GCC may insert a copy? Hmm, but the target's code shows `move s0,a2` before, and sw s0,4(s3) later — no extra copies.

Hmm, wait. Actually since rgb is a local register variable in $16, the assignment `rgb = arg2` puts arg2 in $16 at the function entry (move s0,a2). The asm's output $16 is dead right after (the asm produces nothing but claims $16 output), so GCC treats $16 as defined-but-dead → the next use of rgb (the store) needs $16 = value → but since the asm killed $16, GCC would need to restore it! Yet the target shows sw s0,4(s3) with the value from the original $16 — so GCC kept it (the asm's "=r" output of $16 with input $16 is a no-op; GCC's flow might handle it as a copy: it inserts a copy from the input to the output, but since both are $16 it's nothing... but then $16 is dead after the asm and the later use of rgb would need a reload → GCC's shrink-wrapping/`REG_DEAD` handling...).

Hmm, in fact the compiled target has only ONE def of $16 (move s0,a2 at 6) and one use (sw s0,4(s3)). So GCC didn't treat the asm as killing $16. Actually GCC does handle asm outputs on hard regs: it records the output as a "reg" and inserts the asm; after the asm, $16 is considered to hold the asm's output (which is undefined). Then the use of rgb later needs a copy... unless GCC noticed the asm has a matching input and didn't kill.

Actually, GCC's `reload` might treat the asm output as needing a "reload" of $16 at the later use → would produce `move s0, s0`? Not in the target.

OK. Whatever the mechanism, the target's instruction order differs from mine by exactly the position of `li a0,16`. That means the asm affected the *scheduling* of the entry block: the presence of the asm insn (zero-length but still an insn in the RTL, with a "birth" of $16?) makes sched1 place things differently.

Key insight candidate: the asm is an instruction in the entry block BEFORE the call. sched1's "birthing boost": an insn that defines a pseudo that has no other def... The asm defines $16. Hmm, but $16 is a hard reg.

Alternative key insight: sched1's boost applies to `li a0,16`? Actually, GCC's sched1 has this in its main loop:

```
	      /* Prefer to schedule instructions that are the sole use of a pseudo... */
```
and specifically:
```
	  /* Now, schedule the instruction ... */
```
Hmm.

Let's try to look at gcc's sched1.c source if available on this machine. Probably not. But the project has cc1 dumps tools (alloc_table.py). Maybe I can dump the RTL.

Alternatively, let's try empirically: what if the 2nd set is achieved by making the *use* of rgb happen early — e.g. `if (rgb == rgb) {}`? That's an early use of $16 which forces... hmm, `rgb == rgb` is folded to true. What about using rgb in a dead store to a volatile? No, that changes code.

Different approach: maybe we don't need $16's def placement to change; maybe we need `li a0,16` to be pushed later. What pushes it later? Something between the s0 save and li.

Alternative: change the *statement order* in C: move the `rgb = arg2;` assignment later? No — rgb must be set before the call.

Wait... actually! What if we make the rgb assignment happen at a different point, e.g. right before the store, so the def of $16 is later, and the `li a0,16` stays at 5-6? But target has move s0,a2 BEFORE li a0,16, i.e. the def is early. Hmm.

Let me reconsider: in the target, the order is: sw s0,24(sp) (5), move s0,a2 (6), li a0,16 (7). So the def of $16 is before li. In mine: li (5), sw s0 (6), move s0,a2 (7).

What if the mechanism is: the asm's use of $16 (tied input) creates a dependency that forces $16's def to be scheduled before the asm, and since the asm is in the entry block before the call, the def gets boosted to be as early as possible (right after the prologue arg copies) — i.e. before li a0,16 which belongs to the call group.

So the recipe: give $16 an early *use* in plain C. But an early use that's dead...

Hmm, in GCC, a plain C use of rgb like `rgb = rgb;`? Eliminated.

What about making the store `*(s32 *)((u8 *)temp_v0 + 4) = rgb;` happen... it's after the call.

What about: `if (rgb == 0) { }`? Not dead-code-eliminated necessarily... it adds a branch. Actually GCC would fold `rgb == 0` to a branch — changes code.

Hmm. But maybe there's a smarter path: what if instead of keeping rgb as a pinned register variable with 2 defs, we could restructure so that the def of $16 comes from the argument copy differently. E.g. `rgb = arg2;` — the def is a copy from a2. What if the source of the copy is different, e.g. `rgb = arg2;` vs the pin?

Wait — maybe the difference is not about $16's def but about the *pin* interacting with the asm. Let's test: what if we remove the launder AND the rgb pin (rgb as a normal local)? Then gcc would assign rgb to some other register and the code would differ a lot (but the constraint allows keeping pins; removing the pin is allowed too since pin isn't the row kind — but removing it will change the register allocation drastically).

Let me think about the "birthing boost" in sched1 more concretely. I'm fairly confident about this code in gcc/sched1.c:

```
	      /* Prefer to schedule insns that are the sole use of a pseudo
	         (i.e. that kill a pseudo) ... */
```
Hmm.

Actually! I recall in sched1.c:

```
  /* Now, schedule the instructions ... */
  ...
	      if (!REG_P (dest) ...)
```

There's this in sched1.c (function sched1, main loop):
```
	  /* Increment the priority of the insn if it is the first use of
	     a pseudo (i.e. a "birth").  */
```
Hmm, no. The famous "birthing boost" in sched1 is:

```
/* Return true if INSN is the sole use of the pseudo register... */
```
Hmm.

Alternatively, gcc's "birth" concept appears in `reload`/`global.c`? The term "birthing insn" appears in gcc/sched1.c? Let me search the internet memory: In sched1.c there's:

```
	      /* Prefer to schedule insns that have a higher priority.  */
```
and
```
	  /* Give a boost to instructions that are the birth of a pseudo.  */
```
I'm fairly sure sched1.c has:
```
static int
sched1_look_insn (...)
```
Hmm no.

OK: empirical. The effect I need: `li a0,16` scheduled after the s0 save/def rather than before. What control do I have in plain C? The relative order of the s0 save/def vs the call group.

What if we could make the `sw s0,24(sp)` store happen LATER? No, that's fixed by the callee-saved convention.

What if we avoid the callee-saved s0 entirely? I.e., don't pin rgb to $16; instead, let rgb live in a caller-saved reg... but the target stores rgb after a call, so it must be callee-saved.

Hmm, alternatively: what if rgb is not stored after the call but the whole thing restructured? The target has `sw s0,4(s3)` after the call — the value of rgb must survive the call.

Wait, maybe I'm overcomplicating: maybe the trick is that in the tree, the asm makes GCC think $16 is *not* live across the call in the same way, so the sw s0,24(sp) save is placed differently...

Let me try a completely different tack: use the alloc/dump tooling to inspect what changes. tools/cc1_dumps_tu.sh + tools/alloc_table.py. That could tell me the register allocation. But the difference is only scheduling.

Alternatively, think about "the launder is a zero-byte 2nd SET: kills the sched1 birthing boost". This comment (written by a previous agent, from P36) says the effect: the 2nd set kills the birthing boost. Which instruction gets the birthing boost? In the tree's body (without the pin), rgb = arg2 is a single-set pseudo; sched1 boosts the birth of rgb...

Hmm, here's the thing: sched1's boost is for the *use* side. In gcc's sched1.c there IS this code:

```
	      /* Now, if the insn is a birth of a pseudo (i.e., it defines a
		 pseudo that has only one definition), give it a boost ... */
```

Actually here's the real gcc sched1.c code I recall (from `sched1` function):

```
	  /* Prefer to schedule insns that are the sole use of a pseudo
	     (i.e. that kill a pseudo) ... */
```

Hmm, and there's this famous bit in sched1.c:

```
	  /* Give a boost to the insn if it is the birth of a pseudo.  */
	  if (REG_P (...) && ...)
```

I'm going in circles.

New approach: let's brute force with more variants. The lever-free space here is: plain C, same semantics, changing scheduling. Options that could give $16 two defs or change def order:

1. Make rgb's type u32 (pin $16) and store `(u32)`: the store `sw s0,4(s3)` — with u32 the store is the same. The def `move s0,a2` same. But maybe the mode change alters cse/sched1 priorities (like the s16 trick in G14: "v = (s16)v; real 2nd set"). Try: `register u32 rgb __asm__("$16");` and `rgb = arg2; rgb = (u32)rgb;`? Hmm, (u32)rgb is a no-op cast (same mode, unsignedness change → gcc's convert may still create a NOP_EXPR copy which combine folds).

Actually in G14's case `v = (s16)v` changed the MODE (SI→HI), so it's a real truncation+extend, not folded. For u32→u32 there's no mode change.

What about making rgb s16 and storing `(s32)rgb`? That changes the stored value (truncation) → code differs (extra sign extend). Unless... the target's stored value is `arg2` full 32 bits. So no.

2. What about giving rgb a 2nd def via a different but equivalent expression: `rgb = arg2;` and `rgb = (s32)(u16)...` no.

3. What if we split the difference by changing WHEN the def happens: `rgb = arg2;` placed AFTER the call to func_80010A08? Then $16's def moves later, and maybe the whole entry block reorders to match? But then rgb's value must be arg2, and $16 must be set before the store (after the call) — but $16 is callee-saved so it must be saved/restored in the prologue: `sw s0,24(sp)` still in the prologue, and `move s0,a2` would move to after the call. But the target has move s0,a2 in the prologue. So no.

Hmm, but what if the C says `rgb = arg2;` in the prologue but the ORDER of statements changes so that the compiler schedules differently? C statement order doesn't dictate asm order, but it influences sched1's priority.

4. What about adding a harmless statement that occupies the slot? Like a dead assignment that GCC eliminates — no effect.

5. What about the `mask1` variable or others?

Hmm, let me reconsider the problem: perhaps the difference isn't the launder's 2nd set at all but the fact that the asm is an *asm insn* in the block, and sched1 handles asm insns specially (they get scheduled but the region splitting...).

Since the tree's asm is `__asm__("" : "=r"(rgb) : "0"(rgb))`, GCC's expand_asm produces an ASM insn with output $16 (hard reg). Then in RTL, this ASM insn is a "birth" of $16 (defines it) → sched1 sees a pseudo... $16 is a hard reg (REG). Hmm, for hard regs there's no pseudo.

WAIT. Maybe it's not hard-reg! `register s32 rgb __asm__("$16")` — GCC supports this: the variable is allocated to the specified hard register, and GCC creates a pseudo bound to it (local register var). The pseudo's reg is set to $16 by the local register variable machinery; RTL uses the pseudo with a fixed reg. Then the asm output "=r" forces the pseudo into a hard register? If the pseudo is already fixed to $16, "=r" is fine.

Now, the pseudo for rgb has: def at `rgb = arg2` (set), def at the asm (set), use at the store. With 2 defs, the pseudo is not a "birth" → sched1 doesn't boost the first def.

The boost in sched1: I'm now fairly confident gcc sched1.c contains:

```
	  /* Prefer to schedule the insn that is the birth of a pseudo
	     (i.e., the insn that defines a pseudo which is used only
	     once) ... */
```
Hmm, hmm. There IS a known gcc concept: in sched1.c,

```
/* Return true if INSN is a "birth" of a pseudo, i.e. it defines a
   pseudo that is not live before it. */
```
Hmm, no — that's in regmove? The "birthing" concept appears in `reload.c`?

Whatever. Let's just try: can we get a 2nd def of the rgb pseudo in plain C? The candidates I tried (rgb = arg2 twice, self-copies) all gave score 2 — meaning the second def was folded away (cse/combine), so the pseudo still has 1 def.

A compound assign like `rgb |= 0` was folded. What about a compound assign that ISN'T folded but preserves the value? e.g. `rgb &= 0xFFFFFFFF` — on s32 that's identity; gcc folds `x & -1` → x. `rgb ^= 0` → folded.

What about `rgb = rgb + 0` → folded.

What about a real 2nd def that changes the value in a way gcc can't see? Like `rgb = arg2; rgb = (s32)(u32)rgb;` — folded (cand07, score 2).

Hmm, what about assigning through a different lvalue: `*(s32 *)&rgb = ...`? Ugly, and the pin might break.

What about using a union/struct to force a copy?

Alternatively: what about making the *asm-free* body use a SECOND variable for the value and making the pin apply differently? E.g. pin $16 to a temp that's assigned twice:

```
register s32 rgb __asm__("$16");
rgb = arg2;
rgb = arg2;   /* folded */
```

What if instead:
```
s32 t = arg2;
rgb = t;
t = arg2;      /* 2nd def of t */
rgb = t;       /* 2nd def of rgb! */
```
Would cse merge the two `rgb = t` copies? The second rgb=t copy: cse might see rgb already = t... but t was redefined, so the second copy is a "new" value. Since t is redefined to the same value arg2, cse might propagate t's value (arg2) and then rgb = arg2 → folded to the first copy. But if t is a *pinned* var or volatile... hmm.

But wait, does the 2nd def of the rgb pseudo even matter, or is it the *use* count? Let me test the hypothesis differently: what if I remove the launder but ADD an early use of rgb that is harmless? For instance, reorder statements so that the store of rgb into temp_v0+4 happens before... no, temp_v0 isn't available before the call.

Hmm, actually here's a thought: what if the value stored `*(s32 *)((u8 *)temp_v0 + 4) = rgb;` used `arg2` directly instead of rgb (rgb unused then)? Then $16 is never defined → the pin var is dead → no sw s0 save → different code entirely.

OK here's another thought experiment. What if instead of removing the launder we replace it with a *different lever-free construct that produces an asm-free but scheduling-equivalent effect*: e.g. `do { } while (0);` gave score 4. What about `if (0) { }`? Or `rgb = rgb;` inside a `do{}while(0)`?

Hmm cand03 (do{}while(0)) gave score 4 — worse (probably because the do-while creates a loop and changes other stuff). Let me look at cand03's diff to learn.

Let me be smarter: use the RTL dump to see what the asm does. tools/cc1_dumps_tu.sh can dump the TU's RTL. But the target (tree) build is in build/ — its RTL? The tree's compiled object is the target. I could dump the RTL of the tree's TU (with the asm) and of my candidate, and compare the entry block.

Actually a faster diagnostic: compile the tree TU myself with -fdump-rtl... but tools/cc1_dumps_tu.sh does that. Let me look at it.

Actually, let me think about the actual gcc mechanism for sched1's boost. I'm now recalling more precisely: gcc's sched1.c has this function:

```
/* Return true if INSN is the sole use of the pseudo register REG.  */
static bool
sole_use_of_p (insn_t insn, reg_t reg)
```
Hmm no.

There's definitely this in sched1.c:

```
	  /* Prefer to schedule insns that are the sole use of a pseudo (i.e.
	     that kill a pseudo) ... */
```

And there's this in sched1.c `sched1`:
```
	      /* Increment the priority of the insn if it is the sole use of
		 a pseudo (i.e., a "kill"). */
```

I recall from the RTL scheduling docs: sched1 gives "priority boost" to:
1. instructions that use a pseudo exclusively (sole use) — "use" boost
2. instructions that are the sole definition...

Hmm, but the project's own note says "zero-byte 2nd SET: kills the sched1 birthing boost". So they had a mechanism understanding: 2nd set kills a boost related to "birth".

In gcc's `sched1.c` there IS this comment (I'm now fairly sure):

```
/* Return true if the insn is the "birth" of a pseudo: it defines a pseudo
   that is not defined elsewhere.  */
```
Hmm.

Alternatively, the concept comes from gcc's `sched1.c`:
```
	  /* Some instructions are "births" of pseudos: they define a pseudo
	     that is used only once... */
```

OK. Let's approach it via the "regmove" or "combine" phases? No.

Practical approach: try many plain-C variants and see which shifts the li a0,16. Since scoring is ~1s each, I can try dozens.

Variants to try:
A. Different order of the prologue-ish statements: e.g. move `rgb = arg2;` after the `*(u8*)(...+3) = 3;`? etc.
B. Change `mask1`, `bidx` etc. — no, those are in the if-block.
C. Change the call `func_80010A08(0x10)` to use a variable: `s32 sz = 0x10; temp_v0 = func_80010A08(sz);` — this changes li a0,16 into move a0,sz. No.
D. What if `rgb = arg2` is written as `rgb = arg2, rgb = arg2;`? same.
E. What if we introduce an intermediate: `rgb = arg2;` then later `*(s32*)(...) = rgb;` — what if we store `*(s32*)(...) = (s32)rgb;`? same.

F. What if the *pin* is on a different variable: e.g. pin the store's temp. Hmm.

G. What if we write `rgb = arg2;` as `rgb = arg2;` but declare rgb BEFORE the other decls (decl order)? Already.

H. What if we remove the `register` pin for rgb and instead pin nothing, letting gcc choose? Then rgb would go into a different reg → different code.

Let me test the "how sensitive is this to one instruction" question: is the li a0,16 placement sensitive to the presence of an early *use* of rgb? Let's test a variant where an early harmless use of rgb exists. How about using rgb in the call argument? No, the call takes 0x10.

What about: `if (rgb == 0x12345678) { temp_v0 = func_80010A08(0x10); }`? That adds a branch. No.

Hmm, what about the *unused* use: `rgb = rgb;` might survive as a "copy" in RTL if it's not folded... it was folded (cand04, cand07 score 2).

New idea: use a compound assignment that changes the value in a way that is provably a no-op but not folded: `rgb = rgb + (0 * arg0);`? gcc folds 0*x → 0 (with potential overflow issues, gcc still folds since unsigned/UB). `rgb += (s32)(u8)0;`? folded.

How about `rgb ^= (rgb - rgb);`? folded.

What about a 2nd def that's a *volatile* read? e.g. `rgb = (s32)(volatile s32)rgb;`? That's a volatile read of $16 → gcc would generate a load from memory — no, for a register variable a volatile read of a register var is just the register. Hmm! `volatile s32` on a register variable: gcc might allow reading it. But it adds no code (register var read = the reg). And it would create a NEW set of the pseudo? Actually a volatile read of a register variable is just the register — no instruction, but the RTL would have a set of the pseudo! That's a "2nd SET" — exactly what we need, in plain C!

But: can you declare a register variable volatile? `register volatile s32 rgb __asm__("$16");` — GCC might complain "volatile register variable" is fine? Actually GCC says: "warning: 'register' variable 'rgb' has been assigned to a fixed register" and volatile with register... The C standard says a register variable can't be volatile-ish (address taken). GCC allows `register volatile int x __asm__("$16")`? Hmm, I believe GCC allows it but with restrictions.

But careful: the pinned var rgb is declared in the def; changing `register s32 rgb` to `register volatile s32 rgb` — is that a "lever"? No, it's plain C. But is it a "keepalive"? No.

Hmm, but a volatile read might generate an actual load if the var is not in a register... it IS in a register.

Alternatively — simpler: `rgb = (s32)rgb;` where the cast is to a *different* mode. What if rgb were declared `s16` and the store used `(s32)rgb`? Value change. No.

Hmm OK, but what about this: the launder's purpose is a 2nd def of the *pseudo* for $16. Another plain-C way: make the def come from a copy that GCC cannot fold: e.g. `rgb = arg2;` where arg2 is passed through a function? no.

What about: `rgb = arg2;` then `rgb = rgb;` — folded. `rgb = (rgb, arg2);`? comma expr → same as rgb = arg2.

What about an assignment through a pointer to rgb? `*(s32*)&rgb = arg2;` — taking the address of a register variable is illegal (GCC error: "address of register variable requested"). Yes, error.

Hmm what about `rgb = arg2;` where the second def is via a compound assignment with a variable that's zero at runtime but not provably: `rgb += zero_var;` where zero_var is a local u8 = 0? gcc would propagate the constant 0 → fold. Unless zero_var is set from a call: e.g. `s32 z = func_80010A08(0) ...` no, that adds a call.

What if z is a global (extern s32 z;)? Then `rgb += z;` is not foldable, and it adds a load → changes code. No.

OK: volatile read seems promising. Let me also consider: is a "volatile read" a barrier? The row kind is launder, so a barrier would be adding a NEW lever of another kind — "no new lever of any kind". A volatile is arguably a barrier kind! The brief lists kinds: pin, launder, barrier, keepalive. Adding a volatile read = adding a barrier lever. Risky.

Hmm. But wait — the tree's def may already contain volatile. Not here.

Let me think differently: what about the *dead-reset* trick from G15 item 1 (my own shard!): "pb = 0; // dead reset: breaks cse's equivalence". Here we need a 2nd def of $16 that is DEAD (so it costs no instruction). `rgb = 0;` would be a real def of $16 with a value change → the store would store 0. Unless the def is dead... but it's the same variable; the later use reads the new value.

Hmm! Unless the later use reads a DIFFERENT variable. I.e. split: pin $16 holds `rgb`, and the store uses a different var? No, the store must get arg2.

OK here's another angle: what if we give $16 TWO defs where the second is dead because the store uses a *different* copy of the value? Like:

```
register s32 rgb __asm__("$16");   /* pinned */
s32 v = arg2;
rgb = v;
*(s32 *)((u8 *)temp_v0 + 4) = v;   /* store uses v, not rgb */
rgb = 0;   /* dead reset, 2nd def of $16 */
```
But then the store would use `v` (in a different register) → the target stores from s0 → mismatch.

Hmm, but wait: if the store uses v, and v is a copy of arg2 in some reg, gcc might coalesce v into $16 anyway (since rgb is dead after). Then: $16 = v; store sw $16; then `rgb = 0` → but that's a live def of $16 after the store, so gcc must keep it → `move s0,zero`? That adds an instruction. Unless gcc sees $16 is dead after (function end, $16 restored) → the `rgb = 0` is dead → eliminated → no 2nd def survives!

Order matters: put the dead reset BEFORE the store:
```
rgb = arg2;      /* def 1 */
rgb = 0;         /* def 2, dead? no — the store would then read 0 */
```
No good.

Alternative:
```
s32 v = arg2;
rgb = v;                 /* def 1 of $16 */
rgb = v;                 /* def 2 — cse-folded */
```

Hmm.

What about: the store `*(s32 *)((u8 *)temp_v0 + 4) = rgb;` — what if we write it as `*(s32 *)((u8 *)temp_v0 + 4) = (s32)rgb;`?

OK, let me step back and consider that maybe the 2nd-set hypothesis is wrong and the real mechanism is something else entirely — e.g., the asm prevents gcc from shrinking-wrapping or from "reusing" the arg2 register.

Observation: in the target, `move s0,a2` (def of $16) is at position 6, and the call's arg setup `li a0,16` at 7. In mine, `li a0,16` at 5 and `move s0,a2` at 7.

Note also the target's `sw s0,24(sp)` at 5 — the save of $16. Mine has it at 6.

In gcc, the callee-saved save is inserted early (in the prologue) by the `save` pass... but here they're interleaved with the arg copies, which suggests the prologue was built by "prologue" pass: sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, sw ra, sw s3, jal... Actually the standard MIPS gcc prologue order: it usually emits `addiu sp; sw ra; sw s0; sw s1...; sw s2...`. Here we see a strange order: sw s2, move s2,a0, sw s4, move s4,a1, sw s0, move s0,a2, li a0,16, sw ra, sw s3, jal, sw s1(delay). This looks like the scheduler (sched1) reordered the prologue! The "move sX,aX" copies are inserted by the prologue pass, and then sched1 reorders.

So the question is why sched1 puts the `li a0,16` (call arg) before or after the s0 save/def.

In sched1, priorities are computed; the boost might be given to instructions that are "the birth of a pseudo" — e.g. `li a0,16` defines a0 (a hard reg!). Hmm, a0 is hard. `move s0,a2` defines $16 (pseudo for the local var).

Actually! Since rgb is a local register variable (pseudo bound to $16), the def `move s0,a2` defines a PSEUDO (the local var pseudo) even though it maps to $16. Then the asm's output ALSO defines that pseudo → 2 defs → the pseudo is not a "birth" → sched1 doesn't boost it. Without the asm, the pseudo has 1 def → it's a "birth" → sched1 boosts the birth instruction → schedules `move s0,a2` EARLIER. But observed: in mine, move s0,a2 is LATER (7 vs 6). Hmm, that contradicts... unless the boost moves it earlier in a different sense: boosted instructions are scheduled first within the region, and the region might be after the li.

Wait, actually maybe: the boost applies to the instruction that KILLS the pseudo (the use) vs the birth. "birth" = the def. If move s0,a2 is boosted, it goes earlier relative to competing instructions. In mine it's at 7 vs target 6 — but "earlier" in a different coordinate? In mine the sequence around: [5]=li a0,16, [6]=sw s0, [7]=move s0,a2. In target: [5]=sw s0, [6]=move s0,a2, [7]=li a0,16.

Hmm, so in mine the pair (sw s0, move s0,a2) is at 6,7 and li at 5. If the boost moved move s0,a2 earlier, it'd be at 5, before sw s0? But sw s0 must precede... no, sw s0 stores the OLD s0 (callee-saved save) — the save must come before the def (else it'd save the new value!). So sw s0,24(sp) MUST precede move s0,a2. OK.

So the "boost" in mine might have pushed the (sw s0, move s0,a2) pair to positions 6,7 instead of 5,6, i.e. AFTER li a0,16. Which contradicts "boost → earlier"...

Unless: the boosted thing is `li a0,16`! In mine (single def), li a0,16 gets the boost → placed at 5 (earliest possible). In the target (2 defs), no boost → placed at 7. YES! That fits perfectly: the boost is on the pseudo that the li defines? Hmm, li a0,16 defines a0 (hard reg, no pseudo). Hmm. But sched1's boost may be on the CALL's arg setup: the call group.

Hmm, but how does rgb's def count affect the li's priority? Unless: sched1 boosts "birthing" insns — insns that define a pseudo whose ONLY def is this one, and the pseudo is used soon. In mine, rgb's pseudo has 1 def → the def is boosted → and boosted defs... would go earlier. But it's later!

Ugh, contradiction. Unless the boost in sched1 is: "schedule the birth of a pseudo LATE" — no.

Let me get the actual gcc source. Maybe the machine has gcc source? Let's check: `find / -name "sched1.c"` — unlikely. But maybe the project has notes about sched1. The project's cookbook may have a sched1 note! Let me grep the cookbook index for sched1.

That's a good idea: cookbook/INDEX.md grep "sched1".

Also, the moves.md has many sched1 notes. Let me grep cookbook for "sched1" and "birth".
