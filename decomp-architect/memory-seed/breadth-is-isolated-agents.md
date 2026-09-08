---
name: breadth-is-isolated-agents
description: For breadth-shaped work (many independent functions), isolated agents are token-CHEAPER than the main loop doing them serially — the main context re-sends everything each turn (≈ quadratic), an agent's context is fresh and tiny (≈ linear) and runs in parallel
metadata:
  type: reference
---

For breadth-shaped work — drafting byte-exact C for N functions — spawning one isolated agent per item is cheaper than the
main conversation doing them one after another, even though it looks like N copies of the same prompt.

**Why:** the main conversation re-sends its entire growing context on every turn, so function N is processed with functions 1
through N−1's disassembly, diffs and drafts still in context — the cost grows roughly quadratically. Each spawned agent gets a
fresh, small context (its one function) — roughly linear — and the agents run in parallel, so hours become minutes. Measured on
the source project: forty functions serially cost several times what forty isolated agents cost. The redundant per-agent reading
of shared documents is real but secondary.

**How to apply:** batch a few functions per agent, pre-filter the trivial ones, and trim what each agent reads (an inline idiom
cheat-sheet beats "read the whole cookbook" — more context was measured to be worse, not better). The compile-and-hash gate is
local and free; only the drafting costs tokens. Fully model-free drafting hits a low ceiling; the model is what lifts it. Working
a function by hand in the main loop wins only for a handful of high-value items; past that, accumulation makes it lose.
