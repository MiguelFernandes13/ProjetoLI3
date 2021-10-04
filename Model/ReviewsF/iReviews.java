package ReviewsF;

import java.time.LocalDateTime;
import java.util.Set;

public interface iReviews {
    String getReview_id();
    void setReview_id(String review_id);
    String getUser_id();
    void setUser_id(String user_id);
    String getBusiness_id();
    void setBusiness_id(String business_id);
    double getStars();
    void setStars(Double stars);
    int getUseful();
    void setUseful(int useful);
    int getFunny();
    void setFunny(int funny);
    int getCool();
    void setCool(int cool);
    LocalDateTime getDate();
    void setDate(LocalDateTime date);
    String getText();
    void setText(String text);
    Reviews clone();
    boolean equals(Object o);
}