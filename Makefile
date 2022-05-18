all:
	g++ -ID:\GameLib\SDL2-2.0.20\x86_64-w64-mingw32\include -LD:\GameLib\SDL2-2.0.20\x86_64-w64-mingw32\lib -o main main.cpp BaseObject.cpp base.cpp GameMap.cpp MainPlayer.cpp Timer.cpp BulletObject.cpp ThreatObject.cpp ExplosionObject.cpp TextObject.cpp PlayerPower.cpp Geometric.cpp BossObject.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer