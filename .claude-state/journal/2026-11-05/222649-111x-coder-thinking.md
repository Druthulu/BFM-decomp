---
ts: 2026-11-06T05:26:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WnZZGngFQzsusff3QJgt
---
All 42. The labels were removed.

Time: item 3 at ~22:33 (15 min). ~43 scored tries. I need 20 min. Let me spend a few more minutes.

Let me think once more. The dead-store elimination: `last_mem_set` + `rtx_equal_p`. Where is `last_mem_set` reset? Let me look at propagate_block.

If it's reset at a CALL_INSN, then a call between the stores would fence. But a call adds a jal.

If it's reset at a CODE_LABEL, we need a label that survives.

What about a label that survives because it's referenced by a `switch`? Let me test a switch with a case label at the store:

```
switch (u88) {
case 0x7fffffff:
    break;
default:
    b[0] = u88;
}
```
Hmm, adds code.

What about `asm goto`? lever.

OK, what about the *value* difference: `rtx_equal_p` compares the MEM. If the store's MEM has a different mode... 

Hmm, wait: what if the two stores are to the same address but one is a SUBREG/zero-extract? no.

Let me check `last_mem_set` reset conditions.
