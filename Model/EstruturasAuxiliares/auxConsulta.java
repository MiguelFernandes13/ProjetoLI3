package EstruturasAuxiliares;

import java.util.*;
import java.util.stream.Collectors;

public class auxConsulta {
    private Set<String> ids;
    private int nReviews;
    private int nReviewsDistintos;
    private double nEstrelas;
    private double media;

    public auxConsulta() {
        this.ids = new HashSet<>();
        this.nReviews = 0;
        this.nReviewsDistintos = 0;
        this.nEstrelas = 0.0;
        this.media = 0;
    }

    public auxConsulta(Set<String> ids, int nReviews, int nReviewsDistintos, double nEstrelas, double media) {
        this.ids = new HashSet<>(ids);
        this.nReviews = nReviews;
        this.nReviewsDistintos = nReviewsDistintos;
        this.nEstrelas = nEstrelas;
        this.media = media;
    }

    public Set<String> getIds() {
        return this.ids.stream().collect(Collectors.toSet());
    }

    public void setIds(Set<String> ids) {
        this.ids = new HashSet<>(ids);
    }

    public int getNReviews() {
        return this.nReviews;
    }

    public void setNReviews(int nReviews) {
        this.nReviews = nReviews;
    }

    public int getNReviewsDistintos() {
        return this.nReviewsDistintos;
    }

    public void setNReviewsDistintos(int nReviewsDistintos) {
        this.nReviewsDistintos = nReviewsDistintos;
    }

    public double getNEstrelas() {
        return this.nEstrelas;
    }

    public void setNEstrelas(double nEstrelas) {
        this.nEstrelas = nEstrelas;
    }

    public double getMedia() {
        return this.media;
    }

    public void setMedia(double media) {
        this.media = media;
    }

    public void addID(String id, double stars) {
        if (this.ids.add(id))
            this.nReviews++;
        this.nEstrelas += stars;
    }

    /*
     * public auxConsulta ids(List<String> ids) { setIds(ids); return this; }
     * 
     * public auxConsulta nReviews(int nReviews) { setNReviews(nReviews); return
     * this; }
     * 
     * public auxConsulta nReviewsDistintos(int nReviewsDistintos) {
     * setNReviewsDistintos(nReviewsDistintos); return this; }
     * 
     * public auxConsulta nEstrelas(double nEstrelas) { setNEstrelas(nEstrelas);
     * return this; }
     * 
     * public auxConsulta media(double media) { setMedia(media); return this; }
     */

    @Override
    public boolean equals(Object o) {
        if (o == this)
            return true;
        if (!(o instanceof auxConsulta)) {
            return false;
        }
        auxConsulta auxConsulta = (auxConsulta) o;
        return Objects.equals(ids, auxConsulta.ids) && nReviews == auxConsulta.nReviews
                && nReviewsDistintos == auxConsulta.nReviewsDistintos && nEstrelas == auxConsulta.nEstrelas
                && media == auxConsulta.media;
    }

    @Override
    public int hashCode() {
        return Objects.hash(ids, nReviews, nReviewsDistintos, nEstrelas, media);
    }

    @Override
    public String toString() {
        return "{" + " ids='" + this.getIds() + "'" + ", nReviews='" + this.getNReviews() + "'"
                + ", nReviewsDistintos='" + this.getIds().size() + "'" + ", media='"
                + String.format("%.2f",(this.getNEstrelas() / this.getNReviews())) + "'" + "}";
    }

}