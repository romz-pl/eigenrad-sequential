#include "create_potential.h"

#include <stdexcept>
#include "paramdb.h"
#include "potential_coulomb.h"
#include "potential_hgh_hydrogen.h"

static std::unique_ptr<potential_coulomb> create_coulomb()
{
    const double z = ParamDb::GetDouble( "potential_coulomb_Z" );
    return std::make_unique<potential_coulomb>(z);
}

static std::unique_ptr<potential_hgh_hydrogen> create_hgh_hydrogen()
{
    return std::make_unique<potential_hgh_hydrogen>();
}

std::unique_ptr<Fun1D> create_potential()
{
    const std::string potential_name = ParamDb::GetString( "potential_name" );

    if(potential_name == "coulomb")
        return create_coulomb();

    if(potential_name == "hgh_hydrogen")
        return create_hgh_hydrogen();

    throw std::invalid_argument("Unknown potenial: " + potential_name);

}