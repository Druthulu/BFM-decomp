---
ts: 2026-10-21T23:56:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CzCM05EcMAzsgOG0POS3
---
Excellent! The comment in the source explains everything:

"RC-12 ($0-ADD OPAQUE COPY): the target keeps the packed read live in $a3 while a second, opaque copy lives in $a2 ... A plain C copy is dissolved by cse/canon; `x = y + zr` with zr pinned to $0 emits the byte-identical `addu rD,rS,$zero` that neither cse nor combine can remove."

So the project KNOWS this is a lever ("RC-12"). The task is to find a real-C way to produce an opaque copy.

Also: "The 8-byte frame is a phantom: the target reserves vars= 8 but never touches the stack. An unused 8-byte local reproduces it" — so `u32 dead[2]` gives the 8-byte frame. But in my c1, the frame was -16! So the dead[2] plus something else. Hmm, maybe because in c1 gcc kept h in memory? No, h was in a0.

Hmm, mine had frame -16. Maybe because `dead[2]` (8 bytes) + `h` spilled? Hmm. Or maybe because in c1 `now` was in a2 and... 

Actually, let me reconsider: with the pin, orig gets frame -8. Without, c1 gets -16. The extra 8 bytes might be a spill slot for something.

OK so the key question remains: how to make an opaque copy in real C?

Ideas for an "opaque copy" that cse/combine can't remove:
1. A copy through a different mode: e.g. `h = (s16)arg0` — but that changes the value.
2. A copy through a union/memory — no.
3. A copy where the source is a *volatile* read — no (barrier).
4. `h = arg0 + zr` where zr is a variable gcc can't fold.

Hmm, what about #4 with a variable that's a *function parameter*? E.g., if the function had an extra parameter that is 0 at runtime... but the signature can't change.

Hmm, what about a static/global variable that is 0? `extern s32 D_800xxxx;` — loading it costs an instruction.

Hmm, what about `h = arg0 + (0 & something)`?

What about arithmetic that gcc can't fold but which is free? Like `h = arg0 + (arg1 - arg1)`? That computes arg1-arg1 = 0 (gcc would fold to 0? `arg1 - arg1` → combine can't fold that (it's not a constant), it would generate a subu instruction → extra insn ✗).

Hmm.

IDEA: What if the copy is produced by the *type* of the source: e.g. `now` is `u32` and `r` is `u32`, but the copy is `r = (s32)now` — no-op.

IDEA: `r = now` where `now` is `u32` and `r` is `s32`?? Both SI.

Hmm, hold on! What about the **mode**: if `now` were `u32` and `r` were `u16`, the assignment would truncate → extra insn.

What about making the copy go through a `long`? On MIPS32, long = 32 bits.

Hmm, what about `unsigned long long`? 64-bit → different.

OK, think about "neither cse nor combine can remove". What operations survive combine?
- A copy of a value that's not a simple register copy.

Hmm, what about the "s16 copy escapes cse" trick from moves.md — an HImode copy. Let's think: 
```c
s32 h;
{
    s16 t = (s16)arg0;   /* HImode copy of arg0 */
    h = t;               /* sign-extend */
}
```
This gives: `sll t0,a0,16; sra t0,t0,16` → 2 insns instead of 1. ✗ (target has `move t0,a0`).

Hmm, but what if the SIGN extension is free because gcc folds it into the subsequent use? The target's uses of h: `(u32)h & 0xFF` and `h - v1`. Hmm.

Hmm, actually wait: what if `h` itself is declared `s16` and the source's uses are compatible? Let's check the target's uses of t0:
- `andi v0,t0,0xff` — low byte ✓ (same for s16 h)
- `subu v0,t0,v1` — h - v1 where v1 = (r&0xFFFF)>>8 (0..0xFF). If h were s16, the subtraction would use the sign-extended 16-bit h. And `h` values: arg0 (or arg0+1) — the caller passes (s16)r & 0xF per the earlier call site... Actually in the ov_MAIN_012 caller: `func_800D0D7C((s16)r, (*(s16 *)&D_8011512E) & 0xF)`. So arg0 is small (0..15). So s16 vs s32 doesn't matter at runtime, but the CODE would differ: if h were s16, the assignment `h = arg0` would need a truncation `andi t0,a0,0xffff` — the target has a plain `move t0,a0` ✗.

So h is s32.

Hmm OK. So we need an opaque 32-bit copy.

NEW IDEA: what if the copy is made opaque by being a copy of a value that is *also* stored/loaded? No.

NEW IDEA: What about `h = arg0;` where `arg0` is a *parameter* and gcc's copy propagation from the parameter is blocked by the parameter being used elsewhere? Hmm! In gcc, the incoming parameter pseudo (arg0) is copied into a0 at entry (for a non-leaf) — actually for MIPS, the first 4 args come in a0-a3 directly, so the "pseudo" for arg0 IS a0 initially. If arg0 is modified (assigned), gcc creates a new pseudo.

In the target: a0 (arg0) is live until `addiu t0,a0,1` (in the else branch) and `andi v0,t0,0xff`. And t0 = h.

In mine: `h = arg0` coalesced h with a0; `h = arg0+1` → `addiu a0,a0,1`.

So the target has arg0 preserved in a0 and h in t0. The difference is the extra copy.

Hmm, what if the source is:
```c
h = arg0;
```
but with `arg0` ALSO used later — it is (in `h = arg0 + 1`).

Hmm, gcc's cse: `h = arg0` (copy) — cse's `propagate_copy` substitutes arg0 into h's uses, but h is RE-ASSIGNED in the else branch, so the propagation only applies to uses dominated by the copy and before the re-assignment. In the else branch, h is re-assigned, so the propagation doesn't apply there. In the then-branch (fall-through path), h's value = arg0 → propagated to arg0.

So in mine: the first if's condition uses r (not h); the else branch sets h = arg0+1; the second if uses h. Since the else branch re-assigns h, the second if's use of h differs by path. gcc handles this with a phi-like merge: h = phi(arg0, arg0+1) → gcc would create a merge pseudo. Hmm, and mine produced `addiu a0,a0,1` in the else and then `andi v0,a0,0xff` — so h got a0 (merged with arg0's reg).

Hmm OK, whatever the details: the target has an extra copy.

Let me think about the "opaque copy" from a different angle: what if the copy is `h = arg0` but the SOURCE is a *volatile-free* but *non-constant* expression... 

AH WAIT!!! IDEA: What about `h = arg0 + 0` where 0 is not a constant but comes from a **static const array**? no.

IDEA: What if the copy is made opaque by the compiler not knowing the value: `h = arg0 | 0x0` → folded.

IDEA: **What if the two values are of different types where one is `unsigned` and the other `signed` and the copy requires a "convert"?** gcc 2.7 doesn't have type-based conversion insns for int.

IDEA: **What if the copy is `h = arg0` where h is a `volatile`?** → barrier lever, not allowed.

IDEA: **What if the copy comes from a function call?** no.

IDEA: **What if the copy is a struct assignment?** `struct {s32 v;} tmp; tmp.v = arg0; h = tmp.v;` → memory traffic ✗.

IDEA: **What if `h` is an ARRAY element?** memory ✗.

Hmm. Let me reconsider — maybe the answer is that the copy CAN be produced by cse-resistant means: **a copy whose source is a hard register**. Like `h = arg0` where arg0 has been forced into a hard reg by... a call? Hmm.

Hmm, what about this: the source could be written so that gcc's cse doesn't propagate because the copy is a "hard reg copy" — e.g. if `arg0` were used as a call argument, gcc would copy it to a0 (a hard reg) — but there are no calls here.

Hmm.

OK, alternative approach for this item: **PARTIAL**. The brief allows PARTIAL:<kinds still kept> = win.c scores 0 keeping only those levers. Here kinds = pin. So PARTIAL:pin would mean the win.c still has the pin and scores 0 — that's what orig.c already is. That's not progress (the pin is the row's kind). Hmm: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". If kinds=pin and we keep the pin, PARTIAL:pin is just the status quo — not useful.

So for this item I need a full MATCH (no pin).

Hmm. Let me think about "opaque copy" more.

!!!! IDEA !!!!: What about `h = arg0` where **arg0 is declared `s32` but the copy is forced by the source using `arg0` in a context that makes gcc treat it as a different value**... 

Hmm, what about this classic: **`h = arg0;` where `h` is later compared with `>=` — gcc's "nonzero_bits" analysis**... no.

NEW ANGLE: What if the opaque copy is created by the *comparison* itself? The target's `andi v0,a2,0xff` — the comment says "combine cannot see through the opaque copy to fold the low byte back to the D_80078EB0 lbu". So without the opaque copy, gcc would fold `r & 0xFF` to just `D_80078EB0` (the low byte of the packed read)! Because `r = now = D_80078EB0 | (D_80078EB1<<8)`, so `r & 0xFF == D_80078EB0`.

So the opaque copy serves TWO purposes: keeps `now` and `r` distinct, and blocks combine from folding `r & 0xFF`.

So ANY opaque copy works. We need one that survives cse AND combine.

What survives combine? Let's think about gcc 2.7's combine: it folds `(set (reg) (plus (reg) (const_int 0)))` → the reg. `(set (reg) (and (reg) (const_int -1)))` → the reg. `(set (reg) (ior (reg) (const_int 0)))` → the reg. `(set (reg) (mult (reg) (const_int 1)))` → the reg.

What about `(set (reg) (plus (reg) (const_int 0)))` where the reg is in a different MODE? e.g. `h = (s16)arg0` gives `(set (reg:SI) (sign_extend (reg:HI) (reg:SI arg0)))` — combine folds sign_extend of a reg into the reg? There's a combine rule: `(sign_extend (reg:HI) (reg:SI x))` → hmm, sign extension of a 32-bit reg to 32 bits is a no-op → combine folds it → copy. But the HImode truncation first: `(truncate (reg:HI) (reg:SI x))` → combine might fold to `and x, 0xffff` → that's an AND → not folded away (it's a real op) → generates `andi t0,a0,0xffff` ✗ (target has `move`).

Hmm.

What about a copy in a *wider* mode: `h = (long long)arg0`? → 64-bit → different ✗.

OK, what survives BOTH cse and combine and generates exactly `addu rd,rs,$zero`?

The `addu rd,rs,$zero` encoding is gcc's "move" — emitted for a plain register copy in SI mode. So the RTL must be `(set (reg:SI d) (reg:SI s))` — a pure copy. And combine won't fold a pure copy (it's already minimal). The question is only whether CSE propagates it away.

So the question is: **how to prevent gcc's cse from propagating a copy**.

gcc's cse propagates a copy when the source reg is not modified between the copy and the use. In our case: `h = arg0` at the top; h's uses: in the second if's condition `(u32)h & 0xFF` — but h is REASSIGNED in the else branch (`h = arg0+1`). So at that use, h's value is a merge of arg0 (then-path) and arg0+1 (else-path).

Hmm, so gcc would create a phi. In the target, the merge is avoided by having h in t0: `move t0,a0` in the then-path and `addiu t0,a0,1` in the else-path. So h's phi is realized as t0 in both paths — no merge insn needed since both paths write t0.

So the target's h is a pseudo with 2 sets (t0 = arg0 in the then-path; t0 = arg0+1 in the else path) and the phi is resolved by the register.

In mine, gcc chose to use a0 for h in the then-path (h coalesced with arg0) and a0 for h in the else path (`addiu a0,a0,1`). But that destroys arg0 in the else path — which is fine because arg0 isn't needed after.

So gcc's choice is driven by the copy propagation: `h = arg0` propagated → h's then-path value = arg0 = a0 → so h lives in a0 → and the else path's `h = arg0+1` also computes into a0.

To break this, the copy `h = arg0` must not be propagated.

How about making the copy's SOURCE be modified in between? E.g., if `arg0` were modified between `h = arg0` and h's use — but arg0 isn't modified.

Hmm! Unless... we make `h = arg0` into `h = arg0` where the value is used in a way that requires the copy... 

**IDEA**: What if `h` is assigned arg0 and arg0 is ALSO assigned somewhere? The source's `h = arg0 + 1` in the else branch. Hmm, what if the ORIGINAL source was:

```c
h = arg0 + zr;     /* h = arg0, opaque */
...
h = arg0 + 1;
```
That's the current source.

**IDEA**: What if the original source used a helper: `h = (arg0 + 0)` where 0 is... 

**IDEA**: What if `zr` was a MACRO expanding to something opaque, e.g. `#define zr (0*1)`? folded.

Hmm, hmm. What about **`zr` being a `static const` in another TU**? gcc 2.7: `extern const s32 zr;` → gcc would load it (const globals aren't folded in gcc 2.7 without LTO) → extra insn ✗.

OK, let me think about **cse's propagation rule** more precisely. gcc 2.7's cse.c has `propagate_copy`? Hmm. Actually, I recall gcc 2.7's cse.c does the copy propagation in `find_duplicate_insn`:
```c
	  /* If this insn is a copy of a reg, note it in the equiv table */
```
and `cse.c` has `equiv` handling where a register's value can be replaced by another. Hmm.

But here's the thing: the equiv table is invalidated when the source reg is modified. `arg0` (a0) is not modified until `h = arg0+1` in the else branch — but that's a different basic block.

In gcc 2.7's cse, the equiv propagation happens within a basic block scan but the table persists across blocks (the "life" of the equiv). Hmm.

OK. Let me just TRY things empirically! Let me write a batch of variants for func_800D0D7C and see which gets closer:

v1: `r = now; h = arg0;` (done, 17)
v2: `r = now + 0; h = arg0 + 0;` — probably same as v1.
v3: `r = now; h = arg0;` with `now` declared `u32` and `r` declared `s32`? (type difference)
v4: `r = now; h = arg0;` but with `h` used as `((u32)h & 0xFF)` — same.
v5: swap roles: make `now` the copy and `r` the original:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;      /* r in a2 */
```
Hmm.

v6: What if we make `r` a different variable that is assigned the OR expression and `now` the copy?
```c
r = D_80078EB0 | (D_80078EB1 << 8);   /* r = a3 */
now = r;                                /* now = a2?? */
```
Hmm, then the roles of &0xFF vs &0xFF00 swap. But we could rename the uses! I.e., write the code so that the variable that holds the OR value in a3 is the one used with &0xFF00 and the copy is used with &0xFF.

So: in the source, `now` is used with &0xFF00 and `r` with &0xFF. If instead I write:
```c
u32 r = D_80078EB0 | (D_80078EB1 << 8);   /* r in a3 */
u32 now = r;                                /* now in a2 (copy) */
```
then `now` (a2) is used with &0xFF00 — but the target uses a3 with &0xFF00. ✗ reversed.

Hmm. Unless the copy direction is what matters: `r = now` where now is the ORIGINAL (a3) and r is the copy (a2). The copy's destination is r. So we need r to be a copy of now, with now kept in a3.

The problem is cse dissolving the copy. What if `now` is MODIFIED after the copy? Then cse can't propagate. But `now` isn't modified...

WAIT!!! What if the source uses `now` in a way that modifies it? Like... hmm.

**KEY IDEA**: What if the copy is made opaque by making the SOURCE a value that gcc recomputes? E.g., what if `now` is assigned in BOTH branches? No.

**KEY IDEA 2**: What if the copy is `r = now` where `now` is a **volatile-qualified**... no.

**KEY IDEA 3**: What if we introduce the copy through a **union or a bit-field**? A bit-field assignment would generate masking ✗.

**KEY IDEA 4**: What if `r` and `now` are the SAME variable but with different lifetimes such that gcc... no.

**KEY IDEA 5**: What if the copy is preserved because `r` is **address-taken**? That would force r to memory ✗.

**KEY IDEA 6**: What if `now` is used in a **call argument**? No calls here.

**KEY IDEA 7**: What if the copy is `r = now` and `now` is later REASSIGNED in a branch that gcc keeps? Look at the source: `now` is never reassigned. But the ORIGINAL might have been! Hmm, but the target shows a3 = now unchanged.

**KEY IDEA 8**: gcc's cse equiv propagation is blocked if the source reg is used as a **call argument** (because the call could modify it). No calls.

**KEY IDEA 9**: **The `h` case**: `h = arg0` — arg0 is the incoming parameter pseudo. In gcc, the incoming parameter is a pseudo that's copied to a0. Actually for MIPS with -mips1, the first 4 args are in a0-a3 and gcc creates a pseudo for arg0 with a copy `move pseudo, a0`... Actually gcc's prologue does `move $4,$2` style? Hmm, in the target, is there a copy of a0 into a pseudo? The target's first insns are the lbu/lui sequence; arg0 (a0) is used directly (`move t0,a0`). So gcc kept arg0 in a0.

Hmm OK.

**KEY IDEA 10**: What if the copy is made opaque by using a **different but equal-valued expression involving a non-constant**? Like `r = now + (arg1 & 0)`? That computes arg1&0 → gcc folds `and arg1, 0` → 0 → folded ✗.

**KEY IDEA 11**: What if we use `r = now - 0`? folded.

**KEY IDEA 12**: What if the copy is `r = now` and we ALSO write `now` somewhere? no.

**KEY IDEA 13**: What if we give `now` a second definition? E.g.:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
now = now;  
```
no.

**KEY IDEA 14**: THE BIG ONE — what if the opaque copy comes from **the value being read from memory twice**? E.g. `now` is read from two globals; the target's `or a3,v1,v0` computes the packed value. Then `r = now` is a copy. Since `now`'s value is a computed expression, cse... no, cse propagates.

Hmm, hmm. Let me look at the problem from the "what did the ORIGINAL PSX source look like" angle. The original PSX source (the game) had this function. It probably was:

```c
s32 func_800D0D7C(s32 arg0, s32 arg1) {
    u32 now = D_80078EB0 | (D_80078EB1 << 8);
    u32 r = now;
    s32 h = arg0;
    ...
}
```
Hmm, but then the compiler (the original Sony compiler, not gcc) produced the opaque copy. The original compiler wasn't gcc! The TARGET is from the original game's compiler (SCEI's psx compiler / gcc 2.7-ish? Actually the target object is the ORIGINAL GAME's object, compiled with the original toolchain).

Hmm, but the whole project decompiles to gcc 2.7.2 output, and the target is the original binary's code. The original was compiled with a different compiler, so exact instruction matching is a "coincidence" goal — the project aims to match the original's code with gcc 2.7.2.

So the original source had something that made its compiler emit an opaque copy. Common PSX idiom: `x = y + zr` where zr... hmm.

OR the original might have had the values as separate variables that the compiler kept in separate registers for other reasons.

Hmm, since the original compiler is not gcc, "opaque copy" might just be its register allocation.

OK. So for us: we need gcc 2.7.2 to emit an opaque copy. The project's own comment says `x = y + zr` with zr pinned to $0 does it. And they call it a LEVER (RC-12) — meaning the project considers this a residual lever that must be removed. Our task: remove it with real C.

Hmm, since the comment says "A plain C copy is dissolved by cse/canon", maybe there's a real-C spelling that survives.

Let me think about what survives gcc 2.7.2's cse:
- cse propagates a copy `(set d s)` into uses of d, IF s is not modified in between AND the copy is not "hard reg".
- **If the source s is a HARD REG (not a pseudo), cse still propagates** (it just copies the hard reg).

Hmm.

- **What if the copy's destination is a hard reg?** e.g. via a call arg.

Hmm, what if the destination `r` is passed to a function... no calls.

WAIT!!! What about **`r` being used in a comparison where gcc's `nonzero_bits` analysis kicks in**? The moves.md entry: "$0 zr pin: s16 flag2/3/4 copies (HImode copy escapes cse, combine nonzero_bits -> move)". Hmm, that says an HImode copy escapes cse.

Hmm, so maybe an HImode copy survives cse but generates extra instructions.

Hmm, hold on, let me reconsider: maybe for THIS function the trick is different. Let's reconsider what's needed:
1. `or a3,v1,v0` — the packed value in a3.
2. `move a2,a3` — a copy in a2, used for `r & 0xFF` and the comparisons.
3. `move t0,a0` — a copy of arg0 in t0.

For (3): `h = arg0` where h is later `arg0+1`. The target keeps arg0 in a0 and h in t0. What if the source is:
```c
h = arg0;
...
h = arg0 + 1;
```
gcc coalesces. What if instead:
```c
h = arg0;
```
and then in the else branch `h = h + 1;` → then h's else value = h+1 where h = arg0 → `addiu t0,t0,1`? But the target is `addiu t0,a0,1` (from a0!). Hmm, `addiu t0,a0,1` — a0 + 1. If h were t0 and h = a0's value, `h+1` would be `addiu t0,t0,1` — different word ✗.

So the target computes arg0+1 from a0 directly, meaning arg0 is preserved in a0 and h is a separate t0. So `h = arg0 + 1` (reading the ORIGINAL arg0, not h).

Hmm OK, so in the target:
- a0 = arg0 (preserved)
- t0 = h = arg0 (copy) [then-path]
- t0 = h = arg0+1 (else path)

Both `move t0,a0` and `addiu t0,a0,1`. So h is a pseudo with 2 sets, and the first set is a copy from a0.

For gcc to emit `move t0,a0` rather than coalescing h with a0, the copy must be opaque.

**BREAKTHROUGH IDEA**: What if `arg0` is used as a CALL argument or the function is not a leaf... no.

**BREAKTHROUGH IDEA 2**: What if the copy is `h = arg0` where `arg0` is a **parameter of type s32** and gcc's "argument copy" pseudo is what gets copied... Hmm, in the target, is there an extra copy of arg0 into a pseudo? The target's `move t0,a0` copies from a0 (the hard reg). So arg0's pseudo IS a0 (no prologue copy).

**BREAKTHROUGH IDEA 3**: What if we make h's first assignment `h = arg0` and ALSO use `h` in a way where the copy must be preserved...

Hmm, hold on! What about **the order of the branches**? The target's structure:
```
cc4: bnez v0, ce0        (if (r&0xFF) >= (arg1&0xFF) → else path)
cc8: move t0,a0          (then path: h = arg0)
ccc: subu v0,a2,a1
...
ce0: (else path) ... addiu t0,a0,1
```
So `move t0,a0` is in the THEN path (the >= case), and `addiu t0,a0,1` in the ELSE path.

The then path doesn't modify h at all! h is only set in the else path (`h = arg0 + 1`). And in the then path, h = arg0 (set before the branch).

So `h = arg0` is executed BEFORE the branch (at the top), and the copy `move t0,a0` is placed in the then path by the scheduler (it could have been hoisted to the top; it's cheap and the scheduler sank it? Actually the scheduler wouldn't sink it... hmm, it's in the then path because the else path re-sets h).

Hmm, interesting: so `h = arg0` at the top, but gcc placed the copy in the then path? That suggests the copy is NOT at the top in the original, but rather:
- then path: h = arg0
- else path: h = arg0 + 1

i.e., the source might be:
```c
if (cond) {
    h = arg0;
    r = ...;
} else {
    h = arg0 + 1;
    r = ...;
}
```
Hmm! But then the copy would be in the then path and `addiu t0,a0,1` in the else path. YES! That matches the target's placement exactly!

Hmm, but the current source has `h = arg0 + zr;` at the top (before the if). With the pin, the copy `move t0,a0` is opaque and the scheduler could place it anywhere — it placed it in the then path (since the else path overwrites t0). Hmm, actually with `h = arg0+zr` at the top, gcc's flow: h = arg0 (top) then h = arg0+1 (else). The scheduler sank the first copy into the then path (dead in the else path). That's plausible: the scheduler sinks it since it's not needed on the else path... Actually no, sched wouldn't sink an insn. Hmm, but the "reorg" pass or the "jump" pass might.

Hmm, alternatively the original source had:
```c
if (...) {
    h = arg0;
    ...
} else {
    h = arg0 + 1;
    ...
}
```
This is a natural way to write it! And the current source's version (h = arg0+zr at top) is the project's reconstruction.

With that source: in the then path, `h = arg0` → copy t0 = a0 (if opaque) or coalesced (h = a0). Hmm, the coalescing question remains.

Hmm! But here's the thing: if `h = arg0` is INSIDE the then branch and `h = arg0+1` inside the else branch, then h's two values are in DIFFERENT blocks. gcc's local-alloc might then assign h to a register... and the copy `h = arg0` would be a plain copy → cse propagates → h = a0. Hmm, same issue.

Unless the propagation is blocked because arg0 is modified in the else path? No, arg0 isn't modified.

Hmm, hold on, but in the ELSE path: `h = arg0 + 1` → `addiu t0,a0,1`. If h were coalesced with a0, we'd get `addiu a0,a0,1` and then the second if would use a0. But the target uses t0 in both paths and keeps a0 intact for the `addiu t0,a0,1`.

Why does the target keep a0 intact? Because `addiu t0,a0,1` needs arg0 AFTER the copy `move t0,a0`. If h were coalesced with a0, the else path would destroy a0 — which is fine since a0 isn't needed later. gcc chose to coalesce (in my c1). The target didn't.

So the target's h is a distinct register from a0. The ONLY difference is the opacity of the copy.

So: we need `h = arg0` to be an opaque copy. In the target, the copy is `addu t0,a0,$0` — a plain register copy in the final code, but opaque at the RTL level.

Hmm! So the RTL was NOT a plain copy — it was e.g. `(set t0 (plus a0 zr))` where zr is $0. After combine, `plus a0, $0` — would combine fold that? The comment says NO ("neither cse nor combine can remove").

So we need an RTL-level operation that (a) survives combine, (b) generates `addu rd,rs,$zero`.

What RTL operations generate `addu rd,rs,$zero`? Only the "move" pattern = a plain SI copy. So the RTL after combine IS a plain copy. The question is whether cse propagates it.

⇒ cse must be prevented from propagating a plain copy. 

**How does gcc 2.7's cse decide to propagate?** In cse.c, `find_duplicate_insn` handles `(set (reg) (reg))` by recording in the equiv table: `record_equiv`? Hmm, actually gcc 2.7's cse.c has:

```c
	  /* If this is a copy, record it.  */
	  if (GET_CODE (src) == REG && GET_CODE (dst) == REG) {
	      ...
	      equiv_regs (dst, src, ...)
	  }
```
and `equiv_regs` sets up the equivalence so later uses of dst get src.

The propagation is blocked if:
- src is modified before the use (cse invalidates the equiv when src is set).
- The copy crosses a basic block boundary? gcc's equiv table is per-function with "life" tracking... In gcc 2.7, `equiv_regs` records `equiv_insn` and the equiv is valid only within the "life range" — the table is reset at certain points (e.g., when a call is made, or when the reg is set).

**KEY**: gcc 2.7's cse invalidates equivalences when a CALL occurs (because the callee may modify memory, but regs aren't clobbered... hmm, calls clobber caller-saved regs). Hmm! But if `arg0` were live across a call, it'd be in a callee-saved reg.

**KEY 2**: What if the copy is in one block and the use is in ANOTHER block, and gcc's equiv propagation doesn't cross blocks? Then the copy survives! In gcc 2.7's cse.c, the equiv table is reset at the start of each basic block? Hmm, no — cse.c does handle cross-block copies via the "life" mechanism.

Hmm, but the current source's structure (h = arg0 at the top, use in the second if) — the copy is at the top block and the use is in a later block.

Hmm, what if I put `h = arg0` INSIDE the then-branch and the use is in the second if? Still cross-block.

OK, let me just try a bunch of variants empirically. Variants:

A) Move `h = arg0` into the then-branch, `h = arg0 + 1` in the else:
```c
if (cond) {
    h = arg0;
    r = ...;
} else {
    h = arg0 + 1;
    r = ...;
}
```
B) Same for r/now:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
```
Hmm, r is assigned in both branches later, so `r = now` at the top is the only def. Hmm.

C) For the r/now copy: what if `now` is read TWICE from the globals? No, the target computes the OR once into a3.

Hmm, for (a): `now` (a3) is used at cd4 (`andi v1,a3,0xff00`) and cf0. And `r` (a2) is used for `r & 0xFF`, `r - arg1`, etc.

What if the source is:
```c
now = D_80078EB0 | (D_80078EB1 << 8);
r = now;
```
and gcc propagates now into r → r and now are the same → a3 used for both → no `move a2,a3` ✗.

What if instead:
```c
r = D_80078EB0 | (D_80078EB1 << 8);   /* r = a3 */
now = r;                               /* now = a2 (copy) */
```
Then `now` (a2) is used with &0xFF00 — but the target uses a3 for &0xFF00. ✗ — BUT hold on! Maybe I can swap the ROLES in the source: use `r` for the &0xFF00 terms and `now` for the &0xFF terms. I.e., rename the variables in the source so that the one in a3 is used with &0xFF00 and the copy in a2 is used with &0xFF.

With `r = OR; now = r;`: r is in a3 (the original), now is the copy in a2. The source uses `now & 0xFF00` and `r & 0xFF`. So in the target, the &0xFF00 term must read a3 = the ORIGINAL = r. But the source's `now` (the copy) is used with &0xFF00 → it would read a2 ✗.

Unless I rewrite the source to use `r` for the &0xFF00 terms and `now` for the &0xFF terms! I.e., swap the roles:
```c
r = D_80078EB0 | (D_80078EB1 << 8);   /* r = a3 (original) */
now = r;                                /* now = a2 (copy) */
if ((now & 0xFF) >= ((u32)arg1 & 0xFF)) {
    now = ((now - arg1) & 0xFF) | (r & 0xFF00);
} else {
    now = ((0x3C - (arg1 - now)) & 0xFF) | (r & 0xFF00);
    h = arg0 + 1;
}
...
```
Hmm, but wait: then `now` is the copy in a2 and `r` in a3. The target: a2 used with &0xFF ✓ (now), a3 used with &0xFF00 ✓ (r). 

But hold on — this is just a renaming! The real question is whether the copy survives. With `now = r` (a plain copy), cse propagates → now = r → same reg → no copy ✗.

ARGH. Same problem.

OK so the crux: **make a plain copy survive cse**.

Let me think about gcc 2.7's cse more concretely. The relevant code (cse.c, gcc 2.7):

```c
	  /* If this is a copy (set (reg) (reg)), then ... */
	  if (GET_CODE (src) == REG && GET_CODE (dst) == REG && ...)
	    {
	      ...
	      /* Record the equivalence */
	      ...
	    }
```
Hmm, and there's `equiv_regs` in cse.c? Actually, gcc 2.7's cse.c has:

```c
/* Record that X and Y are equivalent... */
static void
equiv_regs (reg1, reg2, insn)
```
Hmm. And it does propagate: in `cse_insn`, when looking up a reg in the hash table, if the reg has an equiv, it uses the equiv reg.

The equiv is invalidated when the reg is SET (in `update_src_eq_notes` / when processing a set).

So `h = arg0`: h's equiv = arg0. Then any use of h before arg0 is set → replaced by arg0.

In our function, arg0 is never set → the equiv stays valid → h is always replaced by arg0. Hence h = arg0 in the target too... unless the equiv is broken.

**When is the equiv broken?** In gcc 2.7's cse.c, `equiv_regs` is only valid within the "life" of the reg: the equiv table entry has a `life` field... Hmm. Actually there's this in cse.c:

```c
/* Return true if we should ignore this insn... */
```

Hmm, and importantly:
```c
	  /* If we have a copy, and the source is live... */
```

I recall gcc 2.7's cse has a concept: `equiv_reg` entries are invalidated at the end of a basic block? Let me test empirically!

TEST: put `h = arg0` in the then-branch and see if the copy survives (if equivs don't cross blocks).

Similarly for `r = now`: put it... hmm, r = now must be before the first use (the condition). Hmm.

Hmm, but actually! Here's a thought: in the target, `move a2,a3` is placed BEFORE the branch (at cb4, before `andi v0,a2,0xff`)... let me re-check the target order:
```
cb0: or a3,v1,v0
cb4: move a2,a3
cb8: andi v0,a2,0xff
cbc: andi v1,a1,0xff
cc0: sltu v0,v0,v1
cc4: bnez v0,ce0
```
So `move a2,a3` is at the top, before the branch ✓. And `move t0,a0` is at cc8 (in the then path, after the branch).

So: `r = now` is at the top (same block as the comparison) — cross-block propagation to the branch's use... The use `r & 0xFF` is in the same block (before the branch). So the copy is used in the same block → cse would propagate it (r = now → r's use becomes now → `andi v0,a3,0xff`).

Hmm, but the target has `andi v0,a2,0xff`. So the copy ISN'T propagated even within the same block.

⇒ The RTL at that point was NOT a plain copy (it was `plus now, zr` with zr=$0 → combine turned it into... hmm, but then the final instruction is `addu a2,a3,$0` = a plain copy).

Hmm! So combine turned `plus(now, $0)` into `a copy` but cse didn't propagate it. But if combine turns it into a copy BEFORE cse... hmm, order: cse runs, then combine? gcc 2.7's pass order: combine → cse → cse2 → ... Actually in gcc 2.7: `combine` runs, then `cse`, then `cse2`, then `jump`, etc. Hmm, but combine also runs after cse? In gcc 2.7's final.c: 
```
  /* Perform the first CSE pass. */
  ...
  cse (max_reg, max_reg_num);
  ...
  /* Perform the second CSE pass. */
  cse2 (max_reg, max_reg_num);
```
and combine is called from within various passes.

So if `plus(now, zr)` with zr = hard reg $0: combine (in the first combine pass) might convert `plus(reg, $0)` → the reg (if it knows $0 is zero) or keep it. gcc 2.7's combine has a rule: `(plus (reg) (const_int 0))` → the reg. But `$0` is a REG, not a const. Does gcc's combine know that reg 0 is zero? In gcc 2.7 for MIPS, the hard reg 0 is not special in the RTL (it's just a register). So `plus(now, reg0)` stays. Then at RTL expansion, `addu a2,a3,$0`.

And cse sees `(set a2 (plus a3 reg0))` — not a copy → doesn't propagate ✓.

So the target's `addu a2,a3,$0` came from `plus(now, $0)` — a genuine ADD with a $0 addend, and gcc emitted `addu rd,rs,$zero`.

BUT the objdump output says "move a2,a3" — because objdump prints `addu rd,rs,$zero` as "move". Hmm, does it? For MIPS, GNU objdump prints "move" for `or $rd,$rs,$zero` (funct 0x25) and ALSO for `addu $rd,$rs,$zero`? The word 0x00e03021 has funct 0x21 = addu. If objdump printed "move" for addu-with-zero, fine.

So the target genuinely has `addu a2,a3,$0` — an add with a zero addend. NOT a plain copy!

⇒ We need real C that produces `plus(reg, $0)` — an addition whose addend is a register that gcc believes is zero but doesn't fold.

In real C: `x = y + z` where z is a variable whose value is 0 but gcc can't prove it. That requires loading z ✗.

Hmm, BUT: what if z is a **constant 0 that gcc keeps as a register**? gcc's combine folds `plus(reg, const 0)`.

Hmm, what if the addend is `$0` because of a **`(s16)0` cast**? no.

Hmm, what about `x = y + 0` where y is `unsigned` and the addition is done in a different mode... no.

Hmm, what about `x = y - 0`? combine folds.

What about `x = y + 0L` where long is 32-bit? Same.

Hmm. What about the possibility that gcc's combine does NOT fold `plus(reg, const_int 0)` when the reg is in a specific mode (e.g. SI) but the const is in a different mode? gcc 2.7's combine rule for plus with 0:
```c
	    /* X + 0 -> X  */
	    if (GET_CODE (new_op0) == CONST_INT && ... INTPTR... )
```
Hmm, gcc 2.7's combine has:
```c
	  /* Handle + and - with zero specially.  */
	  if (GET_CODE (new_op0) == CONST_INT && INTPTR_TYPE_SIZE...)
```
I'm fairly sure `x + 0` IS folded by gcc 2.7.

Hmm, so how did the ORIGINAL source produce `plus(reg, $0)`?

Maybe the original source had `zr` as a **macro for a variable that is a global register variable**? Or maybe the original source had:

```c
static s32 zr;   /* always 0 */
```
Then `now + zr` → gcc loads zr → `lw` ✗.

Hmm, what if zr is a **static const s32 zr = 0;**? gcc 2.7 would treat it as a constant → folded.

Hmm, what if zr is a **local variable set to 0 by a volatile read**? no.

What about: the original source used `x = y + 0` and the ORIGINAL compiler (SCEI's, based on gcc 2.x but with different folding) kept it! The target is from the ORIGINAL compiler, so the original source may well have had `x = y + 0` and the original compiler emitted `addu rd,rs,$zero` while gcc 2.7.2 folds it away.

Hmm! So the real question: is there a spelling that gcc 2.7.2 keeps?

In gcc 2.7.2, combine's rule (combine.c):
```c
	    /* X + 0 -> X  */
	    if (GET_CODE (new_op0) == CONST_INT
		&& INTPTR_TYPE_SIZE (GET_MODE (new_op0)) == word_size
		&& ...)
```
Hmm, but there's a condition: the addition is only simplified if the constant is 0 AND the machine doesn't have a cheaper way. I believe gcc 2.7 DOES simplify `x + 0` → x.

BUT WAIT: maybe it doesn't when x is a register and the result is used in a way... Hmm.

Hmm, let me test empirically! Let me try `r = now + 0;` and `h = arg0 + 0;` and see the score. Maybe gcc 2.7.2 does NOT fold it! Cheap to test.

Let me also try `+ 0L`, `+ (s32)0`, `| 0`, `& -1`, `^ 0`.

Let me write these variants and score them.

Also for the frame size issue (mine -16 vs target -8): the `dead[2]` array should give 8 bytes. Mine gave 16. Hmm, maybe because in mine `h` needed a stack slot? Or because `dead[2]` (8 bytes) + alignment → 16? In the target, frame -8 = dead[2]. In mine, -16 = dead[2] + 8 (something spilled). Hmm, or gcc aligned the array to 8 bytes → frame 16? Hmm, dead[2] is u32[2] = 8 bytes, aligned 4 → frame 8. So mine has an extra 8 bytes.

Maybe in mine, `h` was spilled to the stack? Or `now`/`r`? Hmm, in mine the frame is set up with `addiu sp,sp,-16` appearing at insn 9 — odd placement. Whatever; maybe the extra 8 bytes is a spill slot for the merge pseudo.

Let's test variants and see.

Let me write variants:
d1: `r = now + 0; h = arg0 + 0;`
d2: `r = now | 0; h = arg0 | 0;`
d3: `r = now & -1; h = arg0 & -1;`
d4: h = arg0 moved into the then-branch; r = now at top
d5: `r = now + 0;` with h in branches
d6: `r = now;` + `h = arg0;` but with `now` declared as `u32` and `r` as `s32`... hmm r is u32 in the source.

Let me do d1, d2, d3 first.
