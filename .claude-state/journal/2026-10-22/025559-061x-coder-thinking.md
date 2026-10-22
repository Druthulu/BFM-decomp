---
ts: 2026-10-22T08:55:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FG0AQOsiGPPzn54TJ55I
---
In the sched1 dump, the copy `(set (reg:SI 4 a0) (reg/v:SI 74))` exists (the call-arg copy) — and there's NO copy of r73 into a0.

Interesting: ";; register 74 life shortened from 9 to 8" — sched1 shortened a live range!

So the preference "73 prefers 4" remains unexplained by a copy...

Hmm, unless the preference is not for r73 but the print means something else. Let me test the hypothesis "the print means: pseudo X has a preference for hard reg R" by looking at the PINNED version's dump:
```
;; 4 regs to allocate: 74 76 83 72
;; 72 conflicts: 72 74 83 2 3 4 29
;; 74 conflicts: 72 74 83 2 29
;; 74 preferences: 4
;; 76 conflicts: 76 3 29
;; 83 conflicts: 72 74 83 2 29
```
In the pinned version: r74 prefers 4, and the dispositions: 74 in 4 (a0).

In the pinned version, what is r74? Let me get the pinned .rtl to map the pseudos. In the pinned version, the q is hard $3, so the pseudo set differs. Let me check the pinned .lreg/.rtl.

If in the pinned version r74 = the ptr (the call-arg copy source) → consistent.

And in the lever-free version, r73 = q with "preferences: 4" and r74 = ptr with "preferences: 4". Both prefer a0! But only the ptr has a copy.

UNLESS: the q pseudo r73 is a *copy* of the ptr r74 in the RTL?! Hmm! Look at the arm blocks: insn 43: `(set (reg/v:SI 73) (mem/s:SI (plus:SI (reg/v:SI 72) 100)))` — a load, not a copy.

Hmm, BUT: what about the *join* block: the store's address uses r73. Hmm.

WAIT A SECOND. What about cse? The two loads (insn 43 and insn 74) are the same expression but in different blocks with a call between → not CSE'd. OK.

Hmm, what about the possibility that the preference print means "the pseudos that prefer hard reg 4"? I.e., ";; 73 preferences: 4" = "pseudo 73's preferences: [4]" — that's what I assumed.

Ugh. Let me try to settle it by a controlled experiment: compile a tiny function with a known copy and check the .greg dump format. E.g.:

```c
s32 f(s32 x) { s32 y; y = x + 1; return y; }
```
Hmm, that has a copy from a0? Let me write a small test TU and dump it. That's a cheap, decisive experiment (~30s).

Test:
```c
s32 tf(s32 a, s32 b)
{
    s32 p;
    s32 q;
    p = a + b;
    q = p * 2;
    return q + p;
}
```
Hmm, I want a copy from a hard reg to a pseudo and see the dump.

Let me do:
```c
s32 tf(s32 a)
{
    s32 p;
    p = a;        /* copy from a0 (hard) to pseudo p */
    return p + 1;
}
```
Then the .greg dump should show "preferences: 4" for p if my reading is right.

Let me do this with the rdump script on a small file. The cpp needs the include path etc. Let me write the test file under my shard dir and run rdump.sh with -dg.

This is worth 2 minutes to settle the mechanism.
