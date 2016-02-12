// ****
// *
// * Defines for particular properties of the simulation and definition of the parameters structure
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 21/12/2012
// *
// ****


#include "config.h"

#include "../../Heating_Model/source/heat.h"
#include "../../Radiation_Model/source/ionfrac.h"
#include "../../Radiation_Model/source/radiation.h"
#include "../../Radiation_Model/source/OpticallyThick/OpticallyThickIon.h"
#include "../../Kinetic_Model/source/kinetic.h"

// **** PARAMETERS STRUCTURE ****

// Define the parameters structure
struct Parameters {

    // Initial (t=0) loop density, momentum density and energy density profiles
    char Profiles[256];

    // Loop length
    double L;

    // Gravity look-up table filename
    char GravityFilename[256];

    // Duration and profile output period
    double Duration, OutputPeriod;
	
	//Output options
	int output_every_n_time_steps;
	bool write_file_physical, write_file_ion_populations, write_file_scales, write_file_terms;
	//Physics options
	int heated_species;
	double minimum_collisional_coupling_timescale
	bool non_equilibrium_radiation, use_power_law_radiative_losses, decouple_ionisation_state_solver, density_dependent_rates, optically_thick_radiation, use_kinetic_model, force_single_fluid;
	//Solver options
	double safety_radiation, safety_conduction, safety_advection, safety_viscosity, time_step_increase_limit, relative_viscous_time_scale, minimum_radiation_temperature, zero_over_temperature_interval, minimum_temperature;
	bool numerical_viscosity;
	//Grid Options
	bool adapt, refine_on_density, refine_on_electron_energy, refine_on_hydrogen_energy, linear_restriction, enforce_conservation;

};

// Define a type for the parameters structure
typedef Parameters PARAMETERS;
