---
ts: 2026-11-06T14:59:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2WsItSaFK9AASYaJqjRy
---
So item 1 (func_801806D8, ov_SC03_099) has:
- launder: `__asm__("" : "=r"(vol) : "0"(vol));` on `vol` — lever 3.
- Also pins: `$4` register void *r4 __asm__("$4") on the first func_8004914C, and `$5` register s32 av __asm__("$5")`.

The kinds file says only `launder`. The pins under other causes may stay (per constraints: "levers of other kinds the def already had (pins under other causes) may stay, never added"). So for MATCH we need only to remove the launder — the `__asm__` on vol — and score 0.

Interesting: from moves.md line 187: `func_8018CDEC | MATCH: the launder tied-output on sc -> empty do { } while (0) ...` and line 192: launder on diff -> do{}while(0)+ real 2nd set.

But here, the launder's purpose (per comment) is: "lever 3: sched1 otherwise hoists the PAN multiply ahead of this one". So the launder prevents sched1 from reordering the two magic multiplies. The classic fix from cookbook: real 2nd set of `vol` — e.g. `vol = (s16)vol` or a compound assignment, or `do { } while (0)` with a 2nd set.

Note vol = ((0xA0 - av) * 0x7F) / 0xA0; then the launder; then sx = (sx+0xA0)/0x14.

The launder asm is `"=r"(vol) : "0"(vol)` — tied output, zero-width. To make it a real 2nd set: `vol = vol | 0;`? That would be folded away by the tree folder probably. `vol = (u16)vol;` gives an andi — changes ins count (value ≤ 0x7F so mask is a no-op value-wise but emits andi → +1 ins, mismatch). `vol = (s16)vol` is a no-op cast → no RTL change probably. Hmm. In G14: "v0 = (s16)v0 (a real 2nd set)". Since v0 is sign-extended s16, the cast is a no-op but creates a 2nd set in RTL? Actually a cast to the same type may create a SET of the pseudo in RTL? In G14, func_8017D73C: "n = (s16)n at both sites (a real 2nd set, value-preserving)". Hmm — that suggests gcc 2.7.2 does emit a real set for a cast to same-ish type? Possibly the cast makes a new pseudo with a conversion... Actually (s16)n where n is s32 → conversion to HImode then back to SImode: subreg. That generates a SET of a new pseudo... whatever. The empirical evidence says it works.

But there's a subtlety: the goal here is not the number of sets but preventing sched1 from hoisting the PAN multiply ahead of the VOL multiply. Actually the comment says "Both magic-multiplies write the same match_scratch, so sched1 ... always hoisted the PAN multiply first". So the fix must break that — a real 2nd set of vol adds a dependency: vol is used in the call arg (vol | (0x3000|sx)) & 0xFFFF; the 2nd set... hmm, the launder creates a REG_DEP_OUTPUT on vol making the vol computation "born" at the asm and the pan multiply cannot be scheduled before? Actually with sched1, scheduling is bottom-up; the asm is a barrier-ish (SCHED_GROUP? no, asm has priority). Hmm.

Wait, but a real 2nd set of vol: `vol = (s16)vol;` — the second set is a new insn whose source is the first vol; it doesn't prevent the pan mult from being hoisted... unless the 2nd set changes birth order.

Rather than theorize, let's just try candidates. That's the shard's job: lever-free bodies.

Important: lever-free means none of the row kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm. Wait — "no pin (register-asm/`__asm__` reg steer)" — the constraint says MATCH = the kinds in <dir>/kinds gone. The kinds here is only `launder`. But the CHANGE bullet says "Lever-free = none of the row kinds in <dir>/kinds remain: no pin ... launder, barrier, keepalive macro or asm". Hmm, ambiguous: "none of the row kinds in <dir>/kinds remain" and then it enumerates what those kinds mean. And CONSTRAINTS says "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added".

So for these items (kinds=launder), the pins ($4, $5) may stay since they're not row kinds here. Good — that matches e.g. moves.md line 49: "launder->pv=*p; pv&=0xFF000000 split; pv $3 pin dropped; ang $4 pin kept (not row kind)".

But careful: the pins here use `register ... __asm__("$4")` which is a pin — not a launder. Keeping them is allowed. Removing the launder asm is required.

However, "no new lever of any kind" — so we can't add pins or asm.

Now, the plan: for each item, copy orig.c (the function body? or the whole def?), then produce win.c that scores 0.

Let me check what dt.sh expects as "body file": delever_search.py --try <TU> <fn> <file> --body. Let me check the worked example .run/P40/T10/func_80181F4C/win.c and orig.c to see the format.
