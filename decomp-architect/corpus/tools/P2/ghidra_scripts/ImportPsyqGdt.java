// ImportPsyqGdt.java — headless equivalent of the GUI ".gdt attach".
// Opens a PsyQ type archive (default psyq400.gdt) and resolves ALL its data
// types into the program's DataTypeManager. resolve() both copies the types in
// AND registers the .gdt as their SourceArchive, so the program shows psyq400
// as an attached source archive and the MCP types/struct tools can reference
// the PsyQ structs/typedefs. Run via: -process SLUS_007.26 -noanalysis
//   -postScript ImportPsyqGdt.java [/abs/path/to/psyqXXX.gdt]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeConflictHandler;
import ghidra.program.model.data.DataTypeManager;
import ghidra.program.model.data.FileDataTypeManager;
import ghidra.program.model.data.SourceArchive;
import java.io.File;
import java.util.Iterator;

public class ImportPsyqGdt extends GhidraScript {
    @Override
    public void run() throws Exception {
        // P33 B5: default = THIS Ghidra installation's ghidra_psx_ldr extension (no home-directory assumption)
        String gdt = new File(ghidra.framework.Application.getInstallationDirectory().getFile(false),
                              "Ghidra/Extensions/ghidra_psx_ldr/data/psyq400.gdt").getPath();
        String[] a = getScriptArgs();
        if (a.length > 0) gdt = a[0];
        File f = new File(gdt);
        println("=== IMPORT PSYQ GDT ===");
        println("GDT: " + f.getAbsolutePath() + "  exists=" + f.exists());
        if (!f.exists()) { println("ERROR: gdt not found"); return; }

        FileDataTypeManager fdtm = FileDataTypeManager.openFileArchive(f, false);
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        int before = dtm.getDataTypeCount(true);
        println("Program DTM types before: " + before);
        println("Archive DTM types:        " + fdtm.getDataTypeCount(true));

        int n = 0;
        java.util.List<String> sample = new java.util.ArrayList<>();
        int tx = currentProgram.startTransaction("import " + f.getName());
        try {
            Iterator<DataType> it = fdtm.getAllDataTypes();
            while (it.hasNext()) {
                DataType dt = it.next();
                dtm.resolve(dt, DataTypeConflictHandler.DEFAULT_HANDLER);
                if (n < 15) sample.add(dt.getName());
                n++;
            }
        } finally {
            currentProgram.endTransaction(tx, true);
        }
        fdtm.close();

        println("Resolved " + n + " types from " + f.getName());
        println("Program DTM types after:  " + dtm.getDataTypeCount(true));
        println("Sample type names: " + sample);
        println("Source archives now associated with the program:");
        for (SourceArchive sa : dtm.getSourceArchives()) {
            println("  - " + sa.getName());
        }
        println("=== END IMPORT PSYQ GDT ===");
    }
}
