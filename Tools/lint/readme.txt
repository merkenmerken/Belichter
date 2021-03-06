

             --------------------------------------------------
                   --- Manual Additions/Modifications  ---
             --------------------------------------------------
                       PC-lint for C/C++ Version 9.00L

    This readme.txt supplements the PC-lint manual entitled "Reference
    Manual for PC-lint/FlexeLint" found in the installation directory
    under the name "pc-lint.pdf"


                ------ Printing the Reference Manual  ------

    You have permission to print out the Reference Manual (or other
    related documentation) in whole or in part in support of the use of
    this software.

    A softcover version of the Reference Manual can be ordered directly
    from the Book Patch for US$ 35 plus shipping.  The URL is
    www.thebookpatch.com/BookStoreResults.aspx?search=gimpel&ddl=any



       ------ Support for Microsoft through Visual Studio 2010  ------

    Patches 9.00e and later support Visual Studio 2010 and the Microsoft
    Visual C/C++ 10.0 compiler (as well as all earlier versions of the
    Microsoft compiler series).  Support comes mainly from the compiler
    options files (co-...lnt).  Thus options files co-msc70.lnt,
    co-msc71.lnt, co-msc80.lnt, co-msc90.lnt and co-msc100.lnt support
    versions 7.0, 7.1, 8.0, 9.0 and 10.0 respectively.

    The file co-msc100.lnt is preconfigured to match the default macro
    settings of the compiler.  However, owing to compiler options the
    settings of these macros are subject to change.  We have therefore
    provided a way to automatically generate the macro definitions.  See
    co-msc100.lnt and/or macros-msc.c or macros-msc.cpp (renamed from
    vs2010-m.cpp).

    Also, starting with 9.00e, PC-lint supports .sln and .vcxproj files
    as described below under ".sln Support" and ".vcxproj Support"
    respectively.


                   ------ What's New in Version 9  ------

    To find out what we've added to the product since Version 8.00,
    check out Chapter 20 "What's New" in the Reference Manual.

    We traditionally include Version Shock in our "What's New" section.
    This was inadvertently omitted in producing the document.  So here
    it is.


    ------ Ongoing support and patch versions.

    Periodically between versions we have so-called patches.  These are
    intended to fix bugs and provide support for new technologies
    (language versions, compiler features, etc.).  This readme contains
    an abbreviated list of newer features for each patch of the current
    version.  A detailed feature-by-feature list is presented on our web
    site www.gimpel.com.  Click on "Lint 9.00 Patches" and look at
    bugfix90.txt.


    ------ Version Shock (from Version 8 to Version 9)

    wchar_t -- We are treating wchar_t slightly differently in Version
       9.  The difference would not normally be detected.  See flag -fwc
       in Section 5.5 of the manual.

    Strong Type Change -- We now support dimensional analysis using
       strong types.  This resulted in some changes which are not upward
       compatible.  See Section 9.4 "Multiplication and Division of
       Strong Types".

       You can opt out of this change.  See The Dimension by Default
       flag (-fdd) in Section 5.5 and Jm controls the Multiplier group
       flag (-fjm) also in Section 5.5.


                          ------ Front End  ------

    Your linting experience will be considerably enhanced by adapting
    your favorite editor or compiler environment to the task of
    sequencing from error to error.  See Section 3.5 of the Reference
    Manual.


                       ------ Getting Started  ------

    In section 3.2 of our Reference Manual we indicate that you need to
    specify where your compiler header files are located as well as the
    location of any third party libraries you might be using.  This is
    done using one or more -i options.  If you are not aware of where
    your libraries are you can compile (using your compiler, not lint)
    the file called:

          where_is_stdio_h.c

    The purpose and use of the file is documented as commentary within
    the file itself.  It is designed to find the location of your
    compiler's headers and contains instructions on locating other
    library headers as well.


                       ------ Multiple Passes  ------

    By default, PC-lint/FlexeLint will go through all your modules in
    one pass.  For projects not previously linted there will be enough
    messages to look at.  However, with just one pass, you will not be
    taking full advantage of our new static data tracking or the
    interfunction value tracking.  With just one pass, we cannot say
    very much about static variables.  We may see a variable being set
    to a value but we don't know of intervening functions that may be
    modifying the variable.  We will also not know about dangerous
    return values for functions that are defined later than they are
    called, and we will not know about dangerous arguments for functions
    that are defined early.  To introduce a second pass you need only to
    add the command line option:

        -passes(2)

    or, if this syntax presents a problem with your Shell, you may use:

        -passes[2]

    or, in some cases,

        -passes=2

    is needed.  Of course, you can replace the 2 with any number you
    wish.  The larger the number, the more bugs that can be found and
    the more processing time that will be required.

    See Section 10.2 "Value Tracking" in the Reference Manual.


                ------ What's New in the 9.00b Patch  ------

    We have been diligent in responding to users that may have
    experienced difficulties in one of the many new options that Version
    9.00 provides.  These features include Pre-compiled Headers (-pch
    option), Bypass Headers (+/-byph(), etc.) and pre-determined
    predicates.


                ------ What's New in the 9.00c Patch  ------

    We have special author files ('au-' prefix) for porting to 64-bit
    programming.  The names of these files are perhaps self-explanatory:

        au-LLP64.lnt        LLP64 model
        au-LP64.lnt         LP64  model
        au-ILP64.lnt        ILP64 model

    Each of these files references the model-independent file au-64.lnt
    that enables Warnings, Informationals and Elective Notes suitable
    when porting from 32 bits to 64 bits.  The file also contains
    directions for employing strong typing to assist in torture testing
    your code.

    In attempting to track the forthcoming C++ standard we have
    implementations of a number of voted on features.  These are
    available using the option: -A(C++2010) and consist of:

        static_assert()
        Extended friend Declarations
        Adding the long long Type to C++
        C99 Preprocessor Synchronization
        Right Angle Brackets
        'extern template'
        Delegating Constructors
        Using 'auto' to deduce types of variables
        Rvalue References
        New Character Types
        sizeof() for non-static members without 'this->'
        decltype
        Strongly Typed Enums
        A name for the null pointer: nullptr


                ------ What's New in the 9.00d Patch  ------

    In addition to the usual set of miscellaneous bug fixes we have made
    a substantial upgrade to our overload resolution algorithms to
    accommodate some subtle language requirements.

    Some additions have been made to our suite of C++ 2011 features
    (activated through the use of the option: -A(C++2010)) and consist
    of:

        'explicit' conversion functions
        explicitly defaulted special member functions

    An important bug was found and fixed in connection with pre-compiled
    headers and MSVC 8.0 and 9.0


                ------ What's New in the 9.00e Patch  ------

    Visual Studio 2010 is now supported.

    Our MISRA support (MISRA C 1998, MISRA C 2004 and MISRA C++) has
    been substantially enhanced and our coverage of the various rules is
    now virtually complete.  See Author files au-misra1.lnt,
    au-misra2.lnt and au-misra-cpp.lnt.

    Improved emulation of the Microsoft header search algorithm.  See
    "Microsoft's nested #include search" below.

    Improved support for embedded systems using the @ location
    specifier.  See "Enhanced support for address-specifiers" below.

    Improved Boost.Typeof support for Visual Studio users owing to
    better emulation of Microsoft's __if_exists keyword.


                ------ What's New in the 9.00f Patch  ------

    9.00f removes a troubling undeserved 1013 introduced in 9.00e.

    A number of MISRA issues were addressed.

    A template bug was removed thereby helping us greatly with our Boost
    lambda support.


                ------ What's New in the 9.00g Patch  ------

    Patch 9.00g introduces support for lambda-expressions and alias
    declarations.  As with other C++ 2011 features, these are available
    using the option: -A(C++2011).

    The complete list of supported core language proposals is as
    follows.  (Where given, the tags in square brackets indicate the
    names of relevant sections in the Final Draft International Standard
    (FDIS).)

        static_assert declarations  [dcl.dcl]
        Extended friend declarations
        The type 'long long'
        C99 preprocessor synchronization
        Right angle brackets  [temp.names]
        'extern template'     [temp.explicit]
        Delegating constructors [class.base.init]
        The 'auto' type specifier [dcl.spec.auto]
        Rvalue references
        New Character Types
        sizeof() for non-static members without 'this->'
        decltype  [dcl.type.simple]
        Strongly Typed Enums [dcl.enum]
        'nullptr'
        'explicit' conversion functions
        Defaulted functions [dcl.fct.def.default]
        Deleted functions [dcl.fct.def.delete]
        Explicitly defaulted special member functions
        Lambda expressions [expr.prim.lambda]
        Alias declarations [dcl.typedef]

    Other Enhancements include:

    Our .lnt files now contain an embedded date-last-changed
    identification which can be reflected to the output stream (check
    any .lnt file).

    We have continued to enhance our MISRA C and MISRA C++ checking.

    We also now support the simultaneous activation of both MISRA C 1998
    and MISRA C 2004 thru the use of the combination of the +misra(1)
    and +misra(2) options.

    We have improved and extended our processing with respect to
    standard limits.

    We now avoid issuing warnings #417 and #694 prematurely when
    processing macro expansions.

    We now remain silent with respect to elective note #952 for
    parameters declared as arrays.

    We corrected a crash which occurred when an EOF was found inside a
    macro argument list.  Though processing will still stop in such
    cases, we now recover much more gracefully.

    We addressed the occurrence of a segmentation fault when attempting
    to use the program info facility.

    We have harmonized Lint's behavior with respect to ++efreeze and
    message activation options to allow such options to take effect, as
    described in the manual.

    We were inadvertently attempting to define a function after the end
    of a module was found, resulting in a segmentation fault.  We have
    taken steps to prevent this behavior.

    We were issuing a segmentation fault over the processing of
    '__declspec'.  This error has been corrected.

    Plus numerous other minor and not-so-minor corrections.

    Disenhancements:

    Regrettably we are no longer able to upgrade our MSDOS version of
    PC-lint.  It has been frozen at 9.00f.  Note this does not affect
    our Windows command-line version, lint-nt.exe, nor our OS/2 version,
    lint-os2.exe.


                ------ What's New in the 9.00h Patch  ------

    Version 9.00g introduced initial support for C++ 2011
    Lambda-expressions; this initial version of Lambda support
    introduced a regression in our support for attribute syntax in the
    C++/CLI dialect.  As a result some Microsoft users may have seen
    undesired error messages like the following.

        #...                                [SA_Pre(Null=SA_No)]
        #...           _Pre1_impl_(_$notnull) _Deref_pre1_impl_(_$valid)
        #...                      _Pre_valid_ _Post_valid_
        #...                  _Prepost_valid_
        inline HRESULT CComVariant::WriteToStream(_Inout_ IStream* pStream)
        c:\vs9\VC\atlmfc\include\atlcomcli.h(2637): error 26: (Error --
            Expected an expression, found '[')

    This is now resolved by an improved disambiguator.

    *   Template alias support as described in C++ 2011 documentation

    *   Support for the __asm keyword semantics as understood by ARMcc
        and WindRiver.  The new keyword is __ARM_asm and can be used to
        set the semantics of __asm by using the option
        -rw_asgn(__asm,__ARM_asm)

    *   Alignment of an empty class is now assumed to be 1 (rather
        than 0)

    *   It contains our latest efforts at understanding and implementing
        the mysteries of when extern "C" meets with static.

    *   We now perform a more accurate analysis for compliance with
        MISRA C 2004, rule #8.7.

    *   We were tripping over a printf-style format specifier which
        involved a string literal and the binary '+' operator.  We now
        handle this situation more gracefully.

    *   We were accidentally describing two structures with different
        definitions but identical tags as being defined identically.  We
        now recognize the difference.

    *   We now refrain from issuing elective note #953 if the object
        is a variable with class or struct type and lacks a
        User-provided default constructor.

    *   We now allow catch parameters to be inheritance related to the
        type thrown.

    *   We now allow physical tabs to appear in the output by use of \T

    *   We now flag uses of 00 and \00 within the MISRA prohibition of
        the use of octal.  We still allow single 0's.

    *   We no longer suggest that block-scope using declarations might
        be declared as const.

    *   We now avoid duplicate appended text for the same message
        number.


                ------ What's New in the 9.00i Patch  ------

    *   We introduced support for UTF-16 byte encoding (both Big and
        Little Endian).  This adds to our support for UTF-8 and plain
        Ascii.

    *   We extended our support for .vcxproj files by digging out
        include and pre-defined symbols appropriate to a build.

    *   Introduced initial support for GCC attributes.
        Unless otherwise documented, GCC attributes will be ignored.
        Over time, we will implement support for specific attributes
        as demand and resources warrant.  To err on the side of
        caution, we do not enable "__attribute__" as a reserved word
        by default. (Non-GCC compilers may use that spelling for a
        different form of attribute syntax.) Instead, we have endowed
        the semantics of GCC's __attribute__ in a reserved word that
        is spelled "__gcc_attribute__" and disabled by default.
        Support can be enabled with an option like this:
        -rw_asgn(__attribute__,__gcc_attribute__)

    *   Introduced support for the GCC "mode" attribute

    *   We now properly interpret the following loop
            int a[10];
            for( i = 10; i > 0; i-- )
                a[i] = 0;
        and give the expected warning (661 out-of-bounds pointer)
        fixing a bug that was introduced in Vers. 8.00x.
        But bewarned that the lower bound tracking for down-progressing
        indices is thereby compromised.   A complete fix will be
        available at some later time.

    *   We now support braceless switch statements; previously they
        were given an Error notification.  The reason for the change
        was the realization that "switch(0) case 0:" can be a useful
        introductory clause to a compound statement from which one can
        use the break statement to break out of.

    *   We are continuing the effort to improve our support for Misra,
        adding messages for MISRA C 1998 #62, MISRA C 2004 #15.3, and
        MISRA C++ #6-4-6, and #6-2-1.

    *   Numerous bugs have been fixed.  For a complete list, go to
        our web site www.gimpel.com and click on "Lint 9.00 Patches".
        And then find file "bugfix90.txt".


                ------ What's New in the 9.00j Patch  ------

    *   We have enhanced our MISRA coverage.  The following rules have
        been affected:
        MISRA 1998: #11 #16 #22 #25 #35 #38 #45 #50 #60 #61 #70 #71
            #90 #96 #100 #111 #112
        MISRA C 2004: #5.1 #6.1 #6.2 #6.4 #6.5 #8.1 #8.7 #8.9
            #8.12 #10.1 #10.2 #10.3 #11.1 #12.8 #12.12 #13.1 #13.3
            #13.4 #14.10 #15.1 #16.2 #18.1 #19.4 #19.10 #19.14
            #19.16 #20.2
        MISRA C++ 2008: #3-1-3 #3-9-3 #5-0-8 #5-0-11 #5-0-12 #5-8-1
            #6-4-2 #6-4-4 #7-3-1 #9-6-2 #16-0-6 #16-0-8 #16-1-1

    *   We now perform a more thorough analysis with respect to MISRA
        guidelines: in requiring an unconditional break statement at the
        end of each switch case, in processing switch statements
        generally, in some preprocessor statements, and in our
        diagnostics

    *   We now support UTF-16 within .lnt files.

    *   The taboo against using compiler optimization when compiling
        FlexeLint has tentatively been lifted

    *   Improved handling of: syntax of sizeof, long lines, collisions
        between strong typing and C++ rules, Lvalue-Rvalue conversions,
        messages during lob absorption, template member function
        evaluation, division, side-effects, Pre-Compiled Headers, new()
        calls within class members, -sem options, 'inverted' tests in
        for clauses, undeserved Fatal Error 330, unclosed File search
        handles, GCC __mode__ attribute, unused values within loops
        and for volatile variables, and messages in general.


                ------ What's New in the 9.00k Patch  ------

    *   This patch contains our initial support for MISRA C3 (MISRA
        C 2012).  MISRA C3 is a significant improvement over the
        earlier MISRA C standard (MISRA C2) being less strict and
        covering deeper, more significant, mal-practices.
        An author file, au-misra3.lnt, has been provided on the
        distribution medium and the latest copy will be contained on
        our web site.

    *   A number of new messages have been added (many for MISRA C3).
        These, and all the other new messages not included in the
        Reference Manual for Version 9.0 are provided in these notes.
        Note that we have extended our Elective Note Range into the
        9xxx territory.

    *   A new msg.txt includes these additions.

    *   Support for VS 2012 is available through co-msc110.lnt.
        Our coverage of C++ 2011 has been increased but not enough to
        handle all the new C++ 2011 syntax introduced in Microsoft
        2012.  As a stop-gap measure we are providing a file named
        "lib-msc110-emergency.lnt".  This can be used to suppress
        many unwarranted messages while using VS 2012 (msvc 11).

    *   Also included is a new file, msg.json, which contains the same
        information as msg.txt in the more easily parsed JSON format.
        The msg.json file contains an array of objects, one for each
        message.  Each object contains the string members TEXT, ID,
        COMMENTARY, and CATEGORY which contain the message text, the
        message number, the commentary present in the msg.txt file,
        and the error level, respectively.

    *   We have improved support for MISRA C 1998 and MISRA C 2004 and
        MISRA C++.

    *   A number of bugs have been fixed and the details can be found
        on our web site (www.gimpel.com) in the bugfix90.txt file.


                ------ What's New in the 9.00L Patch  ------

    *   This patch contains significantly enhanced support for MISRA
        C3 (MISRA C 2012).  A number of new messages to support MISRA
        C3 have been added and the au-misra3.lnt author file has been
        updated accordingly.  We now provide some level of support
        for all but 3 of the decidable rules and 4 of the undecidable
        rules, with full support being provided for the vast majority
        of the rules.

    *   We have broken out the 1960/1963 diagnostics (used to support
        MISRA C++) into individual messages to provide a greater level
        of control and flexibility, especially with regards to message
        suppression.  The 1960/1963 messages will continue to be
        supported for backwards compatibility.  A new author file,
        au-misra-cpp-alt.lnt, can be used to take advantage of the
        new messages in place of the 1960/1963 messages.

    *   We have improved support for MISRA C 2004, namely with regards
        to rules #8.8, #6.2, and #8.9.

    *   We have improved support for MISRA C++, namely with regards to
        rules #7-3-1, #9-6-2, and #9-6-4,

    *   We now provide significantly improved support for VS2012
        through an updated co-msc110.lnt file, available on our
        patches page.

    *   Patch 9.00L introduces support for range-based for statements,
        the 'final' class specifier, standard layout types, improved
        handling of null pointer constants, significantly improved
        handling of C++11 core language features used in Visual Studio
        2012 headers.  As with other C++ 2011 features, these are
        available using the option: -A(C++2011).

    *   We now support binary literals and digit separators from
        C++14.  These features are available using the option:
        -A(C++2014).

    *   We now support the use of message numbers and patterns with
        the +efreeze/-efreeze and ++efreeze options.  For example,
        ++efreeze(534) will prevent later-appearing options from
        suppressing message 534 without affecting the frozen status
        of other messages.

    *   We now support C11's _Static_assert (when using -A(C2011)).

    *   The Program Info facility now includes flags for indicating
        when a function has been declared with the final or override
        specifiers and when a class has been declared with final.

    *   Multiple '-deprecate()' options can now be used to combine
        deprecation messages. Such joined messages appear separated
        by commas.  For example:

            -deprecate(function, printf, Directive #2SFH)
            -deprecate(function, printf, Recommendation #LCD1C)

        would result in

            Warning 586: variable 'printf' is deprecated. Directive
                         #2SFH, Recommendation #LCD1C

        whenever 'printf()' is called.


    Disenhancements:

    We have decided to disable strong type deduction as it was
    responsible for incorrect type deduction in certain cases that did
    not involve strong types.  This feature will be revisited in a
    future release.


                      ------ Additional Options  ------

    The following features have been added since our document was
    produced.

    o  Turning off +source
       You may now turn off the +source option using the option
       --source.

    o  Arguments to compiler code options
       Compiler code options (which have the form -ccode) may in some
       cases now take arguments.  The arguments will typically reflect
       compile options passed to a compiler; thus they will tend to be
       vendor-specific.

       The supported option and argument is:

             -cmsc( clr )

       This not only sets the compiler to the Microsoft compiler but
       also indicates that the project's code is compiled with the /clr
       option, which enables support for certain core-language
       extensions.  When the above Lint option is given, Lint will
       attempt to gracefully ignore such extensions.  (Without
       -cmsc(clr), Lint will generally assume Standard-conforming code
       and issue errors where some CLR extensions are used.)

    o  .vcxproj support
       A .vcxproj file is a recent addition to Microsoft's Visual
       Studio.  Like its cousin the .vcproj file, a .vcxproj file
       describes a single project, possibly consisting of multiple
       modules.  We now process such files in a manner similar to
       .vcproj files (as described in the manual).  Thus, if you have a
       file named x.vcxproj you may process it as follows:

             lint-nt x.vcxproj >x.lnt

       This will capture in x.lnt, the module names that are embedded in
       x.vcxproj.  Unlike .vcproj files, we do not (yet) attempt to
       deduce either -i options or -d options.

    o  .sln support
       A file whose extension is .sln is treated by the Microsoft Visual
       Studio as a solution file.  It will contain the names of one or
       more project files.  These can now be processed by PC-lint.  For
       example if you have a file named s.sln it can be processed with
       the following command:

             lint-nt s.sln >s.bat

       The output (s.bat) will contain a sequence of lint commands, one
       command for each .vcproj or .vcxproj name contained within the
       .sln file.  Each command is similar to the one shown above for
       x.vcxproj.

       The curious reader may wonder why we create an intermediate file
       rather than simply process the entire solution file.  The reason
       is that a .sln file contains information about multiple projects
       and a single run of PC-lint is incapable of handling more than
       one project.  We can handle multiple modules of the same project
       but not multiple projects.  The list of commands that emerge from
       the .sln file represents independent runs of PC-lint.

    o  Enhanced support for address-specifiers
       As indicated in Section 5.8.3 Case '@' of the PC-lint/FlexeLint
       manual, some compilers that target embedded systems provide a
       language extension that enables the user to specify, in a
       declaration of a statically-allocated variable or a function, an
       address where the declared entity is to be stored.  Example:

                 int a @ 0xFF02; // 'a' is at memory location 0xff02

       Since Version 9.00e we are treating the '@' location not as an
       initializer but as a separate address specifier.  This corrected
       two problems; we were not able to use a location specifier in a
       forward declaration and initializers could not accompany location
       specifiers.  Thus we may now write

                 int b @ 0xFF00 = 42; // initializes b, at 0xff00, to 42

       So the grammar for /init-declarator/ is:

             init-declarator:
                 declarator  [address-specifier]   [initializer]

             address-specifier:
                 '@'     constant-expression

       This is now reflected in our parser.

    o  Microsoft's nested #include search
       This information may be considered as an addendum to Section 15.2
       Include Processing, Case 1.

       As of Version 9.00e the option

             +compiler(search_actively_including_stack)

       has been added to the compiler options file for the Microsoft
       compilers co-msc70.lnt through co-msc90.lnt.  This option has the
       effect of emulating Microsoft's "nested #include search" feature,
       in which an include-directive of the form:

             #include "a.h"

       causes the search for "a.h" to consider first the directory of
       the including file and then the directories of all other
       actively-including files (from most nested all the way through
       the directory containing the primary source file) before
       considering directories specified by '-i' options.

       The option has the side effect of setting +fdi.

    o  The % operator with Strong types.
       In our description of "Dimension" at the beginning of section
       9.4.1 we discuss the strong type that results from
       multiplication, division and the modulus operator.  We make the
       false claim that the type returned by the % operator is the same
       as division.  This is not true and as of Version 9.00j the
       implementation has been modified to reflect the fact that the
       type of x % y is the type of x.

    o  The +fta flag.
       A recent modification introduced the notion of checking for
       "typographical ambiguity" as defined by the MISRA C 2012 Advisory
       Directive 4.5.  Depending upon the size of the program and the
       number of declarations involved, such checking can increase the
       run time of Lint substantially. In order to regulate this
       checking, we have introduced this flag which is off by default.
       In order to receive such checking, you will need to not only
       explicitly ask for MISRA C 2012 checking with a -misra(3) option
       but also use a +fta option. This option has been included, though
       commented out, in the au-misra3.lnt options file for reference.



                ------ New or Improved Error Messages  ------

    94   xml element termination name 'String' does not match start name
         'String' -- The tag names delimiting an XML element do not
         match.

    142  case constant 'String' used previously in this switch -- A
         duplicate case constant was detected.  For example, the
         following code will be diagnosed as a repetition of case
         constant '1'.

               switch( n )
                   {
                   case 1:  m = 25;    break;
                   case 2-1: m = 27;   break;
                   }


    165  An [unscoped] enumeration cannot be forward-declared [without
         an enum-base] (int is assumed) -- This message is issued at the
         point of a forward-declaration of an enumeration like so:

                   enum E; // Error

         This is prohibited by ISO C and ISO C++98.  In C++11, we can
         modify this example to be well-formed by explicitly indicating
         the underlying integral type; example:

                   enum E : unsigned short; // Ok

         If you are not using C++11 and/or your compiler supports the
         construct you may simply suppress this message with a -e165.

    166  Function defined within a function -- A function definition was
         found within the body of another function's definition.  Such a
         construct is almost certainly an error.

    169  mode(String) requests an (integral/floating point) type of size
         N, but no such type exists. (Please check -s options in the
         Lint configuration.) -- This occurs for a use of the GCC
         attribute mode() as in:

               __attribute__((mode(DF)));

         This is supposed to match a built-in scalar type whose size is
         the size indicated in the message. If this message is issued,
         it probably means that size options have not been set to match
         the compile configuration; see Section 5.3, Size and Alignment
         Options.

    170  Explicit type-specifier required for symbol 'Symbol', int
         assumed -- A declaration did not have an explicit type as
         required by C99 or C++.  int was assumed.  This could easily
         happen if an intended comma was replaced by a semicolon.  For
         example, if instead of typing:

             double       radius,
                          diameter;

         the programmer had typed:

             double       radius;
                          diameter;


    171  Ellipsis requires at least one parameter-declaration -- A
         function declaration was seen with '...' but no
         parameter-declaration before it, as required by the ISO C
         syntax.  This diagnostic is not given for C++ code.

    318  EOF for a module found within a macro argument list -- We found
         the end of a module within the argument list of a macro.  Since
         such situations are almost certain to be erroneous, we
         gracefully shut down, alerting the User to the reason.

    330  Static assertion failure: String -- For the indicated
         static_assert directive, Lint evaluated the constant expression
         to false, and the resulting message is given by the String.

    333  Not allowed to open file 'String' -- A 'forbidden' file was
         opened.  Opening such a file is considered a security violation
         by a hosted implementation.

    436  Apparent preprocessor directive in invocation of macro 'Symbol'
         -- This is issued in the context of an invocation of a
         function-like macro; example:

               #define FOO(p) p

               FOO(
                       #define X Y
                  )

         According to the ISO Standards, this results in undefined
         behavior.  By the rules of Standard C the preprocessing
         directive is absorbed into the macro argument but then will not
         subsequently get executed.  For this reason some compilers
         treat the apparent preprocessor directive as a directive.  This
         is logical but not portable.  It is therefore best to avoid
         this construct.

    446  side effect in initializer -- An initializer containing a side
         effect can be potentially troublesome. For example, given the
         code:

               void f( int i )
                   {
                   int a[2] = {i++, i++};
                   }

         The values of the array elements are unspecified because the
         order of evaluation is unspecified by the C standard.

    483  boolean value in switch expression -- At least one standards
         organization has expressed the perspective, if the expression
         of a switch-statement is boolean in nature, if-else should be
         used instead.

    484  Stringize operator followed by macro parameter followed by
         pasting operator -- Due to order of evaluation issues, the
         mixing of stringizing and pasting operators, particularly when
         appearing in the order # parameter ##, results in unspecified
         behavior.

    485  Duplicate initialization of object element -- This message is
         given upon an inconsistent use of designated initializers (used
         for specific fields of arrays or structures).  It is possible
         for an element of such an aggregate to be initialized twice
         either through the use of two separate designators or through a
         designator and the conventional sequential initialization
         process.  In either case the end result is not specified and
         the construction is usually a sign of a logic error.

    486  attempting to write to a file opened as read-only -- A file
         pointer was obtained with a call to an fopen-like function in
         read-only mode. This pointer was then used in an attempt to
         write to the file. The ISO standards leave the behavior in such
         cases as unspecified.

    488  Symbol 'Symbol' has same implicit enumerator value 'String' as
         enumerator 'Symbol' -- Two enumerators have the same value and
         at least one received that value implicitly. For example:

           enum colors { red, blue, green = 1 };

         will elicit this informational message while

           enum colors { red, blue = 1, green = 1 };

         will not.

    489  attempting to modify the contents of a string literal -- An
         assignment to an element of a string literal was seen. Doing so
         results in undefined behavior.

    491  non-standard use of 'defined' preprocessor operator -- The ISO
         standards restrict the use of the defined preprocessor keyword
         to either

               defined(identifier)
               defined identifier

         Additionally, the preprocessor operator may not result from the
         expansion of another macro. This diagnostic highlights
         departures from these requirements as non-portable code.

    510  File extension 'String' reserved for future versions of this
         product -- File name extensions that are not those recognized
         as implying C++ source code or indirect files for lint or
         pre-compiled headers for lint or lint object modules or project
         files are assumed to be C source code.  If we recognize a new
         file extension in some future version of lint it can be
         beneficial to warn about the use of this file extension in any
         earlier version of lint.  One reason for this is to aid in the
         transition between versions of the product.  During this
         transition period a new file extension may be provided
         unintentionally to a former version of the product resulting in
         surprising behavior.

    598  Excessive shift value (precision Integer shifted left by
         Integer) -- A quantity is being shifted to the left by a value
         greater than or equal to the precision of that quantity or by a
         negative value. For example,

             i << 32

         will elicit this message if i is typed int and where int is 32
         bits wide or less (the usual case). Such shift results in
         undefined behavior. To suppress the message you may cast the
         shifted quantity to a type whose length is at least the length
         of the shift value.

    686  Option 'String' is suspicious because of 'Name' -- An option is
         considered suspicious for one of a variety of reasons.  The
         reason is designated by a reason code that is specified by
         Name.  At this writing the following reasons for issuing this
         message exist:

         o  unbalanced quotes -- An option was seen with a quote
         character which was not balanced within that same option.

         o  backtick preceding non-meta character is superfluous and has
         been dropped -- A backtick (`) was seen before a character
         other than a * or a ?. The use of a backtick in this fashion
         has no effect.

         o  Upper case characters within extension 'String'; these will
         match lower case when +fff is on; try -fff -- A file extension
         involving upper-case letters was seen in a +cpp(), +lnt(), or
         +ext() option while the +fff flag was active. If, for example,
         you intend for .c to indicate a C module and .C to indicate a
         C++ module, turning off the fff flag will help avoid
         unnecessary complaints from Lint.

         o  extraneous characters following String -- One or more
         characters were seen immediately following a character which is
         expected to signify the end of an option, such as a closing
         right parenthesis. While the extraneous characters are ignored,
         their presence may indicate a typographical error.

         o  missing field-specifier in a non-empty format string [No
         data will be generated for this category.] -- A -program_info()
         option was expecting a field-specifier which was actually
         missing. As noted, no data for this particular category will be
         generated.

         o  the likelihood of causing meaningless output -- An option,
         such as -elib(*), -wlib(0), or +fce was seen; this typically
         hides a problem in the Lint configuration. When using a new
         Lint configuration, it's common for a user to encounter Error
         messages from Lint about library header code. (This usually
         does not indicate a problem with library headers.) For example,
         a misconfiguration of Lint's preprocessor is by far the most
         common source of these errors.  If you merely suppress basic
         Syntax Errors (like Error 10) and/or Fatal Errors (like Error
         309), the underlying Lint configuration problem still exists;
         as a result, Lint will fail to parse your code correctly
         (because your code depends on the aforementioned library code).
         The output from Lint would then seem illogical and/or
         meaningless. Therefore, blanket suppression options like this
         are highly discouraged.  Instead, other aspects of the Lint
         configuration should be modified to make Lint's behavior more
         similar to that of the compiler at (or, typically, before) the
         point of the Error.

         o  a lack of an argument -- A -message() was found to not
         include text between the parentheses, rendering the option
         meaningless. Did the User possibly intend to include the text
         immediately after this option?

    1009 operator 'String' not redefinable -- The three operators:

               .*   ?   .

         are not redefinable and may not be overloaded [11, 13.4].

    1084 Ambiguous use of template-id for instantiation of 'Type' --
         When the language calls for a class template to be instantiated
         and the primary template is "overloaded" via one or more
         partial specializations, there is an attempt to see if the
         template arguments match any of those partial specializations.
         (Note, explicit specializations would have been considered
         before determining that the class definition needs to be
         generated by way of instantiation.)  If multiple partial
         specializations match then:

             - If one of the matching partial specializations is more
               specialized than all others then it is used for the
               instantiation.

             - Otherwise, the program is ill-formed, so Lint issues
               message 1084.

         In the message, the matching partial specializations are
         provided as the list of candidates.  Example:

               template<class T1, class T2, int I> class A {};             //#1
               template<class T1, class T2, int I> class A<T1*, T2, I> {}; //#2
               template<class T1, class T2, int I> class A<T1, T2*, I> {}; //#3
               A<int*, int*, 2> a; // ambiguous: matches #2 and #3
                   // (and neither template is more specialized than the other)


    1096 A target ctor must be the only mem-initializer in the
         mem-initializer-list of a delegating ctor -- C++11 requires
         that if a constructor delegates to another constructor, then
         the mem-initializer (the region between the colon and the
         function body) must contain only one item, and that item must
         be a call to another constructor (which is called the "target
         constructor").  Example:

           struct A
               {
               int n;
               A(int);
               A( const A& p) : A(p.n) {} // Ok
               A() :
                   n(42),  A(32)  // Error 1096
                   {}
               };


    1097 Delegating ctor delegates directly to itself, causing infinite
         recursion -- Example:

           struct A
               {
               int n;
               A(int x) : A(x){} // Error 1097
               };


    1098 Function template specialization 'Symbol' does not match any
         function template -- This message is issued for a declaration
         where the user apparently intended to name a specialization of
         a function template (e.g., in an explicit specialization, an
         explicit instantiation or a friend declaration of
         specialization), but no previously-declared function template
         is matched.  Example:

               template<class T> void f( const T& ); // #1

               struct A{};
               template<> void f( const A& ); // Ok
               // (A is the deduced argument to T.)

               struct B{};
               template<> void f( const B ); // Error 1097.
               // (A template argument cannot be deduced for T.)


    1099 Ambiguous function template specialization 'Symbol' -- This
         message is issued for a declaration where the user apparently
         intended to name a specialization of a function template (e.g.,
         in an explicit specialization, an explicit instantiation or a
         friend declaration of specialization), but the specialization
         matches multiple function templates, and none of the matched
         templates is more specialized than all of the other matching
         templates.  The candidates (i.e., the matching templates) are
         provided in the message.  Example:

               template<class T> struct A {};

               template<class T, class U> void f( T*, U    ); // #1
               template<class T, class U> void f( T,  A<U> ); // #2

               struct B{};
               template<> void f( B, A<B> ); // Ok
               // #1 does not match but #2 does.

               template<> void f( char*, A<int> ); // Error 1099
               // Both #1 and #2 match and neither is more specialized than the
               // other.

         This situation can be avoided in at least a couple of ways.
         One way is to explicitly specify one or more template
         arguments.  Example:

               // continuing from above...
               template<> void f<char*>( char*, A<int> ); // Ok
               // #1 does not match but #2 does.

         Another way is to use SFINAE tactics in the declaration of one
         or more function templates, e.g. with boost::enable_if.

    1100 Declaration of 'Symbol' does not declare an explicit
         specialization, explicit instantiation or friend -- In a
         declaration that explicitly specifies template arguments with
         angle brackets immediately after the name of a function
         template, the declaration must declare either an explicit
         specialization, explicit instantiation or friend.  (Note, an
         explicit specialization always begins with 'template<>' and an
         explicit instantiation always begins with 'template'---without
         angle brackets after the keyword 'template'.)

               template<class T> struct A {};

               template<class T> inline void f( A<T> ); // #1
               void f( A<int> ); // #2 // Ok, declares an ordinary function

               void f<char>( A<char> ); // Error 1100


    1101 Type of variable 'Symbol' cannot be deduced from its
         initializer -- Example:

               int f(void);
               int f(char*);
               auto n = f; // Error

         In terms of deduction, this is equivalent to:

               int f(void);
               int f(char*);
               template<class T> void g( const T& );
               void h( void )
                   {
                   g( f ); // Error
                   }

         Here,  'f' refers to multiple overloaded functions, so it is an
         ambiguous reference and T cannot be deduced.  (Code like this
         could still be well-formed however, e.g. if g is overloaded
         with a non-template function whose parameter type is
         'ptr-to-function returning int taking (char*)'.)

    1102 auto type deduced inconsistently: 'Type' for 'Symbol' but
         'Type' for 'Symbol' -- When multiple variables are defined in
         the same declaration, and when that declaration uses the
         keyword auto as the type-specifier (a feature of C++11), the
         type for which auto is a placeholder must be the same for each
         variable.  Example:

               float g(void);
               char* s();
               auto a = 42; // Ok, auto is 'int'
               auto b = g(); // Ok, auto is 'float'
               auto c = 'q',
                    *d = s(); // Ok, auto is 'char' (for both c and d)
               auto x = 42, y = g(); // Error 1102 here


    1103 Type 'Type' is not allowed as an enum-base -- When an
         enumeration type is declared with an explicit underlying type,
         that type must be integral.  Example:

               enum A : bool; // ok
               enum B : short; // ok
               enum C : unsigned long long; // ok
               enum D : float; // Error 1103


    1104 A reference to enumeration 'Symbol' should not use 'String' --
         Although an enumeration may be declared or defined using a
         scope indicator or an underlying type indicator, these should
         not be applied when simply referencing the enumeration.  E.g.

               enum class A { red, green };
               enum class A x;         // Error: don't need 'class'
               enum A : unsigned { red, green };
               enum A : unsigned y;    // Error: don't need ': unsigned'


    1105 Use of ref qualification of 'Symbol' inconsistent with
         overloaded function 'Symbol' (Location) -- If an explicit ref
         qualifier ('&' or '&&') of a nonstatic member function is
         employed, an explicit ref qualifier needs to be used with every
         member of the overload set.  Thus:

               class A
                   {
                   void f(int) &;  // ok (so far)
                   void f(int);    // 1105
                   void f(double); // 1105
                   void g(int);    // ok (fresh function)
                   void g(double); // still ok
                   };


    1106 Initializing value 'String' of enumerator 'Name' cannot be
         represented by the enumeration's underlying type 'Type' -- An
         enumerator is being initialized with a value that is
         inappropriate to the declared type of the initializer.
         Example:

               enum E : unsigned char { e = 256 };

         The value 256 cannot be represented by an unsigned char.

    1107 Mixing two different kinds of string literals -- Two string
         literals are being concatenated which have different types.
         Examples:

               char *s = u"abc" U"def";
               char *q = L"ghi" u"jkl";

         This message is issued for mixing strings of char16_t,
         char32_t, and/or wchar_t (as shown).  Literal string
         concatenation of any of these with an ordinary character
         literal is permitted and will receive Informational 707.

    1108 Use of deleted function 'Symbol' defined at 'Location' -- This
         message is issued when a deleted function is used.  Example:

               void f( int ) = delete;
               void f( double );
               void g( double d, int n ) {
                   f( d ); // Ok
                   f( n ); // Error
               }


    1110 Cycle detected: explicit application of 'Name'::operator->
         causes infinite implicit applications of the same operator --
         When an overloaded operator-> is used as in

               a->b

         it is effectively expanded to:

               a.operator->()->b

         And this expansion repeats until an operator-> is found that
         does not yield a class type.  But in the process of evaluating
         this expansion, it might be found that one  of the operators
         returns a class type for which an overloaded operator-> was
         already expanded; in that case, Error 1110 is triggered.
         Example:

               struct B;
               struct A { struct B& operator->(); };
               struct B { struct A& operator->(); };
               int  f( A & p ) { p->g(); } // Error


    1111 ISO C++ requires an explicit specialization/instantiation to
         appear at namespace scope -- This message is issued at the
         beginning of each explicit specialization/instantiation that
         does not appear at namespace scope.  Example:

               struct A {
                   template <typename U> struct B {};

                   // template <>  // Would be ill-formed by ISO C++.
                   //     struct B<int> {};
               };
               template<> struct A::B<int> {}; // Ok.

         There is an additional limitation with member class templates
         of class templates.  As with members of a non-template class,
         one cannot write a specialization at class scope.   Example:

               template<typename T> struct G {
                   template <typename U> struct H {};
                   // template <>  // Would be ill-formed by ISO C++.
                   //     struct H<int> {};
               };

         But the language specification does not even allow this to be
         expressed in a namespace-scope definition; there is no way to
         write an explicit specialization that is a member of a class
         template.  Example:

               template<typename T> struct J {
                   template <typename U> struct K {};
               };
               // template<typename T>
               //     template <>  // Would be ill-formed by ISO C++;
               //         struct J<T>::K<int> {};

         This is because the rules for explicit specializations say that
         'template<>' is not allowed to appear after a non-empty
         template-parameter-list within the same declaration.  However,
         one may write an explicit specialization that is a member of an
         implicitly-instantiated specialization of a class template.
         Example:

               template<typename T> struct L {
                   template <typename U> struct M {};
               };
               template <> template <> struct L<char>::M<int> {}; // Ok

         Here, the body of the class L<char> is automatically generated
         by implicit instantiation (otherwise the reference to
         'L<char>::M' would be ill-formed), while the body of
         L<char>::M<int> is provided in the explicit specialization.

         In March of 2009, the ISO C++ committee reviewed a report
         submitted against this example:

              struct A {
                 template<class T> struct B;
                 template <class T> struct B<T*> { }; // well-formed
                 template <> struct B<int*> { }; // ill-formed
               };

         While it might seem odd that one is able to write the partial
         specialization but not the full specialization, the committee
         (which at the time was in a "feature-freeze" mode and trying to
         finalize a draft for the next International Standard) decided
         that this capability would need to be regarded as an
         "extension", meaning that it could be considered as a new
         feature in a future standard but not as a bug-fix for C++11.

         Note that the Microsoft compiler implements this extension.
         For that reason, the Lint option

               -elib(1111)

         appears in recent versions of our configuration files for
         Microsoft compilers.

    1112 In a declaration, the form 'auto D(parms)->type' (where D is
         either a name or a parenthesized region) is the only valid way
         to use a trailing-return-type -- For example, if you want to
         declare that f returns a pointer-to-int, you must write:

               auto f() -> int *;

         ... and not:

               auto *f() -> int;

         This also applies to a type-id (e.g., in a cast to a
         pointer-to-function, or as an argument to a template
         type-parameter).

    1113 In this use of 'Template', type substitution failed for 'Type'
         -- Type is the type of Template; it is used at the cited
         location with concrete arguments, but substitution failed.
         Example:

               template<class T> using X = typename T::type;
               typedef X<int> XI; // error 1113


    1116 Virtual function 'Symbol' overrides function marked with final
         -- A derived class attempted to override a virtual function
         that is marked with the final virt-specifier in a base class.

    1117 Non-virtual function 'Symbol' marked with 'String' -- A
         virt-specifier (final or override) was supplied to a
         non-virtual function.

    1118 Virtual function 'Symbol' already marked with 'String' -- A
         virt-specifier (final or override) was encountered multiple
         times for the specified virtual function.

    1119 Virtual function 'Symbol' marked with override does not
         override -- A virtual function was marked with the override
         keyword but does not override a base class function.

    1120 Incomplete type 'Type' is not a valid range expression -- An
         incomplete type was used as a range expression in a range-based
         for statement.  A range expression must be a complete type.

    1121 No viable 'String' function defined for type 'Type' used as
         range expression -- A non-array range expression used in a
         range-based for statement has no viable begin or end function.

    1122 Range expression of type 'Type' has 'String' member but no
         'String' member -- The type of a range expression used in a
         range-based for statement has either a begin or end member
         function but not both.

    1123 Attempt to derive from class 'Symbol' marked as 'final' at
         Location -- A class that was marked with the final
         class-virt-specifier was used as a base class in a class
         declaration.

    1124 Digit separator not allowed: 'String' -- A digit separator
         character was encountered within a numeric literal at a point
         where digit separators are not allowed.  Digit separators are
         allowed only between digits of a numeric literal and cannot be
         adjacent to each other.  String contains additional information
         related to the specific misuse such as "after digit sequence",
         "following base prefix", "consecutive digit separators", etc.

    1125 A type cannot be defined in a friend declaration -- Example:

               class A {
                 friend struct B;    // ok
                 friend struct C {}; // error
               };

    1126 In std::underlying_type<T>, T must be an enumeration type; but
         here, T is 'Type'. -- The special library template
         std::underlying_type is intended to take an enumeration type;
         when this condition is satisfied, its typedef member 'type' is
         the underlying integral type of the enumeration. This error is
         issued for the case where the type is not an enumeration.

    1127 catch handler after catch(...) -- A catch handler appeared
         following a catch(...) in the same try-catch statement which
         invokes undefined behavior.

    1419 explicit throw of the NULL macro -- The macro NULL was passed
         to a throw expression.  An exception resulting from such a
         throw can be caught only by an exception handler expecting an
         integer type, it will not be caught by an exception handler
         expecting a pointer type which may not be obvious.

    1574 Returning the address of an auto variable indirectly through
         reference variable 'Symbol' -- Within a function whose return
         type is reference to some type, a return statement is returning
         a reference which has been initialized (possibly indirectly)
         with an auto variable.  For example:

               int &f( int k )
                   {
                   int &r = k;
                   return r;
                   }


    1723 Template 'Symbol' arbitrarily selected.  Refer to Error
         'Integer' -- This is a supplemental message to the Error that
         immediately preceded, which was about a failure to select a
         single best partial specialization for an instantiation. Its
         purpose is to show some of the context of subsequent processing
         (which is now in a state of recovery).  Example:

               template<class T, class U> struct A;
               template<class T, class U> struct A<T*, U> {  };
               template<class T, class U> struct A<T, U*> {  };
               A<int*, char*>  x; // Error 1084 followed by Info 1723


    1751 unnamed namespace in header -- An unnamed namespace was used in
         a header file.

    1915 Overriding virtual function 'Symbol' is not marked with
         override -- A virtual function that overrides a base class
         function was not declared with the override virt-specifier.
         This message is emitted only for C++11 and higher.

    9001 Octal constant used -- An octal constant appears in the code.
         Octal constants may be inadvertently interpreted by engineers
         as decimal values. This message is not issued for a constant
         zero written as a single digit.

    9003 could define variable 'Symbol' at block scope -- A variable was
         declared at global scope but only utilized within one function.
         Moving the declaration of this variable to that function
         reduces the chance the variable will be used incorrectly.

    9004 object/function 'Symbol' previously declared -- The named
         symbol was declared in multiple locations, not counting the
         point of defintion for that symbol. Declaring a symbol in one
         location and in one file helps to ensure consistency between
         declaration and definition as well as avoiding the risk of
         conflicting defintions across modules.

    9005 attempt to cast away const/volatile from a pointer or reference
         -- A cast attempted to remove the qualifiers from an object to
         which a pointer points or a reference refers. Doing so can
         result in undesired or unexpected modification of the object in
         question and may result in an exception being thrown.

    9006 'sizeof' used on expression with side effect -- If the operand
         of the sizeof operator is an expression, it is not usually
         evaluated.  Attempting to apply sizeof to such an expression
         can result, therefore, in code one expects to be evaluated
         actually not being evaluated and the side-effects not taking
         place.

    9007 side effects on right hand of logical operator, 'String' -- The
         right hand side of the || and && operators is evaluated only if
         the left hand side evaluates to a certain value.  Consequently,
         code which expects the right hand side to be evaluated
         regardless of the left hand side can produce unanticipated
         results.

    9008 comma operator used -- The comma operator is thought by some to
         reduce readability in code.

    9009 floating point variable used as loop counter -- The use of
         floating point variables as loop counters can produce
         surprising behavior if the accumulation of rounding errors
         results in a different numer of iterations than anticipated.

    9011 more than one 'break/goto' terminates loop -- More than one
         break or goto statement was seen in a loop. Minimizing the
         number of exits from a loop is thought by some to reduce visual
         complexity of the code.

    9012 sub-statement should be a compound statement -- Multiple
         authors have advised making sure the body of every
         iteration-statement and selection-statement be a
         compound-statement. However, no { was seen to begin the
         compound-statement.

    9013 no 'else' at end of 'if ... else if' chain -- An if ... else if
         chain was seen without a final else statement. Providing such a
         statement helps to act as an analog to the default case of a
         switch-statement.

    9014 default missing from switch statement -- A switch-statement was
         found without a default case.  Providing such a case provides
         defensive programming.

    9015 macro argument is used both with and without '#/##' and is
         subject to further replacement -- A macro argument was used
         both as an operand to the stringizing or pasting operators and
         not used as such.  Moreover, this macro argument is subject to
         further replacement.  This could cause confusion.

    9016 pointer arithmetic other than array indexing used -- Array
         indexing is thought, by some, to be more readily understood and
         less error prone than other forms of pointer arithmetic.

    9017 pointer arithmetic by increment or decrement used -- While at
         least one standards organization cautions against using any
         pointer arithmetic besides array indexing, the use of increment
         or decrement operators with pointers may represent an intuitive
         application and illustration of the underlying logic.
         Consequently, such constructs are separated from the prior
         message #9016 and placed under this one, allowing more fine
         tuning of Lint diagnostics.

    9018 declaration of union type or object of union type, 'Type' --
         Depending upon padding, alignment, and endianness of union, as
         well as the size and bit-order of their members, the use of
         unions can result in unspecified, undefined, or implementation
         defined behavior, prompting some to advise against their use.

    9019 declaration of 'String' before #include -- The symbol mentioned
         in String was seen in a module with a subsequent #include
         directive. It can be argued that collecting all #include
         directives at the beginning of the module helps improve code
         readability and helps reduce the risk of undefined behavior
         resulting from any use of the ISO standard library before the
         relevant #include directive.

    9020 header file name with non-standard character 'String' -- The
         use of non-standard characters in #include directives results
         in undefined behavior.

    9021 use of '#undef' is discouraged: 'String' -- The use of the
         #undef directive can lead to confusion about whether or not a
         particular macro exists at a randomly given point of code.

    9022 unparenthesized macro parameter in definition of macro 'String'
         -- Multiple authors have cautioned against the use of
         unparenthesized macro parameters in cases where the parameter
         is used as an expression. If care is not taken, unparenthesized
         macro parameters can result in operator precedence rules
         producing expressions other than intended. See also warning
         665.

    9023 Multiple use of '#/##' operators in definition of macro
         'String' -- Multiple use of such operators is thought by some
         to increase the risk of undefined behavior.

    9024 '#/##' operator used in macro 'String' -- The use of such
         operators is thought to reduce code clarity and increase the
         risk of undefined behavior.

    9025 More than two pointer indirection levels used for type 'Type'
         -- Three or more levels of pointer indirection may make it
         harder to understand the code.

    9026 Function-like macro, 'String', defined -- Multiple authors have
         expressed reasons why a function, when possible, should be used
         in place of a function-like macro.

    9027 Unpermitted operand to operator 'String' -- Out of concern for
         unspecified, undefined, and/or implementation defined behavior,
         some standards urge restrictions on certain types of operands
         when used with certain operators.

    9028 Unpermitted arithmetic involving an essentially character type
         -- MISRA C 2012 has defined the concept of essentially
         character type and placed restrictions on the use of
         expressions with such a type.

    9029 Mismatched essential type categories for binary operator --
         MISRA C 2012 has defined the concept of essential type and
         placed restrictions on the use of expressions with certain
         types with respect to binary operators.

    9030 Impermissible cast -- MISRA C 2012 has defined the concept of
         essential type and placed restrictions on the use of casts
         between certain types.

    9031 Composite expression assigned to a wider essential type --
         MISRA C 2012 has defined the concepts of composite expression
         and essential type and placed restrictions on assignments of
         the former.

    9032 Composite expression with smaller essential type than other
         operand -- MISRA C 2012 has defined the concepts of composite
         expression and essential type and placed restrictions on
         operands to binary operators when at least one of the operands
         meets the definition of the former concept.

    9033 Impermissible cast of composite expression 'Reason' -- MISRA C
         2012 has defined the concepts of composite expression and
         essential type and placed restrictions on casts of the former.
         This message, when given, is also followed by text explaining
         why the cast is considered "impermissible".

    9034 Expression assigned to a narrower or different essential type
         -- MISRA C 2012 has defined the concept of essential type and
         placed restrictions on assignments in relation to such types.

    9035 Variable length array declared -- Some have expressed concern
         over the use of variable length arrays, noting how, even in
         common use cases of arrays, use of such arrays can result in
         undefined or unspecified behavior.

    9036 Conditional expression should have essentially Boolean type --
         MISRA C 2012 has defined the concept of essentially Boolean
         type and requires that the conditional expressions of all if
         and iteration-statements comply with this definition.

    9037 Conditional of #if does not evaluate to 0 or 1 -- Some urge
         such a practice in the interest of strong typing.

    9038 Flexible array member declared -- Flexible array members can
         alter the behavior of sizeof in surprising ways. Additionally,
         flexible array members often require dynamic memory allocation
         which may be problematic in safety critical code.

    9039 Prohibited escape sequence usage -- An octal or hexadecimal
         escape sequence has been detected within a string or character
         literal which is not immediately followed by another escape
         sequence or end of literal.  Such escape sequence usage has
         been deprecated on the grounds of potential confusion when
         attempting to read such code.

    9041 goto 'Symbol' appears in block 'String' which is not nested in
         block 'String' which contains the label. -- It has been deemed
         safer by some experts that the block (i.e. compound statement)
         containing the goto should be the same as or nested within the
         block containing the label.  Thus

               {  label:  {  goto label;  }  }

         is permitted but

               {  goto label;  {  label:  }  }

         is not.  To assist the programmer, the message refers in the
         blocks using an identification code (Example: "1.2.1").  This
         identification scheme is defined as follows.
             (a) The outer block has an identification of 1.
             (b) If a particular block is identified by x then its
                 immediate subblocks, if any, are identified as x.1,
                 x.2, x.3, etc.

         Thus in the following 'code',

               {  {  }  { { label: } { } } }

         label: lies in block 1.2.1.

    9042 departure from MISRA switch syntax -- A switch-statement was
         found which does not comply with the MISRA switch-statement
         syntax.

    9043 static keyword between brackets of array declaration -- Some
         advocate against using the keyword static in array declarations
         due to a perceived increased risk of undefined behavior.

    9044 function parameter modified -- It has been advocated that
         function parameters be first copied to local variables where
         they can be modified rather than modifying the parameters
         directly.

    9045 non-hidden definition of type 'Type' -- Some advise against
         including structure definitions unless the definition is
         required for the current module.

    9046 Typographical ambiguity with respect to symbol, 'Symbol',
         Reasons, Location -- Some have warned against the use of
         identifiers which may be considered typographically ambiguous.
         In addition to the name of the previously seen symbol, the
         reasons Lint considers the identifiers to be ambiguous and the
         location of said previous symbol are provided in the message,
         if available.

    9047 FILE pointer dereferenced -- At least one standards
         organization urges against this practice, directly or
         indirectly.

    9048 unsigned integer literal without a 'U' suffix -- An integer
         literal of unsigned type was found without a 'U' suffix.

    9049 increment/decrement operation combined with other operation
         with side-effects -- An expression was seen involving an
         increment or decrement operator and the expression also
         contained potential side-effects other than those resulting
         from said operator.

    9050 dependence placed on C/C++ operator precedence -- Reliance on
         operator precedence was found in a particular expression.
         Using parentheses, it is felt, helps clarify the order of
         evaluation.

    9051 macro 'Symbol' defined with the same name as a C keyword -- A
         macro was defined with the same name as an ISO C keyword. The
         use of such a macro causes undefined behavior.

    9052 macro 'Symbol' defined with the same name as a C++ keyword -- A
         macro was defined with the same name as an ISO C++ keyword. The
         use of such a macro causes undefined behavior.

    9053 the shift value is at least the precision of the essential type
         of the left hand side -- MISRA 2012 defines the notion of an
         "essential type". A quantity with a certain essential type, as
         defined by MISRA, was left shifted by a number exceeding the
         number of bits used to represent that essential type.

    9054 designated initalizer used with array of unspecified dimension
         -- It has been advocated, when array initializers contain
         designators, the dimension of the array should be explicitly
         stated in the declaration. The initializer of the array in
         question has been found in violation of this recommendation.

    9055 Most closely enclosing compound statement of a case/default is
         not the body of a switch -- Switch labels nested inside of
         compound statements within the corresponding switch are legal
         but can reduce comprehension and lead to unstructured code.

    9056 Inline function 'Symbol' defined with storage-class specifier
         'String' -- This message is issued for all inline functions
         defined with a storage-class specifier.  +estring can be used
         to find all inline functions defined with a specific specifier.
         For example, +estring(9056, extern) will report all inline
         functions defined with extern.

    9057 Lowercase L follows 'u' in literal suffix -- A lowercase letter
         "l" is used inside of a literal suffix following an upper or
         lowercase letter u.  With some fonts, the lowercase letter "l"
         can be easily confused with the number one.  This is less
         likely to happen when there is a "u" between the number and the
         "l" (as in 35ul), but some coding standards forbid the use of
         "l" in any literals.  Message 620 reports the more suspicious
         case where the "l" immediately follows a number (as in 35l).

    9058 tag 'Symbol' (Location) unused outside of typedefs -- A tag was
         used only in the course of creating a typedef.  Was the tag
         unused by mistake (say a recursive reference inside the body of
         the struct was accidentally omitted)?  Such tags are most often
         redundant and can be eliminated.

    9059 C comment contains C++ comment -- A C++-style comment was seen
         inside a C-style comment.  This can be confusing.

    9060 trigraph in comment -- A trigraph was seen inside a comment.
         Since trigraphs are translated before preprocessing, a trigraph
         sequence like ??/ can have surprising results, especially in a
         C++ style comment where the trigraph sequence translates into a
         backslash.

    9063 no comment or action in else-branch -- An else-branch was seen
         which contained neither a comment nor an actionable statement.
         At least one standards organization cautions against such
         "empty else" branches.

    9064 goto references earlier label -- A goto makes reference to a
         label appearing earlier in the code. At least one author
         recommends all such statements reference points later in the
         code in an attempt to reduce visual code complexity.

    9066 C++ comment contains C comment -- A C-style comment was seen
         inside a C++-style comment.  This can result in confusion.

    9067 array declared without explicit dimension -- An array was
         declared without a dimension. At least one standards
         organization advises against such a practice in the interest of
         safety. Note: this message is not given if the array is
         initialized at the time of declaration.

    9068 partial array initialization -- An array has been initialized
         only partly. Providing an explicit initialization for each
         element of an array makes it clear every element has been
         considered. This diagnostic is not issued if the array is
         initialized with a {0} initializer or if the initializer
         consists entirely of designated initializers  or if the array
         is initialized using a string literal.

    9069 in initializer for symbol 'Symbol', initializer of type 'Type'
         needs braces or designator -- An array is initialized without
         sufficient braces or designators to clarify exactly which
         elements are initialized with which values.

    9070 recursive function 'Symbol', location Location -- The named
         function has been found to potentially call itself, either
         directly or indirectly. Recursion carries with it the danger of
         exceeding available stack space, which can lead to a run-time
         failure.  All else being equal, the more that recursion is
         constrained, the easier it can be to determine the worst-case
         stack usage.

    9071 defined macro 'Name' is reserved to the compiler String -- A
         macro was defined which is reserved to the compiler. Such
         definition results in undefined behavior. If String is present,
         the macro name is one of the more obscure identifiers reserved
         and String provides an explanation to that effect.

    9072 parameter list differs from prior declaration for function
         'Symbol' -- The parameter list for the named function differs
         from a previously seen declaration either by type or parameter
         name.  At least one author advises against such inconsistency
         for various reasons.

    9074 conversion between a pointer to function and another type -- A
         conversion was seen between a pointer to function and a
         different type. The conversion of a pointer to a function into
         or from a pointer to object, pointer to incomplete type, or
         pointer to void results in undefined behavior and,
         consequently, at least one standards organization advises
         against such practice. This diagnostic is suppressed if the
         conversion is to void.

    9075 external symbol 'Symbol' defined without a prior declaration --
         If a declaration for an object or function is visible when that
         object or function is defined, a compiler must verfiy that the
         declaration and definition are compatible. A lack of prior
         declaration prevents such checking.

    9076 conversion between a pointer to incomplete type and another
         type -- Conversions involving pointers to incomplete types
         cause undefined behavior if converted to or from a floating
         point type and can cause incorrect alignment if to or from a
         pointer type. This message is suppressed if the conversion is
         to void. Also, for purposes of this diagnostic, pointers to
         void are not treated as pointers to incomplete types.

    9077 missing unconditional break from final switch case -- A case at
         the end of a switch had no unconditional break.  Some coding
         guidelines require the use of a break for every switch case,
         including the last one, for maintenance reasons.

    9078 conversion between a pointer and integer type -- A conversion
         between a pointer type and an integer/enum type was seen. Such
         conversions can result in undefined behavior if the pointer
         value cannot be represented in the integer/enum type. This
         diagnostic is not given for null pointer constants.

    9079 conversion from pointer to void to pointer to other type --
         Conversion of a pointer to void into a pointer to object may
         result in a pointer which is not correctly aligned, resulting
         in undefined behavior.

    9080 integer null pointer constant used -- An integer null pointer
         constant other than the NULL macro was used. Using the NULL
         macro makes it clear a null pointer constant was intended.

    9081 too few independent cases for switch -- A switch was seen with
         fewer than two non-consecutive case labels. A switch with fewer
         than two such cases is redundant and may indicate a programming
         error.

    9082 switch statement should either begin or end with default label
         -- Placing the default label either first or last makes
         locating it easier.

    9083 undefined macro 'String' matches an identifier reserved to the
         compiler -- A #undef was seen applied to an identifier given by
         String and that identifier is reserved to the compiler by the
         ISO C/C++ standards.

    9084 result of assignment operator used in larger expression -- An
         assignment expression was seen inside a larger expression. The
         use of assignment operators, simple or compound, in combination
         with other arithmetic operations can significantly impair the
         readability of the code.

    9085 statement or comment should appear in default case -- A default
         was seen without a comment or statement between it and either
         the corresponding break or, if default is the last case in the
         switch, the closing }. Adding a statement to take action or
         adding a comment to explain why no action is taken is a form of
         defensive programming.

    9086 include directives should have single arguments -- A #include
         directive is followed by more than one angle bracket sequence
         or string literal. The ISO standards do not define behavior in
         such cases.

    9087 cast performed between a pointer to object type and a pointer
         to a different object type -- A cast was seen between two
         pointer types which differ with respect to what those types
         point to. Additionally, the type to which the expression was
         cast is not a pointer to char, whether signed or unsigned. At
         least one standards organization has cautioned against such a
         practice.

    9088 named signed single-bit bit-field -- A named bit-field was
         declared with a signed data type and only one bit of width.
         According to the ISO C Standard, a single-bit signed bit-field
         has one sign bit and no value bits and, consequently does not
         specify a meaningful value.

    9089 potential side-effect in argument to sizeof -- An argument to
         sizeof was found to have a potential side-effect.  Arguments to
         sizeof are not usually evaluated, unless the argument names a
         variable length array type. Avoidance of such arguments is
         advised.

    9090 unconditional break missing from switch case -- A switch case
         was seen which did not conclude with an unconditional break.
         Some authors advise against such absences on the grounds they
         are often errors.

    9091 casting from pointer type to integer type -- A cast of a
         pointer to an integer type was seen. Since the size of the
         integer required when a pointer is converted to an integer is
         implementation defined, some coding guidelines advise against
         such casts.

    9102 possible digraph, 'String' -- A possible digraph was seen. At
         least one set of coding guidelines advises against such due to
         the risk of failure to meet developer expectations.

    9103 identifier with static storage is reused. See 'Symbol' at
         Location -- An identifier of the given name was seen declared
         static in one location and not static in another. Some coding
         guidelines advise against such practice due to the potential
         for programmer confusion.

    9104 octal escape sequence used -- Octal escape sequences can be
         problematic because the inadvertent introduction of a decimal
         digit (i.e. 8 or 9) ends the octal escape and introduces
         another character.  This diagnostic is not given for \0.

    9105 unsigned octal and hexadecimal literals require a 'U' suffix --
         The inclusion of such a suffix makes clear the value has
         unsigned type.

    9106 lower case literal suffix, 'String' -- Using upper case literal
         suffixes removes the potential for ambiguity with respect to
         literal values.

    9107 header cannot be included in more than one translation unit
         because of the definition of symbol 'Symbol' -- One set of
         guidelines advises the use of headers in such a way as to avoid
         the definition of objects or functions which occupy storage.

    9108 function 'Symbol' not declared at file scope -- A function
         declared at block scope will refer to a member of the enclosing
         namespace. Additionally, where a declaration statement could
         either declare a function or an object, the compiler will
         choose to declare the function. Declaring the function at file
         scope reduces the likelihood of confusion in both cases.

    9109 type 'Symbol' previously declared at location 'Location' --
         Having a single declaration of a type helps the compiler detect
         type incompatibility. One simple solution to ensure type
         declaration consistency is to declare a type in a header if it
         is used in multiple modules.

    9110 bit representation of a floating point type used -- The
         underlying bit representation of floating point values can
         differ from compiler to compiler, making reliance upon such
         representation non-portable.

    9111 boolean expression used with non-permitted operator 'String' --
         The use of expressions of bool with certain operators, such as
         the bitwise operators, is not likely to be either meaningful or
         intended.

    9112 plain char used with prohibited operator 'String' -- With the
         exception of the sequence of character values representing 0
         thru 9, the exact value of any other particular character is
         not guaranteed and reliance upon such an order is non-portable.

    9113 dependence placed on C/C++ operator precedence -- The use of
         parentheses instead of relying upon operator precedence can
         help make the code easier to understand.

    9114 implicit conversion of integer cvalue expression -- A prominent
         coding standard has defined the notion of a cvalue expression
         and, to help ensure operations in a given expression are
         performed within a particular fashion, the guidelines caution
         against such a value undergoing implicit conversions.

    9115 implicit conversion from integer to floating point type -- Such
         conversions between these two types of values can result in
         inexact representation.

    9116 implicit conversion of floating point cvalue expression -- A
         prominent coding standard has defined the notion of a cvalue
         expression and, to help ensure operations in a given expression
         are performed within a particular fashion, the guidelines
         caution against such a value undergoing implicit conversions.

    9117 implicit conversion changes signedness -- Some such conversions
         can lead to implementation defined behavior. Reliance upon such
         behavior is, therefore, not portable.

    9118 implicit conversion from floating point to integer type -- Such
         conversions between these two types of values can result in
         undefined behavior.

    9119 implicit conversion of integer to smaller type -- A prominent
         coding standard has defined the notion of an underlying type.
         Such conversions, when the underlying type is an integral type,
         can result in the loss of information.

    9120 implicit conversion of floating point to smaller type -- A
         prominent coding standard has defined the notion of an
         underlying type. Such conversions, when the underlying type is
         floating point type, can result in the loss of information.

    9121 cast of cvalue expression from integer to floating point type
         -- A prominent coding standard has defined the notion of a
         cvalue expression and the casting of such expressions does not
         change the type in which such expressions are evaluated.

    9122 cast of cvalue expression from floating point to integer type
         -- A prominent coding standard has defined the notion of a
         cvalue expression and the casting of such expressions does not
         change the type in which such expressions are evaluated.

    9123 cast of integer cvalue expression to larger type -- A prominent
         coding standard has defined the notion of a cvalue expression
         and the casting of such expressions does not change the type in
         which such expressions are evaluated.

    9124 cast of floating point cvalue expression to larger type -- A
         prominent coding standard has defined the notion of a cvalue
         expression and the casting of such expressions does not change
         the type in which such expressions are evaluated.

    9125 cast of cvalue expression changes signedness -- A prominent
         coding standard has defined the notion of a cvalue expression
         and an underlying type. Casting a cvalue expression from an
         (un)signed underlying type to the other may lead to a value
         inconsistent with expectations.

    9126 operators '~' and '<<' require recasting to underlying type for
         sub-integers -- A prominent coding standard has defined the
         notion of an underlying type. Casting an expression resulting
         from these operators, when the operand has an underlying type
         of unsigned char or unsigned short, reduces the risk of
         unexpected high order bits resulting from integral promotion.

    9127 disallowed use of non-character value String -- A prominent
         standard urges, since whether plain char is signed or unsigned
         is implementation defined, the char type be used only for
         character values.

    9128 plain char mixed with type other than plain char -- A prominent
         standard urges, since whether plain char is signed or unsigned
         is implementation defined, the char type not be mixed with
         other types.

    9129 disallowed use of non-numeric value String -- A prominent
         standard urges, since whether plain char is signed or unsigned
         is implementation defined, the signed char and unsigned char
         types not be used for character values.

    9130 bitwise operator 'String' applied to signed underlying type --
         A prominent coding standard has defined the notion of an
         underlying type and notes the fact bitwise operations are not
         typically meaningful when applied to operands of signed type
         and can even result in implementation defined behavior. As
         such, when the underlying type of an expression is signed,
         bitwise operations are discouraged.

    9131 non-postfix expression used with logical operator -- Using only
         postfix-expressions with logical operators helps to improve
         readability of the code. Note, this message is not given if the
         expression consists of either a sequence of only logical && or
         a sequence of only logical ||.

    9132 array type passed to function expecting a pointer --
         Array-to-pointer decay results in a loss of array bound
         information. A function depending upon an array to have a
         certain length, if that array decays to a pointer, can result
         in out-of-bounds operations, depending upon whether or not the
         bound of the original array matches with expectations.

    9133 boolean expression required for operator 'String' -- The use of
         non-bool operands with !, &&, or || is unlikely to be
         meaningful or intended. A more likely scenario is the
         programmer meant to use such an operand with one of the bitwise
         operators.

    9134 prohibited operator 'String' applied to unsigned underlying
         type -- A prominent coding standard has defined the notion of
         an underlying type and requires the named operator not be used
         with an expression with an unsigned underlying type because
         either (a) the operation is not meaningful if the underlying
         type is unsigned int or larger or (b) the operator is applied
         to an expression with an unsigned sub-int, which is not
         considered to be good practice.

    9135 unary operator & overloaded -- The unary operator & was
         overloaded.

    9136 out of bounds value for right hand side of shift operator --
         The value specified for the right hand side of a shift operator
         was out of bounds for the MISRA C++ underlying type on the left
         hand side of the operator.

    9137 floating point test for equality or inequality -- A floating
         point value was tested, directly or indirectly, for
         (in)equality with another value.

    9138 null statement not in line by itself -- A null statement was
         encountered that, before preprocessing, did not appear on a
         line by itself.  Comments following the null statement are
         allowed as long as there is whitespace separating the null
         statement from the comment.

    9139 case label follows default in switch statement -- A case label
         was encountered following the default label of a switch
         statement.

    9140 continue statement detected -- A continue statement appears
         outside what one author calls a "well-formed for loop". Said
         author advises against such usage in the interest of reducing
         code complexity.

    9141 global declaration of symbol 'Symbol' -- The specified symbol
         was declared in the global namespace.

    9142 non-global function, main, declared -- A function with the name
         'main' was declared that was not the global main function.

    9144 using-directive used -- A using directive was encountered.

    9145 using-directive/declaration in header file -- A using directive
         or using declaration was encountered in a header file.

    9146 multiple declarators in a declaration -- A declaration was
         encountered that contains multiple declarators.  For example:

               int i, j;

         will elicit this message.

    9147 function identifier 'Symbol' used without '&' or parenthesized
         parameter list -- The unadorned name of a function was
         encountered that was not part of a function call.

    9148 '=' should initialize either all enum members or only the first
         for enumerator 'Symbol' -- Unintentional duplication of
         enumerator values can occur when an enumeration consists of
         members with explicit and implicit values.

    9149 bit field must be explicitly signed integer, unsigned integer,
         or bool -- When using 'int' or 'wchar_t' as the bit-field type,
         it is implementation defined whether or not the type used is a
         signed type.  Explicitly specifying 'signed' or 'unsigned'
         makes it clear what type will be used as the underlying type.

    9150 non-private data member 'Symbol' within a non-POD structure --
         A member of a non-POD structure was declared public or
         protected.

    9151 public copy assignment operator in abstract class -- A public
         copy assignment operator was declared in an abstract class.

    9152 explicit specialization of overloaded function templates
         'String' and 'String' -- An explicit specialization of one of
         the named function templates was seen. Since explicit
         specializations are considered only after overload resolution
         chooses a best match from a set of primary function templates,
         at least one set of coding guidelines suggests avoiding such
         specialization to reduce the risk of developer confusion.

    9153 viable set contains both function 'Symbol' and template
         'Symbol' -- In a context where a name resolves either to a
         non-template function or to a specialization of a function
         template (typically a call), the set of viable candidates
         included both.

    9154 pointer expression thrown -- A pointer type was passed to a
         throw expression. It may not be clear who is responsible for
         cleaning up the pointed to object.

    9156 empty throw outside of a catch block -- An empty throw
         expression was encountered outside of a try-catch block.  An
         empty throw re-throws the currently handled exception. If there
         is no such exception std::terminate() will be called.  This is
         likely to be unintended.

    9158 '#define' used within a block for macro 'Name' -- A macro
         definition occured inside of a braced region such as in a
         function or class definition.  Such usage could imply the
         belief that the scope of the macro definition is limited to the
         braced region which is not the case.

    9159 '#undef' used within a block for macro 'Name' -- A macro was
         undefined inside of a braced region such as in a function or
         class definition.  Such usage could imply the mistaken belief
         that the scope of the directive is limited to the braced
         region.

    9160 all preprocessing directives must be valid -- The first token
         on a line was a '#' but was not part of a valid preprocessing
         directive.

    9162 use of 'String' at global scope -- Either a static_assert() or
         a using-declaration was seen at global scope, as indicated by
         the String.

    9163 increment/decrement operator combined with another operator --
         One of these two operators appears in combination with another
         arithmetic operator. At least one author advises against such
         practice for purposes of code readability and concerns about
         undefined behavior.

    9165 function 'Symbol' defined with a variable number of arguments
         -- The named function is defined to take a variable number of
         arguments. At least one author advises against such a practice
         because doing so avoids the type checking provided by the
         compiler.

    9166 function parameter list differs from prior
         declaration/overloaded function -- A function's parameter list
         has been found to differ from either the parameter list of a
         prior declaration of that function or from an overload of that
         function. At least one author recommends making counterpart
         parameters identical in name in the interest of documentation.
         Note: In the case of overloaded functions, if one function has
         fewer parameters than the other, only the number of parameters
         in the shorter parameter list are examined.


                    Gimpel Software
                    October, 2014
