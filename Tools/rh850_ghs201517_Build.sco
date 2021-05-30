###############################################################################
# General Paths
out_path = 'out'
Export('out_path')
Import('tgtOptions')

###############################################################################
# Tools Based
cc_tools_path = '..\\tools\\ghs\\rh850_ghs201517'

# Environment for the target.
tgtEnv = Environment()
tgtEnv['ENV']['LIBPATH'] = []
tgtEnv['ENV']['LIB'] = []
tgtEnv['ENV']['INCLUDE'] = []
tgtEnv['ENV']['OUT_INSTR'] = [ r'out' ]

tgtEnv['ENV']['PATH'] = [ r'..\tools\ghs\rh850_ghs201517\bin' ]

###############################################################################
# Compilable elements.
import sys
sys.path.append('../../python')
from Compilables import Compilable, Compile_STD, Assemble_STD, AssemblePreComp_STD, Library_STD

Export('Compilable', 'Compile_STD', 'Assemble_STD', 'AssemblePreComp_STD', 'Library_STD')

###############################################################################
# Lint.
lint_tools_path = '..\\tools\\lint'
tgtEnv.Replace(LINT_ERROR   = '')
tgtEnv.Replace(LINT_WARNING = '-')
tgtEnv.Replace(LINT_DISABLE = '-@rem ')
tgtEnv.Replace(PRELINT = '')
tgtEnv.Replace(LINT = lint_tools_path + '\\lint.cmd')
tgtEnv.Replace(LINTOPTIONS_C   = '+v -u +e900 -i' + lint_tools_path + ' std/au-misra.lnt     generic.lnt std/rh850_ghs201517.lnt')
tgtEnv.Replace(LINTOPTIONS_CPP = '+v -u +e900 -i' + lint_tools_path + ' std/au-misra-cpp.lnt generic.lnt std/rh850_ghs201517.lnt')

###############################################################################
# Compiler.
tgtEnv.Replace(CCCOM = [
'$PRELINT$LINT $LINTOPTIONS_C   $CDEFINES  out\\includes.lnt $SOURCES',
'$CC @out\\c_opt.inc $CUSTOM_FLAGS $LOCAL_CFLAGS $CDEFINES @out\\includes.lnt $SOURCES -o $TARGET',
])
# Compiler. C++
tgtEnv.Replace(CXXCOM = [
'$PRELINT$LINT $LINTOPTIONS_CPP $CDEFINES  out\\includes.lnt $SOURCES',
'$CCPP @out\\c_opt.inc --no_exceptions $CUSTOM_FLAGS $LOCAL_CFLAGS $CDEFINES @out\\includes.lnt $SOURCES -o $TARGET',
])

tgtEnv.Replace(CCCOM_COVERAGE = [
'$PRELINT$LINT $LINTOPTIONS_C        $CDEFINES  out\\includes.lnt $SOURCES',
'$CCCOV --cs-compiler=ghs_ccv850e @out\\c_opt.inc $CUSTOM_FLAGS $CDEFINES @out\\includes.lnt $SOURCES -o $TARGET',
])
tgtEnv.Replace(CC = cc_tools_path + '\\bin\\cxrh850.exe')
tgtEnv.Replace(CCPP = cc_tools_path + '\\bin\\cxrh850.exe')
tgtEnv.Replace(CCCOV = '..\\tools\\coveragescanner\\coveragescanner.exe')
tgtEnv.Replace(OBJSUFFIX = '.o')

# XXX here we have the possibility to pass that QAC should not be done TODO
if 'TGT_SQA' in tgtOptions:
    if 'TGT_QAC' in tgtOptions:
        # do not set the skip QAC option
        tgtEnv.Replace(SKIP_QAC = '')
    else:         
        # set the skip QAC option
        tgtEnv.Replace(SKIP_QAC = '-s')
    tgtEnv.Append(CCCOM = [
    # Executes SQA commands
    '..\\tools\\qac\\executesQAC.cmd -n "${SOURCES}" -e "@out\\includes.lnt,$CUSTOM_FLAGS,$CDEFINES,@out\\defines.lnt,$CFLAGS" $SKIP_QAC -c "$LINT $LINTOPTIONS_C  $CDEFINES out\\includes.lnt $SOURCES" -o "${SOURCES.file}.lnt_report"',
    ])
    tgtEnv.Append(CXXCOM = [
    # Executes SQA commands
    '..\\tools\\qac\\executesQAC.cmd -n "${SOURCES}" -e "@out\\includes.lnt,$CUSTOM_FLAGS,$CDEFINES,@out\\defines.lnt,$CFLAGS" $SKIP_QAC -c "$LINT $LINTOPTIONS_CPP $CDEFINES out\\includes.lnt $SOURCES" -o "${SOURCES.file}.lnt_report"',
    ])

# Add custom include paths
tgtEnv.Append(CPPPATH = [
'../tools/ghs/rh850_ghs201517/bin/ansi',
#'../tools/ghs/rh850_ghs201517/bin/src/Renesas/include',
])

# Add custom define flags
tgtEnv.Replace(CDEFINES = [
'-DTGT_RH850_GHS201517',
])

# C flags
compilerCustomModes = {
#   'name':             ['Aligned comment      ', 'compiler switch'],
    'speed':            ['Speed optimization   ', '-Ospeed'],
    'speed_noPeep':     ['Speed optimization   ', '-Ospeed -Onopeephole'],
    'space':            ['Space optimization   ', '-Ospace'],
    'space_noPeep':     ['Space optimization   ', '-Ospace -Onopeephole'],
    'debug':            ['Debug optimization   ', '-Omaxdebug'],
    'default':          ['Default optimization ', ''],
    'coverage':         ['Debug + Coverage hit ', '-Omaxdebug --cs-on --cs-full-instrumentation --cs-keep-instrumentation-files --cs-bit-fields'],
    'coverage-count':   ['Debug +Coverage count', '-Omaxdebug --cs-on --cs-full-instrumentation --cs-keep-instrumentation-files'],
    'space_enum':       ['Space optimiz. & enum', '-Ospace --short_enum'],
#   'tbd-N':            ['Comment N to define  ', ''],
}
Export('compilerCustomModes')

tgtEnv.Replace(CFLAGS = [
'-c',                                    # Produces an object file (called input-file.o) for each source file
'-c99',                                  # Specifies ISO C99. This mode provides all features of the C99 language in addition to some extensions
'-cpu=rh850g3kh',                        # Specify a target processor with the driver
'-delete',                               # Controls the removal from the executable of functions that are unused and unreferenced
'--diag_error', 193,                     # Sets the specified compiler diagnostic messages to the level of error
'-dual_debug',                           # Enables the generation of DWARF debugging information in the object file
'-g',                                    # Displays global symbols
'-gsize',                                # Controls use of the gsize utility to determine the size of the output executable
'-ignore_callt_state_in_interrupts',     # Controls whether the CTPSW and CTPC registers are saved in interrupt routines generated by the compiler
'-inline_prologue',                      # Controls the manner in which the compiler generates each function prologue and epilogue
'-large_sda',                            # Generate 23-bit SDA relocations for load/store instructions
'-no_callt',                             # Controls the use of the V850E callt instruction function prologues and epilogues
'--no_commons',                          # Allocates uninitialized global variables to a section and initializes them to zero at program startup
'-nofloatio',                            # Controls the use of floating-point in stdio operations
'-Osize',                                # Enables optimizations that improve both size and performance, and additional optimizations that improve code size at the expense of performance.
'-prepare_dispose',                      # Returns address register (lp) and frame pointer register (fp) are saved in the permanent register area
'--prototype_errors',                  # Controls the treatment of functions that are referenced or called when no prototype has been provided
'-reserve_r2',                           # Controls the treatment of register r2
'-sda=all',                              # Enables the Small Data Area optimization with threshold size
'--short_enum',                          # Controls the allocation of enumerations
'-shorten_loads',                        # Converts 6-byte load and store instructions to 4-byte instructions when possible
'-shorten_moves',                        # Convert 32 and 48-bit move relocations to 16-bit in move instructions when possible
'-Wshadow',                              # Controls a warning that is issued if the declaration of a local variable shadows the declaration of a variable of the same name declared at the global scope
'-Wundef',                               # Controls a warning that is issued for undefined symbols in preprocessor expressions
'-Onoloop'
])
tgtEnv.Replace(CCFLAGS = '')
# Include paths and sources & outputs
tgtEnv.Replace(INCPREFIX = '-I')

###############################################################################
# Assembler
tgtEnv.Replace(ASCOM     = '$AS                            $ASFLAGS                              -filetype.assembly $SOURCES -o $TARGET')
tgtEnv.Replace(PRE_ASCOM = '$AS -preprocess_assembly_files $ASFLAGS $CDEFINES @out\\includes.lnt -filetype.assembly $SOURCES -o $TARGET')
tgtEnv.Replace(AS = cc_tools_path + '\\bin\\cxrh850.exe')
# Asm flags
tgtEnv.Replace(ASFLAGS = [
'-c',
'-c99',                                  # Ansi-c 99 compatible. Require declarations to compile
'-cpu=rh850g3kh',
'-allocate_ep',                          # Controls an optimization that attempts to allocate pointer variables to the EP register in order to use short load and store instructions
'--no_commons',                          # Allocates uninitialized global variables to a section and initializes them to zero at program startup
'--no_implicit_include',                 # Controls implicit inclusion of source files as a method of finding definitions of template entities to be instantiated
'--prototype_warnings',                  # Controls the treatment of functions that are referenced or called when no prototype has been provided
'-G',                                    # Generates source-level debugging information
#'-list_dir=.\\out\\lst',                # Outputs assembly listing files in the specified directory
#'-list',                                # Creates a listing
#'-passsource',                          # Add source to the list
'--diag_suppress', 618,                  # Disable the message 'struct  or  union  declares  no  named  members'
'-dwarf2',                               # ELF File Options. Produces DWARF information only.
'--no_wrap_diagnostics',                 # No wrap the message line even it is too long
])

###############################################################################
# Linker
Import('tgtName')
tgtEnv.Replace(PROGSUFFIX = '.elf')
tgtEnv.Replace(LINKCOM = [
'$LINK $LINKFLAGS -o $TARGET $LIB_LIST @out\\objToLink.inl',
])
tgtEnv.Replace(LINKCOM_COVERAGE = tgtEnv['LINKCOM'] + [
'$LINK_COVERAGE --cs-compiler=null_linker --cs-on --cs-instr-file=out/coverage.isym --cs-no-cslib -o $TARGET @out\\objToLink.inl',
])
tgtEnv.Replace(LINK = cc_tools_path + '\\bin\\cxrh850.exe')
tgtEnv.Replace(LINK_COVERAGE = '..\\tools\\coveragescanner\\coveragescanner.exe')
tgtEnv.Replace(LIB_LIST = [])
tgtEnv.Replace(LINKFLAGS = [
'-entry=_RESET',
'-map',                                             # Creates a map file with the name of the object file plus a .map extension.
'-keepmap',                                         # Controls the retention of the map file in the event of a link error
#'-gsize',                                          # Output File Size Analysis
'-callgraph',                                       # Creates a call graph
'-delete',                                          # Deletion of Unused Functions
'-locatedprogram',                                  # Generates an executable program
'-srec',                                            # Generates S-Record File
'-dwarf2',                                          # ELF File Options. Produces DWARF information only.
'-ignore_debug_references',                         # Else the debuger lost information
#'-codefactor',                                     # Controls the code factoring optimization, which reduces code size by merging redundant sequences of object code at link-time.
'-Olink',                                           # The linker optimizations that are enabled depends upon whether you are optimizing for speed or size.
'-c99',                                             # Ansi-c 99 compatible (Require declarations to compile)
'-Mx',                                              # Map File Cross-Referencing
'-G',                                               # Generates source-level debugging information
'-cpu=rh850g3kh',
'-locatedprogram',                                  # Generates an executable program
'-lnk=-no_append',                                  # Promotes warnings concerning sections that do not appear in the section map to errors.
'-L' + cc_tools_path + '\\bin\\lib\\rh850',
'--no_wrap_diagnostics',
'--no_exceptions',                                  # Exception handling disabled
'--preprocess_linker_directive',
'-nofloatio',
])

if 'AUTOSAR_OS_USED' in tgtOptions:
        tgtEnv.Append(LINKFLAGS = [
            #'-nostartfile',                             # No compiler start up code
            'bsw/mcal/mcalm/locate_libc_flash_AOS.ld',
        ])
elif 'LEAR_OS_USED' in tgtOptions:
        tgtEnv.Append(LINKFLAGS = [
            'bsw/mcal/mcalm/dr7f701581.ld',
        ])
else:
    print 'A valid OS mode must be defined for os_sconstruct.sco'
    exit(1)

###############################################################################
# Library archiver
tgtEnv.Replace(RANLIB = '')
tgtEnv.Replace(RANLIBCOM = '')
tgtEnv.Replace(RANLIBFLAGS = '')
tgtEnv.Replace(LIBPREFIX = '')
tgtEnv.Replace(LIBSUFFIX = '.a')
tgtEnv.Replace(ARCOM     = ['$AR $SOURCES $ARFLAGS -o $TARGET'])
tgtEnv.Replace(AR = cc_tools_path + '\\bin\\ccppc.exe')
tgtEnv.Replace(ARFLAGS = [
'-archive',
])

###############################################################################
# Lint & singlefile compile chaintool parse
tgtEnv['CCCOM']  = ['-@echo '+sComLine+' >>comp_tmp.log' for sComLine in tgtEnv['CCCOM'] if sComLine.startswith('$CC ') ] + tgtEnv['CCCOM']
tgtEnv['CCCOM']  = ['-@echo '+sComLine[8:]+' >>lint_tmp.log' for sComLine in tgtEnv['CCCOM'] if sComLine.startswith('$PRELINT$LINT ') ] + tgtEnv['CCCOM']
tgtEnv['CXXCOM'] = ['-@echo '+sComLine+' >>comp_tmp.log' for sComLine in tgtEnv['CXXCOM'] if sComLine.startswith('$CCPP ') ] + tgtEnv['CXXCOM']
tgtEnv['CXXCOM'] = ['-@echo '+sComLine[8:]+' >>lint_tmp.log' for sComLine in tgtEnv['CXXCOM'] if sComLine.startswith('$PRELINT$LINT ') ] + tgtEnv['CXXCOM']

if 'TGT_ONLY_LINT' in tgtOptions:
    tgtEnv['LINT_ERROR'] = tgtEnv['LINT_WARNING']
    tgtEnv['CCCOM']  = [sComLine for sComLine in tgtEnv['CCCOM']  if sComLine.startswith('$PRELINT')]
    tgtEnv['CXXCOM'] = [sComLine for sComLine in tgtEnv['CXXCOM'] if sComLine.startswith('$PRELINT')]
    tgtEnv['LINK'] = '@rem' + tgtEnv['LINK']
    tgtEnv['AS']   = '@rem' + tgtEnv['AS']
    tgtEnv['AR']   = '@rem' + tgtEnv['AR']

Export('tgtEnv')
