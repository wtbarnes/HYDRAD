# HYDRAD
*HYD*rodynamics and *RAD*iation code for computing field-aligned solutions to hydrodynamic solutions of coronal loop plasma. See Bradshaw and Cargill (2013)

##TODO:

 - Rewrite make/build system for portability and to make it less of a nightmare; possibly use Python to do some of the trickier configuration?
 - Remove hardcoding of input/output paths
 - Make all .cfg files into XML configuration files
 - Determine structure of .cfg files
 
## Workflow
Here, keep a record of the HYDRAD workflow as I understand it.

### Initial Conditions

- Configure initial conditions at GUI level; write initial parameters to .cfg files and rewrite needed header files
- These files go to `InitialConditions/config` and various header files (new header file for each new set of initial conditions means need to compile again for each new set of inputs!)
- Run initial conditions code to generate equilibrium loop solutions

### HYDRAD (dynamics)

- Heating, radiation, mesh options all set by GUI
- Path to initial profile is hardcoded
- Run dynamics code with custom .h files, given .cfg files
- Results output to `Results/` (this path is hardcoded)

##Ideas