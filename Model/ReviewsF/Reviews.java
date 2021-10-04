package ReviewsF;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.Objects;
import java.util.Set;

public class Reviews implements Serializable, iReviews {
    private String review_id;
    private String user_id;
    private String business_id;
    private double stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String text;

    public Reviews(String line) {
        String[] c = line.split(";", 9);
        this.review_id = c[0];
        this.user_id = c[1];
        this.business_id = c[2];
        this.stars = Double.parseDouble(c[3]);
        this.useful = Integer.parseInt(c[4]);
        this.funny = Integer.parseInt(c[5]);
        this.cool = Integer.parseInt(c[6]);
        String data = c[7];
        String data2[] = data.split(" ", 2);
        String data3[] = data2[0].split("-", 3);
        String data4[] = data2[1].split(":", 3);
        this.date = LocalDateTime.of(Integer.parseInt(data3[0]), Integer.parseInt(data3[1]), Integer.parseInt(data3[2]),
                Integer.parseInt(data4[0]), Integer.parseInt(data4[1]), Integer.parseInt(data4[2]));
        this.text = c[8];

    }

    public Reviews(String review_id, String user_id, String business_id, double stars, int useful, int funny, int cool,
            LocalDateTime date, String text) {
        this.review_id = review_id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;
    }

    public Reviews(Reviews reviews) {
        this.review_id = reviews.getReview_id();
        this.user_id = reviews.getUser_id();
        this.business_id = reviews.getBusiness_id();
        this.stars = reviews.getStars();
        this.useful = reviews.getUseful();
        this.funny = reviews.getFunny();
        this.cool = reviews.getCool();
        this.date = reviews.getDate();
        this.text = reviews.getText();
    }

    public String getReview_id() {
        return this.review_id;
    }

    public void setReview_id(String review_id) {
        this.review_id = review_id;
    }

    public String getUser_id() {
        return this.user_id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public String getBusiness_id() {
        return this.business_id;
    }

    public void setBusiness_id(String business_id) {
        this.business_id = business_id;
    }

    public double getStars() {
        return this.stars;
    }

    public void setStars(Double stars) {
        this.stars = stars;
    }

    public int getUseful() {
        return this.useful;
    }

    public void setUseful(int useful) {
        this.useful = useful;
    }

    public int getFunny() {
        return this.funny;
    }

    public void setFunny(int funny) {
        this.funny = funny;
    }

    public int getCool() {
        return this.cool;
    }

    public void setCool(int cool) {
        this.cool = cool;
    }

    public LocalDateTime getDate() {
        return this.date;
    }

    public void setDate(LocalDateTime date) {
        this.date = date;
    }

    public String getText() {
        return this.text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public Reviews clone() {
        return new Reviews(this);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof Reviews)) {
            return false;
        }
        Reviews reviews = (Reviews) o;
        return Objects.equals(review_id, reviews.review_id) && Objects.equals(user_id, reviews.user_id)
                && Objects.equals(business_id, reviews.business_id) && stars == reviews.stars
                && useful == reviews.useful && funny == reviews.funny && cool == reviews.cool
                && Objects.equals(date, reviews.date) && Objects.equals(text, reviews.text);
    }

    /*@Override
    public int hashCode() {
        return Objects.hash(review_id, user_id, business_id, stars, useful, funny, cool, date, text);
    }*/

    @Override
    public String toString() {
        return "{" + " review_id='" + getReview_id() + "'" + ", user_id='" + getUser_id() + "'" + ", business_id='"
                + getBusiness_id() + "'" + ", stars='" + getStars() + "'" + ", useful='" + getUseful() + "'"
                + ", funny='" + getFunny() + "'" + ", cool='" + getCool() + "'" + ", date='" + getDate() + "'"
                + ", text='" + getText() + "'" + "}";
    }

}
