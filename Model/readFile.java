
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class readFile {
    private List<String> lines;

    public static List<String> readLineByLine(String filepath) throws IOException {
        File file = new File(filepath);
        List<String> r = new ArrayList<>();
        BufferedReader reader;
        reader = new BufferedReader(new FileReader(file));
        String line = reader.readLine();
        while (line != null) {
            r.add(line);
            line = reader.readLine();
        }
        reader.close();

        r.remove(0);
        return r;
    }

    public static List<String> readLineByLineScanner(String filepath) throws FileNotFoundException {
        List<String> r = new ArrayList<>();
        Scanner scanner = new Scanner(new File(filepath));
        while (scanner.hasNextLine()) {
            r.add(scanner.nextLine());
        }
        r.remove(0);
        scanner.close();
        return r;
    }

    public static List<String> readFileInList(String fileName) throws IOException {
        List<String> lines;
        lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);
        lines.remove(0);
        return lines;
    }

    public List<String> getLines() {
        return new ArrayList<String>(this.lines);
    }

    public readFile(String filepath) throws IOException {
        this.lines = new ArrayList<>();
        readLineByLine(filepath);
    }
}
