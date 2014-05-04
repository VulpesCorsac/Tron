#ifndef POLYGON2D_HPP_INCLUDED
#define POLYGON2D_HPP_INCLUDED

template < class T >
class Polygon2D {
public:
    std::vector < Point2D < T > > Polygon;

    Polygon2D() {
        this->Polygon.clear();
    }

    Polygon2D(const std::vector < Point2D < T > > &_Polygon) {
        this->Polygon = _Polygon;
    }

    ~Polygon2D() {
        this->Polygon.clear();
    }

    Polygon2D &operator = (const Polygon2D &_Polygon) {
        if (this == &_Polygon)
            return *this;
        this->Polygon = _Polygon.Polygon;
        return *this;
    }

    friend bool operator == (const Polygon2D &Polygon1, const Polygon2D &Polygon2) {
        if (Polygon1.Polygon.size() != Polygon2.Polygon.size())
            return false;
        int matches = 0;
        for (size_t i = 0; i < Polygon1.Polygon.size(); i++)
            for (size_t j = 0; j < Polygon2.Polygon.size(); j++)
                if (Polygon1.Polygon[i] == Polygon2.Polygon[j])
                    matches++;
        if (matches == Polygon1.Polygon.size())
            return true;
        return false;
    }

    friend bool operator != (const Polygon2D &Polygon1, const Polygon2D &Polygon2) {
        return (!(Polygon1 == Polygon2));
    }

    friend std::ostream& operator << (std::ostream& outputstream, const Polygon2D &_Polygon) {
        outputstream << "[";
        for (size_t i = 0; i < _Polygon.Polygon.size() - 1; i++)
            outputstream << _Polygon.Polygon[i] << ",";
        outputstream << _Polygon.Polygon[_Polygon.Polygon.size() - 1];
        outputstream << "]";
        return outputstream;
    }

    friend std::istream& operator >> (std::istream& inputstream, Polygon2D &_Polygon) {
        int N;
        inputstream >> N;
        _Polygon.Polygon.resize(N);
        for (size_t i = 0; i < _Polygon.Polygon.size(); i++)
            inputstream >> _Polygon.Polygon[i];
        return inputstream;
    }
};

#endif // POLYGON2D_HPP_INCLUDED
