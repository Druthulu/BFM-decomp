---
ts: 2026-10-17T18:53:36.277Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a6ee12ed7d3da1789
model: claude-opus-5-5[1m]
effort: medium
turnId: c73a5082-25b2-49a4-a028-dd1d5ff9dd77
---
I'm tracing through how v0's set count interacts with the scheduler's "boosting" logic — since v0 is live at the return and only set once, it gets placed late, whereas the target register with multiple sets wouldn't get that treatment.

So I need another set of hard register v0 somewhere in the function to push n_sets to 2. A call-value could do it: if func_8005C604 is void but I cast the call site to return a value that's then ignored, gcc 2's expand_call still emits the call_value insn and sets v0 via hard_function_value, even though the result is discarded. That's a legitimate C-level trick — casting the function pointer type at the call site — and it should bump v0's set count without touching the original declaration.
