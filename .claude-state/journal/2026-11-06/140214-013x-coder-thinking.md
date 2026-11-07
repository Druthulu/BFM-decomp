---
ts: 2026-11-06T21:02:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ewDBamJeACJnrVL5Ag9n
---
Without keepalive, `andi` result goes directly to s0 (the pin $4 a was apparently optimized: `a` pinned to $4 but then `ang = a` and since `a` isn't used later, it coalesced... wait target wants andi a0, then move s0,a0. Mine has andi s0 directly. That's local-alloc/copy-prop merging a→ang.

Actually the pin `register s32 a __asm__("$4")` — with the keepalive asm using `a`, `a` must stay in $4 through the asm. Then `ang = a` copies. Without the asm, cse/flow sees a and ang as same value and coalesces into s0 directly? Hmm.

Target: andi a0 (a in $4), then move s0,a0 (ang = a). So we need `a` to live in a0 ($4) at the andi, and `ang` in s0 separately, with a real copy.

The pin forces `a` to $4. But apparently without keepalive, gcc still merges ang into a (copy propagation) and assigns the merged pseudo s0 (because ang used later across the beq and s0 is callee-saved). So andi writes s0 directly.

So the keepalive asm's role: it's a use of `a` after `d = ...`, forcing `a` to be considered live and preventing the copy-prop/coalescing of ang with a? Actually `__asm__ volatile("" : : "r"(a))` makes `a` used at that point, but `ang = a` also uses a. Hmm. Copy propagation would merge them anyway.

Wait, the asm is a barrier for copy-prop? An asm with "r"(a) operand constrains a to a register but not a specific one. Hmm.

Actually maybe the asm prevents the `d` load from being scheduled before? Let me think about ordering. In target, order: andi a0 (a), then lbu v1 (d load), li v0, beq. In mine (w1): andi s0, then lbu, etc. So the andi happens before d load in both. The difference is only the reg (s0 vs a0) and the move.

The keepalive asm probably forces `a` to be live until that point, and since `a` is pinned to $4, it's in a0. `ang` is a separate pseudo s0. Then the move.

Without asm: copy propagation in cse/flow merges ang and a into one pseudo; the merged is used across the beq (live through), so local-alloc/global assigns it s0, and the andi writes s0. No move.

So to keep two pseudos with a real copy, we need the copy `ang = a` to not be coalesced. Real C levers: make `ang`'s value differ? No. Or make `a` used somewhere else so it can't be merged? But no levers allowed.

Alternative: use a different variable arrangement. E.g., don't have a separate `a`; instead compute directly into ang and... but target needs andi a0 then move s0,a0, i.e., the andi result is in $4 then copied to s0. So `a` must be $4. The pin gives that. We need the copy to survive.

Maybe: `ang = a;` is copy-prop'd because a's only remaining use is this copy. If `a` had another use after, it couldn't merge. But `a` is used only here.

What about making the value flow through a function-like barrier? No levers.

Hmm — but maybe the trick: since `ang` is read later in `res = (ang + ...)`, and `a` isn't used later, the compiler coalesces. The pin `$4` should prevent coalescing to a different hard reg though: a is fixed to $4; ang could be allocated anywhere. Copy propagation replaced ang's uses with a? That would make ang's uses read a ($4), but a is pinned $4 and the value is live across the beq and the call — $4 is call-clobbered, so it can't stay in $4 across `jal`. So copy-prop cannot keep it in a; instead it merges the pseudo and lets it be s0. Right: cse's copy merging with a hard-reg... Actually the pin is a hard reg only in local-alloc; global-alloc may treat the $4 pin as a preference/constraint.

The keepalive asm forces `a` to be in a register at that point (right after the d load, before ang=a). It's a use, so copy-prop's single-use condition? Copy propagation in gcc 2.7.2 cse: it replaces a register with its equivalent if... Actually flow/cse. The asm makes `a` have two uses? No, asm is one use, ang=a is another → a has 2 uses, so cse doesn't merge? Hmm, cse merging (make_regs_eqv) works on copies: `ang = a` makes ang equivalent to a; then it replaces subsequent uses of ang with a... no wait, it replaces uses of a with ang or vice versa based on which is "canonical". If a has more uses/longer life, ang is replaced by a? Then ang's uses would read a. But a is $4 hard-pinned.

Hmm, target has `move s0,a0` then uses s0 later. So the copy exists in the target. Meaning the original C (with keepalive) produced that. The asm keeps `a` as an asm operand which may make it non-copy-propagatable (asm operands are opaque). That's why removing it merges.

So we need another way to stop the merge without asm. Real-C ideas:
- Use `a` again later in a real expression, forcing it to stay distinct. E.g., compute something with `a` that's dead? That would be a launder (identity statement) — not allowed. But a real use that the target also has? Target uses `s0` in `addu v0,s0,v0` at the end. That's ang. Only one use.
- Change decl order/scope.
- Use s16/u8 widths.
- Use a temp: `s32 t = ...; a = t & 0xFFF;`?

Alternatively, maybe the copy merges because `a` and `ang` are both s32 and ang = a. If instead we write `ang = a` where a is declared with a different type or the copy happens through a cast, maybe it survives. E.g., `ang = (s32)a;` — probably same.

Hmm, but wait: the pin `register s32 a __asm__("$4")` is a "register asm" local. In GCC 2.7.2, `register ... asm("$4")` makes that variable's rtl be a hard register (a pseudo is not created; uses become reg $4 directly). Then `ang = a` is `(set (reg ang) (reg $4))` — a copy from hard reg. cse may try to merge. The asm keeps it.

If we keep the pin, we need the copy to survive. Options: make `ang`'s copy not the only... 

Idea: assign ang later. Currently order: a computed; d loaded; [asm]; ang=a; if... So `ang = a` occurs before the branches. What if we move `ang = a;` into the `final:` block (just before use)? Then ang is set later; the copy `ang = a` would be at final. But a ($4) is clobbered by the `call` path's jalr and by ratan2 in final. So a must be copied to a callee-saved reg before any call. Target copies to s0 right after andi (before beq). So ang must be set early.

Hmm, the copy target is s0 (callee-saved) because ang must survive the ratan2 call at 3550. So we need ang live in s0.

Real C: use `ang` directly as the destination of the computation but force the andi into $4 first via the pin on a temp? That's the same.

What if `a` is used in the condition? No, target doesn't.

Maybe: the merge is a cse copy-merge (wall cse-copy-merge). But the worked example for similar items (W03 func_8018E428 "launder gone via in-place pv chain; pv pin dropped too") shows there are cracks.

Let me look at what pass merges. Let me generate cc1 dump for the w1 body. Use tools/cc1_dumps_tu.sh? The brief says tools/cc1_dumps_tu.sh + tools/alloc_table.py. But simpler: maybe delever_search has dump options. Let me check delever_search.py --help.

Actually, let me first try quick variants. Time budget 20-30 min per item. Let me try a batch.

Variants for item 1:
1. Remove keepalive, add `ang` initialized at decl and assign a to ang later differently.
2. Declare `ang` before `a`.
3. Use `s16` for ang? No.
4. Write `ang = a & 0xFFF;` and a = ratan2... without &0xFFF? But then andi applies to ang, target andi a0.
5. Introduce an intermediate: `s32 b = ratan2(...) - 0x400; a = b & 0xFFF;` then ang = a. Probably same merge.
6. Make `a`'s value used twice: e.g., `ang = a;` and also `d = ...` no.

Wait — maybe the merge is because ang is only assigned once and used; if we make ang's assignment happen after a conditional... 

Actually, think about what the keepalive asm really does at RTL: `(asm_operands/v ("") ("") 0[ (reg $4)])`. It's an insn using $4. So $4 has a use at that point, before `ang=a`. That doesn't stop the copy merge per se, but it makes $4 live there. The copy `ang=$4` then... Hmm, maybe cse doesn't merge copies involving hard registers? Let me test: what if we keep the pin but replace the asm with a real read of `a` that the target doesn't show? That would be a launder if identity. But we could do something where the result is genuinely used.

Alternatively: maybe we don't need `a` at all. What if the pin is on `ang`? `register s32 ang __asm__("$4")`? Then andi would write a0=ang, but then ang needs to survive the call → copy to s0 would be needed but compiler wouldn't create it (ang pinned to $4, can't). Hmm, actually a pinned register across a call is broken; gcc may spill.

Wait, is the pin really needed for item 1? kinds=keepalive only. But maybe we can drop the pin too and get the same via a real C arrangement? The target wants andi a0 then move s0,a0. Without a pin, can plain C produce andi a0, move s0,a0? The andi result is the value of `a`; it's later used as s0. If we compute `a` and copy to `ang`, the copy might be coalesced. To prevent, maybe use `ang` in a way... 

Hold on: target order: andi a0,v0,0xfff ; then lbu v1 (d) ; li v0,0x53 ; beq v1,v0 ; delay move s0,a0. So the copy is in the branch delay slot. That's scheduling. The copy exists because $4 holds a and ang is a distinct pseudo in s0.

For plain C without pin, we'd need two distinct pseudos where one is forced to a0. The andi writes a0 because... ratan2 returns v0; andi a0 = v0&0xFFF means the andi's destination got $4. That's local-alloc choice, perhaps because `a` was pinned. Without pin, andi dest could be s0 directly.

So the pin likely is load-bearing for the andi→a0. Good: keep the pin.

Then the only problem is the copy merge. What real-C move keeps `ang = a` a copy? 

GCC 2.7.2 cse: copies are merged via `make_regs_eqv`. It merges if the source and dest are both pseudos/hard regs, with conditions. Let me read cse.c around make_regs_eqv (cse.c:840 per walls). Let me look.

Actually the wall "cse-copy-merge | cse | cse make_regs_eqv (cse.c:840): iVar1 outlives t -> canonical; cmp/store of t rewritten to iVar1 (s-reg); target keeps t in v0". So cse merges and keeps the longer-lived one. Here `a` ($4) vs `ang`: ang outlives a (a dies after the copy; ang lives across branches and calls). cse would make ang canonical and rewrite... but a is $4 fixed. Hmm, if ang is canonical, uses of a get rewritten to ang: the copy `ang = a` then becomes `ang = ang` (dead). But the andi writes a ($4). Then `ang = a` dead → andi's result never used?! No — cse wouldn't rewrite the *definition* of a (the andi), only uses. The andi defines $4; the copy defines ang. If ang canonical, the copy's source use of a is rewritten to ang, making `ang = ang` which cse deletes, and then the andi's $4 is dead → but the andi still exists writing $4 (unused). That's not what we see. We see andi writes s0 = ang directly, no move. So maybe it's local-alloc/copy-prop that merged the pseudos: register allocation coalesced `a` (pinned $4)... no, pinned can't coalesce.

Hmm, actually with `register asm("$4")`, in GCC 2.7.2 the variable is a hard register from the start (not a pseudo). Then `ang = $4` is a copy. `-fno-...`? Copy propagation (flow/combine?) could replace ang's later uses with $4 only if $4 is not clobbered. $4 is clobbered by calls (ratan2 at 3550, jalr at 3504). So it can't. So the copy should survive...

But we observed andi s0 directly. So the pinned `a` didn't stay hard? Maybe with the asm removed, `register s32 a __asm__("$4")` plus single assignment gets... Hmm, actually maybe GCC's `local-alloc` for a hard-reg variable: the "register asm" declaration makes it a hard reg only if used as an operand? Let me check: In GCC 2.7.2, `register int a asm("$4")` — "The asm keyword on a register variable specifies a register". It creates a hard-register rtx for uses, but assignments... I believe it's a genuine hard reg.

Wait, but the diff shows andi s0. If `a` were hard $4, andi would write $4. Unless the andi was combined with the copy: the andi's result is copied to ang, and cse/combine folded the copy into the andi destination (change destination from $4 to ang) because $4 dead. That's exactly what the "replace" shows: mine andi s0. So combine/cse retargeted the andi to ang's reg. That's a copy-propagation into the definition.

So to stop it, we need the andi's destination $4 to be used elsewhere or the copy not foldable.

Idea: Use `a` in the final expression instead of ang? No, a is clobbered.

Idea: assign ang from a inside a block where a's use is opaque... no.

Idea: make `ang` an `s16`? The target stores ang in s0 as full reg. ang = a where a is 0..0xFFF fits s16. But later `res = (ang + ratan2(...)) & 0xFFF` — ang as s16 would be sign-extended? If ang is s16, the copy would be `andi`/`sll/sra`? Probably changes code.

Idea: Use a union/struct? No levers.

Hmm. What about declaring `a` and `ang` such that `ang` is used BEFORE a dies in a way that... 

Alternative real-C: don't use a copy. Have the andi write $4 and then ang read from $4 in a context that can't be folded: e.g., `if (d == 0x53) { ang = a; goto final; }`? No, ang needed in all paths... Actually in the target, ang is used only at `final:` (3558). The copy at 34ac is unconditional. If we set ang only in the final block from a, a is dead by then (clobbered). No.

What if we restructure: compute `a`, then `ang = a;` where ang is declared as a pointer or something? no.

Let's look at how other items in moves.md cracked keepalive. E.g., `keepalive | func_80184D28 | MATCH — keepalive replaced by return v0`. Not applicable. `func_801810F8 MATCH: obase set right after pbase...` no.

Maybe the answer is: the keepalive asm here isn't just keeping a; it forces `a` to be materialized into $4 *before* the d load (the asm acts as a scheduling barrier, forcing andi before lbu). Without it, maybe scheduling moves things. But the diff only shows reg differences, so ordering is same.

Let me try: keep the pin, remove asm, and add a second real use of `a` that the target also has? Target uses a? Only $4 at andi, then move s0,a0. So no second use.

What if we change the source of `ang`: `ang = a;` → make it not a plain copy but e.g. `ang = a + 0;`? That's an identity launder (add 0) — not allowed as a crack? "identity-statement launders do NOT count as a crack". Adding 0 would be folded anyway.

What about using `a` to compute the condition? `d = (s32)D_80126C01;` target lbu. If we did `if ((d = ...) ...)` no.

Hmm, let me reconsider: maybe we can drop the pin and get andi→a0 by a different real-C route. But target wants $4. Plain C could get $4 if... The andi result is the return of ratan2 & 0xFFF, then it's copied to a callee-saved. local-alloc might put andi in a0 if a0 is free and the copy to s0 happens. Actually maybe not.

Let me try a bunch of variants and score them. I'll write a batch of candidate files and use sc.sh.

Variants (keeping pin, no asm):
- v1: `ang = a;` moved right after the andi (same as now effectively).
- v2: declare `ang` as `volatile s32 ang;`? That adds a store/load — no.
- v3: make ang initialized at decl: `s32 ang = 0; ... ang = a;` no change.
- v4: use `ang = a;` but make `a` used again: e.g., `d = (s32)D_80126C01; if (d == (a & 0)) ...` — launder.
- v5: reverse: compute into ang then copy to a? Target andi a0 then move s0,a0: so the andi dest is a0 and copy to s0. If C: `ang = ratan2(...) - 0x400; a = ang & 0xFFF;` → andi a0? no, would be andi to ang's reg.

Hmm, what about making the copy happen through the branch structure: 
```
if (d == 0x53) { ang = a; goto final; }
```
That would produce a copy only on that path; target has it in the delay slot unconditionally. Probably wrong.

Let me look at the exact keepalive semantic: `__asm__ __volatile__("" : : "r"(a));` with "r" forces a into a register (it's already hard $4). The asm is volatile, so it's a scheduling barrier and cannot be deleted. It makes `a` used. Crucially, since `a` is $4 and the asm uses it, `a` is live until the asm. Then `ang = a`. Copy propagation might see that `a` is dead after the copy and fold the andi into ang — but the asm use means a is NOT dead at the andi; a is used by the asm. Still dead after.

Why does the asm prevent folding? Because `a` is used by the asm, so the andi's destination $4 is needed for the asm; the andi cannot be retargeted to ang. Right! The andi defines $4; $4 is used by the asm; so andi must write $4. Then `ang = a` is a separate copy. Without the asm, $4's only use is the copy, so combine folds andi into ang's reg.

So we need $4's value used by something real between the andi and the copy... but the target shows nothing between except the lbu d and beq. The asm emits zero bytes but counts as a use.

So: is there any real C use of `a` that emits no code? An asm is the only way... unless the use is the copy itself and we prevent folding differently.

Alternative: prevent combine from folding by making `ang`'s reg not a simple destination — e.g., if ang is assigned via a conditional. Or make the copy `ang = a` where ang is a different type causing a conversion (emits a real insn, but target has `move` which is the copy — a move is a copy anyway).

Actually the target's `move s0,a0` IS the copy. So the copy is expected. The problem is only that combine folds andi's dest into s0 and then the copy disappears. If we can make the copy "not a simple reg-reg set" that combine won't merge... but a move is exactly reg-reg.

What if ang is used before the copy? no.

What if we introduce a second variable so the andi's result is used twice? E.g.:
```
a = ... & 0xFFF;
ang = a;
```
That's what we have.

Consider: `d` is loaded between. What if `a` is used in computing d? No.

Hmm, let me look at other similar cases in moves.md with keepalive cracks. Search "keepalive" lines:
- func_80184D28 MATCH — keepalive replaced by return v0
- func_801810F8 MATCH — keepalive... 
- func_8017E804 PARTIAL:keepalive
- func_80188F14 PARTIAL:keepalive
- func_8017BF14 WALL lreg-tie-dying-pin

Let me grep moves.md for all "MATCH" with keepalive in kinds. Actually the grep earlier covered lines starting with barrier/keepalive/pin/launder. Let me grep more broadly for "keepalive" anywhere.

Actually the format is `kind | func | ...`. Let me grep '^keepalive' and '^.*keepalive'.

The earlier output had:
- keepalive | func_80184D28 | MATCH — keepalive replaced by return v0
- keepalive | func_801810F8 | MATCH: obase set right after pbase...
- keepalive,pin | func_80184FB0 | PARTIAL:keepalive,pin expand-void-return
- barrier,keepalive | func_80189214 | PARTIAL
- barrier,keepalive | func_80188F14 | PARTIAL
- barrier,keepalive | func_8017E804 | PARTIAL
- keepalive,pin | func_800D2A24 | WALL expand-void-return
- keepalive | func_8017BF14 | WALL lreg-tie-dying-pin

Not directly helpful.

Let me try to think about a real-C construct that makes `a` have another use. What if `a` is reused as the loop/condition variable? No.

What if the copy is done through a function? No.

What if we compute `ang` from `a` using a cast that generates the move but blocks combine: `ang = (s32)a;` — same.

What if we declare `a` as `s32 a` (no register asm) and instead pin via... no, pin needed.

Hmm, wait. Maybe the answer is different: maybe we can remove the pin too and use a completely different real-C structure that yields andi a0 + move s0,a0. How does one get andi a0 without a pin? If the value `a` is passed as an argument later? No.

Let me look at the actual delever_search mechanism — maybe it has a "try" mode with multiple candidates and reports. Let me read tools/delever_search.py --help and maybe its scoring details.

Also, maybe there's a much simpler solution: keep `a` used by a real computation that the target also has but I misread. Look at target again: at 3558 `addu v0,s0,v0` uses s0=ang. And andi a0 at 3498. The `move s0,a0` at 34ac. So yes.

What if the C is:
```
ang = (a = (ratan2(...) - 0x400) & 0xFFF);
```
Same.

What if `a` is used as the ratan2 argument later? No.

OK here's an idea: use `a` in the `final` block *in place of* ang, but ensure the value is preserved by re-reading... no.

Another idea: Make the copy `ang = a` appear BEFORE the andi? Not possible.

Another idea: instead of `a` being $4-pinned, pin `ang`? Then andi writes ang ($4) and then... but ang must survive the call; pinned $4 can't. GCC might copy to s0 anyway. Let's test: `register s32 ang __asm__("$4");` and no `a`. Actually then the andi result in $4, used across branches; the call at 3550 clobbers $4 so gcc must copy to s0 before the call. Where would it copy? Possibly at the same place (34ac)? Might. Let's try.

Actually more precisely, the pin on ang forces the value to be in $4 through all uses. At the call it must be saved to a callee-saved. GCC's local-alloc for a hard reg that's call-clobbered across a call... It would insert a save/restore. Might produce move s0,$4 before and move back. Not matching.

Let me just experiment. Write several candidate bodies and score. Let me also check delever_search's dump ability to understand which pass merges.

Let me read the tool help.
