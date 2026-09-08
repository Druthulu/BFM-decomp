// DumpProgramInfo.java — headless postScript that prints the authoritative
// program metadata after import+analysis: language/compiler spec, image base,
// function count, and every Program-Information property (incl. the
// ghidra_psx_ldr "PsyQ Version" that Phase 1's milestone requires recorded).
// Plain Java GhidraScript (compiled at runtime by Ghidra; no Jython needed).
import ghidra.app.script.GhidraScript;
import ghidra.framework.options.Options;
import ghidra.program.model.listing.Program;

public class DumpProgramInfo extends GhidraScript {
    @Override
    public void run() throws Exception {
        Program p = currentProgram;
        println("=== BFM PROGRAM INFO ===");
        println("Name:             " + p.getName());
        println("LanguageID:       " + p.getLanguageID());
        println("CompilerSpecID:   " + p.getCompilerSpec().getCompilerSpecID());
        println("ImageBase:        " + p.getImageBase());
        println("ExecutableFormat: " + p.getExecutableFormat());
        println("FunctionCount:    " + p.getFunctionManager().getFunctionCount());
        println("DefinedDataCount: " + p.getListing().getDefinedData(true).hasNext());
        Options opts = p.getOptions(Program.PROGRAM_INFO);
        println("--- Program Information properties ---");
        for (String n : opts.getOptionNames()) {
            println("PROP  " + n + " = " + opts.getValueAsString(n));
        }
        println("=== END BFM PROGRAM INFO ===");
    }
}
