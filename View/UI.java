import EstruturasAuxiliares.auxConsulta;

import java.util.*;
import java.util.stream.Collectors;

import static java.lang.Math.max;

public class UI {
	private static Scanner input;

	public static void clearScreen() {
		for (int i = 0; i < 100; i++)
			System.out.println("\n");
	}

	public static void printEstatisticas(String nomeFicheiro, int nReviewsErradas, int nTotalBizs, int nBizsAval,
			int nBizsNaoAval, int nTotalUtilz, int nTotalUtilzAval, int nTotalUtilzNaoAval, int nReviewsSemImpac) {
		StringBuilder sb = new StringBuilder();
		sb.append("Nome do ficheiro: " + nomeFicheiro + "\n");
		sb.append("Numero de reviews erradas: " + nReviewsErradas + "\n");
		sb.append("Numero total de negocios: " + nTotalBizs + "\n");
		sb.append("Numero de negocios avaliados: " + nBizsAval + "\n");
		sb.append("Numero de negocios nao avaliados: " + nBizsNaoAval + "\n");
		sb.append("Numero total de utilizadores: " + nTotalUtilz + "\n");
		sb.append("Numero de utilizadores que avaliaram: " + nTotalUtilzAval + "\n");
		sb.append("Numero de utilizadores que nao avaliaram: " + nTotalUtilzNaoAval + "\n");
		sb.append("Numero de reviews sem impacto: " + nReviewsSemImpac + "\n");
		System.out.print(sb.toString());
	}

	public static void printEstatisticas2(Map<Integer, List<Integer>> numeroDeReviewsPorMes,
										  AbstractMap.SimpleEntry<Map<Integer, Map<Integer, Double>>, Double> mediaClassificacaoPorMes
										  , Map<Integer, Map<Integer, Integer>> numeroDistintoDeUtilizadoresPorMes){
		StringBuilder sb = new StringBuilder();
		sb.append("Numero de Reviews por mes: \n");
		for (Map.Entry<Integer, List<Integer>> m : numeroDeReviewsPorMes.entrySet()){
			sb.append("  Ano: " + m.getKey() + " -> " + m.getValue().toString() + "\n");
		}
		sb.append("Media de classificação por mes: \n");
		for (Map.Entry<Integer, Map<Integer, Double>> m : mediaClassificacaoPorMes.getKey().entrySet()){
			sb.append("  Ano: " + m.getKey() + "\n");
			for (Map.Entry<Integer, Double> m2 : m.getValue().entrySet()){
				sb.append("    Mes: " + m2.getKey() + " -> " + (String.format("%.2f", m2.getValue())) + "\n");
			}
		}
		sb.append("Media global das reviews: " + (String.format("%.2f", mediaClassificacaoPorMes.getValue()))+ "\n");
		sb.append("Numero distinto de utilizadores por mes: \n");
		for (Map.Entry<Integer, Map<Integer, Integer>> m : numeroDistintoDeUtilizadoresPorMes.entrySet()){
			sb.append("  Ano:" + m.getKey() + "\n");
			for (Map.Entry<Integer, Integer> m2 : m.getValue().entrySet()){
				sb.append("    Mes: " + m2.getKey() + " -> " + m2.getValue() + "\n");
			}
		}
		System.out.print(sb.toString());
	}

	public static void printMainMenu() {
		StringBuilder sb = new StringBuilder();
		sb.append("\033[33m+----------Main-Menu----------+\n");
		sb.append("\033[33m1.\033[0m	Queries\n");
		sb.append("\033[33m2.\033[0m	Estatísticas\n");
		sb.append("\033[33m3.\033[0m	Load\n");
		sb.append("\033[33m4.\033[0m	Load (ObjectStream)\n");
		sb.append("\033[33m5.\033[0m	Save (ObjectStream)\n");
		sb.append("\033[33m6.\033[0m	Quit\n");
		System.out.print(sb.toString());
	}

	public static void printQueries() {
		StringBuilder sb = new StringBuilder();
		sb.append("\033[33m+----------Queries----------+\n");
		sb.append("\033[33m1.\033[0m	Negócios nunca avaliados\n");
		sb.append("\033[33m2.\033[0m	Nº de review e users no mês dado\n");
		sb.append("\033[33m3.\033[0m	Reviews, negócios e média de um user por mês\n");
		sb.append("\033[33m4.\033[0m	Reviews, users e média de um negócio por mês\n");
		sb.append("\033[33m5.\033[0m	Negócios mais avaliados por um user\n");
		sb.append("\033[33m6.\033[0m	Top X negócios mais avaliados por ano\n");
		sb.append("\033[33m7.\033[0m	Top 3 negócios mais avaliados por cidade\n");
		sb.append("\033[33m8.\033[0m	Top X users que avaliaram mais negócios\n");
		sb.append("\033[33m9.\033[0m	Top X users que mais avaliaram um negócio\n");
		sb.append("\033[33m10.\033[0m	Média de todos os negócios\n");
		sb.append("\033[33m11.\033[0m	Go back\n");
		System.out.print(sb.toString());
	}

	public static void closeScanner() {
		input.close();
	}

	public static String getString() {
		input = new Scanner(System.in);
		String result = input.nextLine();
		return result;
	}

	public static String getString(String question) {
		System.out.print(question);
		return UI.getString();
	}

	public static int getInt() {
		int result = Integer.parseInt(UI.getString());
		return result;
	}

	public static int getInt(String question) {
		int result = Integer.parseInt(UI.getString(question));
		return result;
	}

	public static void printError(String message) {
		StringBuilder sb = new StringBuilder("\033[31m[ERROR] \033[0m" + message);
		System.out.print(sb.toString());
	}

	public static void print(String message) {
		System.out.print(message);
	}

	public static void printList1(List<String> lista) {
		int x = 0;
		String command;
		while (true) {
			lista.subList(x, Math.min( lista.size()-1,x+20)).forEach(System.out::println);
			command = UI.getString("< , > , q :");
			if (command.equals("<")) x = max(0,x-20);
			if (command.equals(">") && x+20 < lista.size() -1) x = x+20;
			if (command.equals("q")) break;
		}
	}

	public static void printList2(List<AbstractMap.SimpleEntry<String, Integer>> lista) {
		int x = 0;
		String command;
		while (true) {
			lista.subList(x, Math.min( lista.size()-1,x+20)).forEach(System.out::println);
			command = UI.getString("< , > , q :");
			if (command.equals("<")) x = max(0,x-20);
			if (command.equals(">") && x+20 < lista.size() -1) x = x+20;
			if (command.equals("q")) break;
		}
	}

	public static void printList3(List<AbstractMap.SimpleEntry<String, Double>> lista) {
		int x = 0;
		String command;
		while (true) {
			lista.subList(x, Math.min( lista.size()-1,x+20)).forEach(System.out::println);
			command = UI.getString("< , > , q :");
			if (command.equals("<")) x = max(0,x-20);
			if (command.equals(">") && x+20 < lista.size() -1) x = x+20;
			if (command.equals("q")) break;
		}
	}


	public static void printMap1(Map<Integer, auxConsulta> map) {
		for (Map.Entry<Integer, auxConsulta> m : map.entrySet()){
			System.out.println("Mes: " + m.getKey() + " -> " + m.getValue());
		}
	}
	public static void printMap2(Map<Integer, List<AbstractMap.SimpleEntry<String, Integer>>> map){
		List<Integer> sortedKey = map.keySet().stream().sorted(Integer :: compareTo).collect(Collectors.toList());
		for(int i = 0; i < map.size(); i++){
			Integer key = sortedKey.get(i);
			System.out.println("Ano: " + key + " -> " + map.get(key));
		}
	}

	public static void printMap3(Map<String, List<String>> map){
		String command;
		int x = 1;
		for (Map.Entry<String, List<String>> m : map.entrySet()){
			System.out.println("Cidade: " + m.getKey() + " -> " + m.getValue());
			if (x%15 == 0) {
				command = UI.getString(">, q :");
				if (command.equals("q")) break;
			}
			x++;
		}
	}

	public static void printMap4(Map<String, Map<String, List<AbstractMap.SimpleEntry<String, Double>>>> map){
		String command;
		for (Map.Entry<String, Map<String, List<AbstractMap.SimpleEntry<String, Double>>>> m : map.entrySet()){
			System.out.println("Estado: " + m.getKey());
			for(Map.Entry<String, List<AbstractMap.SimpleEntry<String, Double>>>m2 : m.getValue().entrySet()) {
				System.out.println("  Cidade: " + m2.getKey());
				for(AbstractMap.SimpleEntry<String, Double> m3 : m2.getValue()){
					System.out.println("    Negócio : " + m3.getKey() + " -> " + String.format("%.2f", m3.getValue())) ;
				}
			}
			command = UI.getString(">, q :");
			if (command.equals("q")) break;
		}
	}


	public static void printTime() {
		Crono.printElapsedTime();
	}
}
