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

#include <iostream>
#include "mesh.h"
#include "boost/program_options.hpp"


int main( int argc, char **argv )
{	
	char configFilename[256],rad_config_eqFilename[256],rad_config_neqFilename[256];
	PMESH pMesh;

	//Read command line options 
	namespace po = boost::program_options;
	po::options_description description("The HYDrodynamics and RADiation code for computing field-aligned coronal loop solutions\n\n(c) Dr. Stephen J. Bradshaw\n\nUsage");
	description.add_options()
		("help,h","The help message")
		("config,c",po::value<std::string>()->required(),"HYDRAD configuration file.")
		("rad_config_eq,e",po::value<std::string>()->required(),"Equilibrium radiation model configuration file.")
		("rad_config_neq,n",po::value<std::string>()->required(),"Non-equilibrium radiation model configuration file.");
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
	std::strcpy(rad_config_eqFilename,vm["rad_config_eq"].as<std::string>().c_str());
	std::strcpy(rad_config_neqFilename,vm["rad_config_neq"].as<std::string>().c_str());
	
	// Set up the problem, create the mesh and solve the equations
	pMesh = new CAdaptiveMesh(configFilename, rad_config_eqFilename, rad_config_neqFilename);
	
	// Delete the mesh
	delete pMesh;
	
	return 0;
}
