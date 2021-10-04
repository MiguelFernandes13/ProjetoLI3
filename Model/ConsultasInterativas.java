import BusinessF.Business;
import BusinessF.BusinessCaT;
import EstruturasAuxiliares.ListOfStringInt;
import EstruturasAuxiliares.auxConsulta;
import ReviewsF.Reviews;
import ReviewsF.ReviewsCat;
import UsersF.UsersCat;

import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

public class ConsultasInterativas {
    private ReviewsCat reviews;
    private BusinessCaT bizs;

    public ConsultasInterativas(ReviewsCat reviews, BusinessCaT bizs) {
        this.reviews = reviews;
        this.bizs = bizs;
    }

    public ConsultasInterativas(List<String> revs1, List<String> revs2) {
        this.reviews = new ReviewsCat(revs1);
        this.bizs = new BusinessCaT(revs2);
    }

    public AbstractMap.SimpleEntry<List<String>, Integer> consulta1() {
        Set<String> r = new HashSet<>(this.bizs.getAllBizs().keySet());
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            r.remove(rev.getBusiness_id());
        }
        return new AbstractMap.SimpleEntry<>(r.stream().sorted(String::compareTo).collect(Collectors.toList()),
                r.size());
    }

    public AbstractMap.SimpleEntry<List<String>, Integer> consulta1List() {
        List<String> r = new ArrayList<>(new ArrayList<>(this.bizs.getAllBizs().keySet()));
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            r.remove(rev.getBusiness_id());
        }
        return new AbstractMap.SimpleEntry<>(r.stream().sorted(String::compareTo).collect(Collectors.toList()),
                r.size());
    }

    public AbstractMap.SimpleEntry<Integer, Integer> consulta2(int mes, int ano) {
        Set<String> usersRep = new HashSet<>();
        int sameData = 0, usersDif = 0;
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            LocalDateTime d = rev.getDate();
            if (d.getYear() == ano && d.getMonthValue() == mes) {
                sameData++;
                String u_id = rev.getUser_id();
                if (!usersRep.contains(u_id)) {
                    usersRep.add(u_id);
                    usersDif++;
                }
            }
        }
        return new AbstractMap.SimpleEntry<>(sameData, usersDif);
    }

    public AbstractMap.SimpleEntry<Integer, Integer> consulta2List(int mes, int ano) {
        List<String> usersRep = new ArrayList<>();
        int sameData = 0, usersDif = 0;
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            LocalDateTime d = rev.getDate();
            if (d.getYear() == ano && d.getMonthValue() == mes) {
                sameData++;
                String u_id = rev.getUser_id();
                if (!usersRep.contains(u_id)) {
                    usersRep.add(u_id);
                    usersDif++;
                }
            }
        }
        return new AbstractMap.SimpleEntry<>(sameData, usersDif);
    }

    public Map<Integer, auxConsulta> consulta3(String user_id) {
        Map<Integer, auxConsulta> userMes = new HashMap<>();
        for (Reviews r : this.reviews.getAllReviews().values()) {
            int mes = r.getDate().getMonthValue();
            if (r.getUser_id().equals(user_id)) {
                userMes.putIfAbsent(mes, new auxConsulta());
                auxConsulta tmp = userMes.get(mes);
                tmp.addID(r.getBusiness_id(), r.getStars());
            }
        }
        return userMes;
    }

    public Map<Integer, auxConsulta> consulta4(String business_id) {
        Map<Integer, auxConsulta> businessMes = new HashMap<>();
        for (Reviews r : this.reviews.getAllReviews().values()) {
            int mes = r.getDate().getMonthValue();
            if (r.getBusiness_id().equals(business_id)) {
                businessMes.putIfAbsent(mes, new auxConsulta());
                auxConsulta tmp = businessMes.get(mes);
                tmp.addID(r.getUser_id(), r.getStars());
            }
        }
        return businessMes;
    }

    public List<String> consulta5(String user_id) {
        Map<String, Integer> c5 = new TreeMap<>();
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            String id = rev.getUser_id();
            if (id.equals(user_id)) {
                c5.putIfAbsent(rev.getBusiness_id(), 0);
                c5.put(rev.getBusiness_id(), c5.get(rev.getBusiness_id()) + 1);
            }
        }

        Comparator<Map.Entry<String, Integer>> cmp = (o1, o2) -> {
            int r = o2.getValue() - o1.getValue();
            if (r == 0)
                r = o1.getKey().compareTo(o2.getKey());
            return r;
        };

        return c5.entrySet().stream().sorted(cmp).map(Map.Entry::getKey).collect(Collectors.toList());
    }

    public Map<Integer, List<AbstractMap.SimpleEntry<String, Integer>>> consulta6(int x) {
        Map<Integer, Map<String, Set<String>>> r = new HashMap<>();
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            int year = rev.getDate().getYear();
            r.putIfAbsent(year, new TreeMap<>());
            Map<String, Set<String>> tmp = r.get(year);
            tmp.putIfAbsent(rev.getBusiness_id(), new HashSet<>());
            tmp.get(rev.getBusiness_id()).add(rev.getUser_id());
        }

        Map<Integer, List<AbstractMap.SimpleEntry<String, Integer>>> res = new HashMap<>();
        for (Map.Entry<Integer, Map<String, Set<String>>> m : r.entrySet()) {
            List<AbstractMap.SimpleEntry<String, Integer>> ord = ListOfStringInt.sortList(new StringSetMapComparator(), m);
            res.put(m.getKey(), ord.subList(0, Math.min(ord.size(), x)));
        }
        return res;
    }

    public Map<String, List<String>> consulta7() {
        Map<String, Map<String, Integer>> r = new HashMap<>();
        Map<String, Business> allBizs = bizs.getAllBizs();
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            Business b = allBizs.get(rev.getBusiness_id());
            if (b != null) {
                String cidade = b.getCity().toLowerCase(Locale.ROOT);
                r.putIfAbsent(cidade, new TreeMap<>());
                Map<String, Integer> tmp = r.get(cidade);
                tmp.putIfAbsent(rev.getBusiness_id(), 0);
                tmp.put(rev.getBusiness_id(), tmp.get(rev.getBusiness_id()) + 1);
            }
        }
        Map<String, List<String>> result = new HashMap<>();
        for (Map.Entry<String, Map<String, Integer>> m : r.entrySet()) {
            List<String> rr = m.getValue().entrySet().stream().sorted((c1, c2) -> c2.getValue() - c1.getValue())
                    .map(Map.Entry::getKey).collect(Collectors.toList());
            rr = rr.subList(0, Math.min(3, rr.size()));
            result.put(m.getKey(), rr);
        }
        return result;
    }

    public List<AbstractMap.SimpleEntry<String, Integer>> consulta8(int x) {
        Map<String, Set<String>> r = new HashMap<>();
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            r.putIfAbsent(rev.getUser_id(), new TreeSet<>());
            r.get(rev.getUser_id()).add(rev.getBusiness_id());
        }
        List<AbstractMap.SimpleEntry<String, Integer>> c8 = r.entrySet().stream()
                .sorted((c1, c2) -> c2.getValue().size() - c1.getValue().size())
                .map(e -> new AbstractMap.SimpleEntry<>(e.getKey(), e.getValue().size())).collect(Collectors.toList());
        return c8.subList(0, Math.min(x+1, c8.size()));
    }

    public List<AbstractMap.SimpleEntry<String, Double>> consulta9(String business_id, int x) {
        Map<String, List<Double>> c9 = new TreeMap<>();
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            String id = rev.getBusiness_id();
            if (id.equals(business_id)) {
                c9.putIfAbsent(rev.getUser_id(), new ArrayList<>());
                c9.get(rev.getUser_id()).add(rev.getStars());
            }
        }
        Comparator<Map.Entry<String, List<Double>>> cmp = (o1, o2) -> {
            int r = o2.getValue().size() - o1.getValue().size();
            if (r == 0)
                r = o1.getKey().compareTo(o2.getKey());
            return r;
        };
        List<String> r = c9.entrySet().stream().sorted(cmp).map(Map.Entry::getKey).collect(Collectors.toList());

        return r.subList(0, Math.min(x+1, r.size())).stream().map(
                c -> new AbstractMap.SimpleEntry<>(c, c9.get(c).stream().mapToDouble(d -> d).average().orElse(0.0)))
                .sorted((c1, c2) -> Double.compare(c2.getValue(), c1.getValue())).collect(Collectors.toList());
    }

    public Map<String, Map<String, List<AbstractMap.SimpleEntry<String, Double>>>> consulta10() {
        Map<String, Map<String, Map<String, List<Double>>>> r = new HashMap<>();
        Map<String, Business> bCat = this.bizs.getAllBizs();
        for (Reviews rev : this.reviews.getAllReviews().values()) {
            Business b = bCat.get(rev.getBusiness_id());
            if (b != null) {
                String state = b.getState().toUpperCase();
                String city = b.getCity().toLowerCase();
                r.putIfAbsent(state, new TreeMap<>());

                Map<String, Map<String, List<Double>>> tmp = r.get(state);
                tmp.putIfAbsent(city, new HashMap<>());

                Map<String, List<Double>> tmp2 = tmp.get(city);
                tmp2.putIfAbsent(b.getBusiness_id(), new ArrayList<>());
                tmp2.get(b.getBusiness_id()).add(rev.getStars());

                tmp.put(city, tmp2);
            }
        }
        Map<String, Map<String, List<AbstractMap.SimpleEntry<String, Double>>>> res = new HashMap<>();
        for (Map.Entry<String, Map<String, Map<String, List<Double>>>> m : r.entrySet()) {
            Map<String, List<AbstractMap.SimpleEntry<String, Double>>> res2 = new HashMap<>();
            for (Map.Entry<String, Map<String, List<Double>>> m2 : m.getValue().entrySet()) {
                List<AbstractMap.SimpleEntry<String, Double>> res3 = new ArrayList<>();
                for (Map.Entry<String, List<Double>> m3 : m2.getValue().entrySet()) {
                    double d = m3.getValue().stream().mapToDouble(e -> e).average().orElse(0.0);
                    res3.add(new AbstractMap.SimpleEntry<>(m3.getKey(), d));
                }
                res2.put(m2.getKey(), res3);
            }
            res.put(m.getKey(), res2);
        }
        return res;
    }
}
