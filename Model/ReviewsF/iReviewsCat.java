package ReviewsF;

import java.util.Map;

public interface iReviewsCat {
    int getNumeroDeReviewsErradas();
    Map<String, Reviews> getAllReviews();
    ReviewsCat clone();
    boolean valid(String line);

}