#include "create_potential.h"

#include <stdexcept>
#include "paramdb.h"
#include "potential_coulomb.h"
#include "potential_hgh_hydrogen.h"
#include "potential_soft_coulomb.h"

static std::unique_ptr<potential_soft_coulomb> create_soft_coulomb();
static std::unique_ptr<potential_coulomb> create_coulomb();
static std::unique_ptr<potential_hgh_hydrogen> create_hgh_hydrogen();


std::unique_ptr<Fun1D> create_potential()
{
    const std::string potential_name = ParamDb::GetString( "potential_name" );

    if(potential_name == "coulomb")
        return create_coulomb();

    if(potential_name == "hgh_hydrogen")
        return create_hgh_hydrogen();

    if(potential_name == "soft_coulomb")
        return create_soft_coulomb();

    throw std::invalid_argument("Unknown potenial: " + potential_name);

}

std::unique_ptr<potential_coulomb> create_coulomb()
{
    const double z = ParamDb::GetDouble( "potential_coulomb_Z" );
    return std::make_unique<potential_coulomb>(z);
}

std::unique_ptr<potential_hgh_hydrogen> create_hgh_hydrogen()
{
    return std::make_unique<potential_hgh_hydrogen>();
}

std::unique_ptr<potential_soft_coulomb> create_soft_coulomb()
{
    const double Z = ParamDb::GetDouble( "potential_soft_coulomb_Z" );
    const double a = ParamDb::GetDouble( "potential_soft_coulomb_a" );
    const double q = ParamDb::GetDouble( "potential_soft_coulomb_q" );
    return std::make_unique<potential_soft_coulomb>(Z, a, q);
}

