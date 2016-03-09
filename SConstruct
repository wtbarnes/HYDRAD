#HYDRAD Build Configuration
#Will Barnes
#15 December 2015

#Import needed modules
import sys
import os

#Command line argument
AddOption('--exec',dest='exec',type='string',nargs=1,action='store',default='initial_conditions',help='Target to be compiled; use either "initial_conditions" or "hydrad"')

#Define subdirectories needed for common build
subdirs = ['Radiation_Model','rsp_toolkit']

#Add subdirectories depending on which executable will be compiled
if GetOption('exec') == 'initial_conditions':
    subdirs = subdirs + ['Initial_Conditions']
elif GetOption('exec') == 'hydrad':
    subdirs = subdirs + ['Kinetic_Model','Heating_Model','HYDRAD']
else:
    print("Unrecognized target option. Use 'initial_conditions' or 'hydrad'")
    sys.exit(1)

#Build C++ environment
env = Environment(CXX='g++',CXXFLAGS=['-march=native','-mfpmath=sse','-ffast-math','-O3','-Wall'])

#Check OS and change include path
if 'darwin' in sys.platform:
    env.Append(CPPPATH=['/opt/local/include','/usr/include/malloc'])
    env.Append(LIBS=['boost_program_options-mt'])
    env.Append(LIBPATH=['/opt/local/lib'])
elif 'linux' in sys.platform:
    env.Append(CPPPATH=['/usr/include'])
    env.Append(LIBS=['boost_program_options'])
    env.Append(LIBPATH=['/usr/lib'])
else:
    print("Unrecognized platform. Set CPPPATH manually.")
    sys.exit(1)
    #TODO: add Windows option here; where is malloc.h in Cygwin?
    
#Iterate over subdirectories
allobjs = []
for sd in subdirs:
    consfile = os.path.join(sd,'SConscript')
    allobjs = allobjs + env.SConscript(consfile,exports=['env'])
    
env.Program(GetOption('exec')+'.run',allobjs)