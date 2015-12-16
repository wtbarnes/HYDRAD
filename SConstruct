#HYDRAD Build Configuration
#Will Barnes
#15 December 2015

#Import needed modules
import sys
import os

#Command line argument
AddOption('--exec',dest='exec',type='string',nargs=1,action='store',default='initial_conditions',help='Target to be compiled; use either "initial_conditions" or "hydrad"')

#Define subdirectories needed for common build
subdirs = ['Radiation_Model/source','Resources/source']

#Add subdirectories depending on which executable will be compiled
if GetOption('exec') == 'initial_conditions':
    subdirs = subdirs + ['Initial_Conditions/source']
elif GetOption('exec') == 'hydrad':
    subdirs = subdirs + ['Kinetic_Model/source','Heating_Model/source','HYDRAD/source']
else:
    print("Unrecognized target option. Use 'initial_conditions' or 'hydrad'")
    sys.exit(1)

#Build C++ environment
env = Environment(CXX='g++',CXXFLAGS=['-march=native','-mfpmath=sse','-ffast-math','-O3','-Wall'])

#Check OS and change include path
if sys.platform == 'darwin':
    env.Append(CPPPATH=['/usr/include/malloc'])
elif sys.platform == 'linux':
    env.Append(CPPPATH=['/usr/include'])
else:
    print("Unrecognized platform. Set CPPPATH manually.")
    #TODO: add Windows option here; where is malloc.h in Cygwin?
    
#Iterate over subdirectories
allobjs = []
for sd in subdirs:
    consfile = os.path.join(sd,'SConscript')
    allobjs = allobjs + env.SConscript(consfile,exports=['env'])
    
env.Program(GetOption('exec')+'.run',allobjs)