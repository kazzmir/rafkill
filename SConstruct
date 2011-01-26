import os
import sys


def getDebug():
    try:
        return int(os.environ[ 'DEBUG' ])
    except KeyError:
        return 0


def usePandora():
    try:
        return "pandora" in ARGUMENTS[ 'env' ]
    except KeyError:
        return False

env = Environment( ENV = os.environ );
config = env.Configure();

# env.Append( CCFLAGS = flags, CPPPATH = [ "../src" ] );

prefix = '/usr/local/games'
bin = '/usr/local/bin'
if sys.platform == 'win32':
    try:
        Execute(Mkdir('gen'))
    except:
        pass

    prefix = 'gen'
    bin = 'gen'

if False:
    env.Append( CCFLAGS = [ '-Werror' ] )

if False:
    env.Append( CCFLAGS = [ '-pg' ] )
    env.Append( LINKFLAGS = [ '-pg' ] )

env.VariantDir( 'build/', 'src/' )
env.Append( LIBS = [ 'aldmb', 'dumb' ] );
if sys.platform == 'win32':
    env.Append( CCFLAGS = [ '-DWINDOWS' ] )
    env.Append( LIBS = [ 'alleg', 'pthreadGC2' ] )
elif usePandora():
    print "Using pandora Config"
    prefix = '/mnt/utmp'
    bin = '/mnt/utmp/rafkill/bin'
    env['CC'] = os.environ['CC']
    env['CXX'] = os.environ['CXX']
    env['LD'] = os.environ['CC']
    env['AS'] = os.environ['AS']
    env['AR'] = os.environ['AR']
    env.Append(CPPDEFINES = ['PANDORA'])
    env.Append( LINKFLAGS = [ '-L/mnt/utmp/rafkill/lib' ] )
    env.Append( LIBS = [ 'pthread', 'alleg' ] )
    flags = ['-pipe', '-march=armv7-a', '-mtune=cortex-a8', '-mfpu=neon', '-mfloat-abi=softfp', '-ftree-vectorize', '-ffast-math', '-fsingle-precision-constant', '-DINSTALL_DIR=\\\"$prefix\\\"' ]
else:
    env.ParseConfig( 'allegro-config --libs' );
    env.Append( LIBS = [ 'pthread' ] )


print "Use 'scons -h' for help"
opts = Options( 'rafkill.conf' )
opts.Add( PathOption('prefix', 'Directory to install under', prefix ) )
opts.Add( PathOption('bin', 'Directory where symlinked executable should go', bin ) )
opts.Update( env )
opts.Save( 'rafkill.conf', env )
Help( opts.GenerateHelpText( env ) )

# print "Install directory = $prefix"
# print "Directory where symlinked binary will go = $bin"

if not usePandora():
    flags = [ '-Wall', '-fno-rtti', '-Woverloaded-virtual', '-DINSTALL_DIR=\\\"$prefix\\\"' ];
if getDebug():
    flags.append("-g3")
else:
    flags.append("-O2")

env.Append( CCFLAGS = flags, CPPPATH = [ "build" ] )

# SConscript( 'src/SConscript', build_dir='build', exports = 'env' );
sources = SConscript( 'src/SConscript', exports = 'env' );
rafkill = env.Program( 'rafkill', map( lambda x: 'build/' + x, sources ) )

def installReminder( target, source, env ):
    print
    print "Run 'scons install' to install rafkill"
    return 0

def ShutUp( target, source, env ):
    pass

env.AddPostAction( rafkill, Action( installReminder, strfunction=ShutUp ) )
env.Default( rafkill )
# rafkill = env.Install( '.', 'build/rafkill' );

# env.Default( rafkill )

# package = env.Install( '.', 'source.tar' )
env.Alias( 'package', 'src/source.tar' )

def install( target, source, env ):
	print "Installing!"
	return 0

installDir = '$prefix/'

## Install binary
env.Install( installDir + 'rafkill', rafkill )
def addData( file ):
	env.Install( installDir + 'rafkill/data', "data/%s" % file )

map( lambda x: addData( x ), Split( """
1.pck
2.pck
3.pck
beast.fnt
fonts.dat
intro.mod
level1.lev
level2.lev
level3.lev
level4.lev
level5.lev
level6.lev
level7.lev
level8.lev
raptor.dat
sound.dat
table.col
vulture.fnt
"""));
if usePandora():
    addData("buy-menu-pandora.pcx");
    addData("buy-scene-pandora.pcx");
    addData("logosmoot-pandora.pcx");
else:
    addData("buy-menu.pcx");
    addData("buy-scene.pcx");
    addData("logosmoot.pcx");

def addMusic( file ):
	env.Install( installDir + 'rafkill/music', "music/%s" % file )

def songFile( song ):
	import re
	types = [ '.*\.s3m$', '.*\.mod$', '.*\.it$', '.*\.xm$' ]
	for type in types:
		if re.compile( type ).match( song.lower() ):
			return True
	return False

for i in os.listdir( 'music' ):
	if songFile( i ):
		addMusic( i )

installSymlink = '$bin/'

def makeSymLink( target, source, env ):
	# srcFile = os.path.abspath( str(source[ 0 ]) )
	srcFile = source[ 0 ]
	env.Execute( Action( 'ln -s %s %s' % (srcFile,target[0]) ) )

# SymLink = Builder( action = "ln -s $SOURCES $TARGET" )
SymLink = Builder( action = Action( makeSymLink ) )

env.Append( BUILDERS = { 'SymLink' : SymLink } )

# link = env.SymLink( target = 'rafkill-link', source = '$prefix/rafkill/rafkill' )

# env.InstallAs( target = installSymlink + 'rafkill', source = link )
# env.Install( installSymlink + 'rafkill', link )

# print 'Absolute path = ' + os.path.abspath( '$prefix/rafkill/rafkill' )

# xpath = os.path.abspath( 'rafkill' )

xpath = '$prefix/rafkill/rafkill'

# print "XPath = " + xpath

# env.SymLink( '$bin/rafkill', os.path.abspath( '$prefix/rafkill/rafkill' ) )
if sys.platform != 'win32':
	env.SymLink( '$bin/rafkill', xpath )

env.Alias( 'install', installDir )
env.Alias( 'install', installSymlink )
