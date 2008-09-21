import os
import sys


def getDebug():
    try:
        return int(os.environ[ 'DEBUG' ])
    except KeyError:
        return 0

env = Environment( ENV = os.environ );
config = env.Configure();

# env.Append( CCFLAGS = flags, CPPPATH = [ "../src" ] );

print "Use 'scons -h' for help"

prefix = '/usr/local/games'
bin = '/usr/local/bin'
if sys.platform == 'win32':
    try:
        Execute(Mkdir('gen'))
    except:
        pass

    prefix = 'gen'
    bin = 'gen'

opts = Options( 'rafkill.conf' )
opts.Add( PathOption('prefix', 'Directory to install under', prefix ) )
opts.Add( PathOption('bin', 'Directory where symlinked executable should go', bin ) )
opts.Update( env )
opts.Save( 'rafkill.conf', env )

Help( opts.GenerateHelpText( env ) )

if False:
    env.Append( CCFLAGS = [ '-Werror' ] )

if False:
    env.Append( CCFLAGS = [ '-pg' ] )
    env.Append( LINKFLAGS = [ '-pg' ] )

env.BuildDir( 'build/', 'src/' )
env.Append( LIBS = [ 'aldmb', 'dumb' ] );
if sys.platform == 'win32':
    env.Append( CCFLAGS = [ '-DWINDOWS' ] )
    env.Append( LIBS = [ 'alleg', 'pthreadGC2' ] )
else:
    env.ParseConfig( 'allegro-config --libs' );
    env.Append( LIBS = [ 'pthread' ] )

# print "Install directory = $prefix"
# print "Directory where symlinked binary will go = $bin"

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
buy-menu.pcx
buy-scene.pcx
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
logosmoot.pcx
raptor.dat
sound.dat
table.col
vulture.fnt
"""));

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
