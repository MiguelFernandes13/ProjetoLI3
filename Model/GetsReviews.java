import BusinessF.BusinessCaT;
import ReviewsF.ReviewsCat;
import UsersF.UsersCat;

import java.io.*;
import java.util.AbstractMap;
import java.util.List;
import java.util.Map;

public class GetsReviews implements Serializable{
    private ReviewsCat reviews;
    private BusinessCaT bizs;
    private UsersCat users;

    public GetsReviews(ReviewsCat reviews, BusinessCaT bizs, UsersCat users) {
        this.reviews = reviews;
        this.bizs = bizs;
        this.users = users;
    }

    public ReviewsCat getReviews(){
        return this.reviews;
    }

    public BusinessCaT getBizs(){
        return this.bizs;
    }

    public UsersCat getUsers() {
        return users;
    }

    public void saveToBinary(String fn) throws IOException {
        ObjectOutputStream os = new ObjectOutputStream(new FileOutputStream(fn));
        os.writeObject(this);
        os.close();
    }

    public static GetsReviews readFromBinary(String fn)
            throws IOException, FileNotFoundException, ClassNotFoundException {
        ObjectInputStream is = new ObjectInputStream(new FileInputStream(fn));
        GetsReviews r = (GetsReviews) is.readObject();
        is.close();
        return r;
    }
}
