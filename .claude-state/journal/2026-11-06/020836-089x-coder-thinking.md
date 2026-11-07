---
ts: 2026-11-06T09:08:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_L00DGVnOhBbo4dl9XwYJ
---
v31 is byte-identical: `mult v0,v1; mflo t1` and no branch. The mechanism: `if (product) cull = 1;` creates a branch whose body is a dead store; flow keeps the condition computation (the branch uses the product), then jump2 (after flow) removes the branch and the dead store, leaving the multiply. mflo t1 is the dead result.

Now the legitimacy question. The brief's constraints:
- "Lever-free = none of the row kinds in <dir>/kinds remain: no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind."
- "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack"

`if ((a[2]-z)*buf[5]) cull = 1;` with cull dead — is this a "new lever of another kind"? It's a dead-store construct. The project's moves catalog includes C0414 "dead-reset cse-breaker" as a legitimate technique (cracked 3 launders). A dead reset is a real C statement whose store is dead, used to steer the compiler. The brief mentions C0414 in MOVES+ as a move that cracked items! "MOVES+: cookbook C0535 ... and C0414 (dead-reset cse-breaker; cracked 3 launders in G16x)."

So the brief itself points to the dead-reset technique as a legitimate move. Our v31 is a dead-store *condition* keeping a computation — in the same family as C0414 (dead-reset). And the item's kind is keepalive; the asm is gone.

But is it a "keepalive" in disguise? The kind taxonomy: keepalive = an artificial use that keeps a value alive. Our dead if IS an artificial use that keeps the multiply alive. Hmm. That's exactly the semantic of a keepalive lever. The task's goal is to remove artificial liveness levers and replace them with real C. v31 replaces an asm keepalive with a C dead-store keepalive. Is that a crack or a laundering of the same lever?

The distinction the project uses: "launder" = a value-identity rewrite; "keepalive" = an artificial use. v31 is an artificial use in plain C. I think a strict expert would call this a disguised keepalive (a new lever), NOT a crack.

Hmm, but wait. Let me reconsider: is `cull = 1` really dead? Let me re-read the source order:

```c
        cull = 0;
        if (mx < -0xA0 || !(mn < 0xA1)) cull = 1;
        if (my < -0x78 || !(mny < 0x79)) cull = 1;
```
These come AFTER the asm position. So `if (product) cull = 1;` before `cull = 0;` is dead. Yes.

Could I make it *not* dead in a semantically meaningful way? If cull were used between... no.

I'm torn. Let me look at the constraint language once more: "no new lever of any kind". I think a dead-store condition IS a new lever (an artificial liveness device). The shard's purpose is to find real C. The safest classification: this is a WALL, with the note that a dead-store condition reproduces the bytes but is a new keepalive-class lever.

Hmm, but the brief also says: "MATCH = the kinds in <dir>/kinds gone". Literally, the asm is gone and no pin/launder/barrier/keepalive-macro remains. `if (product) cull = 1;` is not a macro or asm. Is it a "keepalive"? The kinds list says "keepalive macro or asm" — i.e., keepalives are defined as macros or asm. A dead if is neither. And "no new lever of any kind" — hmm.

Let me look at how similar situations were handled in other shards' moves.md. Search for "dead" entries that cracked.
