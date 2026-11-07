---
ts: 2026-11-06T16:36:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hr5kn1jXVRYxFPkQ4Srd
---
Still 9. Let me check the label idea concretely: we need a CODE_LABEL between the then arm's branch and its jump. What C creates a label there? 

Consider:
```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    if (0) { docall: ; }
    ...
```
Dead label deleted.

What about a label targeted by a goto from the else arm, placed in the then arm? That would change control flow but if unreachable... e.g.:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
lbl:
    goto docall;
} else {
    if (d >= 0x201) goto skip;
    goto lbl;    /* never: skip taken? no, if d<0x201 falls here -> goto lbl -> docall. Same behavior. */
}
docall: call;
```
This changes: else arm with d<0x201 jumps to lbl (in then arm) then to docall. Target's else arm falls into the call. This adds a jump. No.

Hmm. Alternatively place a used label after the branch in the then arm, targeted from within the same arm by a conditional that's folded? 

Different idea: make the then arm's branch and jump adjacent but have the branch's RTL differ from the else's by using a different comparison constant type. Actually wait — what about making the *else* arm's test use `>` with a different constant that folds to the same 0x201? E.g. `if (d > 0x200)` → same slti 513. RTL same.

What if the else arm's test is `if ((s32)(d - 0x201) >= 0)`? Different insns.

Hmm, what about making the branch compare against a *pseudo* that's copy-propagated to the same RTL? Post-reload, same.

Let me reconsider: maybe the merge isn't the unconditional-jump cross-jump. Let me look at what actually changed between v1.jump and v1.jump2 (the goto-docall variant) to identify the pass and mechanism. Compare the function section.
