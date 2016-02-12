// ****
// *
// * Include file for miscellaneous routines used by the hydrostatic code
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 29/12/2012
// *
// ****

void GetConfigurationParametersXML( PARAMETERS *pParams, char *configFilename );

void GenerateSemiCircularLoop( PARAMETERS Params );

void WriteAMRFile( int iTotalSteps, double *s, double *T, double *nH, double *ne, PARAMETERS Params );
void WritePHYFile( int iTotalSteps, double *s, double *T, double *nH, double *ne, PARAMETERS Params );
void WriteSOLFile( double finalH0, PARAMETERS Params );
