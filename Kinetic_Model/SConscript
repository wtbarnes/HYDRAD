#HYDRAD Build SConscript
#Will Barnes
#15 December 2015

#Import needed modules
import glob

#Import environment from SConstruct
Import('env')

sources = glob.glob('source/*.cpp')

objs = env.Object(sources)

Return('objs')