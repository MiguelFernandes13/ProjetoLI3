package ReviewsF;

import BusinessF.Business;
import BusinessF.BusinessCaT;
import UsersF.Users;
import UsersF.UsersCat;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ReviewsCat implements Serializable, iReviewsCat {
    private Map<String, Reviews> allReviews;
    public int numeroDeReviewsErradas;

    public ReviewsCat(List<String> s) {
        this.allReviews = new HashMap<>();
        for (String l : s) {
            if (this.valid(l)) {
                Reviews n = new Reviews(l);
                this.allReviews.put(n.getReview_id(), n);
            } else {
                numeroDeReviewsErradas++;
            }
        }
    }

    public ReviewsCat(List<String> s, BusinessCaT bizs, UsersCat users) {
        this.allReviews = new HashMap<>();
        Map<String, Business> b = bizs.getAllBizs();
        Map<String, Users> u = users.getAllUsers();
        for (String l : s) {
            if (this.valid(l) ) {
                Reviews n = new Reviews(l);
                if (b.get(n.getBusiness_id()) != null && u.get(n.getUser_id()) != null) {
                    this.allReviews.put(n.getReview_id(), n);
                } else numeroDeReviewsErradas++;
            } else numeroDeReviewsErradas++;

        }
    }



    public ReviewsCat(ReviewsCat rc) {
        this.allReviews = rc.getAllReviews();
    }

    public Map<String, Reviews> getAllReviews() {
        return this.allReviews.entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey, e -> e.getValue().clone()));
    }

    public int getNumeroDeReviewsErradas() {
        return this.numeroDeReviewsErradas;
    }

    public ReviewsCat clone() {
        return new ReviewsCat(this);
    }

    public boolean valid(String line) {
        String[] c = line.split(";", -1);
        if (c.length != 9)
            return false;
        for (int i = 0; i < 8; i++) {
            if (c[i].isEmpty()) {
                return false;
            }
        }
        return true;
    }
}