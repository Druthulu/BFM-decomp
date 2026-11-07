---
ts: 2026-11-06T09:57:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_388a73ntJZrhENbuUg9a
---
Interesting: `return rv;` in void function → 11 ins, target 26. So gcc deleted all the rv stores and the return did nothing (void return drops the value). So that doesn't work.

Wait 11 ins means it dropped most. So `return rv;` in void function → expand_null_return, value dropped. Confirmed wall expand-void-return.

Hmm. So lever-free can't keep rv in v0 through a void return.

But wait — maybe the target's v0 sets can be produced by a *real use*: e.g., the last statement calls a function whose result... no.

Alternative: Make the value live through a store? The target doesn't store it.

What if the function returns via `return func_8002D4C8(...)`? No.

Let's think about what C construct puts a value in v0 as the last thing before `jr ra` in a void function. A void function can still have a value in v0 from a call (e.g., the last statement is a call whose return value stays in v0). But target's v0 = rv (computed value), not a call.

Another idea: use `asm`-free "return" via function pointer? No.

Wait, maybe I misread: the function's declared type. `void func_80182420(a0, a1)` — is that a definition with return type void, yes.

Could we use a nested function or a `static` helper? No, that changes the TU.

Hmm. What about a computed goto / label address? No.

The wall "expand-void-return" is exactly this. Many prior items hit it. But the task expects attempts and a WALL if impossible. But hold on — maybe there IS a lever-free route: the target returns the value because the real function is s32. The brief says "no signature or decl change outside the body". So we cannot change void→s32. So likely WALL.

But wait, maybe we can put the computation into a *use* that gcc must keep and that also happens to leave it in v0. For example, at the end: `if (rv == 0) {}`? No, dead.

Hmm, what if the function's last statement is a `switch` on rv with no cases? Dead.

Let me reconsider the target's register allocation. Maybe the target's v0 is not the return value but a normal allocated register that happens to be v0 because v0 is caller-saved and unused? In gcc, v0 is not generally allocatable (it's a call-clobbered reg but local-alloc can use it? Actually $2 is used for return values but is a general reg; local-alloc/global-alloc can allocate it). Wait, the target's function never calls anything (it's pure computation + return). So $2 could be allocated as a normal register! In gcc 2.7.2, the return-value register $2 is `RETURN_REG` but also in the allocatable set? Hmm, typically $2 and $3 are allocatable caller-saved registers in MIPS gcc. But the return value gets forced there.

Look at the target: v1 holds x, a0/a1 args, v0 is the result. In a void function with dead rv, the value is deleted. But if rv is live at exit for some real reason, local-alloc might allocate it to v0 naturally! The keepalive asm kept rv live; but maybe a *real C use* after the label keeps it live and local-alloc picks v0.

But any real use would add instructions. Unless the use is the return itself... which is void.

What if we return the value through a `return` in a function whose return type we don't change but we use a trick: `return (void)rv;`? No.

Hmm wait — is the TU compiled with the function definition `void`? The scorer replaces the body in the TU text. The TU line is `void func_80182420(a0, a1)`. The body we provide is the whole definition including `void func_80182420(a0, a1)`. The brief says "write a lever-free body of func ... (bare definition)". And "no signature or decl change outside the body". The body includes the definition line? The `--body` option replaces the function definition (from `void func_80182420` to closing brace). The signature is part of the body file... Hmm, "no signature or decl change outside the body" means don't touch callers/extern decls; the definition signature in the body file might be allowed to change? The worked example win.c: `void func_80181F4C(s32 arg0, s32 arg1) {` — same signature. 

Let me re-read: "CONSTRAINTS: ... no signature or decl change outside the body (callers stay as they are)". "outside the body" modifies both "signature" and "decl"? I read it as: no signature change, no decl change outside the body. I.e., don't change the signature or other declarations. So we cannot make it return s32.

Hmm, but actually changing `void` to `s32` on the definition WOULD change the signature and conflict with the TU's callers (which declare it void). Actually in the TU, callers declare `extern void func_80182420(...)` and then call via casts. If the definition is `s32 func_80182420(...)`, the TU would have a conflicting declaration: `extern void func_80182420(s32,s32);` then definition s32 → error "conflicting types". So not possible.

Wait, actually the def line is `void func_80182420(a0, a1)`. The preceding decl in the TU: is there an `extern void func_80182420(...)` before the definition? Let me check around line 3252. Let me look at the lines just before 3252 and the def. There's `extern s32 D_801E1BCC[];` at 3250. The callers later each have their own extern void. So the definition is the first declaration; making it s32 might be OK if no earlier decl... but callers declare void → conflicting. Also "no signature change" forbids.

OK so likely WALL expand-void-return for the clones. But the brief gives 20-30 min per item and expects a wall only after ≥30 scored tries. Hmm, that's a lot. But maybe there's a known move.

Wait, actually let me reconsider. Maybe the value can be kept live without asm by a *conditional* real use that gcc folds to nothing but keeps liveness? No — "identity-statement launders do NOT count as a crack". But the requirement is the body scores 0 and kinds gone. A dead-reset cse-breaker (C0414) is a lever? "no new lever of any kind". Hmm.

Let me look at what the orig actually needs: the pin $2 forces rv into v0, and the keepalive keeps rv live. Could a real C use keep rv live with zero extra instructions? E.g., at `done:`, `if (rv) ;`? That adds a test instruction. No.

What about using rv as the value of a `return` in a *different* function via... no.

Hmm, let me look at the target more carefully. Actually maybe the target function does return the value and the "void" declaration in the TU is simply wrong; but the build compiles the TU with `void`, and yet the target object was built from the real game. The scorer compares against the baseline object built from the fleet run. The baseline object's func_80182420 has 26 ins with v0 return. But the TU declares void... The project's src currently matches with pin+keepalive. So the project accepts the pin.

The task explicitly asks to find a lever-free body. If it's impossible, WALL is acceptable but needs ≥30 tries. Hmm, but maybe there's a clever route.

Idea: In a void function, the value can be forced into v0 by making the last statement a *call through a function pointer* that takes rv? No.

Idea: `return` in a void function is dropped, but what about `return (s32)rv;` — same.

Idea: The value can be left in v0 if rv is used as the argument to a call placed in the delay slot? The target has no call.

Idea: Use `__builtin_return`? No.

Idea: A `switch` where rv is the discriminant: `switch (rv) { }` — gcc must evaluate rv, might load it into a register for the jump table or compare; with no cases, dead.

Idea: Use rv in a loop condition after done: `while (rv) break;` — adds a branch. Target has none.

Hmm. What about the function epilogue: gcc sets v0 for the return only if the function returns a value. Void → no.

So genuinely, the only way is a lever. Therefore the clones are WALL expand-void-return? But wait — the brief's list says kinds keepalive,pin. The prior shards hit exactly `keepalive,pin | func_800D2A24 | WALL expand-void-return`, `func_800CD494 WALL expand-void-return`, `func_800CD5CC WALL expand-void-return`, `func_801F0C4C WALL expand-void-return`, `func_80183E68 WALL lreg-copy-pref-dying-base`. So these clones are very likely the same wall. But wait — those walls were reached with 30-180 tries. The brief allows WALL with best score. But maybe there's a PARTIAL: keep win.c scoring 0 while keeping only the pin (drop the keepalive). "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". So if we can drop the keepalive but keep the pin and still score 0, that's PARTIAL:pin! That's a valuable outcome. Let's test: pin only (no keepalive asm). The pin `register s32 rv __asm__("$2")` makes rv live? A register asm var without a use — the stores to a hard reg: `rv = -1` stores to $2. Are those stores dead? Since rv is a register variable bound to $2, and the function is void, the stores are dead... but register variables are often not deleted? Actually the keepalive was needed. Let's test.

Test variant: pin only.

Also variant: keepalive only (rv plain + asm keepalive) — keeps rv live but not in $2; local-alloc might give it v0 naturally? Let's test both.

Let me create b2 (pin only) and b3 (keepalive only) for func_80182420.
