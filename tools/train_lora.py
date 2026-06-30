#!/usr/bin/env python3
"""train_lora.py — QLoRA fine-tune a code model into a BFM/gcc-2.7.2 MATCHING specialist.

Pilot recipe (docs/gen2-mips-matching-model.md). Trains on datasets/match_pairs/train_ft.jsonl
(produced by tools/format_finetune.py) and saves a LoRA adapter + a merged GGUF for LM Studio.

RUN THIS WHERE YOU HAVE A GPU + Unsloth (your 3080 Ti via WSL, or a cloud A100). NOT runnable in the
headless agent sandbox (no CUDA / no model download there). On a 12 GB card use the 7B base in 4-bit.

  # one-time setup (WSL2 with CUDA, or cloud):
  pip install "unsloth[cu121] @ git+https://github.com/unslothai/unsloth.git" trl peft datasets

  python tools/train_lora.py            # 7B pilot, ~3 epochs
  python tools/train_lora.py --base unsloth/Qwen2.5-Coder-14B-Instruct-bnb-4bit --rank 32

Then load models/bfm-match-7b/*.gguf in LM Studio and eval LEAN:
  LEAN=1 API_BASE=http://<host>:1234/v1 MODEL=bfm-match-7b \
    .venv/bin/python tools/api_draft.py --targets .run/ab-exp/targets20.json --out .run/ab-exp/lora --iters 4
  .venv/bin/python tools/ab_score.py --arms haiku local lora   # beat stock-local's ~0
"""
import argparse, os

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--base', default='unsloth/Qwen2.5-Coder-7B-Instruct-bnb-4bit',
                    help='4-bit base (7B fits a 12GB card; 14B needs ~16GB)')
    ap.add_argument('--data', default='datasets/match_pairs/train_ft.jsonl')
    ap.add_argument('--out', default='models/bfm-match-7b')
    ap.add_argument('--rank', type=int, default=16)
    ap.add_argument('--epochs', type=float, default=3.0)
    ap.add_argument('--max-steps', type=int, default=0, help='>0 overrides epochs (use for a smoke run)')
    ap.add_argument('--lr', type=float, default=2e-4)
    ap.add_argument('--maxlen', type=int, default=4096, help='token cap; lower to 2048 to avoid 12GB VRAM spill')
    ap.add_argument('--batch', type=int, default=2, help='per-device batch; 1 halves activation memory')
    ap.add_argument('--no-gguf', action='store_true', help='skip the merged-GGUF export step')
    a = ap.parse_args()

    # Imported here so --help works without a GPU/unsloth install.
    from unsloth import FastLanguageModel
    from unsloth.chat_templates import get_chat_template
    from datasets import load_dataset
    from trl import SFTTrainer, SFTConfig

    model, tok = FastLanguageModel.from_pretrained(
        model_name=a.base, max_seq_length=a.maxlen, load_in_4bit=True, dtype=None)
    model = FastLanguageModel.get_peft_model(
        model, r=a.rank, lora_alpha=a.rank * 2, lora_dropout=0.0, bias='none',
        target_modules=['q_proj', 'k_proj', 'v_proj', 'o_proj',
                        'gate_proj', 'up_proj', 'down_proj'],
        use_gradient_checkpointing='unsloth', random_state=3407)
    tok = get_chat_template(tok, chat_template='qwen-2.5')

    ds = load_dataset('json', data_files=os.path.join(REPO, a.data), split='train')

    def fmt(ex):
        return {'text': tok.apply_chat_template(ex['messages'], tokenize=False,
                                                add_generation_prompt=False)}
    ds = ds.map(fmt)

    trainer = SFTTrainer(
        model=model, tokenizer=tok, train_dataset=ds,
        args=SFTConfig(
            dataset_text_field='text', max_seq_length=a.maxlen,
            per_device_train_batch_size=a.batch, gradient_accumulation_steps=max(1, 16 // a.batch),
            warmup_ratio=0.03, num_train_epochs=a.epochs,
            max_steps=(a.max_steps if a.max_steps > 0 else -1), learning_rate=a.lr,
            logging_steps=1 if a.max_steps else 10, optim='adamw_8bit', weight_decay=0.01,
            lr_scheduler_type='cosine', seed=3407,
            output_dir=os.path.join(REPO, a.out, 'ckpt')))
    trainer.train()

    out = os.path.join(REPO, a.out)
    model.save_pretrained(out); tok.save_pretrained(out)
    print('LoRA adapter ->', a.out)
    if not a.no_gguf:
        model.save_pretrained_gguf(out, tok, quantization_method='q4_k_m')
        # disk hygiene: GGUF conv leaves a ~15GB merged-16bit + ~15GB BF16 gguf; keep ONLY the q4
        # (the ~30GB peak is what crashed C: last time — delete intermediates immediately after)
        import glob as _g
        for pat in (os.path.join(out, 'model-0000*.safetensors'),
                    os.path.join(out, 'model.safetensors.index.json'),
                    out + '_gguf/*BF16*.gguf', out + '_gguf/*bf16*.gguf', out + '_gguf/*F16*.gguf'):
            for f in _g.glob(pat):
                try:
                    os.remove(f); print('cleaned intermediate:', f)
                except OSError:
                    pass
        print('merged q4_k_m GGUF ->', a.out + '_gguf', '— intermediates cleaned')


if __name__ == '__main__':
    main()
