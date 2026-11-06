---
ts: 2026-10-22T21:42:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7nwIcC38XHaJqKw5SKkk
---
Pins are needed (nopins = 17). breset/treset = 3 (COUNT — worse than the ORDER 2).

Time: item 4 started 15:34, now ~15:47. 13 min. Let me keep going a bit more; I have budget to 16:04.

Let me think harder about the sched1 tie-break. In gcc 2.7.2 sched.c, the ready list insertion:

```
static void
ready_add (ready, insn)
{
  struct ready_list *ready;
  rtx insn;
{
  rtx link;

  if (ready->count > 0)
    {
      int priority = INSN_PRIORITY (insn);
      rtx *prev = &ready->vec[0];
      ...
```
I recall it inserts by priority with a scan from the end:
```
      /* Find the first insn in the queue with a lower priority */
```
Let me actually check if the gcc source is in the repo (tools/bin/gcc-2.7.2-psx/ maybe only binaries). If sched.c is available, I can read the tie-break.

Actually, a faster empirical route: figure out what makes the $4 copy first. Try making testval's *use* later in the same block: if testval is used at the very end of the block... The block ends at the beq. testval's use (beqz at 13) is in the next block.

Hmm, so what if I restructure the condition so that testval's use is inside block 1? Not possible — the branch IS the use.

New angle: maybe the order isn't sched1 at all, but the *expand* order: maybe the `testval = src` copy is emitted before `byteval = src` because gcc emits the branch condition first? No.

Actually! Consider that in mine (u32/u32), the copies are at 7 and 8 — and 8 is the *delay slot* of the beq at 11? No, delay slots are 12 (sll a1). So both are regular.

Let me test a quick experiment to identify the pass: compile with -fno-schedule-insns? We can't change the pipeline flags, but I can look at the RTL dumps with tools/cc1_dumps_tu.sh. That's the reliable route but costs time (dump + read). The brief says "read dumps when unsure".

Given time, maybe try a couple more real-C ideas first:

Idea I: swap the two copies' *destinations*? Not allowed (pins).

Idea J: make byteval's copy also feed an early insn: what if `uVar4 = 0;` uses byteval? No.

Idea K: Use the `&&`/`||` fold: rewrite `if ((iVar3 == c5) || (testval != 0))` as `if (!((iVar3 != c5) && (testval == 0)))`. The codegen would flip branches. Not the target.

Idea L: Assign testval *inside* a nested block after the byteval assignment — block scope changes local-alloc's reg_basic_block. Let me try:
```
        byteval = src;
        {
            testval = src;
        }
```
Hmm, block scope for a pinned hard-reg variable — the pin declaration is inside the loop block already.

Idea M: declare testval at function scope (like byteval_outer tried for byteval → 3). Try testval at function scope.

Idea N: change `testval = src;` to `testval = src + 0;`... folded.

Idea O: since the target's order is $3 then $4, and mine is $4 then $3 — what if I make byteval's copy come from a *different* register chain so it's born earlier: e.g. `byteval = src;` where src is `(param_2 >> 0x10) & 0xf` — the copy is at 7 (right after the andi). In mine the a0 copy is at 7. So mine's $4 copy is born immediately after the andi, and the $3 copy after it. The target: $3 immediately after the andi, $4 after.

What if I give the $3 copy a *shorter dependency chain*? Both depend on v0 (andi result).

What if byteval is assigned from `(param_2 >> 0x10) & 0xf` directly (recomputing the expression) rather than from src? cse would fold it to src's value... but if cse folds, we get the same. Unless the second expression is not cse-equal... it is.

Hmm, what about assigning byteval from `src` but src as a *different mode* variable... 

Let me try the RTL dump route — it will tell me exactly which pass orders them. Cost: ~2-3 min. Let me check tools/cc1_dumps_tu.sh usage.

Actually, a cheaper diagnostic: compile with the same pipeline but add -dp? Not available.

Hmm, alternative cheap diagnostic: test whether the order flips if the *branch* is absent (e.g. replace `testval != 0` with `testval != 0x100`) — no.

Let me think about gcc 2.7.2's sched1 priority more concretely. INSN_PRIORITY is computed by `priority()` in sched.c:

```
static int
priority (insn)
{
  ...
  if (INSN_PRIORITY_STATUS (insn)) return INSN_PRIORITY (insn);
  for each successor: priority = max(priority, 1 + priority(next)) where next is the next insn in the *block* (via next_nonnote_insn, and if it's a barrier/jump → 0)
```
Actually in 2.7.2 it's:
```
  if (GET_CODE (insn) == NOTE ...) 
  next = next_nonnote_insn (insn);
  if (next) this_priority = priority (next) + 1;
```
So the priority is the count of insns to the end of the function?? `priority()` walks next_nonnote_insn regardless of blocks (with a check for BARRIER/CODE_LABEL → 0). Hmm, in 2.7.2:

```
static int
priority (insn)
     rtx insn;
{
  int this_priority = -1;
  ...
  if (GET_CODE (insn) == NOTE)
    return priority (next_nonnote_insn (insn));
  /* Find the next real insn */
  next = next_nonnote_insn (insn);
  ...
  if (next) this_priority = priority(next) + 1;
  /* Loop through the successors */
  ...
```
I don't remember exactly. But if priority counts through the whole function (past branches to the following code), then the $3 copy (used at 19-25, far later) would have HIGHER priority than the $4 copy (used at 13). Higher priority → scheduled FIRST in 2.7.2 (the ready list is sorted by priority descending? or ascending?). Empirically mine schedules $4 first, so either priority is ascending or the $4 path is longer.

$4's use at 13 (beqz) → the path continues to 14... (the fallthrough block) which then jumps to 30 (jr ra) or the loop. $3's use at 19 → 20 → 25 → 29 → 30.

Both end at 30. The $4 path: 13→14→...→30 = many insns. The $3 path: 19→...→30 = fewer.

If priority = distance to the end, $4's is longer → scheduled first if higher priority goes first. So the $4 copy is scheduled first because it's "closer to the branch". And with both QI, the $3 copy is forced first by the dependency.

To flip: make the $3 value's path longer than the $4's? The $3 value (byteval) is used at 19 (sll v1,v1,3) and 20. Its path to the end: 19→20→25→29→30 ≈ 5. The $4 value is used at 13 → 14→15→...→30 ≈ 15.

Alternatively, the scheduler's `priority` counts *all* insns after the use to the end of the block? If blocks matter, both are 1.

Whatever the exact rule, the lever is: which value is used earlier in the code. If I could use byteval before the branch and testval after... but the branch is where testval is used.

Hmm! What if testval's use were later in the block — i.e. the condition uses testval in the *second* branch (beqz) which is at 13, i.e. block 2. And byteval's use at 19.

So: make byteval used in block 1 (before the beq) and testval in block 2? Then byteval's use is closer → higher priority → scheduled first. But what use of byteval can I add in block 1? None naturally.

Alternatively: make testval's use in a LATER block (block 3) — e.g. move the `beqz` check after the store? That changes the code shape.

OK here's another thought: what if the ORDER difference is not sched1 but *local-alloc's tie-breaking*, since both copies target hard regs and both are live... 

Time is 15:52. Let me try 4-5 more variants then decide.

Variant P: `testval = src;` replaced by `testval = (u32)src;` on u32 base — no-op.
Variant Q: give the sb an intermediate temp so v1's chain is longer... no.
Variant R: make byteval's assignment the *second* statement AND wrap testval in a do-while(0)? 
Variant S: `if ((iVar3 == c5) || (testval != 0))` → assign testval inside the `||` via a comma? e.g. `if ((iVar3 == c5) || ((testval = src) != 0))` — then testval's birth is inside the condition, likely later in RTL! That could flip the order: byteval's copy born first (statement), testval's copy born in the condition expression (later). And it's real C (comma/assignment inside a condition). But the value must still be `src`. Let me test:

```
        byteval = src;
        param_2 = param_2 << 4;
        if ((iVar3 == c5) || ((testval = src) != 0)) {
```
Careful: `testval` is assigned only in the || right side — but with short-circuit, if iVar3==c5 it's not evaluated; testval is only used there, so fine. But it's a pinned register var; assignment in the condition is legal C.

Hmm, but is the testval assignment then in a different basic block? No, it's the same block (the condition is evaluated before the branch).

Variant T: similarly assign byteval in a comma expression.

Let me test S.
