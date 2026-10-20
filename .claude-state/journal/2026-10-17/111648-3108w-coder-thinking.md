---
ts: 2026-10-17T17:16:48.509Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm tracing how pseudo a1 got directly combined into the hard register set, explaining why insn 94's UID places it after the call-argument setup rather than earlier in the chain—since combine merged it into the arg-register assignment at the call position.

With a keepalive, an extra use of a1 would block combine from merging it, keeping the set early and allowing the arg move to be deleted after allocation. I'm trying to figure out how to naturally force two uses of a1 without the combine engine folding it—maybe via a separate reference that doesn't get constant-folded, or through a block boundary that breaks the LOG_LINKS connection combine relies on to merge the set and use.

A cast to int wouldn't change anything since it's a no-op in that mode, and other type possibilities don't fit either. I think the mechanism here is that combine folds the single-use a1 pseudo into the call-arg move, and scheduling keeps it after the v0 chain, but the keepalive's second use blocks the merge — I'll tag this as a new combine-argcopy-sink pattern, ranking it 4th best.
