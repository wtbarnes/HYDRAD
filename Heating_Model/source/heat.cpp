// ****
// *
// * A heating code to simulate different forms of heat deposition
// *
// * Class function bodies
// *
// * (c) Dr. Stephen J. Bradshaw
// *     
// * Date last modified: 25/09/2014
// *
// ****


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "heat.h"
#include "../../Resources/source/file.h"
#include "../../Resources/source/fitpoly.h"
#include "../../Resources/source/xmlreader.h"

CHeat::CHeat( TiXmlElement *heating_node, double fL )
{
Initialise( heating_node, fL );
}

CHeat::~CHeat( void )
{
FreeAll();
}

void CHeat::Initialise( TiXmlElement *heating_node, double fL )
{
// Get the length of the loop
fLoopLength = fL;

// GetHeatingData( szFilename );
GetHeatingDataXml(heating_node);
GetVALHeatingData(heating_node);
}

void CHeat::FreeAll( void )
{
int i;

for( i=0; i<2; i++ )
    free( ppVALHeating[i] );
free( ppVALHeating );

if( !NumActivatedEvents )
    return;

// Location, scale-length and maximum energy
free( s0episodic );
free( sHepisodic );
free( E0episodic );

// Start and end times of rise phase
free( tsRepisodic );
free( teRepisodic );

// Start and end times of decay phase
free( tsDepisodic );
free( teDepisodic );
}

void CHeat::GetHeatingDataXml(TiXmlElement *heating_node)
{	
	//Load static heating parameteters
	fDuration = atof(check_element(recursive_read(heating_node,"duration"),"duration")->GetText());
	s0quiescent = atof(check_element(recursive_read(heating_node,"bg_loc"),"bg_loc")->GetText());
	sHquiescent = atof(check_element(recursive_read(heating_node,"bg_spread"),"bg_spread")->GetText());
	E0quiescent = atof(check_element(recursive_read(heating_node,"bg_magnitude"),"bg_magnitude")->GetText());
	NumActivatedEvents = atoi(check_element(recursive_read(heating_node,"num_events"),"num_events")->GetText());
	
	//Return if only bg heating selected
	if(!NumActivatedEvents || NumActivatedEvents == 0)
	{
		return;
	}
	
	// Allocate sufficient memory to store heating information for each event
	// Location, scale-length and maximum energy
	s0episodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	sHepisodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	E0episodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	// Start and end times of rise phase
	tsRepisodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	teRepisodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	// Start and end times of decay phase
	tsDepisodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	teDepisodic = (double*)malloc( sizeof(double) * NumActivatedEvents );
	
	//Loop over event list
	int i = 0;
	TiXmlElement *eventList = check_element(recursive_read(heating_node,"events"),"events");
	for(TiXmlElement *child = eventList->FirstChildElement(); child != NULL; child=child->NextSiblingElement())
	{
		s0episodic[i] = atoi(child->Attribute("loc"));
		sHepisodic[i] = atoi(child->Attribute("spread"));
		E0episodic[i] = atoi(child->Attribute("magnitude"));
		tsRepisodic[i] = atoi(child->Attribute("rise_start"));
		teRepisodic[i] = atoi(child->Attribute("rise_end"));
		tsDepisodic[i] = atoi(child->Attribute("decay_start"));
		teDepisodic[i] = atoi(child->Attribute("decay_end"));
		i++;		
	}
}

void CHeat::GetVALHeatingData( TiXmlElement *heating_node )
{
char ValHeatingFile[512];
FILE *pFile;
int i;

//Get filename
sprintf(ValHeatingFile,"%s",check_element(recursive_read(heating_node,"val_heating_file"),"val_heating_file")->GetText());
// Open and read the configuration file
pFile = fopen( ValHeatingFile, "r" );

// Get the number of data points in the file
fscanf( pFile, "%i", &iVALHeatingDP );

// Allocate sufficient memory to hold the heating data
ppVALHeating = (double**)malloc( sizeof(double) * 2 );
for( i=0; i<2; i++ )
    ppVALHeating[i] = (double*)malloc( sizeof(double) * iVALHeatingDP );

for( i=0; i<iVALHeatingDP; i++ )
{
    // Array index [0][i] contain the spatial coordinate and [1][i] contain the volumetric heating rate
    ReadDouble( pFile, &(ppVALHeating[0][i]) );
    ReadDouble( pFile, &(ppVALHeating[1][i]) );
}

fclose( pFile );
}

double CHeat::CalculateQuiescentHeating( double s )
{
double fQuiescent = 0.0, term1;

// Left footpoint
if( E0quiescent )
{
    term1 = ( s - s0quiescent );
    term1 *= term1;

    fQuiescent = E0quiescent * exp( - term1 / (2.0*sHquiescent*sHquiescent) );
}

return fQuiescent;
}

double CHeat::CalculateEpisodicHeating( double s, double t )
{
double fEpisodic = 0.0, term1, term2;
int i;

for( i=0; i<NumActivatedEvents; i++ )
{
    if( t >= tsRepisodic[i] && t <= teDepisodic[i] )
    {
        if( t >= tsRepisodic[i] && t <= teRepisodic[i] )
        {
            term1 = ( s - s0episodic[i] );
            term1 *= term1;

            term2 = ( t - tsRepisodic[i] ) / ( teRepisodic[i] - tsRepisodic[i] );

            fEpisodic += E0episodic[i] * exp( - term1 / (2.0*sHepisodic[i]*sHepisodic[i]) ) * term2;
        }
        else if( t > teRepisodic[i] && t < tsDepisodic[i] )
        {
            term1 = ( s - s0episodic[i] );
        	term1 *= term1;

            fEpisodic += E0episodic[i] * exp( - term1 / (2.0*sHepisodic[i]*sHepisodic[i]) );
        }
        else if( t >= tsDepisodic[i] && t <= teDepisodic[i] )
        {
            term1 = ( s - s0episodic[i] );
            term1 *= term1;

            term2 = 1.0 - ( ( t - tsDepisodic[i] ) / ( teDepisodic[i] - tsDepisodic[i] ) );

            fEpisodic += E0episodic[i] * exp( - term1 / (2.0*sHepisodic[i]*sHepisodic[i]) ) * term2;
        }
    }
}

return fEpisodic;
}

double CHeat::CalculateHeating( double s, double t )
{
double fQuiescentHeating = 0.0, fEpisodicHeating = 0.0;

if( E0quiescent )
    fQuiescentHeating = CalculateQuiescentHeating( s );

if( NumActivatedEvents )
    fEpisodicHeating = CalculateEpisodicHeating( s, t );

return( fQuiescentHeating + fEpisodicHeating );
}

double CHeat::CalculateVALHeating( double flog10_rho_c )
{
int i;
double x[3], y[3], fVALHeating;

if( !iVALHeatingDP ) return 0.0;

// Trap limits
if( flog10_rho_c < ppVALHeating[0][0] ) return pow( 10.0, ppVALHeating[1][0] );
else if( flog10_rho_c > ppVALHeating[0][iVALHeatingDP-1] ) return pow( 10.0, ppVALHeating[1][iVALHeatingDP-1] );

for( i=0; i<iVALHeatingDP; i++ )
{
    if( flog10_rho_c <= ppVALHeating[0][i] ) break;
}

// Trap the special cases
if( i == 0 ) i = 1;
else if( i == iVALHeatingDP ) i = iVALHeatingDP - 1;

x[1] = ppVALHeating[0][i-1];
x[2] = ppVALHeating[0][i];
y[1] = ppVALHeating[1][i-1];
y[2] = ppVALHeating[1][i];

LinearFit( x, y, flog10_rho_c, &fVALHeating );

return pow( 10.0, fVALHeating );
}
