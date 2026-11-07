---
ts: 2026-11-06T16:40:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IylcQUgPU1m7MRclqGhJ
---
Notably: "A goto chain → structured C ... cross-jump re-merges duplicated tails (jump.c:2371) at zero bytes". And "duplicate the statement after an if/else join into both arms — one insn of live length splits it and cross-jump re-merges (R39)".

Hmm. Let me reconsider: maybe the answer is to *not* have the join be a separate block: duplicate the call in both arms and let cross-jump merge the call tails. We tried v3 (duplicated call) and got the same 197. But maybe with a different arrangement the cross-jump merges the calls, leaving the branch+jump structure of the target. Let's inspect v3's jump2 to see what merged.

Actually, let's dump v3 and look. But each dump costs time. Let me instead think about the order of cross-jump passes.

Alternatively, maybe the correct source structure is:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else {
    if (d >= 0x201) goto skip;
}
if (1) {  // no
```

Hmm.

Let me try a different tack: what if the two inner ifs are *separate statements* rather than an if/else, e.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
} else {
    if (d >= 0x201) goto skip;
}
```
The join block after the if-else. What if we put the call in the then arm's fallthrough by using `return` and in the else arm's fallthrough as well (v3). Let me actually check v3's jump2 to understand why it didn't work. Quick dump of v3.
