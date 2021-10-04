import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;

public class TestesPerformance {
    public static void main(String[] args) throws IOException {

        Crono.start();
        readFile.readFileInList("../../../input_files/reviews_1M.csv");
        readFile.readFileInList("../../../input_files/business_full.csv");
        readFile.readFileInList("../../../input_files/users_full.csv");
        Crono.stop();
        System.out.println(
                "Tempo para ler todos os ficheiros a ler o ficheiro todo de uma vez: " + Crono.getTimeAsString());

        Crono.start();
        readFile.readLineByLineScanner("../../../input_files/reviews_1M.csv");
        readFile.readLineByLineScanner("../../../input_files/business_full.csv");
        readFile.readLineByLineScanner("../../../input_files/users_full.csv");
        Crono.stop();
        System.out.println("Tempo para ler todos os ficheiros com Scanner: " + Crono.getTimeAsString());

        Crono.start();
        List<String> rdR = readFile.readLineByLine("../../../input_files/reviews_1M.csv");
        List<String> rdB = readFile.readLineByLine("../../../input_files/business_full.csv");
        List<String> rdU = readFile.readLineByLine("../../../input_files/users_full.csv");
        Crono.stop();
        System.out.println("Tempo para ler todos os ficheiros com BufferedReader: " + Crono.getTimeAsString());

        ConsultasInterativas ci = new ConsultasInterativas(rdR, rdB);

        Crono.start();
        ci.consulta1();
        Crono.stop();
        System.out.println("Tempo para consulta 1 usando Set<>: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta1List();
        Crono.stop();
        System.out.println("Tempo para consulta 1 usando List<>: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta2(2012, 5);
        Crono.stop();
        System.out.println("Tempo para consulta 2 usando Set<> para o ano 2012 e mes 5: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta2List(2012, 5);
        Crono.stop();
        System.out.println("Tempo para consulta 2 usando List<> para o ano 2012 e mes 5: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta3("7MTNM_Rwlc4up5PF180rDQ");
        Crono.stop();
        System.out.println("Tempo para consulta 3 com user_id: 7MTNM_Rwlc4up5PF180rDQ : " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta4("EXOsmAB1s71WePlQk0WZrA");
        Crono.stop();
        System.out.println("Tempo para consulta 4 com business_id: EXOsmAB1s71WePlQk0WZrA : " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta5("YoVfDbnISlW0f7abNQACIg");
        Crono.stop();
        System.out.println("Tempo para consulta 5 com user_id: YoVfDbnISlW0f7abNQACIg : " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta6(15);
        Crono.stop();
        System.out.println("Tempo para consulta 6 com x=15 : " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta7();
        Crono.stop();
        System.out.println("Tempo para consulta 7: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta8(15);
        Crono.stop();
        System.out.println("Tempo para consulta 8 com x=15: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta9("A-xLw4u4wYusT1A2N-1Vxw", 15);
        Crono.stop();
        System.out.println("Tempo para consulta 9 com business:id = A-xLw4u4wYusT1A2N-1Vxw e x=15: " + Crono.getTimeAsString());

        Crono.start();
        ci.consulta10();
        Crono.stop();
        System.out.println("Tempo para consulta 10: " + Crono.getTimeAsString());
    }
}
