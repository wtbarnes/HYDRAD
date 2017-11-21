g++ -O3 -msse4.2 -ffast-math -Wall ../source/main.cpp ../source/ode.cpp ../source/misc.cpp ../../Radiation_Model/source/element.cpp ../../Radiation_Model/source/radiation.cpp ../../Radiation_Model/source/OpticallyThick/OpticallyThickIon.cpp ../../Radiation_Model/source/OpticallyThick/RadiativeRates.cpp ../../Resources/source/gammabeta.cpp ../../Resources/source/fitpoly.cpp ../../Resources/Utils/regPoly/regpoly.cpp ../../Resources/Utils/regPoly/nrutil.cpp ../../Resources/source/file.cpp -o ../../Initial_Conditions.exe