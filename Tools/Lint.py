import sys

def generate(env):

    env["PYTHON"] = sys.executable
    env["LINT"] = "cpplint.py"
    env["LINT_OPTIONS"] = ["--filter=-whitespace,+whitespace/tab,-legal/copyright,-build/include_subdir,-readability/multiline_comment", "--verbose=3"]
    env["LINTCOM"] = ["$LINT $LINT_OPTIONS $SOURCE"]


    # env["LINT"] = "lint-nt.exe"
    # env["LINT_OPTIONS"] = "-b -e9059 -D__ATmega8__ -D__AVR_ATmega8__ -DF_CPU=8000000UL --iTools/lint/lnt --iTools/lint/conf co-gcc.lnt au-misra3.lnt"
    # env["LINTCOM"] = ["$LINT $LINT_OPTIONS $_CPPINCFLAGS $SOURCE"]



    # -b -os(LINT.OUT) -i%LINT_CFG_DIR% std env-si %PRJ_LNT% %PRJ_INCLUDES% %PRJ_FILES%
# E:\FreeRtosTest\Tools\lint\lnt

# E:\FreeRtosTest\Tools\lint\lnt\co-gcc.lnt
# E:\FreeRtosTest\Tools\lint\lnt\au-misra3.lnt

def exists(env):
    return 1 

    