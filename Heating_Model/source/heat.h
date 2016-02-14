// ****
// *
// * A heating code to simulate different forms of heat deposition
// *
// * Class function definitions
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 19/12/2012
// *
// ****

#include "tinyxml.h"

class CHeat {

    private:

    // The length of the loop
    double fLoopLength;

    // The duration of the time-dependent heating
    double fDuration;

    // Quiescent heating parameters

    // Location, scale-length and maximum energy
    double s0quiescent, sHquiescent, E0quiescent;
	
    // Episodic heating parameters

    // The number of episodic heating events to be activated
    int NumActivatedEvents;

    // Location, scale-length and maximum energy
    double *s0episodic, *sHepisodic, *E0episodic;

    // Start and end times of rise phase
    double *tsRepisodic, *teRepisodic;
    // Start and end times of decay phase
    double *tsDepisodic, *teDepisodic;

    // The background volumetric heating required to maintain the VAL atmosphere in equilibrium
    int iVALHeatingDP;
    double **ppVALHeating;

    void Initialise( TiXmlElement *heating_node, double fL );
    void FreeAll( void );

    void GetHeatingData ( char *szFilename );
    void GetHeatingDataXml ( TiXmlElement *heating_node );
    void GetVALHeatingData( TiXmlElement *heating_node );

    public:

    CHeat( TiXmlElement *heating_node, double fL );
    ~CHeat( void );

    double CalculateQuiescentHeating( double s );
    double CalculateEpisodicHeating( double s, double t );
    double CalculateHeating( double s, double t );

    double CalculateVALHeating( double flog10_rho_c );

};

typedef CHeat* PHEAT;
