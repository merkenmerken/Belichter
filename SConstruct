# Set environment for AVR-GCC.

# import sys

AddOption(
'--programm',
dest='prog',
nargs=1,
default=0,
type='int',
action='store',
metavar='flag',
help='programm after build',
)

#Tool path
Tool_AVR_GCC = ['C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\bin' , 'tools/avrdude-6.3-mingw32',
                'C:\\Python\\Python39\\Lib\\site-packages',
                'tools/lint']

# Variables
vars = Variables('variables.py')
vars.Add('TARGETNAME', 'Define target name', 'main')
vars.Add('MCU', 'Microcontroller', 'atmega8')
vars.Add('F_CPU', 'CPU frequency in Hz', 8000000)
vars.Add('OPT', 'Optimization Level Possible value: 0 . . . s, g', 's')
vars.Add('Programmer', 'Programmer Name', 'stk500')
vars.Add('Comport', 'Com Port = COMx', 'COM5')



# Create Devault Environment for AVR_GCC
env = Environment(  tools = ['AVR'] ,
                    toolpath=['tools'],
                    variables = vars,
                    ENV = {'PATH' : Tool_AVR_GCC},
                    PROG = GetOption('prog')
                 )

env['BUILDDIR'] = '#build'


ccompilerFlags = [  '-mmcu=${MCU}',
                    '-O${OPT}',
                    '-Wall',
                    # '-Werror',
                    '-std=gnu99',
                    '-ffunction-sections',
                    '-fdata-sections',
                    '-fpack-struct',
                    '-fshort-enums',
                    '-g2',
                    '-x','c',
                    '-funsigned-char', 
                    '-funsigned-bitfields',
                    '-c'
                    # ,
                    # '-B', 'C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\Packs\\atmel\\ATmega_DFP\\1.6.364\\gcc\\dev\\atmega8'
                    ]

clinkerFlags = [    '-mmcu=${MCU}',
                    '-Wl,-Map="${TARGETNAME}.map"', 
                    '-Wl,--start-group' ,
                    '-Wl,-lm' ,
                    '-Wl,--end-group' ,
                    '-Wl,--gc-sections' 
                    # ,
                    # '-B', 'C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\Packs\\atmel\\ATmega_DFP\\1.6.364\\gcc\\dev\\atmega8'
                    ]

assemblerFlags = [  '-mmcu=${MCU}',
                    '-x','assembler-with-cpp',
                    '-c', 
                    # ,
                    # '-B', 'C:\\Program Files (x86)\\Atmel\\Studio\\7.0\\Packs\\atmel\\ATmega_DFP\\1.6.364\\gcc\\dev\\atmega8',
                    ]

customDefines = [   'F_CPU=${F_CPU}UL'
                ]


# Set environment for an Atmel AVR Atmega 328p microcontroller.
# Create and initialize the environment.
env.Append(CCFLAGS = ccompilerFlags)
env.Append(LINKFLAGS = clinkerFlags)
env.Append(ASFLAGS = assemblerFlags)
env.Append(CPPDEFINES = customDefines)

BuildDir = '#' + '${BuildDir}'


env['OBJECTS_BUILT'] = []
env['OBJECTS_LINT_BUILT'] = []


SConscript('src/SConscript',
        variant_dir = env['BUILDDIR'],
        duplicate = 0,
        exports = ['env'])

Help(vars.GenerateHelpText(env))




