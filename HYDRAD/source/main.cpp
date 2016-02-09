// ****
// *
// * HYDrodynamics and RADiation code (HYDRAD)
// * An astrophysical fluid dynamics code for 
// * solar and stellar atmospheres
// *
// * (c) Dr. Stephen J. Bradshaw
// *
// * Date last modified: 01/02/2007
// *
// ****


#include "mesh.h"
#include "boost/program_options.hpp"


int main( int argc, char **argv )
{
	char configFilename[256],rad_configFilename[256];
	PMESH pMesh;

	//Read command line options 
	namespace po = boost::program_options;
	po::options_description description("The HYDrodynamics and RADiation code for computing field-aligned coronal loop solutions\n\n(c) Dr. Stephen J. Bradshaw\n\nUsage");
	description.add_options()
		("help,h","The help message")
		("config,c",po::value<std::string>()->required(),"HYDRAD configuration file.")
		("rad_config,r",po::value<std::string>()->required(),"Radiation model configuration file.");
	po::variables_map vm;
	po::store(po::command_line_parser(argc,argv).options(description).run(),vm);
	//Check if the help option is selected
	if(vm.count("help"))
	{
		std::cout << description;
		return 0;
	}
	po::notify(vm);
	
	//Copy command line options to variables (as needed)
	std::strcpy(configFilename,vm["config"].as<std::string>().c_str());
	std::strcpy(rad_configFilename,vm["rad_config"].as<std::string>().c_str());
	
	// Set up the problem, create the mesh and solve the equations
	pMesh = new CAdaptiveMesh(configFilename, rad_configFilename);
	
	// Delete the mesh
	delete pMesh;
	
	return 0;
}
