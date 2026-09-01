#include "create_potential.h"

#include <stdexcept>
#include "paramdb.h"
#include "potential_coulomb.h"

std::unique_ptr<potential_coulomb> create_coulomb()
{
    const double z = ParamDb::GetDouble( "potential_coulomb_Z" );
    return std::make_unique<potential_coulomb>(z);
}

std::unique_ptr<Fun1D> create_potential()
{
    const std::string potential_name = ParamDb::GetString( "potential_name" );

    if(potential_name == "Coulomb")
        return create_coulomb();

    throw std::invalid_argument("Unknown potenial: " + potential_name);

}