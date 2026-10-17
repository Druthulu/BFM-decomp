---
ts: 2026-10-17T16:19:59.190Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb4a08fa100d7feb
model: claude-opus-5-5[1m]
effort: medium
turnId: dd20a3af-7bad-4cc5-bdfe-eb40b857c079
---
I'm analyzing the register priority calculations for pb in function func_8017E804, checking whether its current priority of 1081 with 4 live references needs to exceed roughly 1900 to beat competing registers r169/r170 and r174, and working out how increasing the reference count would affect that priority via the log2 scaling factor.

Verifying the formula against gcc 2.7's actual allocno priority computation, I confirm refs=4 gives 1081 as observed, and testing values shows refs=7 lands right at the boundary (~1891.9) while refs=8 clears it comfortably at 3243. Now I'm thinking through concrete ways to introduce extra pb dereferences in the source — since gcc 2.7 lacks strict aliasing, a store to ot between loads of *pb could force the compiler to redo the load, so I'm considering restructuring the early addPrim code to add fresh *pb reads between statements to push the reference count up.

I'm realizing that just pinning refs artificially won't help since the keepalive trick only adds pseudo-uses without emitting instructions, so matching the target binary means the extra pb references have to come from legitimate reloads triggered by real memory accesses in the existing code, not synthetic additions.

I need to check whether pb2 is actually merged with r77 in the RTL, so I'm planning to grep the .cse and .lreg dumps to see which registers get loaded from the D_800B9A02 symbol.
