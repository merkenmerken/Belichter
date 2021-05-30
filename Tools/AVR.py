import os
import re
import subprocess

import SCons.Util

compiler = 'avr-gcc'
objcopy  = 'avr-objcopy'

def generate(env):
    """Add Builders and construction variables for gcc to an Environment."""

    gnu_tools = ['gcc','g++','asm','gnulink','ar',]
	# for tool in gnu_tools:
	# 	env.Tool(tool)

    for tool in gnu_tools:
        env.Tool(tool)

    ###########################################
    #Assembler
    ###########################################

    env['AS'] = 'avr-gcc'
    env['ASCOM']= '$AS $ASFLAGS $_CPPINCFLAGS -o $TARGET $SOURCES'
    env['ASPPCOM'] ='$CC $ASPPFLAGS $CPPFLAGS $_CPPDEFFLAGS $_CPPINCFLAGS -c -o $TARGET $SOURCES',
    
    env['ASFLAGS'] = [  '-mmcu=${MCU}',
                        '-x',
                        'assembler-with-cpp',
                        '-c'
                     ]
    env['ASPPFLAGS']= '$ASFLAGS'

    ###########################################
    #C,C++
    ###########################################


    env['CC'] = 'avr-gcc'
    env['CXX'] = 'avr-g++'
    env['CPPPATH'] = []
    # env['CPPPATH'] = ["C:\\Program Files (x86)\\Atmel\Studio\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\avr\\include"]
    env['OBJCOPY'] = 'avr-objcopy'
    env['SIZE'] = 'avr-size'

    env.Append(CPPPATH = ['#avr/include','#.'])
    

    env['OBJSUFFIX']= '.o'


    ###########################################
    #Programmer
    ###########################################

    env['AVRDUDE'] = 'avrdude'
    env['DUDEFLAGS'] = '-c ' + '${Programmer}' + ' -p ${MCU}' + ' -P ${Comport}' + ' -u'
    env.AddMethod(flash, "Flash")


    env.Append(BUILDERS = {
        'Size': _get_size_builder(),
        'Hex': _get_hex_builder(),
    })

def exists(env):
    return env.Detect(compiler) and env.Detect(objcopy) 
    
def flash(env,source):
    env.Command('flash',source,'avrdude $DUDEFLAGS -qq -U flash:w:$SOURCE:i')

def _get_hex_builder():
    return SCons.Builder.Builder(action = "$OBJCOPY -O ihex -R .eeprom $SOURCES $TARGET") 

def _get_size_builder():
    return SCons.Builder.Builder(action = "$SIZE -C --mcu=${MCU} $SOURCE") 