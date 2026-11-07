---
ts: 2026-11-06T10:39:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lkX4fvsP7YrC05F6dBIa
---
The struct is complete. Now the C uses `*(s32 *)((s32)s0 + 0x20)` instead of `s0->unk20` — a deliberate spelling? It reads unk20 (a s32). And `((Unkstruct_800B5CB8 *)*(s32 *)((s32)s0 + 0x20))->unk18 = 0x4000;` etc.

Note: using `(Unkstruct*)(s0->unk20)` vs `*(s32*)((s32)s0+0x20)` may matter for aliasing/RTX.

Now the double copy mystery. Let me try a variant using a typed local pointer:

```
void func_8018966C(void *a0)
{
    Unkstruct_800B5CB8 *s0;
    s32 v0;
    ...
    s0 = (Unkstruct_800B5CB8 *)a0;
    v0 = ((s32(*)(void))func_8012C1B8)();
    s0->unk20 = v0;
    if (v0 == 0) { func_8012CAE4(s0); }
    else { ... s0->unk2 = 1; ... }
}
```
and replace `*(s32*)((s32)s0+0x20)` with `s0->unk20`.

Hmm, but that changes the expression tree, which could change codegen. The target's code for `((Unkstruct*)*(s32*)((s32)s0+0x20))->unk18` loads unk20 (lw v0,32(s0)) then stores to 24(v0). Same as s0->unk20. Field-direct might be cleaner. But careful: the pointer at 0x20 is s32; using it as a struct pointer requires a cast anyway.

Let me first test whether a typed local removes the double copy. Quick test with a few variants.

Actually, hold on. Let me reconsider: maybe the double copy is NOT about types at all but about the *order of the assignment relative to the call*. In target, `move s0,a0` is in the delay slot of the call. In mine, `move s1,a0` before, `move s0,s1` after. Two copies arise if the local pseudo is allocated differently in different blocks — which happens when the pseudo is NOT live across... hmm.

New idea: the second copy might be for the *if-branch join*: the value s1 is used in the entry block and in the if branch; s0 is used in the else branch and after. That smells like *local-alloc* allocating the pseudo twice for different blocks? No, a global pseudo has one reg.

Unless the pseudo is not global because it's only live in one block... no.

Wait, maybe gcc's global-alloc assigned the parameter a0 to $s1 (a callee-saved reg!) because a0 is live across the call? Is a0 live across the call? In the C, `s0 = a0` happens BEFORE the call. But if the compiler doesn't copy eagerly and instead keeps a0 live across the call (because the assignment is a copy that can be deferred), then a0's live range spans the call → must be callee-saved → s1. Then after the call, the copy `move s0,s1` materializes the C assignment. That's exactly it! gcc defers the copy: it treats `s0 = a0` as a copy that can be moved later, so a0 is live across the call and allocated to s1, then copied to s0 where the local is first used.

But in the target, `s0` is a hard register $16, so the copy must be emitted as `move s0,a0` — the hard-reg assignment forces it. reorg then puts it in the delay slot.

So the double copy is a *copy-deferral* artifact. To fix lever-free, we need the copy to happen before the call in the same pseudo. How? Make the copy non-deferrable: e.g., assign the local a type that forces materialization? Or use the local in a way that requires it live... hmm.

Alternative: don't copy at all — make the local the parameter itself? We can't change the signature (declaration), but inside the body, we could avoid the local and use a *different* construct: the compiler needs the pointer saved across calls regardless. If we simply use `a0` directly in all uses (and a0 is a parameter that's clobbered), gcc will save a0 to a callee-saved reg *at the point of first use after the call*, which is the same deferral.

Hmm, but what does the target's `move s0,a0` in the delay slot mean? The copy is placed after the call (in the delay slot = executed before the call takes effect, but the instruction is after the jal). Semantically it's fine because a0 isn't clobbered by the call until the call executes... wait, delay slot executes before the call body. So `jal; move s0,a0` is a copy of a0 before the call clobbers it. So the target's copy is *deferred* into the delay slot too! It just happens to be in the delay slot because reorg moved it there.

So the difference is: target has ONE copy (`move s0,a0`) — the parameter a0 (hard reg) is copied directly to $s0 (hard reg local). Mine has TWO copies because the local is a pseudo: a0→s1 (parameter pseudo assigned s1) then s1→s0 (local pseudo assigned s0).

Why does the parameter get s1? Because the parameter's live range extends across the call (deferred copy), so global-alloc gives it a callee-saved reg s1. And the local gets s0. Then the copy between them.

In the target, a0 is a hard register (not allocatable) — the parameter's incoming reg is $4, and it's live across the call (deferred), so... hmm, gcc cannot keep a0 live across a call; it must copy. Actually the deferred copy semantics: the *source* is the hard reg a0; if the copy is deferred past the call, the source value would be destroyed. But the delay slot placement means it's before the call. So in the target, the copy is NOT deferred; it's just placed in the delay slot by reorg, which is fine because the delay slot is before the call executes.

OK whatever the mechanism, the practical question: how to get a single copy without a pin? 

Option: make the copy un-deferrable by using the local in a way that cse/flow can't move the copy. E.g., initialize at declaration `void *s0 = a0;` — same.

Option: use an intermediate that's a *different* kind: e.g., store a0 into a struct field? No.

Option: force the parameter to be dead by clobbering? Hmm.

Option: change the order: do the copy *after* the call from a0? Invalid (a0 clobbered) — but the compiler doesn't know? It does.

Option: use `s32 s0 = (s32)a0;` — an integer copy; maybe the copy is not deferred because the types differ (pointer→int is not a simple reg copy?). Actually pointer→s32 is a bitcast, still a reg copy.

Option: use the parameter directly in the first uses and introduce the local later. E.g., write the body so that a0 is used before the call, and after the call use a saved copy declared with `s0 = a0;` placed *after* the call? Can't.

Hmm, what about this: the deferral happened because `s0 = a0` is a copy that gcc's combine/cse could sink. But if `s0` is used *before* the call, the copy must be before... it's not used before the call (only after). Wait — in the C, `s0 = a0;` then the call, then uses. So the copy could be deferred to the first use (after the call) but the source a0 is clobbered by the call → not allowed. gcc's flow/copy-prop shouldn't defer a copy whose source dies at a call... unless it does and compensates by giving the *source pseudo* a callee-saved reg (that's exactly the "copy deferral with allocation" strategy: keep a0's pseudo alive in a callee-saved reg across the call, then copy).

Right: gcc's global alloc doesn't emit copies; it keeps the value in one pseudo until the copy point, and assigns the *parameter's* pseudo a callee-saved reg because it's live across the call.

So the fix: force the copy to be materialized before the call. How? Make something else use the local before the call, or make the local's value matter... but the C semantics are fixed by the target.

Alternative fix: make the target shape emerge differently: if the parameter pseudo is live across the call and gets a callee-saved reg, and the local also needs a callee-saved reg, we get 2 regs + 2 copies. But if we can make the parameter's live range END at the copy, then it can stay in a0 and the copy is emitted at the top → one copy.

So: force the copy before the call. Ideas:
- Use the local in a conditional before the call? Changes codegen.
- Initialize the local via a function call? no.
- Use `volatile`? Would force stack.
- Use the local in an expression with a side effect? no.

Hmm, what about making the local a *different* variable that's used before the call? Not in the semantics.

What if we pass the pointer as an argument to the first call? `func_8012C1B8` takes void. No.

What about assigning `s0 = a0` and then using `s0` as the base of the store BEFORE the call... the store is after.

Hmm, wait. Let me reconsider the actual target: `jal func_8012C1B8; move s0,a0` — the copy is in the delay slot. If gcc's schedule had the copy before the jal, reorg could still move it into the delay slot. So the target's single copy is consistent with either.

Let's test the hypothesis that gcc defers the copy by checking the nobar/nopin diff again: mine `move s1,a0` is at the top (before jal), so the copy IS at the top, but to s1 not s0. Then `move s0,s1` after the jal. So there are two moves: the first is a *register-to-register* copy inserted by global-alloc because the parameter pseudo got s1 and the incoming value arrives in a0. The second is the C copy s1→s0.

So global-alloc assigned the *parameter* a callee-saved reg (s1) because it's live across the call, and the local to s0. The `move s1,a0` is the incoming-arg move. If the parameter's live range ended before the call, it would stay in a0 (or be assigned a caller-saved reg) and the C copy would be `move s0,a0` — one copy.

How to make the parameter's live range end at the copy? The copy is deferred by gcc; the parameter stays live until the copy. If the copy is not deferrable, the parameter dies at the copy point (which is before the call) → stays in a0.

gcc defers copies via copy propagation in flow/cse. A way to block it: make the copy "used" in a context where the source can't be substituted, e.g., different machine modes? Pointer vs s32 both SImode.

Hmm, alternatively: use `a0` for the first uses and only create the local later... 

What if we *don't* copy, and instead make the parameter itself survive: impossible in C.

OK here's another angle: accept two pseudos but make them *both* allocate to the same reg? If the parameter's pseudo and the local's pseudo were tied (coalesced), one move would vanish. gcc 2.7.2 has copy coalescing in local-alloc (within a block) and global-alloc "copy" handling. The copy `s0 = a0` is in the entry block, so local-alloc could tie them — but the parameter is a global allocno? Parameters are usually in the incoming regs; gcc 2.7.2 makes the parameter a pseudo with preference for its incoming hard reg. If the pseudo must be callee-saved (live across call), it can't tie with a0.

So the real issue is the parameter's live range extending across the call.

Test: what if the call `func_8012C1B8()` is placed AFTER the copy is *forced*? E.g., make the copy produce a value used in a `?:`? no.

Practical trick used in this project: "field post-decrement per arm", "u16 t (HImode copy escapes cse equiv)". The HImode trick! From moves: `pin | func_80184F18 | MATCH — u16 t (HImode copy escapes cse equiv)`. An HImode copy can't be propagated because the mode differs. Here the copy is a pointer (SImode). Could we make the copy through an HImode temporary? Not semantically (pointer).

Another trick: "launder". Not allowed.

What about declaring the local as `s32 s0` and doing `s0 = (s32)a0;` — pointer→s32 conversion. In gcc 2.7.2, pointer-to-integer conversion is a `convert`/SUBREG? Both SImode, so it's just a copy. But maybe the copy is then not recognized as a copy (different modes? no, same mode).

Hmm, but actually maybe it's not a copy-propagation deferral: gcc's `expand_expr` for `s0 = a0` with a0 a parameter in $4 and s0 a pseudo → emits a move; flow/copy-prop may propagate s0's value = a0 to uses. In the target with a hard-reg local, no propagation (hard reg).

Let me just test variants empirically — much faster than theorizing:
1. `void *s0 = a0;`
2. `s32 s0 = (s32)a0;`
3. typed pointer local + field access.
4. reorder: `s0 = a0;` moved to *after* the call? (invalid semantically but let's see the score; no — a0 clobbered, would break correctness; the scorer compares bytes only, but we must keep real C correctness... the task says real C moves only; a wrong-but-matching body would be cheating and the bank would catch. Avoid.)
5. Use the local for the first store and the parameter for... no.

Let me create a generator that emits variants from a template. I'll write them explicitly as files.

Actually, better idea: make the copy happen in a context that cse cannot propagate: `s0 = a0;` then `if (v0 == 0) func_8012CAE4(s0);` — uses in two branches.

Hmm, one classic: initialize the local at declaration *and* make it a `register` variable? Not allowed (`register` vars prohibited). The constraint says no `register` vars.

What about making the local `volatile`? no.

Let me look at what other cracked items did for the same "double copy" pattern. Search moves.md for "copy" and "s1".
