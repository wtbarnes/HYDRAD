// ****
// *
// * Radiation Class Function Bodies for Radiative Emission Model
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 11/20/2015
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "radiation.h"
#include "../../Resources/source/file.h"
#include "../../Resources/source/fitpoly.h"
#include "../../Resources/source/constants.h"
#include "../../Resources/source/xmlreader.h"


CRadiation::CRadiation( char *szFilename )
{
	Initialise(szFilename);
}

CRadiation::~CRadiation( void )
{
FreeAll();
}

void CRadiation::Initialise(char *szFilename)
{
	//Declarations
	char szAtomicDBFilename[256], szRangesFilename[256], szAbundFilename[256], szEmissFilename[256], szRatesFilename[256], szIonFracFilename[256];
	char tempEmiss[256], tempRates[256], tempBalances[256], tempSymb[256];
	int i = 0;
	
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
	
	//Retrieve configuration elements
	sprintf(szAtomicDBFilename,"%s",check_element(recursive_read(root,"atomicDB"),"atomicDB")->GetText());
	sprintf(szRangesFilename,"%sranges/%s",szAtomicDBFilename,check_element(recursive_read(root,"rangesFile"),"rangesFile")->GetText());
	sprintf(tempEmiss,"%semissivities/%s",szAtomicDBFilename,check_element(recursive_read(root,"emissivityDir"),"emissivityDir")->GetText());
	sprintf(szAbundFilename,"%sabundances/%s",szAtomicDBFilename,check_element(recursive_read(root,"abundanceFile"),"abundanceFile")->GetText());
	sprintf(tempRates,"%srates/%s",szAtomicDBFilename,check_element(recursive_read(root,"rates_balancesDir"),"rates_balancesDir")->GetText());
	sprintf(tempBalances,"%sbalances/%s",szAtomicDBFilename,check_element(recursive_read(root,"rates_balancesDir"),"rates_balancesDir")->GetText());
	NumElements = atoi(check_element(recursive_read(root,"numElements"),"numElements")->GetText());
	max_optically_thin_density = atof(check_element(recursive_read(root,"max_optically_thin_density"),"max_optically_thin_density")->GetText());
	
	//Set DB filename for use outside of radiation class
	sprintf(atomicDBFilename,"%s",szAtomicDBFilename);
	
	//Allocate memory for array of element objects
	ppElements = (PPELEMENT)malloc( sizeof( CElement ) * NumElements ); // Allocate sufficient memory to hold the pointers to each element object
	pZ = (int*)malloc( sizeof(int) * NumElements ); // Allocate sufficient memory to hold the list of atomic numbers
	
	//Loop over elements
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
		//Get atomic symbol
		sprintf(tempSymb,"%s",child->Attribute("name"));
	    // Construct the filenames
	    sprintf( szEmissFilename,"%s%s.em",tempEmiss,tempSymb);
	    sprintf( szRatesFilename,"%s%s.rts",tempRates,tempSymb);
	    sprintf( szIonFracFilename,"%s%s.bal",tempBalances,tempSymb);
	    // Instantiate each element object
	    ppElements[i] = new CElement( pZ[i], szRangesFilename, szAbundFilename, szEmissFilename, szRatesFilename, szIonFracFilename );
		// Set initial configuration elements from file
		ppElements[i]->SetConfigVars(root);
		//Increment counter
		i++;
	}
	
	//Free document tree
	doc.Clear();
	
	// Open the temperature and density ranges file and allocate memory to store these quantities
	OpenRangesFile( szRangesFilename );
	
	// Calculate the total phi of all radiating elements as a function of temperature and density
	CalculateTotalPhi();
}

void CRadiation::OpenRangesFile( char *szRangesFilename )
{
FILE *pFile;
int i;
char buffer;

// Open the ranges file
pFile = fopen( szRangesFilename, "r" );

// Read the comment line
buffer = 0;
while( buffer != '.' )
    fscanf( pFile, "%c", &buffer );

// Get the number of temperature and density values
fscanf( pFile, "%i", &NumTemp );
fscanf( pFile, "%i", &NumDen );

// Allocate arrays to hold the log_10 temperature and density values
pTemp = (double*)malloc( sizeof(double) * NumTemp );
pDen = (double*)malloc( sizeof(double) * NumDen );

// Read the comment line
buffer = 0;
while( buffer != '.' )
    fscanf( pFile, "%c", &buffer );

// Get the log_10 temperature values
for( i=0; i<NumTemp; i++ )
    ReadDouble( pFile, &(pTemp[i]) );

// Read the comment line
buffer = 0;
while( buffer != '.' )
    fscanf( pFile, "%c", &buffer );

// Get the log_10 density values
for( i=0; i<NumDen; i++ )
    ReadDouble( pFile, &(pDen[i]) );

fclose( pFile );
}

void CRadiation::CalculateTotalPhi( void )
{
int i, j, k, l, NumTempxNumDen;

// Calculate the 2D array sizes
NumTempxNumDen = NumTemp * NumDen;

// Allocate an array to hold the total values of phi( n, T ) for the element
pTotalPhi = (double*)malloc( sizeof(double) * NumTempxNumDen );
for( l=0; l<NumTempxNumDen; l++ )
	pTotalPhi[l] = 0.0;

l=0;
for( k=0; k<NumDen; k++ )
    for( j=0; j<NumTemp; j++ )
    {
	for( i=0; i<NumElements; i++ )
	    pTotalPhi[l] += ppElements[i]->GetEmissivity( pTemp[j], pDen[k] );
	l++;
    }
}

void CRadiation::FreeAll( void )
{
int i;

free( pTotalPhi );

free( pDen );
free( pTemp );

for( i=0; i<NumElements; i++ )
    delete ppElements[i];
	
free( ppElements );
free( pZ );
}

int* CRadiation::pGetAtomicNumbers( int *iNumElements )
{
*iNumElements = NumElements;
return pZ;
}

double CRadiation::GetAbundance( int iZ )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0.0;

return ppElements[i]->GetAbundance();
}

void CRadiation::GetEquilIonFrac( int iZ, double *pni, double flog_10T )
{
double fTotal = 0.0;
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

// Get the set of equilibrium ion fractional populations for the specified element

for( j=0; j<=iZ; j++ )
{
    pni[j] = ppElements[i]->GetEquilIonFrac( j+1, flog_10T );
    fTotal += pni[j];
}

// Normalise the sum total of the ion fractional populations to 1
Normalise( iZ, pni, fTotal );
}

void CRadiation::GetEquilIonFrac( int iZ, double *pni, double flog_10T, double flog_10n )
{
double fTotal = 0.0;
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

// Get the set of equilibrium ion fractional populations for the specified element

for( j=0; j<=iZ; j++ )
{
    pni[j] = ppElements[i]->GetEquilIonFrac( j+1, flog_10T, flog_10n );
    fTotal += pni[j];
}

// Normalise the sum total of the ion fractional populations to 1
Normalise( iZ, pni, fTotal );
}

void CRadiation::WriteEquilIonFracToFile( void *pFile, int iZ, double flog_10T )
{
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

for( j=0; j<=iZ; j++ )
    fprintf( (FILE*)pFile, "\t%.8e", ppElements[i]->GetEquilIonFrac( j+1, flog_10T ) );

fprintf( (FILE*)pFile, "\n" );
}

void CRadiation::WriteEquilIonFracToFile( void *pFile, int iZ, double flog_10T, double flog_10n )
{
int i, j;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

for( j=0; j<=iZ; j++ )
    fprintf( (FILE*)pFile, "\t%.8e", ppElements[i]->GetEquilIonFrac( j+1, flog_10T, flog_10n ) );

fprintf( (FILE*)pFile, "\n" );
}

void CRadiation::WriteEquilIonFracToFile( void *pFile, double flog_10T )
{
int i, j;

for( i=0; i<NumElements; i++ )
{
    fprintf( (FILE*)pFile, "\n%i", pZ[i] );

    for( j=0; j<=pZ[i]; j++ )
        fprintf( (FILE*)pFile, "\t%.8e", ppElements[i]->GetEquilIonFrac( j+1, flog_10T ) );
}

fprintf( (FILE*)pFile, "\n" );
}

void CRadiation::WriteEquilIonFracToFile( void *pFile, double flog_10T, double flog_10n )
{
int i, j;

for( i=0; i<NumElements; i++ )
{
    fprintf( (FILE*)pFile, "\n%i", pZ[i] );

    for( j=0; j<=pZ[i]; j++ )
        fprintf( (FILE*)pFile, "\t%.8e", ppElements[i]->GetEquilIonFrac( j+1, flog_10T, flog_10n ) );
}

fprintf( (FILE*)pFile, "\n" );
}

void CRadiation::Normalise( int iZ, double *pni, double fTotal )
{
int i;

for( i=0; i<=iZ; i++ )
    pni[i] = pni[i] / fTotal;
}

double CRadiation::GetRadiation( int iZ, int iIon, double flog_10T, double flog_10n )
{
double fEmiss, n;
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0.0;

fEmiss = ppElements[i]->GetEmissivity( iIon, flog_10T, flog_10n );

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return ( n * n ) * fEmiss;
// NOTE: free-free radiation is NOT added here
}

double CRadiation::GetRadiation( int iZ, double flog_10T, double flog_10n )
{
double fEmiss, n;
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0.0;

fEmiss = ppElements[i]->GetEmissivity( flog_10T, flog_10n );

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return ( n * n ) * fEmiss;
// NOTE: free-free radiation is NOT added here
}

double CRadiation::GetRadiation( double flog_10T, double flog_10n )
{
/*
double fEmiss = 0.0, n;
int i;

for( i=0; i<NumElements; i++ )
    fEmiss += ppElements[i]->GetEmissivity( flog_10T, flog_10n );
*/

double x1[5], x2[5], **y, *pfTemp, result, error, n;
int j, k, l;

// Select the four temperature values surrounding the desired one

// If the temperature is out of range then set it to the appropriate limit
if( flog_10T < pTemp[0] )
    flog_10T = pTemp[0];
else if( flog_10T > pTemp[NumTemp-1] )
    flog_10T = pTemp[NumTemp-1];

for( j=0; j<NumTemp; j++ )
    if( pTemp[j] >= flog_10T ) break;

// Deal with the special cases where there aren't two values either side of the
// desired one
if( j < 2 ) j = 2;
else if( j == NumTemp-1 ) j = NumTemp-2;

x1[1] = pTemp[j-2];
x1[2] = pTemp[j-1];
x1[3] = pTemp[j];
x1[4] = pTemp[j+1];

// Select the four density values surrounding the desired one

// If the density is out of range then set it to the appropriate limit
if( flog_10n < pDen[0] )
    flog_10n = pDen[0];
else if ( flog_10n > pDen[NumDen-1] )
    flog_10n = pDen[NumDen-1];

for( k=0; k<NumDen; k++ )
    if( pDen[k] >= flog_10n ) break;

// Deal with the special cases where there aren't two values either side of the
// desired one
if( k < 2 ) k = 2;
else if( k == NumDen-1 ) k = NumDen-2;

x2[1] = pDen[k-2];
x2[2] = pDen[k-1];
x2[3] = pDen[k];
x2[4] = pDen[k+1];

// We are using the j-2, j-1, j and j+1 'th temperature values
// We are using the k-2, k-1, k and k+1 'th density values

// Select the sixteen phi( n, T ) values corresponding to the grid

// Allocate an array of pointers to pointers for the values
y = (double**)alloca( sizeof(double) * 5 );

// Allocate an array to hold the values corresponding to the specified range of
// densities and temperatures
for( l=1; l<=4; l++ )
    y[l] = (double*)alloca( sizeof(double) * 5 );

for( l=1; l<=4; l++ )
{
    // Point to the start of the phi( n, T ) values for the element
    pfTemp = pTotalPhi;

    // Skip to the set corresponding to the l'th density value and get the
    // values of total phi( n, T ) corresponding to the four temperature values
    pfTemp += ( k + l - 3 ) * NumTemp;

    y[1][l] = *( pfTemp + ( j - 2 ) );
    y[2][l] = *( pfTemp + ( j - 1 ) );
    y[3][l] = *( pfTemp + j );
    y[4][l] = *( pfTemp + ( j + 1 ) );
}

// Perform the 2D polynomial interpolation
FitPolynomial2D( x1, x2, y, 4, 4, flog_10T, flog_10n, &result, &error );

// Check the value of phi( n, T ) is physically realistic
if( result < 0.0 ) result = 0.0;

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return ( n * n ) * result;
// NOTE: free-free radiation is NOT added here
}

void CRadiation::Getdnibydt( int iZ, double flog_10T, double flog_10n, double *pni0, double *pni1, double *pni2, double *pni3, double *pni4, double *s, double *s_pos, double *pv, double delta_s, double *pdnibydt, double *pTimeScale )
{
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return;

ppElements[i]->Getdnibydt( flog_10T, flog_10n, pni0, pni1, pni2, pni3, pni4, s, s_pos, pv, delta_s, pdnibydt, pTimeScale );
}

void CRadiation::GetAlldnibydt( double flog_10T, double flog_10n, double **ppni0, double **ppni1, double **ppni2, double **ppni3, double **ppni4, double *s, double *s_pos, double *pv, double delta_s, double **ppdnibydt, double *pTimeScale )
{
double TimeScale, SmallestTimeScale;
int i;

SmallestTimeScale = LARGEST_DOUBLE;

for( i=0; i<NumElements; i++ )
{
    ppElements[i]->Getdnibydt( flog_10T, flog_10n, ppni0[i], ppni1[i], ppni2[i], ppni3[i], ppni4[i], s, s_pos, pv, delta_s, ppdnibydt[i], &TimeScale );

    if( TimeScale < SmallestTimeScale )
        SmallestTimeScale = TimeScale;
}

*pTimeScale = SmallestTimeScale;
}

double CRadiation::GetRadiation( int iZ, int iIon, double flog_10T, double flog_10n, double ni )
{
double fEmiss, n;
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0.0;

fEmiss = ppElements[i]->GetEmissivity( iIon, flog_10T, flog_10n, ni );

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return ( n * n ) * fEmiss;
// NOTE: free-free radiation is NOT added here
}

double CRadiation::GetRadiation( int iZ, double flog_10T, double flog_10n, double *pni )
{
double fEmiss, n;
int i;

// Find the required element
for( i=0; i<NumElements; i++ )
    if( iZ == pZ[i] ) break;

if( i == NumElements ) return 0.0;

fEmiss = ppElements[i]->GetEmissivity( flog_10T, flog_10n, pni );

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return ( n * n ) * fEmiss;
// NOTE: free-free radiation is NOT added here
}

double CRadiation::GetRadiation( double flog_10T, double flog_10n, double **ppni )
{
double fEmiss = 0.0, n;
int i;

for( i=0; i<NumElements; i++ )
    fEmiss += ppElements[i]->GetEmissivity( flog_10T, flog_10n, ppni[i] );

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return ( n * n ) * fEmiss;
// NOTE: free-free radiation is NOT added here
}

double CRadiation::GetPowerLawRad( double flog_10T, double flog_10n )
{
double chi, alpha, fEmiss, n;

// The formulation used here is based on the calculations of John Raymond (1994, private communication)
// and twice the coronal abundances of Meyer (1985)

if( flog_10T <= 4.97 )
{
    chi = 1.09e-31;
    alpha = 2.0;
}
else if( flog_10T <= 5.67 )
{
    chi = 8.87e-17;
    alpha = -1.0;
}
else if( flog_10T <= 6.18 )
{
    chi = 1.90e-22;
    alpha = 0.0;
}
else if( flog_10T <= 6.55 )
{
    chi = 3.53e-13;
    alpha = -3.0/2.0;
}
else if( flog_10T <= 6.90 )
{
    chi = 3.46e-25;
    alpha = 1.0/3.0;
}
else if( flog_10T <= 7.63 )
{
    chi = 5.49e-16;
    alpha = -1.0;
}
else
{
    chi = 1.96e-27;
    alpha = 1.0/2.0;
}

fEmiss = chi * pow( 10.0, (alpha*flog_10T) );

if( flog_10n > max_optically_thin_density )
    flog_10n = max_optically_thin_density;

n = pow( 10.0, flog_10n );

return n * n * fEmiss;
// NOTE: free-free radiation is included in the parameter values for log_10 T > 7.63
}

double CRadiation::GetFreeFreeRad( double flog_10T, double flog_10n )
{
double SqrtT, n;

// Calculate the free-free emission due to thermal bremsstralung for a low-density and fully ionised plasma.
// The previous formulation used here was taken from Mason & Monsignori Fossi (1994, Astron. Astrophys. Rev., 6, 123) where (1.96e-27) is replaced with (2.40e-27)
// The current formulation is taken from the power-law fit for log_10 T > 7.63

SqrtT = pow( 10.0, (0.5*flog_10T) );
n = pow( 10.0, flog_10n );

return (1.96e-27) * SqrtT * n * n;
}
