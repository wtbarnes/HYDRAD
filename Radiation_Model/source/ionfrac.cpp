// ****
// *
// * Ionisation Fraction Class Function Bodies for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 10/29/2015
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ionfrac.h"
#include "config.h"
#include "../../Resources/source/file.h"
#include "../../Resources/source/fitpoly.h"
#include "../../Resources/source/xmlreader.h"


CIonFrac::CIonFrac( CIonFrac *pIonFrac, char *szFilename, PRADIATION pRadiationObj )
{
Initialise( pIonFrac, szFilename, pRadiationObj );
}

CIonFrac::~CIonFrac( void )
{
FreeAll();
}

void CIonFrac::Initialise( CIonFrac *pIonFrac, char *szFilename, PRADIATION pRadiationObj )
{
int i, j, iBytes, *pAtomicNumber = NULL;
double **ppInitIonFrac, **ppInitdnibydt;

// Set the radiation object pointer
pRadiation = pRadiationObj;

// If pIonFrac is NULL then initialise the ion fractional populations using the configuration file
if( !pIonFrac )
{
    
	//Parse XML configuration file
	TiXmlDocument doc(szFilename);
	
	//Check if loaded
	bool loadOK = doc.LoadFile();
	if(!loadOK)
	{
		printf("Failed to load XML configuration file %s.\n",szFilename);
		//TODO: Exit or break out from here
	}
	
	//Get document root
	TiXmlElement *root = doc.FirstChildElement();
	
	//Read in parameters
	cutoff_ion_fraction = atof(check_element(recursive_read(root,"cutoff_ion_fraction"),"cutoff_ion_fraction")->GetText());
	NumElements = atoi(check_element(recursive_read(root,"numElements"),"numElements")->GetText());

    // Allocate sufficient memory to hold the pointers to the ionisation fractions and their
    // rates of change with respect to time for each element
    iBytes = sizeof(double) * NumElements;
    ppIonFrac = (double**)malloc( iBytes );
    ppdnibydt = (double**)malloc( iBytes );

    // Allocate sufficient memory to hold the list of atomic numbers
    pZ = (int*)malloc( sizeof(int) * NumElements );
	
	//Loop over elements
	i = 0;
	TiXmlElement *elementList = check_element(recursive_read(root,"elements"),"elements");
	for(TiXmlElement *child = elementList->FirstChildElement(); child != NULL; child=child->NextSiblingElement())
	{
		//Check counter
		if(i>=NumElements)
		{
			printf("Warning: Element list length > NumElements variable. Some elements may not be read.\n\n");
			break;
		}
		
		//Get atomic number
		pZ[i] = atoi(child->Attribute("number"));
		
		// Allocate sufficient memory to hold the ionisation fractions and their rates of
        // change with respect to time for each element
        iBytes = sizeof(double) * ( pZ[i] + 1 );
        ppIonFrac[i] = (double*)malloc( iBytes );
        ppdnibydt[i] = (double*)malloc( iBytes );
	
        // Zero the arrays containing the rates of change with respect to time of the ionisation
        // fractions
        memset( ppdnibydt[i], 0, iBytes );
		
		//Increment counter
		i++;
	}
	
	//Free document tree
	doc.Clear();
}
else
{
    // Get the element info from the ionfrac object being used to initialise the new
    // ionfrac object
    pAtomicNumber = pIonFrac->pGetElementInfo( &NumElements );
	//Get ion fraction cutoff property
	cutoff_ion_fraction = pIonFrac->cutoff_ion_fraction;

    // Allocate sufficient memory to hold the pointers to the ionisation fractions and their
    // rates of change with respect to time for each element
    iBytes = sizeof(double) * NumElements;
    ppIonFrac = (double**)malloc( iBytes );
    ppdnibydt = (double**)malloc( iBytes );
        
    // Allocate sufficient memory to hold the list of atomic numbers
    pZ = (int*)malloc( sizeof(int) * NumElements );

	// Get the pointers to the ionfracs and dnibydt's to copy into the new ionfrac object
    ppInitIonFrac = pIonFrac->ppGetIonFrac();
    ppInitdnibydt = pIonFrac->ppGetdnibydt();

    for( i=0; i<NumElements; i++ )
    {
        // Get the atomic number
        pZ[i] = pAtomicNumber[i];

        // Allocate sufficient memory to hold the ionisation fractions and their rates of
        // change with respect to time for each element
        iBytes = sizeof(double) * ( pZ[i] + 1 );
        ppIonFrac[i] = (double*)malloc( iBytes );
        ppdnibydt[i] = (double*)malloc( iBytes );

        // Get the ionisation fractions and dnibydt's
        for( j=0; j<=pZ[i]; j++ )
	{
            ppIonFrac[i][j] = ppInitIonFrac[i][j];
            ppdnibydt[i][j] = ppInitdnibydt[i][j];
	}
    }
}
}

void CIonFrac::FreeAll( void )
{
int i;

for( i=0; i<NumElements; i++ )
{
    free( ppIonFrac[i] );
    free( ppdnibydt[i] );
}

free( ppIonFrac );
free( ppdnibydt );
free( pZ );
}

double** CIonFrac::ppGetIonFrac( void )
{
return ppIonFrac;
}

double* CIonFrac::pGetIonFrac( int iZ )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0;

return ppIonFrac[i];
}

void CIonFrac::WriteAllIonFracToFile( void *pFile )
{
int i, j;

for( i=0; i<NumElements; i++ )
{
    fprintf( (FILE*)pFile, "\n%i", pZ[i] );

    for( j=0; j<=pZ[i]; j++ )
        fprintf( (FILE*)pFile, "\t%.8e", ppIonFrac[i][j] );
}

fprintf( (FILE*)pFile, "\n" );
}

void CIonFrac::WriteIonFracToFile( void *pFile, int iZ )
{
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

fprintf( (FILE*)pFile, "\n%i", pZ[i] );

for( j=0; j<=pZ[i]; j++ )
    fprintf( (FILE*)pFile, "\t%.8e", ppIonFrac[i][j] );

fprintf( (FILE*)pFile, "\n" ); 
}

void CIonFrac::ReadAllIonFracFromFile( void *pFile )
{
int i, j;

for( i=0; i<NumElements; i++ )
{
    fscanf( (FILE*)pFile, "%i", &(pZ[i]) );

    for( j=0; j<=pZ[i]; j++ )
        ReadDouble( (FILE*)pFile, &(ppIonFrac[i][j]) );
}
}

void CIonFrac::ReadIonFracFromFile( void *pFile, int iZ )
{
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
	if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

fscanf( (FILE*)pFile, "%i", &(pZ[i]) );

for( j=0; j<=pZ[i]; j++ )
    ReadDouble( (FILE*)pFile, &(ppIonFrac[i][j]) );
}

double** CIonFrac::ppGetdnibydt( void )
{
return ppdnibydt;
}

double* CIonFrac::pGetdnibydt( int iZ )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0;

return ppdnibydt[i];
}

void CIonFrac::IntegrateAllIonFrac( double delta_t )
{
double fTotal;
int i, j;

for( i=0; i<NumElements; i++ )
{
    fTotal = 0.0;
	
    for( j=0; j<=pZ[i]; j++ )
    {
        ppIonFrac[i][j] += ppdnibydt[i][j] * delta_t;

	// Ensure the minimum ion fraction remains above the cut-off and is physically realistic
        if( ppIonFrac[i][j] < cutoff_ion_fraction )
            ppIonFrac[i][j] = 0.0;

        fTotal += ppIonFrac[i][j];
    }
	
    // Normalise the sum total of the ion fractional populations to 1
    pRadiation->Normalise( pZ[i], ppIonFrac[i], fTotal );
}
}

void CIonFrac::IntegrateIonFrac( int iZ, double delta_t )
{
double fTotal = 0.0;
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

for( j=0; j<=pZ[i]; j++ )
{        
    ppIonFrac[i][j] += ppdnibydt[i][j] * delta_t;

    // Ensure the minimum ion fraction remains above the cut-off and is physically realistic
    if( ppIonFrac[i][j] < cutoff_ion_fraction )
        ppIonFrac[i][j] = 0.0;

    fTotal += ppIonFrac[i][j];
}

// Normalise the sum total of the ion fractional populations to 1
pRadiation->Normalise( pZ[i], ppIonFrac[i], fTotal );
}

int* CIonFrac::pGetElementInfo( int *pNumElements )
{
*pNumElements = NumElements;

return pZ;
}

void CIonFrac::CopyAllIonFrac( CIonFrac *pIonFrac )
{
double **ppNewIonFrac;
int i, j;

ppNewIonFrac = pIonFrac->ppGetIonFrac();

for( i=0; i<NumElements; i++ )
    for( j=0; j<=pZ[i]; j++ )
        ppIonFrac[i][j] = ppNewIonFrac[i][j];
}

void CIonFrac::CopyIonFrac( int iZ, CIonFrac *pIonFrac )
{
double *pNewIonFrac;
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

pNewIonFrac = pIonFrac->pGetIonFrac( iZ );

for( j=0; j<=pZ[i]; j++ )
    ppIonFrac[i][j] = pNewIonFrac[j];
}

void CIonFrac::CopyAlldnibydt( CIonFrac *pIonFrac )
{
double **ppNewdnibydt;
int i, j;

ppNewdnibydt = pIonFrac->ppGetdnibydt();

for( i=0; i<NumElements; i++ )
    for( j=0; j<=pZ[i]; j++ )
        ppdnibydt[i][j] = ppNewdnibydt[i][j];
}

void CIonFrac::Copydnibydt( int iZ, CIonFrac *pIonFrac )
{
double *pNewdnibydt;
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

pNewdnibydt = pIonFrac->pGetdnibydt( iZ );

for( j=0; j<=pZ[i]; j++ )
    ppdnibydt[i][j] = pNewdnibydt[j];
}

void CIonFrac::InterpolateAllIonFrac( double *x, double ***pppIonFrac, int iPoints, double s )
{
double y[5], error;
int i, j, n;

if( iPoints < 3 )
{
    for( i=0; i<NumElements; i++ )
    {
        for( j=0; j<=pZ[i]; j++ )
	{
            for( n=1; n<=iPoints; n++ )
                y[n] = pppIonFrac[n][i][j];

            LinearFit( x, y, s, &(ppIonFrac[i][j]) );
	}
    }
}
else
{
    for( i=0; i<NumElements; i++ )
    {
        for( j=0; j<=pZ[i]; j++ )
	{
            for( n=1; n<=iPoints; n++ )
                y[n] = pppIonFrac[n][i][j];

            FitPolynomial4( x, y, s, &(ppIonFrac[i][j]), &error );
	}
    }
}
}

void CIonFrac::InterpolateIonFrac( int iZ, double *x, double ***pppIonFrac, int iPoints, double s )
{
double y[5], error;
int i, j, n;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

if( iPoints < 3 )
{
    for( j=0; j<=iZ; j++ )
    {
        for( n=1; n<=iPoints; n++ )
            y[n] = pppIonFrac[n][i][j];

	LinearFit( x, y, s, &(ppIonFrac[i][j]) );
    }
}
else
{
    for( j=0; j<=iZ; j++ )
    {
        for( n=1; n<=iPoints; n++ )
            y[n] = pppIonFrac[n][i][j];

	FitPolynomial4( x, y, s, &(ppIonFrac[i][j]), &error );
    }
}
}

void CIonFrac::ResetIonFrac( int iZ, double flog_10T )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

// Get the equilibrium ionisation fractions
pRadiation->GetEquilIonFrac( iZ, ppIonFrac[i], flog_10T );
}

void CIonFrac::ResetIonFrac( int iZ, double flog_10T, double flog_10n )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

// Get the equilibrium ionisation fractions
pRadiation->GetEquilIonFrac( iZ, ppIonFrac[i], flog_10T, flog_10n );
}

void CIonFrac::ResetAllIonFrac( double flog_10T )
{
int i;

for( i=0; i<NumElements; i++ )
{
    // Get the equilibrium ionisation fractions
    pRadiation->GetEquilIonFrac( pZ[i], ppIonFrac[i], flog_10T );
}
}

void CIonFrac::ResetAllIonFrac( double flog_10T, double flog_10n )
{
int i;

for( i=0; i<NumElements; i++ )
{
    // Get the equilibrium ionisation fractions
    pRadiation->GetEquilIonFrac( pZ[i], ppIonFrac[i], flog_10T, flog_10n );
}
}