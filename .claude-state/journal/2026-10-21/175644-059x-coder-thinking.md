---
ts: 2026-10-21T23:56:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YuDAkzqexiffCCRXjC41
---
Close! Score 9, same instruction count (40). The difference:
- Target: `move v1,v0` (ret copied to $3), then tests on v1; the result computed in $2 (v0).
- Mine: the ret value stays in $2 (v0) and the result is computed in $3 (v1) then copied to $2 (`move v0,v1` at ins 34).

So without the pin, gcc keeps `ret` in $2 (the call's return reg) and puts `result` in $3.

With the pin, `result` is forced to $2 → the call result `ret` goes to $3 (copied) ✓.

Lever-free fix: make the `result` value land in $2 naturally and `ret` in $3.

Ideas:
1. Swap the roles: since `ret` is only used for tests, and `result` is the return value — gcc gave $2 to ret because it came from the call (the call result is in $2 naturally) and the result got $3.

To flip: the `ret` value should be copied out of $2 into another register, and the result computed in $2.

Why does the target copy `v0 → v1` (move v1,v0)? Because the call result is in $2 and the pin forces $2 to be used by `result`, so `ret` must move to $3.

Without the pin, gcc keeps ret in $2 (no copy) and computes the result in $3, copying to $2 at the end (`move v0,v1`).

How to get the target's shape lever-free? We need the result to be computed in $2 and ret in $3.

Ideas:
(a) Force a copy of ret: e.g. `ret = func_80133784(...)` → then `if (ret != 0)`. What if the source stores the call result into a variable that's then copied? e.g.
```c
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) { ... }
```
That's the current source. gcc keeps it in $2.

(b) What if we use the call result directly in the test and copy it to another variable?
```c
if (func_80133784(1, buf1, (int)buf2) != 0) { ... }
```
but we need `ret` twice (the != 0 test and the & 0x8000 test) → gcc would CSE the call? It can't (the call may have side effects) → it would call twice ✗.

(c) Make the result be computed FIRST (before the call)? No.

(d) Use a different type for `ret` (e.g. s16) so the copy from $2 to $3 is needed: e.g. `s16 ret;` → then `ret = func_80133784(...)` truncates → `move v1,v0`? Hmm: a s16 pseudo would need an HImode copy → the value in $2 (call result) copied to a HImode pseudo → maybe `move v1,v0` + no truncation needed if gcc knows it's 16-bit... The ROM has `move v1,v0` ✓ and `andi v1,v1,0x8000` — hmm, if ret were s16, the test `ret & 0x8000` would be a sign-extended value; the ROM's `andi v1,v1,0x8000` suggests a 32-bit value.

Hmm. But the key difference is just WHICH register holds what. Let me think about how gcc allocates: `ret` (a pseudo) is set from the call (in $2) and used twice → gcc keeps it in $2 (no copy). `result` is a pseudo set in 3 places and returned → gcc gives it $3 and copies to $2 at the end.

Wait, why doesn't gcc give `result` $2? Because the copy preference for the return value... the return value is `result` → the copy `set $2, result` → so `result` has a copy preference for $2. But `ret` also wants $2 (it's live from the call). local-alloc assigned ret → $2 (born first) and result → $3.

With the pin, result IS $2, so ret → $3 (with a copy).

To flip without a pin: make `ret` NOT want $2 — e.g. if `ret` were a *different width* (HImode) or if the call result were copied.

Idea (e): assign the call result to a variable of type `s16` or `u16`:
```c
short ret;   /* hmm, the call returns int */
```
Then `ret = func_80133784(...)` → the pseudo is HImode → gcc must copy $2 → the HImode pseudo (allocated $3?) → `move v1,v0`? But then `ret & 0x8000` on an s16 → sign extension → different bytes (the ROM has `andi v1,v1,0x8000` — a 32-bit andi). With `u16 ret`, `ret & 0x8000` → the value zero-extended → `andi v1,v1,0x8000` ✓ possible! And `ret != 0` ✓.

Hmm, but with u16, the truncation from the call result would need `andi v1,v1,0xffff` (an extra insn) ✗ — unless gcc knows the value fits... it doesn't.

Idea (f): Keep `ret` as int but force a copy by using it in a context that requires a different register: e.g. the target's `andi v1,v1,0x8000` — the AND is done in place on v1. In mine, the AND is done in $2 (v0) in place.

Hmm, what if the source computes `ret & 0x8000` into a variable?
```c
if ((ret & 0x8000) != 0) {
```
The ROM does `andi v1,v1,0x8000` in place ✓ (the same as mine, but on a different reg).

Idea (g): What if the source reads `ret` twice in a way that forces a copy? Like:
```c
if (ret != 0) {
    result = 0;
    if ((ret & 0x8000) != 0) { ... }
}
```
Both uses of ret are in the same block chain; gcc keeps it in one reg.

Idea (h): Swap the ORDER of the tests? no.

Idea (i): What if `result` is assigned BEFORE the call? e.g.
```c
result = 0;
ret = func_80133784(...);
if (ret != 0) { if ((ret & 0x8000) != 0) { result = ...; } }
```
Then `result` is born before `ret` → local-alloc might give $2 to result (born first) and $3 to ret ✓✓!

That's promising: in the target, `result`'s first set is at ins 28 (`move v0,zero` — hmm, that's after the call). Hmm, the ROM's structure:
```
24 move v1,v0     ; ret = v0
25 beqz v1,+0x88  ; ret == 0 → return 0
26 andi v1,v1,0x8000
27 beqz v1,+0x8c  ; → return 0
28 move v0,zero   ; result = 0
...
```
So in the ROM, `result = 0` (ins 28) is AFTER the tests, and `ret` is copied to $3 at ins 24 (right after the call).

The copy `move v1,v0` right after the call suggests gcc needed to move the call result out of $2 because $2 was reserved for `result` (the pin). Without the pin, gcc has no reason to copy.

So the lever-free version must make gcc (a) copy the call result to another register and (b) compute the result in $2.

Hmm, what if the result variable is declared BEFORE ret (decl order) and assigned before the call?

Variant M1:
```c
int func_8014FD54(int param_1)
{
    short buf1[3];
    short buf2[4];
    int result;
    int ret;
    result = 0;
    buf1[0] = 0; ...
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
}
```
This changes the structure (result=0 hoisted before the call) → the ROM has `move v0,zero` at ins 28 (after the tests) ✗ probably different bytes.

Hmm. But maybe gcc sinks the `result = 0`... Since `result` is only assigned in the branch, gcc might sink it. Let me test anyway.

Variant M2: keep the structure but declare result before ret:
```c
    int result;
    int ret;
```
(only the decl order changes). local-alloc might then prefer $2 for result. Cheap test.

Variant M3: use the call result directly in a temp that forces a copy:
```c
    ret = func_80133784(1, buf1, (int)buf2);
    if (ret != 0) {
```
Hmm.

Let me test M1, M2 and also M4: swap the two `result = 0` assignments' structure:
```c
    result = 0;
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
```
(this is M1 without the else branch).

Let me write M2 (decl swap) and M4 (hoisted result=0, no else) and M1 (hoisted result=0, with else). Test all three in parallel.

Hmm, careful with M1: `result = 0;` before the call adds a `move v0,zero` early ✗. Unless gcc sinks it into the branch (gcc does "store motion"/RTL sinking for pseudo sets: the set of a pseudo that's only used later can be sunk into the block where it's used ✓ — that's likely, since the pseudo's set would be sunk to the merge point).

Hmm, but in the ROM the `move v0,zero` at ins 28 is in the "ret != 0" path (after the andi test) — i.e. the set of result=0 in the "then" path. And the else path (ret == 0) has `move v0,zero` at ins 34. So there are 2 sets of result=0, one per path ✓ (as in the source).

So M4/M1 (single hoisted result=0) would give 1 set ✗ (the ROM has 2). Hmm, but the ROM's 2 sets come from the source's 2 assignments (in the if and else branches) ✓. So keep the source structure.

So M2 (decl order swap) is the main candidate. Let me also try:
M5: swap the order of the two tests' source? no.

M6: What if `ret` is assigned via a temporary that forces a copy:
```c
    ret = func_80133784(1, buf1, (int)buf2);
```
→ what if we write:
```c
    int tmp = func_80133784(1, buf1, (int)buf2);
    ret = tmp;
```
Hmm, that gives 2 pseudos: tmp ($2 from the call) and ret ($3) → the copy `move v1,v0` ✓!! And result → $2? Hmm, then $2 would be tmp (born at the call) and result would get $3 or $4... Hmm, but tmp dies right after the copy → $2 could be reused for result? But result's live range overlaps tmp's... result is set at ins 28 (after the copy at 24) → they don't overlap → $2 could be reused ✓!

So M6:
```c
    ret = func_80133784(1, buf1, (int)buf2);
```
→
```c
    tmp = func_80133784(1, buf1, (int)buf2);
    ret = tmp;
```
Hmm, but gcc would coalesce tmp and ret (they're equivalent: tmp = call, ret = tmp → after copy propagation, ret = call → the copy is removed) ✗. Combine would propagate the value → tmp and ret become the same pseudo → no copy.

Hmm. Unless the copy is needed because of the register class... no.

OK, let me think about the priority mechanism: `result` is the return value → in gcc, the returned pseudo gets a copy preference for $2 (via "hard reg copy" preferences). For LOCAL pseudos, local-alloc may honor "reg" preferences? Hmm.

But we observed: without the pin, result got $3 and ret got $2. So the preference wasn't honored, OR ret was born first and local-alloc gave $2 to the first-born.

Test M2 (decl order: result declared before ret) — if the allocation follows the declaration order, this could flip it. But the decl order affects the pseudo numbers (birth order) — the call result `ret` is born at the call, which is later than the declaration. Hmm, the pseudo NUMBER order might matter for local-alloc's tie-break.

Let me just test M2 and a couple of others empirically. Let me write:
M2: decl order swap (result before ret).
M7: `result` declared as `int` but assigned `0` via `result = 0;` in both branches (same) and `ret` used with an explicit cast? no.

Let me also consider: what if the source's `if (ret != 0) {...} else { result = 0; }` is restructured as:
```c
    result = 0;
    if (ret != 0) {
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    }
    return result;
```
The ROM's 2 sets of `move v0,zero` (ins 28 and 34) suggest the source has 2 assignments (or gcc duplicated one). With the hoisted version, gcc might duplicate the `move v0,zero` into both paths (since the value must be set on both paths) → 2 sets ✓ and the structure might match! Actually that's plausible: gcc's "if-conversion"/"expand" would put `move v0,zero` in the predecessor block... Hmm, in the ROM, ins 28 `move v0,zero` is in the "ret != 0" path (after the andi test at 26-27 — wait, ins 27 `beqz v1,+0x8c` jumps to the return-0 path (ins 34), so ins 28 is the fallthrough of the andi test (i.e. (ret & 0x8000) != 0 → result = 0 then check buf2[3]).

Hmm, so ins 28 `move v0,zero` = result = 0 in the path where the mask is set but the byte check gives 0/1.

And ins 34 `move v0,zero` = the "ret == 0" path (the else branch) → result = 0 ✓.

So both `result = 0` assignments are in the source's two branches ✓ (as written).

OK so the structure of the source is right; only the register assignment differs. The lever-free candidate must make gcc allocate $2 to `result`.

Hmm, one more idea: what if `result` is used as the return value directly (`return result;`) — gcc's copy preference for the return reg is expressed as a "preference" attached to the pseudo. In gcc 2.7's global-alloc, copy preferences are honored for globals; for locals, local-alloc has `local_var` handling: in final.c's local_alloc, there's a step "if the pseudo is the return value, prefer the return register" — hmm.

Since ret and result are both local pseudos in the same block, local-alloc allocates them in order of... let me test empirically with decl order.

Let me write M2 (decl swap) and M8 (ret assigned to a variable of type `unsigned short`? no).

Let me do M2 + M4 (hoisted result = 0, no else) in parallel, plus M9:
```c
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
            result = *(unsigned char *)((char *)buf2 + 6) == 0x15;
        }
    } else {
        result = 0;
    }
    return result;
```
= same as nopin.

M10: swap the two tests to use a temp:
```c
    if (ret != 0) {
        result = 0;
        if ((ret & 0x8000) != 0) {
```
Hmm.

Let me try M2 and M4 now.
