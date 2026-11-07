---
ts: 2026-11-06T06:10:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MRpS3MY0TevL3kVmwcW0
---
I need a .c TU file to dump. I can create a spliced TU: copy the src TU and replace the function body with my candidate. Simpler: take the src TU file, splice my body in place of the original function, save as a scratch .c under my item dir, then dump.

That's a bit heavy (7k-line TU). Dumps are large; must delete after.

Alternatively: since I only need pp vs zpush priority, maybe a cheaper experiment path: just try candidates.

Let me think about what free C construct adds a loop-weighted ref. In the worked example: `do { r = p + i; } while (0);` then `*(s16 *)(r + 0xE) = -0x70;` — the add folded into the store's address computation, so r got a ref but no insn.

For pp, a use that folds: any place where a pointer is added to a constant and used as an address. E.g. `pf` is used as `&flag`... 

Hmm! What about `pp` being used in the *else arm* where v0p = arg0+0x84? no.

What if I restructure loop 1's RotTransPers4 call to pass `pp` and `pf` and ALSO give pp an extra use in the loop via the loop counter? no.

Completely different: maybe make `p` itself used directly somewhere so pp gets a use... no.

Let me think about zpush again: 3 refs, live 126. pp: 2 refs (def+1 use? wait: def 1 + use 1 per iteration = 2 refs, loop-weighted 1 + 2 = 3).

Hmm, actually the "refs" in gcc's reg_n_refs: flow.c computes `REG_N_REFS (regno) += (loop_depth + 1)`? Let me check flow.c to be precise. Then I can compute exactly what change flips it.

Let me grep flow.c for n_refs.
