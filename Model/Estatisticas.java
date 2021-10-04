import java.util.*;
import java.util.stream.Collectors;

import ReviewsF.Reviews;
import ReviewsF.ReviewsCat;
import BusinessF.Business;
import BusinessF.BusinessCaT;
import UsersF.UsersCat;
import UsersF.Users;

public class Estatisticas {

    private String nomeFicheiro;
    private Map<String, Reviews> reviews;
    private Map<String, Business> bizs;
    private Map<String, Users> users;
    private int reviewsErrados;

    public Estatisticas(String nomeFicheiro, ReviewsCat reviews, BusinessCaT bizs, UsersCat users) {
        this.nomeFicheiro = nomeFicheiro;
        this.reviews = reviews.getAllReviews().entrySet().stream()
                .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().clone(), (a, b) -> b, HashMap::new));
        this.bizs = bizs.getAllBizs().entrySet().stream()
                .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().clone(), (a, b) -> b, HashMap::new));
        this.users = users.getAllUsers().entrySet().stream()
                .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().clone(), (a, b) -> b, HashMap::new));
        this.reviewsErrados = reviews.getNumeroDeReviewsErradas();
    }

    public Estatisticas(String nomeFicheiro, ReviewsCat reviews, BusinessCaT bizs) {
        this.nomeFicheiro = nomeFicheiro;
        this.reviews = reviews.getAllReviews().entrySet().stream()
                .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().clone(), (a, b) -> b, HashMap::new));
        this.bizs = bizs.getAllBizs().entrySet().stream()
                .collect(Collectors.toMap(e -> e.getKey(), e -> e.getValue().clone(), (a, b) -> b, HashMap::new));
        this.users = new HashMap<>();
        this.reviewsErrados = reviews.getNumeroDeReviewsErradas();
    }

    public String nomeDoFicheiro() {
        return this.nomeFicheiro;
    }

    public int numReviewsErradas() {
        return this.reviewsErrados;
    }

    public int numTotalNegocios() {
        return this.bizs.values().size();
    }

    public int numNegociosAvaliados() {
        int contA = 0;
        Map<String, String> businessJaVisitados = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            if (businessJaVisitados.get(r.getBusiness_id()) == null) {
                businessJaVisitados.put(r.getBusiness_id(), r.getBusiness_id());
                contA++;
            }
        }
        return contA;
    }

    public int numNegociosNaoAvaliados() {
        int contNA = 0;
        Map<String, String> businessJaVisitados = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            if (businessJaVisitados.get(r.getBusiness_id()) == null) {
                businessJaVisitados.put(r.getBusiness_id(), r.getBusiness_id());
            }
        }
        for (String id : bizs.keySet()) {
            if (businessJaVisitados.get(id) == null)
                contNA++;
        }
        return contNA;
    }

    public int numTotaldeUtilizadores() {
        return this.users.values().size();
    }

    public int numTotaldeUtilizadoresQueAvaliaram() {
        int contA = 0;
        Map<String, String> usersQueJaAvaliaram = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            if (usersQueJaAvaliaram.get(r.getUser_id()) == null) {
                usersQueJaAvaliaram.put(r.getUser_id(), r.getUser_id());
                contA++;
            }
        }
        return contA;
    }

    public int numTotaldeUtilizadoresQueNaoAvaliaram() {
        int contNA = 0;
        Map<String, String> usersQueJaAvaliaram = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            if (usersQueJaAvaliaram.get(r.getUser_id()) == null) {
                usersQueJaAvaliaram.put(r.getUser_id(), r.getUser_id());
            }
        }
        for (String id : users.keySet()) {
            if (usersQueJaAvaliaram.get(id) == null)
                contNA++;
        }
        return contNA;
    }

    public int numTotaldeReviewsSemImpacto() {
        int contSI = 0;
        Map<String, Reviews> reviewsSemImpacto = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            if (r.getCool() + r.getFunny() + r.getUseful() == 0)
                reviewsSemImpacto.put(r.getReview_id(), r.clone());
            contSI++;
        }
        return contSI;
    }

    public Map<Integer, List<Integer>> numeroDeReviewsPorMes() {
        Map<Integer, List<Integer>> reviewsPorAnoPorMes = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            int ano = r.getDate().getYear();

            int mes = r.getDate().getMonthValue();
            reviewsPorAnoPorMes.putIfAbsent(ano, new ArrayList<>(Collections.nCopies(12, 0)));
            reviewsPorAnoPorMes.get(ano).set(mes - 1, reviewsPorAnoPorMes.get(ano).get(mes - 1) + 1);
        }
        return reviewsPorAnoPorMes;
    }

    public AbstractMap.SimpleEntry<Map<Integer, Map<Integer, Double>>, Double> mediaClassificacaoPorMes() {
        Map<Integer, Map<Integer, List<Double>>> nEstrelasReviewsPorAnoPorMes = new HashMap<>();
        double mediaGlobal = 0.0;
        int count = 0;
        for (Reviews r : this.reviews.values()) {
            int ano = r.getDate().getYear();
            int mes = r.getDate().getMonthValue();
            nEstrelasReviewsPorAnoPorMes.putIfAbsent(ano, new HashMap<>());
            Map<Integer, List<Double>> tmp = nEstrelasReviewsPorAnoPorMes.get(ano);
            tmp.putIfAbsent(mes, new ArrayList<>());
            tmp.get(mes).add(r.getStars());
        }
        Map<Integer, Map<Integer, Double>> result = new HashMap<>();
        for(Map.Entry<Integer, Map<Integer, List<Double>>> m : nEstrelasReviewsPorAnoPorMes.entrySet()){
            Map<Integer, Double> result2 = new HashMap<>();
            for(Map.Entry<Integer, List<Double>> m2 : m.getValue().entrySet()){
                double media =  m2.getValue().stream().mapToDouble(d->d).average().orElse(0.0);
                result2.put(m2.getKey(), media);
                mediaGlobal += media;
                count++;
            }
            result.put(m.getKey(), result2);
        }
        mediaGlobal = mediaGlobal/count;
        return new AbstractMap.SimpleEntry<>(result, mediaGlobal);
    }

    public Map<Integer, Map<Integer, Integer>> numeroDistintoDeUtilizadoresPorMes() {
        Map<Integer, Map<Integer, Set<String>>> numeroDistintosUtilizadoresPorAnoPorMes = new HashMap<>();
        for (Reviews r : this.reviews.values()) {
            int ano = r.getDate().getYear();
            int mes = r.getDate().getMonthValue();
            numeroDistintosUtilizadoresPorAnoPorMes.putIfAbsent(ano,
                    new HashMap<>());
            Map<Integer, Set<String>> tmp = numeroDistintosUtilizadoresPorAnoPorMes.get(ano);
            tmp.putIfAbsent(mes, new HashSet<>());
            tmp.get(mes).add(r.getReview_id());
            numeroDistintosUtilizadoresPorAnoPorMes.put(ano, tmp);
        }
        Map<Integer, Map<Integer, Integer>> result = new HashMap<>();
        for (Map.Entry<Integer, Map<Integer, Set<String>>> m : numeroDistintosUtilizadoresPorAnoPorMes.entrySet()) {
            Map<Integer, Integer> result2 = new HashMap<>();
            for (Map.Entry<Integer, Set<String>> m2 : m.getValue().entrySet()){
                result2.put(m2.getKey(), m2.getValue().size());
            }
            result.put(m.getKey(), result2);
        }
        return result;
    }

}
