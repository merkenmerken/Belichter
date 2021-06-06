import sys
import SCons.Defaults
import SCons.Builder
import os

OriginalShared = SCons.Defaults.SharedObjectEmitter
OriginalStatic = SCons.Defaults.StaticObjectEmitter


def DoLint(env, source, target):
    for i in range(len(source)):
        s = source[i]
        src = s.srcnode().path

        test = env["WHITELIST"]
        test = [os.path.basename(x) for x in test]

        if os.path.basename(src) not in test:
            out = env.Lint(env["BUILDDIR"] + os.path.basename(src) + ".lint", s)
            env.Depends(target[i], out)

def SharedObjectEmitter(target, source, env):
    DoLint(env, source, target)
    return OriginalShared(target, source, env)

def StaticObjectEmitter(target, source, env):
    DoLint(env, source, target)
    return OriginalStatic(target, source, env)

def generate(env):
    SCons.Defaults.SharedObjectEmitter = SharedObjectEmitter
    SCons.Defaults.StaticObjectEmitter = StaticObjectEmitter
    linter = SCons.Builder.Builder(
        action='$LINT $LINT_OPTIONS $SOURCE' , 'date > $TARGET',
        # action='$LINT $LINT_OPTIONS $SOURCE',
        suffix='.lint',
        src_suffix='.c')
    env.Append(BUILDERS={'Lint': linter})

    env["PYTHON"] = sys.executable
    env["LINT"] = "cpplint.py"
    env["LINT_OPTIONS"] = ["--filter=-whitespace,+whitespace/tab,-legal/copyright,-build/include_subdir,-readability/multiline_comment", "--verbose=3"]

    env["WHITELIST"] = []

    

def exists(env):
    return 1