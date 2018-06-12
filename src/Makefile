CC = gcc

FFLAGS = -I./ -I./engine/audio -I./src -I./hwvideo -I./engine -I./directx -I./frontend -I./hwaudio -I./sdl
CFLAGS = -Ofast -fno-rtti -fno-exceptions -fno-math-errno -fno-threadsafe-statics -Wall $(FFLAGS) `sdl-config --cflags --libs` -DSDL -DCOMPILE_SOUND_CODE
LDFLAGS = -Wl,--as-needed `sdl-config --libs` -lm -lstdc++
OUTPUT = cannonbal

SOURCES = main.cpp romloader.cpp roms.cpp trackloader.cpp utils.cpp video.cpp 
SOURCES += engine/oanimseq.cpp engine/oattractai.cpp engine/obonus.cpp engine/ocrash.cpp engine/oferrari.cpp engine/ohiscore.cpp engine/ohud.cpp engine/oinitengine.cpp engine/oinputs.cpp engine/olevelobjs.cpp engine/ologo.cpp engine/omap.cpp engine/omusic.cpp
SOURCES += engine/ooutputs.cpp engine/opalette.cpp engine/oroad.cpp engine/osmoke.cpp engine/osprite.cpp engine/osprites.cpp engine/ostats.cpp engine/otiles.cpp
SOURCES += engine/otraffic.cpp engine/outils.cpp engine/outrun.cpp engine/audio/osound.cpp engine/audio/osoundint.cpp frontend/config.cpp
SOURCES += frontend/menu.cpp frontend/ttrial.cpp
SOURCES += hwaudio/segapcm.cpp hwaudio/soundchip.cpp hwaudio/ym2151.cpp
SOURCES += hwvideo/hwroad.cpp hwvideo/hwsprites.cpp hwvideo/hwtiles.cpp
SOURCES += sdl/audio.cpp sdl/input.cpp sdl/renderbase.cpp sdl/rendersw.cpp sdl/timer.cpp
OBJS = ${SOURCES:.cpp=.o}

all: cannonball

%.o:		%.cpp
		$(CC) ${CFLAGS} -c -o $@ $?

cannonball:	${OBJS}
		$(CC) -o $@ $+ ${LDFLAGS}
	
clean:
	rm *.o src/*.o engine/audio/*.o engine/*.o hwvideo/*.o engine/*.o directx/*.o frontend/*.o hwaudio/*.o sdl/*.o sdl/*.o
	rm ${OUTPUT}
