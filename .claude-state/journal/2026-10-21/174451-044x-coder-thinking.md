---
ts: 2026-10-21T23:44:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_4Tb1oPlHSIHeYtpIA9pf
---
"cse's find_best_addr keeps an address pseudo that is used twice, and it crosses calls in an $s register"

So the RULES: an address pseudo that is used twice survives cse's find_best_addr and crosses calls in an $s register.

find_best_addr in cse.c: it looks for a better address for a MEM. Hmm.

**find_best_addr!** This is the key. cse.c's `find_best_addr (reg, addr)` is called for MEMs: when cse has a MEM (like `sp10[5]`, i.e. `*(u16*)(sp+26)`) and it finds that the address could be expressed as (reg + offset) with a register... Hmm, actually find_best_addr works on the *address* of a MEM: it tries to find a "better" address expression, e.g. turning (symbol_ref + const) into (reg + const).

Hmm, here's the thing: cse's find_best_addr might be the one that CREATES the address pseudo! Let me think: in cse.c, `record_cse` for a MEM: it computes the address, and calls find_best_addr to see if the address can be represented as base+offset where base is a register. For our case, the address sp+24 = (plus (symbol_ref sp10)(const 8)). find_best_addr would look for a reg... hmm.

Hmm, actually here's the relevant thing: cse.c's find_best_addr:

```
/* If we have a plus of a symbol_ref and a constant, and we can find
   a register that holds the symbol's address, use that instead. */
```

Hmm! That's it! find_best_addr tries to replace (plus (symbol_ref X) (const K)) with (plus (reg R) (const K')) where R holds X's address. But it only does this if the reg is cheaper.

Hmm, but that would produce a register version.

Alternatively, find_best_addr might CREATE a pseudo to hold the address. Let me look at the actual gcc 2.7.2 source... The project mentions "gcc 2.7.2 source" in the comment! ("lane B's map (`.run/P36/engine/residual_moves.md`, S101, gcc 2.7.2 source)").

So the compiler is gcc 2.7.2. Let me find the gcc source in the project — maybe there's a copy for reference. Let me search for cse.c in the repo.
