---
ts: 2026-10-17T14:08:44.887Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a91f36121b5043b6a
model: claude-opus-5-5[1m]
effort: medium
turnId: 2eee350e-3a84-4d56-9c95-e752be0f81a2
---
The simulation checks out: comparing priorities for const1 versus r76 shows const1 winning because scheduler1 places its live range right before the store, giving it a short life and thus high priority. But in the target, v1 gets placed right after the load, giving it a long life and lower priority—so I need const1's live range to also get placed early, meaning it shouldn't be treated as a "birth" that gets deferred.

Actually, rethinking this: the target's li appears early in the final assembly, but scheduler2 could still move it there after allocation, even if local-alloc placed it differently. If val is pinned (hard register) from local-alloc, then r78 takes the first available free register, which turns out to be v1 since v0 is occupied by the hard-pinned val. For const1 to lose priority to val, I need val's priority—based on 4 references over its live range—to exceed const1's priority of 2 references over a life of 2, meaning val's live range must stay short, under about 8 instructions, which could work if its load sits close to the final store and scheduler2 later hoists that load upward past symbol stores with no dependency, consistent with its latency-driven scheduling behavior after reload_completed.

But testing this against variant a3, the actual load ends up stuck between the symbol stores and the final pointer dereference, meaning scheduler2 didn't hoist it at all, so there's clearly no register conflict with `zero` or `at` forcing that order—it just chose not to move it. I'm now considering whether extending const1's life instead, perhaps by making its pseudo register get reused with multiple assignments so it's no longer treated as a short-lived birth value, could shift the priority balance in my favor.

Trying to picture what original source expression would naturally produce this scheduling in the target—maybe something like an increment at the end rather than a direct store, and recalling variant b1's score was worse on ordering, likely because the load placement differed there too.

I think the better approach is a more systematic search: trying combinations of how `val` is expressed (plain addition, pre-increment, post-increment, or no val reference at all), where that read falls among the other stores in the target, and how D_801B7988 factors in, to find which combination reproduces the exact instruction order.

I'm also weighing whether moving the D_801B7988 store earlier, before the func_8017F53C call, could work -- but that risks changing semantics if the callee reads it, so I should look for a safer way to share that constant with an earlier use instead.

I'm trying a few perm2 candidates to check their priority scores. Maybe the li instruction's birthing behavior could change if its constant value were shared with another store elsewhere in the block, but there's no second store of 1 in case 0 to exploit. I'm also considering whether REG_EQUIV handling in local-alloc.c could be keeping this constant's live range artificially doubled.

The simulation confirms the dump exactly: the constant-1 pseudo r78 wins priority because sched1 places its `li` right before the store, giving it a short life of 2 versus val's life of 16. I'll now check local-alloc.c:1016-1064, which the catalog cites for doubled constant lifetimes.
