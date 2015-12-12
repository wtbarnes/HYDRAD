# HYDRAD
**HYD**rodynamics and **RAD**iation code for computing field-aligned solutions to hydrodynamic solutions of coronal loop plasma. See Bradshaw and Cargill (2013)

## Directory Tree
```
.
├── Forward_Model
│   ├── build_scripts
│   ├── config
│   ├── instruments
│   │   ├── HiC
│   │   ├── Hinode_EIS
│   │   │   └── EM\ Loci
│   │   ├── IRIS
│   │   ├── SDO_AIA
│   │   └── TRACE
│   ├── ion_emiss_tables
│   └── source
├── HYDRAD
│   ├── build_scripts
│   ├── config
│   └── source
├── HYDRAD_GUI
│   └── config
├── Heating_Model
│   ├── config
│   └── source
├── Initial_Conditions
│   ├── build_scripts
│   ├── config
│   └── source
├── Kinetic_Model
│   ├── config
│   └── source
├── Radiation_Model
│   ├── atomic_data
│   │   ├── OpticallyThick
│   │   │   ├── VAL_atmospheres
│   │   │   │   └── VAL_C
│   │   │   ├── balances
│   │   │   ├── emissivities
│   │   │   ├── escape_probabilities
│   │   │   └── thermal_conductivities
│   │   ├── abundances
│   │   ├── balances
│   │   │   ├── adas
│   │   │   ├── arnaud_et_al
│   │   │   ├── chianti_v7
│   │   │   ├── dere
│   │   │   ├── mazzotta_et_al
│   │   │   └── raymond
│   │   ├── emissivities
│   │   │   ├── chianti_v4
│   │   │   ├── chianti_v5
│   │   │   ├── chianti_v6
│   │   │   └── chianti_v7
│   │   ├── masses
│   │   ├── ranges
│   │   └── rates
│   │       ├── adas
│   │       ├── arnaud_et_al
│   │       ├── chianti_v7
│   │       ├── dere
│   │       ├── mazzotta_et_al
│   │       └── raymond
│   ├── config
│   └── source
│       └── OpticallyThick
├── Resources
│   ├── Utils
│   │   ├── calculateEM
│   │   │   ├── build_scripts
│   │   │   └── source
│   │   ├── extractSpatialAverages
│   │   │   ├── build_scripts
│   │   │   └── source
│   │   └── writeIEfile
│   │       ├── build_scripts
│   │       └── source
│   └── source
└── Visualisation
    ├── 1D_Plot
    ├── 2D_Plot
    └── 3D_Plot
```

##Build Procedure

1. GUI generates Initial Conditions startup files
  + Configuration files (read in directly)
    * `Initial_Conditions/config/initial_conditions.cfg`
    * `Radiation_Model/config/elements_{eq,neq}.cfg`
  + Header files (define boolean variables using `#if,#else,#endif`)
    * `Initial_Conditions/source/config.h`
    * `Radiation_Model/source/config.h`
2. GUI generates Initial Conditions build scripts
  + `Initial_Conditions.bat`
3. GuI runs `Initial_Conditions.bat`
  + Compile Initial Conditions code via `Initial_Conditions/build_scripts/build_initial_conditions.bat` into `Initial_Conditions.exe`
  + Run `Initial_Conditions.exe`
4. GUI generates HYDRAD startup files
  + Configuration files (read in directly)
    * `HYDRAD/config/hydrad.cfg`
	* `Heating_Model/config/heating_model.cfg`
  + Header files (define boolean variables using `#if,#else,#endif`)
5. GUI generates HYDRAD build scripts
  + `HYDRAD.bat`
6. GUI runs `HYDRAD.bat`
  + Compile HYDRAD via `HYDRAD/build_scripts/build_HYDRAD.bat` into `HYDRAD.exe`
  + Run `HYDRAD.exe`

##Ideas

##TODO:

 - Rewrite make/build system for portability and to make it less of a nightmare; possibly use Python to do some of the trickier configuration?
 - Remove hardcoding of input/output paths
 - Make all .cfg files into XML configuration files
 - Determine structure of .cfg files