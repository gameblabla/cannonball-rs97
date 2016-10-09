CXX = g++

CFLAGS = -g -Wall $(FFLAGS) `sdl2-config --cflags --libs` -DSDL2 -DWITH_OPENGLES -DCOMPILE_SOUND_CODE
FFLAGS = -I./ -I./engine/audio -I./src -I./hwvideo -I./cannonboard -I./engine -I./directx -I./frontend -I./hwaudio -I./sdl
LDFLAGS = -Wl,--as-needed `sdl2-config --libs` -lm -lboost_filesystem -lGLESv2
OUTPUT = cannonbal

SOURCES = main.cpp romloader.cpp roms.cpp trackloader.cpp utils.cpp video.cpp cannonboard/asyncserial.cpp cannonboard/interface.cpp directx/ffeedback.cpp engine/oanimseq.cpp engine/oattractai.cpp engine/obonus.cpp engine/ocrash.cpp engine/oferrari.cpp engine/ohiscore.cpp engine/ohud.cpp engine/oinitengine.cpp engine/oinputs.cpp engine/olevelobjs.cpp engine/ologo.cpp engine/omap.cpp engine/omusic.cpp engine/ooutputs.cpp engine/opalette.cpp engine/oroad.cpp engine/osmoke.cpp engine/osprite.cpp engine/osprites.cpp engine/ostats.cpp engine/otiles.cpp engine/otraffic.cpp engine/outils.cpp engine/outrun.cpp engine/audio/osound.cpp engine/audio/osoundint.cpp frontend/cabdiag.cpp frontend/config.cpp frontend/menu.cpp frontend/ttrial.cpp	 hwaudio/segapcm.cpp	hwaudio/soundchip.cpp hwaudio/ym2151.cpp hwvideo/hwroad.cpp hwvideo/hwsprites.cpp hwvideo/hwtiles.cpp sdl2/audio.cpp sdl2/input.cpp sdl2/renderbase.cpp sdl2/rendergles.cpp sdl2/timer.cpp
OBJS = ${SOURCES:.cpp=.o}

all: cannonball

%.o:		%.cpp
		$(CXX) -c -o $@ $? ${CFLAGS}

cannonball:	${OBJS}
		$(CXX) -o $@ $+ ${LDFLAGS}
	
clean:
	rm *.o src/*.o engine/audio/*.o engine/*.o hwvideo/*.o cannonboard/*.o engine/*.o directx/*.o frontend/*.o hwaudio/*.o sdl/*.o sdl2/*.o
	rm ${OUTPUT}
