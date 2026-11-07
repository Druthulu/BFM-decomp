---
ts: 2026-11-06T06:04:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y3Hk1bxKH9UwWN404WQu
---
Still 10. Time 23:04.

OK, let me now decide: I'll write the item 4 WALL. The wall clock is ~13 min, tries ~70. The ≥20 min rule... Hmm.

Let me look at the exact wording again: "Budget 20-30 min wall per item (`date` at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

I interpret "a WALL needs ≥20 min and ≥30 scored tries" as the criteria for counting the item as a legitimate attempt (as opposed to giving up early). I have 70+ tries. The time is 13 min. To be strictly compliant, let me keep going ~7 more minutes.

Let me think about what else to try. Actually, let me revisit the possibility that the *launder* can be replaced by a real C construct that produces NO instruction but blocks the fold. 

Hmm — what about a `goto` that creates an extra basic block? E.g.:
```c
if (cc != one) goto second;
func_8012D624(...);
goto check;
check:
if (cc == one) goto rejoin;
second:
```
A label after the call creates a new basic block (a branch target). Would that block flow's knowledge? No, the value is still known.

What about a `label` used by a `goto` from elsewhere? E.g.:
```c
if (cc != one) goto second;
func_8012D624(...);
if (cc == one) goto rejoin;
...
```
Hmm.

What if the label `check` is also targeted from a path where cc != one? Then gcc can't assume cc == one at `check`. For example:

```c
if (cc != one) goto second;
func_8012D624(...);
goto check;
second:
    ...
    /* somewhere */
check:
if (cc == one) goto rejoin;
```
Hmm, if `check` is reachable from both paths, the test can't fold. But the target's flow: the `beq s1,s2, rejoin` is only on the cc==one path (after the call), and the second block is separate.

Wait, actually — the target's second test `beq s1,s2, rejoin` at 1890: is it reachable from the second block? No: 1894 (move a0,s0) is the delay slot, then 1898 is `second:`. So the beq is only on the fall-through path.

Hmm.

What if we restructure so the check is shared:
```c
if (cc != one) goto second;
func_8012D624(...);
second:
...
check:
if (cc == one) goto rejoin;
```
Hmm, that changes the flow.

OK, what about making the test reachable from a path where cc is unknown — e.g., a loop that re-enters. If the second test were the loop condition of a loop whose backedge comes from somewhere cc is unknown... 

Let me try:
```c
if (cc != one) goto second;
func_8012D624(...);
for (;;) {
    if (cc == one) goto rejoin;
    break;
}
second:
```
gcc would fold (cc == one known). Hmm.

What if the loop body modifies cc? No.

OK. I'm convinced. Let me write the WALL now and accept the 13-min mark... 

Hmm, actually, let me reconsider the risk: the brief says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". If I record a WALL at 13 min, it might be judged as "not an attempt" and the item would need redoing. That's a real risk. Let me spend the time.

Let me do more experiments, slower. I'll try some of the structural ideas above.

Actually, let me try the "shared check" idea concretely:

```c
if (cc != one) goto second;
func_8012D624((void *)a0, 0xC0, 0x30);
if (cc == one) goto rejoin;
second:
...
```
→
```c
if (cc != one) goto check;    // hmm
func_8012D624(...);
check:
if (cc == one) goto rejoin;
second:
```
That changes the flow: `goto check` where check is the test. Then the test is reachable from both paths (cc != one via the goto, and cc == one via the fall-through) → gcc can't fold it! And the asm might be:
```
bne s1,s2, check     (instead of "second")
call
check: beq s1,s2, rejoin
second:
```
Hmm, but the target's first branch goes to `second` (1898), not to the check. Let me look at the target:
```
187c bne s1,s2, 1898   ← second
...
1890 beq s1,s2, 18c8   ← rejoin
1894 move a0,s0        (second block's a0)
1898 second:
```
So the first bne targets 1898 (second), and the beq targets 18c8 (rejoin). If I write `if (cc != one) goto check;` the bne would target the check (1890). Different.

Hmm, unless gcc arranges it so... no.

OK. Let me try a variant where the first branch targets the second block and the test is reachable from a *third* path. Hmm.

Actually — what if the second block *falls through* to the check? In the target, the second block (1898-18c4) ends with `jal func_8012D624; li a2,48` then 18c8 (rejoin). So the second block flows to rejoin.

Hmm.

OK. Let me now try some "flow" ideas:
bb1: 
```c
if (cc != one) goto second;
func_8012D624(...);
if (cc == one) goto rejoin;
goto second;
second:
```
s4-like (25).

bb2: make the check shared via a label placed after the second block? no.

Let me just accept the WALL and spend the remaining minutes on a couple of long-shot experiments.

Actually, let me try something with the *structure of the whole if*: what if the target's shape comes from the source:
```c
if (cc == one) {
    func_8012D624(...);
    if (cc == one) goto rejoin;
}
```
Hmm, gcc folds the inner.

What if the source is:
```c
if (cc == one) {
    func_8012D624(...);
}
if (cc == one) goto rejoin;
```
The second test is after the if — gcc knows: on the path where cc == one (the if was taken), the test is true → goto rejoin; on the fall-through (cc != one), the test is false. So gcc folds it into a jump.

Hmm.

OK. Let me write the WALL at ~23:08-23:11. Let me do a couple more tries and then write.

Let me try 3 more:
cc1: the "goto check" idea (to see the score).
cc2: `if (cc != one) goto second; func_8012D624(...); if (cc != one) goto second; goto rejoin;` (inverted second test).
cc3: the second test on `cc - one`.

Let me run them.
