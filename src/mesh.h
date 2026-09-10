#pragma once

/** \brief One dimmensional mesh.
*
* \author Zbigniew Romanowski [ROMZ@wp.pl]
*
*/


#include "element.h"

class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;

    void GenLin(double a, double b, size_t nodeNo, size_t degree);
    void AddToMesh(const std::vector<size_t>& eltToSplit);

    void Set(const std::vector<double>& x, size_t degree);

    void CreateCnnt();

    size_t Dim() const;
    size_t GetBand() const;

    const Element& Elt(size_t i) const { return m_elt[i];      }
    const Element& EltFront()    const { return m_elt.front(); }
    const Element& EltBack()     const { return m_elt.back();  }
    size_t EltNo()               const { return m_elt.size();  }

    double X(size_t i) const { return m_x[i];      }
    double XFront()    const { return m_x.front(); }
    double XBack()     const { return m_x.back();  }
    size_t XNo()       const { return m_x.size();  }

    bool IsInRange(double x) const;
    size_t FindElt(double x) const;

    void append_elt( double length );


private:
    // Array of elements
    std::vector<Element> m_elt;

    // vertex coordinates (the size one larger than m_elt.size())
    std::vector<double> m_x;
};
