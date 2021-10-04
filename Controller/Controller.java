import BusinessF.BusinessCaT;
import EstruturasAuxiliares.auxConsulta;
import ReviewsF.ReviewsCat;
import UsersF.UsersCat;

import java.util.*;
import java.io.IOException;

public class Controller {
	private static ConsultasInterativas ci;
	private static Estatisticas e;
	private static ReviewsCat rc;
	private static BusinessCaT bc;
	private static UsersCat uc;

	public static void run() throws IOException, ClassNotFoundException {
		Controller.execCommand(3);

		int mainCommand;

		while (true) {
			// UI.clearScreen();
			UI.printMainMenu();
			mainCommand = UI.getInt("> ");
			Controller.execCommand(mainCommand);
		}
	}

	public static void execCommand(int x) throws IOException, ClassNotFoundException {
		int queryCommand;
		switch (x) {
			case 1:
				UI.printQueries();
				queryCommand = UI.getInt("> ");
				Controller.execQuery(queryCommand);
				break;
			case 2:
				Crono.start();
				UI.printEstatisticas(e.nomeDoFicheiro(), e.numReviewsErradas(), e.numTotalNegocios(),
						e.numNegociosAvaliados(), e.numNegociosNaoAvaliados(), e.numTotaldeUtilizadores(),
						e.numTotaldeUtilizadoresQueAvaliaram(), e.numTotaldeUtilizadoresQueNaoAvaliaram(),
						e.numTotaldeReviewsSemImpacto());
				UI.printEstatisticas2(e.numeroDeReviewsPorMes(), e.mediaClassificacaoPorMes(),
									  e.numeroDistintoDeUtilizadoresPorMes());
				Crono.stop();
				UI.printTime();
				break;
			case 3:
				// Load
				// Reviews
				UI.print("To use the default filepaths just press enter!\n");
				String filepath_Reviews = "../../../input_files/reviews_1M.csv";
				String tmp = UI.getString("Filepath Reviews(default=" + filepath_Reviews + "):");
				if (!tmp.isEmpty())
					filepath_Reviews = tmp;
				// Businesses
				String filepath_Businesses = "../../../input_files/business_full.csv";
				String tmp5 = UI.getString("Filepath Businesses(default=" + filepath_Businesses + "):");
				if (!tmp5.isEmpty())
					filepath_Businesses = tmp5;
				// Users
				String filepath_Users = "../../../input_files/users_full.csv";
				String tmp2 = UI.getString("Filepath Users(default=" + filepath_Users + "):");
				if (!tmp2.isEmpty())
					filepath_Users = tmp2;

				Crono.start();
				List<String> rdR = readFile.readLineByLine(filepath_Reviews);
				List<String> rdB = readFile.readLineByLine(filepath_Businesses);
				List<String> rdU = readFile.readLineByLine(filepath_Users);

				bc = new BusinessCaT(rdB);
				uc = new UsersCat(rdU);
				rc = new ReviewsCat(rdR, bc, uc);

				e = new Estatisticas("Teste.txt", rc, bc, uc);
				ci = new ConsultasInterativas(rc, bc);
				Crono.stop();
				UI.printTime();
				break;
			case 4:
				// Load (ObjectStream)
				String filepath_txt = "gestReviews.dat";
				String tmp3 = UI.getString("Filepath (default=" + filepath_txt + "):");
				if (!tmp3.isEmpty())
					filepath_txt = tmp3;
				Crono.start();
				GetsReviews gr = GetsReviews.readFromBinary(filepath_txt);
				rc = gr.getReviews();
				bc = gr.getBizs();
				uc = gr.getUsers();
				Crono.stop();
				UI.printTime();
				break;
			case 5:
				// Save (ObjectStream)
				String filepath_txt2 = "gestReviews.dat";
				String tmp4 = UI.getString("Filepath (default=" + filepath_txt2 + "):");
				if (!tmp4.isEmpty())
					filepath_txt2 = tmp4;
				Crono.start();
				GetsReviews gr2 = new GetsReviews(rc, bc, uc);
				gr2.saveToBinary(filepath_txt2);
				Crono.stop();
				UI.printTime();
				break;
			case 6:
				// quit
				System.exit(0);
				break;
			default:
				UI.printError("Command " + x + " not recognized!");
				break;
		}
	}

	public static void execQuery(int x) {
		switch (x) {
			case 1:
				// QUERY 1
				Crono.start();
				AbstractMap.SimpleEntry<List<String>, Integer> c1 = ci.consulta1();
				Crono.stop();
				UI.printTime();
				UI.print("Length: " + c1.getValue() + "\n");
				UI.printList1(c1.getKey());
				break;
			case 2:
				// QUERY 2
				int mes = UI.getInt("Mes do ano: ");
				int ano = UI.getInt("Ano: ");
				Crono.start();
				AbstractMap.SimpleEntry<Integer, Integer> c2 = ci.consulta2(mes, ano);
				Crono.stop();
				UI.printTime();
				UI.print("Número total global de reviews realizadas : " + c2.getKey() + "\n");
				UI.print("Número total de users distintos que as realizaram: " + c2.getValue() + "\n");
				break;
			case 3:
				// QUERY 3
				String u_id = UI.getString("User id: ");
				Crono.start();
				Map<Integer, auxConsulta> c3 = ci.consulta3(u_id);
				Crono.stop();
				UI.printTime();
				UI.printMap1(c3);
				break;
			case 4:
				// QUERY 4
				String b_id = UI.getString("Business id: ");
				Crono.start();
				Map<Integer, auxConsulta> c4 = ci.consulta4(b_id);
				Crono.stop();
				UI.printTime();
				UI.printMap1(c4);
				break;
			case 5:
				// QUERY 5
				String u1_id = UI.getString("User id: ");
				Crono.start();
				List<String> c5 = ci.consulta5(u1_id);
				Crono.stop();
				UI.printTime();
				UI.print("Length: " + c5.size() + "\n");
				UI.printList1(c5);
				break;
			case 6:
				// QUERY 6
				int q = UI.getInt("Quantos negócios: ");
				Crono.start();
				Map<Integer, List<AbstractMap.SimpleEntry<String, Integer>>> c6 = ci.consulta6(q);
				Crono.stop();
				UI.printTime();
				UI.printMap2(c6);
				break;
			case 7:
				// QUERY 7
				Crono.start();
				Map<String, List<String>> c7 = ci.consulta7();
				Crono.stop();
				UI.printTime();
				UI.printMap3(c7);
				break;
			case 8:
				// QUERY 8
				int q1 = UI.getInt("Quantos utilizadores: ");
				Crono.start();
				List<AbstractMap.SimpleEntry<String, Integer>> c8 = ci.consulta8(q1);
				Crono.stop();
				UI.printTime();
				UI.printList2(c8);
				break;
			case 9:
				// QUERY 9
				String b1_id = UI.getString("Business id: ");
				int q2 = UI.getInt("Quantos negócios: ");
				Crono.start();
				List<AbstractMap.SimpleEntry<String, Double>> c9 = ci.consulta9(b1_id, q2);
				Crono.stop();
				UI.printTime();
				UI.printList3(c9);
				break;
			case 10:
				// QUERY 10
				Crono.start();
				Map<String, Map<String, List<AbstractMap.SimpleEntry<String, Double>>>> c10 = ci.consulta10();
				Crono.stop();
				UI.printTime();
				UI.printMap4(c10);
				break;
			case 11:
				// go back (do nothing)
				break;
			default:
				UI.printError("Query " + x + " not recognized!");
				break;
		}
	}
}
