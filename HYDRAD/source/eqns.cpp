// ****
// *
// * Function bodies for the class definition of the
// * time-dependent hydrodynamic equations, inherited by the
// * adaptive mesh class
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 11/24/2015
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "eqns.h"
#include "../../rsp_toolkit/source/constants.h"
#include "../../rsp_toolkit/source/file.h"
#include "../../rsp_toolkit/source/fitpoly.h"
#include "../../rsp_toolkit/source/xmlreader.h"


double fLogLambda_ei( double Te, double Ti, double n )
{
double limit;

Te *= 1.29199251618e-4;
Ti *= 1.29199251618e-4;

limit = Ti * ( ELECTRON_MASS / AVERAGE_PARTICLE_MASS );

if( limit < Te && Te < 10.0 )
{
    return 23.0 - log( sqrt( n ) * pow( Te, (-1.5) ) );
}
else if( limit < 10.0 && 10.0 < Te )
{
    return 24.0 - log( sqrt( n ) * ( 1.0 / Te ) );
}
else // if( Te < limit )
{
    return 30.0 - log( sqrt( n ) * pow( Ti, (-1.5) ) );
}
}

double fLogLambda_ii( double Ti, double n )
{
double term1;

// Assume that proton-proton collisions dominate ion-ion interactions
// sqrt(2.0) * Z^3 = 1.4142135623730950488016887242097 * 1.0 * 1.0 * 1.0
term1 = 1.4142135623730950488016887242097 * ( sqrt( n ) / pow( Ti, 1.5 ) );
return 23.0 - log( term1 );
}


// Constructor
CEquations::CEquations( char *configFilename, char *rad_config_eqFilename, char *rad_config_neqFilename )
{

	//Call initialiser
	Initialise(configFilename, rad_config_eqFilename, rad_config_neqFilename);
}

// Destructor
CEquations::~CEquations( void )
{
FreeAll();
}

void CEquations::Initialise( char *configFilename, char *rad_config_eqFilename, char *rad_config_neqFilename )
{
FILE *pFile;
double fTemp;
int i, iTemp;
char kinetic_sh_table_filename[256];

tinyxml2::XMLDocument doc;

//Check if loaded
tinyxml2::XMLError loadOK = doc.LoadFile(configFilename);
if(loadOK != 0)
{
	printf("Failed to load XML configuration file %s.\n",configFilename);
	//TODO: Exit or break out from here
}

//Get Document root
tinyxml2::XMLElement *root = doc.FirstChildElement();

//Load in parameters
//Filenames
sprintf(Params.Profiles,"%s",check_element(recursive_read(root,"ic_profiles"),"ic_profiles")->GetText());
sprintf(Params.GravityFilename,"%s",check_element(recursive_read(root,"tabulated_gravity_file"),"tabulated_gravity_file")->GetText());
Params.Duration = atof(check_element(recursive_read(root,"duration"),"duration")->GetText());
//Output options
sprintf(Params.output_dir,"%s",check_element(recursive_read(root,"output_dir"),"output_dir")->GetText());
Params.OutputPeriod = atof(check_element(recursive_read(root,"file_output_period"),"file_output_period")->GetText());
Params.output_every_n_time_steps = atoi(check_element(recursive_read(root,"output_every_n_time_steps"),"output_every_n_time_steps")->GetText());
Params.write_file_physical = string2bool(check_element(recursive_read(root,"write_file_physical"),"write_file_physical")->GetText());
Params.write_file_ion_populations = string2bool(check_element(recursive_read(root,"write_file_ion_populations"),"write_file_ion_populations")->GetText());
Params.write_file_scales = string2bool(check_element(recursive_read(root,"write_file_scales"),"write_file_scales")->GetText());
Params.write_file_terms = string2bool(check_element(recursive_read(root,"write_file_terms"),"write_file_terms")->GetText());
//Physics options
Params.heated_species = atoi(check_element(recursive_read(root,"heated_species"),"heated_species")->GetText());
Params.minimum_collisional_coupling_time_scale = atof(check_element(recursive_read(root,"minimum_collisional_coupling_time_scale"),"minimum_collisional_coupling_time_scale")->GetText());
Params.non_equilibrium_radiation = string2bool(check_element(recursive_read(root,"non_equilibrium_radiation"),"non_equilibrium_radiation")->GetText());
Params.use_power_law_radiative_losses = string2bool(check_element(recursive_read(root,"use_power_law_radiative_losses"),"use_power_law_radiative_losses")->GetText());
Params.decouple_ionisation_state_solver = string2bool(check_element(recursive_read(root,"decouple_ionisation_state_solver"),"decouple_ionisation_state_solver")->GetText());
Params.density_dependent_rates = string2bool(check_element(recursive_read(root,"density_dependent_rates"),"density_dependent_rates")->GetText());
Params.optically_thick_radiation = string2bool(check_element(recursive_read(root,"optically_thick_radiation"),"optically_thick_radiation")->GetText());
Params.use_kinetic_model = string2bool(check_element(recursive_read(root,"use_kinetic_model"),"use_kinetic_model")->GetText());
Params.force_single_fluid = string2bool(check_element(recursive_read(root,"force_single_fluid"),"force_single_fluid")->GetText());
//solver options
Params.safety_radiation = atof(check_element(recursive_read(root,"safety_radiation"),"safety_radiation")->GetText());
Params.safety_conduction = atof(check_element(recursive_read(root,"safety_conduction"),"safety_conduction")->GetText());
Params.safety_advection = atof(check_element(recursive_read(root,"safety_advection"),"safety_advection")->GetText());
Params.safety_viscosity = atof(check_element(recursive_read(root,"safety_viscosity"),"safety_viscosity")->GetText());
Params.time_step_increase_limit = atof(check_element(recursive_read(root,"time_step_increase_limit"),"time_step_increase_limit")->GetText());
Params.relative_viscous_time_scale = atof(check_element(recursive_read(root,"relative_viscous_time_scale"),"relative_viscous_time_scale")->GetText());
Params.minimum_radiation_temperature = atof(check_element(recursive_read(root,"minimum_radiation_temperature"),"minimum_radiation_temperature")->GetText());
Params.zero_over_temperature_interval = atof(check_element(recursive_read(root,"zero_over_temperature_interval"),"zero_over_temperature_interval")->GetText());
Params.minimum_temperature = atof(check_element(recursive_read(root,"minimum_temperature"),"minimum_temperature")->GetText());
Params.numerical_viscosity = string2bool(check_element(recursive_read(root,"numerical_viscosity"),"numerical_viscosity")->GetText());
//grid options
Params.max_refinement_level = atoi(check_element(recursive_read(root,"max_refinement_level"),"max_refinement_level")->GetText());
Params.min_frac_diff = atof(check_element(recursive_read(root,"min_frac_diff"),"min_frac_diff")->GetText());
Params.max_frac_diff = atof(check_element(recursive_read(root,"max_frac_diff"),"max_frac_diff")->GetText());
Params.adapt = string2bool(check_element(recursive_read(root,"adapt"),"adapt")->GetText());
Params.refine_on_density = string2bool(check_element(recursive_read(root,"refine_on_density"),"refine_on_density")->GetText());
Params.refine_on_electron_energy = string2bool(check_element(recursive_read(root,"refine_on_electron_energy"),"refine_on_electron_energy")->GetText());
Params.refine_on_hydrogen_energy = string2bool(check_element(recursive_read(root,"refine_on_hydrogen_energy"),"refine_on_hydrogen_energy")->GetText());
Params.linear_restriction = string2bool(check_element(recursive_read(root,"linear_restriction"),"linear_restriction")->GetText());
Params.enforce_conservation = string2bool(check_element(recursive_read(root,"enforce_conservation"),"enforce_conservation")->GetText());

// Get the loop length from the profiles file
pFile = fopen( Params.Profiles, "r" );
ReadDouble( pFile, &fTemp );
fscanf( pFile, "%i", &iTemp );
ReadDouble( pFile, &Params.L );
fclose( pFile );

// Initialise the gravity look-up table
pFile = fopen( Params.GravityFilename, "r" );
fscanf( pFile, "%i", &igdp );
ppGravity = (double**)malloc( igdp * sizeof( double ) );
for( i=0; i<igdp; i++ )
{
    ppGravity[i] = (double*)malloc( 2 * sizeof( double ) );
    ReadDouble( pFile, &(ppGravity[i][0]) );
    ReadDouble( pFile, &(ppGravity[i][1]) );
}
fclose( pFile );

if(Params.use_kinetic_model)
{
	ppCellList = NULL;
	//Read in SH Table filename
	sprintf(kinetic_sh_table_filename,"%s",check_element(recursive_read(root,"kinetic_sh_table_filename"),"kinetic_sh_table_filename")->GetText());
	// Get the tabulated values from tables I and II (for Z = 1) in Spitzer & Harm, 1953, Phys. Rev., 89, 977
	Get_SH_Table(kinetic_sh_table_filename);
}

// Create the heating object and set the lower radiation temperature boundary
tinyxml2::XMLElement *heating_config = check_element(recursive_read(root,"heating"),"heating");
pHeat = new CHeat( heating_config, Params.L );

// Create the radiation objects
pRadiation = new CRadiation(rad_config_neqFilename,true);
pRadiation2 = new CRadiation(rad_config_eqFilename,true);
lower_radiation_temperature_boundary = Params.minimum_radiation_temperature + Params.zero_over_temperature_interval;

if(Params.optically_thick_radiation)
{
	// Create the optically-thick ion objects
	pHI = new COpticallyThickIon( 1, (char *)"h_1", pRadiation->atomicDBFilename );
	pMgII = new COpticallyThickIon( 12, (char *)"mg_2", pRadiation->atomicDBFilename );
	pCaII = new COpticallyThickIon( 20, (char *)"ca_2", pRadiation->atomicDBFilename );
}

//Free document tree
doc.Clear();

}

void CEquations::FreeAll( void )
{
int i;

if(Params.use_kinetic_model)
{
	free( ppCellList );
}

// Free the memory allocated to the gravity look-up table
for( i=0; i<igdp; i++ )
    free( ppGravity[i]);
free( ppGravity );

// Delete the heating object
delete pHeat;

// Delete the radiation objects
delete pRadiation;
delete pRadiation2;

if(Params.optically_thick_radiation)
{
	// Delete the optically-thick ion objects
	delete pHI;
	delete pMgII;
	delete pCaII;
}
}

void CEquations::CalculatePhysicalQuantities( void )
{
PCELL pNextActiveCell;
CELLPROPERTIES CellProperties;

// Variables used for calculation of thermal conduction time-scale
double Kappa[SPECIES];
Kappa[ELECTRON] = SPITZER_ELECTRON_CONDUCTIVITY;
Kappa[HYDROGEN] = SPITZER_ION_CONDUCTIVITY;

// General variables
double term1, term2;
int j;
double fHI;

pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

	if(Params.optically_thick_radiation)
    {
	    // Locate the apex cell from which the column densities will be calculated along each leg
	    if( CellProperties.s[1] <= Params.L / 2.0 )
	        pCentreOfCurrentRow = pActiveCell;
    }

// ******************************************************************************
// *                                                                            *
// *    CALCULATE THE PHYSICAL QUANTITIES                                       *
// *                                                                            *
// ******************************************************************************

    CellProperties.n[HYDROGEN] = CellProperties.rho[1] / AVERAGE_PARTICLE_MASS;

    CellProperties.v[1] = CellProperties.rho_v[1] / CellProperties.rho[1];

    term1 = CellProperties.TE_KE[1][HYDROGEN] / CellProperties.rho[1];
    term2 = 0.5 * CellProperties.v[1] * CellProperties.v[1];
    // GAMMA_MINUS_ONE / BOLTZMANN_CONSTANT = 4.830917874e15
    CellProperties.T[HYDROGEN] = (4.830917874e15) * AVERAGE_PARTICLE_MASS * ( term1 - term2 );

	if(Params.optically_thick_radiation)
    {
	    if( CellProperties.T[HYDROGEN] < OPTICALLY_THICK_TEMPERATURE )
	    {
	        // 1.44e-4 provides some negligible number of electrons to avoid division by zero errors
	        fHI = pHI->GetIonFrac( log10(CellProperties.T[HYDROGEN]) );
	        // 1.000144 = 1.0 + 1.44e-4
	        CellProperties.n[ELECTRON] = ( 1.000144 - fHI ) * CellProperties.n[HYDROGEN];
	    }
	    else
	    {
	        // 1.000144 = 1.0 + 1.44e-4
	        CellProperties.n[ELECTRON] = 1.000144 * CellProperties.n[HYDROGEN];
	    }
    }
	else
    {
		CellProperties.n[ELECTRON] = CellProperties.n[HYDROGEN];
	}
    // GAMMA_MINUS_ONE / BOLTZMANN_CONSTANT = 4.830917874e15
    CellProperties.T[ELECTRON] = ( (4.830917874e15) * CellProperties.TE_KE[1][ELECTRON] ) / CellProperties.n[ELECTRON] ;

    // Temperature limiter
    for( j=0; j<SPECIES; j++ )
    {
        if( CellProperties.T[j] < Params.minimum_temperature )
		{
            CellProperties.T[j] = Params.minimum_temperature;
            // BOLTZMANN_CONSTANT / GAMMA_MINUS_ONE = 2.07e-16
            CellProperties.TE_KE[1][j] = (2.07e-16) * CellProperties.n[j] * CellProperties.T[j];

            if( j == HYDROGEN )
                CellProperties.TE_KE[1][j] += 0.5 * CellProperties.rho_v[1] * CellProperties.v[1];
        }
    }

    for( j=0; j<SPECIES; j++ )
    {
        CellProperties.P[1][j] = BOLTZMANN_CONSTANT * CellProperties.n[j] * CellProperties.T[j];
		CellProperties.TE_KE_P[1][j] = CellProperties.TE_KE[1][j] + CellProperties.P[1][j];
    }

    term1 = ( GAMMA * ( CellProperties.P[1][ELECTRON] + CellProperties.P[1][HYDROGEN] ) ) / CellProperties.rho[1];
    CellProperties.Cs = pow( term1, 0.5 );
    CellProperties.M = fabs( CellProperties.v[1] / CellProperties.Cs );

// ******************************************************************************
// *                                                                            *
// *    CALCULATE THE TIMESCALES                                                *
// *                                                                            *
// ******************************************************************************

// ******************************************************************************
// *    COLLISIONS                                                              *
// ******************************************************************************

	if(Params.force_single_fluid)
    {
    	CellProperties.nu_ie = 1.0 / Params.minimum_collisional_coupling_time_scale;
    }
	else
    {
	    // Calculate the collision frequency between the electrons and ions
	    // 4.820055089755540 * ELECTRON_MASS = 4.391070186767300e-27
	    // For derivation of 4.820055089755540 refer to research diary entry: Monday 6th February 2007 (p26)
	    CellProperties.nu_ie = ( ( (4.391070186767300e-27) / AVERAGE_PARTICLE_MASS ) * CellProperties.n[ELECTRON] * fLogLambda_ei( CellProperties.T[ELECTRON], CellProperties.T[HYDROGEN], CellProperties.n[ELECTRON] ) ) / pow( CellProperties.T[ELECTRON], 1.5 );
    }
    // Calculated in EvaluateTerms when the collisional term is known
    CellProperties.collision_delta_t = Params.Duration;

// ******************************************************************************
// *    ADVECTION                                                               *
// ******************************************************************************

    // The time-step is calculated by the CFL condition
    CellProperties.advection_delta_t = Params.safety_advection * ( CellProperties.cell_width / ( fabs( CellProperties.v[1] ) + CellProperties.Cs ) );

// ******************************************************************************
// *    THERMAL CONDUCTION                                                      *
// ******************************************************************************

    // The time-step is calculated by: delta_t = ( n * k_B ) * ( cell width )^2 / ( 2.0 * coefficient of thermal conduction )
    // 0.5 * BOLTZMANN_CONSTANT = 6.9e-17
    term1 = Params.safety_conduction * (6.9e-17) * CellProperties.cell_width * CellProperties.cell_width;
	int start_index;

	if(Params.use_kinetic_model)
    {
	    CellProperties.conduction_delta_t[ELECTRON] = Params.Duration;
	    start_index = 1;
    }
	else
    {
    	start_index = 0;
    }

	for( j=start_index; j<SPECIES; j++ )
	{
		if(Params.optically_thick_radiation && j == HYDROGEN && CellProperties.T[ELECTRON] < OPTICALLY_THICK_TEMPERATURE)
	    {
	        CellProperties.conduction_delta_t[j] = ( term1 * CellProperties.n[j] ) / ( ( Kappa[j] + pHI->Getkappa_0( log10(CellProperties.T[ELECTRON]) ) ) * pow( CellProperties.T[j], 2.5 ) );
	    }
		else
       	{
	       	CellProperties.conduction_delta_t[j] = ( term1 * CellProperties.n[j] ) / ( Kappa[j] * pow( CellProperties.T[j], 2.5 ) );
       	}
	}

// ******************************************************************************
// *    RADIATION                                                               *
// ******************************************************************************

    // Calculated in EvaluateTerms when the radiative term is known
    CellProperties.radiation_delta_t = Params.Duration;

// ******************************************************************************
// *    DYNAMIC VISCOSITY                                                       *
// ******************************************************************************

    // The time-step is calculated by: delta_t = ( rho ) * ( cell width )^2 / ( 2.0 * (4/3) * coefficient of dynamic viscosity )
    CellProperties.eta = DYNAMIC_VISCOSITY * ( pow( CellProperties.T[HYDROGEN], 2.5 ) / fLogLambda_ii( CellProperties.T[HYDROGEN], CellProperties.n[HYDROGEN] ) );
    CellProperties.viscosity_delta_t = Params.safety_viscosity * ( ( CellProperties.rho[1] * CellProperties.cell_width * CellProperties.cell_width ) / ( 2.6666666666666666666666666666667 * CellProperties.eta ) );

    pActiveCell->UpdateCellProperties( &CellProperties );

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}
}

void CEquations::EvaluateTerms( double current_time, double *delta_t, int iFirstStep )
{
PCELL pNextActiveCell, pFarLeftCell, pLeftCell, pRightCell;
CELLPROPERTIES CellProperties, FarLeftCellProperties, LeftCellProperties, RightCellProperties;
//Variables used for non-equilibrium radiation
PCELL pFarRightCell;
CELLPROPERTIES FarRightCellProperties;
// Variables used for time-dependent ionisation balance calculation
double **ppni0, **ppni1, **ppni2, **ppni3, **ppni4, ps[5], **ppdnibydt;
//Variables used for optically thick radiation
double fHI_c, frho_c, cell_width_cos_theta;

// Variables used by advective flux transport algorithm
double Q1, Q2, Q3, QT;

// Variables used by thermal and viscous flux transport algorithms
double T[3][SPECIES], Kappa[SPECIES], max_flux_coeff[SPECIES], Fc_max, v[2], n, P;
//Variables used for numerical viscosity
double rho_v[2];

Kappa[ELECTRON] = SPITZER_ELECTRON_CONDUCTIVITY;
Kappa[HYDROGEN] = SPITZER_ION_CONDUCTIVITY;

max_flux_coeff[ELECTRON] = 1.5 / SQRT_ELECTRON_MASS;
max_flux_coeff[HYDROGEN] = 1.5 / SQRT_AVERAGE_PARTICLE_MASS;

// Variables used for interpolation
double x[5], y[5], UpperValue, LowerValue, error;

// General variables
double term1, term2;
int j, start_index;

if(Params.use_kinetic_model)
{
	CalculateKineticModel( iFirstStep );
}

// ******************************************************************************
// *                                                                            *
// *    CALCULATE THE CELL-INTERFACE TERMS                                      *
// *                                                                            *
// ******************************************************************************

pNextActiveCell = pStartOfCurrentRow->pGetPointer( RIGHT )->pGetPointer( RIGHT );

while( pNextActiveCell->pGetPointer( RIGHT ) )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    pLeftCell = pActiveCell->pGetPointer( LEFT );
    pLeftCell->GetCellProperties( &LeftCellProperties );

    pRightCell = pActiveCell->pGetPointer( RIGHT );
    pRightCell->GetCellProperties( &RightCellProperties );

    pFarLeftCell = pLeftCell->pGetPointer( LEFT );
    pFarLeftCell->GetCellProperties( &FarLeftCellProperties );

// ******************************************************************************
// *    ADVECTIVE FLUX TRANSPORT ALGORITHM                                      *
// ******************************************************************************

    x[1] = LeftCellProperties.s[1];
    x[2] = CellProperties.s[1];
    y[1] = LeftCellProperties.v[1];
    y[2] = CellProperties.v[1];
    LinearFit( x, y, CellProperties.s[0], &(CellProperties.v[0]) );
    LeftCellProperties.v[2] = CellProperties.v[0];

    if( CellProperties.v[0] > 0.0 )
    {
// CALCULATE THE DENSITY

        x[1] = FarLeftCellProperties.s[1];
	x[2] = LeftCellProperties.s[1];
	y[1] = FarLeftCellProperties.rho[1];
	y[2] = LeftCellProperties.rho[1];
	LinearFit( x, y, CellProperties.s[0], &Q1 );

	x[1] = LeftCellProperties.s[1];
	x[2] = CellProperties.s[1];
	y[1] = LeftCellProperties.rho[1];
	y[2] = CellProperties.rho[1];
	LinearFit( x, y, CellProperties.s[0], &Q2 );

        Q3 = LeftCellProperties.rho[1];

	if( CellProperties.rho[1] <= LeftCellProperties.rho[1] )
	{
	    QT = max( Q1, Q2 );
	    if( Q3 < QT )
	        CellProperties.rho[0] = Q3;
	    else
	        CellProperties.rho[0] = QT;
	}
	else
	{
	    QT = min( Q1, Q2 );
	    if( Q3 > QT )
	        CellProperties.rho[0] = Q3;
	    else
	        CellProperties.rho[0] = QT;
	}

	LeftCellProperties.rho[2] = CellProperties.rho[0];

// CALCULATE THE MOMENTUM

    x[1] = FarLeftCellProperties.s[1];
	x[2] = LeftCellProperties.s[1];
	y[1] = FarLeftCellProperties.rho_v[1];
	y[2] = LeftCellProperties.rho_v[1];
	LinearFit( x, y, CellProperties.s[0], &Q1 );

	x[1] = LeftCellProperties.s[1];
	x[2] = CellProperties.s[1];
	y[1] = LeftCellProperties.rho_v[1];
	y[2] = CellProperties.rho_v[1];
	LinearFit( x, y, CellProperties.s[0], &Q2 );

        Q3 = LeftCellProperties.rho_v[1];

	if( CellProperties.rho_v[1] <= LeftCellProperties.rho_v[1] )
	{
	    QT = max( Q1, Q2 );
	    if( Q3 < QT )
	        CellProperties.rho_v[0] = Q3;
	    else
	        CellProperties.rho_v[0] = QT;
	}
	else
	{
	    QT = min( Q1, Q2 );
	    if( Q3 > QT )
	        CellProperties.rho_v[0] = Q3;
	    else
	        CellProperties.rho_v[0] = QT;
	}

	LeftCellProperties.rho_v[2] = CellProperties.rho_v[0];

// CALCULATE THE ENERGY

	for( j=0; j<SPECIES; j++ )
	{
            x[1] = FarLeftCellProperties.s[1];
            x[2] = LeftCellProperties.s[1];
            y[1] = FarLeftCellProperties.TE_KE_P[1][j];
            y[2] = LeftCellProperties.TE_KE_P[1][j];
            LinearFit( x, y, CellProperties.s[0], &Q1 );

            x[1] = LeftCellProperties.s[1];
            x[2] = CellProperties.s[1];
            y[1] = LeftCellProperties.TE_KE_P[1][j];
            y[2] = CellProperties.TE_KE_P[1][j];
            LinearFit( x, y, CellProperties.s[0], &Q2 );

            Q3 = LeftCellProperties.TE_KE_P[1][j];

            if( CellProperties.TE_KE_P[1][j] <= LeftCellProperties.TE_KE_P[1][j] )
            {
                QT = max( Q1, Q2 );
		if( Q3 < QT )
                    CellProperties.TE_KE_P[0][j] = Q3;
		else
		    CellProperties.TE_KE_P[0][j] = QT;
            }
            else
            {
		QT = min( Q1, Q2 );
		if( Q3 > QT )
		    CellProperties.TE_KE_P[0][j] = Q3;
		else
		    CellProperties.TE_KE_P[0][j] = QT;
            }

            LeftCellProperties.TE_KE_P[2][j] = CellProperties.TE_KE_P[0][j];
	}
    }
    else
    {
// CALCULATE THE DENSITY

    x[1] = CellProperties.s[1];
	x[2] = RightCellProperties.s[1];
	y[1] = CellProperties.rho[1];
	y[2] = RightCellProperties.rho[1];
	LinearFit( x, y, CellProperties.s[0], &Q1 );

	x[1] = LeftCellProperties.s[1];
	x[2] = CellProperties.s[1];
	y[1] = LeftCellProperties.rho[1];
	y[2] = CellProperties.rho[1];
	LinearFit( x, y, CellProperties.s[0], &Q2 );

        Q3 = CellProperties.rho[1];

	if( CellProperties.rho[1] <= LeftCellProperties.rho[1] )
	{
            QT = min( Q1, Q2 );
	    if( Q3 > QT )
	        CellProperties.rho[0] = Q3;
	    else
	        CellProperties.rho[0] = QT;
	}
	else
	{
	    QT = max( Q1, Q2 );
	    if( Q3 < QT )
	        CellProperties.rho[0] = Q3;
	    else
	        CellProperties.rho[0] = QT;
	}

	LeftCellProperties.rho[2] = CellProperties.rho[0];

// CALCULATE THE MOMENTUM

	x[1] = CellProperties.s[1];
	x[2] = RightCellProperties.s[1];
	y[1] = CellProperties.rho_v[1];
	y[2] = RightCellProperties.rho_v[1];
	LinearFit( x, y, CellProperties.s[0], &Q1 );

	x[1] = LeftCellProperties.s[1];
	x[2] = CellProperties.s[1];
	y[1] = LeftCellProperties.rho_v[1];
	y[2] = CellProperties.rho_v[1];
	LinearFit( x, y, CellProperties.s[0], &Q2 );

        Q3 = CellProperties.rho_v[1];

	if( CellProperties.rho_v[1] <= LeftCellProperties.rho_v[1] )
	{
	    QT = min( Q1, Q2 );
	    if( Q3 > QT )
	        CellProperties.rho_v[0] = Q3;
	    else
	        CellProperties.rho_v[0] = QT;
	}
	else
	{
	    QT = max( Q1, Q2 );
	    if( Q3 < QT )
	        CellProperties.rho_v[0] = Q3;
	    else
	        CellProperties.rho_v[0] = QT;
	}

	LeftCellProperties.rho_v[2] = CellProperties.rho_v[0];

// CALCULATE THE ENERGY

    for( j=0; j<SPECIES; j++ )
	{
            x[1] = CellProperties.s[1];
            x[2] = RightCellProperties.s[1];
            y[1] = CellProperties.TE_KE_P[1][j];
            y[2] = RightCellProperties.TE_KE_P[1][j];
            LinearFit( x, y, CellProperties.s[0], &Q1 );

            x[1] = LeftCellProperties.s[1];
            x[2] = CellProperties.s[1];
            y[1] = LeftCellProperties.TE_KE_P[1][j];
            y[2] = CellProperties.TE_KE_P[1][j];
            LinearFit( x, y, CellProperties.s[0], &Q2 );

            Q3 = CellProperties.TE_KE_P[1][j];

            if( CellProperties.TE_KE_P[1][j] <= LeftCellProperties.TE_KE_P[1][j] )
            {
		QT = min( Q1, Q2 );
		if( Q3 > QT )
		    CellProperties.TE_KE_P[0][j] = Q3;
		else
                    CellProperties.TE_KE_P[0][j] = QT;
            }
            else
            {
		QT = max( Q1, Q2 );
		if( Q3 < QT )
		    CellProperties.TE_KE_P[0][j] = Q3;
		else
	        CellProperties.TE_KE_P[0][j] = QT;
            }

            LeftCellProperties.TE_KE_P[2][j] = CellProperties.TE_KE_P[0][j];
	}
    }

// ******************************************************************************
// *    THERMAL FLUX TRANSPORT ALGORITHM                                        *
// ******************************************************************************

    x[1] = FarLeftCellProperties.s[1];
    x[2] = LeftCellProperties.s[1];
    x[3] = CellProperties.s[1];
    x[4] = RightCellProperties.s[1];

    // Only need to calculate the diffusive terms on the first time-step
    if( iFirstStep )
    {
	if(Params.use_kinetic_model)
	{
		j = ELECTRON;

		y[1] = FarLeftCellProperties.Fc[1][j];
		y[2] = LeftCellProperties.Fc[1][j];
		y[3] = CellProperties.Fc[1][j];
		y[4] = RightCellProperties.Fc[1][j];

		FitPolynomial4( x, y, CellProperties.s[0], &(CellProperties.Fc[0][j]), &error );
		LeftCellProperties.Fc[2][j] = CellProperties.Fc[0][j];

		start_index = 1;
	}
	else // USE_KINETIC_MODEL
	{
		start_index = 0;
	}
	// Calculate the conducted heat fluxes for the different species
	for( j=start_index; j<SPECIES; j++ )
	{
            y[1] = FarLeftCellProperties.T[j];
            y[2] = LeftCellProperties.T[j];
            y[3] = CellProperties.T[j];
            y[4] = RightCellProperties.T[j];

            FitPolynomial4( x, y, ( CellProperties.s[1] - CellProperties.cell_width ), &(T[0][j]), &error );
            FitPolynomial4( x, y, CellProperties.s[0], &(T[1][j]), &error );
            T[2][j] = CellProperties.T[j];

            // Calculate the conducted heat flux at the left boundary
            if( Params.optically_thick_radiation && j == HYDROGEN && T[1][ELECTRON] < OPTICALLY_THICK_TEMPERATURE )
                CellProperties.Fc[0][j] = - ( Kappa[j] + pHI->Getkappa_0( log10(T[1][ELECTRON]) ) ) * pow( T[1][j], 2.5 ) * ( ( T[2][j] - T[0][j] ) / CellProperties.cell_width );
            else
            {
                CellProperties.Fc[0][j] = - Kappa[j] * pow( T[1][j], 2.5 ) * ( ( T[2][j] - T[0][j] ) / CellProperties.cell_width );
            }

            // Estimate the maximum conducted heat flux (treats n as approximately constant across cell)
            // BOLTZMANN_CONSTANT^1.5 = 1.621132937e-24
            Fc_max = (1.621132937e-24) * max_flux_coeff[j] * CellProperties.n[j] * pow( T[1][j], 1.5 );

            term1 = CellProperties.Fc[0][j] * Fc_max;
            term2 = ( CellProperties.Fc[0][j] * CellProperties.Fc[0][j] ) + ( Fc_max * Fc_max );
            CellProperties.Fc[0][j] =  term1 / sqrt( term2 );

            LeftCellProperties.Fc[2][j] = CellProperties.Fc[0][j];

            if( pLeftCell->pGetPointer( LEFT )->pGetPointer( LEFT ) )
                LeftCellProperties.Fc[1][j] = 0.5 * ( LeftCellProperties.Fc[0][j] + LeftCellProperties.Fc[2][j] );
	}

// ******************************************************************************
// *    VISCOUS FLUX TRANSPORT ALGORITHM                                        *
// ******************************************************************************

	if(Params.use_kinetic_model)
	{
		j = ELECTRON;
		y[1] = FarLeftCellProperties.T[j];
		y[2] = LeftCellProperties.T[j];
		y[3] = CellProperties.T[j];
		y[4] = RightCellProperties.T[j];
		FitPolynomial4( x, y, CellProperties.s[0], &(T[1][j]), &error );
	}

	j = HYDROGEN;
	y[1] = FarLeftCellProperties.n[j];
	y[2] = LeftCellProperties.n[j];
	y[3] = CellProperties.n[j];
	y[4] = RightCellProperties.n[j];
	FitPolynomial4( x, y, CellProperties.s[0], &n, &error );

	y[1] = FarLeftCellProperties.v[1];
	y[2] = LeftCellProperties.v[1];
	y[3] = CellProperties.v[1];
	y[4] = RightCellProperties.v[1];
	FitPolynomial4( x, y, ( CellProperties.s[1] - CellProperties.cell_width ), &(v[0]), &error );

	v[1] = CellProperties.v[1];

	// Calculate the viscosity flux at the left boundary
	term1 = DYNAMIC_VISCOSITY * ( pow( T[1][j], 2.5 ) / fLogLambda_ii( T[1][j], n ) );
	CellProperties.Feta[0] = term1 * 1.3333333333333333333333333333333 * ( ( v[1] - v[0] ) / CellProperties.cell_width );

	// The viscous flux forms the anisotropic part of the pressure tensor and therefore cannot exceed the total pressure
	// Hence, it must be limited to the value of the total pressure
	P = BOLTZMANN_CONSTANT * n * T[1][j];
	term1 = CellProperties.Feta[0] * P;
	term2 = ( CellProperties.Feta[0] * CellProperties.Feta[0] ) + ( P * P );
	CellProperties.Feta[0] =  term1 / sqrt( term2 );

	LeftCellProperties.Feta[2] = CellProperties.Feta[0];

	if( pLeftCell->pGetPointer( LEFT )->pGetPointer( LEFT ) )
	{
            LeftCellProperties.Feta[1] = 0.5 * ( LeftCellProperties.Feta[0] + LeftCellProperties.Feta[2] );
            LeftCellProperties.dvbyds = LeftCellProperties.Feta[1] / LeftCellProperties.eta;
	}

// ******************************************************************************
// *    NUMERICAL VISCOSITY                                                     *
// ******************************************************************************

	if(Params.numerical_viscosity)
	{
		y[1] = FarLeftCellProperties.rho_v[1];
		y[2] = LeftCellProperties.rho_v[1];
		y[3] = CellProperties.rho_v[1];
		y[4] = RightCellProperties.rho_v[1];
		FitPolynomial4( x, y, ( CellProperties.s[1] - CellProperties.cell_width ), &(rho_v[0]), &error );
		rho_v[1] = CellProperties.rho_v[1];

		term1 = ( CellProperties.cell_width * CellProperties.cell_width ) / ( 2.0 * Params.relative_viscous_time_scale * ( CellProperties.advection_delta_t / Params.safety_advection ) );
		CellProperties.Fnumerical[0] = term1 * ( ( rho_v[1] - rho_v[0] ) / CellProperties.cell_width );

	        LeftCellProperties.Fnumerical[2] = CellProperties.Fnumerical[0];
	}
    }

// ******************************************************************************
// *    CELL BOUNDARY PRESSURES                                                 *
// ******************************************************************************

    for( j=0; j<SPECIES; j++ )
    {
		y[1] = FarLeftCellProperties.P[1][j];
		y[2] = LeftCellProperties.P[1][j];
		y[3] = CellProperties.P[1][j];
		y[4] = RightCellProperties.P[1][j];
    	FitPolynomial4( x, y, CellProperties.s[0], &(CellProperties.P[0][j]), &error );
		LeftCellProperties.P[2][j] = CellProperties.P[0][j];
    }

    pActiveCell->UpdateCellProperties( &CellProperties );
    pLeftCell->UpdateCellProperties( &LeftCellProperties );

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

// ******************************************************************************
// *                                                                            *
// *    CALCULATE THE CELL-CENTERED TERMS                                       *
// *                                                                            *
// ******************************************************************************

// ******************************************************************************
// *    COLUMN NUMBER AND MASS DENSITIES                                        *
// ******************************************************************************

if(Params.optically_thick_radiation)
{
	// Left-hand leg of the loop
	fHI_c = 0.0;
	frho_c = 0.0;
	pNextActiveCell = pCentreOfCurrentRow;
	while( pNextActiveCell )
	{
	    pActiveCell = pNextActiveCell;
	    pActiveCell->GetCellProperties( &CellProperties );

	    if( CellProperties.T[ELECTRON] < OPTICALLY_THICK_TEMPERATURE )
	    {
	        cell_width_cos_theta = CellProperties.cell_width * fabs( cos( ( _PI_ * CellProperties.s[1] ) / Params.L ) );
	        // Calculate the neutral hydrogen column number density
	        fHI_c += ( CellProperties.n[HYDROGEN] - ( CellProperties.n[ELECTRON] / 1.000144 ) ) * cell_width_cos_theta;
	        // Calculate the mass column density
	        frho_c += CellProperties.rho[1] * cell_width_cos_theta;

	        CellProperties.HI_c = fHI_c;
	        CellProperties.rho_c = frho_c;

	        pActiveCell->UpdateCellProperties( &CellProperties );
	    }
	    pNextActiveCell = pActiveCell->pGetPointer( LEFT );
	}

	// Right-hand leg of the loop
	fHI_c = 0.0;
	frho_c = 0.0;
	pNextActiveCell = pCentreOfCurrentRow;
	while( pNextActiveCell )
	{
	    pActiveCell = pNextActiveCell;
	    pActiveCell->GetCellProperties( &CellProperties );

	    if( CellProperties.T[ELECTRON] < OPTICALLY_THICK_TEMPERATURE )
	    {
	        cell_width_cos_theta = CellProperties.cell_width * fabs( cos( ( _PI_ * CellProperties.s[1] ) / Params.L ) );
	        // Calculate the neutral hydrogen column number density
	        fHI_c += ( CellProperties.n[HYDROGEN] - ( CellProperties.n[ELECTRON] / 1.000144 ) ) * cell_width_cos_theta;
	        // Calculate the mass column density
	        frho_c += CellProperties.rho[1] * cell_width_cos_theta;

	        CellProperties.HI_c = fHI_c;
	        CellProperties.rho_c = frho_c;

	        pActiveCell->UpdateCellProperties( &CellProperties );
	    }
	    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	}
}

// ******************************************************************************
// *    TERMS OF THE CONVERSATION EQUATIONS                                     *
// ******************************************************************************

pNextActiveCell = pStartOfCurrentRow->pGetPointer( RIGHT )->pGetPointer( RIGHT );

while( pNextActiveCell->pGetPointer( RIGHT )->pGetPointer( RIGHT ) )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    pLeftCell = pActiveCell->pGetPointer( LEFT );
    pLeftCell->GetCellProperties( &LeftCellProperties );

    pRightCell = pActiveCell->pGetPointer( RIGHT );
    pRightCell->GetCellProperties( &RightCellProperties );

	if(Params.non_equilibrium_radiation)
    {
	    pFarLeftCell = pLeftCell->pGetPointer( LEFT );
	    pFarLeftCell->GetCellProperties( &FarLeftCellProperties );

	    pFarRightCell = pRightCell->pGetPointer( RIGHT );
	    pFarRightCell->GetCellProperties( &FarRightCellProperties );
    }

// ******************************************************************************
// *                                                                            *
// *    MASS CONSERVATION                                                       *
// *                                                                            *
// ******************************************************************************

// ******************************************************************************
// *    ADVECTION                                                               *
// ******************************************************************************

    LowerValue = CellProperties.rho[0] * CellProperties.v[0];
    UpperValue = CellProperties.rho[2] * CellProperties.v[2];
    CellProperties.rho_term[0] = - ( UpperValue - LowerValue ) / CellProperties.cell_width;

    CellProperties.drhobydt = CellProperties.rho_term[0];

// ******************************************************************************
// *                                                                            *
// *    MOMENTUM CONSERVATION                                                   *
// *                                                                            *
// ******************************************************************************

// ******************************************************************************
// *    ADVECTION                                                               *
// ******************************************************************************

    LowerValue = CellProperties.rho_v[0] * CellProperties.v[0];
    UpperValue = CellProperties.rho_v[2] * CellProperties.v[2];
    CellProperties.rho_v_term[0] = - ( UpperValue - LowerValue ) / CellProperties.cell_width;

// ******************************************************************************
// *    PRESSURE GRADIENT                                                       *
// ******************************************************************************

    UpperValue = CellProperties.P[2][ELECTRON] + CellProperties.P[2][HYDROGEN];
    LowerValue = CellProperties.P[0][ELECTRON] + CellProperties.P[0][HYDROGEN];
    CellProperties.rho_v_term[1] = - ( UpperValue - LowerValue ) / CellProperties.cell_width;

// ******************************************************************************
// *    GRAVITY                                                                 *
// ******************************************************************************

    CellProperties.rho_v_term[2] = CellProperties.rho[1] * CalculateGravity( CellProperties.s[1] );

    // Terms that must be integrated to first order in time only, otherwise they're unconditionally unstable
    if( iFirstStep )
    {
// ******************************************************************************
// *    VISCOUS STRESS                                                          *
// ******************************************************************************

		CellProperties.rho_v_term[3] = ( CellProperties.Feta[2] - CellProperties.Feta[0] ) / CellProperties.cell_width;

// ******************************************************************************
// *    NUMERICAL VISCOSITY                                                     *
// ******************************************************************************

		if(Params.numerical_viscosity)
		{
			// Numerical viscosity is used to stabilise the solutions as in the Lax scheme
			CellProperties.rho_v_term[4] = ( CellProperties.Fnumerical[2] - CellProperties.Fnumerical[0] ) / CellProperties.cell_width;
		}
    }

    CellProperties.drho_vbydt = CellProperties.rho_v_term[0] + CellProperties.rho_v_term[1] + CellProperties.rho_v_term[2] + CellProperties.rho_v_term[3] + CellProperties.rho_v_term[4];

// ******************************************************************************
// *                                                                            *
// *    ENERGY CONSERVATION                                                     *
// *                                                                            *
// ******************************************************************************

// ******************************************************************************
// *    ADVECTION                                                               *
// ******************************************************************************

    for( j=0; j<SPECIES; j++ )
    {
		LowerValue = CellProperties.TE_KE_P[0][j] * CellProperties.v[0];
		UpperValue = CellProperties.TE_KE_P[2][j] * CellProperties.v[2];
		CellProperties.TE_KE_term[0][j] = - ( UpperValue - LowerValue ) / CellProperties.cell_width;
    }

    // Terms that must be integrated to first order in time only, otherwise they're unconditionally unstable
    if( iFirstStep )
    {
// ******************************************************************************
// *    THERMAL CONDUCTION                                                      *
// ******************************************************************************

	for( j=0; j<SPECIES; j++ )
            CellProperties.TE_KE_term[1][j] = - ( CellProperties.Fc[2][j] - CellProperties.Fc[0][j] ) / CellProperties.cell_width;

// ******************************************************************************
// *    VISCOUS STRESS                                                          *
// ******************************************************************************

        // Heating due to the viscous stress and work done on (by) the flow by (on) the viscous stress
	CellProperties.TE_KE_term[7][HYDROGEN] = ( ( CellProperties.Feta[2] * CellProperties.v[2] ) - ( CellProperties.Feta[0] * CellProperties.v[0] ) ) / CellProperties.cell_width;

// ******************************************************************************
// *    NUMERICAL VISCOSITY                                                     *
// ******************************************************************************

	if(Params.numerical_viscosity)
	{
		// Numerical viscosity is used to stabilise the solutions as in the Lax scheme
		CellProperties.TE_KE_term[8][HYDROGEN] = CellProperties.rho_v_term[4] * CellProperties.v[1];
	}
    }

// ******************************************************************************
// *    GRAVITY                                                                 *
// ******************************************************************************

    CellProperties.TE_KE_term[2][HYDROGEN] = CellProperties.rho_v_term[2] * CellProperties.v[1];

// ******************************************************************************
// *    COLLISIONS                                                              *
// ******************************************************************************

    // The collision frequency is calculated using n_e, therefore the collisional coupling depends on (n_e)(n_H)
    CellProperties.TE_KE_term[3][ELECTRON] = (2.07e-16) * CellProperties.n[HYDROGEN] * CellProperties.nu_ie * ( CellProperties.T[HYDROGEN] - CellProperties.T[ELECTRON] );
    // Set the collisional timescale to 1% of the timescale for order of magnitude changes in the electron energy due to collisional energy exchange
    CellProperties.collision_delta_t = ( 0.01 * CellProperties.TE_KE[1][ELECTRON] ) / fabs( CellProperties.TE_KE_term[3][ELECTRON] );
    // If the collisional timescale is less than the minimum specified collisional timescale then scale the rate of energy exchange so that tiny timesteps can be avoided
    if( CellProperties.collision_delta_t < Params.minimum_collisional_coupling_time_scale )
        CellProperties.TE_KE_term[3][ELECTRON] *= CellProperties.collision_delta_t / Params.minimum_collisional_coupling_time_scale;

    CellProperties.TE_KE_term[3][HYDROGEN] = - CellProperties.TE_KE_term[3][ELECTRON];

// ******************************************************************************
// *    HEATING                                                                 *
// ******************************************************************************

    CellProperties.TE_KE_term[4][Params.heated_species] = pHeat->CalculateHeating( CellProperties.s[1], current_time );

// ******************************************************************************
// *    RADIATION                                                               *
// ******************************************************************************

CellProperties.TE_KE_term[5][ELECTRON] = - SMALLEST_DOUBLE;

double Tcheck;
if(Params.optically_thick_radiation)
{
	Tcheck = OPTICALLY_THICK_TEMPERATURE;
}
else
{
	Tcheck = Params.minimum_radiation_temperature;
}

if( CellProperties.T[ELECTRON] < Tcheck)
{
    if(Params.optically_thick_radiation)
	{
	    CellProperties.TE_KE_term[4][Params.heated_species] += pHeat->CalculateVALHeating( log10( CellProperties.rho_c ) );
	    CellProperties.TE_KE_term[5][ELECTRON] -= pHI->GetVolumetricLossRate( log10(CellProperties.T[ELECTRON]), log10((4e-14)*CellProperties.HI_c), CellProperties.n[ELECTRON] * CellProperties.rho[1]);
	    CellProperties.TE_KE_term[5][ELECTRON] -= pMgII->GetVolumetricLossRate( log10(CellProperties.T[ELECTRON]), log10(CellProperties.rho_c), CellProperties.n[ELECTRON] * CellProperties.rho[1]);
	    CellProperties.TE_KE_term[5][ELECTRON] -= pCaII->GetVolumetricLossRate( log10(CellProperties.T[ELECTRON]), log10(CellProperties.rho_c), CellProperties.n[ELECTRON] * CellProperties.rho[1]);
	    CellProperties.radiation_delta_t = ( Params.safety_radiation * CellProperties.TE_KE[1][ELECTRON] ) / fabs( CellProperties.TE_KE_term[5][ELECTRON] );
    }
	else
	{
        // Provide some additional heating to the chromosphere if the temperature drops below the specified isothermal temperature
        CellProperties.TE_KE_term[5][ELECTRON] = ( ( ( Params.minimum_radiation_temperature / CellProperties.T[ELECTRON] ) - 1.0 ) * CellProperties.TE_KE[1][ELECTRON] ) / Params.minimum_collisional_coupling_time_scale;
		    CellProperties.radiation_delta_t = Params.minimum_collisional_coupling_time_scale;
    }
}
else
{
	term1 = 1.0;
	// Decrease the radiation smoothly to zero in the chromosphere
	if( CellProperties.T[ELECTRON] < lower_radiation_temperature_boundary && Params.optically_thick_radiation==false)
    {
	    term1 = ( CellProperties.T[ELECTRON] - Params.minimum_radiation_temperature ) / Params.zero_over_temperature_interval;
    }

if(Params.decouple_ionisation_state_solver)
{
		if(Params.use_power_law_radiative_losses)
		{
			printf( "nOPTICALLY_THICK_RADIATION; DECOUPLE_IONISATION_STATE_SOLVER; USE_POWER_LAW_RADIATIVE_LOSSES\n" );
			CellProperties.TE_KE_term[5][ELECTRON] -= term1 * pRadiation2->GetPowerLawRad( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) );
		}
		else // USE_POWER_LAW_RADIATIVE_LOSSES
		{
			if(Params.non_equilibrium_radiation)
			{
				printf( "nOPTICALLY_THICK_RADIATION; DECOUPLE_IONISATION_STATE_SOLVER; nUSE_POWER_LAW_RADIATIVE_LOSSES; NON_EQUILIBRIUM_RADIATION\n" );
				CellProperties.TE_KE_term[5][ELECTRON] -= term1 * ( pRadiation->GetRadiation( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) + pRadiation2->GetRadiation( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) + pRadiation2->GetFreeFreeRad( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) );
			}
			else // NON_EQUILIBRIUM_RADIATION
			{
				printf( "nOPTICALLY_THICK_RADIATION; DECOUPLE_IONISATION_STATE_SOLVER; nUSE_POWER_LAW_RADIATIVE_LOSSES; nNON_EQUILIBRIUM_RADIATION\n" );
				CellProperties.TE_KE_term[5][ELECTRON] -= term1 * ( pRadiation2->GetRadiation( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) + pRadiation2->GetFreeFreeRad( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) );
			}
		}
}
else // DECOUPLE_IONISATION_STATE_SOLVER
{
		if(Params.non_equilibrium_radiation)
		{
				printf( "nOPTICALLY_THICK_RADIATION; nDECOUPLE_IONISATION_STATE_SOLVER; NON_EQUILIBRIUM_RADIATION\n" );
		        	ppni2 = CellProperties.pIonFrac->ppGetIonFrac();
			        CellProperties.TE_KE_term[5][ELECTRON] -= term1 * ( pRadiation->GetRadiation( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ), ppni2 ) + pRadiation2->GetRadiation( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) + pRadiation2->GetFreeFreeRad( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) );
		}
		else // NON_EQUILIBRIUM_RADIATION
		{
				if(Params.use_power_law_radiative_losses)
				{
						// printf( "nOPTICALLY_THICK_RADIATION; nDECOUPLE_IONISATION_STATE_SOLVER; nNON_EQUILIBRIUM_RADIATION; USE_POWER_LAW_RADIATIVE_LOSSES\n" );
						CellProperties.TE_KE_term[5][ELECTRON] -= term1 * pRadiation2->GetPowerLawRad( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) );
				}
				else // USE_POWER_LAW_RADIATIVE_LOSSES
				{
						// printf( "nOPTICALLY_THICK_RADIATION; nDECOUPLE_IONISATION_STATE_SOLVER; nNON_EQUILIBRIUM_RADIATION; nUSE_POWER_LAW_RADIATIVE_LOSSES\n" );
			        		CellProperties.TE_KE_term[5][ELECTRON] -= term1 * ( pRadiation2->GetRadiation( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) + pRadiation2->GetFreeFreeRad( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ) ) );
				}
		}
}
	    CellProperties.radiation_delta_t = ( Params.safety_radiation * CellProperties.TE_KE[1][ELECTRON] ) / fabs( CellProperties.TE_KE_term[5][ELECTRON] );
}


// ******************************************************************************
// *    SMALL-SCALE ELECTRIC FIELDS                                             *
// ******************************************************************************

    // Derived from qnEv = v dP/ds
    // The term added to the electron energy equation is (e)nEv = v dPe/ds
    // The term added to the hydrogen energy equation is (-e)nEv = -v dPe/ds
    CellProperties.TE_KE_term[6][ELECTRON] = CellProperties.v[1] * ( ( CellProperties.P[2][ELECTRON] - CellProperties.P[0][ELECTRON] ) / CellProperties.cell_width );
    CellProperties.TE_KE_term[6][HYDROGEN] = -CellProperties.TE_KE_term[6][ELECTRON];

    for( j=0; j<SPECIES; j++ )
        CellProperties.dTE_KEbydt[j] = CellProperties.TE_KE_term[0][j] + CellProperties.TE_KE_term[1][j] + CellProperties.TE_KE_term[2][j] + CellProperties.TE_KE_term[3][j] + CellProperties.TE_KE_term[4][j] + CellProperties.TE_KE_term[5][j] + CellProperties.TE_KE_term[6][j] + CellProperties.TE_KE_term[7][j] + CellProperties.TE_KE_term[8][j];

// ******************************************************************************
// *                                                                            *
// *    TIME-DEPENDENT IONISATION                                               *
// *                                                                            *
// ******************************************************************************

if(Params.non_equilibrium_radiation)
{
	ppni0 = FarLeftCellProperties.pIonFrac->ppGetIonFrac();
	ppni1 = LeftCellProperties.pIonFrac->ppGetIonFrac();
    ppni2 = CellProperties.pIonFrac->ppGetIonFrac();
	ppni3 = RightCellProperties.pIonFrac->ppGetIonFrac();
	ppni4 = FarRightCellProperties.pIonFrac->ppGetIonFrac();

	ps[0] = FarLeftCellProperties.s[1];
	ps[1] = LeftCellProperties.s[1];
	ps[2] = CellProperties.s[1];
	ps[3] = RightCellProperties.s[1];
	ps[4] = FarRightCellProperties.s[1];

	ppdnibydt = CellProperties.pIonFrac->ppGetdnibydt();
	pRadiation->GetAlldnibydt( log10( CellProperties.T[ELECTRON] ), log10( CellProperties.n[ELECTRON] ), ppni0, ppni1, ppni2, ppni3, ppni4, ps, CellProperties.s, CellProperties.v, CellProperties.cell_width, ppdnibydt, &(CellProperties.atomic_delta_t) );
}

    pActiveCell->UpdateCellProperties( &CellProperties );

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

// Find the smallest characteristic time-scale
GetSmallestTimeScale( delta_t, iFirstStep );
}

double CEquations::CalculateGravity( double s )
{
double x[3], y[3], g_parallel;
int i;

for( i=0; i<igdp; i++ )
{
    if( s < ppGravity[i][0] ) break;
}

if( i == 0 ) i = 1;
if( i == igdp ) i = igdp - 1;

x[1] = ppGravity[i-1][0];
x[2] = ppGravity[i][0];

y[1] = ppGravity[i-1][1];
y[2] = ppGravity[i][1];

LinearFit( x, y, s, &g_parallel );

return g_parallel;
}

void CEquations::GetSmallestTimeScale( double *delta_t, int iFirstStep )
{
if( !iFirstStep )
    return;

PCELL pNextActiveCell;
CELLPROPERTIES CellProperties;
int j;

*delta_t = Params.Duration;

pNextActiveCell = pStartOfCurrentRow->pGetPointer( RIGHT )->pGetPointer( RIGHT );

while( pNextActiveCell->pGetPointer( RIGHT )->pGetPointer( RIGHT ) )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    // Advection timescale
    if( CellProperties.advection_delta_t < *delta_t )
	*delta_t = CellProperties.advection_delta_t;

    // Thermal conduction timescale
    for( j=0; j<SPECIES; j++ )
    {
	if( CellProperties.conduction_delta_t[j] < *delta_t )
            *delta_t = CellProperties.conduction_delta_t[j];
    }

    // Viscous timescale
    if( CellProperties.viscosity_delta_t < *delta_t )
	*delta_t = CellProperties.viscosity_delta_t;

    // Collisional timescale
    if( CellProperties.collision_delta_t >= Params.minimum_collisional_coupling_time_scale &&
        CellProperties.collision_delta_t < *delta_t )
        *delta_t = CellProperties.collision_delta_t;

    // Radiation timescale
    if( CellProperties.radiation_delta_t < *delta_t )
	*delta_t = CellProperties.radiation_delta_t;

if(Params.non_equilibrium_radiation)
{
	// Ionisation and recombination timescale
	if( CellProperties.atomic_delta_t < *delta_t )
		*delta_t = CellProperties.atomic_delta_t;
}

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}
}

void CEquations::Half_Time_Step( PCELLPROPERTIES pNewCellProperties, double delta_t )
{
CELLPROPERTIES CellProperties;
int j;

pActiveCell->GetCellProperties( &CellProperties );

if(Params.non_equilibrium_radiation)
{
	// Integrate the ion fractions
	pNewCellProperties->pIonFrac->IntegrateAllIonFrac( delta_t );
}

pNewCellProperties->rho[1] = CellProperties.rho[1] + ( delta_t * CellProperties.drhobydt );
pNewCellProperties->rho_v[1] = CellProperties.rho_v[1] + ( delta_t * CellProperties.drho_vbydt );

for( j=0; j<SPECIES; j++ )
    pNewCellProperties->TE_KE[1][j] = CellProperties.TE_KE[1][j] + ( delta_t * CellProperties.dTE_KEbydt[j] );
}

void CEquations::Full_Time_Step( PCELLPROPERTIES pCellProperties, double delta_t )
{
PCELL pBottomCell;
CELLPROPERTIES BottomCellProperties;
int j;

pBottomCell = pActiveCell->pGetPointer( BOTTOM );
pBottomCell->GetCellProperties( &BottomCellProperties );

if(Params.non_equilibrium_radiation)
{
	// Integrate the ion fractions using the previous set of values
	pCellProperties->pIonFrac->CopyAllIonFrac( BottomCellProperties.pIonFrac );
	pCellProperties->pIonFrac->IntegrateAllIonFrac( delta_t );
}

pCellProperties->rho[1] = BottomCellProperties.rho[1] + ( delta_t * pCellProperties->drhobydt );
pCellProperties->rho_v[1] = BottomCellProperties.rho_v[1] + ( delta_t * pCellProperties->drho_vbydt );

for( j=0; j<SPECIES; j++ )
    pCellProperties->TE_KE[1][j] = BottomCellProperties.TE_KE[1][j] + ( delta_t * pCellProperties->dTE_KEbydt[j] );
}

// ******************************************************************************
// *                                                                            *
// *    KINETIC COMPONENT FOR DISTRIBUTION FUNCTION CALCULATIONS                *
// *                                                                            *
// ******************************************************************************

// Index labels for each column of the table in Spitzer & Harm, 1953, Phys. Rev., 89, 977
#define U							0		// Relative (to u_th) velocity values in column 0
#define X_E							1		// Coefficients when an electric field is present in column 1
#define X_T							2		// Coefficients when a temperature gradient is present in column 2

void CEquations::Get_SH_Table( char *sh_table_filename )
{
FILE *pFile;
int i;

pFile = fopen( sh_table_filename ,"r" );
for( i=0; i<51; i++ )
{
    ReadDouble( pFile, &(SH_Table[i][U]) );
    ReadDouble( pFile, &(SH_Table[i][X_E]) );
    ReadDouble( pFile, &(SH_Table[i][X_T]) );
}
fclose( pFile );
}

void CEquations::CountCells( void )
{
PCELL pNextActiveCell;

iNumCells = 0;

pNextActiveCell = pStartOfCurrentRow;
while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;

    iNumCells++;

    pNextActiveCell=pActiveCell->pGetPointer( RIGHT );
}
}

void CEquations::CreateIndexedCellList( void )
{
PCELL pNextActiveCell;
int iIndex;

// Free the previous indexed cell list and allocate sufficient memory for the next one
if( ppCellList )
    free( ppCellList );

ppCellList = (PCELL*)malloc( iNumCells * sizeof(PCELL) );

// Compile an indexed list of the cells
iIndex = 0;
pNextActiveCell = pStartOfCurrentRow;
while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;

    ppCellList[iIndex] = pActiveCell;
    iIndex++;

    pNextActiveCell=pActiveCell->pGetPointer( RIGHT );
}
}

void CEquations::CalculateKineticModel( int iFirstStep )
{
if( !iFirstStep )
    return;

PCELL pNextActiveCell;
CELLPROPERTIES CellProperties;
double Tmax = 0.0;

// Calculate the physical quantities required for the kinetic model
pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    // Find the maximum temperature to determine the velocity range
    if( CellProperties.T[ELECTRON] > Tmax )
	Tmax = CellProperties.T[ELECTRON];

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

// Calculate the quantities required for the kinetic model
pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    CellProperties.pKinetic->CalculateVelocityRange( CellProperties.T[ELECTRON], Tmax );
    CellProperties.pKinetic->CalculateCollisionalProperties( CellProperties.T[ELECTRON], CellProperties.T[HYDROGEN], CellProperties.n[ELECTRON] );
    CellProperties.pKinetic->CalculateMaxDFN( CellProperties.T[ELECTRON], CellProperties.T[HYDROGEN], CellProperties.n[ELECTRON] );

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

// Calculate the non-Maxwellian distribution function and its moments in each grid cell
CalculateNonMaxDFN();
}

void CEquations::CalculateNonMaxDFN( void )
{
// General variables
double *pupsilon, *pnu_ee, *pnu_ei, *plambda_ei, *pMaxDFN_ee, *pMaxDFN_ei, *pNonMaxDFN;
double dTbyds, K_SH, Kappa;
int iIndex, i, j, half_data_points = DISTRIBUTION_DATA_POINTS / 2;

// Variables for the BGK part of the solution
CELLPROPERTIES CellProperties;
double ds, previous_cell_width, *previous_pNonMaxDFN;
double term1, term2, term3;

// Variables for the Spitzer-Harm part of the solution
CELLPROPERTIES FarLeftCellProperties, LeftCellProperties, RightCellProperties, FarRightCellProperties;
double u_th, u_n;
double fScaleLength, E, lambda_ei, x_e, x_t, fp;
double x[6], y[6], fLowerValue, fUpperValue, fError;

// ******************************************************************************
// *    INITIALISE THE BOUNDARY CONDITIONS                                      *
// ******************************************************************************

iIndex = 0;
pActiveCell = ppCellList[iIndex];
pActiveCell->GetCellProperties( &CellProperties );
pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();
for( i=0; i<DISTRIBUTION_DATA_POINTS; i++ )
    pNonMaxDFN[i] = pMaxDFN_ee[i];

iIndex = 1;
pActiveCell = ppCellList[iIndex];
pActiveCell->GetCellProperties( &CellProperties );
pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();
for( i=0; i<DISTRIBUTION_DATA_POINTS; i++ )
    pNonMaxDFN[i] = pMaxDFN_ee[i];

iIndex = iNumCells-2;
pActiveCell = ppCellList[iIndex];
pActiveCell->GetCellProperties( &CellProperties );
pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();
for( i=0; i<DISTRIBUTION_DATA_POINTS; i++ )
    pNonMaxDFN[i] = pMaxDFN_ee[i];

iIndex = iNumCells-1;
pActiveCell = ppCellList[iIndex];
pActiveCell->GetCellProperties( &CellProperties );
pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();
for( i=0; i<DISTRIBUTION_DATA_POINTS; i++ )
    pNonMaxDFN[i] = pMaxDFN_ee[i];

// ******************************************************************************
// *    BGK PART OF THE SOLUTION                                                *
// ******************************************************************************

// Solve for positive velocities

iIndex = 1;
pActiveCell = ppCellList[iIndex];
pActiveCell->GetCellProperties( &CellProperties );
pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();

for( iIndex=2; iIndex<iNumCells; iIndex++ )
{
    previous_cell_width = CellProperties.cell_width;
    previous_pNonMaxDFN = pNonMaxDFN;

    pActiveCell = ppCellList[iIndex];
    pActiveCell->GetCellProperties( &CellProperties );
    pupsilon = CellProperties.pKinetic->Get_pupsilon();
    pnu_ee = CellProperties.pKinetic->Get_pnu_ee();
    pnu_ei = CellProperties.pKinetic->Get_pnu_ei();
    pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
    pMaxDFN_ei = CellProperties.pKinetic->Get_pMaxDFN_ei();
    pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();

    ds = 0.5 * ( previous_cell_width + CellProperties.cell_width );

    for( i=half_data_points; i<DISTRIBUTION_DATA_POINTS; i++ )
    {
	term1 = ( ( pnu_ee[i] * pMaxDFN_ee[i] ) + ( 4.0 * pnu_ei[i] * pMaxDFN_ei[i] ) ) * ds;
	term2 = pupsilon[i] * previous_pNonMaxDFN[i];
	term3 = pupsilon[i] + ( ( pnu_ee[i] + ( 4.0 * pnu_ei[i] ) ) * ds );

	pNonMaxDFN[i] = ( term1 + term2 ) / term3;
    }
}

// Solve for negative velocities

iIndex = iNumCells-2;
pActiveCell = ppCellList[iIndex];
pActiveCell->GetCellProperties( &CellProperties );
pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();

for( iIndex=iNumCells-3; iIndex>=0; iIndex-- )
{
    previous_cell_width = CellProperties.cell_width;
    previous_pNonMaxDFN = pNonMaxDFN;

    pActiveCell = ppCellList[iIndex];
    pActiveCell->GetCellProperties( &CellProperties );
    pupsilon = CellProperties.pKinetic->Get_pupsilon();
    pnu_ee = CellProperties.pKinetic->Get_pnu_ee();
    pnu_ei = CellProperties.pKinetic->Get_pnu_ei();
    pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
    pMaxDFN_ei = CellProperties.pKinetic->Get_pMaxDFN_ei();
    pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();

    ds = 0.5 * ( previous_cell_width + CellProperties.cell_width );

    for( i=0; i<half_data_points; i++ )
    {
        term1 = ( ( pnu_ee[i] * pMaxDFN_ee[i] ) + ( 4.0 * pnu_ei[i] * pMaxDFN_ei[i] ) ) * ds;
	term2 = pupsilon[i] * previous_pNonMaxDFN[i];
	term3 = pupsilon[i] + ( ( pnu_ee[i] + ( 4.0 * pnu_ei[i] ) ) * ds );

	pNonMaxDFN[i] = ( term1 + term2 ) / term3;
    }
}

// ******************************************************************************
// *    SPITZER PART OF THE SOLUTION                                            *
// ******************************************************************************

for( iIndex=2; iIndex<iNumCells-2; iIndex++ )
{
    pActiveCell = ppCellList[iIndex];
    pActiveCell->GetCellProperties( &CellProperties );

    ppCellList[iIndex-2]->GetCellProperties( &FarLeftCellProperties );
    ppCellList[iIndex-1]->GetCellProperties( &LeftCellProperties );
    ppCellList[iIndex+1]->GetCellProperties( &RightCellProperties );
    ppCellList[iIndex+2]->GetCellProperties( &FarRightCellProperties );

    pupsilon = CellProperties.pKinetic->Get_pupsilon();
    plambda_ei = CellProperties.pKinetic->Get_plambda_ei();
    pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();

    u_th = CellProperties.pKinetic->Get_u_th();

    x[1] = FarLeftCellProperties.s[1];
    x[2] = LeftCellProperties.s[1];
    x[3] = CellProperties.s[1];
    x[4] = RightCellProperties.s[1];
    x[5] = FarRightCellProperties.s[1];

    y[1] = FarLeftCellProperties.T[ELECTRON];
    y[2] = LeftCellProperties.T[ELECTRON];
    y[3] = CellProperties.T[ELECTRON];
    y[4] = RightCellProperties.T[ELECTRON];
    y[5] = FarRightCellProperties.T[ELECTRON];

    FitPolynomial4( x, y, CellProperties.s[0], &fLowerValue, &fError );
    FitPolynomial4( &(x[1]), &(y[1]), CellProperties.s[2], &fUpperValue, &fError );

    dTbyds = ( fUpperValue - fLowerValue ) / CellProperties.cell_width;
    fScaleLength = KNUDSEN_NUMBER * fabs( CellProperties.T[ELECTRON] / dTbyds );
    E = -0.703 * ( BOLTZMANN_CONSTANT / ELECTRON_CHARGE ) * dTbyds;

    lambda_ei = fSHMeanFreePath( u_th, CellProperties.T[ELECTRON], CellProperties.T[HYDROGEN], CellProperties.n[ELECTRON] );

    // Solve for positive velocities

    for( i=half_data_points; i<DISTRIBUTION_DATA_POINTS; i++ )
    {
        // Normalise the velocity to the thermal speed
	u_n = pupsilon[i] / u_th;

	if( plambda_ei[i] > fScaleLength || u_n > 3.20 )
            break;

	// Calculate X_E and X_T
        if( u_n > 0.10 )
	{
            // Find the data points to interpolate at the current velocity
            for( j=0; j<51; j++ )
            {
                if( u_n <= SH_Table[j][U] )
                    break;
            }

            x[1] = SH_Table[j-1][U];
            x[2] = SH_Table[j][U];

            y[1] = SH_Table[j-1][X_E];
            y[2] = SH_Table[j][X_E];
            LinearFit( x, y, u_n, &x_e );

            y[1] = SH_Table[j-1][X_T];
            y[2] = SH_Table[j][X_T];
            LinearFit( x, y, u_n, &x_t );
	}
	else
	{
            x_e = 0.0;
            x_t = 0.0;
	}

	term1 = -x_e * ( ( ELECTRON_CHARGE * E ) / ( BOLTZMANN_CONSTANT * CellProperties.T[ELECTRON] ) );
	term2 = 2.0 * x_t * ( 1.0 / CellProperties.T[ELECTRON] ) * dTbyds;
	fp = lambda_ei * ( term1 + term2 );

	pNonMaxDFN[i] *= ( 1.0 + fp );
    }

    // Solve for negative velocities

    for( i=half_data_points-1; i>=0; i-- )
    {
        // Normalise the velocity to the thermal speed
	u_n = -pupsilon[i] / u_th;

	if( plambda_ei[i] > fScaleLength || u_n > 3.20 )
            break;

	// Calculate X_E and X_T
	if( u_n > 0.10 )
	{
            // Find the data points to interpolate at the current velocity
            for( j=0; j<51; j++ )
            {
                if( u_n <= SH_Table[j][U] )
                    break;
            }

            x[1] = SH_Table[j-1][U];
            x[2] = SH_Table[j][U];

            y[1] = SH_Table[j-1][X_E];
            y[2] = SH_Table[j][X_E];
            LinearFit( x, y, u_n, &x_e );

            y[1] = SH_Table[j-1][X_T];
            y[2] = SH_Table[j][X_T];
            LinearFit( x, y, u_n, &x_t );
	}
	else
	{
            x_e = 0.0;
            x_t = 0.0;
	}

	term1 = -x_e * ( ( ELECTRON_CHARGE * E ) / ( BOLTZMANN_CONSTANT * CellProperties.T[ELECTRON] ) );
	term2 = 2.0 * x_t * ( 1.0 / CellProperties.T[ELECTRON] ) * dTbyds;
	fp = - lambda_ei * ( term1 + term2 );

	pNonMaxDFN[i] *= ( 1.0 + fp );
    }

    CellProperties.Fc[1][ELECTRON] = CellProperties.pKinetic->Get_Fc();

    // Calculate the thermal conduction time-scale
    K_SH = SPITZER_ELECTRON_CONDUCTIVITY * pow( CellProperties.T[ELECTRON], 2.5 );
    Kappa = fabs( CellProperties.Fc[1][ELECTRON] / dTbyds );

    if( Kappa > K_SH )
        Kappa = K_SH;

    // The time-step is calculated by: delta_t = ( n * k_B ) * ( cell width )^2 / ( 2.0 * coefficient of thermal conduction )
    // 0.5 * BOLTZMANN_CONSTANT = 6.9e-17
    term1 = Params.safety_conduction * (6.9e-17) * CellProperties.cell_width * CellProperties.cell_width;
    CellProperties.conduction_delta_t[ELECTRON] = ( term1 * CellProperties.n[ELECTRON] ) / Kappa;

    pActiveCell->UpdateCellProperties( &CellProperties );
}
}
