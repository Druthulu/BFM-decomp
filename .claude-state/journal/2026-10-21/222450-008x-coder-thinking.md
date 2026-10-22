---
ts: 2026-10-22T04:24:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_NYUXsSkcg6067nPiSmZx
---
Fast (1.7s per candidate). Good.

Current: score 6, 39 vs 40 ins. The target has `move v1,v0` (call result copied into $3/v1) and then tests on v1, and `move v0,zero` at ins 28 in the delay slot.

Mine: `beqz v0` — call result tested directly in $2/v0.

So target: after call, `move v1,v0` → the call result lives in $3 (v1), tests on v1, and the return value computed in $2 (v0). Also note target's `move v0,zero` at ins 28 is in the delay slot of `beqz v1,a500` — the mask==0 path returns 0.

Actually wait — target ins 27: `beqz v1,a500` with delay slot ins 28 `move v0,zero`. So when mask test fails, returns 0. Then ins 29 `lbu v0,30(sp)`, 31 `xori v0,v0,0x15`, 32 `j a500` with 33 `sltiu v0,zero,v0`.

So the target computes the boolean in $2 and returns it. Mine computes the boolean but in some reg and copies.

The key: the call result must be in $3 while the returned value is in $2. In lever-free C: `ret = func_...()` — gcc keeps the call result in $2 (v0) as the return value register, and then computes the final value elsewhere, copying at the end.

Hmm, but target: call result in $3, and the returned value in $2. That's opposite of normal gcc behavior... unless the RESULT_DECL is pinned. In the pinned version, result is pinned to $2, so gcc uses $3 for the call result.

Lever-free: how to make gcc put the call result in $3 and the return value in $2? One way: assign the call result to a variable that... hmm.

Idea: `ret = func_80133784(...)` — the call's return value is a "call-result pseudo" that hard-prefers v0. Actually gcc's call result always comes back in $2 and gcc typically treats it as the return reg. If you then do `int t = ret;` gcc may copy. Hmm, actually gcc's "prefers v0" for the call result — but then if the RESULT_DECL also prefers v0, one of them wins and the other gets $3. Currently the call-result wins $2 (it's born earlier, live longer) and the RESULT_DECL gets $3.

To flip: make the RESULT_DECL have higher priority. Priority in gcc's global.c: `pri` computed via `allocno_priority` = refs*10 + 100*uses... Actually in global.c, priority for a pseudo = (REGISTER_NUMBER? ) Let me recall: `allocno_priority()` in global.c computes `pri = 0; ... if (REG_P (reg)) pri += ...`. Actually:

```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  if (reg == REGISTER_NUMBER... )
```
Hmm. There's `REG_FREQ_PRIORITY`? The notes mention "pri 10000" and "refs 3, live 3". This looks like the modern gcc (global.c allocno_priority) which computes:
```
pri = (REG_FREQ_PRIORITY (regno) * REG_FREQ_MAX) ...
```
Actually modern GCC 12+ global.c:
```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  gcc_assert (reg == REGISTER_NUMBER...);
  ...
  if (reg)
    {
      /* registers are expensive */
      ...
    }
```
Hmm, the exact numbers don't matter much. What matters: notes say "call-result pseudo (refs 4, live 7 -> pri 11428)" and "RESULT_DECL (refs 3, live 4 -> pri 7500)". And elsewhere "pri 10000" for others. This is the priority function in the .alloc file. In GCC's global.c there is:

```
#define REG_PRIORITY(REGNO) ...
  pri = (REG_FREQ_PRIORITY (regno) * REG_FREQ_MAX) / 100 ... 
```
Actually there IS `REG_FREQ_PRIORITY` — but that's for hard regs. For allocnos, there's `allocno_priority`:
```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  /* The value of a pseudo that is live across a call ... */
  ...
  if (reg)
    pri = (REG_FREQ_PRIORITY (regno) * ...);
```
Hmm, actually gcc's global.c (since GCC 12 rewrite) has:

```
/* Return the priority of allocation node N.  */
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  ...
```
Not sure. But there's also `pseudo_priority`? Whatever.

Key insight from the notes: pri values like 11428, 7500, 10000. In GCC's global.c:

```
#define PRIO_...
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  /* Compute a priority based on the number of references and the length of the live range */
```
Actually I recall:
```
  pri = (REG_FREQ_PRIORITY (regno) * REG_FREQ_MAX) / 100;
```
and REG_FREQ_PRIORITY is frequency-based, computed from the "Register frequencies" in the .alloc dump.

Hmm, but pri 10000 for a pseudo... In gcc's global.c there's:

```
  /* Priority of a pseudo is the number of references times ... */
  pri = 10000 + ...
```
Actually yes! I remember in modern GCC global.c:
```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  gcc_assert (reg == REGISTER_NUMBER ... );
  ...
}
```
Let me not guess; the notes say "refs 3, live 4 -> pri 7500" and "refs 4, live 7 -> pri 11428". Let's try to fit: pri = refs*? + live*?. For (3,4)->7500 and (4,7)->11428. Hmm 7500/... If pri = 1000*(something)+... Let's see: (3,4): 7500; (4,7): 11428. Difference refs 1, live 3 → +3928. If pri = a*refs + b*live: 3a+4b=7500, 4a+7b=11428 → subtract: a+3b=3928 → a=3928-3b; 3(3928-3b)+4b=7500 → 11784-9b+4b=7500 → 5b=4284 → b=856.8, a=1357.6. Not integer. Maybe pri = refs*1000 + live*... no.

Maybe pri is computed as: pri = (refs * 1000) + something. 3 refs → 7500? no.

Alternatively gcc's actual formula (global.c, GCC 12+):
```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    {
      pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
      ...
    }
  else
    {
      ...
      pri = (100 * num_refs) + ...
    }
```
Hmm.

Actually I do recall the code:
```
  /* Adjust the priority to take into account the frequency of the
     references.  */
  ...
  pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
```
Hmm but pseudo regs have REG_FREQ_PRIORITY computed too.

Wait — 11428 and 7500 — hmm, maybe pri = freq*... Let me look at actual gcc source. I recall in gcc/global.c (GCC 11+):

```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  else
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  ...
```

Actually the real code:
```
/* Return the priority of allocation node N.  */
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    {
      pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
      ...
    }
  ...
```
Hmm, REG_FREQ_MAX = 1000? no.

I think the actual modern code is:

```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;

  /* This used to be the default.  */
  if (reg)
    pri = (REG_FREQ_PRIORITY (reg) * REG_FREQ_MAX) / 100;
  ...
```
OK I'm going in circles. Let's take the pragmatic path: the notes' suggestion (c): "introduce a local live across [call..mask test] with pri > 10000 (refs 3, live 2) so it takes $2 and pushes the call result to $3 — check the allocno tie-break (global.c:607) by declaring it BEFORE ret".

Hmm, but actually maybe a simpler mechanism: gcc's reg allocation gives $2 (v0) to the RESULT_DECL when the result is "used in the epilogue" and gcc does the "return value" copy... Actually in the target, the return value is computed in $2 directly (lbu v0, xori v0). And the call result in $3.

What if the function returns the boolean directly but the RESULT_DECL is a separate variable? Hmm.

Alternative approach: gcc's "prefers v0" for call results: the call-result pseudo is a "call" pseudo which has a hard reg preference. If instead we don't assign the call result to a variable but use it directly in the condition, gcc still has the call result pseudo.

Key idea: make the RESULT_DECL have a SET before the call. E.g.:

```
int result = 0;   // hmm result is the return var
...
```
Wait, the C0505 catalog allows "init at decl". If the return variable is declared and assigned 0 at decl, its live range covers the whole function, so it competes for $2 at the call point and (having more refs) may win.

But the function returns `result` — with the original structure:
```
int result = 0;
...
ret = call();
if (ret != 0) {
    if (ret & 0x8000) result = (byte)buf2[6] == 0x15;
} 
return result;
```
That's the original body but with `result` initialized at decl instead of the pin. The original had `register int result __asm__("$2")` plus `result = 0` inside the branches. Removing the pin but keeping `result` as a normal variable — the RESULT_DECL then would be the variable `result` (which IS the result decl in the original? no, the original returns `result` so result IS the RESULT_DECL).

Wait, in the original pinned code, `result` is declared with `register int result __asm__("$2")` and it's the returned value. So `result` = RESULT_DECL, pinned to $2. Lever-free version: `int result;` with the same body. Then RESULT_DECL refs 3 (set 0, set boolean, use in return), live from... The note says lever-free r73 = RESULT_DECL (pri 10000, refs 3, live 3, prefers v0) and call-result pseudos r79/r82/r84 (pri 10000, refs 2, live 2).

So pri ties at 10000, and the allocno tie-break decides: call-result gets $2 because it has lower allocno (born earlier)? The notes mention "loses the allocno tie-break (global.c:607)".

In gcc global.c, the allocno priority function:
```
static int
allocno_priority (int n)
{
  int reg = reg_allocno[n];
  int pri = 0;
  ...
  if (reg == 0) return 0;
  ...
```
and:
```
/* Return true if allocno N is more urgent than allocno M */
```
There's `global.c:607` in the dump context. Hmm.

Practical approach: try many spellings and score them. Fast (1.7s per try). Let's be systematic:

Spellings to try for func_8014FD54:
1. `int result = 0;` at decl + the body as in orig (with result set in branches). → gives RESULT_DECL a set before the call.
2. Declare result before ret / after ret (decl order).
3. `unsigned` result.
4. Combine: `result = 0;` at decl, `ret = call()`, `if (ret != 0) { if (ret & 0x8000) result = ...; }` `return result;`
5. Use `ret` as the return var directly?
6. `if (ret == 0) return 0;` early return form (tried, 6).
7. Make the boolean comparison into an assignment: `result = (*(u8*)...) == 0x15;`

Actually the crucial structural difference is: target computes the returned value in $2 and the call result in $3, with the tests on $3. In mine, the call result is in $2 and the boolean computed in $3 or $2?

Mine (39 ins): `beqz v0` (test call result in $2), `andi v0,v0,0x8000`, `beqz v0` — so the call result stays in $2 through the tests, then the boolean computed... The diff shows mine[24:28] vs target[24:29]. So mine has 4 ins there vs target 5 (the extra `move v1,v0`).

So the target copies the call result out of $2 to $3 immediately, then the tests on $3, and $2 is free to hold the final boolean.

To do this lever-free, gcc must decide that the call-result pseudo goes to $3 and RESULT_DECL to $2. Since the RESULT_DECL in lever-free form starts late (after the call), the call-result pseudo occupies $2 at the call point; the RESULT_DECL then gets $3 (allocated later? no, regalloc works globally).

Hmm — the note says both have pri 10000 but the call-result wins. In GCC's global allocation, allocation order is by priority, and for equal priority, by allocno number (higher allocno = allocated later?). Actually in global.c the sorting: `qsort` on allocnos by priority, descending; ties broken by allocno? Let me recall `global.c:607`:

```
/* Sort by priority, then by allocno number.  */
```
The note says "loses the allocno tie-break (global.c:607)". So the tie-break is allocno number; the call-result pseudo presumably has a lower allocno? No — lower allocno is allocated first and wins? "loses the allocno tie-break" for RESULT_DECL means RESULT_DECL has a HIGHER allocno (allocated later, lower priority in tie).

To flip, we need the RESULT_DECL to have a LOWER allocno (declared/created earlier) or higher priority.

Try (c): a local live across [call..mask test]. But the final result must be in $2... Actually the RESULT_DECL's register is $2 in target because the pin forced it. Lever-free, if we introduce another variable that is live across the call and takes $2 (higher pri), then the call result goes to $3 and the RESULT_DECL goes to... hmm, $3? Then the RESULT_DECL's boolean would be computed in $3, not $2. But in the target, the final boolean IS in $2 (lbu v0, xori v0). If our extra variable takes $2, the boolean gets $3 → wrong.

Unless the extra variable IS the RESULT_DECL itself, i.e. we want RESULT_DECL to be live across the call and be the one with $2.

So: `int result = 0;` before the call — RESULT_DECL live across call. Then at the call point, both call-result and RESULT_DECL want $2. RESULT_DECL pri 10000 refs 3 live longer (live covers whole function) → live longer might reduce priority (priority usually = refs*... / live?). The notes say call-result pri 11428 (refs 4, live 7) > RESULT_DECL 7500 (refs 3, live 4) in the PINNED dump. So pri grows with refs and live. In the lever-free dump both are pri 10000 — probably clamped/normalized (frequency-based priorities are normalized to 10000 max).

Hmm! pri 10000 in both lever-free cases, and the difference is the allocno tie-break. So in lever-free, priority computation gives exactly 10000 to both — likely the "REG_FREQ_PRIORITY" based (frequency), normalized so the max is 10000.

So to flip the tie we need either different frequency (more references in the hot path?) or a different allocno order (earlier creation).

Frequency-based! REG_FREQ_PRIORITY is based on the estimated execution frequency of the pseudo's references (from profile/loop). Without profile, gcc uses heuristics. Hmm, but if both are 10000, they might both be max.

Alternatively the tie-break at global.c:607 might be `allocno` order, so making the RESULT_DECL created EARLIER (lower allocno) could flip it. The RESULT_DECL is created at the return statement? No — the RESULT_DECL is created when the function's return value is set up (at the epilogue), typically at the end. But if `result` is a local variable that's returned at the end (`return result;`), then `result` is NOT the RESULT_DECL — the RESULT_DECL is a copy of result at the return point! Hmm. That's the key.

So to make the RESULT_DECL be live across the call, you'd need `return result;` where result is set before the call — but the RESULT_DECL pseudo is the copy at return time... Actually gcc's RESULT_DECL is a pseudo holding the return value; `return result;` copies result into RESULT_DECL at the return point. So the RESULT_DECL is live only at the return.

BUT if the function body ends with `return result;` where result is assigned in branches, then the copy into RESULT_DECL happens at the merge point.

Whereas if we write `return <expr>;` directly in each branch (the direct-return form, which they tried → score 6), the RESULT_DECL is set in each branch, but the merge point still has a copy.

Hmm, so how to make $2 hold the RESULT_DECL from the beginning? What if the function returns the value from a single expression that evaluates at the end? No.

Wait. Let me reconsider: maybe in the target, $2 at ins 29-31 (lbu v0, xori v0) is not the RESULT_DECL but just the final value register — in the pinned version, `result` was pinned to $2 so the boolean computed into result lands in $2 and the return just uses it.

In the lever-free version, we want gcc to naturally produce: call result in $3, final boolean in $2, and the return copy `move v0, v0` (nothing). Since $2 is the return register (v0), gcc will naturally put the final returned value in $2 — indeed at the end gcc copies the RESULT_DECL to v0. If the RESULT_DECL were computed in $2 already, no copy needed. So actually the target's structure is natural for gcc if the call result weren't in $2.

So the whole problem: keep the call result out of $2. The call result pseudo prefers v0 and has high pri. To push it to $3, another pseudo must take $2 with higher priority, and that pseudo must be the one holding the final value.

Idea: What if the boolean computation's temp (the u8 load and the xor) is a pseudo that's live across the call?? No, it comes after.

Idea: use `&&`/`||` fold? Tried, score 6.

Idea: make the call result NOT assigned to a variable but compared directly, and make the boolean expression such that gcc evaluates it into $2? e.g.

```
if (func_80133784(1, buf1, (int)buf2) != 0) { ... }
```
The call result is still a pseudo.

Hmm. What about assigning the call result to a variable of a different type, e.g. `short`? Then the call result needs an extension, which forces a copy into $3! E.g. `s16 r = func_80133784(...)` — the call returns int, truncating to s16 requires a copy (move v1,v0 + andi?). Hmm, that adds instructions.

What about `unsigned short ret = func_...()` — zero extension: `move v1,v0; andi v1,v1,0xffff`? That adds an insn. But the target has `move v1,v0` only (no andi). Unless the compiler knows the value fits? no.

Hmm, what about declaring ret as `int` but the comparison `(ret & 0x8000)`: gcc computes andi in place. Fine.

Another idea: make the call result used twice with different types, forcing a copy.

Alternatively, flip which value goes in which register: the target has the call result in $3 and the final in $2. What if lever-free gcc produced the final in $3 and call in $2? That's what mine does (score 6).

Idea from the notes (a): "an instruction-neutral spelling that gives the RESULT_DECL a set BEFORE the call (an early return that crossjump merges into the existing exits)". So a `return` before the call? Like:

```
int result;
if (param_1 == 0) return 0;   // no, changes semantics
```
Hmm.

Let's think about how the RESULT_DECL gets set before the call: e.g.

```
result = 0;
ret = call();
if (ret != 0) { if (ret & 0x8000) result = (u8)buf2[6] == 0x15; }
return result;
```
Here RESULT_DECL (copy of result at return) is still after. But `result` (the local) is a separate pseudo with a set before the call! result is live across the call → result's pseudo is live across a call, and gcc's regalloc might give it $3 or a callee-saved... Hmm, but result's refs: set at decl, set in the branch, use at return = 3 refs, live across the call.

Then RESULT_DECL = copy of result at return, in $2 probably (prefers v0). And `result` gets $3? And the call result gets... hmm, then the final value would be copied from $3 to $2 at the return → extra `move v0,v1` insn.

Unless gcc's cross-jumping merges and the copy disappears... unlikely.

Hmm, but wait: in the target, is there a `move v0, v1` at the end? Let's look at the full target listing. Let me get the target listing. The diff only showed part. Let me dump the target assembly to see ins 29-39.

Let me find the target asm. There's a build/ dir with the target. Let me check tools/delever_search.py to understand how it gets the target, and whether I can dump the target listing.

Let me look for the target objdump.

Actually, maybe there's a helper: .run/P40/T10/func_80181F4C/ (worked example). Let me look at that dir and at tools/delever_search.py --help.

Let me be efficient: run `tools/delever_search.py --help` and find the target asm file.

Also I should consider: is the effort better spent on other items? This item already has 34 tries and a wall hypothesis. The brief says continue from its best, count earlier tries toward 30, budget 20-30 min. So I should spend ~20-30 min here (it may need ≥20 min and ≥30 tries for a WALL). It already has 34 tries but only 15 min wall. So I need ≥20 min wall. Then move on to the other 3 items.

Let me look at the target listing first.
