// ****
// *
// * Function bodies for the class definition of the adaptive mesh
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 11/13/2015
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "mesh.h"
#include "../../Resources/source/constants.h"
#include "../../Resources/source/file.h"
#include "../../Resources/source/fitpoly.h"


// **** ADAPTIVE MESH CLASS ****

// Constructor
CAdaptiveMesh::CAdaptiveMesh( char *configFilename, char *rad_config_eqFilename, char *rad_config_neqFilename ) : CEquations( configFilename, rad_config_eqFilename, rad_config_neqFilename)
{
	//Set member variable(s)
	radConfigNeqFilename = rad_config_neqFilename;
	
	// Create the initial mesh given the steady-state profiles
	CreateInitialMesh();

// Solve the equations
Solve();
}

// Destructor
CAdaptiveMesh::~CAdaptiveMesh( void )
{
// Free all of the memory allocated within the mesh object
FreeCurrentRow();
}

void CAdaptiveMesh::ZeroCellProperties( PCELLPROPERTIES pCellProperties )
{
memset( pCellProperties, 0, sizeof(CELLPROPERTIES) );
}

void CAdaptiveMesh::CreateInitialMesh( void )
{
FILE *pFile;
PCELL pPreviousCell = NULL;
CELLPROPERTIES CellProperties;
int iNumberOfCells, i, j;

printf( "\nProcessing the initial conditions...\n" );

if(Params.non_equilibrium_radiation)
{
	PCELL pNextActiveCell;
	FILE *pIonFile = NULL;
	char szIonFilename[32];
	double fTemp;
}

// ******************************************************************************
// *                                                                            *
// *    CREATE THE COMPUTATIONAL MESH                                           *
// *                                                                            *
// ******************************************************************************

// ******************************************************************************
// *    INITIALISE THE MESH                                                     *
// ******************************************************************************

// Reset the initial cell properties to zero before the initial mesh is created
ZeroCellProperties( &CellProperties );

// Open the initial density, momentum density and thermal + kinetic energy density profiles
pFile = fopen( Params.Profiles, "r" );

ReadDouble( pFile, &mesh_time );
fscanf( pFile, "%i", &iFileNumber );

ReadDouble( pFile, &Params.L );

fscanf( pFile, "%i", &iNumberOfCells );

// Create the initial mesh using values from the user-specified .amr file
for( i = 0; i < iNumberOfCells; i++ )
{
    // Fill in the cell properties structure

    ReadDouble( pFile, &(CellProperties.s[1]) );
    ReadDouble( pFile, &(CellProperties.cell_width) );

    CellProperties.s[0] = CellProperties.s[1] - ( 0.5 * CellProperties.cell_width );
    CellProperties.s[2] = CellProperties.s[1] + ( 0.5 * CellProperties.cell_width );

    ReadDouble( pFile, &(CellProperties.rho[1]) );
    ReadDouble( pFile, &(CellProperties.rho_v[1]) );
    ReadDouble( pFile, &(CellProperties.TE_KE[1][ELECTRON]) );
    ReadDouble( pFile, &(CellProperties.TE_KE[1][HYDROGEN]) );

    // The number of refinement levels in the .amr file MUST match MAX_REFINEMENT_LEVEL
    fscanf( pFile, "%i", &(CellProperties.iRefinementLevel) );
    for( j=1; j<=Params.max_refinement_level; j++ )
		fscanf( pFile, "%i", &(CellProperties.iUniqueID[j]) );

	if(Params.non_equilibrium_radiation)
	{
	    // Reset the pointer to the ion population fractions object
	    CellProperties.pIonFrac = NULL;
	}

	if(Params.use_kinetic_model)
	{
    	CellProperties.pKinetic = new CKinetic();
	}

    // Create a new cell
    pActiveCell = new CAdaptiveMeshCell( &CellProperties );

    // Set the RIGHT pointer to NULL
    pActiveCell->SetPointer( RIGHT, NULL );

    // If this is the first cell
    if( !i )
    {
        // Need to know the address of the left-most cell at each time t
		// in order to derive the row of cells at t + delta_t
		pStartOfCurrentRow = pActiveCell;
		pStartOfPreviousRow = NULL;		

		// Set the LEFT pointer of the left-most cell to NULL
		pActiveCell->SetPointer( LEFT, NULL );
    }
    // If this is not the left-most cell set the RIGHT pointer of the previous cell
    // to point at the new cell and the LEFT pointer of the new cell to point at
    // the previous cell
    else
    {
		pPreviousCell->SetPointer( RIGHT, pActiveCell );
		pActiveCell->SetPointer( LEFT, pPreviousCell );
    }
	
    // Keep track of the cell pointer so that the appropriate LEFT and RIGHT pointers can be set
    // next time around
    pPreviousCell = pActiveCell;
}

fclose( pFile );

// ******************************************************************************
// *    ADAPT THE INITIAL MESH                                                  *
// ******************************************************************************

if(Params.adapt)
{
	if( mesh_time == 0.0 )
    {
	    Adapt();
    }
}

CalculatePhysicalQuantities();

// ******************************************************************************
// *    INITIALISE THE IONISATION STATE                                         *
// ******************************************************************************

if(Params.non_equilibrium_radiation)
{
	// If the mesh time is greater than 0.0 then the nonequilibrium ion population corresponding to
	// the current time should be used
	if( mesh_time > 0.0 )
	{
		sprintf( szIonFilename, "%sprofile%i.ine", Params.output_dir, iFileNumber );
	    pIonFile = fopen( szIonFilename, "r" );
	}

	pNextActiveCell = pStartOfCurrentRow;

	while( pNextActiveCell )
	{
	    pActiveCell = pNextActiveCell;
	    pActiveCell->GetCellProperties( &CellProperties );

	    // Initialise the fractional populations of the ions
	    CellProperties.pIonFrac = new CIonFrac( NULL, radConfigNeqFilename, pRadiation );

	    // If the mesh time is greater than 0.0 then get the nonequilibrium ion population corresponding to
	    // the current time and position
	    if( mesh_time > 0.0 )
	    {
	        ReadDouble( pIonFile, &fTemp );
	        CellProperties.pIonFrac->ReadAllIonFracFromFile( pIonFile );
	    }
	    else
	    {
			// Make sure the ionisation balance EXACTLY matches equilibrium at t = 0 seconds
			if(Params.density_dependent_rates)
			{
				CellProperties.pIonFrac->ResetAllIonFrac( log10(CellProperties.T[ELECTRON]), log10(CellProperties.n[ELECTRON]) );
			
			}	
			else 
			{
				// DENSITY_DEPENDENT_RATES
				CellProperties.pIonFrac->ResetAllIonFrac( log10(CellProperties.T[ELECTRON]) );
			}
	    }

	    pActiveCell->UpdateCellProperties( &CellProperties );

	    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	}

	if( mesh_time > 0.0 )
    {
	    fclose( pIonFile );
    }
}

// ******************************************************************************
// *    INITIALISE THE KINETIC COMPONENT                                        *
// ******************************************************************************

if(Params.use_kinetic_model)
{
	CountCells();
	CreateIndexedCellList();
}

// ******************************************************************************
// *    OUTPUT THE INITIAL STATE                                                *
// ******************************************************************************

EvaluateTerms( mesh_time, &mesh_delta_t, TRUE );
WriteToFile();
}

void CAdaptiveMesh::Adapt( void )
{
PCELL pNextActiveCell, pFarLeftCell, pLeftCell, pRightCell, pFarRightCell, pNewCell[2];
CELLPROPERTIES FarLeftCellProperties, LeftCellProperties, CellProperties, RightCellProperties, FarRightCellProperties, NewCellProperties[2];
double drho = 0.0, dTE_KEe = 0.0, dTE_KEh = 0.0, x[6], y[6];
int iProlonged, iRestricted, j;

if(Params.non_equilibrium_radiation)
{
	double **ppIonFrac[6];
}

if(Params.linear_restriction==false)
{
	double error;
}

double fWeight, temp1, temp2, temp3, temp4;

// ******************************************************************************
// *                                                                            *
// *    PROLONGATION                                                            *
// *                                                                            *
// ******************************************************************************

// Look for cells that can be merged

do {

    iProlonged = FALSE;

    pNextActiveCell = pStartOfCurrentRow;

    while( pNextActiveCell->pGetPointer( RIGHT ) )
    {
        pActiveCell = pNextActiveCell;
	pActiveCell->GetCellProperties( &CellProperties );

	pRightCell = pActiveCell->pGetPointer( RIGHT );
	pRightCell->GetCellProperties( &RightCellProperties );

	// Only neighbouring cells derived from the same parent cell can be merged
	if( CellProperties.iRefinementLevel > 0 && CellProperties.iRefinementLevel == RightCellProperties.iRefinementLevel && CellProperties.iUniqueID[CellProperties.iRefinementLevel] == RightCellProperties.iUniqueID[RightCellProperties.iRefinementLevel] )
	{
		if(Params.refine_on_density)
        {
        	drho = 1.0 - ( min( CellProperties.rho[1], RightCellProperties.rho[1] ) / max( CellProperties.rho[1], RightCellProperties.rho[1] ) );
        }
		if(Params.refine_on_electron_energy)
        {
            dTE_KEe = 1.0 - ( min( CellProperties.TE_KE[1][ELECTRON], RightCellProperties.TE_KE[1][ELECTRON] ) / max( CellProperties.TE_KE[1][ELECTRON], RightCellProperties.TE_KE[1][ELECTRON] ) );
        }
		if(Params.refine_on_hydrogen_energy)
        {
            dTE_KEh = 1.0 - ( min( CellProperties.TE_KE[1][HYDROGEN], RightCellProperties.TE_KE[1][HYDROGEN] ) / max( CellProperties.TE_KE[1][HYDROGEN], RightCellProperties.TE_KE[1][HYDROGEN] ) );
        }
            if( drho < Params.min_frac_diff && dTE_KEe < Params.min_frac_diff && dTE_KEh < Params.min_frac_diff )
            {
                iProlonged = TRUE;

				ZeroCellProperties( &(NewCellProperties[0]) );

				if(Params.non_equilibrium_radiation)
				{
					// Create a new ionfrac object for the new cell
	               	if( CellProperties.pIonFrac )
					{
	                   	NewCellProperties[0].pIonFrac = new CIonFrac( CellProperties.pIonFrac, 0, pRadiation );
						
					}
				}

				if(Params.use_kinetic_model)
				{
					// Create a new kinetic object for the new cell
					NewCellProperties[0].pKinetic = new CKinetic();
				}

				NewCellProperties[0].iRefinementLevel = CellProperties.iRefinementLevel - 1;

				for( j=1; j<=NewCellProperties[0].iRefinementLevel; j++ )
                {
                    NewCellProperties[0].iUniqueID[j] = CellProperties.iUniqueID[j];
                }

				NewCellProperties[0].cell_width = CellProperties.cell_width + RightCellProperties.cell_width;
				NewCellProperties[0].s[0] = CellProperties.s[0];
				NewCellProperties[0].s[1] = CellProperties.s[2];
				NewCellProperties[0].s[2] = RightCellProperties.s[2];

				// ******************************************************************************
				// *    ENSURE MASS, MOMENTUM AND ENERGY IS CONSERVED                           *
				// ******************************************************************************

				// Averaging the mass density, momentum density and energy density of the two grid cells to calculate the corresponding quantities for the merged cell guarantees conservation

				NewCellProperties[0].rho[1] = ( CellProperties.rho[1] + RightCellProperties.rho[1] ) / 2.0;
		
				pLeftCell = pActiveCell->pGetPointer( LEFT );
				pFarRightCell = pRightCell->pGetPointer( RIGHT );
				if( pLeftCell && pFarRightCell )
				{
		    		NewCellProperties[0].rho_v[1] = ( CellProperties.rho_v[1] + RightCellProperties.rho_v[1] ) / 2.0;
				}
				else
				{
					// ******************************************************************************
					// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
					// ******************************************************************************
		    		NewCellProperties[0].rho_v[1] = 0.0;
				}

				for( j=0; j<SPECIES; j++ )
				{
                    NewCellProperties[0].TE_KE[1][j] = ( CellProperties.TE_KE[1][j] + RightCellProperties.TE_KE[1][j] ) / 2.0;
				}
                    
                if( NewCellProperties[0].pIonFrac && Params.non_equilibrium_radiation)
                {
                    x[1] = CellProperties.s[1];
                    x[2] = RightCellProperties.s[1];
                    ppIonFrac[1] = CellProperties.pIonFrac->ppGetIonFrac();
                    ppIonFrac[2] = RightCellProperties.pIonFrac->ppGetIonFrac();
                    NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[0].s[1] );
                }

				pNewCell[0] = new CAdaptiveMeshCell( &(NewCellProperties[0]) );

				if( pLeftCell )
				{
        		            pLeftCell->SetPointer( RIGHT, pNewCell[0] );
        		            pNewCell[0]->SetPointer( LEFT, pLeftCell );
				}
				else
				{
        		            pNewCell[0]->SetPointer( LEFT, NULL );
        		            pStartOfCurrentRow = pNewCell[0];
				}
        		
				if( pFarRightCell )
				{
        		            pNewCell[0]->SetPointer( RIGHT, pFarRightCell );
        		            pFarRightCell->SetPointer( LEFT, pNewCell[0] );
        		            pNextActiveCell = pFarRightCell;
				}
				else
				{
        		            pNewCell[0]->SetPointer( RIGHT, NULL );
        		            pNextActiveCell = pNewCell[0];
				}

                if( CellProperties.pIonFrac && RightCellProperties.pIonFrac && Params.non_equilibrium_radiation)
                {
                    delete CellProperties.pIonFrac;
                    delete RightCellProperties.pIonFrac;
                }

				if(Params.use_kinetic_model)
				{
					delete CellProperties.pKinetic;
					delete RightCellProperties.pKinetic;
				}

				delete pActiveCell;
				delete pRightCell;
            }
            else
            {
                pNextActiveCell = pRightCell;
            }
	}
	else
	{
            pNextActiveCell = pRightCell;
	}
    }
} while ( iProlonged );

// ******************************************************************************
// *                                                                            *
// *    RESTRICTION                                                             *
// *                                                                            *
// ******************************************************************************

// Look for cells that need to be refined

do {

    iRestricted = FALSE;

    pNextActiveCell = pStartOfCurrentRow;

    while( pNextActiveCell->pGetPointer( RIGHT ) )
    {
        pActiveCell = pNextActiveCell;
	pActiveCell->GetCellProperties( &CellProperties );

	pRightCell = pActiveCell->pGetPointer( RIGHT );
	pRightCell->GetCellProperties( &RightCellProperties );
	
	if(Params.refine_on_density)
	{
		drho = 1.0 - ( min( CellProperties.rho[1], RightCellProperties.rho[1] ) / max( CellProperties.rho[1], RightCellProperties.rho[1] ) );
	}
	
	if(Params.refine_on_electron_energy)
	{
		dTE_KEe = 1.0 - ( min( CellProperties.TE_KE[1][ELECTRON], RightCellProperties.TE_KE[1][ELECTRON] ) / max( CellProperties.TE_KE[1][ELECTRON], RightCellProperties.TE_KE[1][ELECTRON] ) );
	}
	
	if(Params.refine_on_hydrogen_energy)
	{
		dTE_KEh = 1.0 - ( min( CellProperties.TE_KE[1][HYDROGEN], RightCellProperties.TE_KE[1][HYDROGEN] ) / max( CellProperties.TE_KE[1][HYDROGEN], RightCellProperties.TE_KE[1][HYDROGEN] ) );
	}
	
	if( ( drho > Params.max_frac_diff || dTE_KEe > Params.max_frac_diff || dTE_KEh > Params.max_frac_diff || abs( CellProperties.iRefinementLevel - RightCellProperties.iRefinementLevel ) > 1 ) && ( CellProperties.iRefinementLevel < Params.max_refinement_level || RightCellProperties.iRefinementLevel < Params.max_refinement_level ) )
	{
            iRestricted = TRUE;

            if( CellProperties.iRefinementLevel <= RightCellProperties.iRefinementLevel )
            {
                // Refine the current cell
                ZeroCellProperties( &(NewCellProperties[0]) );
				ZeroCellProperties( &(NewCellProperties[1]) );

                if( CellProperties.pIonFrac && Params.non_equilibrium_radiation)
                {
                    // Create a new ionfrac object for each new cell
                    NewCellProperties[0].pIonFrac = new CIonFrac( CellProperties.pIonFrac, 0, pRadiation );
                    NewCellProperties[1].pIonFrac = new CIonFrac( CellProperties.pIonFrac, 0, pRadiation );
                }

				if(Params.use_kinetic_model)
				{
					// Create a new kinetic object for each new cell
					NewCellProperties[0].pKinetic = new CKinetic();
					NewCellProperties[1].pKinetic = new CKinetic();
				}

				NewCellProperties[0].iRefinementLevel = CellProperties.iRefinementLevel + 1;
				NewCellProperties[1].iRefinementLevel = NewCellProperties[0].iRefinementLevel;

				for( j=1; j<=CellProperties.iRefinementLevel; j++ )
				{
		                    NewCellProperties[0].iUniqueID[j] = CellProperties.iUniqueID[j];
		                    NewCellProperties[1].iUniqueID[j] = CellProperties.iUniqueID[j];
				}

				NewCellProperties[0].cell_width = 0.5 * CellProperties.cell_width;
				NewCellProperties[1].cell_width = NewCellProperties[0].cell_width;
				NewCellProperties[0].s[0] = CellProperties.s[0];
				NewCellProperties[0].s[1] = NewCellProperties[0].s[0] + ( 0.5 * NewCellProperties[0].cell_width );
				NewCellProperties[0].s[2] = CellProperties.s[1];
				NewCellProperties[1].s[0] = CellProperties.s[1];
				NewCellProperties[1].s[1] = NewCellProperties[1].s[0] + ( 0.5 * NewCellProperties[0].cell_width );
				NewCellProperties[1].s[2] = CellProperties.s[2];
		
				pLeftCell = pActiveCell->pGetPointer( LEFT );

				if( pLeftCell )
				{
                    pLeftCell->GetCellProperties( &LeftCellProperties );

                    do {

                        NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] = rand();

                    } while ( NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] == LeftCellProperties.iUniqueID[NewCellProperties[0].iRefinementLevel] || NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] == RightCellProperties.iUniqueID[NewCellProperties[0].iRefinementLevel] );

                    NewCellProperties[1].iUniqueID[NewCellProperties[1].iRefinementLevel] = NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel];

                    pFarLeftCell = pLeftCell->pGetPointer( LEFT );
                    pFarRightCell = pRightCell->pGetPointer( RIGHT );
			
                    if( pFarLeftCell && pFarRightCell )
                    {
						pFarLeftCell->GetCellProperties( &FarLeftCellProperties );
						pFarRightCell->GetCellProperties( &FarRightCellProperties );

						// NEW CELLS
						x[1] = FarLeftCellProperties.s[1];
						x[2] = LeftCellProperties.s[1];
						x[3] = CellProperties.s[1];
						x[4] = RightCellProperties.s[1];
						x[5] = FarRightCellProperties.s[1];
						y[1] = FarLeftCellProperties.rho[1];
						y[2] = LeftCellProperties.rho[1];
						y[3] = CellProperties.rho[1];
						y[4] = RightCellProperties.rho[1];
						y[5] = FarRightCellProperties.rho[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]), &error );
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]), &error );
							
						}

						y[1] = FarLeftCellProperties.rho_v[1];
						y[2] = LeftCellProperties.rho_v[1];
						y[3] = CellProperties.rho_v[1];
						y[4] = RightCellProperties.rho_v[1];
						y[5] = FarRightCellProperties.rho_v[1];

						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]) );
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]), &error );
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]), &error );
							
						}

						for( j=0; j<SPECIES; j++ )
						{
			                y[1] = FarLeftCellProperties.TE_KE[1][j];
			                y[2] = LeftCellProperties.TE_KE[1][j];
			                y[3] = CellProperties.TE_KE[1][j];
			                y[4] = RightCellProperties.TE_KE[1][j];
			                y[5] = FarRightCellProperties.TE_KE[1][j];
							
							if(Params.linear_restriction)
							{
			                    LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
			                    LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
								
							}
							else
							{
			                    FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]), &error );
			                    FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]), &error );
								
							}
						}

                        if( NewCellProperties[0].pIonFrac && NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = FarLeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[3] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[4] = RightCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[5] = FarRightCellProperties.pIonFrac->ppGetIonFrac();
							if(Params.linear_restriction)
                            {
	                            NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 2, NewCellProperties[0].s[1] );
	                            NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[2]), &(ppIonFrac[2]), 2, NewCellProperties[1].s[1] );
                            }
							else
							{
	                            NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 4, NewCellProperties[0].s[1] );
	                            NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 4, NewCellProperties[1].s[1] );
							}
                        }
                    }
                    else if( !pFarLeftCell )
                    {
						// ******************************************************************************
						// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
						// ******************************************************************************
                    	
						// LEFT-HAND BOUNDARY
                        
                        // Implement hydrostatic boundary conditions in the left-most of the two new cells

                        x[1] = LeftCellProperties.s[1];
						x[2] = CellProperties.s[1];

                        y[1] = LeftCellProperties.rho[1];
                        y[2] = CellProperties.rho[1];
                        LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );

                        NewCellProperties[0].rho_v[1] = 0.0;

                        for( j=0; j<SPECIES; j++ )
                        {
                            y[1] = LeftCellProperties.TE_KE[1][j];
                            y[2] = CellProperties.TE_KE[1][j];
                            LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
                        }

                        if( NewCellProperties[0].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = CellProperties.pIonFrac->ppGetIonFrac();
                            NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[0].s[1] );
                        }

						pFarRightCell->GetCellProperties( &FarRightCellProperties );
            			
						x[2] = LeftCellProperties.s[1];
						x[3] = CellProperties.s[1];
						x[4] = RightCellProperties.s[1];
						x[5] = FarRightCellProperties.s[1];
									
						y[2] = LeftCellProperties.rho[1];
						y[3] = CellProperties.rho[1];
						y[4] = RightCellProperties.rho[1];
						y[5] = FarRightCellProperties.rho[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );
						}
						else
						{
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]), &error );
						}

						y[2] = LeftCellProperties.rho_v[1];
						y[3] = CellProperties.rho_v[1];
						y[4] = RightCellProperties.rho_v[1];
						y[5] = FarRightCellProperties.rho_v[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]) );
						}
						else
						{
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]), &error );
						}

						for( j=0; j<SPECIES; j++ )
						{
                            y[2] = LeftCellProperties.TE_KE[1][j];
                            y[3] = CellProperties.TE_KE[1][j];
                            y[4] = RightCellProperties.TE_KE[1][j];
                            y[5] = FarRightCellProperties.TE_KE[1][j];
							
                            if(Params.linear_restriction)
							{
                            	LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
                            }
							else
                            {
                            	FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]), &error );
                            }
						}

                        if( NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[2] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[3] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[4] = RightCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[5] = FarRightCellProperties.pIonFrac->ppGetIonFrac();
							
                            if(Params.linear_restriction)
							{
								NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[2]), &(ppIonFrac[2]), 2, NewCellProperties[1].s[1] );
                            }
							else 
                            {
								NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 4, NewCellProperties[1].s[1] );
                            }
                        }
                    }
                    else if( !pFarRightCell )
                    {
						pFarLeftCell->GetCellProperties( &FarLeftCellProperties );

						x[1] = FarLeftCellProperties.s[1];
						x[2] = LeftCellProperties.s[1];
						x[3] = CellProperties.s[1];
						x[4] = RightCellProperties.s[1];

						y[1] = FarLeftCellProperties.rho[1];
						y[2] = LeftCellProperties.rho[1];
						y[3] = CellProperties.rho[1];
						y[4] = RightCellProperties.rho[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]), &error );
						}	

						y[1] = FarLeftCellProperties.rho_v[1];
						y[2] = LeftCellProperties.rho_v[1];
						y[3] = CellProperties.rho_v[1];
						y[4] = RightCellProperties.rho_v[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]), &error );
						}

						for( j=0; j<SPECIES; j++ )
						{
                            y[1] = FarLeftCellProperties.TE_KE[1][j];
                            y[2] = LeftCellProperties.TE_KE[1][j];
                            y[3] = CellProperties.TE_KE[1][j];
                            y[4] = RightCellProperties.TE_KE[1][j];
							
							if(Params.linear_restriction)
                            {
								LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
                            }
							else
                            {
								FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]), &error );
                            }
						}

                        if( NewCellProperties[0].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = FarLeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[3] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[4] = RightCellProperties.pIonFrac->ppGetIonFrac();
							
                            if(Params.linear_restriction)
							{
								NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 2, NewCellProperties[0].s[1] );
                            }
							else 
                            {
								NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 4, NewCellProperties[0].s[1] );
                            }
                        }

						// ******************************************************************************
						// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
						// ******************************************************************************
            			
						// RIGHT-HAND BOUNDARY

			            // Implement hydrostatic boundary conditions in the right-most of the two new cells

			            x[1] = CellProperties.s[1];
						x[2] = RightCellProperties.s[1];

			            y[1] = CellProperties.rho[1];
                        y[2] = RightCellProperties.rho[1];
                        LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );

			            NewCellProperties[1].rho_v[1] = 0.0;

      					for( j=0; j<SPECIES; j++ )
                        {
                            y[1] = CellProperties.TE_KE[1][j];
                            y[2] = RightCellProperties.TE_KE[1][j];
                            LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
                        }

                        if( NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = RightCellProperties.pIonFrac->ppGetIonFrac();
                            NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[1].s[1] );
                        }
                    }
		}
		else
		{
                    do {

                        NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] = rand();

                    } while ( NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] == RightCellProperties.iUniqueID[NewCellProperties[0].iRefinementLevel] );

                    NewCellProperties[1].iUniqueID[NewCellProperties[1].iRefinementLevel] = NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel];

					// ******************************************************************************
					// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
					// ******************************************************************************
					
					// LEFT-HAND BOUNDARY

                    // NEW CELLS

                    x[1] = CellProperties.s[1];
		    		x[2] = RightCellProperties.s[1];

                    y[1] = CellProperties.rho[1];
                    y[2] = RightCellProperties.rho[1];
                    LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );
                    LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );

                    NewCellProperties[0].rho_v[1] = 0.0;
                    NewCellProperties[1].rho_v[1] = 0.0;

                    for( j=0; j<SPECIES; j++ )
                    {
                        y[1] = CellProperties.TE_KE[1][j];
                        y[2] = RightCellProperties.TE_KE[1][j];
                        LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
                        LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
                    }

                    if( NewCellProperties[0].pIonFrac && NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                    {
                        ppIonFrac[1] = CellProperties.pIonFrac->ppGetIonFrac();
                        ppIonFrac[2] = RightCellProperties.pIonFrac->ppGetIonFrac();
                        NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[0].s[1] );
                        NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[1].s[1] );
                    }
		}

// ******************************************************************************
// *    ENSURE MASS AND ENERGY IS CONSERVED BY THE RESTRICTION OPERATOR         *
// ******************************************************************************
		if(Params.enforce_conservation)
		{
			// A correction is applied to the mass and energy densities in the event that the sum of the integrated quantities in the new cells does not equal the integrated quantity in the original cell

			fWeight = ( 2.0 * CellProperties.rho[1] ) / ( NewCellProperties[0].rho[1] + NewCellProperties[1].rho[1] );
			NewCellProperties[0].rho[1] *= fWeight;
			NewCellProperties[1].rho[1] *= fWeight;

			if( NewCellProperties[0].rho_v[1] || NewCellProperties[1].rho_v[1] )
			{
	                    temp1 = ( 2.0 * CellProperties.rho_v[1] ) - ( NewCellProperties[0].rho_v[1] + NewCellProperties[1].rho_v[1] );
	                    temp2 = fabs( NewCellProperties[0].rho_v[1] );
	                    temp3 = fabs( NewCellProperties[1].rho_v[1] );
	                    temp4 = temp1 / ( temp2 + temp3 );
	                    NewCellProperties[0].rho_v[1] += ( temp2 * temp4 );
	                    NewCellProperties[1].rho_v[1] += ( temp3 * temp4 );
			}

			for( j=0; j<SPECIES; j++ )
			{
			    fWeight = ( 2.0 * CellProperties.TE_KE[1][j] ) / ( NewCellProperties[0].TE_KE[1][j] + NewCellProperties[1].TE_KE[1][j] );
			    NewCellProperties[0].TE_KE[1][j] *= fWeight;
			    NewCellProperties[1].TE_KE[1][j] *= fWeight;
			}
		}

        pNewCell[0] = new CAdaptiveMeshCell( &(NewCellProperties[0]) );
		pNewCell[1] = new CAdaptiveMeshCell( &(NewCellProperties[1]) );
                
		if( pLeftCell )
		{
        	pLeftCell->SetPointer( RIGHT, pNewCell[0] );
            pNewCell[0]->SetPointer( LEFT, pLeftCell );
		}
		else
		{
        	pNewCell[0]->SetPointer( LEFT, NULL );
            pStartOfCurrentRow = pNewCell[0];
		}

		pNewCell[0]->SetPointer( RIGHT, pNewCell[1] );
		pNewCell[1]->SetPointer( LEFT, pNewCell[0] );

		pNewCell[1]->SetPointer( RIGHT, pRightCell );
		pRightCell->SetPointer( LEFT, pNewCell[1] );

	    if( CellProperties.pIonFrac && Params.non_equilibrium_radiation)
	    {
	    	delete CellProperties.pIonFrac;
	    }

		if(Params.use_kinetic_model)
        {
        	delete CellProperties.pKinetic;
        }

		delete pActiveCell;

		pNextActiveCell = pNewCell[1];
            }
            else
            {
                // Refine the right-hand cell

				// First shift the left-hand and active cells to the right
				pLeftCell = pActiveCell;
				pLeftCell->GetCellProperties( &LeftCellProperties );
				pActiveCell = pRightCell;
				pActiveCell->GetCellProperties( &CellProperties );

				ZeroCellProperties( &(NewCellProperties[0]) );
				ZeroCellProperties( &(NewCellProperties[1]) );

                if( CellProperties.pIonFrac && Params.non_equilibrium_radiation)
                {
                    // Create a new ionfrac object for each new cell
                    NewCellProperties[0].pIonFrac = new CIonFrac( CellProperties.pIonFrac, 0, pRadiation );
                    NewCellProperties[1].pIonFrac = new CIonFrac( CellProperties.pIonFrac, 0, pRadiation );
                }

				if(Params.use_kinetic_model)
				{
					// Create a new kinetic object for each new cell
					NewCellProperties[0].pKinetic = new CKinetic();
					NewCellProperties[1].pKinetic = new CKinetic();
				}

				NewCellProperties[0].iRefinementLevel = CellProperties.iRefinementLevel + 1;
				NewCellProperties[1].iRefinementLevel = NewCellProperties[0].iRefinementLevel;

				for( j=1; j<=CellProperties.iRefinementLevel; j++ )
				{
		                    NewCellProperties[0].iUniqueID[j] = CellProperties.iUniqueID[j];
		                    NewCellProperties[1].iUniqueID[j] = CellProperties.iUniqueID[j];
				}

				NewCellProperties[0].cell_width = 0.5 * CellProperties.cell_width;
				NewCellProperties[1].cell_width = NewCellProperties[0].cell_width;

				NewCellProperties[0].s[0] = CellProperties.s[0];
				NewCellProperties[0].s[1] = NewCellProperties[0].s[0] + ( 0.5 * NewCellProperties[0].cell_width );
				NewCellProperties[0].s[2] = CellProperties.s[1];
				NewCellProperties[1].s[0] = CellProperties.s[1];
				NewCellProperties[1].s[1] = NewCellProperties[1].s[0] + ( 0.5 * NewCellProperties[0].cell_width );
				NewCellProperties[1].s[2] = CellProperties.s[2];

				pRightCell = pActiveCell->pGetPointer( RIGHT );

                if( pRightCell )
				{
                    pRightCell->GetCellProperties( &RightCellProperties );

                    do {

                        NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] = rand();

                    } while ( NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] == LeftCellProperties.iUniqueID[NewCellProperties[0].iRefinementLevel] || NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] == RightCellProperties.iUniqueID[NewCellProperties[0].iRefinementLevel] );

                    NewCellProperties[1].iUniqueID[NewCellProperties[1].iRefinementLevel] = NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel];

                    pFarLeftCell = pLeftCell->pGetPointer( LEFT );
                    pFarRightCell = pRightCell->pGetPointer( RIGHT );
			
                    if( pFarLeftCell && pFarRightCell )
                    {
						pFarLeftCell->GetCellProperties( &FarLeftCellProperties );
						pFarRightCell->GetCellProperties( &FarRightCellProperties );

						// NEW CELLS
						x[1] = FarLeftCellProperties.s[1];
						x[2] = LeftCellProperties.s[1];
						x[3] = CellProperties.s[1];
						x[4] = RightCellProperties.s[1];
						x[5] = FarRightCellProperties.s[1];

						y[1] = FarLeftCellProperties.rho[1];
						y[2] = LeftCellProperties.rho[1];
						y[3] = CellProperties.rho[1];
						y[4] = RightCellProperties.rho[1];
						y[5] = FarRightCellProperties.rho[1];
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]), &error );
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]), &error );
						}

						y[1] = FarLeftCellProperties.rho_v[1];
						y[2] = LeftCellProperties.rho_v[1];
						y[3] = CellProperties.rho_v[1];
						y[4] = RightCellProperties.rho_v[1];
						y[5] = FarRightCellProperties.rho_v[1];
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]) );
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]), &error );
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]), &error );
						}

						for( j=0; j<SPECIES; j++ )
						{
                            y[1] = FarLeftCellProperties.TE_KE[1][j];
                            y[2] = LeftCellProperties.TE_KE[1][j];
                            y[3] = CellProperties.TE_KE[1][j];
                            y[4] = RightCellProperties.TE_KE[1][j];
                            y[5] = FarRightCellProperties.TE_KE[1][j];
			
							if(Params.linear_restriction)
                            {
	                            LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
	                            LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
                            }
							else
                            {
	                            FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]), &error );
	                            FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]), &error );
                            }
						}

                        if( NewCellProperties[0].pIonFrac && NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = FarLeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[3] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[4] = RightCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[5] = FarRightCellProperties.pIonFrac->ppGetIonFrac();
							
							if(Params.linear_restriction)
                            {
	                            NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 2, NewCellProperties[0].s[1] );
	                            NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[2]), &(ppIonFrac[2]), 2, NewCellProperties[1].s[1] );
                            }
							else
                            {
	                            NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 4, NewCellProperties[0].s[1] );
	                            NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 4, NewCellProperties[1].s[1] );
                            }
                        }
                    }
                    else if( !pFarLeftCell )
                    {
						// ******************************************************************************
						// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
						// ******************************************************************************
						
						// LEFT-HAND BOUNDARY

                        // Implement hydrostatic boundary conditions in the left-most of the two new cells

                        x[1] = LeftCellProperties.s[1];
						x[2] = CellProperties.s[1];

                        y[1] = LeftCellProperties.rho[1];
                        y[2] = CellProperties.rho[1];
                        LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );

                        NewCellProperties[0].rho_v[1] = 0.0;

                        for( j=0; j<SPECIES; j++ )
                        {
                            y[1] = LeftCellProperties.TE_KE[1][j];
                            y[2] = CellProperties.TE_KE[1][j];
                            LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
                        }

                        if( NewCellProperties[0].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = CellProperties.pIonFrac->ppGetIonFrac();
                            NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[0].s[1] );
                        }

						pFarRightCell->GetCellProperties( &FarRightCellProperties );

						x[2] = LeftCellProperties.s[1];
						x[3] = CellProperties.s[1];
						x[4] = RightCellProperties.s[1];
						x[5] = FarRightCellProperties.s[1];
						
						y[2] = LeftCellProperties.rho[1];
						y[3] = CellProperties.rho[1];
						y[4] = RightCellProperties.rho[1];
						y[5] = FarRightCellProperties.rho[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );
						}
						else
						{
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]), &error );
						}

						y[2] = LeftCellProperties.rho_v[1];
						y[3] = CellProperties.rho_v[1];
						y[4] = RightCellProperties.rho_v[1];
						y[5] = FarRightCellProperties.rho_v[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]) );
						}
						else
						{
							FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].rho_v[1]), &error );
						}

						for( j=0; j<SPECIES; j++ )
						{
                            y[2] = LeftCellProperties.TE_KE[1][j];
                            y[3] = CellProperties.TE_KE[1][j];
                            y[4] = RightCellProperties.TE_KE[1][j];
                            y[5] = FarRightCellProperties.TE_KE[1][j];
							
                            if(Params.linear_restriction)
							{
 							   LinearFit( &(x[2]), &(y[2]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
                            }
							else
							{
	                            FitPolynomial4( &(x[1]), &(y[1]), NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]), &error );
							}
						}

                        if( NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[2] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[3] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[4] = RightCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[5] = FarRightCellProperties.pIonFrac->ppGetIonFrac();
							
                            if(Params.linear_restriction)
							{
								NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[2]), &(ppIonFrac[2]), 2, NewCellProperties[1].s[1] );
                            }
                            else
							{
								NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 4, NewCellProperties[1].s[1] );
                            }
                        }
                    }
                    else if( !pFarRightCell )
                    {
						pFarLeftCell->GetCellProperties( &FarLeftCellProperties );

						x[1] = FarLeftCellProperties.s[1];
						x[2] = LeftCellProperties.s[1];
						x[3] = CellProperties.s[1];
						x[4] = RightCellProperties.s[1];

			            y[1] = FarLeftCellProperties.rho[1];
						y[2] = LeftCellProperties.rho[1];
						y[3] = CellProperties.rho[1];
						y[4] = RightCellProperties.rho[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]), &error );
						}

						y[1] = FarLeftCellProperties.rho_v[1];
						y[2] = LeftCellProperties.rho_v[1];
						y[3] = CellProperties.rho_v[1];
						y[4] = RightCellProperties.rho_v[1];
						
						if(Params.linear_restriction)
						{
							LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]) );
						}
						else
						{
							FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho_v[1]), &error );
						}

						for( j=0; j<SPECIES; j++ )
						{
                            y[1] = FarLeftCellProperties.TE_KE[1][j];
                            y[2] = LeftCellProperties.TE_KE[1][j];
                            y[3] = CellProperties.TE_KE[1][j];
                            y[4] = RightCellProperties.TE_KE[1][j];
							
							if(Params.linear_restriction)
                            {
								LinearFit( &(x[1]), &(y[1]), NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
                            }
							else
                            {
								FitPolynomial4( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]), &error );
                            }
						}

                        if( NewCellProperties[0].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = FarLeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[3] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[4] = RightCellProperties.pIonFrac->ppGetIonFrac();
							
                            if(Params.linear_restriction)
							{
								NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( &(x[1]), &(ppIonFrac[1]), 2, NewCellProperties[0].s[1] );
                            }
							else
                            {
								NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 4, NewCellProperties[0].s[1] );
                            }
                        }

						// ******************************************************************************
						// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
						// ******************************************************************************
						
						// RIGHT-HAND BOUNDARY

                        // Implement hydrostatic boundary conditions in the right-most of the two new cells

                        x[1] = CellProperties.s[1];
						x[2] = RightCellProperties.s[1];

                        y[1] = CellProperties.rho[1];
                        y[2] = RightCellProperties.rho[1];
                        LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );

                        NewCellProperties[1].rho_v[1] = 0.0;

                        for( j=0; j<SPECIES; j++ )
                        {
                            y[1] = CellProperties.TE_KE[1][j];
                            y[2] = RightCellProperties.TE_KE[1][j];
                            LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
                        }

                        if( NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
                        {
                            ppIonFrac[1] = CellProperties.pIonFrac->ppGetIonFrac();
                            ppIonFrac[2] = RightCellProperties.pIonFrac->ppGetIonFrac();
                            NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[1].s[1] );
                        }
                    }
		}
		else
		{
            do {

                NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] = rand();

            } while ( NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel] == LeftCellProperties.iUniqueID[NewCellProperties[0].iRefinementLevel] );

            NewCellProperties[1].iUniqueID[NewCellProperties[1].iRefinementLevel] = NewCellProperties[0].iUniqueID[NewCellProperties[0].iRefinementLevel];

			// ******************************************************************************
			// *    IMPLEMENT HYDROSTATIC BOUNDARY CONDITIONS                               *
			// ******************************************************************************

			// RIGHT-HAND BOUNDARY
                    
            // NEW CELLS
                    
		    x[1] = LeftCellProperties.s[1];
		    x[2] = CellProperties.s[1];

            y[1] = LeftCellProperties.rho[1];
            y[2] = CellProperties.rho[1];
            LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].rho[1]) );
            LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].rho[1]) );

            NewCellProperties[0].rho_v[1] = 0.0;
            NewCellProperties[1].rho_v[1] = 0.0;

            for( j=0; j<SPECIES; j++ )
            {
                y[1] = LeftCellProperties.TE_KE[1][j];
                y[2] = CellProperties.TE_KE[1][j];
                LinearFit( x, y, NewCellProperties[0].s[1], &(NewCellProperties[0].TE_KE[1][j]) );
                LinearFit( x, y, NewCellProperties[1].s[1], &(NewCellProperties[1].TE_KE[1][j]) );
            }

            if( NewCellProperties[0].pIonFrac && NewCellProperties[1].pIonFrac && Params.non_equilibrium_radiation)
            {
                ppIonFrac[1] = LeftCellProperties.pIonFrac->ppGetIonFrac();
                ppIonFrac[2] = CellProperties.pIonFrac->ppGetIonFrac();
                NewCellProperties[0].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[0].s[1] );
                NewCellProperties[1].pIonFrac->InterpolateAllIonFrac( x, ppIonFrac, 2, NewCellProperties[1].s[1] );
            }
		}

		// ******************************************************************************
		// *    ENSURE MASS AND ENERGY IS CONSERVED BY THE RESTRICTION OPERATOR         *
		// ******************************************************************************
		if(Params.enforce_conservation)
		{
			// A correction is applied to the mass and energy densities in the event that the sum of the integrated quantities in the new cells does not equal the integrated quantity in the original cell

			fWeight = ( 2.0 * CellProperties.rho[1] ) / ( NewCellProperties[0].rho[1] + NewCellProperties[1].rho[1] );
			NewCellProperties[0].rho[1] *= fWeight;
			NewCellProperties[1].rho[1] *= fWeight;

			if( NewCellProperties[0].rho_v[1] || NewCellProperties[1].rho_v[1] )
			{
                temp1 = ( 2.0 * CellProperties.rho_v[1] ) - ( NewCellProperties[0].rho_v[1] + NewCellProperties[1].rho_v[1] );
                temp2 = fabs( NewCellProperties[0].rho_v[1] );
                temp3 = fabs( NewCellProperties[1].rho_v[1] );
                temp4 = temp1 / ( temp2 + temp3 );
                NewCellProperties[0].rho_v[1] += ( temp2 * temp4 );
                NewCellProperties[1].rho_v[1] += ( temp3 * temp4 );
			}

			for( j=0; j<SPECIES; j++ )
			{
			    fWeight = ( 2.0 * CellProperties.TE_KE[1][j] ) / ( NewCellProperties[0].TE_KE[1][j] + NewCellProperties[1].TE_KE[1][j] );
			    NewCellProperties[0].TE_KE[1][j] *= fWeight;
			    NewCellProperties[1].TE_KE[1][j] *= fWeight;
			}
		}

		pNewCell[0] = new CAdaptiveMeshCell( &(NewCellProperties[0]) );
		pNewCell[1] = new CAdaptiveMeshCell( &(NewCellProperties[1]) );
                    
		pLeftCell->SetPointer( RIGHT, pNewCell[0] );
		pNewCell[0]->SetPointer( LEFT, pLeftCell );

		pNewCell[0]->SetPointer( RIGHT, pNewCell[1] );
		pNewCell[1]->SetPointer( LEFT, pNewCell[0] );
			
		if( pRightCell )
		{
            pNewCell[1]->SetPointer( RIGHT, pRightCell );
            pRightCell->SetPointer( LEFT, pNewCell[1] );
		}
		else
		{
            pNewCell[1]->SetPointer( RIGHT, NULL );
		}

        if( CellProperties.pIonFrac && Params.non_equilibrium_radiation)
        {
        	delete CellProperties.pIonFrac;
        }

		if(Params.use_kinetic_model)
		{
			delete CellProperties.pKinetic;
		}

		delete pActiveCell;

		pNextActiveCell = pNewCell[1];
            }
	}
	else
	{
            pNextActiveCell = pRightCell;
	}
    }

} while( iRestricted );

if(Params.use_kinetic_model)
{
	CountCells();
	CreateIndexedCellList();
}
}

void CAdaptiveMesh::Solve( void )
{
int iOutputStepCount = 0;
double fNextOutputTime;

printf( "\nSolving...\n\n" );

fNextOutputTime = mesh_time + Params.OutputPeriod;

// Now time-step the mesh

while( mesh_time <= Params.Duration )
{
    iOutputStepCount++;

    if( iOutputStepCount == Params.output_every_n_time_steps )
    {
        printf( "Timestep = %.8e seconds : Time elapsed = %.4e seconds\n", mesh_delta_t, mesh_time );
		iOutputStepCount = 0;
    }

    Integrate();

    // If the output period has elapsed since the last output then write the profiles to a file
    if( mesh_time >= fNextOutputTime )
    {
        WriteToFile();
		fNextOutputTime += Params.OutputPeriod;
    }
}

printf( "\nDone!\n\n" );
}

void CAdaptiveMesh::Integrate( void )
{
PCELL pNextActiveCell, pPreviousCell = NULL, pNewCell;
CELLPROPERTIES CellProperties, NewCellProperties;
double delta_t;

if(Params.use_kinetic_model)
{
	int iCell = 0;
}

// The integration is 2nd order in time and uses the derivatives calculated at half the time-step
delta_t = 0.5 * mesh_delta_t;

pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &NewCellProperties );

	if(Params.non_equilibrium_radiation)
    {
	    // Create a new ionfrac object for the new cell
	    NewCellProperties.pIonFrac = new CIonFrac( NewCellProperties.pIonFrac, 0, pRadiation );
    }

	if(Params.use_kinetic_model)
    {
		NewCellProperties.pKinetic = new CKinetic();
    }

    Half_Time_Step( &NewCellProperties, delta_t );

    // Create a new mesh cell at the current s but one time step advanced
    pNewCell = new CAdaptiveMeshCell( &NewCellProperties );

    // Set the RIGHT pointer to NULL
    pNewCell->SetPointer( RIGHT, NULL );
		
    // Set the BOTTOM pointer to the active cell (the cell from which the new cell has been derived)
    pNewCell->SetPointer( BOTTOM, pActiveCell );

    // If this is the left-most cell then set the LEFT pointer to NULL
    if( !( pActiveCell->pGetPointer( LEFT ) ) )
    {
        pNewCell->SetPointer( LEFT, NULL );
	
		// Also, set the pointer to the left-most cell at the current time to this pointer and change
		// the pointer to the start of the previous row accordingly
		pStartOfPreviousRow = pStartOfCurrentRow;
		pStartOfCurrentRow = pNewCell;
    }
    // This cell is not the left-most and so it will have a LEFT pointer
    else
    {
        // Set the RIGHT pointer of the previous cell to the new cell
		pPreviousCell->SetPointer( RIGHT, pNewCell );
		pNewCell->SetPointer( LEFT, pPreviousCell );
    }

    pPreviousCell = pNewCell;
    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );

	if(Params.use_kinetic_model)
    {
	    ppCellList[iCell] = pNewCell;
	    iCell++;
    }
}

// Calculate the physical quantities in the new cells
CalculatePhysicalQuantities();

// Evaluate the terms of the equations
EvaluateTerms( mesh_time + delta_t, &delta_t, FALSE );

pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    Full_Time_Step( &CellProperties, mesh_delta_t );

    pActiveCell->UpdateCellProperties( &CellProperties );

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

if(Params.adapt)
{
	// Adapt the mesh
	Adapt();
}

// Calculate the physical quantities
CalculatePhysicalQuantities();

// Evaluate the terms of the equations
EvaluateTerms( mesh_time + mesh_delta_t, &delta_t, TRUE );

// Limit time-step increases to be within a specified fractional amount of the previous time-step
if( delta_t > mesh_delta_t )
{
    if( delta_t / mesh_delta_t > Params.time_step_increase_limit )
    {
    	delta_t = Params.time_step_increase_limit * mesh_delta_t;
    }
}

// The mesh has been time-stepped
mesh_time += mesh_delta_t;
mesh_delta_t = delta_t;

// Free the previous row in order to conserve memory
FreePreviousRow();
}

void CAdaptiveMesh::FreeCurrentRow( void )
{
CELLPROPERTIES CellProperties;

PCELL pNextActiveCell;

// Delete all of the cells by traversing the mesh from the left-most cell at the current time
pNextActiveCell = pStartOfCurrentRow;

// This part deletes all of the cells along s at constant t
while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );
    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );

	if(Params.non_equilibrium_radiation)
    {
    	delete CellProperties.pIonFrac;
    }

	if(Params.use_kinetic_model)
    {
		delete CellProperties.pKinetic;
    }

    delete pActiveCell;
}
}

void CAdaptiveMesh::FreePreviousRow( void )
{
CELLPROPERTIES CellProperties;

PCELL pNextActiveCell;

pNextActiveCell = pStartOfPreviousRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );
    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );

	if(Params.non_equilibrium_radiation)
    {
		delete CellProperties.pIonFrac;
    }

	if(Params.use_kinetic_model)
    {
		delete CellProperties.pKinetic;
    }

    delete pActiveCell;
}
}

void CAdaptiveMesh::WriteToFile( void )
{
FILE *pAMRFile;
char szAMRFilename[256];

if(Params.write_file_physical)
{
	FILE *pPhysicalFile;
	char szPhysicalFilename[256];
	sprintf( szPhysicalFilename, "%sprofile%i.phy", Params.output_dir, iFileNumber );
	pPhysicalFile = fopen( szPhysicalFilename, "w" );
}

if(Params.non_equilibrium_radiation && Params.write_file_ion_populations)
{
	FILE *pNEqIonFile;
	char szNEqIonFilename[256];
	sprintf( szNEqIonFilename, "%sprofile%i.ine", Params.output_dir, iFileNumber );
	pNEqIonFile = fopen( szNEqIonFilename, "w" );
}

if(Params.write_file_scales)
{
	FILE *pScaleFile;
	char szScaleFilename[256];
	sprintf( szScaleFilename, "%sprofile%i.scl", Params.output_dir, iFileNumber );
	pScaleFile = fopen( szScaleFilename, "w" );
}

if(Params.write_file_terms)
{
	FILE *pTermsFile;
	char szTermsFilename[256];
	int iTerm;
	sprintf( szTermsFilename, "%sprofile%i.trm", Params.output_dir, iFileNumber );
	pTermsFile = fopen( szTermsFilename, "w" );
}

PCELL pNextActiveCell;
CELLPROPERTIES CellProperties;

int iNumberOfCells = 0, j;

// Write data into the files

pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    iNumberOfCells++;

    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

	if(Params.write_file_physical)
    {
	    fprintf( pPhysicalFile, "%.8e\t%.8e\t%.8e", CellProperties.s[1], CellProperties.v[1], CellProperties.Cs );

	    for( j=0; j<SPECIES; j++ )
	        fprintf( pPhysicalFile, "\t%.8e", CellProperties.n[j] );

	    for( j=0; j<SPECIES; j++ )
	        fprintf( pPhysicalFile, "\t%.8e", CellProperties.P[1][j] );

	    for( j=0; j<SPECIES; j++ )
	        fprintf( pPhysicalFile, "\t%.8e", CellProperties.T[j] );

	    for( j=0; j<SPECIES; j++ )
	        fprintf( pPhysicalFile, "\t%.8e", CellProperties.Fc[1][j] );

	    fprintf( pPhysicalFile, "\n" );
    }

    if(Params.non_equilibrium_radiation && Params.write_file_ion_populations)
	{
	    fprintf( pNEqIonFile, "%.8e", CellProperties.s[1] );
	    CellProperties.pIonFrac->WriteAllIonFracToFile( pNEqIonFile );
    }

	if(Params.write_file_scales)
    {
	    fprintf( pScaleFile, "%.8e\t%.8e\t%.8e", CellProperties.s[1], CellProperties.cell_width, CellProperties.advection_delta_t );

	    for( j=0; j<SPECIES; j++ )
	        fprintf( pScaleFile, "\t%.8e", CellProperties.conduction_delta_t[j] );

	    fprintf( pScaleFile, "\t%.8e", CellProperties.viscosity_delta_t );
	    fprintf( pScaleFile, "\t%.8e", CellProperties.collision_delta_t );
	    fprintf( pScaleFile, "\t%.8e", CellProperties.radiation_delta_t );
		
		if(Params.non_equilibrium_radiation)
		{
		    fprintf( pScaleFile, "\t%.8e", CellProperties.atomic_delta_t );
		}
	    
		fprintf( pScaleFile, "\n" );
    }

	if(Params.write_file_terms)
	{
	    fprintf( pTermsFile, "%.8e\n", CellProperties.s[1] );

	    fprintf( pTermsFile, "%.8e", CellProperties.drhobydt );
	    for( iTerm=0; iTerm<MASS_TERMS; iTerm++ )
	        fprintf( pTermsFile, "\t%.8e", CellProperties.rho_term[iTerm] );

	    fprintf( pTermsFile, "\n" );

	    fprintf( pTermsFile, "%.8e", CellProperties.drho_vbydt );
	    for( iTerm=0; iTerm<MOMENTUM_TERMS; iTerm++ )
	        fprintf( pTermsFile, "\t%.8e", CellProperties.rho_v_term[iTerm] );

	    fprintf( pTermsFile, "\n" );

	    for( j=0; j<SPECIES; j++ )
	    {
	        fprintf( pTermsFile, "%.8e", CellProperties.dTE_KEbydt[j] );
			for( iTerm=0; iTerm<ENERGY_TERMS; iTerm++ )
	            fprintf( pTermsFile, "\t%.8e", CellProperties.TE_KE_term[iTerm][j] );

			fprintf( pTermsFile, "\n" );
	    }
	}

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

if(Params.write_file_physical)
{
	fclose( pPhysicalFile );
}

if(Params.non_equilibrium_radiation && Params.write_file_ion_populations)
{
	fclose( pNEqIonFile );
}

if(Params.write_file_scales)
{
	fclose( pScaleFile );
}

if(Params.write_file_terms)
{
	fclose( pTermsFile );
}

// Create the .amr file so that the simulation can be continued from the current output if necessary

sprintf( szAMRFilename, "%sprofile%i.amr", Params.output_dir, iFileNumber );

pAMRFile = fopen( szAMRFilename, "w" );

fprintf( pAMRFile, "%g\n%i\n%.16e\n%i\n", mesh_time, iFileNumber, Params.L, iNumberOfCells );

pNextActiveCell = pStartOfCurrentRow;

while( pNextActiveCell )
{
    pActiveCell = pNextActiveCell;
    pActiveCell->GetCellProperties( &CellProperties );

    fprintf( pAMRFile, "%.16e\t%.16e\t%.16e\t%.16e", CellProperties.s[1], CellProperties.cell_width, CellProperties.rho[1], CellProperties.rho_v[1] );
    for( j=0; j<SPECIES; j++ )
        fprintf( pAMRFile, "\t%.16e", CellProperties.TE_KE[1][j] );

    fprintf( pAMRFile, "\t%i", CellProperties.iRefinementLevel );
    for( j=1; j<=Params.max_refinement_level; j++ )
        fprintf( pAMRFile, "\t%i", CellProperties.iUniqueID[j] );

    fprintf( pAMRFile, "\n" );

    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
}

fclose( pAMRFile );

if(Params.use_kinetic_model)
{
	FILE *pDFNFile;
	char szDFNFilename[256];
	double *pupsilon, *pMaxDFN_ee, *pNonMaxDFN;

	// Write the distribution functions to a file
	sprintf( szDFNFilename, "%sprofile%i.dfn", Params.output_dir, iFileNumber );

	pDFNFile = fopen( szDFNFilename, "w" );

	pNextActiveCell = pStartOfCurrentRow;

	while( pNextActiveCell )
	{
	    pActiveCell = pNextActiveCell;
	    pActiveCell->GetCellProperties( &CellProperties );

	    // Write the grid cell locations along the top row of the file
	    fprintf( pDFNFile, "%.8e\t", CellProperties.s[1] );

	    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	}

	// Write the thermal speeds along the next row of the file
	pNextActiveCell = pStartOfCurrentRow;
	pActiveCell = pNextActiveCell;
	pActiveCell->GetCellProperties( &CellProperties );
	pupsilon = CellProperties.pKinetic->Get_pupsilon();
	fprintf( pDFNFile, "\n" );
	for( j=0; j<DISTRIBUTION_DATA_POINTS; j++ )
	    fprintf( pDFNFile, "%.8e\t", pupsilon[j] );

	pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
	fprintf( pDFNFile, "\n" );
	for( j=0; j<DISTRIBUTION_DATA_POINTS; j++ )
	    fprintf( pDFNFile, "%.8e\t", log10( pMaxDFN_ee[j] ) );

	pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	pActiveCell = pNextActiveCell;
	pActiveCell->GetCellProperties( &CellProperties );
	pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
	fprintf( pDFNFile, "\n" );
	for( j=0; j<DISTRIBUTION_DATA_POINTS; j++ )
	    fprintf( pDFNFile, "%.8e\t", log10( pMaxDFN_ee[j] ) );

	pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	while( pNextActiveCell->pGetPointer( RIGHT )->pGetPointer( RIGHT ) )
	{
	    pActiveCell = pNextActiveCell;
	    pActiveCell->GetCellProperties( &CellProperties );
		
	    pNonMaxDFN = CellProperties.pKinetic->Get_pNonMaxDFN();

	    fprintf( pDFNFile, "\n" );
	    for( j=0; j<DISTRIBUTION_DATA_POINTS; j++ )
	        fprintf( pDFNFile, "%.8e\t", log10( pNonMaxDFN[j] ) );

	    pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	}

	pActiveCell = pNextActiveCell;
	pActiveCell->GetCellProperties( &CellProperties );
	pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
	fprintf( pDFNFile, "\n" );
	for( j=0; j<DISTRIBUTION_DATA_POINTS; j++ )
	    fprintf( pDFNFile, "%.8e\t", log10( pMaxDFN_ee[j] ) );

	pNextActiveCell = pActiveCell->pGetPointer( RIGHT );
	pActiveCell = pNextActiveCell;
	pActiveCell->GetCellProperties( &CellProperties );
	pMaxDFN_ee = CellProperties.pKinetic->Get_pMaxDFN_ee();
	fprintf( pDFNFile, "\n" );
	for( j=0; j<DISTRIBUTION_DATA_POINTS; j++ )
	    fprintf( pDFNFile, "%.8e\t", log10( pMaxDFN_ee[j] ) );

	fclose( pDFNFile );
}

iFileNumber++;
}
