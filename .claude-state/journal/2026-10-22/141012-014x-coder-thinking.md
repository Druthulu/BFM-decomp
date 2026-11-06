---
ts: 2026-10-22T20:10:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v9k6sE8J3GWguFesXlQZ
---
So the candidate: `addiu s1,sp,16` in the beqz delay slot, then `move a1,s1` per call. The address pseudo is live from before the copy... no, the copy stores are direct sp offsets. So the address pseudo is only the call args (3 uses) — same as target — but global-alloc gave it s1 because its live range crosses 3 calls.

Target instead rematerializes. Difference must be register pressure/priority. Target: s0=obj, s1=self. Candidate: s0=obj, s1=addr, s2=self. If the addr pseudo weren't allocated, self would be s1 and frame same as target.

So the question: why did global-alloc give the address pseudo a callee-saved reg in mine? Both have the same refs. Unless the target's source has the address pseudo created *inside* each call argument in a way that cse doesn't merge. Wait, if cse merged them, the live range crosses calls, and global-alloc's decision to allocate s1 vs spill depends on priority. The target's pseudo apparently was spilled (or not allocated). Why would the target's be spilled and mine allocated?

Possibility: in the target, the address pseudo is `(plus (reg fp) (const 16))` in QImode? No.

Another thought: GCC's global-alloc has "allocno" priorities; the address pseudo's priority = sum of refs weighted by live length. In the target there are 2 call-crossing pseudos: self (many refs) and obj. The addr pseudo has 3 refs crossing 3 calls. Priority might be lower than self's. But in mine, self is a *different* pseudo (s2) with high refs, obj s0. Both mine and target have the same set: self, obj, addr. Yet different outcome.

Unless in the target, the address pseudo is created by the *movstr* and used... no, direct sp stores.

Hmm, maybe in the target the C source is:
```
RotMatrixX(..., m);
RotMatrixZ(..., m);
RotMatrixY(..., m);
```
but with m declared as `int m[8]` and the copy via a loop or via separate loads... The current src (score 0, with levers) uses scalar `src[i]` loads into `m[i]` assignments, so no movstr. And in the src body, the m-address for calls... The src body with launder+pin scores 0; but the pin $5 is on `src` and there's a launder. What's the address situation there? Let me score a variant of the src body minus the launder (keep pins) to see. Actually the task: kinds=launder only, so I need to remove the launder; pins may stay. Let me try: take orig.c and delete line 19 (`__asm__("" : "=r"(src) : "0"(src));`) — does it score 0? That's the obvious first candidate: "launder" only. Let me test.

That's the key baseline: how far does the launder-free but pin-kept version get? The prior coder apparently found 19 via c_struct. But maybe simpler: remove the launder line and score. Let me test that quickly.

Wait, careful: the launder's purpose is to stop cse from folding `src` (constant address) into uses. Removing it means cse folds. Let me test.
