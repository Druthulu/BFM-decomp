---
ts: 2026-10-17T17:08:26.826Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6aaa11811b8be773
model: claude-opus-5-5[1m]
effort: medium
turnId: c3153718-defe-4620-a7c2-e0184cae88c0
---
This looks like the same cse-const-addr wall pattern again, where the symbol address needs a pseudo before loading into a hard register via "la" on MIPS, and CSE shares that symbol across calls. I'm checking whether reassigning the pointer variable kills the CSE class for that symbol.

My plan is to use a single function-scope pointer variable, assign it the symbol address for the call, then reassign it afterward to another real value (like a struct field pointer), which should break the equivalence so later blocks reloading the symbol address don't get merged. I need to replace the various to1-to6 locals with this one reused pointer across each block, checking their declared types carefully before swapping them in.
