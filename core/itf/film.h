#ifndef LB_FILM_H
#define LB_FILM_H

namespace lb {

class Sample;

class Film
{
    public:
        Film(int xResolution, int yResolution);

        int xResolution() const { return xResolution_; }
        int yResolution() const { return yResolution_; }

        /// Adds a sample to the film, thus this adds the calculated value for
        /// the light hitting the film at the given sample location.
        virtual void addSample(const Sample& sample, float l) = 0;

    protected:
        const int xResolution_;
        const int yResolution_;
};

}

#endif
